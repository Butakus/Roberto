""" Module to parse the bytes read with driver_comm into common types """

import struct


""" Parsers: byte list to common types: """

def parse_char(data):
    """ Convert the given byte into a char """
    return chr(data)


def parse_str(data):
    """ Convert the given byte list into a string (char array) """
    return ''.join(chr(x) for x in data)


def parse_int8(data, big_endian=False):
    """ Convert 1 byte into a 8 bit signed int """
    data_str = parse_str(data)
    byte_format = '>b' if big_endian else '<b'
    return struct.unpack(byte_format, data_str)[0]


def parse_int16(data, big_endian=False):
    """ Convert 2 bytes into a 16 bit int """
    data_str = parse_str(data)
    byte_format = '>h' if big_endian else '<h'
    return struct.unpack(byte_format, data_str)[0]


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
    data_str = parse_str(data)
    byte_format = '>i' if big_endian else '<i'
    return struct.unpack(byte_format, data_str)[0]


def parse_uint32(data, big_endian=False):
    """ Convert 4 bytes into an unsigned 32 bit int """
    val = 0
    if big_endian:
        val = data[3] | (data[2] << 8) | (data[1] << 16) | (data[0] << 24)
    else:
        val = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24)
    return val


def parse_float(data, big_endian=False):
    """ Convert 4 bytes into a 32 bit float """
    data_str = parse_str(data)
    byte_format = '>f' if big_endian else '<f'
    return struct.unpack(byte_format, data_str)[0]



""" Serializers: common types to byte list: """

def serialize_char(data):
    """ Convert the given char into a byte """
    return ord(data)


def serialize_str(data):
    """ Convert the given string into a byte list """
    return [ord(x) for x in data]


def parse_int8(data, big_endian=False):
    """ Convert a 8 bit signed int into a byte """
    byte_format = '>b' if big_endian else '<b'
    data_str = struct.pack(byte_format, data)
    return serialize_str(data_str)


def serialize_int16(data, big_endian=False):
    """ Convert a 16 bit int into 2 bytes """
    byte_format = '>h' if big_endian else '<h'
    data_str = struct.pack(byte_format, data)
    return serialize_str(data_str)


def serialize_uint16(data, big_endian=False):
    """ Convert an unsigned 16 bit int into 2 bytes """
    data_bytes = []
    if big_endian:
        data_bytes[1] = data & 0xFF
        data_bytes[0] = (data >> 8) & 0xFF
    else:
        data_bytes[0] = data & 0xFF
        data_bytes[1] = (data >> 8) & 0xFF
    return data_bytes


def serialize_int32(data, big_endian=False):
    """ Convert a 32 bit int into 4 bytes """
    byte_format = '>i' if big_endian else '<i'
    data_str = struct.pack(byte_format, data)
    return serialize_str(data_str)


def serialize_uint32(data, big_endian=False):
    """ Convert an unsigned 32 bit int into 4 bytes """
    data_bytes = []
    if big_endian:
        data_bytes[3] = data & 0xFF
        data_bytes[2] = (data >> 8) & 0xFF
        data_bytes[1] = (data >> 16) & 0xFF
        data_bytes[0] = (data >> 24) & 0xFF
    else:
        data_bytes[0] = data & 0xFF
        data_bytes[1] = (data >> 8) & 0xFF
        data_bytes[2] = (data >> 16) & 0xFF
        data_bytes[3] = (data >> 24) & 0xFF
    return data_bytes


def serialize_float(data, big_endian=False):
    """ Convert a 32 bit float into 4 bytes """
    byte_format = '>f' if big_endian else '<f'
    data_str = struct.pack(byte_format, data)
    return serialize_str(data_str)
