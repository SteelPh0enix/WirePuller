#!/bin/python3
# This is a template for writing test cases and performance checks
from serial import Serial
from timeit import default_timer as timer
from time import sleep

serial_port_name = '/dev/ttyACM0'
serial_timeout = 5

responses_time_sum = 0
responses_count = 0

ardu = Serial(serial_port_name, 115200, timeout=serial_timeout)
print('Port: ' + ardu.name + ' (' + ('opened' if ardu.is_open else 'closed') + ')')

try:
    while True:
        start = timer()
        ardu.write(b"enter the data here\n")
        print(ardu.readline())
        end = timer()
        
        response_time = (end - start) * 1000
        if (response_time >= serial_timeout * 1000):
            print("Timeout reached.")
            continue

        responses_time_sum += response_time
        responses_count += 1

        print("Response time: " + str(response_time) + "ms")
        sleep(0.5)
        
except KeyboardInterrupt:
    ardu.close()
    avg_response_time = responses_time_sum / responses_count
    avg_response_frequency = 1 / (avg_response_time / 1000)
    print("\n\nResponses count: " + str(responses_count))
    print("Average response time: " + str(avg_response_time) + "ms")
    print("Average response frequency: " + str(avg_response_frequency) + "Hz")