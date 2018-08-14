#include <doctest/doctest.h>
#include "../../include/gsl_function.hpp"

TEST_CASE("gsl_function_test")
{
    CHECK_UNARY(cbp::gsl_function());
}

