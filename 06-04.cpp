#include <iostream>
#include <string>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

namespace ns1
{
	template <typename T>
	void myfunc(T &&tmprv)
	{
		// 这里借助boost手段以得到准确的类型信息
		cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;					 // 显示T类型
		cout << "tmprv = " << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; // 显示tmprv类型
	}

	template <typename T>
	struct TmpClass1
	{
		TmpClass1(T &&) // 右值引用类型
		{
			cout << "TmpClass1<T>::TmpClass1(T &&)" << endl;
		}
	};

	template <typename T>
	class TmpClass2
	{
	public:
		template <typename T2>
		TmpClass2(T2 &&) // 万能引用类型
		{
			cout << "TmpClass2<T>::TmpClass2(T2 &&)" << endl;
		}
	};
}

namespace ns2
{
	void lastfunc(int &&) {}

	template <typename T>
	void midfunc(T &&tmprv)
	{
		lastfunc(tmprv);
	}

	template <typename T>
	void midfunc2(T &&tmprv)
	{
		lastfunc(std::forward<T>(tmprv));
		lastfunc(std::forward<T &&>(tmprv));
	}
}

namespace tpl
{
	// 泛化版本
	template <typename T, typename U = std::void_t<>>
	struct HasMemFunc : std::false_type
	{
	};

