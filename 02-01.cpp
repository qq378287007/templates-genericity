#include <iostream>
using namespace std;

namespace ns1
{
	int Sub(int tv1, int tv2)
	{
		cout << "int Sub(int, int)" << endl;
		return tv1 - tv2;
	}

	float Sub(float tv1, float tv2)
	{
		cout << "int Sub(float, float)" << endl;
		return tv1 - tv2;
	}

	// T，类型模板参数，代表类型，可用class代替
	template <typename T>
	T Sub(T tv1, T tv2)
	{
		cout << "T Sub<T>(T, T)" << endl;
		return tv1 - tv2;
	}

	template <typename T>
	T Add(T tv1, T tv2)
	{
		cout << "T Add<T>(T, T)" << endl;
		return tv1 + tv2;
	}
}

namespace ns2
{
	template <typename T, typename U, typename V>
	V Add1(T tv1, U tv2)
	{
		cout << "V Add1<T, U, V>(T, U)" << endl;
		return tv1 + tv2;
	}

	template <typename V, typename T, typename U>
	V Add2(T tv1, U tv2)
	{
		cout << "V Add2<V, T, U>(T, U)" << endl;
		return tv1 + tv2;
	}

	template <typename T, typename U>
	auto Add3(T tv1, U tv2)
	{
		cout << "auto Add3<T, U>(T, U)" << endl;
		return tv1 + tv2;
	}

	template <typename T, typename U>
	auto Add4(T tv1, U tv2) -> decltype(tv1 + tv2)
	{
		cout << "auto Add4<T, U>(T, U) -> decltype(tv1 + tv2)" << endl;
		return tv1 + tv2;
	}
}

namespace ns3
{
	double mydouble(double tmpvalue)
	{
		cout << "double mydouble(double)" << endl;
		return tmpvalue;
	}

	template <typename T>
	T mydouble(T tmpvalue)
	{
		cout << "T mydouble<T>(T)" << endl;
		return tmpvalue * 2;
	}
}

namespace ns4
{
	void myfunc(int) { cout << "void myfunc(int)" << endl; }

	template <typename T>
	void myfunc(T) { cout << "void myfunc<T>(T)" << endl; }

	template <typename T>
	void myfunc(T *) { cout << "void myfunc<T>(T*)" << endl; }
}

