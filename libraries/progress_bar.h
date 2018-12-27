#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

/**
 * Draws an ASCII progress bar of |WIDTH| segments, eg:
 * [--   ]
 */
template <unsigned int WIDTH>
class ProgressBar {
public:
    ProgressBar() {
        _display[0] = '[';
        
        _display[_array_size - 2] = ']';
        _display[_array_size - 1] = '\0';
    }
    
    char *update(unsigned int progress, unsigned int max) {
        // We use WIDTH + 1, because a display of say 5 segments has 6
        // potential values.
        unsigned int fraction = progress * (WIDTH + 1) / max;
        for (unsigned int i = 0; i < WIDTH; i++) {
            _display[1 + i] = (i < fraction) ? '-' : ' ';
        }

        return str();
    }

    char *str() {
        return &_display[0];
    }
private:
    // Plus 2 for the '[]' and plus 1 for '\0'
    static constexpr unsigned int _array_size = WIDTH + 2 + 1;
    
    char _display[_array_size];
};

#endif