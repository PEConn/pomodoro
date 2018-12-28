#ifndef SAVED_DATA_H
#define SAVED_DATA_H

#ifdef COMPILE_FOR_DEVICE

#include <EEPROM.h>

#else

class Eeprom {
public:
    // The real read returns a 'byte', which is an unsigned char.
    unsigned char read(int address) {}
    void update(int address, unsigned char value) {}
};

Eeprom EEPROM{};

#endif

class SavedData {
public:
    unsigned int readCompleted() {
        if (EEPROM.read(_version_addr) != _version) {
            return 0;
        }

        return EEPROM.read(_completed_addr);
    }

    void writeCompleted(unsigned int completed) {
        if (!_version_written) {
            EEPROM.update(_version_addr, _version);
        }

        EEPROM.update(_completed_addr, completed);
    }
private:
    constexpr static int _version_addr = 0;
    constexpr static int _completed_addr = 1;

    constexpr static int _version = 200;

    bool _version_written = false;
};

#endif