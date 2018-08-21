#include "../../include/gsl_function.hpp"
#include <doctest/doctest.h>

TEST_CASE("gsl_function_test") { CHECK_UNARY(cbp::gsl_function()); }
