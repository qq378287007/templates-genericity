#include <iostream>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	template <bool val>
	struct BoolConstant
	{
		using type = BoolConstant; // 写成using type = BoolConstant<val>;也行
		static constexpr bool value = val;
	};
	using TrueType = BoolConstant<true>;
	using FalseType = BoolConstant<false>;

	//-----------------------------
	template <typename T, bool val>
	struct AClass
	{
		AClass()
		{
			cout << "AClass::AClass()" << endl;
			/*if constexpr (val)
			{
				T tmpa = 15;
			}
			else
			{
				T tmpa = "abc";
			}*/

			AClassEx(BoolConstant<val>()); // 创建一临时对象
		}

		void AClassEx(TrueType) { T tmpa = 15; }
		void AClassEx(FalseType) { T tmpa = "abc"; }
	};
}

int main()
{
	ns1::AClass<int, true> tmpobj1;
	ns1::AClass<string, false> tmpobj2;

	cout << "Over!\n";
	return 0;
}
