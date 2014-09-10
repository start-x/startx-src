# -*- coding: utf-8 -*-

"""
    Simple Unit Test to MSP class
"""

import unittest
import sys
sys.path.append('../')
from msp430 import MSP, available_ports
from glob import glob


class TestMSP(unittest.TestCase):
    """docstring for TestMSP"""

    def shortDescription(self):
        return "Test Microcontroler class"

    def setUp(self):
        """ Sting up """
        func = str(self.id).split('=')[-1][:-2]
        func = func.split('test_')[-1]
        func = func.replace('_', ' ')
        out = '\rTest of ' + func + ' '
        out = out.ljust(65, '-')
        sys.stderr.write(out)
        self.shortDescription()

        port = available_ports()
        if port:
            port = port[0]
        self.msp430 = MSP(port)

    def tearDown(self):
        """ Releasing test """
        sys.stderr.write('Done\n')

    def test_message(self):
        """ A test """
        self.assertIsNotNone(self.msp430.adc.read())

if __name__ == "__main__":
    unittest.main()
