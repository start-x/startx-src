# coding: utf-8

import string
import random
from serial.tools.list_ports import comports
try: 
    from glob import glob 
except Exception as error: 
    print 'Install glob'
    raise error


ROOT_MESSAGE = """    
    .-------------------------------.    
   ( You need Super Cow Powers here. )    
    '-------------------------------'    
           \   ^__^            
            \  (oo)\_______          
               (__)\       )\/\\     
                   ||----w |    
                   ||     ||    
         
  """    
                         

def randomstring():             
    """ rewriting method """                          
    chars = string.ascii_uppercase + string.digits
    return ''.join(random.choice(chars) for _ in range(20))

                          
def available_ports():               
    # looking for available ports
    PORTS_AVAILABLE = glob('/dev/ttyUSB*') + glob('/dev/ttyACM*') + glob('/dev/ttyMOCK*')
    try:                                               
        for port, desc, hwid in sorted(comports()):    
            if port not in port:                
                PORTS_AVAILABLE.append(port)    
    except Exception as error:    
        raise error                  
    if len(PORTS_AVAILABLE) == 0:    
        PORTS_AVAILABLE = None

    return PORTS_AVAILABLE
