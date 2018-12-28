#include "progress_bar.h"

#include "catch.hpp"
#include "test_util.h"

TEST_CASE("ProgressBar", "[progress_bar]") {
    ProgressBar<5> pb{};
    // TODO: Add some tests for invalid inputs.

    SECTION("empty") {
        requireStr("[     ]", pb.update(0, 6));
    }

    SECTION("midway") {
        requireStr("[--   ]", pb.update(2, 6));
    }
    
    SECTION("full") {
        requireStr("[-----]", pb.update(6, 6));
    }
}