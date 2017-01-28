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

class PacketFrame(object):
    """ Class to implement the packet frame functionality """
    # TODO
    def __init__(self, seq_number, command, payload):
        self.seq_number = seq_number
        self.command = command
        self.payload_length = len(payload)
        self.payload = payload

    def serialize(self):
        # Convert the object to a byte array to send it over the serial port and add the checksum
        # TODO
        pass

    def __checksum(self):
        # Compute the checksum of the data
        pass

class PacketFrame(object):
    """ Class to implement the ACK frame functionality """
    # TODO
    def __init__(self, seq_number, command):
        self.seq_number = seq_number
        self.command = ACK_COMMAND
        self.payload_length = 0

    def serialize(self):
        # Convert the object to a byte array to send it over the serial port and add the checksum
        # TODO
        pass

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

