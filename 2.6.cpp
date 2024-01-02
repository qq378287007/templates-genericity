#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
using namespace std;

namespace _nmsp1
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
			cout << "Derived1::myfunc()执行了" << endl;
		}
		//......
	};

	template <typename T>
	class Derived2 : public Base<Derived2<T>> // Derived2是类模板
	{
	};

	// class Derived3 : public Base<Derived1>
	class Derived3 : public Base<Derived3>
	{
	};

	//-----------------------------------
	template <typename T>
	struct shape
	{
		// 不写成友元而写成全局的operator==也可以，但要注意格式就应该是：
		// template <typename T>  bool operator==(const shape<T>& obj1, const shape<T>& obj2){......}
		friend bool operator==(const shape<T> &obj1, const shape<T> &obj2)
		{
			const T &objtmp1 = static_cast<const T &>(obj1);
			const T &objtmp2 = static_cast<const T &>(obj2);
			if (!(objtmp1 < objtmp2) && !(objtmp2 < objtmp1))
				return true;
			return false;
		}
	};
	struct square : public shape<square>
	{
		int sidelength; // 边长
	};

	// 类外运算符重载可以这样写
	bool operator<(square const &obj1, square const &obj2)
	{
		if (obj1.sidelength < obj2.sidelength)
			return true;
		return false;
	}

	//-----------------------------------

}
namespace _nmsp2
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
namespace _nmsp3
{

	// class role
	//{
	// public:
	//	//构造函数
	//	role() :m_attack(0.0), m_defence(0.0), m_life(100.0) {} //初始时攻击力防御力都为0，血量100
	//	role(double att, double def, double life) :m_attack(att), m_defence(def), m_life(life) {}
	// public:
	//	double m_attack;  //攻击力
	//	double m_defence; //防御力
	//	double m_life;    //血量（生命值）
	//	//......其他信息
	// };

	struct npcattr
	{
		int m_sort;			// npc种类：0代表无实际功能装饰游戏场景用的NPC，1代表卖服装的，2代表把游戏任务派送给玩家
		std::string m_lang; // 记录自言自语的一句话的内容
	};

	// class role_npc : public role
	//{
	// public:
	//	//构造函数
	//	role_npc() : role(), m_strucattr{ 0,"" } {}
	//	role_npc(double att, double def, double life, int extraa, int sort, std::string lang) : role(att, def, life), m_strucattr{ sort,lang } {}
	// public:
	//	npcattr m_strucattr;
	// };

	struct playerattr
	{
		int m_strength;		// 力量
		int m_agile;		// 敏捷
		int m_constitution; // 体质
	};

	/*class role_player :public role
	{
	public:
		role_player() :role(), m_strucattr{ 0 } {}
		role_player(double att, double def, double life, int sth, int agi, int cons) : role(att, def, life), m_strucattr{ sth,agi,cons } {}
	public:
		playerattr m_strucattr;
	};*/

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
		// std::vector<role> m_members;
		// std::vector<T> m_members;
		std::vector<role<T...>> m_members;
		//......其他信息，比如家族创建日期等
	};

	using role_npc = role<npcattr>;
	using role_mixnpc = role<npcattr, playerattr>;
}
namespace _nmsp4
{
	template <typename... T>
	class Base : public T...
	{
	public:
		void myfunc()
		{
			cout << "Base::myfunc()执行了!" << endl;
		}
	};

	template <typename... T>
	class Derived : public Base<T...>
	{
	public:
		void myfunc()
		{
			cout << "Derived::myfunc()执行了!" << endl;
		}
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
namespace _nmsp5
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
	/*_nmsp1::Derived1 myd;
	myd.asDerived(); //调用基类的成员函数
	_nmsp1::Derived3 myd3;*/

	/*
	_nmsp1::square objsq1; //派生类对象
	objsq1.sidelength = 15;
	_nmsp1::square objsq2; //派生类对象
	objsq2.sidelength = 21;
	if (!(objsq1 == objsq2))
	{
		cout << "objsq1和objsq2不相等!" << endl;
	}
	else
	{
		cout << "objsq1和objsq2相等!" << endl;
	}*/

	/*
	_nmsp2::Men mymen;
	_nmsp2::Women mywomen;

	mymen.parenteat();
	mywomen.parenteat();
	cout << "-----------------------" << endl;
	myHumanFuncTest(mymen);
	myHumanFuncTest(mywomen);
	*/

	/*
	_nmsp3::role_npc  mynpc;
	mynpc.m_attack = 15;   //攻击
	mynpc.m_defence = 10;  //防御
	mynpc.m_life = 120;    //血量
	mynpc.m_sort = 1;      //npc种类
	mynpc.m_lang = "Are You OK?";  //NPC自言自语时所说的话*/

	/*
	_nmsp4::Base<_nmsp4::A>* pb1 = new _nmsp4::Derived<_nmsp4::A>; //父类指针指向子类对象
	pb1->myfunc();

	_nmsp4::Base<_nmsp4::AVir>* pb2 = new _nmsp4::Derived<_nmsp4::AVir>;
	pb2->myfunc();
	*/

	_nmsp5::A *pa = new _nmsp5::B();
	// delete pa; //编译报错

	cout << "Over!\n";
	return 0;
}
