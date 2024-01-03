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
	template<typename T, int U> //T：元素类型，U：数组大小
	inline auto DotProduct(T* array1, T* array2)
	{
		T dpresult = T{}; //零初始化
		for (int i = 0; i < U; ++i)
		{
			dpresult += array1[i] * array2[i];
		}
		return dpresult;
	}


}
namespace _nmsp2
{
	//泛化版本
	template<typename T, int U> //T：元素类型，U：数组大小
	struct DotProduct
	{
		static T result(const T* a, const T* b)
		{
			return (*a) * (*b) + DotProduct<T, U - 1>::result(a + 1, b + 1);
		}
	};

	//特化版本，用于做递归调用的出口
	template<typename T>
	struct DotProduct<T, 0>
	{
		static T result(const T*, const T*)
		{
			return T{};
		}
	};

}
namespace _nmsp3
{
	/*
	//泛化版本
	template<int x_v, int y_v>
	struct InstantiationObServe
	{
		static const int value = (x_v > y_v) ? InstantiationObServe<x_v - 1, y_v>::value : InstantiationObServe<x_v, x_v>::value; //int可以用auto代替，书写更方便
	};*/

	/*
	//泛化版本
	template<int x_v, int y_v>
	struct InstantiationObServe
	{
		using TmpType = typename std::conditional < (x_v > y_v), InstantiationObServe<x_v - 1, y_v>,
			InstantiationObServe<x_v, x_v>
		>::type;
		static const int value =  TmpType::value;
	};
	//特化版本
	template<int x_v>
	struct InstantiationObServe<x_v, x_v>
	{
		static const int value = x_v; //int可以用auto代替，书写更方便
	};*/

	//泛化版本
	template<int x_v, int y_v>
	struct InstantiationObServe
	{
		using TmpType = typename std::conditional < (x_v > y_v), InstantiationObServe<x_v - 1, y_v>,
			InstantiationObServe<x_v, x_v>
		>::type;
		//enum { value = TmpType::value };
		static inline const int value = TmpType::value;

	};
	//特化版本
	template<int x_v>
	struct InstantiationObServe<x_v, x_v>
	{
		//enum { value = x_v };
		static inline const int value = x_v;
	};

	//----------------------
	struct TST
	{
		static const int mystatic = 1;
		//static inline double mystatic2 = 12.6;
		static constexpr double mystatic2 = 12.6;
	};
	

}

int main()
{	
	/*
	int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int result = _nmsp1::DotProduct<int, 3>(a, b);
	cout << result << endl;*/

	/*int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int result = _nmsp2::DotProduct<int, 3>::result(a, b);
	cout << result << endl;*/

	/*
	int a[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int b[] = { 4,5,6,7,8,9,1,2,3,10,11,12 };
	int result = _nmsp2::DotProduct<int, 12>::result(a, b);
	cout << result << endl;

	int result2 = _nmsp2::DotProduct<int, 12>::result(a, b);*/

	cout << _nmsp3::InstantiationObServe<6, 4>::value << endl;


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
