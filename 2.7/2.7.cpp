#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>

// #include "myclass.h"
#include "ca.h"

using namespace std;

extern template A<float>;					   // 其他所有.cpp文件都这样写
extern template void myfunc(int &v1, int &v2); // 函数模板实例化声明

namespace _nmsp1
{

}

int main()
{
	/*MYClass mycls;
	mycls.func();
	*/

	/*
	MYClass<int> mycls;
	mycls.func();*/

	A<float> a(1, 2);
	A<float> a2(1.1, 2.2);
	// a.myft(3); //3

	// A<int> d(6, 7); //int版本的A（A<int>）会被实例化
}