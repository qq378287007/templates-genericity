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
	//-------------------------------------------------
	//fixed traits类模板的泛化版本
	template<typename T>
	struct SumFixedTraits; //不需要实现代码，因为不需要用该版本进行实例化

	//各个fixed traits类模板的特化版本
	//（1）给进来的是char类型时，返回的是int类型 
	template<>
	struct SumFixedTraits<char> //char表示给进来的是char类型
	{
		using sumT = int; //sumT = int 代表的定义sumT为int类型，代表返回的是一个int类型
	};

	//（2）给进来的是int类型时，返回的是__int64(long long/int64_t)类型
	template<>
	struct SumFixedTraits<int> //int表示给进来的是int类型
	{
		using sumT = __int64; //sumT = __int64 代表的定义sumT为__int64类型，代表返回的是一个__int64类型
	};
	//（3）....其他给进来是某个类型，返回的是另外一个类型，可以任意扩展出多个SumFixedTraits类模板的特化版本

	//---------------------------------------------------
	template<typename T>
	//template<typename U, typename T>
	//T funcsum(const T* begin, const T* end)
	//U funcsum(const T* begin, const T* end)
	auto funcsum(const T* begin, const T* end)
	{
		
		//using boost::typeindex::type_id_with_cvr;
		//cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
		//cout << "tmprv=" << type_id_with_cvr<decltype(begin)>().pretty_name() << endl; //显示tmprv类型		
		//T sum{};  //零初始化，比如数值型变量初始化为0，指针型变量初始化为nullptr，bool型变量初始化为false
		
		using sumT = typename SumFixedTraits<T>::sumT; //给进来一个类型(T)，返回一个类型(sumT)，这是fixed traits的运用

		//U sum{};
		sumT sum{};

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
	void _display_category(random_access_iterator_tag mytag)
	{
		cout << "random_access_iterator_tag" << endl;
	}
	void _display_category(bidirectional_iterator_tag mytag)
	{
		cout << "bidirectional_iterator_tag" << endl;
	}
	void _display_category(forward_iterator_tag mytag)
	{
		cout << "forward_iterator_tag" << endl;
	}
	void _display_category(output_iterator_tag mytag)
	{
		cout << "output_iterator_tag" << endl;
	}
	void _display_category(input_iterator_tag mytag)
	{
		cout << "input_iterator_tag" << endl;
	}
	template <typename T>
	void display_category(T iter)
	{
		typename iterator_traits<T>::iterator_category cagy;//萃取机
		_display_category(cagy);

		if (typeid(typename iterator_traits<T>::iterator_category) == typeid(random_access_iterator_tag)) //typename可以省略
		{
			cout << "发现了某个容器的迭代器是random_access_iterator_tag类型" << endl;
		}

	};

}
namespace _nmsp3
{
	//fixed Traits
	//泛化版本
	template<typename T>
	/*struct GetEleType;*/
	struct GetEleType
	{
		using type = typename T::value_type; //针对容器
	};

	/*
	//特化版本
	template<typename T>
	struct GetEleType<std::vector<T>>
	{
		using type = T;
	};
	template<typename T>
	struct GetEleType<std::list<T>>
	{
		using type = T;
	};
	*/
	template<typename T, std::size_t Size> //这个特化版本增加了一个模板参数
	struct GetEleType<T[Size]> //萃取出数组元素个数
	{
		using type = T;
		static const std::size_t size = Size;
	};

	//-------------------
	//别名模板
	template<typename T>
	using EleType = typename GetEleType<T>::type;


	template<typename T>
	void PrintEleType(const T& container)
	{
		//cout << "容器(数组)的元素类型为：" << typeid(GetEleType< T >::type).name() << endl;
		cout << "容器(数组)的元素类型为：" << typeid(EleType<T>).name() << endl;
	}

}
namespace _nmsp4
{
	template<class T1, class T2>
	void print_is_same()
	{
		cout << "T1类型为：" << typeid(T1).name() << endl;
		cout << "T2类型为：" << typeid(T2).name() << endl;
		//cout << "T1和T2类型是否相等：" << std::is_same<T1, T2>() << endl; //值为1表示2个类型相等，值为0表示2个类型不等，is_same是标准库中用于判断两个类型是否相同的类模板，后面会讲到，写成std::is_same<T1,T2>::value效果也是一样的。
		cout << "T1和T2类型是否相等：" << std::is_same<T1, T2>::value << endl;
	}

	//---------------------------------
	//泛化版本
	template<typename T>
	struct RemoveReference
	{
		using type = T;
	};

	//特化版本
	template<typename T>
	struct RemoveReference<T&>
	{
		using type = T;
	};
	template<typename T>
	struct RemoveReference<T&&>
	{
		using type = T;
	};

