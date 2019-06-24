
import serial
import time
import json

SERIAL_PORT_NAME = "/dev/ttyACM0"

AXIS_DATA = [
    {"name": "X", "startingPower": 20, "ticksPerMm": 5600},
    {"name": "Breaker", "startingPower": 35, "ticksPerMm": 8400},
    {"name": "Wheel", "startingPower": 35, "ticksPerMm": 266.666}
]


def main():
    arduinoPort = serial.Serial(SERIAL_PORT_NAME, 115200, timeout=1)
    print("Opened port: " + arduinoPort.name)
    time.sleep(2)
    for axis in AXIS_DATA:
        print("Testing axis {0}".format(axis["name"]))
        testSpeed(arduinoPort, axis)
        time.sleep(1)


def testSpeed(arduinoPort, axis):
    power = axis["startingPower"] + 50
    powerRequest(arduinoPort, axis["name"], power)
    time.sleep(1)
    printSpeed(axis, power, dataToJson(dataRequest(arduinoPort)))
    powerRequest(arduinoPort, axis["name"], 0)

def printSpeed(axis, power, data):
    ticks = getEncoderReading(data[axis["name"]])
    ticksPerMm = ticks / axis["ticksPerMm"]

    print("Power: {0}, raw reading: {1}, calculated speed: {2}mm/s".format(power, ticks, ticksPerMm))

def powerRequest(arduinoPort, axis, power):
    actual_request = '{"Request": "SetPower", "Data":{"' + \
        axis + '": ' + str(power) + ' } }'
    return sendMessage(arduinoPort, actual_request)


def getEncoderReading(axisJson):
    return axisJson["EncoderTicks"]


def dataToJson(data):
    return json.loads(data)


def dataRequest(arduinoPort):
    return sendMessage(arduinoPort, '{"Request": "GetData", "Data":{ } }')


def sendJson(port, json):
    rawJson = json.dumps(json, separators=(',', ':')).replace('\\', '')
    print("Sending " + rawJson)
    receivedData = sendMessage(port, rawJson)
    print("Raw received string: " + receivedData)

    return json.loads(receivedData)


def sendMessage(port, message):
    messageData = (message + '\n').encode("ASCII")
    port.write(messageData)
    output = str()
    buffer = str(port.readline().decode("ASCII"))
    while(len(buffer) > 0):
        output += buffer
        buffer = str(port.readline().decode("ASCII"))

    return output


if __name__ == "__main__":
    main()
