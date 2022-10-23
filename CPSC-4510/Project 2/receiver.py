""""
Clayton Nguyen
CPSC 4510
Project 2: RDT
May 12, 2022
"""
"""
This project simulates a reliable data transfer on top of the UDP protocol transport layer.
File simulates the receiving side of the transmissions, will ack packets and simulate
timeouts and packet corruption
"""

import time
from socket import *
import util

# helper function to pad the left side of binary integers
def big_endian(binary, padding):
    if len(binary) < padding:
        remaining = padding - len(binary)
    for x in range(remaining):
        binary = "0" + binary
    return binary

# helper function to get the ack number from an 8-bit binary number
def getAck(byteStream):
    eight_bits = big_endian(format(byteStream, "b"), 8)
    return int(eight_bits[6])

# helper function to get the seq number from an 8-bit binary number
def getSeq(byteStream):
    eight_bits = big_endian(format(byteStream, "b"), 8)
    return int(eight_bits[7])

# helper function to provide easy destructuring of a packet
def destructure_message(msg):
    received = []
    for byte in msg:
        received.append(byte)

    checksum = received[8:10]
    seq = getSeq(received[11])
    ack = getAck(received[11])
    data = received[12:]
    packet = received
    return checksum, seq, ack, data, packet


def main():
    # variables needed to connect to socket and for packet recognition
    receiver_port = 10245
    receiver_socket = socket(AF_INET, SOCK_DGRAM)
    receiver_socket.bind(('', receiver_port))
    number = 1
    previous_packet = None

    while True:
        msg, sender_addr = receiver_socket.recvfrom(1024)

        # get data from packet, in an int list, ready to be converted
        # into a byte string, seq and ack are ints
        checksum, seq, ack, data, packet = destructure_message(msg)

        # create packet in bytes with checksum and seq num == ack num
        send_packet = util.make_packet(bytes(data).decode(), seq, seq)

        print('packet num.' + str(number) + ' received:', bytes(packet))

        # message payload in string format
        message = bytes(data).decode()

        # check if the checksum is the same as the data's
        # if not, reack previous packet
        if util.verify_checksum(msg):
            # if the packet numbers are divisible by 6, simulate packet loss, resend after 2 seconds
            # if the packet numbers are divisible by 3, simulate bit errors, reack the previous packet
            # if either, ack the new packet and send to the sender
            if number % 6 == 0:
                print('simulating packet loss: sleep a while to trigger timeout event on the sender side...')
                time.sleep(2)
                receiver_socket.sendto(send_packet, sender_addr)
            elif number % 3 == 0:
                print('simulating packet bit errors/corrupted: ACK the previous packet!')
                receiver_socket.sendto(previous_packet, sender_addr)
            else:
                print('packet is expected, message string delivered: ' + message)
                receiver_socket.sendto(send_packet, sender_addr)
                print('packet is delivered, now creating and sending the ACK packet...')
        else:
            print('The checksum is incorrect, bit errors/corrupted: ACK the previous packet!')
            receiver_socket.sendto(previous_packet, sender_addr)

        # formatting prints to match
        print('all done for this packet!')
        print('')
        print('')

        # store the previous packet so that we can ack the previous packet easily
        previous_packet = send_packet

        # increment packet numbers received by 1 each time a packet is received
        number += 1


if __name__ == '__main__':
    main()