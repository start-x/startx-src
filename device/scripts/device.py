#!/usr/bin/env python
# coding: utf-8

"""
    Device module

    Define the basic classes and rotines to a sensor
"""


class Device(object):

    """docstring for Device"""

    type = ''
    name = 'base'
    data = '-----'
    live = False

    def __init__(self, terminal):
        super(Device, self).__init__()
        self.serial = terminal
        self.enable()
        self.flush()

    def enable(self):
        """ Enable the sensor """

        self.live = True

    def desable(self):
        """ Desable the sensor """

        self.live = False

    def flush(self):
        """ Read data """

        return self.serial.readline()


class Active(Device):

    """docstring for Passive"""

    def __init__(self, terminal):
        super(Active, self).__init__(terminal)
        self.data = self.serial.readline()
        self.data = self.data.split('\n')[0]

    def write_data(self, command, data):
        """ Return actual data from device """
        self.serial.write(command)
        self.serial.write(data)


class Passive(Device):

    """docstring for Active"""

    def __init__(self, terminal):
        super(Passive, self).__init__(terminal)
        self.data = self.serial.readline()
        self.data = self.data.split('\n')[0]

    def read_data(self, command):
        """ Send some data to device """
        self.serial.write(command)
        self.data = self.serial.readline()
        self.data = self.data.split('\n')[0]
        return self.data

if __name__ == '__main__':
    import serial
    from glob import glob
    PORTS_AVAILABLE = glob('/dev/ttyUSB*') + glob('/dev/ttyACM*')
    print PORTS_AVAILABLE
    ser = serial.Serial(PORTS_AVAILABLE[0], 4800)
    act = Active(ser)
    print act.write_data('r', 't')
    passive = Passive(ser)
    print passive.read_data('g')
    ser.close()
