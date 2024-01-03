// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{
	struct A {};
	union B
	{
		int  num;
		char type;
	};


}
namespace _nmsp2
{
	/*template <typename T, T value>
	struct integral_constant
	{
		static constexpr T value = value;
		using value_type = T;
		using type = integral_constant;
		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept { return value; }
	};*/


}

int main()
{
	/*cout << std::is_union<_nmsp1::A>::value << endl;
	cout << std::is_union<_nmsp1::B>::value << endl;

	cout << std::is_union_v<_nmsp1::A> << endl;
	cout << std::is_union_v<_nmsp1::B> << endl;

	cout << std::is_class<_nmsp1::A>::value << endl;
	cout << std::is_class<_nmsp1::B>::value << endl;

	cout << std::is_class_v<_nmsp1::A> << endl;
	cout << std::is_class_v<_nmsp1::B> << endl;

	cout << std::integral_constant<int, 15>::value << endl;
	cout << std::integral_constant<bool, true>::value << endl;*/

	std::integral_constant<bool, !std::is_union<_nmsp1::B>::value> myobj1;
	cout << myobj1.value << endl;

	std::integral_constant<bool, !std::is_union<_nmsp1::A>::value> myobj2;
	cout << myobj2.value << endl;

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
