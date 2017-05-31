""" Test the serialize functions from the parser module """
from parser import *
from driver_comm import *
from time import sleep


def test_callback(command, payload):
    print "\tCommand received: {}".format(command)
    print "\tPayload: {}".format(payload)


if __name__ == '__main__':
    
    comm = ArdPiComm(test_callback, port="/dev/ttyACM0")
    comm.start()

    sleep(3)

    data = 'A'
    print "Sending cmd 10, char: '{}'...".format(data)
    comm.send(10, [serialize_char(data)])
    sleep(1)
    
    data = 'test'
    print "Sending cmd 2, string: '{}'...".format(data)
    comm.send(2, serialize_str(data))
    sleep(1)

    data = -100
    print "Sending cmd 3, int8: {}...".format(data)
    comm.send(3, serialize_int8(data))
    sleep(1)

    data = -1000
    print "Sending cmd 4, int16: {}...".format(data)
    comm.send(4, serialize_int16(data))
    sleep(1)

    data = 1000
    print "Sending cmd 5, uint16: {}...".format(data)
    comm.send(5, serialize_uint16(data))
    sleep(1)

    data = -100000
    print "Sending cmd 6, int32: {}...".format(data)
    comm.send(6, serialize_int32(data))
    sleep(1)

    data = 100000
    print "Sending cmd 7, uint32: {}...".format(data)
    comm.send(7, serialize_uint32(data))
    sleep(1)

    data = 3.14159265
    print "Sending cmd 8, float: {}...".format(data)
    comm.send(8, serialize_float(data))
    sleep(1)

    print "Waiting 5 seconds until all responses are received..."
    sleep(5)

    comm.stop()

