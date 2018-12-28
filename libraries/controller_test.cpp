#include "controller.h"

#include "catch.hpp"
#include "test_util.h"
#include "util.h"

TEST_CASE("Controller", "[controller]") {
    Controller controller{ms(25, 0), ms(5, 0)};
    controller.begin();

    // Press the button to start.
    controller.loop(0, true);

    SECTION("basic") {
        controller.loop(ms(9, 24), false);

        // getBottomLine() gives more informative test failures.
        requireStr("09:24/25:00 Work", controller.getBottomLine());
        requireStr("[--   ] Done:  0", controller.getTopLine());

        controller.loop(ms(23, 12), false);
        requireStr("23:12/25:00 Work", controller.getBottomLine());
        requireStr("[-----] Done:  0", controller.getTopLine());

        // Controller needs an iteration to switch modes.
        controller.loop(ms(25, 0), false);
        // Press the start button again.
        controller.loop(ms(25, 0), true);

        controller.loop(ms(27, 12), false);
        requireStr("2:12/5:00   Rest", controller.getBottomLine());
        requireStr("[--   ] Done:  1", controller.getTopLine());
    }

    SECTION("pause") {
        controller.loop(ms(5, 0), false);
        requireStr("05:00/25:00 Work", controller.getBottomLine());
        requireStr("[-    ] Done:  0", controller.getTopLine());

        controller.loop(ms(6, 0), true);
        requireStr("06:00/25:00 Work", controller.getBottomLine());
        requireStr("[-    ] Done:  0", controller.getTopLine());

        controller.loop(ms(12, 0), false);
        requireStr("06:00/25:00 Work", controller.getBottomLine());
        requireStr("[-    ] Done:  0", controller.getTopLine());
    }
}