	template< class T >
	using RemoveReference_t = typename RemoveReference<T>::type;

}
namespace _nmsp5
{
	template<typename T>
	struct AddLValueReference
	{
		using type = T&;
	};
	template<typename T>
	using AddLValueReference_t = typename AddLValueReference<T>::type; //实际上可以直接简化为using AddLValueReference_t = T&;，这样就不用定义AddLValueReference了


	template<typename T>
	struct AddRValueReference
	{
		using type = T&&;
	};
	template<typename T>
	using AddRValueReference_t = typename AddRValueReference<T>::type; //实际上可以直接简化为using AddRValueReference_t = T&&;，这样就不用定义AddRValueReference了

}
namespace _nmsp6
{
	//泛化版本
	template<typename T>
	struct RemoveConst
	{
		using type = T;
	};

	//特化版本
	template<typename T>
	struct RemoveConst<const T>
	{
		using type = T;
	};

	template<typename T>
	using RemoveConst_t = typename RemoveConst<T>::type;

}
namespace _nmsp7
{
	template<typename T>
	void myffunc(T tmprv)
	{
		cout << "---------------------begin------------------------" << endl;
		using boost::typeindex::type_id_with_cvr;
		cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
		cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
		cout << "----------------------end-------------------------" << endl;
	}
	void testFunc() {}

	//------------------------------
	//前面写过的RemoveReference挪到这里来
	//泛化版本
	template<typename T>
	struct RemoveReference
	{
		using type = T;
	};

	//特化版本
	template<typename T>
	struct RemoveReference<T&>
	{
		using type = T;
	};
	template<typename T>
	struct RemoveReference<T&&>
	{
		using type = T;
	};

	template< class T >
	using RemoveReference_t = typename RemoveReference<T>::type;
	//---------
	//前面写过的RemoveConst挪到这里来
	//泛化版本
	template<typename T>
	struct RemoveConst
	{
		using type = T;
	};

	//特化版本
	template<typename T>
	struct RemoveConst<const T>
	{
		using type = T;
	};

	template<typename T>
	using RemoveConst_t = typename RemoveConst<T>::type;
	//----------------

	template<typename T>
	struct RemoveCR : RemoveConst<typename RemoveReference<T>::type> //把const和引用修饰符去掉
	{
	};
	template<typename T>
	using RemoveCR_t = typename RemoveCR<T>::type;

	/*template<typename T>
	using RemoveCR_t = RemoveConst_t<RemoveReference_t<T>>;*/

	//----------------
	//泛化版本
	template<typename T>
	struct Decay :RemoveCR<T>
	{
	};

	//特化版本，注意这个特化版本没有继承任何父类
	//有边界数组转换成指针
	template<typename T, std::size_t size>
	struct Decay<T[size]>
	{
		using type = T*;
	};

	//无边界数组转换成指针
	template<typename T>
	struct Decay<T[]>
	{
		using type = T*;
	};

	//随便写一个函数用于测试目的
	void testFunc2()
	{
		cout << "testFunc2()执行了" << endl;
	}
	void rfunc()
	{
		cout << "rfunc执行了!" << endl;
	}

	template<typename T, typename... Args>
	struct Decay<T(Args...)>  //返回类型是T，参数是Args...
	{
		using type = T(*)(Args...);
	};
	template<class T>
	using Decay_t = typename Decay<T>::type;

}

