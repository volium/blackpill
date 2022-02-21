from multiprocessing import connection
import serial
import struct
import array
import time

connection = serial.Serial('/dev/cu.usbmodem3777386930301')  # open serial port

# # TEST FOR CDC
# for i in range(1000):

#     print(f"\n\nIteration {i}")
#     nums = [x for x in range(128)]
#     nums_array = array.array('B', nums)
#     print(f"nums = {nums}")
#     connection.write(nums_array)

#     # for i in nums:
#     #     connection.write(struct.pack('B', i))

#     # half_one = []
#     # half_two = []
#     # for i in nums:
#     #     half_one.append(struct.unpack('<B', connection.read(1))[0])
#     #     print(half_one)

#     # print("done half one")

#     # for i in nums:
#     #     half_two.append(struct.unpack('<B', connection.read(1))[0])
#     #     print(half_two)

#     # print("done half two")

#     half_one = list(struct.unpack('<64B', bytearray(connection.read(64))))
#     print(f"half_one = {half_one}")
#     half_two = list(struct.unpack('<64B', bytearray(connection.read(64))))
#     print(f"half_two = {half_two}")

#     values = half_one + half_two

#     assert nums == values, "Lists are different"
# # TEST FOR CDC

led = 0
for i in range(100):

    print(f"Iteration {i}")

    # Call the testInt() function.
    connection.write(struct.pack('B', 0x00))
    r_value = struct.unpack('<h', connection.read(2))[0]
    print(f"Result of testInt = {r_value}\n")
    assert int(r_value) == 42, f"r_value has unexpected value {r_value}"

    # Call the testFloat() function.
    connection.write(struct.pack('B', 0x01))
    r_value = struct.unpack('<f', connection.read(4))[0]
    print(f"Result of testFloat = {r_value}\n")
    assert float(r_value) == 3.1415927410125732, f"r_value has unexpected value {r_value}"

    # Call the add() function.
    connection.write(struct.pack('B', 0x02))
    connection.write(struct.pack('<h', 5))
    connection.write(struct.pack('<h', 6))
    r_value = struct.unpack('<h', connection.read(2))[0]
    print(f"Result of add = {r_value}\n")
    assert int(r_value) == 11, f"r_value has unexpected value {r_value}"

    # Call the setLed() function.
    led = not led;
    connection.write(struct.pack('B', 0x03))
    connection.write(struct.pack('B', led))
    r_value = struct.unpack('<h', connection.read(2))[0]
    print(f"Result of setLed = {r_value}\n")
    assert int(r_value) == led, f"r_value has unexpected value {r_value}"

    time.sleep(0.045)

# Turn off LED
connection.write(struct.pack('B', 0x03))
connection.write(struct.pack('B', 0x1))
r_value = struct.unpack('<h', connection.read(2))[0]
print(f"Result of setLed = {r_value}\n")
assert int(r_value) == 0x1, f"r_value has unexpected value {r_value}"