#include <iostream>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
// #pragma warning(disable : 4996)

namespace ns1
{
	// template <typename T>
	// add_rvalue_reference_t<T> declval() noexcept;

	class A
	{
	public:
		A(int i) { printf("A::A(int), this = %p\n", this); }
		double myfunc()
		{
			printf("A::myfunc(), this = %p\n", this);
			return 12.1;
		}

	private:
		//~A() {}
	};

	template <typename T>
	T &&mydeclval() noexcept; // 这里即便返回的类型是T&也可以

	struct ALR
	{
		void onAnyValue() { cout << "ALR:: onAnyValue()!" << endl; }
		void onLvalue() & { cout << "ALR::onLvalue() &" << endl; }	 // 只能被类ALR的左值对象调用
		void onRvalue() && { cout << "ALR::onRvalue() &&" << endl; } // 只能被类A的右值对象调用
	};
}

namespace ns2
{
	// 随便写一个函数用于测试目的
	int myfunc(int a, int b) { return a + b; }

	template <typename T_F, typename... U_Args>
	// decltype(std::declval<T_F>()(std::declval<U_Args>()...)) TestFnRtnImpl(T_F func, U_Args... args) //std::declval<>中的U_Args写成U_Args&&或U_Args&都可以
	auto TestFnRtnImpl(T_F func, U_Args... args)
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}

	template <typename T_F, typename... U_Args>
	auto TestFnRtnImpl2(T_F func, U_Args... args) -> decltype(func(args...))
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}
}

int main()
{
#if 0
	using namespace ns1;

	using YT = decltype(std::declval<A>()); // 千万不要把std::declval<A>后的圆括号丢掉，否则代码的含义就发生变化了，想象函数调用时即便函数没有参数也要带着一对空的圆括号
	cout << "YT = " << type_id_with_cvr<YT>().pretty_name() << endl;

	A myaobj(1); // 必须为构造函数提供实参
	cout << "return type of myaobj.myfunc() = " << type_id_with_cvr<decltype(myaobj.myfunc())>().pretty_name() << endl;
	cout << "return type of A::myfunc() = " << type_id_with_cvr<decltype(std::declval<A>().myfunc())>().pretty_name() << endl;

	A &&ayinobj();
	// ayinobj();
	// ayinobj().myfunc();
	decltype(ayinobj().myfunc()) mydblvar; // 定义一个double类型的变量mydblvar

	cout << "return type of mydeclval<A>() = " << type_id_with_cvr<decltype(mydeclval<A>())>().pretty_name() << endl;
	cout << "return type of mydeclval<A>().myfunc() = " << type_id_with_cvr<decltype(mydeclval<A>().myfunc())>().pretty_name() << endl;
	cout << "sizeof(mydeclval<A>()) = " << sizeof(mydeclval<A>()) << endl;

	cout << "return type of decltype(mydeclval<A>()) = " << type_id_with_cvr<decltype(mydeclval<A>())>().pretty_name() << endl;
	cout << "return type of decltype(mydeclval<A&>()) = " << type_id_with_cvr<decltype(mydeclval<A &>())>().pretty_name() << endl;
	cout << "return type of decltype(mydeclval<A&&>()) = " << type_id_with_cvr<decltype(mydeclval<A &&>())>().pretty_name() << endl;

	ALR alr; // 左值对象
	alr.onLvalue();
	// alr.onRvalue(); //编译错误，因为onRvalue只能被类A的右值对象调用

	ALR().onRvalue(); // 临时对象是右值对象
	// ALR().onLvalue(); //编译错误，因为onLvalue只能被类A的左值对象调用

	// mydeclval返回右值 引用时的测试代码
	decltype(mydeclval<ALR>().onAnyValue());
	decltype(mydeclval<ALR &>().onLvalue());  // 返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	decltype(mydeclval<ALR &&>().onRvalue()); // 返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onRvalue()没问题
	// decltype(mydeclval<ALR&>().onRvalue());  //返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
	// decltype(mydeclval<ALR&&>().onLvalue()); //返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onLvalue()是错误的

	// mydeclval返回左值 引用时的测试代码
	decltype(mydeclval<ALR>().onAnyValue());
	decltype(mydeclval<ALR &>().onLvalue());  // 返回类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue()没问题
	decltype(mydeclval<ALR &&>().onRvalue()); // 返回类型是class ALR &&，代表返回的是右值对象，右值对象调用onRvalue()没问题

	// decltype(mydeclval<ALR &>().onRvalue());  // 返回类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue()是错误的
#endif

#if 1
	using namespace ns2;
	auto result = TestFnRtnImpl(myfunc, 5, 8);

	auto result2 = TestFnRtnImpl<int(int, int)>(myfunc, 5, 8);
	cout << result2 << endl;

	int (*fp_var)(int x, int y);						  // 函数指针类型fp_var = int (*)(int,int)
	int (*&&yy_fp_var)(int x, int y) = std::move(fp_var); // 函数指针的右值引用类型yy_fp_var = int (*&&)(int, int), 现在yy_fp_var就代表fp_var了
	fp_var = myfunc;
	cout << fp_var(1, 2) << endl;	 // 3
	cout << yy_fp_var(1, 2) << endl; // 3

	auto result3 = TestFnRtnImpl2(myfunc, 13, 15);
	cout << result3 << endl;
#endif

	cout << "Over!\n";
	return 0;
}
