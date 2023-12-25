#ifndef __CAH__
#define __CAH__

template <typename T>
void myfunc(T v1, T v2)
{
	std::cout << v1 + v2 << std::endl;
}

template <typename C>
class A
{
public:
	void myfuncpt() { std::cout << "myfuncpt()执行了" << std::endl; };

public:
	template <typename T2>
	A(T2 v1, T2 v2);

	template <typename T>
	void myft(T tmpt)
	{
		std::cout << tmpt << std::endl;
	}
	C m_ic;
};
template <typename C>
template <typename T2>
A<C>::A(T2 v1, T2 v2)
{
	std::cout << v1 << v2 << std::endl;
}

#endif