namespace ns5
{
	// 函数重载
	void tfunc(int &tmprv, int &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc(int &tmprv, int &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <typename T, typename U>
	void tfunc(T &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<T, U>(T &tmprv, U &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <> // 全特化<>里就是空的
	// void tfunc<int, double>(int &tmprv, double &tmprv2) // 替换原来的T,U，这格式要与泛化版本一一对应不然编译就报错，比如第二个参数写成double tmprv2就会报错
	void tfunc(int &tmprv, double &tmprv2) // 替换原来的T,U，格式要与泛化版本一一对应
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<>(int &tmprv, double &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	// 模板参数数量上，函数模板不能偏特化
	/*
	template <typename U>
	void tfunc<double, U>(double &tmprv, U &tmprv2)
	{
		cout << "tfunc<double, U> partial specialization" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
	}
	*/

	// 模板参数范围上的偏特化，T类型范围变小
	// 实际上是，函数模板的重载
	template <typename T, typename U>
	void tfunc(const T &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "double tfunc<T, U>(const T &tmprv, U &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	// 重载实现模板参数数量上的偏特化
	// 去掉T，同时用double代替
	template <typename U>
	void tfunc(double &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<U>(double &tmprv, U &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <typename T>
	void tfunc(T &tmprv, double &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<T>(T &tmprv, double &tmprv2)" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}
}

namespace ns6
{
	int mf(int tmp1, int tmp2) { return 1; } // 普通函数

	// typedef int (*FunType)(int, int); // 函数指针类型定义
	using FunType = int (*)(int, int); // 函数指针类型定义

	template <typename T, typename F = FunType>
	void testfunc1(T i, T j, F funcpoint = mf) { cout << funcpoint(i, j) << endl; }

	// 函数模板的默认模板参数可以放在前面
	// 类模板的所有默认模板参数必须都放在最后面
	template <typename T = int, typename U>
	void testfunc2(U m)
	{
		T tmpvalue = m;
		cout << tmpvalue << endl;
	}
}

namespace ns7
{
	// 非类型模板参数（普通参数，int，double*等，不支持float、double、string等）
	// 一般给定常量
	// template <typename T, typename U, double val = 100.0>//error
	// template <typename T, typename U, int val = 100>
	template <typename T, typename U, auto val = 100>
	auto Add1(T tv1, U tv2)
	{
		return tv1 + tv2 + val;
	}

	// template <double *p>
	template <double *>
	void mft()
	{
		cout << "void mft<double *>()" << endl;
	}
	double g_d = 1.3; // 全局量

	// 未用到的参数T和int，可省略参数名
	// 第一个typename修饰类型模板参数
	// 第二个typename表明后面的int是一个类型，不能用class取代
	// template <typename T, int value>
	template <typename, int>
	// template <typename, typename int>
	auto Add2()
	{
		return 100;
	}
}

int main()
{
#if 0
	using namespace ns1;

	// 具体类型代替类型模板参数的过程叫做实例化
	// 自动类型推断，int
	int subv1 = Sub(3, 5);
	cout << "subv1 = " << subv1 << endl;

	int subv2 = Sub(4.7f, 2.1f);
	cout << "subv2 = " << subv2 << endl;

	int subv3 = Sub(4.7, 2.1);
	cout << "subv3 = " << subv3 << endl;

	string a("abc");
	string b("def");
	// string result1 = Sub(a, b); //error
	string result2 = Add(a, b);
	cout << "result2 = " << result2 << endl;

	// 自动类型推断中，类型必须精确匹配，否则<>显示指定类型
	// Sub(3, 4.0);//error
	Sub<double>(3, 4.0);
	Sub(double(3), 4.0);
#endif

#if 0
	using namespace ns2;

	// 必须显示指定三种类型
	//  cout << Add1(15, 17.8) << endl;//error
	double result1 = Add1<int, double, double>(15, 17.8);
	cout << "result1 = " << result1 << endl;

	// 显示指定一种类型，自动推断两种类型
	double result2 = Add2<double>(15, 17.8);
	cout << "result2 = " << result2 << endl;

	// 自动推断三种类型
	double result3 = Add3(15, 17.8);
	cout << "result3 = " << result3 << endl;

	// 自动推断三种类型
	double result4 = Add4(15, 17.8);
	cout << "result4 = " << result4 << endl;
	cout << Add4<int, double>(15, 17.8) << endl;
#endif

#if 0
	using namespace ns3;

	// 自动推断类型
	int result1 = mydouble(16);
	cout << "result1 = " << result1 << endl;

	// 显示指定类型，16.9自动转化为int，16
	int result2 = mydouble<int>(16.9);
	cout << "result2 = " << result2 << endl;

	// 自动推断类型，使用类型模板函数
	double result3 = mydouble<>(16.9); // 33.8
	cout << "result3 = " << result3 << endl;

	// 优先使用普通函数
	double result4 = mydouble(16.9);
	cout << "result4 = " << result4 << endl; // 函数
#endif

#if 0
	using namespace ns4;

	// 重载
	// 优先使用普通函数，其次使用范围更小的函数模板
	myfunc(12); // 函数

	char *p = nullptr;
	myfunc(p);

	myfunc(12.1);
	myfunc(nullptr);
#endif

#if 0
	using namespace ns5;

	int ii = 13;
	int jj = 14;
	tfunc(ii, jj);
	// tfunc(13, 14);//error

	int k = 12;
	double db = 15.8;
	tfunc(k, db); // 全特化版本

	tfunc(12, db);// 函数模板重载,实现函数模板参数数量上的偏特化

	tfunc(db, k);

	double kk = 14.0;
	// tfunc(kk, db);//error

	const char *p = "I Love China!";
	int i = 12;
	tfunc(p, i); // 泛化版本
#endif

#if 0
	using namespace ns6;

	testfunc1(15, 16);
	testfunc2(12.5);
#endif

#if 1
	using namespace ns7;

	cout << Add1<float, float>(22.3f, 11.8f) << endl;
	cout << Add1<float, float, 800>(22.3f, 11.8f) << endl;

	// error，非类型模板参数（普通参数），需要常量，编译时确定值
	// int k = 1000;
	// cout << Add1<float, float, k>(22.3f, 11.8f) << endl;// error

	// 非类型模板参数支持的参数类型，支持int，double*等，不支持double、float、string
	// 允许类型：整型或枚举、指针、左值引用、auto或decltype(auto)
	static double data = 1.0;
	mft<&data>();
	mft<&g_d>();

	cout << Add2<int, 1>() << endl;
#endif

	cout << "Over!\n";
	return 0;
};
