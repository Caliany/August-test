/*day25
1、一进程刚获得三个主存块的使用权，若该进程访问页面的次序是{1321215123}，采用LRU算法时，缺页数是（5）次。
2、关于多线程的描述中：
	线程同步的方法包括使用临界区、互斥量、信号量；
	两个线程同时对简单类型全局变量进行写操作也需要互斥；  
	可重入函数不可以调用不可重入函数； *****
3、系统死锁的可能原因是：资源循环等待；
4、使用C语言将一个1G字节的字符数组从头到尾全部设置为字'A',在一台经典的当代PC上，需要花费的CPU时间的数量级最接近（1秒）；
*/


/*day26
1、在单处理器系统中，如果同时存在12个进程，则处于就绪队列中的进程数量最多为:(11);
2、在系统内存中设置磁盘缓冲区的主要目的是(减少磁盘I/O次数)；
3、导致进程从执行态变为就绪态的事件是(被高级优先级进程抢占)；
4、关于管道（pipe）通信的描述中，正确的是：进程对管道进行读操作和写操作都可以被阻塞；
5、一个文件被用户进程首次打开的过程中，操作系统需要做的是：【将文件控制块读到内存中】；
6、可以加快虚实地址转换的是：<1> 增大快表(TLB); <2>让页表常驻内存
7、一个进程的读磁区操作完成后，操作系统针对该进程必做的是：【修改进程状态为就绪状态】；
/*
day27
每日总结：
1、fork:创建一个和当前进程映像一样的进程可以通过fork()系统调用；
成功调用一个fork()会创建一个新的进程，他几乎与调用的fork()的进程一模一样，这两个进程都会继续运行。
vfork：vfork()避免了地址空间的按页复制；vfork()只完成了一件事：复制内部的内核数据结构，子进程也就不能修改地址空间中的任何内存。
	vfork()只是一个封装过多fork()；
*/


/*
智能指针：
连续空间不使用智能指针
*/
#include <iostream>
using namespace std;

// RAII: 
// 智能指针：RAII + operator*()/operator->() + 怎么解决浅拷贝问题


// C++98: 资源的转移
namespace bite
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		auto_ptr(auto_ptr<T>& ap)
			: _ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		// ap1 = ap2;
		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}

			return *this;
		}

		~auto_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		// 具有类似指针的行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()
		{
			return _ptr;
		}

	private:
		T* _ptr;
	};
}

struct A
{
	int a;
	int b;
	int c;
};

void TestAuto1()
{
	bite::auto_ptr<int> ap1(new int);
	*ap1 = 10;

	int a = 10;
	int* pa = &a;

	A aa;
	A* paa = &aa;
	paa->a = 10;

	bite::auto_ptr<A> ap2(new A);
	(*ap2).a = 10;

	ap2->b = 10;
}

void TestAuto2()
{
	int a = 10;
	int* pa1 = &a;
	int* pa2(pa1);

	*pa1 = 20;
	*pa2 = 30;

	bite::auto_ptr<int> ap1(new int);
	bite::auto_ptr<int> ap2(ap1);
	*ap1 = 10;
	*ap2 = 20;


	bite::auto_ptr<int> ap3;
	ap3 = ap2;
}

int main()
{
	TestAuto2();
	return 0;
}


// 资源管理权(对资源释放的权利)的转移
namespace bite
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _owner(false)
		{
			if (_ptr)
			{
				_owner = true;
			}
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
			{
				delete _ptr;
				_owner = false;
				_ptr = nullptr;
			}
		}

		// 类似指针的行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()
		{
			return _ptr;
		}

		auto_ptr(const auto_ptr<T>& ap)
			: _ptr(ap._ptr)
			, _owner(ap._owner)
		{
			ap._owner = false;
		}

		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr && _owner)
				{
					delete _ptr;
				}

				_ptr = ap._ptr;
				_owner = ap._owner;
				ap._owner = false;
			}

			return *this;
		}
	private:
		T* _ptr;
		mutable bool _owner;  // 资源真正的拥有者(资源的释放着)
	};
}


void TestAutoPtr()
{
	bite::auto_ptr<int> ap1(new int);
	bite::auto_ptr<int> ap2(ap1);

	*ap1 = 10;
	*ap2 = 20;

	bite::auto_ptr<int> ap3;
	ap3 = ap2;

	if (true)
	{
		// ap3将资源以及其释放权利转移给ap4
		// ap4在销毁时已经将资源释放了
		bite::auto_ptr<int> ap4(ap3);
	}

	// 野指针
	*ap3 = 10;
}

// 建议：什么情况下，都不要使用auto_ptr

int main()
{
	TestAutoPtr();
	return 0;
}

