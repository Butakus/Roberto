""" Test the serialize functions from the parser module """
from parser import *
from driver_comm import *
from time import sleep


def test_callback(command, payload):
    print "------------------------------------------------"
    print "Command received: {}".format(command)
    print "Payload: {}".format(payload)
    print "###"

    if command == 10:
        data = parse_char(payload)
        print "Received char: '{}'...".format(data)
        print "Match 'A': {}".format(data == 'A')

    elif command == 2:
        data = parse_str(payload)
        print "Received string: '{}'...".format(data)
        print "Match 'test': {}".format(data == "test")

    elif command == 3:
        data = parse_int8(payload)
        print "Received int8: '{}'...".format(data)
        print "Match -100: {}".format(data == -100)

    elif command == 4:
        data = parse_int16(payload)
        print "Received int16: '{}'...".format(data)
        print "Match -1000: {}".format(data == -1000)

    elif command == 5:
        data = parse_uint16(payload)
        print "Received uint16: '{}'...".format(data)
        print "Match 1000: {}".format(data == 1000)

    elif command == 6:
        data = parse_int32(payload)
        print "Received int32: '{}'...".format(data)
        print "Match -100000: {}".format(data == -100000)

    elif command == 7:
        data = parse_uint32(payload)
        print "Received uint32: '{}'...".format(data)
        print "Match 100000: {}".format(data == 100000)

    elif command == 8:
        data = parse_float(payload)
        print "Received float: '{}'...".format(data)
        print "Match 3.14159265: {}".format(data == 3.14159265)
        print "Float error: {}".format(abs(data - 3.14159265))


if __name__ == '__main__':

    comm = ArdPiComm(test_callback, port="/dev/ttyACM0")
    comm.start()

    print "Press Enter to exit..."
    sleep(2)
    raw_input()
    comm.stop()
