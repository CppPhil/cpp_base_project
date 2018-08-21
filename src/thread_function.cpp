#include "../include/thread_function.hpp"
#include <future>
#include <string>

namespace cbp {
namespace {
std::string thread_impl_function(int i) { return "text: " + std::to_string(i); }
} // anonymous namespace

bool thread_function()
{
    std::future<std::string> future{
        std::async(std::launch::async, &thread_impl_function, 5)};

    return future.get() == "text: 5";
}
} // namespace cbp
