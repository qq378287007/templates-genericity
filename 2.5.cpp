// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>

using namespace std;

namespace _nmsp1
{
	class Human
	{
	public:
		virtual void eat()
		{
			cout << "人类以米饭和面食为主!" << endl;
		}
		virtual ~Human() {} //作为父类存在时一般应该书写虚析构函数
	};

	class Men :public Human
	{
	public:
		virtual void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};

	class Women :public Human
	{
	public:
		virtual void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};
}
namespace _nmsp2
{
	class Men
	{
	public:
		void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};
	class Women
	{
	public:
		void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};

	template<typename T>
	void eatTmpl(T& obj)
	{
		obj.eat();
	}
}

int main()
{
	/*
	_nmsp1::Men objmen;
	_nmsp1::Women objwomen;
	//父类引用绑定（指向）子类对象，以表现多态
	_nmsp1::Human& yinbase1 = objmen;
	_nmsp1::Human& yinbase2 = objwomen;
	yinbase1.eat();
	yinbase2.eat();
	*/

	_nmsp2::Men objmen;
	_nmsp2::Women objwomen;
	_nmsp2::eatTmpl(objmen);
	_nmsp2::eatTmpl(objwomen);

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
