""""
Clayton Nguyen
CPSC 4510
Project 2: RDT
May 12, 2022
"""
"""
This project simulates a reliable data transfer on top of the UDP protocol transport layer.
This file simulates the sending side of the transmissions, will send packets and resend packets
if not acked or corrupt
"""

from socket import *
import util

# helper function to provide easy destructuring of a packet
def destructure_message(msg):
    received = []
    for byte in msg:
        received.append(byte)

    checksum = received[8:10]
    seq = util.getSeq(received[11])
    ack = util.getAck(received[11])
    data = received[12:]
    packet = received
    return checksum, seq, ack, data, packet


class Sender:
    # class instance to keep track of the packet numbers and the seq number
    def __init__(self):
        """
        Your constructor should not expect any argument passed in,
        as an object will be initialized as follows:
        sender = Sender()

        Please check the main.py for a reference of how your function will be called.
        """
        self.expected_seq_num = 0
        self.packet_num = 1

    def rdt_send(self, app_msg_str):
        """realibly send a message to the receiver (MUST-HAVE DO-NOT-CHANGE)

        Args:
          app_msg_str: the message string (to be put in the data field of the packet)

        """
        # variable to initialize the sender socket and sending functions
        server_name = 'cs1.seattleu.edu'
        port = 10245
        sender_socket = socket(AF_INET, SOCK_DGRAM)
        packet_ack = 0
        packet_seq = self.expected_seq_num

        print('original message string: ' + app_msg_str)

        # creates the packet in bytes with checksum included
        send_packet = util.make_packet(app_msg_str, packet_ack, packet_seq)

        print('packet created: ', send_packet)

        # send packet to the server at the corresponding port
        sender_socket.sendto(send_packet, (server_name, port))

        # set timeout to activate after two seconds of socket inactivity
        sender_socket.settimeout(2)

        print('packet num.' + str(self.packet_num) + ' is successfully sent to the receiver.')
        self.packet_num += 1

        # get the message back from receiver in bytes and their address
        message_from_receiver, receiver_addr = self.get_message(sender_socket, send_packet, server_name, port, app_msg_str)

        # get all the data from the packet, seq and ack is an int, everything else is a list of integers
        # representing their binary formats in the packet
        checksum, seq, ack, data, packet = destructure_message(message_from_receiver)

        # checks to see if the ack number is correct, if the seq number is the same, and packet is not
        # corrupt from the message received from the ack packet
        self.check_ack_and_checksum(seq, ack, message_from_receiver, app_msg_str, sender_socket, send_packet, server_name, port)

        # formatting prints
        print()
        print()

        # flips sequence number to be 1 or 0 based on the current seq number
        if self.expected_seq_num == 0:
            self.expected_seq_num = 1
        else:
            self.expected_seq_num = 0



        # close the socket
        sender_socket.close()

        ####### Your Sender class in sender.py MUST have the rdt_send(app_msg_str)  #######
        ####### function, which will be called by an application to                 #######
        ####### send a message. DO NOT Change the function name.                    #######
        ####### You can have other functions as needed.                             #######

    # receives ack message from receiver, checks to see if a timeout occured, if it did
    # then resend the packet to the receiver and get the ack message
    def get_message(self, sender_socket, send_packet, server_name, port, app_msg_str):
        message_from_receiver = None
        receiver_addr = None
        try:
            message_from_receiver, receiver_addr = sender_socket.recvfrom(2048)
        except timeout:
            print('socket timeout! resend')
            print('')
            print('')

            sender_socket.sendto(send_packet, (server_name, port))
            print('[timeout retransmission]: ' + app_msg_str)
            print('packet num.' + str(self.packet_num) + ' is successfully sent to the receiver.')
            self.packet_num += 1
            message_from_receiver, receiver_addr = sender_socket.recvfrom(2048)

        return message_from_receiver, receiver_addr

    # checks to see if the seq numbers of the ack message match up with the senders seq number
    # also checks the ack to match the seq number and the integrity of the data by verifying the checksum
    # if any one of that is not fulfilled, then will resend the packet to the receiver. Checks again
    # if the seq number and ack number is correct and the checksum is correct
    def check_ack_and_checksum(self, seq, ack, message_from_receiver, app_msg_str, sender_socket, send_packet, server_name, port):
        if seq == self.expected_seq_num and seq == ack and util.verify_checksum(message_from_receiver):
            print('packet is received correctly: seq. num ' + str(self.expected_seq_num) + ' = ACK num ' + str(ack) + '. all done!')
        else:
            print('receiver acked the previous pkt, resend!')
            print()
            print()
            print('[ACK-Previous retransmission]: ' + app_msg_str)
            sender_socket.sendto(send_packet, (server_name, port))
            print('packet num.' + str(self.packet_num) + ' is successfully sent to the receiver.')
            self.packet_num += 1
            message_from_receiver, receiver_addr = sender_socket.recvfrom(2048)
            checksum, seq, ack, data, packet = destructure_message(message_from_receiver)

            if seq == self.expected_seq_num and seq == ack and util.verify_checksum(message_from_receiver):
                print('packet is received correctly: seq. num ' + str(self.expected_seq_num) + ' = ACK num ' + str(ack) + '. all done!')
            else:
                print('packet not received correctly')