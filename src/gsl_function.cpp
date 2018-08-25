#include <gsl/pointers>
#include <gsl_function.hpp>

namespace cbp {
bool gsl_function()
{
    bool                 v{false};
    gsl::not_null<bool*> p{&v};
    *p = true;
    return *p;
}
} // namespace cbp
