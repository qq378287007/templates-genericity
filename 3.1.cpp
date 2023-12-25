// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>

using namespace std;

namespace _nmsp1
{
	//void func(const int& abc) {}

	//template <typename T>
	//void func(const T& abc) { }

	//void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
	template <typename T>
	//void myfunc(T&& tmprv) //万能引用，注意 &&是属于tmprv类型的一部分，不是T类型的一部分（&&和T类型没有关系）
	void myfunc(const T&& tmprv) //有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
	{
		//tmprv = 12;  //不管tmprv的类型是左值引用还是右值引用，都可以给tmprv赋值，因为tmprv本身是个左值
		cout << tmprv << endl;
		return;
	}
	
	template<typename T>
	void func(std::vector<T>&& param) {}

	template <typename T>
	class mytestc
	{
	public:
		void testfunc(T&& x) {}; //这个不是万能引用，这个是右值引用

		template <typename T2>
		void testfunc2(T2&& x) {} //T2类型是独立的，和T没任何关系，而且x是函数模板形参，类型是推导来的，所以这是个万能 引用

	};


}

int main()
{
	/*_nmsp1::func(10);

	_nmsp1::myfunc(10); //正确，右值做实参 
	int i = 100;
	_nmsp1::myfunc(i); //错，右值引用不能接(绑)左值

	vector<int>aa = { 1 };
	_nmsp1::func(std::move(aa)); //不用std::move不行。也就是说，用左值当参数传递是不行的
	*/

	/*int i = 100;
	_nmsp1::myfunc(i);//左值被传递，因此tmprv是左值引用，也就是类型为int &。执行完毕后，i值变成12
	i = 200;
	_nmsp1::myfunc(std::move(i)); //右值被传递，因此tmprv是右值引用，也就是类型为int &&。执行完毕后，i值变成12
	*/

	/*int i = 100;
	_nmsp1::myfunc(i); //不可以，只能传递右值进去，必须是myfunc(std::move(i));
	*/

	/*_nmsp1::mytestc<int> mc;
	int i = 100;
	mc.testfunc(i); //错，左值不能绑定到右值引用上，必须修改为：mc.testfunc(std::move(i));
	*/

	_nmsp1::mytestc<int> myoc;
	int i = 10;
	myoc.testfunc2(i); //左值可以，给个数字3表示右值也可以


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
