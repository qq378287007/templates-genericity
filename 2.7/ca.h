#ifndef __CAH__
#define __CAH__

#include <iostream>
using namespace std;

template <typename T>
void myfunc(T v1, T v2)
{
	cout << v1 + v2 << endl;
}

template <typename C>
class A
{
public:
	void myfuncpt() { cout << "myfuncpt()执行了" << endl; };

public:
	template <typename T2>
	A(T2 v1, T2 v2);

	template <typename T>
	void myft(T tmpt)
	{
		cout << tmpt << endl;
	}
	C m_ic;
};
template <typename C>
template <typename T2>
A<C>::A(T2 v1, T2 v2)
{
	cout << v1 << v2 << endl;
}

#endif
