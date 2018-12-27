#ifndef BUTTON_H
#define BUTTON_H

/**
 * Given the current state of a button (down/up), returns whether it has just
 * been pressed.
 */
class Button {
public:
    void updateState(bool down) {
        _was_down = _is_down;
        _is_down = down;
    }

    bool isPressed() {
        return _is_down && !_was_down;
    }
private:
    bool _is_down = false;
    bool _was_down = false;
};

#endif