int main()
{
	
	/*
	int myintarray1[] = { 10,15,20 };
	int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	char mychararray[] = "abc";  //97,98,99

	cout << _nmsp1::funcsum(&myintarray1[0], &myintarray1[2]) << endl;
	cout << _nmsp1::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
	cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl;*/

	/*cout << _nmsp1::funcsum<__int64>(&myintarray1[0], &myintarray1[2]) << endl;
	cout << _nmsp1::funcsum<__int64>(&myintarray2[0], &myintarray2[2]) << endl;
	cout << (int)(_nmsp1::funcsum<int>(&mychararray[0], &mychararray[2])) << endl;*/

	/*
	_nmsp2::display_category(vector<int>::iterator());
	_nmsp2::display_category(list<int>::iterator());*/

	/*cout << "vector<double>的元素类型为：" << typeid(_nmsp3::GetEleType< vector<double> >::type).name() << endl;
	cout << "list<int>的元素类型为：" << typeid(_nmsp3::GetEleType< list<int> >::type).name() << endl;
	cout << "float[45]的元素类型为：" << typeid(_nmsp3::GetEleType< float[45] >::type).name() << endl;
	cout << "float[45]的数组元素数量为：" << _nmsp3::GetEleType< float[45] >::size << endl;*/

	/*
	vector<double> mydblvec;
	_nmsp3::PrintEleType(mydblvec);

	list<int> myintlist;
	_nmsp3::PrintEleType(myintlist);

	float myfloatarr[45];
	_nmsp3::PrintEleType(myfloatarr);
	cout << "vector<double>的元素类型为：" << typeid(vector<double>::value_type).name() << endl;
	*/

	/*
	//std::remove_reference<int>::type a;
	//std::remove_reference<int&>::type b;
	//std::remove_reference<int&&>::type c;
	std::remove_reference_t<int> a;
	std::remove_reference_t<int&> b;
	std::remove_reference_t<int&&> c;

	_nmsp4::print_is_same<decltype(a), decltype(b)>();
	_nmsp4::print_is_same<decltype(a), decltype(c)>();*/

	//int&& a2 = 12;
	//_nmsp4::RemoveReference_t<decltype(a2)> b2 = "dd";//从报错的结果就能看到b2的类型已经转换成了int类型

	/*
	int&& a2 = 12;
	_nmsp4::RemoveReference_t<decltype(a2)> b2 = 125;
	int i = 64;
	int& c2 = i;
	_nmsp4::RemoveReference_t<decltype(c2)> d2 = 500;
	using boost::typeindex::type_id_with_cvr;
	cout << "b2=" << type_id_with_cvr<decltype(b2)>().pretty_name() << endl;
	cout << "d2=" << type_id_with_cvr<decltype(d2)>().pretty_name() << endl;*/

	/*
	int a = 15;
	std::add_lvalue_reference<decltype(a)>::type b = a; //b的类型为int &
	std::add_rvalue_reference<decltype(a)>::type c = 16; //c的类型为int &&

	using btype = std::add_lvalue_reference_t<int>;   //_t这个是别名模板
	cout << std::is_same<int&, btype>() << endl;       //1

	using ctype = std::add_rvalue_reference_t<int>;
	cout << std::is_lvalue_reference<btype>::value << endl; //1	
	cout << std::is_rvalue_reference<ctype>::value << endl; //1
		
	std::add_rvalue_reference_t<int&> cc1 = a; //cc的类型为int &，这里涉及到引用折叠：& 和&&折叠得到&
	std::add_rvalue_reference_t<int&&> cc2 = 16; //cc的类型为int &&，这里涉及到引用折叠：&&和&&折叠得到&&
	*/

	/*int anew = 15;
	_nmsp5::AddLValueReference_t<decltype(anew)> bnew = anew; //decltype(anew)的类型为int类型，bnew的类型为int &
	int&& anew2 = 16;
	_nmsp5::AddLValueReference_t<decltype(anew2)> bnew2 = anew2; //decltype(anew)的类型为int&&类型,bnew2的类型为int &
	*/

	/*
	int argnew = 15;
	_nmsp5::AddRValueReference_t<decltype(argnew)> brgnew = 18; //brgnew的类型为int &&

	int&& argnew2 = 15;
	_nmsp5::AddRValueReference_t<decltype(argnew2)> brgnew2 = 18;//brgnew的类型为int &&，根据引用折叠规则，两个右值引用遇到一起，结果还是右值引用

	int tmpvalue = 16;
	int& argnew3 = tmpvalue;
	_nmsp5::AddRValueReference_t<decltype(argnew3)> brgnew3 = tmpvalue;  //brgnew3的类型为int &，因为根据引用折叠规则，左值引用和右值引用遇到一起，结果是左值引用
	*/
	
	/*
	_nmsp6::RemoveConst_t<const int> nca = 15;  //nca是int类型
	nca = 18;  //可以给nca重新赋值*/

	/*
	const int a = 16;
	const int& b = a;
	const int&& c = 18;
	int arry[5] = { 1,2,3,4,5 };
	_nmsp7::myffunc(a);
	_nmsp7::myffunc(b);
	_nmsp7::myffunc(c);
	_nmsp7::myffunc(arry);
	_nmsp7::myffunc(_nmsp7::testFunc);


	std::decay<const int&>::type nb = 26;
	cout << "nb的类型为：" << typeid(decltype(nb)).name() << endl;  //nb的类型为int类型

	_nmsp7::RemoveCR_t<const int&&> rcrobj = 16;  //rcrobj为int类型
	*/

/*
	int arr[2] = { 1,2 };
	_nmsp7::Decay<decltype(arr)>::type myarray = nullptr;
	cout << "myarray类型为：" << typeid(decltype(myarray)).name() << endl;

	extern int g_array[];
	_nmsp7::Decay<decltype(g_array)>::type myarray2 = nullptr;
	cout << "myarray2类型为：" << typeid(decltype(myarray2)).name() << endl;


	void (*p)() = _nmsp7::testFunc2; //定义一个函数指针，指向testFunc2函数
	p(); //调用p指向的函数，也就是testFunc2函数
	*/

	//_nmsp7::Decay<decltype(_nmsp7::testFunc2)>::type rfunc;
	_nmsp7::Decay_t<decltype(_nmsp7::testFunc2)> rfunc;
	cout << "rfunc类型为：" << typeid(decltype(rfunc)).name() << endl;
	rfunc = _nmsp7::testFunc2;  //给函数指针赋值
	rfunc();  //调用rfunc函数

	
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
