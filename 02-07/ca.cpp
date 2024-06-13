#include "ca.h"

template void myfunc<int>(int, int); // 函数模板实例化定义，编译器会为其生成实例化代码
template struct A<float>;            // 这叫"实例化定义"，只有一个.cpp文件里这样写，编译器为其生成代码
