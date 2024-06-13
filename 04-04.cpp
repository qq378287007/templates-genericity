#include <iostream>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	template <bool b, class T, class U>
	struct conditional
	{
		using type = T;
	};

	template <class T, class U>
	struct conditional<false, T, U>
	{
		using type = U;
	};
}

int main()
{
	std::conditional<true, int, double>::type tmp1;
	ns1::conditional<false, int, double>::type tmp2;
	cout << "type of tmp1 = " << type_id_with_cvr<decltype(tmp1)>().pretty_name() << endl;
	cout << "type of tmp2 = " << type_id_with_cvr<decltype(tmp2)>().pretty_name() << endl;

	int i = 35;
	if (i > 100)
	{
		cout << "i > 100" << endl;
	}
	else
	{
		if (i > 80)
		{
			cout << "i > 80 and <= 100" << endl;
		}
		else
		{
			if (i > 40)
			{
				cout << "i > 40 and <= 80" << endl;
			}
			else
			{
				cout << "i <= 40" << endl;
			}
		}
	}

	constexpr int j = 35;											  // 假设给进去的是35
	std::conditional<(j > 100), double,								  // 值>100，tsvar是double类型
					 std::conditional<(j > 80), float,				  // 值在80~100之间，tsvar是float类型
									  std::conditional<(j > 40), int, // 值在40~80之间，tsvar是int类型
													   char			  // 值不超过40，tsvar是char类型
													   >::type>::type>::type tsvar;
	cout << "type of tsvar = " << type_id_with_cvr<decltype(tsvar)>().pretty_name() << endl;

	ns1::conditional<(j > 100), double, ns1::conditional<(j > 80), float, ns1::conditional<(j > 40), int, char>::type>::type>::type tsvar2;
	cout << "type of tsvar2 = " << type_id_with_cvr<decltype(tsvar2)>().pretty_name() << endl;

	cout << "Over!\n";
	return 0;
}
