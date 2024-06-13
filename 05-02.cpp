#include <iostream>
#include <vector>
#include <list>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	class A
	{
	public:
		A(int v1, int v2) : m_i(v1 + v2) {} // 构造函数
		int m_i;							// 成员变量

	public:
		A &operator+=(const A &obj)
		{
			m_i += obj.m_i;
			return *this;
		};
	};

	//-----------------------
	template <typename T>
	struct SumFixedTraits;

	template <>
	struct SumFixedTraits<char>
	{
		using sumT = int;
		// static const sumT initValue = 0;
		static sumT initValue() { return 0; }
	};

	template <>
	struct SumFixedTraits<int>
	{
		using sumT = __int64;
		// static const sumT initValue = 0;
		static sumT initValue() { return 0; }
	};

	template <>
	struct SumFixedTraits<double>
	{
		using sumT = double;
		// static const sumT initValue = 0.0;
		// static constexpr sumT initValue = 0.0;
		static sumT initValue() { return 0.0; }
	};

	template <>
	struct SumFixedTraits<A>
	{
		using sumT = A;
		// static const sumT initValue{ 0,0 };
		// static const sumT initValue; //这是声明，不是定义
		// inline static const sumT initValue{ 0,0 };
		static sumT initValue()
		{
			return sumT{0, 0};
		}
	};
	// A const SumFixedTraits<A>::initValue = A{ 0,0 }; //定义并初始化

	//---------------------------------------------------
	template <typename T>
	auto funcsum(const T *begin, const T *end)
	{
		using sumT = typename SumFixedTraits<T>::sumT; // 给进来一个类型(T)，返回一个类型(sumT)，这是fixed traits的运用
		// sumT sum{};
		// sumT sum = SumFixedTraits<T>::initValue; //给进来一个类型(T)，返回一个值，这是value traits的运用
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

namespace ns2
{
	template <typename T>
	struct voidValueTraits
	{
		static const bool value = false;
	};

	template <> // 特化版本
	struct voidValueTraits<void>
	{
		static const bool value = true;
	};

}

namespace ns3
{
	// 泛化版本
	template <typename T1, typename T2>
	struct IsSameType : std::false_type
	{
		// static const bool value = false;
	};

	// 特化版本
	template <typename T1>
	struct IsSameType<T1, T1> : std::true_type
	{
		// static const bool value = true;
	};

	template <typename T1, typename T2>
	const bool IsSame_v = IsSameType<T1, T2>::value;

}

int main()
{
	/*
	int myintarray1[] = { 10,15,20 };
	int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	char mychararray[] = "abc";  //97,98,99

	cout << ns1::funcsum(&myintarray1[0], &myintarray1[2]) << endl;
	cout << ns1::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
	cout << (int)(ns1::funcsum(&mychararray[0], &mychararray[2])) << endl;

	double mydblarray1[] = { 12.8,15.8,20.6 };
	cout << ns1::funcsum(&mydblarray1[0], &mydblarray1[2]) << endl;

	ns1::A myaobjarray1[] = { ns1::A{2,3},ns1::A{6,8},ns1::A{11,12} };
	cout << funcsum(&myaobjarray1[0], &myaobjarray1[2]).m_i << endl;*/

	//--------------------
	/*cout << "int是void类型吗?" << std::is_void<int>::value << endl;  //0
	cout << "void是void类型吗?" << std::is_void<void>::value << endl;  //1

	cout << "int是否void类型吗?" << ns2::voidValueTraits<int>::value << endl;  //0
	cout << "void是void类型吗?" << ns2::voidValueTraits<void>::value << endl;  //1*/

	//--------------------
	// cout << ns3::IsSameType<int, const int>::value << endl;
	// cout << ns3::IsSameType<int, int>::value << endl;
	cout << ns3::IsSame_v<int, const int> << endl;
	cout << ns3::IsSame_v<int, int> << endl;

	cout << "Over!\n";
	return 0;
}
