from multiprocessing import connection
import serial
import struct
import array
import time

connection = serial.Serial('/dev/cu.usbmodem3777386930301')  # open serial port

# # Call the testInt() function.
# connection.write(struct.pack('B', 0x00))
# print(struct.unpack('<h', connection.read(2))[0])

# # Call the testFloat() function.
# connection.write(struct.pack('B', 0x01))
# print(struct.unpack('<f', connection.read(4))[0])

for i in range(1000):
    print(f"\n\nIteration {i}")
    nums = [x for x in range(128)]
    nums_array = array.array('B', nums)
    print(f"nums = {nums}")
    connection.write(nums_array)

    half_one = list(struct.unpack('<64B', bytearray(connection.read(64))))
    print(f"half_one = {half_one}")
    half_two = list(struct.unpack('<64B', bytearray(connection.read(64))))
    print(f"half_two = {half_two}")

    values = half_one + half_two

    assert nums == values, "Lists are different"

# Call the add() function.
# connection.write(struct.pack('B', 0x02))
# connection.write(struct.pack('<h', 5))
# connection.write(struct.pack('<h', 6))
# r_value = struct.unpack('<h', connection.read(2))[0]
# print(f"0x{r_value:08x}")
# print(f"Result of add = {r_value}\n")

# # Call the testInt() function.
# connection.write(struct.pack('B', 0x00))
# print(f"Result of testInt = {struct.unpack('<h', connection.read(2))[0]}\n")

# # Call the add() function.
# connection.write(struct.pack('B', 0x02))
# connection.write(struct.pack('<h', 8))
# connection.write(struct.pack('<h', 10))
# r_value = struct.unpack('<h', connection.read(2))[0]
# print(f"0x{r_value:08x}")
# print(f"Result of add = {r_value}\n")

# Call the setLed() function.
# connection.write(struct.pack('B', 0x03))
# connection.write(struct.pack('B', 18))
# print(struct.unpack('<h', connection.read(2))[0])

# while True:
#     # Call the setLed() function.
#     connection.write(struct.pack('B', 0x03))
#     connection.write(struct.pack('B', 15))
#     print(struct.unpack('<h', connection.read(2))[0])

#     time.sleep(1)

#     # Call the setLed() function.
#     connection.write(struct.pack('B', 0x03))
#     connection.write(struct.pack('B', 0))
#     print(struct.unpack('<h', connection.read(2))[0])

# import time
# from simple_rpc import Interface

# interface = Interface("/dev/tty.usbmodem4103")
# # print(list(interface.device['methods']))

# add = interface.add(7+2)

# print(add)

# led = 0

# while True:
#     led = not led
#     interface.set_led(led)
#     time.sleep(1)