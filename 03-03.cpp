#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

namespace ns1
{
	void funcLast0(int v1, int v2)
	{
		++v2; // 改变v2值，让其自增1
		cout << v1 + v2 << endl;
	}
	void funcLast1(int v1, int &v2)
	{
		++v2; // 改变v2值，让其自增1
		cout << v1 + v2 << endl;
	}
	void funcLast2(int &&v1, int &v2)
	{
		cout << v1 << endl;
		cout << v2 << endl;
	}

	// f：函数指针类型void (*)(int, int)，而funcLast0是函数类型void (int, int)
	template <typename F, typename T1, typename T2>
	void funcMiddle_Temp1(F f, T1 t1, T2 t2) { f(t1, t2); }

	template <typename F, typename T1, typename T2>
	void funcMiddle_Temp2(F f, T1 &&t1, T2 &&t2) { f(std::forward<T1>(t1), std::forward<T2>(t2)); }
}

namespace ns2
{
	void printInfo(int &)
	{
		cout << "printInfo(int &)" << endl;
	}
	void printInfo(int &&)
	{
		cout << "printInfo(int &&)" << endl;
	}
	void printInfo(const int &)
	{
		cout << "printInfo(const int &)" << endl;
	}

	template <typename T>
	void TestF(T &&t) // 万能引用
	{
		printInfo(std::forward<T>(t));
	}
}

namespace ns3
{
	int getData() { return 3; }
	void funcLast3(int v1) { cout << "v1 = " << v1 << endl; }

	void funcMiddle_Temp2()
	{
		auto &&result = getData(); // getData返回的是右值，所以：auto = int, result = int&&（右值引用）
		//......对result做各种运算等等
		funcLast3(std::forward<decltype(result)>(result));
	}
}

namespace ns4
{
	class Human
	{
		string m_sname;

	public:
		// Human(const string& tmpname):m_sname(tmpname)
		//{	cout << "Human(const string &)" << endl;}

		// Human(string&& tmpname):m_sname(tmpname)
		// Human(string&& tmpname):m_sname(std::move(tmpname))
		//{	cout << "Human(string&&)" << endl;}

		template <typename T>
		Human(T &&tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T &&)" << endl;
		}

		Human(const Human &th) : m_sname(th.m_sname)
		{
			cout << "Human(Human const &)" << endl;
		}
		Human(Human &&th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human &&)" << endl;
		}
	};
}

namespace ns5
{
	void funcLast1(int v1, int &v2)
	{
		++v2; // 改变v2值，让其自增1
		cout << v1 + v2 << endl;
	}

	template <typename F, typename... T>
	void funcMiddle_Temp1(F f, T &&...t)
	{
		f(std::forward<T>(t)...);
	}

	int funcLast2(int v1, int &v2)
	{
		++v2; // 改变v2值，让其自增1
		cout << v1 + v2 << endl;
		return v1 + v2;
	}

	template <typename F, typename... T>
	auto funcMiddle_Temp2(F f, T &&...t) -> decltype(f(std::forward<T>(t)...))
	{
		return f(std::forward<T>(t)...);
	}

	template <typename F, typename... T>
	decltype(auto) funcMiddle_Temp3(F f, T &&...t)
	{
		return f(std::forward<T>(t)...);
	}
}

namespace ns6
{
	void funcLast4(char *p)
	{
		// if (p != NULL)
		if (p != nullptr)
			strncpy(p, "abc", 3); // 为保证这行编译通过，请在.cpp开头位置增加：#pragma warning(disable : 4996)
	}

	template <typename F, typename... T>
	decltype(auto) funcMiddle_Temp(F f, T &&...t)
	{
		return f(std::forward<T>(t)...);
	}
}

int main()
{
#if 0
	using namespace ns1;
	int i;

	i = 50;
	cout << "i = " << i << endl;
	funcLast0(41, i); // 正常显示结果92
	cout << "i = " << i << endl;
	cout << "********************\n";

	i = 70;
	cout << "i = " << i << endl;
	funcMiddle_Temp1(funcLast0, 20, i); // 正常显示结果91，间接调用funcLast0函数，未修改i值
	cout << "i = " << i << endl;
	cout << "********************\n";

	i = 50;
	cout << "i = " << i << endl;
	funcLast1(41, i);			 // 正常显示结果92
	cout << "i = " << i << endl; // i=51，修改了i的值
	cout << "********************\n";

	i = 70;
	cout << "i = " << i << endl;
	funcMiddle_Temp1(funcLast1, 20, i); // 正常显示结果91，间接调用funcLast1函数，未修改i值
	cout << "i = " << i << endl;
	cout << "********************\n";

	i = 70;
	cout << "i = " << i << endl;
	funcLast2(20, i); // 显示20, 70
	cout << "i = " << i << endl;
	cout << "********************\n";

	i = 70;
	cout << "i = " << i << endl;
	funcMiddle_Temp2(funcLast2, 20, i);
	cout << "i = " << i << endl;
	cout << "********************\n";
#endif

#if 0
	using namespace ns2;
	TestF(1); // 1是右值

	int i = 5;
	TestF(i);			 // i是左值
	TestF(std::move(i)); // move:将左值转成右值

	const int j = 8;
	TestF(j);		// j是const左值
	TestF(int(12)); // int(3)是临时对象所以是右值

	int &&tmpvalue = 16;
	TestF(tmpvalue); // tmpvalue是左值
#endif

#if 0
	using namespace ns3;
	funcLast3(getData());
	funcMiddle_Temp2();
#endif

#if 0
	using namespace ns4;
	string sname = "ZhangSan";
	Human myhuman1(sname);			// Human(T &&)
	
	Human myhuman2(string("LiSi")); // Human(T &&), string("LiSi")是string右值类型
	Human myhuman2_1("LiSi");		// Human(T &&), "LiSi"是char const [5]类型

	//Human myhuman3(myhuman1);//error，myhuman1左值，编译器认为匹配构造函数模板比匹配构造函数更合适
	Human myhuman4(std::move(myhuman1));	// Human(Human &&)
	const Human myhuman5(string("WangWu")); // Human(T &&)
	Human myhuman6(myhuman5);				// Human(Human const &)
#endif

#if 0
	using namespace ns5;
	int j;

	j = 70;
	cout << "j = " << j << endl;
	funcMiddle_Temp3(funcLast2, 20, j);
	cout << "j = " << j << endl;
	cout << "*************\n";

	j = 70;
	cout << "j = " << j << endl;
	cout << funcMiddle_Temp2(funcLast2, 20, j) << endl;
	cout << "j = " << j << endl;
#endif

#if 0
	using namespace ns6;
	char *p = new char[100];
	memset(p, 0, 100);

	funcMiddle_Temp(funcLast4, p);
	// #define NULL 0
	//  funcMiddle_Temp(funcLast4, NULL);//error
	funcMiddle_Temp(funcLast4, nullptr);

	delete[] p;
#endif

	cout << "Over!\n";
	return 0;
}
