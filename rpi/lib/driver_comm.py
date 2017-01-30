""" Module to implement the communication protocol between the Raspberry Pi
    and the Arduino in Roberto over a serial port.

    The communication protocol is based on HLDLC with ARQ-StopAndWait error control.
"""

import serial
import sys
from time import sleep
from threading import Thread

ACK_COMMAND = 0x01
MAX_RETRIES = 3

START_FLAG = 0x7E
ESCAPE_FLAG = 0x7D

class PacketFrame(object):
    """ Class to implement the packet frame functionality """
    def __init__(self, seq_number, command, payload):
        self.seq_number = seq_number
        self.command = command
        self.payload_length = len(payload)
        self.payload = payload

    def invert_bit_5(self, val):
        """ Invert the 5th bit """
        if val == START_FLAG or val == ESCAPE_FLAG:
            mask = 1 << 5
            val ^= mask
        return val        

    def check_flag_conflict(self, val):
        """ Check if val conflicts with one of the flags """
        return val == START_FLAG or val == ESCAPE_FLAG

    def serialize(self):
        """ Convert the object to a byte string to send it over the serial port and add the checksum """
        data = ""
        # Start
        data += chr(START_FLAG)
        
        # Sequence number
        if self.check_flag_conflict(self.seq_number):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(self.seq_number))    
        else:
            data += chr(self.seq_number)
        
        # Command
        if self.check_flag_conflict(self.command):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(self.command))    
        else:
            data += chr(self.command)
        
        # Payload length
        if self.check_flag_conflict(self.payload_length):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(self.payload_length))    
        else:
            data += chr(self.payload_length)

        # Payload
        for i in xrange(payload_length):
            if self.check_flag_conflict(self.payload[i]):
                data += chr(ESCAPE_FLAG)
                data += chr(self.invert_bit_5(self.payload[i]))    
            else:
                data += chr(self.payload[i])

        # Checksum
        checksum_msb, checksum_lsb = self.checksum()

        if self.check_flag_conflict(checksum_msb):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(checksum_msb))    
        else:
            data += chr(checksum_msb)
        if self.check_flag_conflict(checksum_lsb):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(checksum_lsb))    
        else:
            data += chr(checksum_lsb)

        # End
        data += chr(START_FLAG)

        return data


    def checksum(self):
        """ Compute the 16bit Fletcher's checksum of the data """
        lsb = 0
        msb = 0
        lsb += self.seq_number
        msb += lsb
        lsb += self.command
        msb += lsb
        lsb += self.payload_length
        msb += lsb
        for i in xrange(self.payload_length):
            lsb += self.payload[i]
            msb += lsb
            if i % 32 == 0:
                # Do a reduction each 16 bytes
                lsb = (lsb & 0xFF) + (lsb >> 8)
                msb = (msb & 0xFF) + (msb >> 8)
        # Last double reduction to add the carry
        lsb = (lsb & 0xFF) + (lsb >> 8)
        lsb = (lsb & 0xFF) + (lsb >> 8)
        msb = (msb & 0xFF) + (msb >> 8)
        msb = (msb & 0xFF) + (msb >> 8)
        return msb, lsb


class ACKFrame(PacketFrame):
    """ Class to implement the ACK frame functionality """
    def __init__(self, seq_number, command):
        self.seq_number = seq_number
        self.command = ACK_COMMAND

    def serialize(self):
        """ Convert the object to a byte string to send it over the serial port and add the checksum """
        data = ""
        # Start
        data += chr(START_FLAG)
        
        # Sequence number
        if self.check_flag_conflict(self.seq_number):
            data += chr(ESCAPE_FLAG)
            data += chr(self.invert_bit_5(self.seq_number))    
        else:
            data += chr(self.seq_number)
        
        # Command
        data += chr(self.command)

        # End
        data += chr(START_FLAG)
 
        return data

class ArdPiComm(Thread):
    """Class to handle the serial object and implement the communication protocol"""
    
    def __init__(self, message_callback, port='/dev/ttyACM0', baudrate=9600):
        self.sent_seq = 0
        self.recv_seq = 0
        self.last_ack = None
        self.callback = message_callback

        print 'Connecting to serial port...'
        try:
            self.ser = serial.Serial(port=port, baudrate=baudrate)
        except serial.serialutil.SerialException:
            print '\nSerial device not connected. Program aborted.\n'
            sys.exit(1)
        except ValueError as ve:
            print '\nSerial parameters not valid.\n'
            raise ve
        else:
            print 'Done!\n'

        Thread.__init__(self)
        self.daemon = True
        self.running = True


    def run(self):
        # TODO
        # Receive all incoming bytes and pack them in frames
        # If the frame is an ack message, put it in the ACK buffer
        # If it is another message, process it with the message callback
        pass    

    def stop(self):
        # Stop the thread and close the serial port
        self.running = False

        if self.ser.isOpen():
            print '\nClosing serial port...'
            self.ser.close()
            print 'Serial port closed.'
        else:
            print 'Serial port is already closed.'

    def send(self, command, argument=0):

        retries = 0
        command = command & 0xFF
        argument = argument & 0xFF

        print 'Sending command {c}, with argument {a}'.format(c=command, a=argument)

        self.ser.write(chr(command))
        self.ser.write(chr(argument))
        
        while self.check_ack() == 0 and retries < MAX_RETRIES:
            self.ser.write(chr(command))
            self.ser.write(chr(argument))
            retries += 1
            sleep(0.1) # 100ms between each retry


        if retries == MAX_RETRIES:
            # No ACK after MAX_RETRIES
            print 'Could not send command {c}, with argument {a}'.format(c=command, a=argument)
            return False
        else:
            return True

    def pack_frame(self, command, payload):
        # TODO
        # Pack all bytes in the frame. Insert escape bytes when necessary and add checksum
        pass

    def check_ack(self):
        print 'Receiving ACK...'
        ack = 0
        if self.ser.inWaiting() > 0:
            ack = ord(self.ser.read(1))
        print 'ACK received: {}'.format(ack)
        return ack

if __name__ == '__main__':
    # Test
    # TODO: Reimplement the test with the new protocol version
    """
    comm = ArdPiComm()
    while True:
        command = raw_input()
        if command == 's':
            print 'Sending stop command'
            comm.send(0x00)
        elif command == 'f':
            print 'Sending forward command'
            comm.send(0x03, 50)
        elif command == 'q':
            break
    comm.stop()
    """

