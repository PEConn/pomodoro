#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "button.h"
#include "timer.h"
#include "printer.h"

// TODO: Create library functions (millis <-> minutes).
const int WORK_TIME_MS = 25 * 60 * 1000;
const int REST_TIME_MS = 25 * 60 * 1000;

class Controller {
public:
    Controller() : _work_timer(WORK_TIME_MS), _rest_timer(REST_TIME_MS) {}

    void begin() {
        // TODO: Load number of completed.
    }

    void loop(unsigned long millis, bool buttonDown) {
        _button.updateState(buttonDown);

        Timer &timer = _working ? _work_timer : _rest_timer;

        if (_button.isPressed()) {
            timer.toggle(millis);
        }

        if (timer.completed(millis)) {
            if (_working) {
                // TODO: Save completed++.
                _completed++;
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

    bool _working = true;
    unsigned int _completed = 0;
};

#endif