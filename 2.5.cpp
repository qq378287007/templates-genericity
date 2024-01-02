#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
using namespace std;

namespace ns1
{
	class Human
	{
	public:
		virtual void eat()
		{
			cout << "人类以米饭和面食为主!" << endl;
		}
		virtual ~Human() {} // 作为父类存在时一般应该书写虚析构函数
	};

	class Men : public Human
	{
	public:
		virtual void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};

	class Women : public Human
	{
	public:
		virtual void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};
}
namespace ns2
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

	template <typename T>
	void eatTmpl(T &obj)
	{
		obj.eat();
	}
}

int main()
{
#if 1
	using namespace ns1;
	Men objmen;
	Women objwomen;
	// 父类引用(指针)绑定（指向）子类对象，以表现多态
	Human &yinbase1 = objmen;
	Human *yinbase2 = &objwomen;
	yinbase1.eat();
	yinbase2->eat();
#endif

#if 0
	using namespace ns2;
	Men objmen;
	Women objwomen;
	eatTmpl(objmen);
	eatTmpl(objwomen);
#endif

	cout << "Over!\n";
	return 0;
}
