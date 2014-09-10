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


class MSP(Miniterm):

    """docstring for MSP

    Dowith the ideia that all the interface happens
    by UART

    """
    port = 0
    alive = False

    def __init__(self, tty,baud = 9600):
        super(MSP, self).__init__(tty, baud, 'N',False,False,False,CONVERT_CRLF,0)
        self.port = tty
        self.adc = sensor.Passive(self.serial)

    def enable(self):
        """ Method to enable the micro """
        self.alive = True

    def disable(self):
        """ Method to desable the micro """
        self.alive = False
        self.serial.close()

if __name__ == '__main__':
    PORTS_AVAILABLE = glob('/dev/ttyUSB*') + glob('/dev/ttyACM*')
    try:
        for port, desc, hwid in sorted(comports()):
            if port not in port:
                PORTS_AVAILABLE.append(port)
    except Exception as error:
        raise error
    print 'Available ports:'
    for i in PORTS_AVAILABLE:
        print '>>> %s' % i

    if len(PORTS_AVAILABLE) == 1:
        msp430 = MSP(PORTS_AVAILABLE[0],4800)
        for x in xrange(1,10):
            print msp430.adc.read()


