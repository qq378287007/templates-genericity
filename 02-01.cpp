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
	void myfunc(int tmpvalue)
	{
		cout << "void myfunc(int)" << endl;
	}

	template <typename T>
	void myfunc(T tmpvalue)
	{
		cout << "void myfunc<T>(T)" << endl;
	}

	template <typename T>
	void myfunc(T *tmpvalue)
	{
		cout << "void myfunc<T>(T*)" << endl;
	}
}

namespace ns5
{
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
		cout << "void tfunc<T, U>(T &tmprv, U &tmprv2)泛化" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <>
	void tfunc(int &tmprv, double &tmprv2) // 替换原来的T,U，格式要与泛化版本一一对应
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<>(int &tmprv, double &tmprv2)全特化" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <typename T, typename U>
	void tfunc(const T &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "double tfunc<T, U>(const T &tmprv, U &tmprv2)偏特化" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <typename U>
	void tfunc(double &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<U>(double &tmprv, U &tmprv2)偏特化" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	template <typename T>
	void tfunc(T &tmprv, double &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "void tfunc<T>(T &tmprv, double &tmprv2)偏特化" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}
}

namespace ns6
{
	int mf(int tmp1, int tmp2) // 普通函数
	{
		return 1;
	}

	//typedef int (*FunType)(int, int); // 函数指针类型定义
	using FunType = int (*)(int, int); // 函数指针类型定义
	template <typename T, typename F = FunType>
	void testfunc1(T i, T j, F funcpoint)
	{
		cout << funcpoint(i, j) << endl;
	}

	template <typename T = int, typename U>
	void testfunc2(U m)
	{
		T tmpvalue = m;
		cout << tmpvalue << endl;
	}
}

namespace ns7
{
	// template <typename T, typename U, double val = 100.0>//error
	template <typename T, typename U, int val = 100>
	// template <typename T, typename U, auto val = 100>
	auto Add1(T tv1, U tv2)
	{
		return tv1 + tv2 + val;
	}

	double g_d = 1.3; // 全局量
	template <double *>
	void mft()
	{
		cout << "void mft<double *>()" << endl;
	}

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
#endif

#if 0
	using namespace ns2;

	double result1 = Add1<int, double, double>(15, 17.8);
	cout << "result1 = " << result1 << endl;

	double result2 = Add2<double>(15, 17.8);
	cout << "result2 = " << result2 << endl;

	double result3 = Add3(15, 17.8);
	cout << "result3 = " << result3 << endl;

	double result4 = Add4(15, 17.8);
	cout << "result4 = " << result4 << endl;
#endif

#if 0
	using namespace ns3;

	int result1 = mydouble(16);
	cout << "result1 = " << result1 << endl;

	int result2 = mydouble<int>(16.9);
	cout << "result2 = " << result2 << endl;

	double result3 = mydouble<>(16.9);
	cout << "result3 = " << result3 << endl;

	double result4 = mydouble(16.9);
	cout << "result4 = " << result4 << endl; // 函数
#endif

#if 0
	using namespace ns4;

	myfunc(12); // 函数

	myfunc(12.1);
	myfunc(nullptr);

	char *p = nullptr;
	myfunc(p);
#endif

#if 0
	using namespace ns5;

	int ii = 13;
	int jj = 14;
	tfunc(ii, jj);
	// tfunc(13, 14);//error

	int k = 12;
	double db = 15.8;
	tfunc(k, db);

	tfunc(12, db);

	tfunc(db, k);

	double kk = 14.0;
	// tfunc(kk, db);//error

	const char *p = "I Love China!";
	int i = 12;
	tfunc(p, i);
#endif

#if 0
	using namespace ns6;

	testfunc1(15, 16, mf);
	testfunc2(12.5);
#endif

#if 1
	using namespace ns7;

	cout << Add1<float, float>(22.3f, 11.8f) << endl;
	cout << Add1<float, float, 800>(22.3f, 11.8f) << endl;
	
	// int k = 1000;
	// cout << Add1<float, float, k>(22.3f, 11.8f) << endl;// error

	mft<&g_d>();

	cout << Add2<int, 1>() << endl;
#endif

	cout << "Over!\n";
	return 0;
};
