// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <vector>
//#include <list>
//#include <functional>
//
using namespace std;
//#include <boost/type_index.hpp>
//
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	//constexpr int myfunc(int abc)
	int myfunc(int abc)
	{
		return abc * 2;
	}


}
namespace _nmsp2
{
	template<int x_v, int y_v>
	struct Calc
	{
		/*enum
		{
			addvalue = x_v + y_v,
			subvalue = x_v - y_v
		};*/

		static const int addvalue = x_v + y_v;	 //const可以用constexpr代替
	};

	void testfunc(const int& tmpvalue)
	{
		return;
	}

	//--------------------------------
	//计算n的阶乘的泛化版本
	template<int n_v>
	struct Factorial
	{
		enum { value = n_v * Factorial<n_v - 1>::value };
	};
	//计算n的阶乘的特化版本，用于做递归调用的出口
	template<>
	struct Factorial<1>
	{
		enum { value = 1 };
	};
}
namespace _nmsp3
{
	//constexpr int Factorial(int n_v)
	//{
	//	return n_v <= 1 ? 1 : (n_v * Factorial(n_v - 1));
	//}

	//---------------------------
	constexpr int Factorial(int n_v)
	{
		int result = 1;
		for (int i = 1; i <= n_v; ++i)
		{
			result *= i;
		}
		return result;
	}
}
namespace _nmsp4
{
	//变量模板（其实 result代表的是常量），看起来也象函数调用，也是元函数的一种形式
	////泛化版本
	//template<int Arg>
	//constexpr int result = Arg * result<Arg - 1>;

	////特化版本
	//template<>
	//constexpr int result<0> = 1;
	//--------------------
	//泛化版本
	template<int Arg>
	constexpr int result() { return  Arg * result<Arg - 1>(); };

	//特化版本
	template<>
	constexpr int result<0>() { return  1; };

	//--------------------
	//泛化版本
	template<int... FTArgs>
	constexpr int resultsum = 0;

	//特化版本
	template<int First, int... Others>
	constexpr int resultsum<First, Others...> = First + resultsum<Others...>;

	//---------------------
	template<int... FTArgs>
	constexpr int resultsum2()
	{
		return (... + FTArgs); //或者写成return (0 + ... + FTArgs);	
	}


}
namespace _nmsp5
{
	/*template<typename T>
	struct AddPoint
	{
		using type = T*;
	};*/

	//-------------------------
	template<typename T>
	using AddPoint = T*;

}

int main()
{	
	//constexpr int var = 11 * _nmsp1::myfunc(12);
	//static_assert(var == 264, "sth error");

	/*
	int var2 = 12;
	int var3 = _nmsp1::myfunc(var2);*/

	/*const int var3 = _nmsp2::Calc<12, 15>::addvalue;
	static_assert(var3 == 27, "sth error");
	std::cout << var3 << std::endl;*/

	//std::cout << _nmsp2::Calc<12, 15>::subvalue << std::endl;

	//_nmsp2::testfunc(_nmsp2::Calc<12, 15>::addvalue);

	/*
	cout << _nmsp2::Factorial<5>::value << endl;
	static_assert(_nmsp2::Factorial<5>::value == 120, "sth error");
	int tempvalue = _nmsp2::Factorial<5>::value;*/

	/*cout << _nmsp3::Factorial(5) << endl;
	static_assert(_nmsp3::Factorial(5) == 120, "sth error");
	int tempvalue = _nmsp3::Factorial(5);*/

	//cout << _nmsp4::result<5> << endl; //120
	//cout << _nmsp4::result<5>() << endl; //120

	/*
	cout << _nmsp4::resultsum<1, 10, 100> << endl;  //111
	cout << _nmsp4::resultsum2<1, 10, 100>() << endl;*/

	//_nmsp5::AddPoint<const char>::type s = "I Love China!";
	//printf("s的类型是：%s\n", typeid(decltype(s)).name());
	_nmsp5::AddPoint<const char> s = "I Love China!";
	printf("s的类型是：%s\n", typeid(decltype(s)).name());



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
