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
	/*template <typename T>
	add_rvalue_reference_t<T> declval() noexcept;*/

	class A
	{
	public:
		A(int i)
		{
			printf("A::A()函数执行了,this = %p\n", this);
		}
		double myfunc()
		{
			printf("A::myfunc()函数执行了,this = %p\n", this);
			return 12.1;
		}

	private:
		~A() {}

	};
	
	template <typename T>
	//T& mydeclval() noexcept; //这里即便返回的类型是T&也可以
	T&& mydeclval() noexcept; //这里即便返回的类型是T&也可以


	class ALR
	{
	public:
		void onAnyValue()
		{
			cout << "ALR:: onAnyValue()函数执行了!" << endl;
		}
		void onLvalue()&   //只能被类ALR的左值对象调用
		{
			cout << "ALR::onLvalue()函数执行了!" << endl;
		}
		void onRvalue()&&  //只能被类A的右值对象调用
		{
			cout << "ALR::onRvalue()函数执行了!" << endl;
		}
	};

}
namespace _nmsp2
{
	//随便写一个函数用于测试目的
	int myfunc(int a, int b)
	{
		return a + b;
	}
	template<typename T_F, typename... U_Args>
	//decltype(std::declval<T_F>()(std::declval<U_Args>()...)) TestFnRtnImpl(T_F func, U_Args... args) //std::declval<>中的U_Args写成U_Args&&或U_Args&都可以
	auto TestFnRtnImpl(T_F func, U_Args... args) 
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}

	template<typename T_F, typename... U_Args>
	auto TestFnRtnImpl2(T_F func, U_Args... args) -> decltype(func(args...))
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}

}

int main()
{	
	/*
	using YT = decltype(std::declval<_nmsp1::A>()); //千万不要把std::declval<A>后的圆括号丢掉，否则代码的含义就发生变化了，想象函数调用时即便函数没有参数也要带着一对空的圆括号

	//利用boos输出类型名的方式比 typeid(...).name()用法输出类型名更准确
	using boost::typeindex::type_id_with_cvr;
	cout << "YT=" << type_id_with_cvr<YT>().pretty_name() << endl;

	//_nmsp1::A myaobj(1); //必须为构造函数提供实参
	//cout << "myaobj.myfunc()的返回类型=" << type_id_with_cvr< decltype(myaobj.myfunc()) >().pretty_name() << endl;
	//cout << "A::myfunc()的返回类型=" << type_id_with_cvr< decltype(std::declval<_nmsp1::A>().myfunc()) >().pretty_name() << endl;

	_nmsp1::A&& ayinobj();
	//ayinobj();
	//ayinobj().myfunc();
	//decltype(ayinobj().myfunc()) mydblvar; //定义一个double类型的变量mydblvar
	
	
	//---------------------------------------------------------------------
	cout << "mydeclval<A>()的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>()) >().pretty_name() << endl;
	cout << "mydeclval<A>().myfunc()的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>().myfunc()) >().pretty_name() << endl;
	cout << "sizeof(mydeclval<A>())=" << sizeof(_nmsp1::mydeclval<_nmsp1::A>()) << endl;

	//---------------------------------------------------------------------
	cout << "decltype(mydeclval<A>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A>()) >().pretty_name() << endl;
	cout << "decltype(mydeclval<A&>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A&>()) >().pretty_name() << endl;
	cout << "decltype(mydeclval<A&&>())的返回类型=" << type_id_with_cvr< decltype(_nmsp1::mydeclval<_nmsp1::A&&>()) >().pretty_name() << endl;

	//---------------------------------------------------------------------
	_nmsp1::ALR alr; //左值对象
	alr.onLvalue();
	//alr.onRvalue(); //编译错误，因为onRvalue只能被类A的右值对象调用
	_nmsp1::ALR().onRvalue(); //临时对象是右值对象
	//_nmsp1::ALR().onLvalue(); //编译错误，因为onLvalue只能被类A的左值对象调用

	
	//---------------------------------------------------------------------
	//mydeclval返回右值 引用时的测试代码
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue());
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onRvalue()没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onLvalue()是错误的

	//---------------------------------------------------------------------
	//mydeclval返回左值 引用时的测试代码
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue());
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	*/

	//auto result = _nmsp2::TestFnRtnImpl(_nmsp2::myfunc, 5, 8);
	auto result = _nmsp2::TestFnRtnImpl<int(int, int)>(_nmsp2::myfunc, 5, 8);
	cout << result << endl;

	/*int (*fp_var)(int x, int y); //函数指针类型fp_var= int (*)(int,int)
	int (*&&yy_fp_var)(int x, int y) = std::move(fp_var); //函数指针的右值引用类型yy_fp_var=int (*&&)(int,int),现在yy_fp_var就代表fp_var了
	fp_var = _nmsp2::myfunc;
	cout << fp_var(1, 2) << endl; //3
	cout << yy_fp_var(1, 2) << endl; //3*/

	auto result2 = _nmsp2::TestFnRtnImpl2(_nmsp2::myfunc, 13, 15);
	cout << result2 << endl;


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
