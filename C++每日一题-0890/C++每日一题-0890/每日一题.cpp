/*
ÿ���ܽ᣺
1����������ĳ����ҳȴͻȻ������ĳ����Ӫ�̵���ҳ(����ͨ������)�����ִ������ԭ���ǣ�DNS�ٳ֣�����
2��TCP�������֣�SYN--SYN+ACK--ACK;
	�Ĵλ���:FIN--ACK--FIN--ACK
3����ʹ��TCPЭ����ʱ���������ݵĸ�ʽ��Ӧ�ò�Э�����ɳ���Ա���Ǻʹ���ģ�
4�������кܶ���վ����ʼѡ��HTTPS��ΪĬ�ϵ�Э�飬HTTPS����;�ǣ�����ȷ���������ݵİ�ȫ�Ժͷ��۸ģ�
5��ĳ�����������HTTP���������£�
GET/index.html HTTP/1.1
Host:www.test.cdn.cn
Connection:Close
Cookie:123456
�ñ��ı�ʾ���������������� index.html 
			Index.html ����� www.test.edu.cn��
			���������������� www.test.edu.cn
6�������׺��������½�һ��TCP ���ӣ��׵�ӵ�����Ƴ�ʼ��ֵΪ 32KB��������ʼ���� MSS=1KB ��С�Ķη� �����ݣ���һֱ�����ݷ��ͣ�
��Ϊ�����ӷ��� 16KB ���ջ��棬����ÿ�����ݶν���ȷ�ϣ� ���Զδ����� �١������յ�������ȫ�����뻺�棬����ȡ�ߣ���״����ӽ����ɹ�ʱ����δ���ͳ�ʱ ������£�
���� 4 �� RTT �󣬼׵ķ��ʹ����ǡ�1K����
7��ͨ��POP3Э������ʼ�ʱ��ʹ�õĴ������������ǣ������ӿɿ������ݴ������
8������UDPЭ���������1.�ṩ�����ӷ���  2.�ṩ����/���÷���
9��/etc/resolv.conf����;�ǣ�DNS�����������ļ���
10���ܹ�PINGͨͬ���εĽڵ㣬��ȴ��PING��ͨ�������ε����нڵ������ܵ�ԭ�򣺱����������ô���
11�������ἰ��Dos�����������µ���Ϊ��C ������Ч������ʹ����ȷ�������޷�����Ӧ���������ơ�
12�����²���DNS��������õ��ǣ���IP������MAC��ַ��
*/


/*
day34:
��Ŀ������һֻ���������ÿ�춼�ܲ���һ̥���ӡ�ÿֻ���ӵĳ�������һ�졣
ĳ��������һֻ���ӣ����ʵ�N���Ժ��������ж���ֻ���ӣ�
��Ŀ��������������ӵڶ���Ϳ�ʼ��С�����ˣ���������Ǵӵڶ��ʼ��쳲��������С�ǰ90�������ǡ�û���long long�ķ�Χ�ڣ�
ֱ�ӿ������
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
//����ù�ʽ���㣬��Ҫ�����������ֵ 
void solve(long long num[]) { 
	for (int i = 2; i < MAX; i++) {
		num[i] = num[i - 1] + num[i - 2];
	}
}
//long long sum_traversal(long long num[], int from, int to) 
////�ⷨ1���ñ��������� 
//{ 
//	long long ans = 0; 
//	for (int i = from - 1; i < to; i++) 
//		//�������±��from - 1������to - 1 
//	{
//		ans += num[i]; 
//	}
//	return ans; 
//
//}

//�ⷨ2���ù�ʽ��� 
long long sum_formula(long long num[], int from, int to) 
{
	return num[to + 1] - num[from];
	//��to + 2����±���to + 1����from + 2 - 1����� ����from 
}
int main() { 
	int from, to; 
	long long num[MAX] = {1, 1}; 
	//��ǰ����Fibonacci���� 
	solve(num); 
	while (std::cin >> from >> to) { 
		std::cout << sum_formula(num, from, to) << std::endl; 
		//����������ѡһ���� ʽ���졣
	}
	return 0; 
}

