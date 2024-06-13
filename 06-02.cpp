#include <iostream>
using namespace std;

namespace ns1
{
	template <typename T, int U> // T：元素类型，U：数组大小
	inline auto DotProduct(T *array1, T *array2)
	{
		T dpresult = T{}; // 零初始化
		for (int i = 0; i < U; ++i)
			dpresult += array1[i] * array2[i];
		return dpresult;
	}
}
namespace ns2
{
	// 泛化版本
	template <typename T, int U> // T：元素类型，U：数组大小
	struct DotProduct
	{
		static T result(const T *a, const T *b) { return (*a) * (*b) + DotProduct<T, U - 1>::result(a + 1, b + 1); }
	};

	// 特化版本，用于做递归调用的出口
	template <typename T>
	struct DotProduct<T, 0>
	{
		static T result(const T *, const T *) { return T{}; }
	};
}
namespace ns3
{
	/*
		//泛化版本
		template<int x_v, int y_v>
		struct InstantiationObServe
		{
			static const int value = (x_v > y_v) ? InstantiationObServe<x_v - 1, y_v>::value : InstantiationObServe<x_v, x_v>::value; //int可以用auto代替，书写更方便
		};
	*/
	// 泛化版本2
	template <int x_v, int y_v>
	struct InstantiationObServe
	{
		using TmpType = typename std::conditional<(x_v > y_v), InstantiationObServe<x_v - 1, y_v>, InstantiationObServe<x_v, x_v>>::type;
		static const int value = TmpType::value;
	};
	// 特化版本
	template <int x_v>
	struct InstantiationObServe<x_v, x_v>
	{
		static const int value = x_v; // int可以用auto代替，书写更方便
	};
}
namespace ns4
{
	// 泛化版本
	template <int x_v, int y_v>
	struct InstantiationObServe
	{
		using TmpType = typename std::conditional<(x_v > y_v), InstantiationObServe<x_v - 1, y_v>, InstantiationObServe<x_v, x_v>>::type;
		// enum { value = TmpType::value };
		static inline const int value = TmpType::value;
	};
	// 特化版本
	template <int x_v>
	struct InstantiationObServe<x_v, x_v>
	{
		// enum { value = x_v };
		static inline const int value = x_v;
	};

	struct TST
	{
		static const int mystatic = 1;
		// static inline double mystatic2 = 12.6;
		static constexpr double mystatic2 = 12.6;
	};
}

int main()
{
#if 0
	using namespace ns1;

	int a[] = {1, 2, 3};
	int b[] = {4, 5, 6};
	int result = DotProduct<int, 3>(a, b);
	cout << result << endl;
#endif

#if 0
	using namespace ns2;
	int a[] = {1, 2, 3};
	int b[] = {4, 5, 6};
	int result = DotProduct<int, 3>::result(a, b);
	cout << result << endl;

	int a2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int b2[] = {4, 5, 6, 7, 8, 9, 1, 2, 3, 10, 11, 12};
	int result2 = DotProduct<int, 12>::result(a2, b2);
	cout << result2 << endl;
#endif

#if 0
	using namespace ns3;
	cout << InstantiationObServe<6, 4>::value << endl;
#endif

#if 1
	using namespace ns4;
	cout << InstantiationObServe<6, 4>::value << endl;
#endif

	cout << "Over!\n";
	return 0;
}
