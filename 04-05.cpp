#include <iostream>
#include <vector>
#include <functional>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
#pragma warning(disable : 4996)

namespace ns1
{
	void myfunc(int tmpvalue) { cout << "void myfunc(int), tmpvalue = " << tmpvalue << endl; }
	void callObjFunc(function<void(int)> cobj) { cobj(120); }

	// 可调用对象处理器
	template <typename T, typename... Args>
	class CFObjHandler
	{
	public:
		virtual T invoke(Args... args) const = 0;
	};

	template <typename U, typename T, typename... Args>
	class CFObjHandlerChild : public CFObjHandler<T, Args...>
	{
	public:
		CFObjHandlerChild(U &&tmpfuncobj) : functor(forward<U>(tmpfuncobj))
		{
			cout << "-------------------" << endl;
			cout << "type of U = " << type_id_with_cvr<U>().pretty_name() << endl;
			cout << "type of tmpfuncobj = " << type_id_with_cvr<decltype(tmpfuncobj)>().pretty_name() << endl;
		}

		T invoke(Args... args) const override { return functor(forward<Args>(args)...); }

	private:
		U functor; // U是一个可调用对象类型，functor用于保存可调用对象的一个拷贝
	};

	// 泛化版本
	template <typename T>
	class CallFuncObj;

	// 特化版本
	template <typename T, typename... Args>
	class CallFuncObj<T(Args...)>
	{
	public:
		template <typename U>
		CallFuncObj(U &&acobj) // 可以接收各种可调用对象（函数对象、lambda表达式等等）
		{
			// cout << "U=" << type_id_with_cvr<U>().pretty_name() << endl;  //U=class `int __cdecl main(void)'::`2'::<lambda_1>
			// cout << "tmprv=" << type_id_with_cvr<decltype(acobj)>().pretty_name() << endl; //tmprv=class `int __cdecl main(void)'::`2'::<lambda_1>
			// cout << "tmprv2=" << type_id_with_cvr<decltype(forward<U>(acobj))>().pretty_name() << endl;

			handler = new CFObjHandlerChild<U, T, Args...>(forward<U>(acobj));
		}

		~CallFuncObj()
		{
			delete handler;
		}

	public: // 重载()，实现该类对象的可调用
		T operator()(Args... args) const { return handler->invoke(forward<Args>(args)...); }

	private:
		CFObjHandler<T, Args...> *handler; // 可调用对象处理器
	};

	void callObjFunc2(CallFuncObj<void(int)> cobj) { cobj(120); }
}

int main()
{
	using namespace ns1;

	callObjFunc(myfunc);
	callObjFunc([](int tmpvalue)
				{ cout << "[](int), tmpvalue = " << tmpvalue << endl; });

	callObjFunc2(myfunc);
	callObjFunc2([](int tmpvalue)
				 { cout << "[](int), tmpvalue = " << tmpvalue << endl; });

	CallFuncObj<void(int)> f1 = myfunc;
	f1(1200);
	CallFuncObj<void(int)> f2 = [](int tmpvalue)
	{ cout << "[](int), tmpvalue = " << tmpvalue << endl; };
	f2(1200);

	auto ftest = [](int tmpvalue)
	{ cout << "[](int), tmpvalue = " << tmpvalue << endl; };
	CallFuncObj<void(int)> f3 = ftest;
	f3(1200);

	cout << "Over!\n";
	return 0;
}
