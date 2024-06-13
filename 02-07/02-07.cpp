#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
using namespace std;

#include "ca.h"
#include "myclass.h"

int main()
{
	A<float> a(1, 2);
	A<float> a2(1.1, 2.2);
	a.myft(3); // 3

	A<int> d(6, 7); // int版本的A（A<int>）会被实例化

	MYClass<double> mycls;
	mycls.func();

	MYClass<int> mycls2;
	mycls2.func();

	cout << "Over!\n";
	return 0;
}