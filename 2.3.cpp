#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;

namespace ns1
{
	// 类模板B声明
	template <typename U>
	class B;

	template <typename T>
	class A
	{
		friend class B<long>; // 友元类, 不需要任何public、private等修饰符修饰
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
			cout << atmpobj.data << endl;
		}
	};

}

namespace ns2
{
	template <typename T>
	class A
	{
		template <typename>
		friend class B; // 友元类模板
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
			cout << atmpobj.data << endl;
		}
	};
}

namespace ns3
{
	template <typename T>
	class A2
	{
		friend T;
		// friend class CF;
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
			cout << aobj1.data << endl;

			// A2<int> aobj2;
			// aobj2.data = 12;
		}
	};
}

namespace ns4
{
	// template<typename U, typename V> void func(U val1, V val2);

	template <typename Z>
	class Men
	{
		friend void func2(Men<Z> &tmpmen)
		{
			for (int i = 0; i < 1; ++i)
				tmpmen.funcmen();
		}

		// friend void func<int, int>(int, int);
		// friend void func<int>(int, int);
		/*	friend void func<>(int, int);
			friend void func<>(float, int);
			friend void func<>(int, float);*/

		template <typename U, typename V>
		friend void func(U val1, V val2);

	private:
		void funcmen() const
		{
			cout << "Men:funcmen被调用了" << endl;
		};
	};

	template <typename U, typename V>
	void func(U val1, V val2)
	{
		/*cout << "val1 = " << val1 << endl;
		cout << "val2 = " << val2 << endl;*/

		// Men mymen;
		Men<int> mymen;
		mymen.funcmen(); // 这行报错
	};

	template <>
	void func(int val1, double val2)
	{
		Men<int> mymen;
		mymen.funcmen();
	}
}

int main()
{
#if 0
	ns1::B<long> bobj;
	bobj.callBAF();
#endif

#if 0
	ns2::B<long> bobj;
	bobj.callBAF();
#endif

#if 0
	using namespace ns3;
	CF mycfobj;
	mycfobj.callCFAF();

	// A2<CF> aobj1;
	// aobj1.data = 12;
#endif

#if 1
	// 调用func方法很多
	/*ns4::func(2, 3);
	ns4::func<float>(4.6f, 5); //第一个模板参数指定，第二个模板参数自己能推断出来
	ns4::func<int, float>(4, 5.8f); //完全手工指定模板参数
	ns4::func<int, double>(4, 5.8);*/

	/*
		ns4::Men<double> mymen2;
		func2(mymen2); // 直接调用Men类模板中定义的友元函数func2
		ns4::Men<int> mymen3;
		func2(mymen3);
	*/
#endif

	cout << "Over!\n";
	return 0;
}