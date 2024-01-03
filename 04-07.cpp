// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{
	/*template<class T, T... Ints>
	struct integer_sequence
	{
		using value_type = T;
		static constexpr size_t size() noexcept
		{
			return sizeof...(Ints);
		}
	};*/

	//向integer_sequence末尾插入元素：泛化版本
	template<typename INTSEQ, unsigned int NewElem> //INTSEQ代表整个std::integer_sequence<......>类型
	struct IntSeq_PushBack;

	//向integer_sequence末尾插入元素：特化版本（泛化版本一般要求可变参放在最后，特化版本一般无此要求）
	template<typename T, unsigned int... Elems, unsigned int NewElem>
	struct IntSeq_PushBack <  std::integer_sequence<T, Elems...>, NewElem  >
	{
		using type = std::integer_sequence<T, Elems..., NewElem>;
	};

	//向integer_sequence开头插入元素：泛化版本
	template<typename INTSEQ, unsigned int NewElem>
	struct IntSeq_PushFront;

	//向integer_sequence开头插入元素：特化版本
	template<typename T, unsigned int... Elems, unsigned int NewElem>
	struct IntSeq_PushFront <  std::integer_sequence<T, Elems...>, NewElem  >
	{
		using type = std::integer_sequence<T, NewElem, Elems...>;
	};
	
	//泛化版本
	template<typename T, unsigned int N>
	struct Integer_Sequence
	{
		//依次遍历出4,3,2,1，应该往末尾插入元素，所以还应该引入IntSeq_PushBack操作
		using type = typename IntSeq_PushBack<typename Integer_Sequence<T, N - 1>::type, N - 1 >::type; //这里理解成函数调用，把type理解成所调用的函数名
	};

	//特化版本
	template<typename T>
	struct Integer_Sequence<T, 1> //这里是1，意味着递归到1即可
	{
		using type = std::integer_sequence<T, 0>;  //这里是0，注意
	};

	//定义别名模板
	template<typename T, unsigned int N>
	using Integer_Sequence_T = typename Integer_Sequence<T, N>::type;


	//---------------------------
	//泛化版本
	template<typename T, unsigned int N, unsigned int Count = 1> //从1开始记数
	struct Integer_Sequence_Reverse
	{
		using type = typename IntSeq_PushFront<typename
			Integer_Sequence_Reverse<T, N - 1>::type, N - Count >::type;
	};

	//特化版本
	template<typename T, unsigned int N>
	struct Integer_Sequence_Reverse<T, N, N>
	{
		using type = std::integer_sequence<T, N - 1>;
	};

	//定义别名模板
	template<typename T, unsigned int N>
	using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

	//---------------------------
	//泛化版本
	template<std::size_t Num, std::size_t RepeatTime, typename INTSEQ = std::integer_sequence<std::size_t> >
	class Repeat_Integer;

	//特化版本1
	template<std::size_t Num, std::size_t RepeatTime, std::size_t... index>
	class Repeat_Integer<Num, RepeatTime, std::integer_sequence<std::size_t, index...> > : public Repeat_Integer<Num, RepeatTime - 1, std::integer_sequence<std::size_t, index..., Num>>
	{
	};

	//特化版本2（用于结束递归）
	template<std::size_t Num, std::size_t... index>
	class Repeat_Integer<Num, 0, std::integer_sequence<std::size_t, index...>>
	{
	public:
		using type = std::integer_sequence<std::size_t, index...>;
	};

	//定义别名模板
	template<std::size_t Num, std::size_t RepeatTime>
	using Repeat_Integer_T = typename Repeat_Integer<Num, RepeatTime>::type;

}



int main()
{
	std::make_integer_sequence<int, 5> tmpobj;
	cout << "tmpobj的类型为：" << typeid(decltype(tmpobj)).name() << endl;

	make_index_sequence<4> tmpobj2;
	cout << "tmpobj2的类型为：" << typeid(decltype(tmpobj2)).name() << endl;

	_nmsp1::Integer_Sequence_T<int, 4> tmpobj3;
	cout << "tmpobj3的类型为：" << typeid(decltype(tmpobj3)).name() << endl;

	_nmsp1::Integer_Sequence_Reverse_T<int, 4> tmpobj4;
	cout << "tmpobj4的类型为：" << typeid(decltype(tmpobj4)).name() << endl;


	_nmsp1::Repeat_Integer<1, 4>::type tmpobj5; //定义别名模板可写成Repeat_Integer_T<1,4> tmpobj5;
	cout << "tmpobj5的类型为：" << typeid(decltype(tmpobj5)).name() << endl;

	_nmsp1::Repeat_Integer<1, 4, std::integer_sequence<std::size_t, 12, 18, 19>>::type tmpobj6; //这里为Repeat_Integer增加了第三个模板参数std::integer_sequence<...>
	cout << "tmpobj6的类型为：" << typeid(decltype(tmpobj6)).name() << endl;

	
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
