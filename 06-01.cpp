#include <iostream>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

namespace ns1
{
	constexpr int myfunc(int abc)
	{
		return abc * 2;
	}

	int myfunc2(int abc)
	{
		return abc * 2;
	}
}

namespace ns2
{
	template <int x_v, int y_v>
	struct Calc
	{
		static const int addvalue = x_v + y_v; // const可以用constexpr代替
	};

	template <int x_v, int y_v>
	struct Calc2
	{
		enum
		{
			addvalue = x_v + y_v,
			subvalue = x_v - y_v
		};
	};

	void testfunc(const int &tmpvalue) {}

	// 计算n的阶乘的泛化版本
	template <int n_v>
	struct Factorial
	{
		enum
		{
			value = n_v * Factorial<n_v - 1>::value
		};
	};
	// 计算n的阶乘的特化版本，用于做递归调用的出口
	template <>
	struct Factorial<1>
	{
		enum
		{
			value = 1
		};
	};
}

namespace ns3
{
	constexpr int Factorial(int n_v)
	{
		int result = 1;
		for (int i = 1; i <= n_v; ++i)
			result *= i;
		return result;
	}

	constexpr int Factorial2(int n_v)
	{
		return n_v <= 1 ? 1 : (n_v * Factorial2(n_v - 1));
	}
}

namespace ns4
{
	// 变量模板（其实 result代表的是常量），看起来也象函数调用，也是元函数的一种形式
	// 泛化版本
	template <int Arg>
	constexpr int result = Arg * result<Arg - 1>;

	// 特化版本
	template <>
	constexpr int result<0> = 1;

	// 泛化版本
	template <int Arg>
	constexpr int result2() { return Arg * result2<Arg - 1>(); };

	// 特化版本
	template <>
	constexpr int result2<0>() { return 1; };

	// 泛化版本
	template <int... FTArgs>
	constexpr int resultsum = 0;

	// 特化版本
	template <int First, int... Others>
	constexpr int resultsum<First, Others...> = First + resultsum<Others...>;

	template <int... FTArgs>
	constexpr int resultsum2()
	{
		return (... + FTArgs); // 或者写成return (0 + ... + FTArgs);
	}
}

namespace ns5
{
	template <typename T>
	struct AddPoint
	{
		using type = T *;
	};

	template <typename T>
	using AddPoint2 = T *;
}

int main()
{
#if 0
	using namespace ns1;
	constexpr int var = 11 * myfunc(12);
	static_assert(var == 264, "sth error");//static_assert，静态断言，编译期间断言，用于判断var是否编译期间求值

	int var2 = 12;
	int var3 = myfunc2(var2);
	int var4 = myfunc(var2);//运行时被调用
#endif

#if 0
	using namespace ns2;
	const int var3 = Calc<12, 15>::addvalue;
	static_assert(var3 == 27, "sth error");
	cout << var3 << endl;

	cout << Calc2<12, 15>::subvalue << endl;

	// testfunc(Calc<12, 15>::addvalue);//error
	testfunc(Calc2<12, 15>::addvalue);

	const int tempvalue = Factorial<5>::value;
	cout << tempvalue << endl;
	static_assert(tempvalue == 120, "sth error");
#endif

#if 0
	using namespace ns3;
	const int tempvalue = Factorial(5);
	static_assert(tempvalue == 120, "sth error");
	cout << Factorial2(5) << endl;
#endif

#if 0
	using namespace ns4;
	cout << result<5> << endl;	  // 120
	cout << result2<5>() << endl; // 120

	cout << resultsum<1, 10, 100> << endl;	  // 111
	cout << resultsum2<1, 10, 100>() << endl; // 111
#endif

#if 1
	using namespace ns5;
	AddPoint<const char>::type s = "I Love China!"; // const char *
	cout << "type(s): " << type_id_with_cvr<decltype(s)>().pretty_name() << endl;
	AddPoint2<const char> s2 = "I Love China!"; // const char *
	cout << "type(s2): " << type_id_with_cvr<decltype(s2)>().pretty_name() << endl;
#endif

	cout << "Over!\n";
	return 0;
}
