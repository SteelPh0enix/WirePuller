import serial
import time
import json

SERIAL_PORT_NAME = "/dev/ttyACM0"


def main():
    arduinoPort = serial.Serial(SERIAL_PORT_NAME, 115200, timeout=1)
    print("Opened port: " + arduinoPort.name)
    time.sleep(1)

    while(True):
        try:
            cmd = input("Query: ").split(' ')
            if (cmd[0] == "data"):
                print(sendMessage(arduinoPort,
                                  '{"Request": "GetData", "Data":{ } }'))
            if (cmd[0] == "power"):
                powerRequest(cmd, arduinoPort)
            if (cmd[0] == "stop"):
                print(sendMessage(
                    arduinoPort, '{"Request": "SetPower", "Data": {"X": 0, "Wheel": 0, "Breaker": 0} }'))
        except KeyboardInterrupt:
            arduinoPort.close()
            exit(0)


def powerRequest(command, arduinoPort):
    actual_request = '{"Request": "SetPower", "Data":{"' + \
        command[1] + '": ' + command[2] + ' } }'

    print("Message: " + actual_request)

    print(sendMessage(arduinoPort, actual_request))


def sendJson(port, message):
    rawJson = json.dumps(message, separators=(',', ':')).replace('\\', '')
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
