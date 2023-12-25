// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	/*template <bool b, class T, class U>
	struct conditional 
	{
		using type = T;
	};

	template <class T, class U>
	struct conditional<false, T, U> 
	{
		using type = U;
	};*/


}


int main()
{	
	std::conditional<true, int, double>::type tmp1;
	std::conditional<false, int, double>::type tmp2;

	cout << "tmp1的类型为：" << typeid(decltype(tmp1)).name() << endl;
	cout << "tmp2的类型为：" << typeid(decltype(tmp2)).name() << endl;

	int i = 35;
	if (i > 100)
	{
		cout << "i > 100" << endl;
	}
	else
	{
		if (i > 80)
		{
			cout << "i > 80 并且 <= 100" << endl;
		}
		else
		{
			if (i > 40)
			{
				cout << "i > 40 并且 <= 80" << endl;
			}
			else
			{
				cout << "i <= 40" << endl;
			}
		}
	}

	constexpr int j = 35; 					   //假设给进去的是35
	std::conditional< (j > 100), double,      //值>100，tsvar是double类型
			std::conditional< (j > 80), float,   //值在80~100之间，tsvar是float类型
				std::conditional< (j > 40), int, //值在40~80之间，tsvar是int类型
				char                  		      //值不超过40，tsvar是char类型
			>::type
		>::type
	>::type tsvar;
	cout << "tsvar的类型为：" << typeid(decltype(tsvar)).name() << endl;

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
