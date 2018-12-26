#include <string>

#include "catch.hpp"

#include "timer.h"

// TODO: Move this into a header.
extern void requireStr(const char *exp, char *act);

TEST_CASE("Timer", "[timer]") {
    Timer timer{500};

    SECTION("not started") {
        REQUIRE(0 == timer.elapsed(0));
        REQUIRE(0 == timer.elapsed(500));
    }

    SECTION("started") {
        timer.start(100);
        REQUIRE(0 == timer.elapsed(100));
        REQUIRE(100 == timer.elapsed(200));
    }
    
    SECTION("paused") {
        timer.start(100);
        timer.stop(200);
        REQUIRE(100 == timer.elapsed(200));
        REQUIRE(100 == timer.elapsed(300));
    }

    SECTION("restarted") {
        timer.start(100);
        timer.stop(200);
        timer.start(300);
        REQUIRE(200 == timer.elapsed(400));
    }

    SECTION("completed") {
        timer.start(0);
        REQUIRE_FALSE(timer.completed(0));
        REQUIRE(timer.completed(500));
    }
}