#!/bin/python3
# This is a `data_request` request type test
from serial import Serial
from timeit import default_timer as timer
from time import sleep
from enum import IntFlag

class RequestData(IntFlag):
    MOTOR = 1
    ENDSTOP = 2
    ENCODER = 4

serial_port_name = '/dev/ttyACM0'
serial_timeout = 5
delay_time_ms = 300

responses_time_sum = 0
responses_count = 0

ardu = Serial(serial_port_name, 115200, timeout=serial_timeout)
print('Port: ' + ardu.name + ' (' + ('opened' if ardu.is_open else 'closed') + ')')

request_flag = RequestData.ENDSTOP

def write_json(json):
    start = timer()
    ardu.write(b"enter the data here\n")
    print(ardu.readline())
    end = timer()
        
    response_time = (end - start) * 1000
    timeout = False

    if response_time >= serial_timeout * 1000:
        print("Timeout reached.")
        timeout = True
    else:    
        print("Response time: " + str(response_time) + "ms")

    return timeout, response_time

try:
    while True:
        timeout, response_time = write_json("{}")

        if not timeout:
            responses_count += 1
            responses_time_sum += response_time
        
        sleep(delay_time_ms / 1000)
        
except KeyboardInterrupt:
    ardu.close()
    avg_response_time = responses_time_sum / responses_count
    avg_response_frequency = 1 / (avg_response_time / 1000)
    print("\n\nResponses count: " + str(responses_count))
    print("Average response time: " + str(avg_response_time) + "ms")
    print("Average response frequency: " + str(avg_response_frequency) + "Hz")