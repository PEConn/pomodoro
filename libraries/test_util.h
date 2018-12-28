#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <string>

#include "catch.hpp"

inline void requireStr(const char *exp, char *act) {
    REQUIRE(std::string(exp) == std::string(act));
}

#endif