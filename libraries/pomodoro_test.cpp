#include "pomodoro.h"

#include "catch.hpp"
#include "test_util.h"

TEST_CASE("Time output is correct", "[output]") {
    Pomodoro pm{};

    requireStr("00:02/25:00 Work", pm.getTimeLine(2 * 1000));
    requireStr("00:02/25:00 Work", pm.getTimeLine(2 * 1000));
    requireStr("12:00/25:00 Work", pm.getTimeLine(12 * 60 * 1000));
    requireStr("25:00/25:00 Work", pm.getTimeLine(25 * 60 * 1000));
    requireStr("02:00/05:00 Rest", pm.getTimeLine(27 * 60 * 1000));
    requireStr("04:59/05:00 Rest", pm.getTimeLine(30 * 60 * 1000 - 1));
    requireStr("00:00/25:00 Work", pm.getTimeLine(30 * 60 * 1000));
    requireStr("00:02/25:00 Work", pm.getTimeLine(30 * 60 * 1000 + 2 * 1000));
}

TEST_CASE("Progress output is correct", "[output]") {
    Pomodoro pm{};

    requireStr("[     ] Done: 00", pm.getProgressLine(0));
    requireStr("[--   ] Done: 00", pm.getProgressLine(25 * 60 * 1000 * 2 / 6));
    requireStr("[--   ] Done: 00", pm.getProgressLine(25 * 60 * 1000 * 3 / 6 - 1));
    requireStr("[-----] Done: 00", pm.getProgressLine(25 * 60 * 1000 - 1));
}