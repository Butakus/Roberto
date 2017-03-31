""" Module to parse the bytes read with driver_comm into common types """

import struct


""" Parsers: byte list to common types: """

def parse_char(data):
    """ Convert the given byte into a char """
    return chr(data)


def parse_str(data):
    """ Convert the given byte list into a string (char array) """
    return ''.join(chr(x) for x in data)


def parse_int16(data, big_endian=False):
    """ Convert 2 bytes into a 16 bit int """
    str_data = parse_str(data)
    byte_format = '>h' if big_endian else '<h'
    return struct.unpack(byte_format, str_data)[0]


def parse_uint16(data, big_endian=False):
    """ Convert 2 bytes into an unsigned 16 bit int """
    val = 0
    if big_endian:
        val = data[1] | (data[0] << 8)
    else:
        val = data[0] | (data[1] << 8)
    return val


def parse_int32(data, big_endian=False):
    """ Convert 4 bytes into a 32 bit int """
    str_data = parse_str(data)
    byte_format = '>i' if big_endian else '<i'
    return struct.unpack(byte_format, str_data)[0]


def parse_uint32(data, big_endian=False):
    """ Convert 4 bytes into an unsigned 32 bit int """
    val = 0
    if big_endian:
        val = data[3] | (data[2] << 8) | (data[1] << 16) | (data[0] << 24)
    else:
        val = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24)
    return val


def parse_int64(data, big_endian=False):
    # TODO: Convert 8 bytes into a 64 bit int (long long)
    str_data = parse_str(data)
    byte_format = '>q' if big_endian else '<q'
    return struct.unpack(byte_format, str_data)[0]


def parse_uint64(data, big_endian=False):
    """ Convert 8 bytes into an unsigned 64 bit int (unsigned long long) """
    val = 0
    if big_endian:
        val = data[7] | (data[6] << 8) | (data[5] << 16) | (data[4] << 24) | (data[3] << 32) | (data[2] << 40) | (data[1] << 48) | (data[0] << 56)
    else:
        val = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24) | (data[4] << 32) | (data[5] << 40) | (data[6] << 48) | (data[7] << 56)
    return val


def parse_float32(data, big_endian=False):
    """ Convert 4 bytes into a 32 bit float """
    str_data = parse_str(data)
    byte_format = '>f' if big_endian else '<f'
    return struct.unpack(byte_format, str_data)[0]
    

def parse_float64(data, big_endian=False):
    """ Convert 8 bytes into a 64 bit float (double) """
    str_data = parse_str(data)
    byte_format = '>d' if big_endian else '<d'
    return struct.unpack(byte_format, str_data)[0]




""" Serializers: common types to byte list: """

def serialize_char(data):
    """ Convert the given char into a byte """
    return ord(data)


def serialize_str(data):
    """ Convert the given string into a byte list """
    return [ord(x) for x in data]


def serialize_int16(data, big_endian=False):
    # TODO: Convert a 16 bit int into 2 bytes
    pass


def serialize_uint16(data, big_endian=False):
    # TODO: Convert an unsigned 16 bit int into 2 bytes
    pass


def serialize_int32(data, big_endian=False):
    # TODO: Convert a 32 bit int into 4 bytes
    pass


def serialize_uint32(data, big_endian=False):
    # TODO: Convert an unsigned 32 bit int into 4 bytes
    pass


def serialize_int64(data, big_endian=False):
    # TODO: Convert a 32 bit int (long) into 8 bytes
    pass


def serialize_uint64(data, big_endian=False):
    # TODO: Convert an unsigned 32 bit int (unsigned long) into 8 bytes
    pass


def serialize_float32(data, big_endian=False):
    # TODO: a 32 bit float into 4 bytes
    pass


def serialize_float64(data, big_endian=False):
    # TODO: a 64 bit float (double) into 8 bytes
    pass