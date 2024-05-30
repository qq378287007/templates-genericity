#include <iostream>
// #include <vector>
// #include <list>
// #include <functional>
using namespace std;

// #include <boost/type_index.hpp>

// #pragma warning(disable : 4996)

namespace tplt
{
	// 所有的typelist设计代码都放入这里
	template <typename... T> // T代表typelist中装的一包类型（typelist中装的一系列元素）
	class typelist
	{
	};

	// 泛化版本，用不到，所以只需声明即可，存在的目的是引出特化版本
	template <typename TPLT> // TPLT代表整个typelist<...>类型
	class front;

	// 特化版本，写特化版本时，先书写front后面尖括号中内容（这个内容，必须遵从泛化版本中template中的内容来书写），回头再根据尖括号中用到的内容来填补template中内容
	template <typename FirstElem, typename... OtherElem> // FirstElem代表typelist中的第一个元素（类型），OtherElem代表typelist中其他元素
	class front<typelist<FirstElem, OtherElem...>>
	{
	public:
		using type = FirstElem;
	};

	// 泛化版本
	template <typename TPLT>
	class size;

	// 特化版本
	template <typename... Args>
	class size<typelist<Args...>>
	{
	public:
		static inline size_t value = sizeof...(Args);
	};

	// 泛化版本
	template <typename TPLT>
	class pop_front;

	// 特化版本
	template <typename FirstElem, typename... OtherElem>
	class pop_front<typelist<FirstElem, OtherElem...>>
	{
	public:
		using type = typelist<OtherElem...>;
	};

	// 向开头插入元素：泛化版本
	template <typename TPLT, typename NewElem> // TPLT代表整个typelist<...>类型，NewElem代表要插入的新元素
	class push_front;

	// 向开头插入元素：特化版本
	template <typename... Elems, typename NewElem>
	class push_front<typelist<Elems...>, NewElem>
	{
	public:
		using type = typelist<NewElem, Elems...>;
	};

	// 向结尾插入元素：泛化版本
	template <typename TPLT, typename NewElem>
	class push_back;

	// 向结尾插入元素：特化版本
	template <typename... Elems, typename NewElem>
	class push_back<typelist<Elems...>, NewElem>
	{
	public:
		using type = typelist<Elems..., NewElem>;
	};

	// 泛化版本
	template <typename TPLT, typename NewElem>
	class replace_front;

	// 特化版本
	template <typename FirstElem, typename... OtherElem, typename NewElem>
	class replace_front<typelist<FirstElem, OtherElem...>, NewElem>
	{
	public:
		using type = typelist<NewElem, OtherElem...>;
	};

	// 泛化版本
	template <typename TPLT>
	class is_empty
	{
	public:
		static inline const bool value = false;
	};

	// 特化版本
	template <>
	class is_empty<typelist<>>
	{
	public:
		static inline const bool value = true;
	};

	// 泛化版本
	template <typename TPLT, unsigned int index_v>
	class find : public find<typename pop_front<TPLT>::type, index_v - 1>
	{
	};

	// 特化版本
	template <typename TPLT>
	class find<TPLT, 0> : public front<TPLT> // 0，作为递归的出口了
	{
	};

	// 泛化版本
	template <typename TPLT>
	class get_maxsize_type
	{
	private:
		// 当前get_maxsize_type中typelist（模板参数）的第一个元素
		using tl_first_elem = typename front<TPLT>::type; // 获取typelist中第一个元素(是一个类型)，比如获取到的是int
		using tl_remain = typename pop_front<TPLT>::type;
		// 递归下去的get_maxsize_type中typelist（模板参数）的第一个元素（sizeof值最大的元素）
		using tl_first_elem_rec = typename get_maxsize_type<tl_remain>::type;

	public:
		using type = typename std::conditional<sizeof(tl_first_elem) >= sizeof(tl_first_elem_rec), tl_first_elem, tl_first_elem_rec>::type;
	};
	// 特化版本
	template <>
	class get_maxsize_type<typelist<>>
	{
	public:
		using type = char;
	};

	// 泛化版本
	template <typename TPLT, bool = is_empty<TPLT>::value>
	class reverse;

	// 特化版本1, 当typelist中还有元素时
	template <typename TPLT>
	class reverse<TPLT, false>
	{
	private:
		using tl_first_elem = typename front<TPLT>::type; // 获取typelist中第一个元素(是一个类型)，比如获取到的是int
		// 促使递归的using，递归结束后，tl_result_rec负责配合type来整理最终的结果
		using tl_result_rec = typename reverse<typename pop_front<TPLT>::type>::type;

