// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{			
	//SumFixedTraits类模板
	template<typename T>
	struct SumFixedTraits;

	template<>
	struct SumFixedTraits<char>
	{
		using sumT = int;
		static sumT initValue() { return 0; }
	};

	template<>
	struct SumFixedTraits<int>
	{
		using sumT = __int64;
		static sumT initValue() { return 0; }
	};

	template<>
	struct SumFixedTraits<double>
	{
		using sumT = double;
		static sumT initValue() { 

			return 0.0; 
		}
	};

	//---------------------------------
	template<typename T>
	struct MinFixedTraits;

	template<>
	struct MinFixedTraits<int>
	{
		using sumT = int; //求最小值，结果类型与元素类型相同即可，为名字统一，都用sumT这个名字
		static sumT initValue() { return INT_MAX; }  //这里给整型最大值，相信任何一个数组元素都不会比这个值更大，因此可以顺利找到数组元素中的最小值，见MinPolicy::algorithm。
	};


	//---------------------------------
	//求和策略类以实现求和算法
	template<typename sumT, typename T>
	struct SumPolicy
	{
		//静态成员函数模板
		//template<typename sumT, typename T>  //sumT是和值类型，T是数组元素类型
		static void algorithm(sumT& sum, const T& value) //该策略类的核心算法
		{
			sum += value;  //求和
		}
	};

	template<typename minT, typename T>
	struct MinPolicy
	{
		//template<typename minT, typename T>
		static void algorithm(minT& min, const T& value)
		{
			if (min > value)
				min = value;
		}
	};
	
	//---------------------------------
	template<typename T, typename U = SumFixedTraits<T>, 
		template<class, class> class V = SumPolicy //这里的class也可以写成typename
		//typename V = SumPolicy
	>
	auto funcsum(const T* begin, const T* end)
	{
		typename U::sumT sum = U::initValue();
		for (;;)
		{
			//sum += (*begin); 此行被下面一行取代
			//V::algorithm(sum, *begin);
			V<U::sumT,T>::algorithm(sum, *begin); //捋一下：T是数组成员类型，U是fixed traits，从中可以提取出计算的结果类型（U::sumT）以及结果的初值，V是策略类模板，用于实现具体算法（求和、求最小值等）
			if (begin == end)
				break;
			++begin;
		}
		return sum;
	}



}

int main()
{
	int myintarray1[] = { 10,15,20 };
	//cout << _nmsp1::funcsum<int, _nmsp1::SumFixedTraits<int>, _nmsp1::MinPolicy>(&myintarray1[0], &myintarray1[2]) << endl;
	cout << _nmsp1::funcsum<int, _nmsp1::MinFixedTraits<int>, _nmsp1::MinPolicy>(&myintarray1[0], &myintarray1[2]) << endl;


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
