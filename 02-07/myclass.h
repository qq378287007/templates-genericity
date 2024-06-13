
#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct MYClass
{
	void func() { cout << "MYClass<T>::func()" << endl; }
};
// template <typename T>
// void MYClass<T>::func() { cout << "MYClass<T>::func()" << endl; }

// 特化版本
template <>
struct MYClass<int>
{
	void func();
};
// 不需要template <>
void MYClass<int>::func() { cout << "MYClass<int>::func()" << endl; }