	// 特化版本
	template <typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc_MTL())>> : std::true_type
	{
	};

	// 泛化版本
	template <typename... Types>
	struct TuplE;

	// 特化版本1
	template <typename First, typename... Others>
	struct TuplE<First, Others...>
	{
		First first;
		TuplE<Others...> others;

		// 构造函数1，支持TuplE<int, float> mytuple;这种构造方式
		TuplE() {}

		// 构造函数模板2，支持TuplE<int, float> mytuple(12, 23.5f); 构造方式

		// template <typename C_First, typename... C_Others>
		// C_First代表一个元素类型比如float，C_Others代表其余一堆元素类型
		// 比如float, int, string，parf或first代表第一个元素比如12.5f，others或paro代表其余的元素，比如100，string("abc")
		// others是TuplE<...>类型

		// 判断类C_First中是否存在myfunc_MTL()函数，是就匹配构造函数模板，负责忽略
		template <typename C_First, typename... C_Others, typename = std::enable_if_t<!HasMemFunc<C_First>::value>>
		TuplE(C_First &&parf, C_Others &&...paro)
			: first(std::forward<C_First>(parf)), others(std::forward<C_Others>(paro)...)
		{
			// 为避免报错，牵扯开发者精力，不要输出first值，因为可能有些first值不能用cout正常输出
			// cout << "TuplE<First, Others...>::TuplE(C_First &&parf, C_Others &&...paro), first = " << first << endl;
			cout << "TuplE<First, Others...>::TuplE(C_First &&parf, C_Others &&...paro)" << endl;
		}

		// 拷贝构造函数
		// TuplE(TuplE<First, Others...> &tmptpl)
		TuplE(const TuplE<First, Others...> &tmptpl)
			: first(tmptpl.first), others(tmptpl.others)
		{
			// 为避免报错，牵扯开发者精力，不要输出first值，因为可能有些first值不能用cout正常输出
			// cout << "TuplE<First, Others...>::TuplE(const TuplE<First, Others...> &tmptpl), first = " << first << endl;
			cout << "TuplE<First, Others...>::TuplE(const TuplE<First, Others...> &tmptpl)" << endl;
		}

		// 构造函数模板
		template <typename C_First, typename... C_Others>
		TuplE(const TuplE<C_First, C_Others...> &tmptpl)
			: first(tmptpl.first), others(tmptpl.others)
		{
			cout << "TuplE<First, Others...>::TuplE(const TuplE<C_First, C_Others...> &tmptpl)" << endl;
		}

		void myfunc_MTL() {}
	};

	// 特化版本2：空元组不需要存储任何内容，支持TuplE<> mytuple;这种构造方式
	template <>
	struct TuplE<>
	{
		int m_sign; // 引入的目的其实仅仅是为了设置断点调试时方便观察和确认

		TuplE() // 构造函数
		{
			m_sign = 0; // 随便给个的值，方便调试时观察而已
			cout << "TuplE<>::TuplE()" << endl;
		}

		TuplE(const TuplE<> &) // 拷贝构造函数
		{
			m_sign = 100; // 随便给个的值，方便调试时观察而已
			cout << "TuplE<>::TuplE(const TuplE<> &)" << endl;
		}
	};

	// 泛化版本
	template <int index>
	struct TPLGetIdx
	{
		template <typename First, typename... Others>
		static auto myget(const TuplE<First, Others...> &tmptpl) // auto用的好
		{
			return TPLGetIdx<index - 1>::myget(tmptpl.others);
		}
	};

	// 特化版本
	template <>
	struct TPLGetIdx<0>
	{
		template <typename First, typename... Others>
		static auto myget(const TuplE<First, Others...> &tmptpl) // auto用的好
		{
			return tmptpl.first;
		}
	};

	// 函数模板
	template <int index, typename... Types>
	auto TuplEGet(const TuplE<Types...> &tmptpl)
	{
		return TPLGetIdx<index>::myget(tmptpl);
	}

	template <typename... Types>
	auto Make_TuplE(Types &&..._Args) // 形参是万能引用（转发引用）
	{
		return TuplE<std::decay_t<Types>...>(std::forward<Types>(_Args)...);
	}

	// 泛化版本
	template <typename TPLE> // TPLE代表整个TuplE<...>类型
	class pop_front_type;

	// 特化版本
	template <typename FirstElem, typename... OtherElem>
	class pop_front_type<TuplE<FirstElem, OtherElem...>>
	{
	public:
		using type = TuplE<OtherElem...>;
	};

	// template <typename... ElemsTypes, typename NewType>
	// auto push_front(const TuplE<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
	// {
	//		return TuplE<NewType, ElemsTypes...>(tmpvalue, tmptuple);
	// }

	// 向空TuplE的开头插入元素，用于结束递归
	template <typename NewType>
	auto push_front(const TuplE<> &, const NewType &tmpvalue)
	{
		return TuplE<NewType>(tmpvalue);
	}

	// 向非空TuplE的开头插入元素，利用递归
	template <typename FirstType, typename... OtherType, typename NewType>
	auto push_front(const TuplE<FirstType, OtherType...> &tmptuple, const NewType &tmpvalue)
	{
		return TuplE<NewType, FirstType, OtherType...>(tmpvalue, push_front(tmptuple.others, tmptuple.first));
	}

	// 向空TuplE的结尾插入元素，用于结束递归
	template <typename NewType>
	auto push_back(const TuplE<> &, const NewType &tmpvalue)
	{
		return TuplE<NewType>(tmpvalue);
	}

	// 向非空TuplE的结尾插入元素，利用递归
	template <typename FirstType, typename... OtherType, typename NewType>
	// 函数返回类型，实际相当于TuplE<FirstType, OtherType..., NewType>
	auto push_back(const TuplE<FirstType, OtherType...> &tmptuple, const NewType &tmpvalue)
	{
		return TuplE<FirstType, OtherType..., NewType>(tmptuple.first, push_back(tmptuple.others, tmpvalue));
	}

	// error
	// template<typename... ElemsTypes, typename NewType>
	// auto push_back(const TuplE<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
	// {
	//		return TuplE<ElemsTypes..., NewType>(tmptuple, tmpvalue);
	// }

	template <typename... ElemsTypes>
	auto pop_front(const TuplE<ElemsTypes...> &tmptuple)
	{
		return tmptuple.others;
	}

	// 普通函数reverse
	auto reverse(const TuplE<> &)
	{
		return TuplE<>();
	}

	// 函数模板reverse
	template <typename FirstType, typename... OtherType>
	auto reverse(const TuplE<FirstType, OtherType...> &tmptuple)
	{
		// 利用reverse递归可以逐步取得TuplE中每个元素，而后用push_back把取得的元素放到TuplE末尾，即可达到颠倒的效果
		return push_back(reverse(tmptuple.others), tmptuple.first);
	};
	/*
		// 向integer_sequence开头插入元素：泛化版本
		template <typename INTSEQ, unsigned int NewElem>
		struct IntSeq_PushFront;

		// 向integer_sequence开头插入元素：特化版本
		template <typename T, unsigned int... Elems, unsigned int NewElem>
		struct IntSeq_PushFront<std::integer_sequence<T, Elems...>, NewElem>
		{
			using type = std::integer_sequence<T, NewElem, Elems...>;
		};

		// 泛化版本
		template <typename T, unsigned int N, unsigned int Count = 1> // 从1开始记数
		struct Integer_Sequence_Reverse
		{
			using type = typename IntSeq_PushFront<typename Integer_Sequence_Reverse<T, N - 1>::type, N - Count>::type;
		};

		// 特化版本
		template <typename T, unsigned int N>
		struct Integer_Sequence_Reverse<T, N, N>
		{
			using type = std::integer_sequence<T, N - 1>;
		};

		// 定义别名模板
		template <typename T, unsigned int N>
		using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

		template <typename... Elems, std::size_t... Index>
		auto TPL_LastReverse(const TuplE<Elems...> &tmptuple, std::integer_sequence<std::size_t, Index...>)
		{
			return Make_TuplE(TuplEGet<Index>(tmptuple)...);
		}

		template <typename... Elems>
		auto TPL_MidReverse(const TuplE<Elems...> &tmptuple)
		{
			return TPL_LastReverse(tmptuple, Integer_Sequence_Reverse_T<unsigned int, sizeof...(Elems)>());
		}
	*/
}

