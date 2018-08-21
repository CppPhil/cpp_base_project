#include "../include/gsl_function.hpp"
#include <gsl/pointers>

namespace cbp {
bool gsl_function() {
  bool v{false};
  gsl::not_null<bool *> p{&v};
  *p = true;
  return *p;
}
} // namespace cbp
