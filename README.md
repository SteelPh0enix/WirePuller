# WirePuller Arduino driver

## JSON API

### Description

JSON API will expose functionality of driver to external application by serial interface.
**Serial data rate is set to `115200` by default. Consult [`Globals.hpp`](lib/Globals/Globals.hpp) for details**

Note, that JSON should have **no line breaks** and, if possible, as little as possible white characters.
**Line break indicates the end of JSON (defined in [`Globals.hpp`](lib/Globals/Globals.hpp), `'\n'` by default)**

### Basic functionality

* Setting and getting motors speeds
* Getting endstops states
* Getting motor current draw and checking for errors
* Getting information from motor encoders

### Message format

Every message will be based on a basic skeleton

```json
{
    "type": "type",
    "data": {
        "field": object/value,
        "field": object/value
    }
}
```

Where

* `type` - *string* - type of the request. Valid types are listed below.
* `data` - *object* - request/response data.

#### Setting motor speeds

To set motor speeds, you have to send message like that

```json
{
    "type": "set_motor_speed",
    "data": {
        "motor_ID": speed,
        "motor_ID": speed
    }
}
```

Where

* `motor_ID` - *string* - ID of the motor
* `speed` - *number* - speed, in range [-400, 400] (will be limited to maximum/minimum if exceeding)

##### Example 1 - setting motors speed

```json
{
    "type": "set_motor_speed",
    "data": {
        "MOTOR1": 123,
        "MOTOR2": -20
    }
}
```

Driver will respond with the state of all motors

```json
{
    "type": "data",
    "data": {
        "motors": {
            "motor_ID": {
                "speed": speed,
                "current": current,
                "error": true/false
            },

            "motor_ID": {
                "speed": speed,
                "current": current,
                "error": true/false
            }
        }
    }
}
```

Where

* `speed` - *number* - actual speed of the motor
* `current` - *number* - current draw of motor, in milliampers

##### Example 2 - response from driver with motor data

```json
{
    "type": "data",
    "data": {
        "motors": {
            "MOTOR1": {
                "speed": 123,
                "current": 320,
                "error": false
            },

            "MOTOR2": {
                "speed": -20,
                "current": 0,
                "error": true
            },

            "MOTOR3": {
                "speed": -234,
                "current": 670,
                "error": false
            }
        }
    }
}
```

*Note: Motor speed will not be 0 in case of error, since it's readed from driver object (it will be basically the speed you have set, no matter what, it won't represent real speed of the motor at all times). I'm not sure about current tho.*

#### Getting the data

To request for data, you have to send a JSON like that

```json
{
    "type": "data_request",
    "data": {
        "flag": data_flag
    }
}
```

* `data_flag` - *number* - Flag informing what data do you request. It's combination of binary flags from DataFlags enum (see [`Globals.hpp`](lib/Globals/Globals.hpp))

##### Example 3 - requesting for data

```json
{
    "type": "data_request",
    "data": {
        "flag": 7
    }
}
```

And you will get a response (content will depend from the flag, but description below shows all the data driver can provide)

```json
{
    "type": "data",
    "data": {
        "motors": {
            "motor_ID": {
                "speed": speed,
                "current": current,
                "error": true/false
            },

            "motor_ID": {
                "speed": speed,
                "current": current,
                "error": true/false
            }
        },

        "endstops": {
            "endstop_ID": true/false,
            "endstop_ID": true/false
        },

        "encoders": {
            "encoder_ID": encoder_data,
            "encoder_ID": encoder_data
        }
    }
}
```

Where

* `speed` - *number* - actual speed of the motor
* `current` - *number* - current draw of motor, in milliampers
* `encoder_data` - *unknown yet* - data from encoder, the type and more info will be available soon

##### Example 4 - data from driver

```json
{
    "type": "data",
    "data": {
        "motors": {
            "MOTOR1": {
                "speed": 30,
                "current": 10,
                "error": false
            },

            "MOTOR2": {
                "speed": 250,
                "current": 1034,
                "error": false
            }
        },

        "endstops": {
            "ENDSTOP1": false,
            "ENDSTOP2": false,
            "ENDSTOP3": true,
            "ENDSTOP4": false
        }
    }
}
```

## Performance metrics

Dry request-response run (app skeleton, empty response) takes around 3ms, so i expect timings around 10ms which will give performance of around 100 requests and responses per second, but this is extremely optimistic number. Safe limit should be around 50 request and response cycles per second.

## Naming convention

To be done soon. Element ID's will be short (15 character max, excluding terminator) strings. I will probably put them in [`WirePullerApp.hpp`](lib/WirePullerApp/WirePullerApp.hpp)