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
        
        // TODO: Make these not magic numbers.
        _display[WIDTH + 1] = ']';
        _display[WIDTH + 2] = '\0';
    }
        // unsigned int fraction = 0;
        // if (passed_time_ms <= work_length_ms) {
        //     fraction = passed_time_ms * 6 / work_length_ms;
        // } else {
        //     fraction = (passed_time_ms - minutes_to_ms(_rest_length_minutes)) * 6
        //                 / minutes_to_ms(_rest_length_minutes);
        // }

        // char progress[] = "     ";
        // for (unsigned int i = 0; i < fraction; i++) progress[i] = '-';
        // snprintf(&_first_line[0], 17, "[%s] Done: %02lu",
        //         progress,
        //         num_periods_passed(time_ms));
    char *update(unsigned int progress, unsigned int max) {
        // We use WIDTH + 1, because a display of say 5 segments, has 6
        // potential values.
        unsigned int fraction = progress * (WIDTH + 1) / max;
        for (unsigned int i = 0; i < WIDTH; i++) {
            _display[1 + i] = (i < fraction) ? '-' : ' ';
        }

        return &_display[0];
    }
private:
    // Plus 2 to hold the brackets and plus 1 for the null terminator.
    char _display[WIDTH + 2 + 1];
};

#endif