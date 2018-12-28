#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>

#include "progress_bar.h"
#include "timer_printer.h"

/**
 * Generates and stores two blocks 16 character lines of text, as such:
 * |<---- 16 ---->|
 * [---  ] Done:  2
 * 16:32/25:00 Work
 */
class Printer {
public:
    void update(unsigned long time, unsigned long duration,
            bool working, unsigned int completed) {
        
        snprintf(&_top_line[0], _array_size, "%s Done: %2u",
            _progress_bar.update(time, duration),
            completed);

        snprintf(&_bottom_line[0], _array_size, "%s %s",
            _timer_printer.update(time, duration),
            working ? "Work" : "Rest");
    }

    char *getTopLine() {
        return _top_line;
    }

    char *getBottomLine() {
        return _bottom_line;
    }
private:
    TimerPrinter _timer_printer;
    ProgressBar<5> _progress_bar;

    // Line length is 16, plus 1 for null terminator.
    static constexpr unsigned int _array_size = 16 + 1;
    char _top_line[_array_size];
    char _bottom_line[_array_size];
};

#endif