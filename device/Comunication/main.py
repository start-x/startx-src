#!/usr/bin/env python
# coding: utf-8

"""
    Package to the interface between the Bike-X and the
    MSP430.
"""

import util
import sys
from msp430 import MSP
import device as sensor
from signal import signal, SIGINT, SIGALRM, SIGABRT, SIGQUIT
from startx import SIG1, SIG2, SIG3, ACTIVE_FILE, PASSIVE_FILE
from time import sleep
from os import getpid, kill
from mock import MagicMock
from random import random


# MSP430 object
msp430 = object()


def safe_quit(signum, frame):
    """ Care for a safe quit """
    print "Exiting"
    msp430.disable()
    exit()


def write_file(signum, frame):
    """Requisited new data from sensor"""
    print "Requisited new data from sensor"
    f = open(PASSIVE_FILE, 'w')
    f.write(msp430['passives'])
    print msp430['passives']
    f.close()
    try:
        # Without a real pid, could be dangerous
        # kill(pid_bikex,SIG2)
        pass
    except Exception, e:
        print 'Father not available'


def read_file(signum, frame):
    """ read file and send to mcu """
    print "BikeX send new data"
    f = open(ACTIVE_FILE, 'a+r')
    data = f.readline()
    print data,
    msp430['curb'] = data
    f.close()


def main():
    pid_bikex = sys.argv[1:2]
    print "Father: %s" % pid_bikex
    print "Mine: %d " % getpid()
    print """Signals:
    %i - BikeX -> MSP430
    %i - MSP430 -> BikeX
    %i - close aplication
    """ % (SIG3, SIG1, 2)

    msp430.curb = sensor.Break(msp430.serial, 0)
    msp430.passives = sensor.Passives(msp430.serial, 0)

    signal(SIG1, write_file)
    signal(SIG3, read_file)
    signal(SIGINT, safe_quit)
    signal(SIGQUIT, safe_quit)
    signal(SIGABRT, safe_quit)
    while True:
        sleep(0.01)
        write_file(0, 0)

if __name__ == '__main__':
    # list available ports
    PORTS_AVAILABLE = util.available_ports()
    try:
        print 'Available ports:'
        for i in PORTS_AVAILABLE:
            print '>>> %s' % i
        print '---'
        # choose a port
        if len(PORTS_AVAILABLE) > 0:
            msp430 = MSP(PORTS_AVAILABLE[0])
    except TypeError, error:
        print "None device connected - test mode"
        msp430 = MagicMock()
        msp430.__getitem__ = MagicMock(return_value='120.2 50')

    print 'Ready'
    main()
