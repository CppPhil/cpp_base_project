#include "../include/philslib_function.hpp"
#include <pl/byte.hpp>        // pl::byte
#include <pl/zero_memory.hpp> // pl::zero_memory

namespace cbp {
namespace {
struct S {
  int a;
  float b;
};
} // anonymous namespace

bool philslib_function() 
{
  S s;
  pl::zero_memory(&s, sizeof(s));

  bool ret{true};

  for (const pl::byte* it{reinterpret_cast<const pl::byte*>(&s)},
       *end{it + sizeof(s)};
       it != end; ++it) {

    if (*it != static_cast<pl::byte>(0x00U)) {
      return false;
    }
  }

  return true;
}
} // namespace cbp
