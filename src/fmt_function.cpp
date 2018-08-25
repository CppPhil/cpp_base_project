#include <fmt/format.h>
#include <fmt_function.hpp>
#include <string>

namespace cbp {
bool fmt_function()
{
    const std::string s{fmt::format("{0}{1}{0}", "abra", "cad")};
    return s == "abracadabra";
}
} // namespace cbp
