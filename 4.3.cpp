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
	//template<typename...Args>
	//using void_t = void;

	struct NoInnerType
	{
		int m_i;
	};
	struct HaveInnerType
	{
		using type = int;
		void myfunc() {}
	};


	//泛化版本
	template<typename T, typename U = std::void_t<> >
	struct HasTypeMem : std::false_type  //struct默认是public继承，class默认是private继承
	{
	};

	//特化版本
	template<typename T>
	struct HasTypeMem<T, std::void_t<typename T::type>> : std::true_type
	{
	};

	//带参数的宏定义，注意“反斜杠”表示下一行接着本行来，是本行的一部分 
	#define _HAS_TYPE_MEM_(parMTpNm) \
	template<typename T, typename U = std::void_t<> > \
	struct HTM_##parMTpNm : std::false_type { }; \
	template<typename T> \
	struct HTM_##parMTpNm<T, std::void_t<typename T::parMTpNm>> : std::true_type { };

	_HAS_TYPE_MEM_(type)
	_HAS_TYPE_MEM_(sizetype)

	//------------------------------------------------------
	//泛化版本
	//template<typename T, typename U = std::void_t<> >
		template<typename T, typename U = int >
	struct HasMember : std::false_type
	{
	};
	//特化版本
	template<typename T>
	struct HasMember<T, std::void_t<decltype(T::m_i)>> : std::true_type
	{
	};

	//------------------------------------------------------
	//泛化版本
	template<typename T, typename U = std::void_t<> >
	struct HasMemFunc : std::false_type
	{
	};
	//特化版本
	template<typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc())>> : std::true_type
	{
	};

}
namespace _nmsp2
{
	class ACPABL
	{
	};

	class BCPABL
	{
	public:
		BCPABL& operator= (const BCPABL& tmpobj)
		{
			return *this;
		};
	};

	class CCPABL
	{
	public:
		CCPABL& operator= (const CCPABL& tmpobj) = delete;
	};

	//-------------------------------------------------
	//泛化版本
	template<typename T, typename U = std::void_t<>>
	struct IsCopyAssignable : std::false_type
	{
	};

	//特化版本
	template<typename T>
	struct IsCopyAssignable<T, std::void_t<decltype(std::declval<T&>() = std::declval<const T&>())> > : std::true_type
	{
	};

}
namespace _nmsp3
{
	//泛化版本
	template<typename T, typename U, typename V = std::void_t<>>  //T,U,V都可以省略不写，变成template<typename, typename, typename=std::void_t<>>
	struct IfCanAdd : std::false_type
	{
	};

	//特化版本
	template<typename T, typename U>
	struct IfCanAdd<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type
	{
	};

	/*
	template<typename T, typename U>
	struct VecAddResult
	{
		//using type = decltype(T() + U());
		using type = decltype(std::declval<T>() + std::declval<U>());
	};*/
	//泛化版本
	template<typename T, typename U, bool ifcando = IfCanAdd<T, U>::value>
	struct VecAddResult
	{
		using type = decltype(std::declval<T>() + std::declval<U>());
	};

	//特化版本
	template<typename T, typename U>
	struct VecAddResult<T, U, false>
	{
	};


	template<typename T, typename U>
	using VecAddResult_t = typename VecAddResult<T, U>::type;

		
	template<typename T, typename U>
	//std::vector<T> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2);
	//std::vector< typename VecAddResult<T, U>::type > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	std::vector< VecAddResult_t<T, U> > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	{
		//随便写几句代码
		//std::vector<  typename VecAddResult<T, U>::type  > tmpvec;
		std::vector<  VecAddResult_t<T, U>  > tmpvec;
		return tmpvec;

	}

	//--------------------
	struct elemC
	{
		elemC(int tmpvalue); //带一个参数的构造函数
		elemC operator+(const elemC& tmppar); //重载加法运算符以支持加法操作,VecAddResult中会用到
	};


}


int main()
{	
	/*
	cout << _nmsp1::HasTypeMem<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasTypeMem<_nmsp1::HaveInnerType>::value << endl;

	cout << _nmsp1::HTM_type<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HTM_type<_nmsp1::HaveInnerType>::value << endl;
	cout << _nmsp1::HTM_sizetype<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HTM_sizetype<_nmsp1::HaveInnerType>::value << endl;
	*/
	
	/*cout << _nmsp1::HasMember<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMember<_nmsp1::HaveInnerType>::value << endl; */
		
	/*cout << _nmsp1::HasMemFunc<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMemFunc<_nmsp1::HaveInnerType>::value << endl;*/

	/*
	_nmsp2::ACPABL aobj1;
	_nmsp2::ACPABL aobj2;
	aobj2 = aobj1;

	_nmsp2::BCPABL bobj1;
	_nmsp2::BCPABL bobj2;
	bobj2 = bobj1;

	//_nmsp2::CCPABL cobj1;
	//_nmsp2::CCPABL cobj2;
	//cobj2 = cobj1;

	cout << "int: " << std::is_copy_assignable<int>::value << endl;
	cout << "ACPABL: " << std::is_copy_assignable<_nmsp2::ACPABL>::value << endl;
	cout << "BCPABL: " << std::is_copy_assignable<_nmsp2::BCPABL>::value << endl;
	cout << "CCPABL: " << std::is_copy_assignable<_nmsp2::CCPABL>::value << endl;
	*/

	/*
	cout << "int: " << _nmsp2::IsCopyAssignable<int>::value << endl;
	cout << "ACPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::ACPABL>::value << endl;
	cout << "BCPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::BCPABL>::value << endl;
	cout << "CCPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::CCPABL>::value << endl;*/


	int i = int();  //其实就是定义一个int类型变量，而且这种定义方式会把i初值设置为0。
	i = 5;
	double j = double(); //其实就是定义一个double类型变量，而且这种定义方式会把j初值设置为0.0
	j = 13.6;

	std::vector<_nmsp3::elemC> veca;
	std::vector<_nmsp3::elemC> vecb;
	veca + vecb; //会调用全局的operator+(......)函数模板


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
