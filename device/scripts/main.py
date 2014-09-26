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
from startx import SIG1,SIG2,SIG3,ACTIVE_FILE, PASSIVE_FILE
from time import sleep
from os import getpid,kill
from mock import MagicMock

# Bike-X PID
pid_bikex =0
# MSP430 object
msp430 = object()

def safe_quit(signum, frame):
    """ Care for a safe quit """
    print "Exiting"
    msp430.desable()
    exit()

def write_file(signum, frame):
    """ was requisited new data from sensor"""
    f = open(PASSIVE_FILE,'w')
    #f.write(msp430.read_data()) 
    f.write(msp430['direcao'])
    f.close()
    #kill(pid_bikex,SIG2)
    pass

def read_file(signum, frame):
    """ read file and sendo to mcu """
    f = open(ACTIVE_FILE,'a+r')
    data = f.readline() 
    print data
    msp430['freio'] = data
    f.close()
    pass

def main():
    pid_bikex = sys.argv[1:2]
    print "Father: %s" % pid_bikex
    print "Mine: %d " % getpid()
    print SIG1,SIG2,SIG3
    msp430.freio = sensor.Freio(msp430.serial,0)
    msp430.direcao = sensor.Direction(msp430.serial,0)

    signal(SIG1, write_file)
    signal(SIG3, read_file)
    signal(SIGINT, safe_quit)
    signal(SIGQUIT, safe_quit)
    signal(SIGABRT, safe_quit)
    while True:
        sleep(0.01)

if __name__ == '__main__':
    # list available ports
    print 'Available ports:'
    PORTS_AVAILABLE = util.available_ports()
    try:
        for i in PORTS_AVAILABLE:
            print '>>> %s' % i
        print '---'
        # choose a port
        if len(PORTS_AVAILABLE) == 1:
            msp430 = MSP(PORTS_AVAILABLE[0])
    except TypeError, error:
        print "None device connected"
        msp430 = MagicMock()

        msp430.read_data =  MagicMock(return_value='jhasdfaskjfkjb'
        #exit()
)

    print 'Ready'
    main()
