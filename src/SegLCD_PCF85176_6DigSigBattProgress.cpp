#include <Wire.h>
#include <SegLCD_PCF85176_6DigSigBattProgress.h>


SegLCD_PCF85176_6DigitSignalBatteryProgress::SegLCD_PCF85176_6DigitSignalBatteryProgress(TwoWire& i2c, uint8_t address, uint8_t subaddress) :  SegDriver_PCF85176(i2c, address, subaddress) {}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::begin() {
    SegDriver_PCF85176::begin();
    _setMode(MODE_STATUS_ENABLED, MODE_BIAS_13, MODE_DRIVE_14);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::setBatteryLevel(uint8_t level) {
    if (level > 4)
        level = 4;

    _buffer_sigbatt &= ~(0x0f);

    if (level > 0)
        _buffer_sigbatt |= 8;
    if (level > 1)
        _buffer_sigbatt |= 1;
    if (level > 2)
        _buffer_sigbatt |= 2;
    if (level > 3)
        _buffer_sigbatt |= 4;

    _write(_buffer_sigbatt, ADDR_SIGNAL_BATT);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::setSignalLevel(uint8_t level) {
    if (level > 4)
        level = 4;

    _buffer_sigbatt &= ~(0xf0);

    if (level > 0)
        _buffer_sigbatt |= 0x80;
    if (level > 1)
        _buffer_sigbatt |= 0x40;
    if (level > 2)
        _buffer_sigbatt |= 0x20;
    if (level > 3)
        _buffer_sigbatt |= 0x10;

    _write(_buffer_sigbatt, ADDR_SIGNAL_BATT);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::setProgress(uint8_t value) {
    uint8_t buffer[2] = { 0, 0 };

    if (value > 0) {
        buffer[0] |= 0x80;
    }
    if (value >= 10) {
        buffer[0] |= 0x40;
    }
    if (value >= 20) {
        buffer[0] |= 0x20;
    }
    if (value >= 30) {
        buffer[0] |= 0x10;
    }
    if (value >= 40) {
        buffer[0] |= 0x08;
    }
    if (value >= 50) {
        buffer[0] |= 0x04;
    }
    if (value >= 60) {
        buffer[0] |= 0x02;
    }
    if (value >= 70) {
        buffer[0] |= 0x01;
    }

    if (value >= 80) {
        buffer[1] |= 0x80;
    }
    if (value >= 90) {
        buffer[1] |= 0x40;
    }
    if (value >= 100) {
        buffer[1] |= 0x20;
    }
    if (value >= 110) {
        buffer[1] |= 0x10;
    }
    if (value >= 120) {
        buffer[1] |= 0x08;
    }
    if (value >= 130) {
        buffer[1] |= 0x04;
    }
    if (value >= 140) {
        buffer[1] |= 0x02;
    }
    if (value == 150) {
        buffer[1] |= 0x01;
    }

    _write(buffer, sizeof(buffer), ADDR_PROGRESS);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::setWheel(uint16_t value) {
    uint8_t buffer[2] = { 0, 0 };
    
    buffer[0] = value & 0xFF;
    buffer[1] = (((value >> 8) & 0x0F) << 4);

    _write(buffer, sizeof(buffer), ADDR_WHEEL);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::setLabels(LabelFlags labels) {
    _buffer_labels |= labels;
    
    _write(_buffer_labels, ADDR_PRES_LABELS);
}

void SegLCD_PCF85176_6DigitSignalBatteryProgress::clearLabels(LabelFlags labels) {
    _buffer_labels &= ~labels;
    
    _write(_buffer_labels, ADDR_PRES_LABELS);
}
