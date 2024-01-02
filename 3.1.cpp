#include <iostream>
#include <vector>
using namespace std;

namespace ns1
{
	// void func(const int& abc) {}

	// template <typename T>
	// void func(const T& abc) { }

	// void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
	template <typename T>
	// void myfunc(T&& tmprv) //万能引用，注意 &&是属于tmprv类型的一部分，不是T类型的一部分（&&和T类型没有关系）
	void myfunc(const T &&tmprv) // 有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
	{
		// tmprv = 12; // 不管tmprv的类型是左值引用还是右值引用，都可以给tmprv赋值，因为tmprv本身是个左值
		cout << tmprv << endl;
	}

	template <typename T>
	void func(vector<T> &&param) {}

	template <typename T>
	class mytestc
	{
	public:
		void testfunc(T &&x){}; // 右值引用(非万能引用)

		template <typename T2>
		void testfunc2(T2 &&x) {} // T2类型独立，和T没关系，万能引用
	};
}

int main()
{
	/*ns1::func(10);

	ns1::myfunc(10); //正确，右值做实参
	int i = 100;
	ns1::myfunc(i); //错，右值引用不能接(绑)左值

	vector<int> aa = { 1 };
	ns1::func(move(aa)); //不用move不行。也就是说，用左值当参数传递是不行的
	*/

	/*int i = 100;
	ns1::myfunc(i);//左值被传递，因此tmprv是左值引用，也就是类型为int &。执行完毕后，i值变成12
	i = 200;
	ns1::myfunc(move(i)); //右值被传递，因此tmprv是右值引用，也就是类型为int &&。执行完毕后，i值变成12
	*/

	/*int i = 100;
	ns1::myfunc(i); //不可以，只能传递右值进去，必须是myfunc(move(i));
	*/

	/*ns1::mytestc<int> mc;
	int i = 100;
	mc.testfunc(i); //错，左值不能绑定到右值引用上，必须修改为：mc.testfunc(move(i));
	*/

	/*
	ns1::mytestc<int> myoc;
	int i = 10;
	myoc.testfunc2(i); // 左值可以，给个数字3表示右值也可以
	*/

	cout << "Over!\n";
	return 0;
}
