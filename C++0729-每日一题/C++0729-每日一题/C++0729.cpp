/*day25
1��һ���̸ջ������������ʹ��Ȩ�����ý��̷���ҳ��Ĵ�����{1321215123}������LRU�㷨ʱ��ȱҳ���ǣ�5���Ρ�
2�����ڶ��̵߳������У�
	�߳�ͬ���ķ�������ʹ���ٽ��������������ź�����
	�����߳�ͬʱ�Լ�����ȫ�ֱ�������д����Ҳ��Ҫ���⣻  
	�����뺯�������Ե��ò������뺯���� *****
3��ϵͳ�����Ŀ���ԭ���ǣ���Դѭ���ȴ���
4��ʹ��C���Խ�һ��1G�ֽڵ��ַ������ͷ��βȫ������Ϊ��'A',��һ̨����ĵ���PC�ϣ���Ҫ���ѵ�CPUʱ�����������ӽ���1�룩��
*/


/*day26
1���ڵ�������ϵͳ�У����ͬʱ����12�����̣����ھ��������еĽ����������Ϊ:(11);
2����ϵͳ�ڴ������ô��̻���������ҪĿ����(���ٴ���I/O����)��
3�����½��̴�ִ��̬��Ϊ����̬���¼���(���߼����ȼ�������ռ)��
4�����ڹܵ���pipe��ͨ�ŵ������У���ȷ���ǣ����̶Թܵ����ж�������д���������Ա�������
5��һ���ļ����û������״δ򿪵Ĺ����У�����ϵͳ��Ҫ�����ǣ������ļ����ƿ�����ڴ��С���
6�����Լӿ���ʵ��ַת�����ǣ�<1> ������(TLB); <2>��ҳ��פ�ڴ�
7��һ�����̵Ķ�����������ɺ󣬲���ϵͳ��Ըý��̱������ǣ����޸Ľ���״̬Ϊ����״̬����
/*
day27
ÿ���ܽ᣺
1��fork:����һ���͵�ǰ����ӳ��һ���Ľ��̿���ͨ��fork()ϵͳ���ã�
�ɹ�����һ��fork()�ᴴ��һ���µĽ��̣�����������õ�fork()�Ľ���һģһ�������������̶���������С�
vfork��vfork()�����˵�ַ�ռ�İ�ҳ���ƣ�vfork()ֻ�����һ���£������ڲ����ں����ݽṹ���ӽ���Ҳ�Ͳ����޸ĵ�ַ�ռ��е��κ��ڴ档
	vfork()ֻ��һ����װ����fork()��
*/


/*
����ָ�룺
�����ռ䲻ʹ������ָ��
*/
#include <iostream>
using namespace std;

// RAII: 
// ����ָ�룺RAII + operator*()/operator->() + ��ô���ǳ��������


// C++98: ��Դ��ת��
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

		// ��������ָ�����Ϊ
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


// ��Դ����Ȩ(����Դ�ͷŵ�Ȩ��)��ת��
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

		// ����ָ�����Ϊ
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
		mutable bool _owner;  // ��Դ������ӵ����(��Դ���ͷ���)
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
		// ap3����Դ�Լ����ͷ�Ȩ��ת�Ƹ�ap4
		// ap4������ʱ�Ѿ�����Դ�ͷ���
		bite::auto_ptr<int> ap4(ap3);
	}

	// Ұָ��
	*ap3 = 10;
}

// ���飺ʲô����£�����Ҫʹ��auto_ptr

int main()
{
	TestAutoPtr();
	return 0;
}

// ����ָ��ԭ��RAII������Դ + ����ָ�����Ϊ + ���ǳ��������
// ��Դ��ռ��������������
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

		// ��ֹ������
		// C++98
		//private:
		//	unique_ptr(const unique_ptr<T>&);
		//	unique_ptr<T>& operator=(const unique_ptr<T>& ap);

		// C++11 delete:��ֹĬ�ϳ�Ա����������
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

// shared_ptr��������������ָ��


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
		T* _ptr; // ��Դ
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
	// ֻ�ܹ���new����Դ
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

		// sp2:û�й�����Դ ��sp1ֱ�ӹ���
		// sp2: ���Թ�����Դ 
		// sp2: ��������������Դ  ����-1
		// sp2 = sp1
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// �õ�ǰ�����������Դ�Ͽ���ϵ
				release();

				// �õ�ǰ������sp������Դ
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
		T* _ptr; // ��Դ
		int* _pCount;  // ָ������Ŀռ�
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
	// 	// sp2û�й�����Դ
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



// ����ɾ����

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

// malloc����Դ
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
	// ������Դ�ǲ���delete��ʽ�����ͷ�
	// ��ȷ�ͷŷ�ʽ��������Դ������ȥ�ͷ�
	// ������Դʱ��������ʽ�������
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
				// �õ�ǰ�����������Դ�Ͽ���ϵ
				release();

				// �õ�ǰ������sp������Դ
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
		T* _ptr; // ��Դ
		int* _pCount;  // ָ������Ŀռ�
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
