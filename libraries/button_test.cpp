#include "button.h"

#include "catch.hpp"

TEST_CASE("Button works correctly", "[button]") {
    Button button{};
    REQUIRE(!button.isPressed());

    SECTION("initial down") {
        button.updateState(true);
        REQUIRE(button.isPressed());
    }

    SECTION("subsequent down") {
        button.updateState(true);
        button.updateState(true);
        REQUIRE(!button.isPressed());
    }

    SECTION("back up") {
        button.updateState(true);
        button.updateState(false);
        REQUIRE(!button.isPressed());
    }

    SECTION("reset") {
        button.updateState(true);
        button.updateState(false);
        button.updateState(true);
        REQUIRE(button.isPressed());
    }
}