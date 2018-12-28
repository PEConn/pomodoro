#include "timer_printer.h"

#include "catch.hpp"
#include "test_util.h"
#include "util.h"

TEST_CASE("TimerPrinter", "[timer_printer]") {
    TimerPrinter tp{};

    SECTION("zero") {
        requireStr("00:00/25:00", tp.update(ms(0, 0), ms(25, 0)));
        requireStr("0:00/5:00  ", tp.update(ms(0, 0), ms(5, 0)));
    }

    SECTION("seconds") {
        requireStr("00:31/25:00", tp.update(ms(0, 31), ms(25, 0)));
        requireStr("0:31/5:00  ", tp.update(ms(0, 31), ms(5, 0)));
    }

    SECTION("minutes") {
        requireStr("07:00/25:00", tp.update(ms(7, 0), ms(25, 0)));
        requireStr("16:00/25:00", tp.update(ms(16, 0), ms(25, 0)));
        requireStr("3:00/5:00  ", tp.update(ms(3, 0), ms(5, 0)));
    }

    SECTION("both") {
        requireStr("08:52/25:00", tp.update(ms(8, 52), ms(25, 0)));
        requireStr("13:12/25:00", tp.update(ms(13, 12), ms(25, 0)));
        requireStr("1:20/5:00  ", tp.update(ms(1, 20), ms(5, 0)));
    }

    SECTION("full") {
        requireStr("25:00/25:00", tp.update(ms(25, 0), ms(25, 0)));
        requireStr("5:00/5:00  ", tp.update(ms(5, 0), ms(5, 0)));
    }

    SECTION("overflow") {
        // TODO: Better error handling.
        // 112 -> 52 because we modulus minutes to 60.
        requireStr("07:31/52:00", tp.update(ms(7, 31), ms(112, 0)));
        // 12 -> 12 because we don't enforce time < duration.
        requireStr("12:12/5:00 ", tp.update(ms(12, 12), ms(5, 0)));
    }

    SECTION("column selection") {
        requireStr("0:00/9:59  ", tp.update(ms(0, 0), ms(9, 59)));
        requireStr("00:00/10:00", tp.update(ms(0, 0), ms(10, 0)));
    }
}