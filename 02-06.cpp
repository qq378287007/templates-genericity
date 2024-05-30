#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <string>
using namespace std;

namespace ns1
{
	template <typename T> // T代表着派生类
	class Base			  // Base是类模板
	{
	public:
		void asDerived()
		{
			T &derived = static_cast<T &>(*this);
			derived.myfunc(); // 调用派生类的成员函数
		}

	private:
		Base(){};
		friend T;
	};

	class Derived1 : public Base<Derived1> // Derived1是普通类
	{
	public:
		void myfunc()
		{
			cout << "Derived1::myfunc()" << endl;
		}
	};

	template <typename T>
	class Derived2 : public Base<Derived2<T>> // Derived2是类模板
	{
	public:
		void myfunc()
		{
			cout << "Derived2<T>::myfunc()" << endl;
		}
	};

	// class Derived3 : public Base<Derived1>
	class Derived3 : public Base<Derived3>
	{
	};

	template <typename T>
	struct shape
	{
		// 不写成友元而写成全局的operator==也可以，但要注意格式就应该是：
		// template <typename T>  bool operator==(const shape<T>& obj1, const shape<T>& obj2){......}
		friend bool operator==(const shape<T> &obj1, const shape<T> &obj2)
		{
			const T &objtmp1 = static_cast<const T &>(obj1);
			const T &objtmp2 = static_cast<const T &>(obj2);
			return (!(objtmp1 < objtmp2) && !(objtmp2 < objtmp1));
		}
	};
	struct square : public shape<square>
	{
		int sidelength; // 边长
	};

	// 类外运算符重载可以这样写
	bool operator<(square const &obj1, square const &obj2)
	{
		return (obj1.sidelength < obj2.sidelength);
	}
}
namespace ns2
{
	// 基类模板
	template <typename T>
	class Human
	{
	public:
		const T &toChild() const
		{
			return static_cast<const T &>(*this);
		}

		T &toChild()
		{
			return static_cast<T &>(*this);
		}

		void parenteat()
		{
			toChild().eat();
		}

	private:
		Human(){};
		friend T;
	};

	class Men : public Human<Men>
	{
	public:
		void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};

	class Women : public Human<Women>
	{
	public:
		void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};

	template <typename T>
	void myHumanFuncTest(Human<T> &tmpobj)
	{
		tmpobj.parenteat();
	}
}
namespace ns3
{
	// struct role
	//{
	//	role(double att = 0.0, double def = 0.0, double life = 100.0)
	//		: m_attack(att), m_defence(def), m_life(life) {}
	//	double m_attack;  // 攻击力
	//	double m_defence; // 防御力
	//	double m_life;	  // 血量（生命值）
	// };

	struct npcattr
	{
		int m_sort;	   // npc种类：0代表无实际功能装饰游戏场景用的NPC，1代表卖服装的，2代表把游戏任务派送给玩家
		string m_lang; // 记录自言自语的一句话的内容
	};

	// struct role_npc : role
	//{
	//	role_npc(double att, double def, double life, int sort, string lang)
	//		: role(att, def, life), m_strucattr{sort, lang} {}
	//	npcattr m_strucattr;
	// };

	struct playerattr
	{
		int m_strength;		// 力量
		int m_agile;		// 敏捷
		int m_constitution; // 体质
	};

	// struct role_player : role
	//{
	//	role_player(double att, double def, double life, int sth, int agi, int cons)
	//		: role(att, def, life), m_strucattr{sth, agi, cons} {}
	//	playerattr m_strucattr;
	// };

	//-----------------------------------------
	template <typename... T>
	class role : public T... // 把传入的模板参数当做该类模板的父类
	{
	public:
		role() : T()..., m_attack(0.0), m_defence(0.0), m_life(100.0) {}
		role(double att, double def, double life) : T()..., m_attack(att), m_defence(def), m_life(life) {}

	public:
		double m_attack;  // 攻击力
		double m_defence; // 防御力
		double m_life;	  // 血量（生命值）
	};

	// template<typename T>
	template <typename... T>
	class family
	{
	public:
		// vector<role> m_members;
		// vector<T> m_members;
		vector<role<T...>> m_members;
	};

	using role_npc = role<npcattr>;
	using role_mixnpc = role<npcattr, playerattr>;
}
namespace ns4
{
	template <typename... T>
	class Base : public T...
	{
	public:
		void myfunc() { cout << "Base<typename... T>::myfunc()" << endl; }
	};

	template <typename... T>
	class Derived : public Base<T...>
	{
	public:
		void myfunc() { cout << "Derived<typename... T>::myfunc()" << endl; }
	};

	class A
	{
	};

	class AVir
	{
	public:
		virtual void myfunc() {}
	};
}
namespace ns5
{
	class A
	{
	protected:
		~A() {}
	};
	class B : public A
	{
	};
}

int main()
{
#if 0
	using namespace ns1;
	Derived1 myd;
	myd.asDerived(); // 调用基类的成员函数
	Derived2<int> myd2;
	myd2.asDerived();
	Derived3 myd3;
	// myd3.asDerived();//error

	square objsq1; // 派生类对象
	objsq1.sidelength = 15;
	square objsq2; // 派生类对象
	objsq2.sidelength = 21;
	if (!(objsq1 == objsq2))
		cout << "objsq1 != objsq2" << endl;
	else
		cout << "objsq1 == objsq2" << endl;
#endif

#if 0
	using namespace ns2;
	Men mymen;
	Women mywomen;

	mymen.parenteat();
	mywomen.parenteat();
	cout << "-----------------------" << endl;
	myHumanFuncTest(mymen);
	myHumanFuncTest(mywomen);
#endif

#if 0
	using namespace ns3;
	role_npc mynpc;
	mynpc.m_attack = 15;		  // 攻击
	mynpc.m_defence = 10;		  // 防御
	mynpc.m_life = 120;			  // 血量
	mynpc.m_sort = 1;			  // npc种类
	mynpc.m_lang = "Are You OK?"; // NPC自言自语时所说的话*/
#endif

#if 0
	using namespace ns4;
	Base<A> *pb1 = new Derived<A>; // 父类指针指向子类对象
	pb1->myfunc();
	delete pb1;

	Base<AVir> *pb2 = new Derived<AVir>;
	pb2->myfunc();
	delete pb2;
#endif

#if 1
	using namespace ns5;
	A *pa = new B();
	// delete pa; //编译报错
#endif

	cout << "Over!\n";
	return 0;
}
