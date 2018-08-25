#include <boost/regex.hpp>
#include <boost_function.hpp>
#include <string>

namespace cbp {
bool boost_function()
{
    const boost::regex pat{"^Subject: (Re: |Aw: )*(.*)"};
    const std::string  line{"Subject: Will Success Spoil Rock Hunter?"};
    boost::smatch      matches{};
    return boost::regex_match(line, matches, pat);
}
} // namespace cbp
