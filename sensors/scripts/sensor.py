#!/usr/bin/env python
# coding: utf-8


class Sensor(object):

    """docstring for Sensor"""

    type = ''
    name = 'base'
    data = '-----'
    live = False

    def __init__(self):
        super(Sensor, self).__init__()

    def enable(self):
        self.live = True

    def desable(self):
        self.live = False


class Passive(Sensor):

    """docstring for Passive"""

    def __init__(self):
        super(Passive, self).__init__()

    def read(self):
        return self.data


class Active(Sensor):

    """docstring for Active"""

    def __init__(self):
        super(Active, self).__init__()

    def _sendData(self, data):
        pass

    def read(self, command='r'):
        self._sendData(command)
        return self.data

if __name__ == '__main__':
    k = Active()
    print k.read()
