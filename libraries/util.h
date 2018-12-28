#ifndef UTIL_H
#define UTIL_H

inline unsigned long ms(unsigned long minutes, unsigned long seconds) {
    return minutes * 60 * 1000 + seconds * 1000;
}

#endif