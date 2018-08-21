#include "../../include/expected_lite_function.hpp"
#include <doctest/doctest.h>

TEST_CASE("expected_lite_function_test") {
  CHECK_UNARY(cbp::expected_lite_function());
}
