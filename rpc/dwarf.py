import sys
from elftools.elf.elffile import ELFFile

class C_Type(object):

    def __init__(self, is_ptr = False, base_type = None, size = 0, parent = None):
        self.is_ptr = is_ptr
        self.base_type = base_type
        self.size = size
        self.parent = parent

    def __str__(self):
        return f"{self.base_type}" + ("*" if self.is_ptr else "")

    def get_root(self):
        return self if self.parent is None else self.parent.get_root()

def process_file(filename):
    print('Processing file:', filename)
    with open(filename, 'rb') as f:
        elffile = ELFFile(f)

        if not elffile.has_dwarf_info():
            print('  file has no DWARF info')
            return

        # get_dwarf_info returns a DWARFInfo context object, which is the
        # starting point for all DWARF-based processing in pyelftools.
        dwarfinfo = elffile.get_dwarf_info()
        # Iterate over all CUs (Compile Units, aka source files)
        for CU in dwarfinfo.iter_CUs():

            # Start with the top DIE, the root for this CU's DIE tree
            top_DIE = CU.get_top_DIE()

            cu_path = top_DIE.get_full_path()

            if "main" in cu_path:
                print(f"Inspecting {cu_path}")

                functions = []
                # Iterate over the children of the top_DIE and look for the ones that refer to
                # functions (subprograms)
                for child in top_DIE.iter_children():
                    if child.tag == "DW_TAG_subprogram":
                        f_name = child.attributes['DW_AT_name'].value
                        print(f"\nFound function {f_name}")
                        # Get the return type if "DW_AT_type" attribute is present, otherwise it's "void"
                        f_return_type = get_return_type(child)
                        print(f"\tFound return type {f_return_type} ({f_return_type.size} bytes)")
                        f_attributes = get_parameters(child)

def get_return_type(die):
    type_object = None
    type = die.attributes.get("DW_AT_type")
    if type is not None:
        # type is not None, meaning the function returns "something", in order to decode what it is,
        # we need to get the DIE for the "DW_AT_type"
        type_die = die.get_DIE_from_attribute("DW_AT_type")
        type_name = type_die.tag
        type_object = C_Type()
        while type_name != "DW_TAG_base_type":
            if type_name == "DW_TAG_pointer_type":
                if type_object.is_ptr and type_object.base_type is None:
                    type_object.base_type = C_Type(parent=type_object)
                    type_object = type_object.base_type
                type_object.is_ptr = True
                # print(f"\t\tReturn type is a pointer")
                type_object.size = type_die.attributes['DW_AT_byte_size'].value
                # print(f"\t\tSize of this return type is {type_object.size}")

            else:
                # print(f"\t\tThe name of this return type is {type_die.attributes['DW_AT_name'].value}")
                pass

            type_die = type_die.get_DIE_from_attribute("DW_AT_type")
            type_name = type_die.tag

        type_object.base_type = type_die.attributes['DW_AT_name'].value.decode("utf-8")
        # print(f"\t\tThe base type is {type_object.base_type}")
        type_object.size = type_die.attributes['DW_AT_byte_size'].value if not type_object.size else  type_object.size
        # print(f"\t\tSize of this return type is {type_object.size}")

        type_object = type_object.get_root()
    return type_object or C_Type(base_type="void")


def get_parameters(die):
    # We need to inspect the children of the die and retrieve the ones of type "DW_TAG_formal_parameter"
    for child in die.iter_children():
        if child.tag == "DW_TAG_formal_parameter":
            print(f"\tFound parameter {child.attributes['DW_AT_name'].value.decode('utf-8')}")
            f_return_type = get_return_type(child)
            print(f"\t\tType {f_return_type} ({f_return_type.size} bytes)")

    pass


if __name__ == '__main__':
    filename = sys.argv[1]
    process_file(filename)