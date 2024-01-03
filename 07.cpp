#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996)

namespace _nmsp1
{

	//-----------------------
	template <typename T>
	struct mylist_node
	{
		mylist_node *next;
		mylist_node *prev;
		T data;

		// 构造函数，根据容器中的实际的元素来构造一个mylist_node对象
		// 为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
		explicit mylist_node(const T &x) : data(x), next(nullptr), prev(nullptr)
		{
		}
	};
	//---------------------------------------
	template <typename T> // T代表容器中的元素类型
	struct mylist_iterator
	{
		using iterator_category = bidirectional_iterator_tag;

		// 为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
		explicit mylist_iterator() : node(nullptr) {}						 // 默认构造函数
		explicit mylist_iterator(mylist_node<T> *tmpnode) : node(tmpnode) {} // 构造函数

		T &operator*() // 返回迭代器所指向的元素，注意返回类型是T&
		{
			return node->data;
		}
		mylist_iterator &operator++() // 重载前置++，注意++在前，形如：++i
		{
			node = node->next; // 指向了mylist容器中的下一个元素
			return *this;
		}
		mylist_iterator operator++(int) // 重载后置++ (圆括号中多了个int，只是为了与前置++做区分)，注意++在后，形如：i++，所以遍历的时候提倡用前置++ (避免产生临时对象)
		{
			mylist_iterator tmp(*this);
			node = node->next; // 也可以写成++*this，如果这样写，这里的++会调用重载的前置++
			return tmp;
		}

		mylist_node<T> *node; // 定义指向容器中元素的指针

		bool operator!=(const mylist_iterator &tmpobj)
		{
			return node != tmpobj.node;
		}
		bool operator==(const mylist_iterator &tmpobj)
		{
			return node == tmpobj.node;
		}
	};

	template <typename T>
	class mylist
	{
	public:
		using iterator = mylist_iterator<T>; // 迭代器类型

	public:
		explicit mylist() // 默认构造函数
		{
			void *point = new char[sizeof(mylist_node<T>)];
			head = reinterpret_cast<mylist_node<T> *>(point);
			// head = new mylist_node<T>();
			head->next = head;
			head->prev = head;
		}
		~mylist() // 析构函数
		{
			clear();			 // 注意位置，要放在delete head;语言行之前
			delete (void *)head; // 释放特殊mylist_node对象所指向的内存
			head = nullptr;
		}

		iterator begin()
		{
			return iterator(head->next); // 注意，head->next始终指向第一个元素
		}
		iterator end()
		{
			return iterator(head);
		}

		void push_back(const T &tmpelem)
		{
			// 创建一个待加入的节点
			mylist_node<T> *pnewnode = new mylist_node<T>(tmpelem);
			if (head->next == head) // 等价于if (begin() == end())
			{
				// 当前容器为空
				pnewnode->next = head; // 新mylist_node对象节点的next指针，指向这个特殊mylist_node对象节点
				pnewnode->prev = head; // 新mylist_node对象节点的prev指针，指向这个特殊mylist_node对象节点

				head->next = pnewnode; // 对于已经存在的特殊mylist_node对象节点的next指针，始终要指向整个mylist容器中最前面的元素，所以指向的应该是新mylist_node对象节点
				head->prev = pnewnode; // 对于已经存在的特殊mylist_node对象节点的prev指针，指向的应该是新mylist_node对象节点
			}
			else
			{
				// 当前容器不为空，这部分代码和if中有重复，但为了理解直观，重复是值得的
				pnewnode->next = head;		 // 新mylist_node对象节点的next指针，指向这个特殊mylist_node对象节点
				pnewnode->prev = head->prev; // 新mylist_node对象节点的prev指针，指向的应该是容器中的前一个mylist_node对象节点，这里head->prev代表的就是前一个mylist_node对象节点

				head->prev->next = pnewnode; // 老mylist_node对象节点的next指针指向新mylist_node对象节点
				head->prev = pnewnode;		 // 特殊mylist_node对象节点的prev指针指向新mylist_node对象节点，注意本行语句放在最后，不能与上行互换
			}								 // end if
		}

