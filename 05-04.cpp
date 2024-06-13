#include <iostream>
#include <vector>
#include <list>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	// SumFixedTraits类模板
	template <typename T>
	struct SumFixedTraits;

	template <>
	struct SumFixedTraits<char>
	{
		using sumT = int;
		static sumT initValue() { return 0; }
	};

	template <>
	struct SumFixedTraits<int>
	{
		using sumT = __int64;
		static sumT initValue() { return 0; }
	};

	template <>
	struct SumFixedTraits<double>
	{
		using sumT = double;
		static sumT initValue() { return 0.0; }
	};

	// funcsum函数模板
	template <typename T, typename U = SumFixedTraits<T>>
	auto funcsum(const T *begin, const T *end)
	{
		// using sumT = typename SumFixedTraits<T>::sumT;  本行不再需要
		// sumT sum = SumFixedTraits<T>::initValue();  本行不再需要
		typename U::sumT sum = U::initValue();
		for (;;)
		{
			sum += (*begin);
			if (begin == end)
				break;
			++begin;
		}
		return sum;
	}
}

int main()
{
	char mychararray[] = "abc";
	cout << (int)(ns1::funcsum(&mychararray[0], &mychararray[2])) << endl;

	cout << "Over!\n";
	return 0;
}
