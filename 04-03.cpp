#include <iostream>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	// template<typename...Args>
	// using void_t = void;

	struct NoInnerType
	{
		int m_i;
	};
	struct HaveInnerType
	{
		using type = int;
		void myfunc() {}
	};

	// 泛化版本
	template <typename T, typename U = std::void_t<>>
	struct HasTypeMem : std::false_type // struct默认是public继承，class默认是private继承
	{
	};

	// 特化版本
	template <typename T>
	struct HasTypeMem<T, std::void_t<typename T::type>> : std::true_type
	{
	};

// 带参数的宏定义，注意“反斜杠”表示下一行接着本行来，是本行的一部分
#define _HAS_TYPE_MEM_(parMTpNm)                                                 \
	template <typename T, typename U = std::void_t<>>                            \
	struct HTM_##parMTpNm : std::false_type                                      \
	{                                                                            \
	};                                                                           \
	template <typename T>                                                        \
	struct HTM_##parMTpNm<T, std::void_t<typename T::parMTpNm>> : std::true_type \
	{                                                                            \
	};

	_HAS_TYPE_MEM_(type)
	_HAS_TYPE_MEM_(sizetype)

	//------------------------------------------------------
	// 泛化版本
	// template<typename T, typename U = std::void_t<> >
	template <typename T, typename U = int>
	struct HasMember : std::false_type
	{
	};
	// 特化版本
	template <typename T>
	struct HasMember<T, std::void_t<decltype(T::m_i)>> : std::true_type
	{
	};

	//------------------------------------------------------
	// 泛化版本
	template <typename T, typename U = std::void_t<>>
	struct HasMemFunc : std::false_type
	{
	};
	// 特化版本
	template <typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc())>> : std::true_type
	{
	};
}

namespace ns2
{
	class ACPABL
	{
	};

	class BCPABL
	{
	public:
		BCPABL &operator=(const BCPABL &tmpobj)	{	return *this;	};
	};

	class CCPABL
	{
	public:
		CCPABL &operator=(const CCPABL &tmpobj) = delete;
	};

	// 泛化版本
	template <typename T, typename U = std::void_t<>>
	struct IsCopyAssignable : std::false_type
	{
	};

	// 特化版本
	template <typename T>
	struct IsCopyAssignable<T, std::void_t<decltype(std::declval<T &>() = std::declval<const T &>())>> : std::true_type
	{
	};
}

namespace ns3
{
	// 泛化版本
	template <typename T, typename U, typename V = std::void_t<>> // T,U,V都可以省略不写，变成template<typename, typename, typename=std::void_t<>>
	struct IfCanAdd : std::false_type
	{
	};

	// 特化版本
	template <typename T, typename U>
	struct IfCanAdd<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type
	{
	};

	/*
	template<typename T, typename U>
	struct VecAddResult
	{
		//using type = decltype(T() + U());
		using type = decltype(std::declval<T>() + std::declval<U>());
	};
	*/
	// 泛化版本
	template <typename T, typename U, bool ifcando = IfCanAdd<T, U>::value>
	struct VecAddResult
	{
		using type = decltype(std::declval<T>() + std::declval<U>());
	};

	// 特化版本
	template <typename T, typename U>
	struct VecAddResult<T, U, false>
	{
	};

	template <typename T, typename U>
	using VecAddResult_t = typename VecAddResult<T, U>::type;

	template <typename T, typename U>
	// std::vector<T> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2);
	// std::vector< typename VecAddResult<T, U>::type > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	std::vector<VecAddResult_t<T, U>> operator+(std::vector<T> const &vec1, std::vector<U> const &vec2)
	{
		// 随便写几句代码
		// std::vector<  typename VecAddResult<T, U>::type  > tmpvec;
		std::vector<VecAddResult_t<T, U>> tmpvec;
		return tmpvec;
	}

	struct elemC
	{
		elemC(int tmpvalue);				  // 带一个参数的构造函数
		elemC operator+(const elemC &tmppar); // 重载加法运算符以支持加法操作,VecAddResult中会用到
	};
}

int main()
{
	/*
	cout << ns1::HasTypeMem<ns1::NoInnerType>::value << endl;
	cout << ns1::HasTypeMem<ns1::HaveInnerType>::value << endl;

	cout << ns1::HTM_type<ns1::NoInnerType>::value << endl;
	cout << ns1::HTM_type<ns1::HaveInnerType>::value << endl;
	cout << ns1::HTM_sizetype<ns1::NoInnerType>::value << endl;
	cout << ns1::HTM_sizetype<ns1::HaveInnerType>::value << endl;
	*/

	/*cout << ns1::HasMember<ns1::NoInnerType>::value << endl;
	cout << ns1::HasMember<ns1::HaveInnerType>::value << endl; */

	/*cout << ns1::HasMemFunc<ns1::NoInnerType>::value << endl;
	cout << ns1::HasMemFunc<ns1::HaveInnerType>::value << endl;*/

	/*
	ns2::ACPABL aobj1;
	ns2::ACPABL aobj2;
	aobj2 = aobj1;

	ns2::BCPABL bobj1;
	ns2::BCPABL bobj2;
	bobj2 = bobj1;

	//ns2::CCPABL cobj1;
	//ns2::CCPABL cobj2;
	//cobj2 = cobj1;

	cout << "int: " << std::is_copy_assignable<int>::value << endl;
	cout << "ACPABL: " << std::is_copy_assignable<ns2::ACPABL>::value << endl;
	cout << "BCPABL: " << std::is_copy_assignable<ns2::BCPABL>::value << endl;
	cout << "CCPABL: " << std::is_copy_assignable<ns2::CCPABL>::value << endl;
	*/

	/*
	cout << "int: " << ns2::IsCopyAssignable<int>::value << endl;
	cout << "ACPABL: " << ns2::IsCopyAssignable<ns2::ACPABL>::value << endl;
	cout << "BCPABL: " << ns2::IsCopyAssignable<ns2::BCPABL>::value << endl;
	cout << "CCPABL: " << ns2::IsCopyAssignable<ns2::CCPABL>::value << endl;*/

	/*
		int i = int();  //其实就是定义一个int类型变量，而且这种定义方式会把i初值设置为0。
		i = 5;
		double j = double(); //其实就是定义一个double类型变量，而且这种定义方式会把j初值设置为0.0
		j = 13.6;

		std::vector<ns3::elemC> veca;
		std::vector<ns3::elemC> vecb;
		veca + vecb; //会调用全局的operator+(......)函数模板
	*/

	cout << "Over!\n";
	return 0;
}
