#include <iostream>
using namespace std;

namespace _nmsp1
{
	/*int Sub(int tv1, int tv2)
	{
		return tv1 - tv2;
	}

	float Sub(float tv1, float tv2)
	{
		return tv1 - tv2;
	}*/

	template <typename T>
	T Sub(T tv1, T tv2)
	{
		return tv1 + tv2;
	}
}

namespace _nmsp2
{
	// template <typename T, typename U, typename V>
	/*template <typename V, typename T, typename U >
	V Add(T tv1, U tv2)
	{
		return tv1 + tv2;
	}*/

	template <typename T, typename U>
	// auto Add(T tv1, U tv2)
	auto Add(T tv1, U tv2) -> decltype(tv1 + tv2)
	{
		return tv1 + tv2;
	}
}

namespace _nmsp3
{
	template <typename T>
	T mydouble(T tmpvalue)
	{
		return tmpvalue * 2;
	}

	double mydouble(double tmpvalue)
	{
		return tmpvalue * 2;
	}

}

namespace _nmsp4
{
	template <typename T>
	void myfunc(T tmpvalue)
	{
		cout << "myfunc(T tmpvalue)执行了" << endl;
	}

	template <typename T>
	void myfunc(T *tmpvalue)
	{
		cout << "myfunc(T *tmpvalue)执行了" << endl;
	}
	void myfunc(int tmpvalue)
	{
		cout << " myfunc(int tmpvalue)执行了" << endl;
	}

}

namespace _nmsp5
{
	template <typename T, typename U>
	void tfunc(T &tmprv, U &tmprv2)
	{
		cout << "tfunc泛化版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
	}

	template <>							   // 全特化<>里就是空的
	void tfunc(int &tmprv, double &tmprv2) // 替换原来的T,U，这格式要与泛化版本一一对应不然编译就报错，比如第二个参数写成double tmprv2就会报错
	{
		cout << "-------------begin-------------" << endl;
		cout << "tfunc<int,double>特化版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

	void tfunc(int &tmprv, double &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "tfunc普通函数" << endl;
		cout << "-------------end---------------" << endl;
	}
	/*template<typename U>
	void tfunc<double, U>(double& tmprv, U& tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "tfunc<double,U>偏特化版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}*/
	template <typename T, typename U>
	void tfunc(const T &tmprv, U &tmprv2)
	{
		//......
	}

	template <typename U>
	void tfunc(double &tmprv, U &tmprv2)
	{
		cout << "-------------begin-------------" << endl;
		cout << "类似于tfunc<double,U>偏特化的tfunc重载版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "-------------end---------------" << endl;
	}

}

namespace _nmsp6
{
	// 普通函数
	int mf(int tmp1, int tmp2)
	{
		return 1;
	}
	typedef int (*FunType)(int, int); // 函数指针类型定义
	template <typename T, typename F = FunType>
	void testfunc(T i, T j, F funcpoint)
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

namespace _nmsp7
{
	// template <typename T, typename U, int val = 100>
	template <typename T, typename U, auto val = 100>
	// template <typename T, typename U, double val = 100>
	auto Add(T tv1, U tv2)
	{
		return tv1 + tv2 + val;
	}

	template <double *p>
	void mft()
	{
		cout << "mft()执行了" << endl;
	}
	double g_d = 1.3; // 全局量

	// template <typename T, int value>
	// template <typename, int>
	template <typename, typename int>
	auto Add2()
	{
		return 100;
	}
}

int main()
{
	/*int subv = _nmsp1::Sub(3, 5);
	cout << "subv = " << subv << endl;
	double subv2 = _nmsp1::Sub(4.7, 2.1);
	cout << "subv2 = " << subv2 << endl;

	string a("abc"), b("def");
	string addresult = _nmsp1::Sub(a, b);*/

	/*cout << _nmsp2::Add(15, 17.8) << endl;
	//cout << _nmsp2::Add<int, double, double>(15, 17.8) << endl;
	cout << _nmsp2::Add<double>(15, 17.8) << endl;
	cout << _nmsp2::Add(15, 17.8) << endl;*/

	/*int result = _nmsp3::mydouble(15);
	//int result2 = _nmsp3::mydouble<int>(16.9);
	auto result3 = _nmsp3::mydouble<>(16.9); //33.8
	auto  result4 = _nmsp3::mydouble(16.9);*/

	/*_nmsp4::myfunc(12);
	char* p = nullptr;
	_nmsp4::myfunc(p);
	_nmsp4::myfunc(12.1);*/

	/*const char* p = "I Love China!";
	int i = 12;
	_nmsp5::tfunc(p, i);

	int k = 12;
	double db = 15.8f;
	_nmsp5::tfunc(k, db);  //这里调用的就是特化版本*/

	/*const char* p = "I Love China!";
	int i = 12;
	_nmsp5::tfunc(p, i);

	double j = 18.5;
	_nmsp5::tfunc(j, i);*/

	/*_nmsp6::testfunc(15, 16, _nmsp6::mf);
	_nmsp6::testfunc2(12);*/

	/*cout << _nmsp7::Add<float, float>(22.3f, 11.8f) << endl;
	cout << _nmsp7::Add<float, float, 800>(22.3f, 11.8f) << endl;*/

	/*int k = 1000;
	cout << _nmsp7::Add<float, float, k>(22.3f, 11.8f) << endl;*/

	_nmsp7::mft<&_nmsp7::g_d>(); // mft()执行了

	cout << _nmsp7::Add2<int, 1>() << endl;

	return 0;
};
