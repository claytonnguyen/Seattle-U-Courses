""""
Clayton Nguyen
CPSC 4510
Project 2: RDT
May 12, 2022
"""
"""
This project simulates a reliable data transfer on top of the UDP protocol transport layer.
This file is has helper functions that help with checksum verification and creation, and creation
of the packet in bytes
"""

# creates the checksum based on the byte string with no checksum
# header field with 8 bytes for prefix, 2 bytes for checksum, 2 bytes for length, ack num, and seq num
# translate the header bytes into binary treat 16 bit groups as an integer to
# add them together (checksum addition of all groups with a carryover) then
# you will ones complement the last result and that will be the checksum of the
# packet -------> packet header and data w/o checksum binary addition
def create_checksum(packet_wo_checksum):
    """create the checksum of the packet (MUST-HAVE DO-NOT-CHANGE)

    Args:
      packet_wo_checksum: the packet byte data (including headers except for checksum field)

    Returns:
      the checksum in bytes

    """

    packet_in_binary_list =[]

    for byte in packet_wo_checksum:
        packet_in_binary_list.append(big_endian(format(byte, "b"), 8))

    # separates the packet bytes into two bytes (16-bits) to be computed in an addition function
    # works with odd numbered length of bytes as the left side is padded to be added in the function
    # goes through the int representation of bytes list two bytes at a time and concatentates them to
    # create 16-bit versions which then be called with binaryAddition(num1, num2)
    first_bits = packet_in_binary_list[0] + packet_in_binary_list[1]
    for x in range(2, len(packet_in_binary_list), 2):
        if x + 1 < len(packet_in_binary_list):
            second_bits = packet_in_binary_list[x] + packet_in_binary_list[x+1]
        else:
            second_bits = "00000000" + packet_in_binary_list[x]
        first_bits = binaryAddition(first_bits, second_bits)

    # ones complement the result of the binary addition
    ones_comp = ''
    for x in range(len(first_bits)):
        if first_bits[x] == '0':
            ones_comp = ones_comp + '1'
        else:
            ones_comp = ones_comp + '0'

    first_part = ones_comp[0:8]
    second_part = ones_comp[8:16]
    int_representation = [int(first_part, 2), int(second_part, 2)]

    return bytes(int_representation)

# verifies if the checksum in the packet also matches
# a recalculated checksum done on the bytes in the packet
# both checksums should equal each other if no corruption occurred
# returns True when no corruption occurred, returns False otherwise
def verify_checksum(packet):
    """verify packet checksum (MUST-HAVE DO-NOT-CHANGE)

    Args:
      packet: the whole (including original checksum) packet byte data

    Returns:
      True if the packet checksum is the same as specified in the checksum field
      False otherwise

    """
    # -------> packet header and data w/o checksum binary addition and the result
    # of all these bits will be the opposite of the checksum, binary addition with
    # the checksum will result in a 16 bit integer with all bits set to one
    # if the binary addition of the packet header and checksum and data is not all
    # 1's in the bits, then the packet was corrupted

    list_of_bytes = []

    for byte in packet:
        list_of_bytes.append(byte)

    checksum = bytes(list_of_bytes[8:10])
    packet_wo_checksum = bytes(list_of_bytes[0:8] + list_of_bytes[10:])

    recalculated_checksum = create_checksum(packet_wo_checksum)

    if checksum == recalculated_checksum:
        return True
    else:
        return False

# creates a packet based on a string from the top level, an ack num, and a seq num
def make_packet(data_str, ack_num, seq_num):
    """Make a packet (MUST-HAVE DO-NOT-CHANGE)

    Args:
      data_str: the string of the data (to be put in the Data area)
      ack: an int tells if this packet is an ACK packet (1: ack, 0: non ack)
      seq_num: an int tells the sequence number, i.e., 0 or 1

    Returns:
      a created packet in bytes

    """
    # make sure your packet follows the required format!

    data_bytes = data_str.encode()  # data in bytes
    packet_header = "COMPNETW".encode()  # header in bytes
    data_bytes_length = len(data_bytes)  # length of data in bytes
    default_header_bytes_length = 12  # length of header in bytes
    packet_length = data_bytes_length + default_header_bytes_length  # length of packet in bytes

    # data length cannot exceed (16383 - 12 (header size)) = 16371 bytes
    packet_length_bits = format(packet_length, "b")
    # pads the length bits to match 14 bits in the format
    packet_length_bits = big_endian(packet_length_bits, 14)

    length_ack_and_seq = packet_length_bits + str(ack_num) + str(seq_num)
    first_part = int(length_ack_and_seq[0:8], 2)
    second_part = int(length_ack_and_seq[8:16], 2)
    int_representation = [first_part, second_part]
    eleven_and_twelve_byte = bytes(int_representation)

    # create packet_without_checksum in bytes
    packet_without_checksum = packet_header + eleven_and_twelve_byte + data_bytes

    # create the checksum with the packet_without_checksum
    checksum = create_checksum(packet_without_checksum)

    # combine all the packet components, packet header, checksum, length, ack, seq and data into
    # the final packet being sent as a byte string
    final_packet = packet_header + checksum + eleven_and_twelve_byte + data_bytes

    return final_packet

###### These three functions will be automatically tested while grading. ######
###### Hence, your implementation should not make any changes to         ######
###### the above function names and args list.                           ######
###### You can have other helper functions if needed.                    ######  

# helper function to pad the left side of binary integers
def big_endian(binary, padding):
    if len(binary) < padding:
        remaining = padding - len(binary)
    for x in range(remaining):
        binary = "0" + binary
    return binary


# helper function that is similar to a reduce function that takes in two 16 bit
# binary numbers and adds them together accounting for overflow
def binaryAddition(num1, num2):
    summation = bin(int(num1, 2) + int(num2, 2))
    while len(summation[2:]) == 17:
        summation = bin(int(summation[3:], 2) + int("0000000000000001", 2))
        summation = big_endian(summation[2:], 16)
        if len(summation) == 16:
            break
        else:
            summation = "0b" + summation

    summation = summation[2:]

    if len(summation) < 16:
        padding = 16 - len(summation)
        for x in range(padding):
            summation = "0" + summation

    return summation


# helper function to get the ack number from an 8-bit binary number
def getAck(byteStream):
    eight_bits = big_endian(format(byteStream, "b"), 8)
    return int(eight_bits[6])


# helper function to get the seq number from an 8-bit binary number
def getSeq(byteStream):
    eight_bits = big_endian(format(byteStream, "b"), 8)
    return int(eight_bits[7])