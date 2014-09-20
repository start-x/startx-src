# coding: utf-8

"""
    MSP module

    A Interface with the hardware
"""
try:
    # Terminal Class
    from serial.tools.miniterm import Miniterm
    from serial.serialutil import SerialException
except Exception as error:
    try:
        import serial
    except ImportError as error:
        print 'Install Pyserial'
        raise error
    if float(serial.VERSION) < 2.6:
        print 'Upgrade Pyserial'
    raise error

import device as sensor
from mock import MagicMock
import util


class MSP(Miniterm):

    """docstring for MSP

    Done with the ideia that all the interface happens
    by UART

    """
    port = 0
    alive = False
    modules={}

    def __init__(self, tty, baud=9600):
        if tty is not None:
            try:
                super(MSP, self).__init__(tty, baud, 'N',
                  False, False)
            except SerialException:
                print util.ROOT_MESSAGE
                exit(-1)
            self.serial.setTimeout(1)
        else:
            """FIXME: remove the code bellow in 
            production environment"""
            self.serial = MagicMock()
            self.serial.readline = util.randomstring
            # raise Exception  
        self.port = tty
        self.adc = sensor.Passive(self.serial)
        self.pwm = sensor.Active(self.serial)
        self.modules['active'] = [self.pwm]
        self.modules['passive'] = [self.adc]

        self.enable()

    def __getitem__(self,key):
        return getattr(self,key).read_data('t')

    def __setitem__(self,key,item):
        getattr(self,key).write_data('r',str(item))

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
    PORTS_AVAILABLE = util.available_ports()
    try:
        for i in PORTS_AVAILABLE:
            print '>>> %s' % i
        print '---'
    except TypeError, error:
        print "None device connected"
        exit()

    # choose a port
    if len(PORTS_AVAILABLE) == 1:
        msp430 = MSP(PORTS_AVAILABLE[0], 4800)

    # make 10 reads from adc
    print '\nRaw data \n----------'
    for x in xrange(1, 11):
        print x, msp430.adc.read_data('t')

    # define a new reading method
    def thridfirst(item):
        """ Rewritng method """
        data = msp430.serial.readline()
        return data.split(',')[:3]

    print msp430['adc']
    msp430.adc.read_data = thridfirst

    # make 10 reads from adc using the new method
    print '\nProcessed data \n----------'
    for x in xrange(1, 11):
        print x, msp430.adc.flush()

    # example of using a active sensor
    print '\nActive sensor\'s data \n----------'
    for x in xrange(1, 11):
        print x, msp430.pwm.write_data('r', 't')

    # new microcontroller interface
    print msp430['adc']
    msp430['pwm'] = 25
    print msp430['pwm']

    # closes msp430 dependecies
    msp430.desable()