	public:
		using type = typename push_back<tl_result_rec, tl_first_elem>::type;
	};

	// 特化版本2,当typelist中没有元素（空）时
	template <typename TPLT>
	class reverse<TPLT, true>
	{
	public:
	//	using type = typename TPLT; // 其实此时的TPLT就是typelist<>
	};
}

using TPL_NM1 = tplt::typelist<int, double, float, char, bool>;
using TPL_NM2 = tplt::typelist<>; // 没有元素的typelist容器

namespace tplt2
{
	class NullTypelist
	{
	}; // 空Typelist就用这个class表达
	template <typename T, typename U = NullTypelist>
	class Typelist // 类模板名字首字母大写以示与前面typelist的区别
	{
	public:
		using Head = T;
		using Tail = U;
	};

	//---------------------------
	template <typename TPLT>
	class front
	{
	public:
		using type = typename TPLT::Head;
	};

	//---------------------------
	// 泛化版本
	template <typename TPLT>
	class size;

	// 特化版本1
	template <>
	class size<NullTypelist>
	{
	public:
		static inline size_t value = 0;
	};

	// 特化版本2
	template <typename T, typename U>
	class size<Typelist<T, U>>
	{
	public:
		static inline size_t value = size<U>::value + 1; // 递归调用
	};

	//-----------------------------
	template <typename TPLT>
	class pop_front
	{
	public:
		using type = typename TPLT::Tail;
	};

	//-----------------------------
	template <typename TPLT, typename NewElem>
	class push_front
	{
	public:
		using type = Typelist<NewElem, TPLT>;
	};
	//-----------------------------
	// 泛化版本
	template <typename TPLT>
	class is_empty
	{
	public:
		static inline const bool value = false;
	};

	// 特化版本
	template <>
	class is_empty<NullTypelist>
	{
	public:
		static inline const bool value = true;
	};

	//-------------------------------
	/*//泛化版本
	template<typename TPLT, unsigned int index_v>
	class find : public find < typename pop_front<TPLT>::type, index_v - 1>
	{
	};
	//特化版本
	template<typename TPLT>
	class find<TPLT, 0> : public front<TPLT>  //0，作为递归的出口了
	{
	};
	*/
	//-------------------------------
	// 泛化版本
	template <class TPLT, unsigned int index_v>
	class find;

	// 特化版本1
	template <class Head, class Tail>
	class find<Typelist<Head, Tail>, 0>
	{
	public:
		using type = Head;
	};

	// 特化版本2
	template <class Head, class Tail, unsigned int index_v>
	class find<Typelist<Head, Tail>, index_v>
	{
	public:
		using type = typename find<Tail, index_v - 1>::type;
	};

	//-------------------------------
	// 泛化版本
	template <class TPLT, unsigned int index_v, typename DefaultType = NullTypelist>
	class find_nostrict
	{
	public:
		using type = DefaultType;
	};

	// 特化版本1
	template <class Head, class Tail, typename DefaultType>
	class find_nostrict<Typelist<Head, Tail>, 0, DefaultType>
	{
	public:
		using type = Head;
	};

	// 特化版本2
	template <class Head, class Tail, unsigned int index_v, typename DefaultType>
	class find_nostrict<Typelist<Head, Tail>, index_v, DefaultType>
	{
	public:
		using type = typename find_nostrict<Tail, index_v - 1, DefaultType>::type;
	};
}

namespace ns1
{
	template <typename Args>
	class TestTPClass
	{
	public:
		// 下面注意不要使用find，否则可能导致编译出错的境况
		using Arg1 = typename tplt2::find_nostrict<Args, 0>::type;
		using Arg2 = typename tplt2::find_nostrict<Args, 1>::type;
		using Arg3 = typename tplt2::find_nostrict<Args, 2>::type;
		// 可以根据需要加入更多Arg开头的类型

		void myfunc(Arg1 val1, Arg2 val2)
		{
			std::cout << "myfunc执行了：参数之和为：" << val1 + val2 << endl;
		}
	};
}

