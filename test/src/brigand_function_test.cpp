#include <doctest/doctest.h>
#include "../../include/brigand_function.hpp"

TEST_CASE("brigand_function_test")
{
	CHECK_UNARY(cbp::brigand_function());
}
