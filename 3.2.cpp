#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

//函数模板
template <typename T>
//void myfunc(T& tmprv)
//void myfunc(const T& tmprv)
//void myfunc(T* tmprv)
//void myfunc(T&& tmprv)
//void myfunc(T tmprv)
//template <typename T, unsigned L1>
//void myfunc(T(&tmprv)[L1])
void myfunc(std::initializer_list<T> tmprv)
{
	//tmprv = 15;

	//int& tmpvaluec = tmprv;
	//tmpvaluec = 1200;

	//cout << L1 << endl;

	cout << "---------------------begin------------------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}

template<typename T>
void tf(const T& tmprv) //这里把auto替换成T,上面auto里的xy就相当于这里的tmprv
{
	cout << "---------------------begin------------------------" << endl;;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;;		return;
}


//void mf(int& tmprv) 
//{
//	tmpv = 12;
//}
template <typename T>
void mf(T tmprv)
{
	tmprv = 12;

	cout << "---------------------begin------------------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}

void testFunc() {}

namespace _nmsp1
{

	

}

int main()
{	
	//myfunc(100);

	/* //myfunc(T& tmprv)
	int i = 18;            //一眼看得出来i的类型为int
	const int j = i;       //一眼看得出来j的类型为const int
	const int& k = i;      //一眼看得出来k的类型为const int &

	myfunc(i);            //先猜测一下类型：T=int,tmprv=int &。实际执行结果(编译器推断出来的)：T=int, tmprev = int &，说明猜测正确
	myfunc(j);            //因为j的类型中带个const，所以猜不出来，那么就看实际执行结果：T=int const, tmprev=int const &
	myfunc(k);            //看实际执行结果：T=int const, tmprev=int const &

	//临时范例
	{
		int ii = 1;
		int& jj = i;
		mf(jj); 
		cout << ii << endl;
	}
	*/

	/* //myfunc(const T& tmprv)
	int i = 18;            //一眼看得出来i的类型为int
	const int j = i;      //一眼看得出来j的类型为const int
	const int& k = i;     //一眼看得出来k的类型为const int &

	myfunc(i);            //看实际执行结果：T=int, tmprev=int const & ，tmprev这里多了个const
	myfunc(j);            //看实际执行结果：T=int, tmprev=int const & ，T类型原来的const变没了
	myfunc(k);            //看实际执行结果：T=int, tmprev=int const & ，T类型原来的const变没了
	*/

	/*//myfunc(T* tmprv)
	int i = 18;
	const int* pi = &i;
	myfunc(&i);   //看实际执行结果：T=int,tmprev=int *
	myfunc(pi);   //看实际执行结果：T=int const, tmprev =int const *
	*/

	/*
	int i = 18;         //一眼看得出来i的类型为int
	const int j = i;    //一眼看得出来j的类型为const int
	const int& k = i;   //一眼看得出来k的类型为const int &
	myfunc(i);         //i是左值，看实际执行结果：T=int &，tmprv=int &
	myfunc(j);         //j是左值，看实际执行结果：T=int const &，tmprv=int const &
	myfunc(k);        //k是左值(只要能往等号左边放的都是左值，就是算是右值引用，也是个左值）,看实际执行结果：T=int const &，tmprv=int const &
	myfunc(100);      //100是右值，看实际执行结果：T=int，tmprv=int &&
	*/

	/*
	int i = 18;           //一眼看得出来i的类型为int
	const int j = i;     //一眼看得出来j的类型为const int
	const int& k = i;    //一眼看得出来k的类型为const int &
	myfunc(i); //看实际执行结果：T=int,tmprv=int
	myfunc(j); //看实际执行结果：T=int,tmprv=int，const属性没传递，因为对方是新副本
	myfunc(k); //看实际执行结果：T=int,tmprv=int，const属性没传递，因为对方是新副本
	*/

	/*char mystr[] = "I Love China!";
	const char* const p = mystr;
	myfunc(p);        //看实际执行结果：T=char const *,tmprv=char const *
	*/

	/*
	int m = 180;
	myfunc(std::ref(m));
	cout << "m=" << m << endl;*/

	/*const char mystr[] = "I Love China!";
	myfunc(mystr); //看实际执行结果：T=char const *,tmprv=char const *，按指针方式处理数组了
	*/

	/*
	const char mystr[] = "I Love China!";
	myfunc(mystr);//看实际执行结果：T=char const [14], tmprv =char const (&)[14]
	*/

	//myfunc(testFunc);
	//myfunc({ 1, 2, 3 });

	//auto x = 27;    //x = int,auto = int

	
	auto x = 27;    //估计：x = int,auto = int
	const auto x2 = x;  //估计：x2 = const int,auto =int
	const auto& xy = x; //这个auto并不是传值方式，估计：xy = const int &,auto = int
	auto xy2 = xy; //估计：xy2 = int,auto = int。这种应该是属于传值方式，传值方式时：引用类型会被抛弃,const属性会被抛弃，xy2是个新副本，这一点和函数模板类型推断非常类似
	//using boost::typeindex::type_id_with_cvr;
	//cout << "xy2=" << type_id_with_cvr<decltype(xy2)>().pretty_name() << endl;
	tf(x);

	auto& xy3 = xy; //估计：xy3 = const int &,auto = const int，针对auto类型：引用会被丢弃，const属性会被保留
	auto y = new auto (100);//new一块内存，内存的初始值给100。估计：y = int *,auto = int *。auto可以用于new操作符
	const auto* xp = &x; //估计：xp = const int *,auto = int
	auto* xp2 = &x; //估计：xp2 = int *,auto = int
	auto xp3 = &x; //估计：xp3 = int *，auto = int *; xp3不声明为指针，也能推导出指针类型

	auto&& wnyy0 = 222;  //估计：这是万能引用，222是右值，所以：auto = int,wnyy0 = int&&（右值引用）
	auto&& wnyy1 = x;//估计：这是万能引用，x是左值，所以：auto=int&，wnyy1=int&
	auto&& wnyy2 = x2;   //编译器推断：这是万能引用，x2是左值，则auto是int const & ，wnyy2也是int const &

}
