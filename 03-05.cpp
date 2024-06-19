#include <iostream>
#include <vector>
using namespace std;

template <typename... Args>
struct myclasst
{
	myclasst() { cout << "myclasst::myclasst(), sizeof...(Args) = " << sizeof...(Args) << endl; }
};

template <typename... Args>
struct myclasst2 : myclasst<Args...>
{
	myclasst2() { cout << "myclasst2::myclasst2(), sizeof...(Args) = " << sizeof...(Args) << endl; }
};

template <typename... Args>
struct myclasst3 : myclasst<Args>...
{
	myclasst3() { cout << "myclasst3::myclasst3(), sizeof...(Args) = " << sizeof...(Args) << endl; }
};

template <typename... Args>
struct myclasst4 : myclasst<Args, char>...
{
	myclasst4() { cout << "myclasst4::myclasst4(), sizeof...(Args) = " << sizeof...(Args) << endl; }
};

template <typename... Args>
struct myclasst5 : myclasst<Args, Args...>...
{
	myclasst5() { cout << "myclasst5::myclasst5(), sizeof...(Args) = " << sizeof...(Args) << endl; }
};

int main()
{
	myclasst2<double, float, int> tmpobj2;
	cout << "*************************\n";

	myclasst3<double, float, int> tmpobj3;
	cout << "*************************\n";

	myclasst4<double, float, int> tmpobj4;
	cout << "*************************\n";

	myclasst5<double, float, int> tmpobj5;
	cout << "*************************\n";

	cout << "Over!\n";
	return 0;
}
