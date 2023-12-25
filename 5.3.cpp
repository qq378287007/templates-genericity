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
	class A {};
	class B
	{
	public:
		B(int tmpval) {};
	}; 

	/*
	//--------------------------------
	//泛化版本
	template<typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};
	//---------------------------------
	template<typename T>
	class IsDefConstructible
	{
	private:
		template<typename = decltype(T())>
		static std::true_type test(void*);

		template<typename = int>
		static std::false_type test(...);
	public:
		static constexpr bool value = IsSameType< decltype(test(nullptr)), std::true_type >::value;
	};
	*/
	
	template<typename T>
	class IsDefConstructibleHelper
	{
	private:
		template<typename = decltype(T())>
		static std::true_type test(void*);

		template<typename = int> //这行代码其实可以不要
		static std::false_type test(...);
	public:
		using type = decltype(test(nullptr));
	};

	template<typename T>
	class IsDefConstructible : public IsDefConstructibleHelper<T>::type
	{
	};


}
namespace _nmsp2
{
	class A {};
	class B : public A
	{
	};

	template<typename FROM, typename TO>
	struct IsConvertibleHelper
	{
	private:
		static void testfunc(TO);

		template<typename = decltype(testfunc(std::declval<FROM>()))>
		static std::true_type test(void*);

		static std::false_type test(...);
	public:
		using type = decltype(test(nullptr));
	};

	template<typename FROM, typename TO>
	struct IsConvertible : IsConvertibleHelper<FROM, TO>::type //struct缺省的继承方式就是public继承
	{
	};

	template<typename FROM, typename TO>
	constexpr bool IsConvertible_v = IsConvertible<FROM, TO>::value;

}
namespace _nmsp3
{
	class A {};
	class B : public A
	{
	};

	//--------------------------------
	//泛化版本
	template<typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};

	//--------------------------------
	template<typename T>
	class IsClass
	{
	private:
		template<typename U>
		static std::integral_constant<bool, !std::is_union<U>::value> test(int U::*);

		template<typename>
		static std::integral_constant<bool, false> test(...);

	public:
		static constexpr bool value = IsSameType<decltype(test<T>(nullptr)), std::integral_constant<bool, true>>::value;
	};

}
namespace _nmsp4
{
	class A {};
	class B : public A
	{
	};
	
	//--------------------------------
	//泛化版本
	template<typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};

	//template<typename Base, typename Derived>
	//struct is_base_of { ...... };

	//-------------------------------
	template<typename Base, typename Derived> //<父,子>
	class IsBaseOf
	{
	private:
		template<typename T>
		static std::true_type  test(T*);

		template<typename>
		static std::false_type test(void*);

		template <typename B, typename D> //<父,子>
		static auto test_middle() ->decltype(test<B>(static_cast<D*>(nullptr))); //调用test()

	public:
		static constexpr bool value = IsSameType<
			std::integral_constant<
			bool,
			std::is_class_v<Base> &&
			std::is_class_v<Derived> &&
			decltype(test_middle<Base, Derived>())::value
			>
			, std::integral_constant<bool, true>>::value;
	};

	class PAR {}; //父类
	class SON :public PAR {}; //PAR的子类
	class OTHER {};  //其他类
	void f(PAR*) {}
	void f(void*) {}
}
namespace _nmsp5
{
	class A {};
	class B
	{
	public:
		B(int tmpval) {};
	};

	//-------------------------
	//泛化版本
	template<typename T, typename U = std::void_t<> >
	class IsDefConstructible : public std::false_type
	{
	};
	//特化版本
	template<typename T>
	class IsDefConstructible<T, std::void_t<decltype(T())> > :public  std::true_type
	{
	};
}


int main()
{
	/*_nmsp1::A aobj;
	//_nmsp1::B bobj;
	_nmsp1::B bobj(1);

	cout << std::is_default_constructible<int>::value << endl;
	cout << std::is_default_constructible<double>::value << endl;
	cout << std::is_default_constructible<_nmsp1::A>::value << endl;
	cout << std::is_default_constructible<_nmsp1::B>::value << endl;
	*/

	/*
	cout << _nmsp1::IsDefConstructible<int>::value << endl;
	cout << _nmsp1::IsDefConstructible<double>::value << endl;
	cout << _nmsp1::IsDefConstructible<_nmsp1::A>::value << endl;
	cout << _nmsp1::IsDefConstructible<_nmsp1::B>::value << endl;*/

	/*cout << std::is_convertible<float, int>::value << endl;
	cout << std::is_convertible<int, float>::value << endl;
	cout << std::is_convertible<_nmsp2::A, _nmsp2::B>::value << endl;
	cout << std::is_convertible<_nmsp2::B, _nmsp2::A>::value << endl;*/

	/*
	cout << _nmsp2::IsConvertible<float, int>::value << endl;
	cout << _nmsp2::IsConvertible<int, float>::value << endl;
	cout << _nmsp2::IsConvertible<_nmsp2::A, _nmsp2::B>::value << endl;
	cout << _nmsp2::IsConvertible<_nmsp2::B, _nmsp2::A>::value << endl;

	cout << _nmsp2::IsConvertible_v<float, int> << endl;
	cout << _nmsp2::IsConvertible_v<int, float> << endl;
	cout << _nmsp2::IsConvertible_v<_nmsp2::A, _nmsp2::B> << endl;
	cout << _nmsp2::IsConvertible_v<_nmsp2::B, _nmsp2::A> << endl;*/

	/*
	cout << _nmsp3::IsClass<_nmsp3::A>::value << endl;
	cout << _nmsp3::IsClass<_nmsp3::B>::value << endl;
	cout << _nmsp3::IsClass<int>::value << endl;*/

	/*
	cout << std::is_base_of<_nmsp4::A, _nmsp4::A>::value << endl;
	cout << std::is_base_of<_nmsp4::B, _nmsp4::A>::value << endl;
	cout << std::is_base_of<_nmsp4::A, _nmsp4::B>::value << endl;

	cout << std::is_base_of_v<_nmsp4::A, _nmsp4::A> << endl;
	cout << std::is_base_of_v<_nmsp4::B, _nmsp4::A> << endl;
	cout << std::is_base_of_v<_nmsp4::A, _nmsp4::B> << endl;*/

	/*
	cout << _nmsp4::IsBaseOf<_nmsp4::A, _nmsp4::A>::value << endl;
	cout << _nmsp4::IsBaseOf<_nmsp4::B, _nmsp4::A>::value << endl;
	cout << _nmsp4::IsBaseOf<_nmsp4::A, _nmsp4::B>::value << endl;

	_nmsp4::f(static_cast<_nmsp4::PAR*>(nullptr)); //没问题
	_nmsp4::f(static_cast<_nmsp4::SON*>(nullptr)); //没问题，因为SON是PAR的子类
	_nmsp4::f(static_cast<_nmsp4::OTHER*>(nullptr)); //编译报错*/


	cout << _nmsp5::IsDefConstructible<_nmsp5::A>::value << endl;
	cout << _nmsp5::IsDefConstructible<_nmsp5::B>::value << endl;

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
