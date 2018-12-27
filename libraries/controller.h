#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "button.h"
#include "printer.h"
// TODO: Make this build on tests.
#include "saved_data.h"
#include "timer.h"

// TODO: Create library functions (millis <-> minutes).
// const unsigned long WORK_TIME_MS = 25ul * 60 * 1000;
// const unsigned long REST_TIME_MS = 5ul * 60 * 1000;
const unsigned long WORK_TIME_MS = 10ul * 1000;
const unsigned long REST_TIME_MS = 5ul * 1000;

class Controller {
public:
    Controller() : _work_timer(WORK_TIME_MS), _rest_timer(REST_TIME_MS) {}

    void begin() {
        _completed = _saved_data.readCompleted();
    }

    void loop(unsigned long millis, bool buttonDown) {
        _button.updateState(buttonDown);

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