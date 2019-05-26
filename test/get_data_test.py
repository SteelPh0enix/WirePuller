#!/bin/python3
# This is a `data_request` request type test
from serial import Serial, SerialException
from timeit import default_timer as timer
from time import sleep

serial_port_name = 'COM3'
serial_timeout = 5
delay_time_ms = 300

global responses_time_sum
global responses_count
responses_time_sum = 0
responses_count = 0

try:
    ardu = Serial(serial_port_name, 115200, timeout=serial_timeout)
except SerialException:
    print(SerialException)

print('Port: ' + ardu.name + ' (' + ('opened' if ardu.is_open else 'closed') + ')')


def write_json(json_bytes):
    json_bytes += b'\n'
    print("Sending " + str(json_bytes))

    start = timer()
    ardu.write(json_bytes)
    response = ardu.readline()
    end = timer()

    print("Response: " + str(response))

    response_time = (end - start) * 1000
    timeout = False

    if response_time >= serial_timeout * 1000:
        print("Timeout reached.")
        timeout = True
    else:
        print("Response time: " + str(response_time) + "ms")

    return timeout, response_time


def test(data):
    global responses_count
    global responses_time_sum

    timeout, response_time = write_json(data)

    if not timeout:
        responses_count += 1
        responses_time_sum += response_time


try:
    while True:
        # test(b'{ddd}')  # invalid json
        # test(b'{}')  # empty json
        # test(b'{"type":"test"}')  # no data
        # test(b'{"type": "test", "data": {}}')  # unknown request type
        # data not being an object
        #test(b'{"type": "data_request", "data":"not an object"}')
        # test(b'{"type": "data_request", "data":{}}')  # data is an empty object
        # flag is not a number
        #test(b'{"type": "data_request", "data":{"flag": "d"}}')
        # well, this will yield a result
        #test(b'{"type": "data_request", "data":{"flag": 929292}}')
        test(b'{"type": "data_request", "data":{"flag": 7}}')  # valid

except KeyboardInterrupt:
    ardu.close()
    avg_response_time = responses_time_sum / responses_count
    avg_response_frequency = 1 / (avg_response_time / 1000)
    print("\n\nResponses count: " + str(responses_count))
    print("Average response time: " + str(avg_response_time) + "ms")
    print("Average response frequency: " + str(avg_response_frequency) + "Hz")