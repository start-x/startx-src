#!/usr/bin/env python
# coding: utf-8

"""
    Sensor module

    Define the basic classes and rotines to a sensor
"""


class Sensor(object):

    """docstring for Sensor"""

    type = ''
    name = 'base'
    data = '-----'
    live = False

    def __init__(self):
        super(Sensor, self).__init__()

    def enable(self):
        """ Enable the sensor """

        self.live = True

    def desable(self):
        """ Desable the sensor """

        self.live = False


class Passive(Sensor):

    """docstring for Passive"""

    def __init__(self):
        super(Passive, self).__init__()

    def read(self):
        """ Return actual data from sensor """

        return self.data


class Active(Sensor):

    """docstring for Active"""

    def __init__(self):
        super(Active, self).__init__()

    def _send_data(self, data):
        """ Send some data to sensor """

        pass

    def read(self, command='r'):
        """ Return actual data from sensor """

        self._send_data(command)
        return self.data

if __name__ == '__main__':
    k = Active()
    print k.read()
