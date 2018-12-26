#ifndef TIMER_H
#define TIMER_H

/**
 * A countdown timer that allows pausing and printing.
 */
class Timer {
public:
    Timer(unsigned long duration) : _duration(duration) {}

    void start(unsigned long millis) {
        if (_running) return;
        _running = true;

        _last_start = millis;
    }

    void stop(unsigned long millis) {
        if (!_running) return;
        _running = false;

        _elapsed += millis - _last_start;
        _last_start = 0;
    }

    bool completed(unsigned long millis) {
        return elapsed(millis) >= _duration;
    }

    unsigned long elapsed(unsigned long millis) {
        if (_running) {
            return _elapsed + (millis - _last_start);
        }
        return _elapsed;
    }
private:
    unsigned long _duration;
    unsigned long _elapsed = 0;
    bool _running = false;
    unsigned long _last_start = 0;
};

#endif