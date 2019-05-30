import serial
import time
import json

SERIAL_PORT_NAME = "COM12"


def main():
    arduinoPort = serial.Serial(SERIAL_PORT_NAME, 115200, timeout=1)
    print("Opened port: " + arduinoPort.name)
    time.sleep(1)

    cmd = input("Query: ")
    if (cmd == "data"):
        print(sendMessage(arduinoPort, '{"Request": "GetData", "Data":{ } }'))
    if (cmd == "power"):
        print(sendMessage(arduinoPort,
                          '{"Request": "SetPower", "Data": {"X": 123, "Wheel": 456, "Breaker": -123} }'))

    arduinoPort.close()


def sendJson(port, message):
    rawJson = json.dumps(message, separators=(',', ':')).replace('\\', '')
    print("Sending " + rawJson)
    receivedData = sendMessage(port, rawJson).decode("ASCII")
    print("Raw received string: " + receivedData)

    return json.loads(receivedData)


def sendMessage(port, message):
    messageData = (message + '\n').encode("ASCII")
    port.write(messageData)
    return port.readline()


if __name__ == "__main__":
    main()
