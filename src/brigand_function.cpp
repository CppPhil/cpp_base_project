#include <brigand.hpp>
#include "../include/brigand_function.hpp"
#include <type_traits>

namespace cbp
{
bool brigand_function()
{
	using list = brigand::list<bool, int, char*>;
	using head = brigand::front<list>;

	return std::is_same<head, bool>::value;
}
} // namespace cbp

