#include "controller.h"

#include "catch.hpp"
#include "util.h"

TEST_CASE("Controller", "[controller]") {
    Controller controller{ms(25, 0), ms(5, 0)};
}