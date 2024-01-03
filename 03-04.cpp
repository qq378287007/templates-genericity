#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{
	template <typename T>
	void myfunc(const T& t)
	{
		cout << "myfunc函数模板执行了" << endl;
	}

	//void myfunc(int tmpvalue)
	void myfunc(unsigned int tmpvalue)
	{
		cout << "myfunc函数执行了" << endl;
	}
}
namespace _nmsp2
{
	template <typename T>
	typename T::size_type mydouble(const T& t)
	{
		return t[0] * 2;
	}

	int mydouble(int i)
	{
		return i * 2;
	}

}
namespace _nmsp3
{
	template <typename T>
	struct MEB
	{
		using type = T;
	};

	//// STRUCT TEMPLATE enable_if
	//template <bool _Test, class _Ty = void> //泛化版本
	//struct enable_if {};

	//template <class _Ty>     //偏特化版本
	//struct enable_if<true, _Ty> {
	//	using type = _Ty;
	//};


}
namespace _nmsp4
{
	template<typename T>
	//typename std::enable_if< (sizeof(T) > 2) >::type  funceb()
	//std::enable_if_t< (sizeof(T) > 2) >  funceb()
	std::enable_if_t< (sizeof(T) > 2), T >  funceb()
	{
		//......
		T myt = {};
		return myt;
	}

	//template <bool _Test, class _Ty = void>
	//using enable_if_t = typename enable_if<_Test, _Ty>::type;

}
namespace _nmsp5
{
	template<typename T>
	using StrProcType = std::enable_if_t< std::is_convertible<T, std::string>::value >;
	
	class Human
	{
	public:
		
		

		//template<typename T>
		template<
			typename T,
			/*typename = std::enable_if_t<
										std::is_convertible<T, std::string>::value
										>*/
			typename = StrProcType<T>
		>

		Human(T&& tmpname) :m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T&& tmpname)执行" << endl;
		}

		Human(const Human& th) : m_sname(th.m_sname)
		{
			cout << "Human(Human const& th)拷贝构造函数执行" << endl;
		}
		Human(Human&& th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human const& th)移动构造函数执行" << endl;
		}


	private:
		string m_sname;  //姓名	

	};
}

int main()
{	
	//_nmsp1::myfunc(15u);

	/*
	_nmsp2::mydouble(15);

	vector<int> myvec;
	myvec.push_back(15);
	cout << _nmsp2::mydouble(myvec) << endl;
	*/

	/*
	//_nmsp3::MEB<int>::type  abc = 15;
	std::enable_if< (3 > 2) >::type* mypoint1 = nullptr; //等价于void *mypoint1=nullptr;
	//std::enable_if< (3 < 2) >::type* mypoint2 = nullptr;*/

	/*
	_nmsp4::funceb<int>();
	//_nmsp4::funceb<char>();*/


	//cout << "string => float: " << std::is_convertible<string, float>::value << endl;//0
	//cout << "float => int: " << std::is_convertible<float, int>::value << endl;//1

	string sname = "ZhangSan";
	_nmsp5::Human myhuman1(sname);	
	_nmsp5::Human myhuman3(myhuman1);

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
