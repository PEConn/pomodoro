#ifndef PAUSER_H
#define PAUSER_H

/**
 * An abstraction over time that allows pausing.
 */
class Pauser {
public:
    void pause(unsigned long millis) {
        if (_paused) return;

        _paused = true;
        _last_paused_time = millis;
    }

    void resume(unsigned long millis) {
        if (!_paused) return;

        _paused = false;
        _total_paused_duration += millis - _last_paused_time;
        _last_paused_time = 0;
    }

    bool isPaused() {
        return _paused;
    }

    unsigned long getResumedTime(unsigned long millis) {
        if (_paused) {
            return _last_paused_time - _total_paused_duration;
        } else {
            return millis - _total_paused_duration;
        }
    }
private:
    bool _paused = false;
    unsigned long _total_paused_duration = 0;
    unsigned long _last_paused_time = 0;
};

#endif