#include <doctest/doctest.h>
#include <expected_function.hpp>

TEST_CASE("expected_function_test")
{
    CHECK_UNARY(cbp::expected_function());
}
