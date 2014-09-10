#!/usr/bin/env python
# coding: utf-8

"""
    MSP module

    A Interface with the hardware
"""
try:
        # Terminal Class
    from serial.tools.miniterm import Miniterm
    from serial.tools.miniterm import CONVERT_CRLF
    # Terminal macros
    from serial.tools.list_ports import comports
except Exception as error:
    import serial
    if float(serial.VERSION) < 2.6:
        print 'Upgrade Pyserial'
    raise error
try:
    from glob import glob
except Exception as error:
    print 'Install glob'
    raise error

import sensor
from mock import MagicMock
import string, random

def randomstring():
    """ rewriting method """
    chars = string.ascii_uppercase + string.digits
    return ''.join(random.choice(chars) for _ in range(20))

def available_ports():
    # looking for available ports
    PORTS_AVAILABLE = glob('/dev/ttyUSB*') + glob('/dev/ttyACM*')
    try:
        for port, desc, hwid in sorted(comports()):
            if port not in port:
                PORTS_AVAILABLE.append(port)
    except Exception as error:
        raise error
    if len(PORTS_AVAILABLE) == 0:
        PORTS_AVAILABLE = None

    return PORTS_AVAILABLE

class MSP(Miniterm):

    """docstring for MSP

    Done with the ideia that all the interface happens
    by UART

    """
    port = 0
    alive = False

    def __init__(self, tty, baud=9600):
        if tty != None:
            super(MSP, self).__init__(tty, baud, 'N',
                False, False, False, CONVERT_CRLF, 0)
        else:
            self.serial = MagicMock()
            self.serial.readline = randomstring
        self.port = tty
        self.adc = sensor.Passive(self.serial)
        self.pwm = sensor.Active(self.serial)
        self.enable()

    def enable(self):
        """ Method to enable the micro """
        self.alive = True

    def desable(self):
        """ Method to desable the micro """
        self.alive = False
        self.serial.close()

if __name__ == '__main__':

    # list available ports
    print 'Available ports:'
    PORTS_AVAILABLE = available_ports()
    for i in PORTS_AVAILABLE:
        print '>>> %s' % i
    print '---'

    # choose a port
    if len(PORTS_AVAILABLE) == 1:
        msp430 = MSP(PORTS_AVAILABLE[0], 4800)

    # make 10 reads from adc
    print '\nRaw data \n----------'
    for x in xrange(1, 11):
        print x, msp430.adc.read()

    # define a new reading method
    def thridfirst():
        """ Rewritng method """
        data = msp430.serial.readline()
        return data.split(',')[:3]

    msp430.adc.read = thridfirst

    # make 10 reads from adc using the new method
    print '\nProcessed data \n----------'
    for x in xrange(1, 11):
        print x, msp430.adc.read()

    # example of using a active sensor
    print '\nActive sensor\'s data \n----------'
    for x in xrange(1, 11):
        print x, msp430.pwm.read('r')

    # closes msp430 dependecies
    msp430.desable()
