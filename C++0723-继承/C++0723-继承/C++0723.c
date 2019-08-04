/*
C++ 继承：
继承：实现函数复用的功能
访问方式：基类的私有成员已经继承到了子类，知识不能被访问<例如：私房钱>
	使用class是默认继承的是private继承，使用struct时默认继承方式是public;
	在实际应用中一般使用的都是public，几乎很少使用private/protected;
	注意：基类的private成员在派生类中无论以何种方式继承都是不可见的；
>1.派生类对象可以赋值给基类的对象、基类的指针、基类的引用【在public的继承方式下】
>2.基类对象不能赋值给派生类
继承中的作用域：
	1.在继承体系中，积累和派生类都是不同且独立的作用域；
	同名隐藏：子类和基类具有相同的函数名；
	成员函数的隐藏，只需要函数名字相同就构成了隐藏；
新关键字：final--禁止隐藏
				修饰类----作用：该类不能被继承
				虚函数----作用：该虚函数不能被派生类重写
继承和友元：、
	友元函数不能被继承，也就是说基类友元不能访问子类的私有和保护成员；
虚拟继承：虚拟继承比普通的继承多了4个字节
	virtual：虚拟关键字
类的6个默认成员函数：
	构造函数、拷贝构造函数、析构函数、赋值操作符重载、取地址操作符重载、const修饰的取地址操作符重载
继承的总结和反思：
	public继承其实是一种 is-a 的关系，即就是说每个派生类对象都是一个基类对象。*******

C++多态：
	多态的实现方式：(必须在继承的体系中)
	1.基类中必须包含有虚函数，在派生类中必须对基类中的虚函数进行重写
	2.虚函数的调用：必须使用基类的指针或者引用调用基类
	两个条件缺一不可，否则就不能实现多态，不管传递哪个类的对象，调用的都是基类的虚函数
重写：一定是派生类重写基类的虚函数
	  派生类虚函数的原型必须与基类中虚函数的原型（返回值类型、函数名字、参数列表）完全相同
	表现：在代码运行时，根据基类指针指向不同子类的对象，选择调用不同类的虚函数

（虚函数重写的两个例外）
协变：
	基类和派生类虚函数的返回值类型不同；
	基类虚函数返回“基类”的指针和引用；
	派生类虚函数返回“派生类”的指针和引用；
析构函数的重写：
	基类和派生类析构函数的名字不同

C++11中的关键字:override
	override:检查派生类虚函数是否重写了基类的某一个虚函数,如果没有则报错！
	
如果一个类包含了虚函数：
	1.对象多了4个字节
	2.该4个字节内容在构造函数中进行填充
	3.前4个字节中放置一个地址-----指向虚函数
	4.派生类虚表构建规则：
	a.将基类虚表中内容拷贝一份放到派生类虚表中；
	b.如果派生类重写了基类的某个虚函数，用派生类自己的虚函数替换虚表中相同偏移量位置的基类虚函数；
	c.对于派生类自己新增的虚函数将其按照在类中声明的先后次序一次放在虚表的最后。
*/

//每日一题
#include<stdio.h>
#include <stdlib.h>

int foo(int x,int y){
	if (x <= 0 || y <= 0)
		return 1;
	return 3 * foo(x - 6, y / 2);
}
int main(){
	printf("%d\n", foo(20, 13));//输出：81
	system("pause");
	return 0;
}


//函数的递归调用
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int fac(int n){
	if (n < 0){
		printf("data error");
	}
	else if (n == 0 || n == 1){
		return 1;
	}
	else{
		return fac(n - 1)*n;
	}
}
int main(){
	int fac(int n);
	//int y;
	int n;
	printf("please input an integer number:");
	scanf("%d", &n);
		//y = fac(n);
	printf("%d!=%d\n", n, fac(n));
	system("pause");
	return 0;
}


//函数的指针的用法1
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "swap.h"

void exchange(int *a1, int *a2, int *a3){//定义改变变量值的函数
	//void swap(int *pt1, int *pt2);
	if (*a1<*a2) swap(a1, a2);
	if (*a1<*a3) swap(a1, a3);
	if (*a2<*a3) swap(a2, a3);
}
void swap(int *pt1, int *pt2){ // 定义实现交换的函数
	int temp;
	temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
}
int main(){
	//void exchange(int *a1, int *a2, int *a3);
	int A, B, C, *b1, *b2, *b3;
	printf("please input three integer number:");
	scanf("%d%d%d", &A, &B, &C);
	b1 = &A;
	b2 = &B;
	b3 = &C;
	exchange(b1, b2, b3);
	printf("order is:%d %d %d\n", A, B, C);
	system("pause");
	return 0;
}