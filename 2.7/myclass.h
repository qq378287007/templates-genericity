
#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <iostream>
using namespace std;

template <typename T>
class MYClass
{
public:
	void func();
};
template <typename T>
void MYClass<T>::func()
{
	cout << "MYClass::func成员函数执行了!" << endl;
}

//-------------------------
// 特化版本
template <>
class MYClass<int>
{
public:
	void func();
};
void MYClass<int>::func() // 这行的前面不需要template <>
{
	cout << "MYClass<int>::func成员函数执行了!" << endl;
}

#endif