		void clear()
		{
			if (head->next != head)
			{
				// 当前容器不为空
				mylist_node<T> *currnode = head->next; // currnode指向第一个节点
				while (currnode != head)			   // 指向的不是"特殊mylist_node对象节点"
				{
					mylist_node<T> *nextnode = currnode->next; // 指向当前节点后的节点（下一个节点）
					delete currnode;						   // 释放当前节点所指向的内存
					currnode = nextnode;					   // 让currnode指向下一个节点
				}											   // end while
			}												   // end if
		}

	private:
		mylist_node<T> *head;
	};

	//----------------------
	class A
	{
	public:
		explicit A(int tmpi) : m_i(tmpi)
		{
			cout << "A::A()执行了" << endl;
		}
		int m_i;
	};

	//---------------------------------------------------
	// 别名模板
	template <class _Iter>													//_Iter代表迭代器类型
	using _Iter_cat_t = typename iterator_traits<_Iter>::iterator_category; // 为萃取机定义别名模板（5.1.2节看到过）

	// 变量模板（元函数）
	template <class _From, class _To>
	constexpr bool is_convertible_v = __is_convertible_to(_From, _To);

	template <class _Iter>
	constexpr bool _Is_input_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, input_iterator_tag>;

	template <class _Iter>
	constexpr bool _Is_fwd_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, forward_iterator_tag>;

	template <class _Iter>
	constexpr bool _Is_bidi_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, bidirectional_iterator_tag>;

	template <class _Iter>
	constexpr bool _Is_random_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, random_access_iterator_tag>;

	//---------------------------------------------------

	bool myfuncfind(int val)
	{
		if (val > 0)
			return true; // 返回true就停止遍历
		return false;
	}

	//--------------------------------------------------
	// T代表的是迭代器类型，U代表的是可调用对象（可调用对象常被用作算法中的参数）
	template <class T, class U>
	T my_find_if(T first, T last, U funcobj)
	{
		for (; first != last; ++first)
		{
			if (funcobj(*first))
			{
				break;
			}
		}
		return first;
	}

}

int main()
{
	/*
	std::list<int>  msgList;
	msgList.push_back(1); //末尾插入1，list中内容：1
	msgList.push_front(2);//开头插入2，list中内容：2，1
	msgList.push_back(3); //末尾插入3，list中内容：2，1，3
	for (std::list<int>::iterator pos = msgList.begin(); pos != msgList.end(); ++pos)
	{
		cout << *pos << endl;
	}*/

	/*_nmsp1::mylist<_nmsp1::A> msgList;

	if (msgList.end() == msgList.begin())
	{
		//msgList容器是空的
		cout << "msgList容器为空!" << endl;
	}
	if (msgList.end() != msgList.begin())
	{
		//msgList容器不是空的
		cout << "msgList容器不为空!" << endl;
	}*/

	/*
	_nmsp1::mylist<_nmsp1::A> msgList;
	msgList.push_back(_nmsp1::A(2));
	msgList.push_back(_nmsp1::A(1));
	msgList.push_back(_nmsp1::A(3));
	for (_nmsp1::mylist<_nmsp1::A>::iterator pos = msgList.begin(); pos != msgList.end(); ++pos)
	{
		cout << (*pos).m_i << endl;
	}

	//bidirectional_iterator_tag
	//std::list<int>::iterator
	cout << typeid(_nmsp1::mylist_iterator<int>::iterator_category).name() << endl;*/

	/*std::list<int>  msgList10;
	msgList10.push_back(1);
	msgList10.push_back(2);
	std::sort(msgList10.begin(), msgList10.end());*/

	_nmsp1::mylist<int> msgList2;
	msgList2.push_back(2);
	msgList2.push_back(1);
	msgList2.push_back(3);

	// auto result = std::find_if(msgList2.begin(), msgList2.end(), [](int val) {
	//	if (val > 0)
	//		return true; //返回true就停止遍历
	//	return false;
	//	});
	// auto result = std::find_if(msgList2.begin(), msgList2.end(), _nmsp1::myfuncfind);
	auto result = _nmsp1::my_find_if(msgList2.begin(), msgList2.end(), _nmsp1::myfuncfind);
	if (result == msgList2.end())
	{
		cout << "没找到" << endl;
	}
	else
	{
		cout << "找到了，结果为:" << *result << endl;
	}
}