#define MAC_TYPELIST1(T1) tplt2::Typelist<T1, tplt2::NullTypelist>
#define MAC_TYPELIST2(T1, T2) tplt2::Typelist<T1, MAC_TYPELIST1(T2)>
#define MAC_TYPELIST3(T1, T2, T3) tplt2::Typelist<T1, MAC_TYPELIST2(T2, T3)>
#define MAC_TYPELIST4(T1, T2, T3, T4) tplt2::Typelist<T1, MAC_TYPELIST3(T2, T3, T4)>
// 根据此法可以定义出许多个参数的Typelist......
using TPL_NM3 = MAC_TYPELIST3(int, double, char);

int main()
{
#if 0
	using namespace tplt;
	typelist<> t0;
	typelist<int> t1;
	typelist<int, double, float, char, bool> t5;
#endif

#if 0
	using namespace tplt;

	cout << typeid(front<TPL_NM1>::type).name() << endl;
	// cout << typeid(front<TPL_NM2>::type).name() << endl;//error

	cout << tplt::size<TPL_NM1>::value << endl;
	cout << tplt::size<TPL_NM2>::value << endl;

	cout << typeid(pop_front<TPL_NM1>::type).name() << endl;
	// cout << typeid(pop_front<TPL_NM2>::type).name() << endl; // 编译报错，问题类似于front

	cout << typeid(push_front<TPL_NM1, bool>::type).name() << endl;
	cout << typeid(push_front<TPL_NM2, bool>::type).name() << endl;

	cout << typeid(push_back<TPL_NM1, bool>::type).name() << endl;
	cout << typeid(push_back<TPL_NM2, bool>::type).name() << endl;

	using TmpType = push_front<pop_front<TPL_NM1>::type, __int64>::type;
	cout << typeid(TmpType).name() << endl;
	cout << typeid(replace_front<TPL_NM1, __int64>::type).name() << endl;

	cout << tplt::is_empty<TPL_NM1>::value << endl; // 注意不要丢掉tplt::
	cout << tplt::is_empty<TPL_NM2>::value << endl;
#endif

#if 1
	using namespace tplt;

	cout << typeid(tplt::find<TPL_NM1, 2>::type).name() << endl;
	// cout << typeid(tplt::find<TPL_NM1, 20>::type).name() << endl; // 超出边界编译时就会报错

	cout << typeid(get_maxsize_type<TPL_NM1>::type).name() << endl;

	// cout << typeid(tplt::reverse<typelist<int, double, float>>::type).name() << endl;
#endif

	// cout << typeid(tplt2::front<MAC_TYPELIST1(int) >::type).name() << endl;
	// cout << typeid(tplt2::front< MAC_TYPELIST3(char, float, double) >::type).name() << endl;

	/*cout << tplt2::size< tplt2::NullTypelist >::value << endl;
	cout << tplt2::size< MAC_TYPELIST1(int) >::value << endl;
	cout << tplt2::size< MAC_TYPELIST3(int, double, char) >::value << endl;*/

	/*cout << typeid(tplt2::pop_front<MAC_TYPELIST1(int) >::type).name() << endl;
	cout << typeid(tplt2::pop_front<	MAC_TYPELIST3(char, float, double)>::type).name() << endl;*/

	/*cout << typeid(tplt2::push_front<MAC_TYPELIST1(int), bool>::type).name() << endl;
	cout << typeid(tplt2::push_front<MAC_TYPELIST2(char, double), int>::type).name() << endl;*/

	/*cout << tplt2::is_empty<MAC_TYPELIST1(int)>::value << endl;
	cout << tplt2::is_empty<MAC_TYPELIST3(char, float, double)>::value << endl;
	cout << tplt2::is_empty<tplt2::NullTypelist>::value << endl;
	*/

	/*cout << typeid(tplt2::find<MAC_TYPELIST1(int), 0>::type).name() << endl;
	cout << typeid(tplt2::find<MAC_TYPELIST3(char, float, double), 2>::type).name() << endl;*/

	// cout << typeid(tplt2::find<MAC_TYPELIST3(char, float, double), 5>::type).name() << endl;

	/*cout << typeid(tplt2::find_nostrict<
		MAC_TYPELIST4(int, double, char, float), 2>::type).name() << endl;
	cout << typeid(tplt2::find_nostrict<
		MAC_TYPELIST4(int, double, char, float), 100>::type).name() << endl;*/

#if 1
	using namespace ns1;
	TestTPClass<MAC_TYPELIST2(int, int)> myodtpobj;
	myodtpobj.myfunc(18, 19);
#endif

	cout << "Over!\n";
	return 0;
}
