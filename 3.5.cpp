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
	template<typename... Args>
	class myclasst
	{
	public:
		myclasst()
		{
			cout << "myclasst::myclasst()执行了，可变参个数=" << sizeof...(Args) << endl;
		}
	};

	template<typename... Args>
	//class myclasst2 : public myclasst<Args...>
	//class myclasst2 : public myclasst <Args>...
	//class myclasst2 : public myclasst <Args,char>...
	class myclasst2 : public myclasst <Args, Args...>...
	{
	public:
		myclasst2()
		{
			cout << "myclasst2::myclasst2()执行了，可变参个数=" << sizeof...(Args) << endl;
		}
	};

}

int main()
{	
	_nmsp1::myclasst2<double, float, int> tmpobj;


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