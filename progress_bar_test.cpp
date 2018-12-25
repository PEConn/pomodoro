#include <string>

#include "catch.hpp"

#include "progress_bar.h"

// TODO: Move this into a header.
extern void requireStr(const char *exp, char *act);

TEST_CASE("ProgressBar", "[progress_bar]") {
    ProgressBar<5> pb{};

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