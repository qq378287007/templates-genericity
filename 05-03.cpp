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
	};
	class B
	{
	public:
		B(int tmpval){};
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

	template <typename T>
	class IsDefConstructibleHelper
	{
	private:
		template <typename = decltype(T())>
		static std::true_type test(void *);

		template <typename = int> // 这行代码其实可以不要
		static std::false_type test(...);

	public:
		using type = decltype(test(nullptr));
	};

	template <typename T>
	class IsDefConstructible : public IsDefConstructibleHelper<T>::type
	{
	};

}

namespace ns2
{
	class A
	{
	};
	class B : public A
	{
	};

	template <typename FROM, typename TO>
	struct IsConvertibleHelper
	{
	private:
		static void testfunc(TO);

		template <typename = decltype(testfunc(std::declval<FROM>()))>
		static std::true_type test(void *);

		static std::false_type test(...);

	public:
		using type = decltype(test(nullptr));
	};

	template <typename FROM, typename TO>
	struct IsConvertible : IsConvertibleHelper<FROM, TO>::type // struct缺省的继承方式就是public继承
	{
	};

	template <typename FROM, typename TO>
	constexpr bool IsConvertible_v = IsConvertible<FROM, TO>::value;

}

namespace ns3
{
	class A
	{
	};
	class B : public A
	{
	};

	//--------------------------------
	// 泛化版本
	template <typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	// 特化版本
	template <typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};

	//--------------------------------
	template <typename T>
	class IsClass
	{
	private:
		template <typename U>
		static std::integral_constant<bool, !std::is_union<U>::value> test(int U::*);

		template <typename>
		static std::integral_constant<bool, false> test(...);

	public:
		static constexpr bool value = IsSameType<decltype(test<T>(nullptr)), std::integral_constant<bool, true>>::value;
	};

}

namespace ns4
{
	class A
	{
	};
	class B : public A
	{
	};

	//--------------------------------
	// 泛化版本
	template <typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	// 特化版本
	template <typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};

	// template<typename Base, typename Derived>
	// struct is_base_of { ...... };

	//-------------------------------
	template <typename Base, typename Derived> //<父,子>
	class IsBaseOf
	{
	private:
		template <typename T>
		static std::true_type test(T *);

		template <typename>
		static std::false_type test(void *);

		template <typename B, typename D>										   //<父,子>
		static auto test_middle() -> decltype(test<B>(static_cast<D *>(nullptr))); // 调用test()

	public:
		static constexpr bool value = IsSameType<
			std::integral_constant<
				bool,
				std::is_class_v<Base> &&
					std::is_class_v<Derived> &&decltype(test_middle<Base, Derived>())::value>,
			std::integral_constant<bool, true>>::value;
	};

	class PAR
	{
	}; // 父类
	class SON : public PAR
	{
	}; // PAR的子类
	class OTHER
	{
	}; // 其他类
	void f(PAR *) {}
	void f(void *) {}
}

namespace ns5
{
	class A
	{
	};
	class B
	{
	public:
		B(int tmpval){};
	};

	//-------------------------
	// 泛化版本
	template <typename T, typename U = std::void_t<>>
	class IsDefConstructible : public std::false_type
	{
	};
	// 特化版本
	template <typename T>
	class IsDefConstructible<T, std::void_t<decltype(T())>> : public std::true_type
	{
	};
}

int main()
{
	/*ns1::A aobj;
	//ns1::B bobj;
	ns1::B bobj(1);

	cout << std::is_default_constructible<int>::value << endl;
	cout << std::is_default_constructible<double>::value << endl;
	cout << std::is_default_constructible<ns1::A>::value << endl;
	cout << std::is_default_constructible<ns1::B>::value << endl;
	*/

	/*
	cout << ns1::IsDefConstructible<int>::value << endl;
	cout << ns1::IsDefConstructible<double>::value << endl;
	cout << ns1::IsDefConstructible<ns1::A>::value << endl;
	cout << ns1::IsDefConstructible<ns1::B>::value << endl;*/

	/*cout << std::is_convertible<float, int>::value << endl;
	cout << std::is_convertible<int, float>::value << endl;
	cout << std::is_convertible<ns2::A, ns2::B>::value << endl;
	cout << std::is_convertible<ns2::B, ns2::A>::value << endl;*/

	/*
	cout << ns2::IsConvertible<float, int>::value << endl;
	cout << ns2::IsConvertible<int, float>::value << endl;
	cout << ns2::IsConvertible<ns2::A, ns2::B>::value << endl;
	cout << ns2::IsConvertible<ns2::B, ns2::A>::value << endl;

	cout << ns2::IsConvertible_v<float, int> << endl;
	cout << ns2::IsConvertible_v<int, float> << endl;
	cout << ns2::IsConvertible_v<ns2::A, ns2::B> << endl;
	cout << ns2::IsConvertible_v<ns2::B, ns2::A> << endl;*/

	/*
	cout << ns3::IsClass<ns3::A>::value << endl;
	cout << ns3::IsClass<ns3::B>::value << endl;
	cout << ns3::IsClass<int>::value << endl;*/

	/*
	cout << std::is_base_of<ns4::A, ns4::A>::value << endl;
	cout << std::is_base_of<ns4::B, ns4::A>::value << endl;
	cout << std::is_base_of<ns4::A, ns4::B>::value << endl;

	cout << std::is_base_of_v<ns4::A, ns4::A> << endl;
	cout << std::is_base_of_v<ns4::B, ns4::A> << endl;
	cout << std::is_base_of_v<ns4::A, ns4::B> << endl;*/

	/*
	cout << ns4::IsBaseOf<ns4::A, ns4::A>::value << endl;
	cout << ns4::IsBaseOf<ns4::B, ns4::A>::value << endl;
	cout << ns4::IsBaseOf<ns4::A, ns4::B>::value << endl;

	ns4::f(static_cast<ns4::PAR*>(nullptr)); //没问题
	ns4::f(static_cast<ns4::SON*>(nullptr)); //没问题，因为SON是PAR的子类
	ns4::f(static_cast<ns4::OTHER*>(nullptr)); //编译报错*/

	cout << ns5::IsDefConstructible<ns5::A>::value << endl;
	cout << ns5::IsDefConstructible<ns5::B>::value << endl;

	cout << "Over!\n";
	return 0;
}
