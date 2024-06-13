#include <iostream>
#include <vector>
using namespace std;

//#include <boost/type_index.hpp>
// using boost::typeindex::type_id_with_cvr;
//#pragma warning(disable : 4996)

namespace ns1
{
	template <typename T>
	void myfunc(const T &t) { cout << "myfunc(const T& t)" << endl; }

	void myfunc(int tmpvalue) { cout << "myfunc(int tmpvalue)" << endl; }

	void myfunc(unsigned int tmpvalue) { cout << "myfunc(unsigned int tmpvalue)" << endl; }
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

	template <class _Ty> // 偏特化版本
	struct enable_if<true, _Ty>
	{
		using type = _Ty;
	};
}

namespace ns4
{
	template <typename T>
	// typename std::enable_if< (sizeof(T) > 2) >::type  funceb()
	// std::enable_if_t< (sizeof(T) > 2) >  funceb()
	std::enable_if_t<(sizeof(T) > 2), T> funceb()
	{
		T myt = {};
		return myt;
	}

	// template <bool _Test, class _Ty = void>
	// using enable_if_t = typename enable_if<_Test, _Ty>::type;
}

namespace ns5
{
	template <typename T>
	using StrProcType = std::enable_if_t<std::is_convertible<T, std::string>::value>;

	class Human
	{
	public:
		// template<typename T>
		template <
			typename T, // typename = std::enable_if_t<std::is_convertible<T, std::string>::value>
			typename = StrProcType<T>>

		Human(T &&tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T &&tmpname)" << endl;
		}

		Human(const Human &th) : m_sname(th.m_sname)
		{
			cout << "Human(Human const &th)" << endl;
		}
		Human(Human &&th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human &&th)" << endl;
		}

	private:
		string m_sname; // 姓名
	};
}

int main()
{
#if 0
	using namespace ns1;
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
	funceb<int>();
	// funceb<char>();//eror
#endif

#if 0
	cout << "string => float: " << std::is_convertible<string, float>::value << endl; // 0
	cout << "float => int: " << std::is_convertible<float, int>::value << endl;		  // 1
#endif

#if 1
	using namespace ns5;
	string sname = "ZhangSan";
	Human myhuman1(sname);		// Human(T &&tmpname)
	Human myhuman2("ZhangSan"); // Human(T &&tmpname)
	Human myhuman3(myhuman1);	// Human(Human const &th)
#endif

	cout << "Over!\n";
	return 0;
}
