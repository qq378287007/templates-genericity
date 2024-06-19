#include <iostream>
#include <initializer_list>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

void testFunc() {}

void mf(int &tmprv) { tmprv = 12; }
template <typename T>
void mf2(T &tmprv) { tmprv = 12; }
template <typename T>
void mf3(T tmprv) { tmprv = 12; }

template <typename T>
//  void myfunc(const T &tmprv)
//  void myfunc(T &tmprv)
//  void myfunc(T *tmprv)
//  void myfunc(T &&tmprv)
//  void myfunc(T tmprv)
void myfunc(initializer_list<T> tmprv)
{
	cout << "---------------------begin------------------------" << endl;
	cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;					 // 显示T类型
	cout << "tmprv = " << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; // 显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}

template <typename T, unsigned L1>
void myfunc2(T (&tmprv)[L1])
{
	cout << "---------------------begin------------------------" << endl;
	cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;					 // 显示T类型
	cout << "tmprv = " << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; // 显示tmprv类型
	cout << "L1 = " << L1 << endl;
	cout << "----------------------end-------------------------" << endl;
}

template <typename T>
void tf(const T &tmprv)
{
	cout << "---------------------begin------------------------" << endl;
	cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;					 // 显示T类型
	cout << "tmprv = " << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; // 显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}

int main()
{
	// myfunc(100);//void myfunc(const T &tmprv)

#if 0 // void myfunc(T &tmprv)
	int i = 100; //一眼看得出来i的类型为int
	const int j = i; //一眼看得出来j的类型为const int
	const int &k = i;  //一眼看得出来k的类型为const int &
	myfunc(i);
	myfunc(j);
	myfunc(k);
#endif

#if 0
	int ii;
	int &jj = ii;

	ii = 1;
	mf(jj);
	cout << ii << endl;

	ii = 1;
	mf2(jj);
	cout << ii << endl;

	ii = 1;
	mf3(jj);
	cout << ii << endl;
#endif

#if 0 // void myfunc(const T &tmprv)
	int i = 100;
	const int j = i;
	const int &k = i;
	myfunc(i);
	myfunc(j);
	myfunc(k);
#endif

#if 0 // void myfunc(T *tmprv)
	int i = 100;
	const int *pi = &i;
	myfunc(&i);
	myfunc(pi);
#endif

#if 0 // void myfunc(T &&tmprv)
	int i = 100;
	const int j = i;
	const int &k = i;
	myfunc(i);
	myfunc(j);
	myfunc(k);
	myfunc(100);
#endif

#if 0 // void myfunc(T tmprv)
	int i = 100;
	const int j = i;
	const int &k = i;
	myfunc(i);
	myfunc(j);
	myfunc(k);

	int &m = i;
	myfunc<int &>(m);

	char mystr[] = "I Love China!";
	const char *const p = mystr;
	myfunc(p);
#endif

#if 0 // void myfunc(T tmprv)
	int mm = 180;

	// int& tmpvalue = tmprv;//隐式类型转换
	// tmpvalue = 12;
	myfunc(std::ref(mm)); // 引用（std::reference_wrapper<T>，T为int），可修改
	cout << "mm = " << mm << endl;

	myfunc(std::cref(mm)); // 常量引用（std::reference_wrapper<T>，T为const int），不可修改
#endif

#if 0 // void myfunc(T tmprv)
	const char mystr1[] = "I Love China!";
	myfunc(mystr1);
#endif

#if 0 // void myfunc(T &tmprv)
	const char mystr2[] = "I Love China!";
	myfunc(mystr2);
	myfunc2(mystr2);
#endif

#if 0 // void myfunc(T tmprv)
	myfunc(testFunc);
#endif

#if 0 // void myfunc(T &tmprv)
	myfunc(testFunc);
#endif

#if 0 // void myfunc(initializer_list<T> tmprv)
	myfunc({1, 2, 3});
#endif

#if 1
	auto x = 27;		// 估计：x = int,auto = int
	const auto x2 = x;	// 估计：x2 = const int,auto =int
	const auto &xy = x; // 这个auto并不是传值方式，估计：xy = const int &,auto = int
	auto xy2 = xy;		// 估计：xy2 = int,auto = int。这种应该是属于传值方式，传值方式时：引用类型会被抛弃,const属性会被抛弃，xy2是个新副本，这一点和函数模板类型推断非常类似

	cout << "xy2 = " << type_id_with_cvr<decltype(xy2)>().pretty_name() << endl; // 显示tmprv类型
	tf(x);																		 // T=int=auto

	auto &xy3 = xy; // 估计：xy3 = const int &,auto = const int，针对auto类型：引用会被丢弃，const属性会被保留
	tf(xy3);

	auto y = new auto(100); // new一块内存，内存的初始值给100。估计：y = int *,auto = int *。auto可以用于new操作符
	const auto *xp = &x;	// 估计：xp = const int *,auto = int
	auto *xp2 = &x;			// 估计：xp2 = int *,auto = int
	auto xp3 = &x;			// 估计：xp3 = int *，auto = int *; xp3不声明为指针，也能推导出指针类型
	tf(xp3);

	auto &&wnyy0 = 222; // 估计：这是万能引用，222是右值，所以：auto = int,wnyy0 = int&&（右值引用）
	auto &&wnyy1 = x;	// 估计：这是万能引用，x是左值，所以：auto=int&，wnyy1=int&
	auto &&wnyy2 = x2;	// 编译器推断：这是万能引用，x2是左值，则auto是int const & ，wnyy2也是int const &
	tf(wnyy2);
#endif

	cout << "Over!\n";
	return 0;
}
