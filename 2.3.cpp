// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

namespace _nmsp1
{
	template <typename U> class B; //类模板B声明

	template <typename T>
	class A
	{
		//友元类
		friend class B<long>; //不需要任何public、private等修饰符修饰

	private:
		int data;
	};

	template <typename U>
	class B
	{
	public:
		void callBAF()
		{
			A<int> atmpobj;
			atmpobj.data = 5;
			std::cout << atmpobj.data << std::endl;
		}
	};

}
namespace _nmsp2
{
	template <typename T>
	class A
	{
		//friend class B<long>;
		template<typename> friend class B; //友元类模板
	private:
		int data;
	};

	template <typename U>
	class B
	{
	public:
		void callBAF()
		{
			A<int> atmpobj;
			atmpobj.data = 5;
			std::cout << atmpobj.data << std::endl;
		}
	};

}
namespace _nmsp3
{
	template <typename T>
	class A2
	{
		friend  T;
		//friend class CF;
	private:
		int data;
	};

	class CF
	{
	public:
		void callCFAF()
		{
			A2<CF> aobj1;
			aobj1.data = 12;
			std::cout << aobj1.data << std::endl;

			/*A2<int> aobj2;
			aobj2.data = 12;*/

		}
	};

}
namespace _nmsp4
{
	//template<typename U, typename V> void func(U val1, V val2);

	template<typename Z>
	class Men
	{
		friend void func2(Men<Z>& tmpmen)
		{
			for (int i = 0; i < 1; ++i)
			tmpmen.funcmen();
		}
		
		//friend void func<int, int>(int, int);
		//friend void func<int>(int, int);
	/*	friend void func<>(int, int);
		friend void func<>(float, int);
		friend void func<>(int, float);*/

		template<typename U, typename V>friend void func(U val1, V val2);

	private:
		void funcmen() const
		{
			std::cout << "Men:funcmen被调用了" << std::endl;
		};
	};
	

	template<typename U, typename V>
	void func(U val1, V val2)
	{
		/*cout << "val1 = " << val1 << endl;
		cout << "val2 = " << val2 << endl;*/

		//Men mymen;
		Men<int> mymen;
		mymen.funcmen(); //这行报错

	};

	template<>
	void func(int val1, double val2)
	{
		Men<int> mymen;
		mymen.funcmen();
	}

	


}

int main()
{
	/*
	_nmsp1::B<long> bobj;
	bobj.callBAF();*/

	/*_nmsp2::B<long> bobj;
	bobj.callBAF();
	*/

	/*_nmsp3::CF mycfobj;
	mycfobj.callCFAF();*/
	
	//_nmsp3::A2<_nmsp3::CF> aobj1;
	//aobj1.data = 12;

	//调用func方法很多 
	/*_nmsp4::func(2, 3);
	_nmsp4::func<float>(4.6f, 5); //第一个模板参数指定，第二个模板参数自己能推断出来
	_nmsp4::func<int, float>(4, 5.8f); //完全手工指定模板参数
	_nmsp4::func<int, double>(4, 5.8);*/

	_nmsp4::Men<double> mymen2;
	func2(mymen2);  //直接调用Men类模板中定义的友元函数func2
	_nmsp4::Men<int> mymen3;
	func2(mymen3);

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
