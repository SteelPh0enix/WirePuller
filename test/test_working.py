#!/bin/python3
# This is a `data_request` request type test
from serial import Serial, SerialException
from timeit import default_timer as timer
from time import sleep

serial_port_name = '/dev/ttyACM0'
serial_timeout = 5
delay_time_ms = 300

global responses_time_sum
global responses_count
responses_time_sum = 0
responses_count = 0

try:
    ardu = Serial(serial_port_name, 250000, timeout=serial_timeout)
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
    test(b'{"type": "reset_encoder", "data": {"ENC_OX": true, "ENC_WH": true}}')
    while True:
        test(b'{type: "set_motor_speed", "data": {"MOT_OX": -150, "MOT_WH": 00}}')
        #test(b'{"type": "data_request", "data":{"flag": 7}}')  # valid
        #sleep(1)
        #test(b'{type: "set_motor_speed", "data": {"MOT_OX": 50, "MOT_WH": 200}}')
        #test(b'{"type": "data_request", "data":{"flag": 7}}')  # valid
        #sleep(1)

except KeyboardInterrupt:
    ardu.close()
    avg_response_time = responses_time_sum / responses_count
    avg_response_frequency = 1 / (avg_response_time / 1000)
    print("\n\nResponses count: " + str(responses_count))
    print("Average response time: " + str(avg_response_time) + "ms")
    print("Average response frequency: " + str(avg_response_frequency) + "Hz")
