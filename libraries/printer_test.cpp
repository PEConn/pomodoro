#include "catch.hpp"

#include "printer.h"

// TODO: Move this into a header.
extern void requireStr(const char *exp, char *act);
extern unsigned long ms(int minutes, int seconds);

TEST_CASE("Printer", "[printer]") {
    Printer p{};

    SECTION("basic") {
        p.update(ms(16, 32), ms(25, 00), true, 3);
        requireStr("[---  ] Done:  3", p.getTopLine());
        requireStr("16:32/25:00 Work", p.getBottomLine());
    }

    SECTION("rest") {
        p.update(ms(3, 12), ms(5, 00), false, 4);
        requireStr("[---  ] Done:  4", p.getTopLine());
        requireStr("3:12/5:00   Rest", p.getBottomLine());
    }
}