// 智能指针原理：RAII管理资源 + 具有指针的行为 + 解决浅拷贝问题
// 资源独占，不允许发生拷贝
namespace bite
{
	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// 防止被拷贝
		// C++98
		//private:
		//	unique_ptr(const unique_ptr<T>&);
		//	unique_ptr<T>& operator=(const unique_ptr<T>& ap);

		// C++11 delete:禁止默认成员函数的生成
		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& ap) = delete;

	private:
		T* _ptr;
	};
}

class A
{
public:
	A(int a)
		: _a(a)
	{}

	A() = default;


private:
	int _a;
};

void TestA()
{
	A a1(10);
	A a2;
}

void TestUniquePtr()
{
	bite::unique_ptr<int> up1(new int);
	//bite::unique_ptr<int> up2(up1);

	bite::unique_ptr<int> up3;
	//up3 = up1;
}


#include <memory>

int main()
{
	unique_ptr<int> ap1(new int);
	//unique_ptr<int> ap2(ap1);

	return 0;
}


// _CrtDumpMemoryLeaks();

// shared_ptr：共享类型智能指针


namespace bite
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{
			if (_ptr)
				_count = 1;
		}

		shared_ptr(shared_ptr<T>& sp)
			: _ptr(sp._ptr)
		{
			_count++;
		}

		~shared_ptr()
		{
			if (_ptr && 0 == --_count)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}
	private:
		T* _ptr; // 资源
		static int _count;
	};

	template<class T>
	int shared_ptr<T>::_count = 0;
}

void TestSharedPtr()
{
	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int> sp2(sp1);

	bite::shared_ptr<int> sp3(new int);
}


int main()
{
	TestSharedPtr();
	return 0;
}


namespace bite
{
	// 只能管理new的资源
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr)
				_pCount = new int(1);
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++(*_pCount);
		}

		// sp2:没有管理资源 与sp1直接共享
		// sp2: 独自管理资源 
		// sp2: 与其他对象共享资源  计数-1
		// sp2 = sp1
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 让当前对象与管理资源断开联系
				release();

				// 让当前对象与sp共享资源
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					++(*_pCount);
			}

			return *this;
		}

		~shared_ptr()
		{
			release();
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void release()
		{
			if (_ptr && 0 == --*_pCount)
			{
				delete _ptr;
				_ptr = nullptr;

				delete _pCount;
				_pCount = nullptr;
			}
		}
	private:
		T* _ptr; // 资源
		int* _pCount;  // 指向计数的空间
	};
}

void TestSharedPtr1()
{
	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	bite::shared_ptr<int> sp3(new int);
	cout << sp3.use_count() << endl;
}

void TestSharedPtr2()
{
	// 	bite::shared_ptr<int> sp1(new int);
	// 	bite::shared_ptr<int> sp2;
	// 
	// 	// sp2没有管理资源
	// 	sp2 = sp1;

	// 	bite::shared_ptr<int> sp1(new int);
	// 	bite::shared_ptr<int> sp2(new int);
	// 	sp2 = sp1;

	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int> sp2(new int);
	bite::shared_ptr<int> sp3(sp2);

	sp2 = sp1;
}

int main()
{
	//TestSharedPtr1();
	TestSharedPtr2();
	return 0;
}



// 定制删除器

// new
template<class T>
class DFDel
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

// malloc的资源
template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};

class FClose
{
public:
	void operator()(FILE*& pf)
	{
		if (pf)
		{
			fclose(pf);
			pf = nullptr;
		}
	}
};

namespace bite
{
	// 所有资源是采用delete方式进行释放
	// 正确释放方式：根据资源的类型去释放
	// 析构资源时，析构方式必须灵活
	template<class T, class DF = DFDel<T> >
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr)
				_pCount = new int(1);
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++(*_pCount);
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 让当前对象与管理资源断开联系
				release();

				// 让当前对象与sp共享资源
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					++(*_pCount);
			}

			return *this;
		}

		~shared_ptr()
		{
			release();
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void release()
		{
			if (_ptr && 0 == --*_pCount)
			{
				//delete _ptr;
				//DF df;
				//df.operator()(_ptr);
				DF()(_ptr);

				_ptr = nullptr;

				delete _pCount;
				_pCount = nullptr;
			}
		}
	private:
		T* _ptr; // 资源
		int* _pCount;  // 指向计数的空间
	};
}

void TestSharedPtr()
{
	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int, Free<int>> sp2((int*)malloc(sizeof(int)));
	bite::shared_ptr<FILE, FClose> sp3(fopen("1.txt", "w"));
}

int main()
{
	TestSharedPtr();
	return 0;
}
