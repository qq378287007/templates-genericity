#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	struct A
	{
	};
	union B
	{
		int num;
		char type;
	};
}
namespace ns2
{
	template <typename T, T v>
	struct integral_constant
	{
		static constexpr T value = v;
		using value_type = T;
		using type = integral_constant;
		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept { return value; }
	};
}

int main()
{
	using namespace ns1;

	cout << is_union<A>::value << endl;
	cout << is_union<B>::value << endl;

	cout << is_union_v<A> << endl;
	cout << is_union_v<B> << endl;

	cout << is_class<A>::value << endl;
	cout << is_class<B>::value << endl;

	cout << is_class_v<A> << endl;
	cout << is_class_v<B> << endl;

	cout << integral_constant<int, 15>::value << endl;
	cout << integral_constant<bool, true>::value << endl;

	ns2::integral_constant<bool, !is_union<B>::value> myobj1;
	cout << myobj1.value << endl;

	std::integral_constant<bool, !is_union<A>::value> myobj2;
	cout << myobj2.value << endl;

	cout << "Over!\n";
	return 0;
}
