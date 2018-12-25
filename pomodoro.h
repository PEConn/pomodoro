#ifndef POMODORO_H
#define POMODORO_H

// TODO: Hide this behind a debug.
#include <iostream>

class Pomodoro {
public:
    void begin() {

    }
    void loop(unsigned long millis, bool buttonDown) {
    }

    // TODO: What should I use for printing?
    char *getProgressLine(unsigned long time_ms) {
        // Output: "[--    ] Done: 0"
        unsigned long passed_time_ms = passed_time_in_period_ms(time_ms);
        // TODO: Make this memory safe.
        unsigned long work_length_ms = minutes_to_ms(_work_length_minutes);

        // TODO: Make this less ugly.
        unsigned int fraction = 0;
        if (passed_time_ms <= work_length_ms) {
            fraction = passed_time_ms * 6 / work_length_ms;
        } else {
            fraction = (passed_time_ms - minutes_to_ms(_rest_length_minutes)) * 6
                        / minutes_to_ms(_rest_length_minutes);
        }

        char progress[] = "     ";
        for (unsigned int i = 0; i < fraction; i++) progress[i] = '-';
        snprintf(&_first_line[0], 17, "[%s] Done: %02lu",
                progress,
                num_periods_passed(time_ms));

        return &_first_line[0];
    }
    char *getTimeLine(unsigned long time_ms) {
        // Output: "16:32/25:00 Work"
        unsigned long passed_time_ms = passed_time_in_period_ms(time_ms);
        // TODO: Make this memory safe.
        if (passed_time_ms <= minutes_to_ms(_work_length_minutes)) {
            snprintf(&_second_line[0], 17, "%02lu:%02lu/%02lu:%02lu Work",
                    ms_to_minutes(passed_time_ms),
                    ms_to_seconds(passed_time_ms),
                    _work_length_minutes,
                    0);
        } else {
            snprintf(&_second_line[0], 17, "%02lu:%02lu/%02lu:%02lu Rest",
                    ms_to_minutes(passed_time_ms) - _work_length_minutes,
                    ms_to_seconds(passed_time_ms),
                    _rest_length_minutes,
                    0);
        }
        return &_second_line[0];
    }
private:
    unsigned long passed_time_in_period_ms(unsigned long time_ms) {
        unsigned long passed_time_ms = time_ms - _paused_time_ms - _start_time_ms;
        unsigned long period_ms = minutes_to_ms(_work_length_minutes + _rest_length_minutes);
        return passed_time_ms % period_ms;
    }

    unsigned long num_periods_passed(unsigned long time_ms) {
        unsigned long passed_time_ms = time_ms - _paused_time_ms - _start_time_ms;
        unsigned long period_ms = minutes_to_ms(_work_length_minutes + _rest_length_minutes);
        return passed_time_ms / period_ms;
    }

    // TODO: Make static/anon
    unsigned long minutes_to_ms(unsigned long minutes) {
        return minutes * 60 * 1000;
    }

    unsigned long ms_to_seconds(unsigned long ms) {
        return (ms / 1000) % 60;
    }

    unsigned long ms_to_minutes(unsigned long ms) {
        return (ms / (1000 * 60)) % 60;
    }
    
    unsigned long _start_time_ms = 0;
    unsigned long _paused_time_ms = 0;
    unsigned long _work_length_minutes = 25;
    unsigned long _rest_length_minutes = 5;

    // TODO: Get rid of these.
    char _first_line[17] = {};
    char _second_line[17] = {};
};

#endif