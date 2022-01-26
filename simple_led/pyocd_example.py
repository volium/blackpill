from pyocd.core.helpers import ConnectHelper
from pyocd.core.target import Target
from pyocd.debug.elf.symbols import ELFSymbolProvider
from pathlib import Path
import logging

# Change longing level here
# logging.basicConfig(level=logging.DEBUG)

# Connect to the target
with ConnectHelper.session_with_chosen_probe(target_override="stm32f411ce") as session:
    target = session.target

    # Set ELF file on target
    elf_path = Path(__file__).parent / "build/simple_led.elf"
    target.elf = str(elf_path)

    print(f"Target State = {target.get_state()}")

    # Look up address of main()
    provider = ELFSymbolProvider(target.elf)
    main_address = provider.get_symbol_value("main")

    print(f"Address of main() function is: {main_address:#010x}")

    # Address may have LSB set if in "Thumb mode"
    if main_address & 0x1:
        print(f"Thumb mode is enabled")
        # Mask the LSB so addresses from PC matches
        main_address &= ~1

    print(f"Address of main() function is: {main_address:#010x}")

    # Set breakpoint
    print(f"Setting breakpoint at: {main_address:#010x}")
    target.set_breakpoint(main_address, Target.BreakpointType.HW)

    br = target.find_breakpoint(0x08000614)
    print(f"Breakpoint enabled = {br.enabled}")

    # Breakpoint shouldn't be enabled yet
    assert br.enabled == False

    # We now "run" the target, either stepping or resuming
    print(f"Advancing target...")
    # target.step()
    target.resume()

    print(f"Target State = {target.get_state()}")

    br = target.find_breakpoint(0x08000614)
    print(f"Breakpoint enabled = {br.enabled}")

    # Breakpoint should be enabled now
    assert br.enabled == True

    # Reset target to start from the beginning
    print(f"Resetting target...")
    target.reset()
    print(f"Target State = {target.get_state()}")

    # Resume target
    print(f"Resumming target...")
    target.resume()
    print(f"Target State = {target.get_state()}")

    br = target.find_breakpoint(0x08000614)
    print(f"Breakpoint enabled = {br.enabled}")

    # Breakpoint should still be enabled
    assert br.enabled == True

    # Wait until breakpoint is hit
    while target.get_state() != Target.State.HALTED:
        pass

    # Print PC
    pc = target.read_core_register("pc")
    print(f"PC value: {pc:#010x}")

    assert pc == main_address, f"PC ({pc:#010x}) does not match expected value ({main_address:#010x})"
    print(f"Address of main() function and PC value match, breakpoint was set and hit as expected")

    # Remove breakpoint
    target.remove_breakpoint(main_address)
