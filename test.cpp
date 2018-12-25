#include <iostream>

#include "pomodoro.h"

int test(char *expected, char *actual) {
    if (strcmp(expected, actual) == 0) return 0;

    std::cout << "Expected: \"" << expected << "\"\n";
    std::cout << "Actual:   \"" << actual << "\"\n";

    return 1;
}

int main() {
    Pomodoro pm{};

    int errors = 0;
    
    errors += test("00:02/25:00 Work", pm.getTimeLine(2 * 1000));
    errors += test("12:00/25:00 Work", pm.getTimeLine(12 * 60 * 1000));
    errors += test("25:00/25:00 Work", pm.getTimeLine(25 * 60 * 1000));
    errors += test("02:00/05:00 Rest", pm.getTimeLine(27 * 60 * 1000));
    errors += test("04:59/05:00 Rest", pm.getTimeLine(30 * 60 * 1000 - 1));
    errors += test("00:00/25:00 Work", pm.getTimeLine(30 * 60 * 1000));
    errors += test("00:02/25:00 Work", pm.getTimeLine(30 * 60 * 1000 + 2 * 1000));

    errors += test("[     ] Done: 00", pm.getProgressLine(0));
    errors += test("[--   ] Done: 00", pm.getProgressLine(25 * 60 * 1000 * 2 / 6));
    errors += test("[--   ] Done: 00", pm.getProgressLine(25 * 60 * 1000 * 3 / 6 - 1));
    errors += test("[-----] Done: 00", pm.getProgressLine(25 * 60 * 1000 - 1));
    // TODO: Stuff for Rest progress bar.

    std::cout << errors << " errors";

    return errors == 0;
}