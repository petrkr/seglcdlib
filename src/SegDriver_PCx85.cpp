#include <Arduino.h>
#include <SegDriver_PCx85.h>


SegDriver_PCx85::SegDriver_PCx85(TwoWire& i2c, uint8_t address, uint8_t subaddress) : _i2c(i2c) {
    _address = address;
    _subaddress = subaddress;
}

void SegDriver_PCx85::begin() {
    _deviceSelect();
}

void SegDriver_PCx85::bankSelect(uint8_t input, uint8_t output) {
    uint8_t data;

    data |= CMD_BANK_SELECT;
    data |= input << 1;
    data |= output;
    data |= CMD_LAST_COMMAND;

    _i2c.beginTransmission(_address);
    _i2c.write(data);
    _i2c.endTransmission();
}

void SegDriver_PCx85::blink(BlinkFrequency frequency, BlinkMode mode) {
    uint8_t data;

    data |= CMD_BLINK;
    data |= mode << 2;
    data |= frequency;
    data |= CMD_LAST_COMMAND;

    _i2c.beginTransmission(_address);
    _i2c.write(data);
    _i2c.endTransmission();
}

void SegDriver_PCx85::clear() {
    uint8_t tmp[(MAX_ADDRESS / 2) - 1] = { 0 };
    _write(tmp, sizeof(tmp), 0);
}

void SegDriver_PCx85::display() {
    _setMode(MODE_STATUS_ENABLED, _bias, _drive);
}

void SegDriver_PCx85::noDisplay() {
    _setMode(MODE_STATUS_BLANK, _bias, _drive);
}

void SegDriver_PCx85::_write(uint8_t data, uint8_t address) {
    _write(&data, 1, address);
}

void SegDriver_PCx85::_write(uint8_t *data, size_t length, uint8_t address) {
    _i2c.beginTransmission(_address);
    _i2c.write(address);
    _i2c.write(data, length);
    _i2c.endTransmission();
}

void SegDriver_PCx85::_deviceSelect() {
    uint8_t data;

    data |= CMD_DEVICE_SELECT;
    data |= _subaddress;
    data |= CMD_LAST_COMMAND;

    _i2c.beginTransmission(_address);
    _i2c.write(data);
    _i2c.endTransmission();
}

void SegDriver_PCx85::_setMode(ModeStatus status, ModeBias bias, ModeDrive drive) {
    _bias = bias;
    _drive = drive;

    uint8_t data;

    data |= CMD_MODE;
    data |= status << 3;
    data |= _bias << 2;
    data |= _drive;
    data |= CMD_LAST_COMMAND;

    _i2c.beginTransmission(_address);
    _i2c.write(data);
    _i2c.endTransmission();
}
