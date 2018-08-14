#include <doctest/doctest.h>
#include "../../include/expected_lite_function.hpp"

TEST_CASE("expected_lite_function_test")
{
	CHECK_UNARY(cbp::expected_lite_function());
}

