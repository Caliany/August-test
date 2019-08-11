/*
每日总结：
1、上网访问某个网页却突然出现了某个运营商的网页(如联通、电信)。出现此问题的原因是：DNS劫持！！！
2、TCP三次握手：SYN--SYN+ACK--ACK;
	四次挥手:FIN--ACK--FIN--ACK
3、当使用TCP协议编程时，发送数据的格式和应用层协议是由程序员考虑和处理的；
4、现在有很多网站都开始选择HTTPS作为默认的协议，HTTPS的用途是：可以确保传输数据的安全性和防篡改；
5、某浏览器发出的HTTP请求报文如下：
GET/index.html HTTP/1.1
Host:www.test.cdn.cn
Connection:Close
Cookie:123456
该报文表示：该浏览器请求浏览 index.html 
			Index.html 存放在 www.test.edu.cn上
			该浏览器曾经浏览过 www.test.edu.cn
6、主机甲和主机乙新建一个TCP 连接，甲的拥塞控制初始阈值为 32KB，甲向乙始终以 MSS=1KB 大小的段发 送数据，并一直有数据发送；
乙为该连接分配 16KB 接收缓存，并对每个数据段进行确认， 忽略段传输延 迟。若乙收到的数据全部存入缓存，不被取走，则甲从连接建立成功时刻起，未发送超时 的情况下，
经过 4 个 RTT 后，甲的发送窗口是【1K】。
7、通过POP3协议接收邮件时，使用的传输层服务类型是：有链接可靠地数据传输服务
8、关于UDP协议的描述：1.提供无连接服务  2.提供复用/分用服务
9、/etc/resolv.conf的用途是：DNS解析的设置文件；
10、能够PING通同网段的节点，但却如PING不通其他网段的所有节点的最可能的原因：本机网关设置错误；
11、常被提及的Dos攻击的是以下的行为：C 发送无效的请求，使得正确的请求无法被响应【阻塞机制】
12、以下不是DNS服务的作用的是：将IP解析成MAC地址；
*/


/*
day34:
题目描述：一只成熟的兔子每天都能产下一胎兔子。每只兔子的成熟期是一天。
某人领养了一只兔子，请问第N天以后，他将会有多少只兔子？
题目解析：本体的兔子第二天就开始下小兔子了，所以这个是从第二项开始的斐波那契数列。前90组的数据恰好还在long long的范围内：
直接看代码吧
*/
//#include <iostream> 
//#include <cstdio>
//using namespace std;
//
//int main() { 
//	long long fib[91] = { 1, 2 }; 
//	for (int i = 2; i <= 90; i++) { 
//		fib[i] = fib[i - 1] + fib[i - 2]; 
//	}
//	int d;
//	while(cin >> d) {
//		printf("%d\n", fib[d - 1]);
//	}
//}


#include <iostream> 
#define MAX 83 
//如果用公式计算，需要接下来两项的值 
void solve(long long num[]) { 
	for (int i = 2; i < MAX; i++) {
		num[i] = num[i - 1] + num[i - 2];
	}
}
//long long sum_traversal(long long num[], int from, int to) 
////解法1：用遍历求和求解 
//{ 
//	long long ans = 0; 
//	for (int i = from - 1; i < to; i++) 
//		//让数组下标从from - 1遍历到to - 1 
//	{
//		ans += num[i]; 
//	}
//	return ans; 
//
//}

//解法2：用公式求解 
long long sum_formula(long long num[], int from, int to) 
{
	return num[to + 1] - num[from];
	//第to + 2项的下标是to + 1，第from + 2 - 1项的下 标是from 
}
int main() { 
	int from, to; 
	long long num[MAX] = {1, 1}; 
	//提前计算Fibonacci数列 
	solve(num); 
	while (std::cin >> from >> to) { 
		std::cout << sum_formula(num, from, to) << std::endl; 
		//两个方法二选一。公 式更快。
	}
	return 0; 
}

