#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "button.h"
#include "timer.h"

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
            }

            _working = !_working;
            timer.reset();
        }

        // TODO: Display timer.
    }
private:
    Button _button{};
    Timer _work_timer;
    Timer _rest_timer;

    bool _working = true;
};

#endif