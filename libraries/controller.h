#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "button.h"
#include "printer.h"
#include "saved_data.h"
#include "timer.h"

class Controller {
public:
    Controller(unsigned long work_duration_ms, unsigned long rest_duration_ms)
            : _work_timer(work_duration_ms), _rest_timer(rest_duration_ms) {}

    void begin() {
        _completed = _saved_data.readCompleted();
    }

    void loop(unsigned long millis, bool button_down) {
        _button.updateState(button_down);

        Timer &timer = _working ? _work_timer : _rest_timer;

        if (_button.isPressed()) {
            timer.toggle(millis);
        }

        if (timer.completed(millis)) {
            if (_working) {
                _completed++;
                _saved_data.writeCompleted(_completed);
            }

            _working = !_working;
            timer.reset();
        }
        
        _printer.update(timer.elapsed(millis), timer.duration(),
                _working, _completed);
    }

    char *getTopLine() {
        return _printer.getTopLine();
    }

    char *getBottomLine() {
        return _printer.getBottomLine();
    }
private:
    Button _button{};
    Timer _work_timer;
    Timer _rest_timer;
    Printer _printer{};
    SavedData _saved_data{};

    bool _working = true;
    unsigned int _completed = 0;
};

#endif