
#include <iostream>
#include "myclass.h"
using namespace std;

template <typename T>
// void MYClass::func()
void MYClass<T>::func()
{
	cout << "MYClass::func成员函数执行了!" << endl;
}
