# This is a template for writing test cases and performance checks
from serial import Serial
from timeit import default_timer as timer
from time import sleep

serialPortName = '/dev/ttyACM0'

ardu = Serial(serialPortName, 115200, timeout=5)
print('Port: ' + ardu.name + ' (' + ('opened' if ardu.is_open else 'closed') + ')')

try:
    while True:
        start = timer()
        ardu.write(b"haha ruchansko\n")
        print(ardu.readline())
        end = timer()

        print(str((end - start) * 1000) + "ms")
        sleep(0.5)
        
except KeyboardInterrupt:
    ardu.close()