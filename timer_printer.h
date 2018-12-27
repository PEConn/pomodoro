#ifndef TIMER_PRINTER_H
#define TIMER_PRINTER_H


// TODO: Do this really need to be a class? I'm not using polymorphism
// for testing, so I'm not gaining anything over just functions.
/**
 * Gives a string representation of a Timer, takes 11 characters as such:
 * |16:31/25:00|
 * |4:06/5:00  |
 */
class TimerPrinter {
public:
    char *update(unsigned long time, unsigned long duration) {
        char *format = msToMinutes(duration) < 10
                ? "%lu:%02lu/%lu:%02lu  "
                : "%02lu:%02lu/%02lu:%02lu";

        snprintf(&_display[0], _array_size, format,
            msToMinutes(time), msToSeconds(time),
            msToMinutes(duration), msToSeconds(duration));
        
        return str();
    }

    char *str() {
        return &_display[0];
    }
private:
    // TODO: Move these somewhere else.
    static unsigned long msToSeconds(unsigned long ms) {
        return (ms / 1000) % 60;
    }

    static unsigned long msToMinutes(unsigned long ms) {
        return (ms / (1000 * 60)) % 60;
    }

    // TODO: Can I extract common functionality between this and ProgressBar?
    // Plus 1 for the '\0'
    static constexpr unsigned int _array_size = 11 + 1;
    char _display[_array_size];
};

#endif