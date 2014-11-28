import unittest
import sys, os, inspect
current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from Comunication import msp430
from Comunication import util

class BasicTestComunication(unittest.TestCase):

    def setUp(self):
        #Find which method will run and shows
        func = str(self.id).split('=')[-1][:-2]
        func = func.split('test_')[-1]
        func = func.replace('_',' ')
        out = '\rTest: ' + func + ' '
        out = out.ljust(65,'-')
        sys.stderr.write(out)


    def tearDown(self):
        sys.stderr.write('Done\n')


class testUtil(BasicTestComunication):
    """docstring for testMock"""
   
    def test_Find_Port(self):
        ports = util.available_ports()
        self.assertGreaterEqual(len(ports),0)

    def test_Random_Message(self):
        self.assertEquals(len(util.randomstring(5)),5)
        self.assertEquals(len(util.randomstring(15)),15)
        self.assertEquals(len(util.randomstring(25)),25)

    def test_Root_message(self):
        self.assertEquals(len(util.ROOT_MESSAGE),317)
        self.assertIn("You need Super Cow Powers here.",util.ROOT_MESSAGE)
        print util.ROOT_MESSAGE

class ClassName(object):
    """docstring for ClassName"""
    def __init__(self, arg):
        super(ClassName, self).__init__()
        self.arg = arg
        

if __name__ == '__main__':
            unittest.main()

