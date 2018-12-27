#include "catch.hpp"

#include "pauser.h"

TEST_CASE("Pauser works correctly", "[pauser]") {
    Pauser pauser{};
    REQUIRE(!pauser.isPaused());
    
    SECTION("no pauses") {
        REQUIRE(20 == pauser.getResumedTime(20));
        REQUIRE(0 == pauser.getResumedTime(0));
    }

    SECTION("paused") {
        pauser.pause(200);
        REQUIRE(pauser.isPaused());

        REQUIRE(200 == pauser.getResumedTime(200));
        REQUIRE(200 == pauser.getResumedTime(400));
    }

    SECTION("paused then resumed") {
        pauser.pause(300);
        pauser.resume(500);

        REQUIRE(!pauser.isPaused());
        REQUIRE(600 == pauser.getResumedTime(800));
    }

    SECTION("paused twice") {
        pauser.pause(200);
        pauser.resume(400);
        pauser.pause(600);

        REQUIRE(400 == pauser.getResumedTime(800));
    }
}