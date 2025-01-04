#ifndef SEGLCDLIB_H
#define SEGLCDLIB_H

#include <Arduino.h>

typedef enum {
    MODE_BIAS_13 = 0,
    MODE_BIAS_12 = 1
} ModeBias;

typedef enum {
    MODE_DRIVE_STATIC = 1,
    MODE_DRIVE_12 = 2,
    MODE_DRIVE_13 = 3,
    MODE_DRIVE_14 = 0
} ModeDrive;

class SegLCDLib {
    public:
        virtual void begin() = 0;
        virtual void clear() = 0;
        virtual ~SegLCDLib() {}
        virtual void display() = 0;
        virtual void noDisplay() = 0;

    protected:
        virtual void _write(uint8_t data, uint8_t address) = 0;
        virtual void _write(uint8_t *data, size_t length, uint8_t address) = 0;
};

#endif