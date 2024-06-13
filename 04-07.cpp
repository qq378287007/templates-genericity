#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
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

	// 向integer_sequence末尾插入元素：泛化版本
	template <typename INTSEQ, unsigned int NewElem> // INTSEQ代表整个std::integer_sequence<......>类型
	struct IntSeq_PushBack;

	// 向integer_sequence末尾插入元素：特化版本（泛化版本一般要求可变参放在最后，特化版本一般无此要求）
	template <typename T, unsigned int... Elems, unsigned int NewElem>
	struct IntSeq_PushBack<std::integer_sequence<T, Elems...>, NewElem>
	{
		using type = std::integer_sequence<T, Elems..., NewElem>;
	};

	// 向integer_sequence开头插入元素：泛化版本
	template <typename INTSEQ, unsigned int NewElem>
	struct IntSeq_PushFront;

	// 向integer_sequence开头插入元素：特化版本
	template <typename T, unsigned int... Elems, unsigned int NewElem>
	struct IntSeq_PushFront<std::integer_sequence<T, Elems...>, NewElem>
	{
		using type = std::integer_sequence<T, NewElem, Elems...>;
	};

	// 泛化版本
	template <typename T, unsigned int N>
	struct Integer_Sequence
	{
		// 依次遍历出4,3,2,1，应该往末尾插入元素，所以还应该引入IntSeq_PushBack操作
		using type = typename IntSeq_PushBack<typename Integer_Sequence<T, N - 1>::type, N - 1>::type; // 这里理解成函数调用，把type理解成所调用的函数名
	};

	// 特化版本
	template <typename T>
	struct Integer_Sequence<T, 1> // 这里是1，意味着递归到1即可
	{
		using type = std::integer_sequence<T, 0>; // 这里是0，注意
	};

	// 定义别名模板
	template <typename T, unsigned int N>
	using Integer_Sequence_T = typename Integer_Sequence<T, N>::type;

	//---------------------------
	// 泛化版本
	template <typename T, unsigned int N, unsigned int Count = 1> // 从1开始记数
	struct Integer_Sequence_Reverse
	{
		using type = typename IntSeq_PushFront<typename Integer_Sequence_Reverse<T, N - 1>::type, N - Count>::type;
	};

	// 特化版本
	template <typename T, unsigned int N>
	struct Integer_Sequence_Reverse<T, N, N>
	{
		using type = std::integer_sequence<T, N - 1>;
	};

	// 定义别名模板
	template <typename T, unsigned int N>
	using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

	//---------------------------
	// 泛化版本
	template <std::size_t Num, std::size_t RepeatTime, typename INTSEQ = std::integer_sequence<std::size_t>>
	class Repeat_Integer;

	// 特化版本1
	template <std::size_t Num, std::size_t RepeatTime, std::size_t... index>
	class Repeat_Integer<Num, RepeatTime, std::integer_sequence<std::size_t, index...>> : public Repeat_Integer<Num, RepeatTime - 1, std::integer_sequence<std::size_t, index..., Num>>
	{
	};

	// 特化版本2（用于结束递归）
	template <std::size_t Num, std::size_t... index>
	class Repeat_Integer<Num, 0, std::integer_sequence<std::size_t, index...>>
	{
	public:
		using type = std::integer_sequence<std::size_t, index...>;
	};

	// 定义别名模板
	template <std::size_t Num, std::size_t RepeatTime>
	using Repeat_Integer_T = typename Repeat_Integer<Num, RepeatTime>::type;

}

int main()
{
	make_integer_sequence<int, 5> tmpobj;
	cout << "type of tmpobj: " << type_id_with_cvr<decltype(tmpobj)>().pretty_name() << endl;

	make_index_sequence<4> tmpobj2;
	cout << "type of tmpobj2: " << type_id_with_cvr<decltype(tmpobj2)>().pretty_name() << endl;

	// ns1::Integer_Sequence_T<int, 4> tmpobj3;
	// cout << "type of tmpobj3: " << type_id_with_cvr<decltype(tmpobj3)>().pretty_name() << endl;

	//ns1::Integer_Sequence_Reverse_T<int, 4> tmpobj4;
	//cout << "type of tmpobj4: " << type_id_with_cvr<decltype(tmpobj4)>().pretty_name() << endl;

	//ns1::Repeat_Integer<1, 4>::type tmpobj5; // 定义别名模板可写成Repeat_Integer_T<1,4> tmpobj5;
	//cout << "type of tmpobj5: " << type_id_with_cvr<decltype(tmpobj5)>().pretty_name() << endl;

	//ns1::Repeat_Integer<1, 4, std::integer_sequence<std::size_t, 12, 18, 19>>::type tmpobj6; // 这里为Repeat_Integer增加了第三个模板参数std::integer_sequence<...>
	//cout << "type of tmpobj6: " << type_id_with_cvr<decltype(tmpobj6)>().pretty_name() << endl;

	cout << "Over!\n";
	return 0;
}
