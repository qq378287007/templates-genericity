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
	template <bool val>
	struct BoolConstant
	{
		using type = BoolConstant;  //写成using type = BoolConstant<val>;也行
		static constexpr bool value = val;
	};
	using TrueType = BoolConstant<true>;
	using FalseType = BoolConstant<false>;

	//-----------------------------
	template <typename T, bool val>
	struct AClass
	{
		AClass() //构造函数
		{
			cout << "AClass::AClass()执行了" << endl;
			/*if constexpr (val)
			{
				T tmpa = 15;
			}
			else
			{
				T tmpa = "abc";
			}*/

			AClassEx(BoolConstant<val>()); //创建一临时对象
		}

		void AClassEx(TrueType)
		{
			T tmpa = 15;
		}
		void AClassEx(FalseType)
		{
			T tmpa = "abc";
		}
	};

}



int main()
{	
	_nmsp1::AClass<int, true> tmpobj1;
	_nmsp1::AClass<string, false> tmpobj2;


	


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
