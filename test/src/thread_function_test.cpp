#include <doctest/doctest.h>
#include <thread_function.hpp>

TEST_CASE("thread_function_test") { CHECK_UNARY(cbp::thread_function()); }
