#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	template <class T>
	struct remove_all_extents
	{
		using type = T;
	};
	template <class T, std::size_t N>
	struct remove_all_extents<T[N]>
	{
		using type = typename remove_all_extents<T>::type;
	};
	template <class T>
	struct remove_all_extents<T[]>
	{
		using type = typename remove_all_extents<T>::type;
	};
}

int main()
{
	float a[12];
	int b[5][8];
	int c[2][8][9];

	//cout << typeid(std::remove_all_extents<decltype(a)>::type).name() << endl;
	cout << type_id_with_cvr<std::remove_all_extents<decltype(a)>::type>().pretty_name() << endl;
	cout << type_id_with_cvr<std::remove_all_extents<decltype(b)>::type>().pretty_name() << endl;
	cout << type_id_with_cvr<std::remove_all_extents<decltype(c)>::type>().pretty_name() << endl;

	cout << "Over!\n";
	return 0;
}
