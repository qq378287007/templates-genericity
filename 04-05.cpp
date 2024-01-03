// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	void myfunc(int tmpvalue) //一个普通函数
	{
		std::cout << "myfunc执行了：tmpvalue = " << tmpvalue << endl;
	}
	void callObjFunc(std::function<void(int)> cobj)
	{
		cobj(120); 
	}

	//----------------------------
	//可调用对象处理器
	template<typename T, typename... Args>
	class CFObjHandler
	{
	public:
		virtual T invoke(Args... args) const {}; //虚函数，因为后续要创建子类
	};

	template<typename U, typename T, typename... Args>
	class CFObjHandlerChild :public CFObjHandler<T, Args...>
	{
	public:
		//构造函数	
		CFObjHandlerChild(U&& tmpfuncobj) :functor(std::forward<U>(tmpfuncobj))		
		{
			/*cout << "-------------------" << endl;
			using boost::typeindex::type_id_with_cvr;
			cout << "U1111=" << type_id_with_cvr<U>().pretty_name() << endl;
			cout << "tmprv11111=" << type_id_with_cvr<decltype(tmpfuncobj)>().pretty_name() << endl;*/
		}

		virtual T invoke(Args... args) const
		{
			return functor(std::forward<Args>(args)...);
		}

	private:
		U functor;  //U是一个可调用对象类型，functor用于保存可调用对象的一个拷贝
	};



	//泛化版本
	template<typename T>
	class CallFuncObj;
	

	//特化版本
	template<typename T, typename... Args>
	class CallFuncObj<T(Args...)>
	{
	public:
		//构造函数模板
		template<typename U>
		CallFuncObj(U&& acobj) //可以接收各种可调用对象（函数对象、lambda表达式等等）
		{
			//using boost::typeindex::type_id_with_cvr;
			//cout << "U=" << type_id_with_cvr<U>().pretty_name() << endl;  //U=class `int __cdecl main(void)'::`2'::<lambda_1> 
			//cout << "tmprv=" << type_id_with_cvr<decltype(acobj)>().pretty_name() << endl; //tmprv=class `int __cdecl main(void)'::`2'::<lambda_1> 
			//cout << "tmprv2=" << type_id_with_cvr<decltype(std::forward<U>(acobj))>().pretty_name() << endl;
						
			handler = new CFObjHandlerChild<U, T, Args...>(std::forward<U>(acobj));
			
		}

		//析构函数
		~CallFuncObj()
		{
			delete handler;
		}


	public:
		//重载()，实现该类对象的可调用
		T operator()(Args... args) const
		{
			return handler->invoke(std::forward<Args>(args)...);  //使用std::forward实现参数的完美转发，保持原始实参的左值或者右值性
		}
	private:
		CFObjHandler<T, Args...>* handler;  //可调用对象处理器

	};

	void callObjFunc2(CallFuncObj<void(int)> cobj)
	{
		cobj(120);
	}
}



int main()
{
	/*_nmsp1::callObjFunc(_nmsp1::myfunc);
	_nmsp1::callObjFunc([](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
		});
	*/
	
	
	//_nmsp1::callObjFunc2(_nmsp1::myfunc);
	/*_nmsp1::callObjFunc2([](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
		});*/

	
	/*_nmsp1::CallFuncObj<void(int)> f1 = _nmsp1::myfunc;
	f1(1200);*/
	/*_nmsp1::CallFuncObj<void(int)> f2 = [](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl; 
	};
	f2(1200);*/

	auto ftest = [](int tmpvalue) {std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl; };
	_nmsp1::CallFuncObj<void(int)> f3 = ftest;
	f3(1200);

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