int main()
{
#if 0
	string str1 = "abc";

	string str2 = str1;
	cout << "str1.size(): " << str1.size() << endl;

	string str3 = std::forward<string &&>(str1);
	cout << "str1.size(): " << str1.size() << endl;
#endif

#if 0
	using namespace ns1;
	int k = 10;
	myfunc(k);
	myfunc(10);

	TmpClass1<int> tcobj1(10);
	// TmpClass1<int> tcobj2(k);//error

	TmpClass2<int> tcobj3(10);
	TmpClass2<int> tcobj4(k); // ok
#endif

#if 0
	using namespace ns2;

	lastfunc(10);
	// midfunc(10);//error
	midfunc2(10);
#endif

#if 0
	tuple<float, int, string> mytuple(12.5f, 100, "abc"); // 一个tuple（元组）：一堆各种类型数据的组合
	cout << get<0>(mytuple) << endl;					  // 12.5，get是一个函数模板
#endif

#if 1
	using namespace tpl;

	TuplE<> mytuple0;
	TuplE<int, float> mytuple2;

	int i = 100;
	TuplE<float, int, string> mytuple3(12.5f, i, string("abc"));

	TuplE<float, int, string> mytuple3_2(mytuple3);
	TuplE<double, int, string> mytuple3_22(mytuple3);

	TuplE<float> tupleet1(12.5f);
	TuplE<int, TuplE<float>> tmptuple1(15, tupleet1);
	TuplE<int, TuplE<float>> tmptuple2(15, TuplE<float>(12.5f));

	const TuplE<float> tupleet10(12.5f);
	TuplE<float> tupleet11(tupleet10);

	cout << TuplEGet<2>(mytuple3) << endl;

	auto mytuple10 = std::make_tuple(12.5f, 100, string("abc")); // 3个元素
	std::tuple<float, int, string> mytuple11 = std::make_tuple(12.5f, 100, string("abc"));
	auto mytuple12 = Make_TuplE(12.5f, 100, string("abc"));

	TuplE<int, double> wtTpl1(100, 12.5);
	// TuplE<TuplE<int, double>> wtTpl2(wtTpl1);//error

	TuplE<float, int, string> mytpobj1(12.5f, 100, "abc");
	pop_front_type<decltype(mytpobj1)>::type mytpobj2(100, "abc");
	cout << TuplEGet<1>(mytpobj2) << endl;

	TuplE<> mytpobj3;
	auto mytpobj4 = push_front(mytpobj3, 12);
	TuplE<float, int, string> mytpobj5(12.5f, 100, "abc");
	auto mytpobj6 = push_front(mytpobj5, 12);

	auto mytpobj7 = push_back(mytpobj5, 12);

	auto mytpobj8 = pop_front(mytpobj5);
	auto mytpobj9 = reverse(mytpobj5);

	// auto mytpobj10 = TPL_MidReverse(mytpobj5);
#endif

	cout << "Over!\n";
	return 0;
}
