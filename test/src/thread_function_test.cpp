#include "../../include/thread_function.hpp"
#include <doctest/doctest.h>

TEST_CASE("thread_function_test")
{
    CHECK_UNARY(cbp::thread_function());
}

