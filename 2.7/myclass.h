
#ifndef __MYCLASS_H__
#define __MYCLASS_H__

template <typename T>
class MYClass
{
public:
	void func();
};

template <typename T>
// void MYClass::func()
void MYClass<T>::func()
{
	std::cout << "MYClass::func成员函数执行了!" << std::endl;
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
	std::cout << "MYClass<int>::func成员函数执行了!" << std::endl;
}

#endif
