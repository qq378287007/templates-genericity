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

	// f：函数指针类型void (*)(int, int)，而funcLast2是函数类型void (int, int)

	template <typename F, typename T1, typename T2>
	void funcMiddle_Temp1(F f, T1 t1, T2 t2) { f(t1, t2); }

	template <typename F, typename T1, typename T2>
	void funcMiddle_Temp2(F f, T1 &&t1, T2 &&t2) { f(std::forward<T1>(t1), std::forward<T2>(t2)); }
}

namespace ns2
{
	void printInfo(int &t)
	{
		cout << "printInfo(int &t)" << endl;
	}
	void printInfo(int &&t)
	{
		cout << "printInfo(int &&t)" << endl;
	}
	void printInfo(const int &t)
	{
		cout << "printInfo(const int &t)" << endl;
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
	void funcLast3(int &&v1) { cout << "v1 = " << v1 << endl; }

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
	public:
		// Human(const string& tmpname):m_sname(tmpname)
		//{	cout << "Human(const string & tmpname)" << endl;}

		// Human(string&& tmpname):m_sname(tmpname)
		// Human(string&& tmpname):m_sname(std::move(tmpname))
		//{	cout << "Human(string&& tmpname)" << endl;}

		template <typename T>
		Human(T &&tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T &&tmpname)" << endl;
		}

		Human(const Human &th) : m_sname(th.m_sname)
		{
			cout << "Human(Human const& th)" << endl;
		}
		Human(Human &&th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human &&th)" << endl;
		}

	private:
		string m_sname;
	};
}

namespace ns5
{
	template <typename F, typename... T>
	void funcMiddle_Temp1(F f, T &&...t)
	{
		f(std::forward<T>(t)...);
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

	void funcLast1(int v1, int &v2)
	{
		++v2; // 改变v2值，让其自增1
		cout << v1 + v2 << endl;
	}
	int funcLast2(int v1, int &v2)
	{
		++v2;
		cout << v1 + v2 << endl;
		return v1 + v2;
	}
}

namespace ns6
{
	template <typename F, typename... T>
	decltype(auto) funcMiddle_Temp(F f, T &&...t)
	{
		return f(std::forward<T>(t)...);
	}

	void funcLast4(char *p)
	{
		// if (p != NULL)
		if (p != nullptr)
			strncpy(p, "abc", 3); // 为保证这行编译通过，请在.cpp开头位置增加：#pragma warning(disable : 4996)
	}
}

int main()
{
#if 0
	using namespace ns1;

	int i;

	i = 50;
	funcLast0(41, i); // 正常显示结果92
	cout << "i = " << i << endl
		 << endl;

	i = 70;
	funcMiddle_Temp1(funcLast1, 20, i);
	cout << "i = " << i << endl
		 << endl;

	i = 70;
	funcMiddle_Temp2(funcLast1, 20, i);
	cout << "i = " << i << endl
		 << endl;

	i = 70;
	funcMiddle_Temp2(funcLast2, 20, i);
	cout << "i = " << i << endl
		 << endl;
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
	Human myhuman1(sname);			// Human(T &&tmpname)
	Human myhuman2(string("LiSi")); // Human(T &&tmpname), string("LiSi")是string类型
	Human myhuman2_1("LiSi");		// Human(T &&tmpname), "LiSi"是char const [5]类型

	// Human myhuman3(myhuman1);//error
	Human myhuman4(std::move(myhuman1));	// Human(Human &&th)
	const Human myhuman5(string("WangWu")); // Human(T &&tmpname)
	Human myhuman6(myhuman5);				// Human(Human const& th)
#endif

#if 0
	using namespace ns5;
	int j;

	j = 70;
	funcMiddle_Temp3(funcLast2, 20, j);
	cout << "j = " << j << endl
		 << endl;

	j = 70;
	int k = funcMiddle_Temp2(funcLast2, 20, j);
	cout << "j = " << j << endl;
	cout << "k = " << k << endl;
#endif

#if 1
	using namespace ns6;
	char *p = new char[100];
	memset(p, 0, 100);

	funcMiddle_Temp(funcLast4, p);
	// funcMiddle_Temp(funcLast4, NULL);//error
	funcMiddle_Temp(funcLast4, nullptr);

	delete[] p;
#endif

	cout << "Over!\n";
	return 0;
}
