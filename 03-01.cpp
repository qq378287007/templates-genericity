#include <iostream>
#include <vector>
using namespace std;

namespace ns0
{
	void func(const int &abc)
	{
		cout << "void func(const int &abc)" << endl;
	}
	/*
	template <typename T>
	void func(const T &abc)
	{
		cout << "void func<T>(const T &abc)" << endl;
	}
	*/
	template <typename T>
	void func(vector<T> &&param)
	{
		cout << "void func<T>(vector<T> &&param)" << endl;
	}
}

namespace ns1
{
	// void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
	template <typename T>
	void myfunc(T &&tmprv) // 万能引用，注意 &&是属于tmprv类型的一部分，不是T类型的一部分（&&和T类型没有关系）
	// void myfunc(const T &&tmprv) // 有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
	{
		tmprv = 12; // 不管tmprv的类型是左值引用还是右值引用，都可以给tmprv赋值，因为tmprv本身是个左值
		cout << tmprv << endl;
	}
}

namespace ns2
{
	// void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
	template <typename T>
	void myfunc(const T &&tmprv) // 有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
	{
		cout << tmprv << endl;
	}

	template <typename T>
	class mytestc
	{
	public:
		void testfunc(T &&x) {}; // 右值引用(非万能引用)

		template <typename T2>
		void testfunc2(T2 &&x) {} // T2类型独立，和T没关系，万能引用
	};
}
int main()
{
#if 0
	using namespace ns0;
	func(10);
	vector<int> aa = {1};
	func(move(aa)); // 不用move不行。也就是说，用左值当参数传递是不行的
	//func(aa);

	/*ns1::
	ns1::myfunc(10); //正确，右值做实参
	int i = 100;
	ns1::myfunc(i); //错，右值引用不能接(绑)左值
	*/
#endif

#if 0
	using namespace ns1;
	int i = 100;
	myfunc(i); // 左值被传递，因此tmprv是左值引用，也就是类型为int &。执行完毕后，i值变成12
	cout << "i=" << i << endl;

	i = 200;
	myfunc(move(i)); // 右值被传递，因此tmprv是右值引用，也就是类型为int &&。执行完毕后，i值变成12
	cout << "i=" << i << endl;
#endif

#if 1
	using namespace ns2;
	int i = 100;
	myfunc(move(i));
	// myfunc(i); //error，只能传递右值进去

	mytestc<int> mc;
	int j = 100;
	mc.testfunc(move(j));
	// mc.testfunc(j); //error，左值不能绑定到右值引用上

	mytestc<int> myoc;
	myoc.testfunc2(i);	// 左值可以
	myoc.testfunc2(12); // 数字12表示右值也可以
#endif

	cout << "Over!\n";
	return 0;
}
