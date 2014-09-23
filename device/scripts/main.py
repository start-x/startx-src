#!/usr/bin/env python
# coding: utf-8

import msp430
import util
import sys
import signal
from startx import SIG1,SIG2,SIG3,SIG4,FILE
from time import sleep
from os import getpid,kill
from mock import MagicMock

pid_bikex =0
msp430 = MagicMock()

msp430.read_data =  MagicMock(return_value='jhasdfaskjfkjb')

def write_file(signum, frame):
    """ was requisited new data from sensor"""
    f = open(FILE,'w')
    f.write(msp430.read_data()) 
    # f.write(msp430['direcao'])
    f.close()
    #kill(pid_bikex,SIG2)
    pass

def read_file(signum, frame):
    """ read file and sendo to mcu """
    f = open(FILE,'r')
    data = f.readline() 
    print data
    # msp430['freio'] = data
    f.close()
    pass

def main():
    pid_bikex = sys.argv[1]
    print getpid()
    print SIG1,SIG2,SIG3,SIG4
    #msp430.freio = sensor.Freio(msp430.serial,0)
    #msp430.direcao = sensor.Direction(msp430.serial,0)


    signal.signal(SIG1, write_file)
    signal.signal(SIG3, read_file)
    while True:
        sleep(0.01)

if __name__ == '__main__':
    # list available ports
    # print 'Available ports:'
    # PORTS_AVAILABLE = util.available_ports()
    # try:
    #     for i in PORTS_AVAILABLE:
    #         print '>>> %s' % i
    #     print '---'
    # except TypeError, error:
    #     print "None device connected"
    #     #exit()

    # # choose a port
    # if len(PORTS_AVAILABLE) == 1:
    #     msp430 = MSP(PORTS_AVAILABLE[0])
    print 'Ready'
    main()
