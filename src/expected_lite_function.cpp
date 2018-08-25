#include <ciso646>
#include <cstdlib>
#include <expected_lite_function.hpp>
#include <nonstd/expected.hpp>
#include <string>

namespace cbp {
namespace {
/*!
 * \brief Function with internal linkage to convert a null-terminated
 *        byte character string into an integer.
 * \param text A null-terminated byte character string to convert to
 *             an integer.
 * \return An expected containing the resulting integer or containing
 *         a string that contains an error message on error.
 **/
auto to_int(const char* text) -> nonstd::expected<int, std::string>
{
    using namespace std::literals::string_literals;

    char* pos{nullptr};
    auto  value = std::strtol(text, &pos, 0);

    if (pos != text) { return value; }

    return nonstd::make_unexpected("'"s + text + "' isn't a number");
}
} // anonymous namespace

bool expected_lite_function()
{
    static const char number[] = "42";
    static const char text[]   = "text";

    auto ei = to_int(number);

    bool firstOk{false};
    bool secondOk{false};

    if (ei) { firstOk = (*ei == 42); }

    ei = to_int(text);

    secondOk = static_cast<bool>(ei);

    return firstOk and not secondOk;
}
} // namespace cbp
