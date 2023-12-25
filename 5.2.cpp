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
	class A
	{
	public:
		A(int v1, int v2) :m_i(v1 + v2) {} //构造函数
		int m_i; //成员变量

	public:
		A& operator +=(const A& obj)
		{
			m_i += obj.m_i;
			return *this;
		};

	};

	//-----------------------
	template<typename T>
	struct SumFixedTraits;

	template<>
	struct SumFixedTraits<char>
	{
		using sumT = int;
		//static const sumT initValue = 0;
		static sumT initValue() { return 0; }
	};

	template<>
	struct SumFixedTraits<int> 
	{
		using sumT = __int64;
		//static const sumT initValue = 0;
		static sumT initValue() { return 0; }
	};

	template<>
	struct SumFixedTraits<double>
	{
		using sumT = double;
		//static const sumT initValue = 0.0;
		//static constexpr sumT initValue = 0.0;
		static sumT initValue() { return 0.0; }
	};

	template<>
	struct SumFixedTraits<A>
	{
		using sumT = A;
		//static const sumT initValue{ 0,0 };
		//static const sumT initValue; //这是声明，不是定义
		//inline static const sumT initValue{ 0,0 };
		static sumT initValue()
		{
			return sumT{ 0,0 };
		}

	};
	//A const SumFixedTraits<A>::initValue = A{ 0,0 }; //定义并初始化

	//---------------------------------------------------
	template<typename T>
	auto funcsum(const T* begin, const T* end)
	{		
		using sumT = typename SumFixedTraits<T>::sumT;  //给进来一个类型(T)，返回一个类型(sumT)，这是fixed traits的运用		
		//sumT sum{};
		//sumT sum = SumFixedTraits<T>::initValue; //给进来一个类型(T)，返回一个值，这是value traits的运用
		sumT sum = SumFixedTraits<T>::initValue();

		for (;;)
		{
			sum += (*begin);
			if (begin == end)
				break;
			++begin;
		}
		return sum;
	}

	

}
namespace _nmsp2
{
	template <typename T>
	struct voidValueTraits
	{
		static const bool value = false;
	};

	template<>  //特化版本
	struct voidValueTraits<void>
	{
		static const bool value = true;
	};

}
namespace _nmsp3
{
	//泛化版本
	template<typename T1, typename T2>
	struct IsSameType : std::false_type
	{
		//static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1, T1>: std::true_type
	{
		//static const bool value = true;
	};

	template<typename T1, typename T2>
	const bool IsSame_v = IsSameType<T1, T2>::value;

}

int main()
{
	
	/*
	int myintarray1[] = { 10,15,20 };
	int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	char mychararray[] = "abc";  //97,98,99

	cout << _nmsp1::funcsum(&myintarray1[0], &myintarray1[2]) << endl;
	cout << _nmsp1::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
	cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl;

	double mydblarray1[] = { 12.8,15.8,20.6 };
	cout << _nmsp1::funcsum(&mydblarray1[0], &mydblarray1[2]) << endl;

	_nmsp1::A myaobjarray1[] = { _nmsp1::A{2,3},_nmsp1::A{6,8},_nmsp1::A{11,12} };
	cout << funcsum(&myaobjarray1[0], &myaobjarray1[2]).m_i << endl;*/

	//--------------------
	/*cout << "int是void类型吗?" << std::is_void<int>::value << endl;  //0
	cout << "void是void类型吗?" << std::is_void<void>::value << endl;  //1

	cout << "int是否void类型吗?" << _nmsp2::voidValueTraits<int>::value << endl;  //0
	cout << "void是void类型吗?" << _nmsp2::voidValueTraits<void>::value << endl;  //1*/

	//--------------------
	//cout << _nmsp3::IsSameType<int, const int>::value << endl;
	//cout << _nmsp3::IsSameType<int, int>::value << endl;
	cout << _nmsp3::IsSame_v<int, const int> << endl;
	cout << _nmsp3::IsSame_v<int, int> << endl;



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
