#ifndef RESPONSETYPE_H
#define RESPONSETYPE_H


enum class ResponseType
{
    UNKNOWN,
    ERROR,
    DATA
};

enum class ResponseObject
{
    UNKNOWN,
    MOTORS,
    ENDSTOPS,
    ENCODERS
};

#endif // RESPONSETYPE_H
