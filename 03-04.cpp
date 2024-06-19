#include <iostream>
#include <vector>
using namespace std;

namespace ns1
{
	template <typename T>
	void myfunc(const T &) { cout << "myfunc(const T&)" << endl; }

	void myfunc(int) { cout << "myfunc(int)" << endl; }

	void myfunc(unsigned int) { cout << "myfunc(unsigned int)" << endl; }
}

namespace ns2
{
	template <typename T>
	typename T::size_type mydouble(const T &t) { return t[0] * 2; }

	int mydouble(int i) { return i * 2; }
}

namespace ns3
{
	template <typename T>
	struct MEB
	{
		using type = T;
	};

	template <bool _Test, class _Ty = void> // 泛化版本
	struct enable_if
	{
	};

	template <class _Ty> // 偏特化版本，_Ty默认值是void（与泛化版本一致）
	struct enable_if<true, _Ty>
	{
		using type = _Ty;
	};
}

namespace ns4
{
	template <typename T>
	typename std::enable_if<(sizeof(T) > 2)>::type funceb1() {}

	template <bool _Test, class _Ty = void>
	using enable_if_t = typename std::enable_if<_Test, _Ty>::type;

	template <typename T>
	enable_if_t<(sizeof(T) > 2)> funceb2() {}

	template <typename T>
	std::enable_if_t<(sizeof(T) > 2), T> funceb()
	{
		T myt = {};
		return myt;
	}
}

namespace ns5
{
	class Human
	{
		string m_sname;

	public: // U可省略（没用到），T不能转换为string时，这个函数模板会被忽略
		template <typename T, typename U = std::enable_if_t<std::is_convertible<T, std::string>::value>>
		Human(T &&tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T &&)" << endl;
		}

		Human(const Human &th) : m_sname(th.m_sname) // 拷贝构造函数
		{
			cout << "Human(Human const &)" << endl;
		}
		Human(Human &&th) : m_sname(std::move(th.m_sname)) // 移动构造函数
		{
			cout << "Human(Human &&)" << endl;
		}
	};
}

namespace ns6
{
	template <typename T>
	using StrProcType = std::enable_if_t<std::is_convertible<T, std::string>::value>;

	class Human
	{
		string m_sname;

	public: // U可省略（没用到），T不能转换为string时，这个函数模板会被忽略
		template <typename T, typename U = StrProcType<T>>
		Human(T &&tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T &&)" << endl;
		}

		Human(const Human &th) : m_sname(th.m_sname) // 拷贝构造函数
		{
			cout << "Human(Human const &)" << endl;
		}
		Human(Human &&th) : m_sname(std::move(th.m_sname)) // 移动构造函数
		{
			cout << "Human(Human &&)" << endl;
		}
	};
}

int main()
{
#if 0
	using namespace ns1;
	myfunc(15);
	myfunc(15u);
#endif

#if 0
	using namespace ns2;
	cout << mydouble(15) << endl;

	vector<int> myvec{15}; // myvec.push_back(15);
	cout << mydouble(myvec) << endl;
#endif

#if 0
	using namespace ns3;
	MEB<int>::type abc = 15;

	ns3::enable_if<(3 > 2)>::type *mypoint1 = nullptr; // 等价于void *mypoint1 = nullptr;
	// ns3::enable_if<(3 < 2)>::type *mypoint2 = nullptr;	// error
#endif

#if 0
	using namespace ns4;
	funceb1<int>();
	funceb2<int>();
	funceb<int>();
	//funceb<char>();//eror
#endif

#if 0
	cout << "string => float: " << std::is_convertible<string, float>::value << endl; // 0
	cout << "float => int: " << std::is_convertible<float, int>::value << endl;		  // 1
#endif

#if 0
	using namespace ns5;
	string sname = "ZhangSan";
	Human myhuman1(sname);		// Human(T &&)
	Human myhuman2("ZhangSan"); // Human(T &&)
	Human myhuman3(myhuman1);	// Human(Human const &)
	Human myhuman4(move(myhuman1));	// Human(Human &&)
#endif

#if 1
	using namespace ns6;
	string sname = "ZhangSan";
	Human myhuman1(sname);			// Human(T &&)
	Human myhuman2("ZhangSan");		// Human(T &&)
	Human myhuman3(myhuman1);		// Human(Human const &)
	Human myhuman4(move(myhuman1)); // Human(Human &&)
#endif

	cout << "Over!\n";
	return 0;
}
