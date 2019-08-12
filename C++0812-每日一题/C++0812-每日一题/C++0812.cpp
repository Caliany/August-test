/*
�����������ڶ�������M����Ҳ��һ����
�У���ʽΪm s1 s2����ʾ����m������s1����ɡ��������е�����ʵ����1<=m<=20��s1��k����Ȼ��s2Ҳ����ô������
��ʹ�õľ�������������������ĸ���������ķ�Χ���ᳬ23561-ǰ��ͺ������Ƕ�����Ϥ��������ǰ������ͺ�
������������ݽṹ���У�ͨ����������������ͺ�����������ǰ������⣬���Ǹ���ǰ����������������⡣
��һ������£�����������ǰ��ͺ���ʱ��������ȷ���������������������������ĸ������������Ƕ�ӵ������ͬ
��ǰ��ͺ�����ʵ����������������ڶ�������M����Ҳ��һ���������������������ɶ������������ɡ�ÿ������
ֻ��һ�У���ʽΪm s1 s2����ʾ����m������s1��ǰ�������s2�Ǻ�������������ַ�������Сд��ĸ�ַ���ɡ�����
���е�����ʵ����1<=m<=20��s1��s2�ĳ��Ƚ�����1��26֮�䣨��1��26�������s1�ĳ�����k����Ȼ��s2Ҳ����ô������
��ʹ�õľ�����ĸ���ǰK����ĸ������һ��0��ʾ��ֹ���롣


������˼·�����������ǵ�ǰ����abejkcfghid��������jkebfghicda��
��ô���Ǹ���ǰ�򣬾���֪����1����������13��������Ҳ����ÿһ�㶼��13������λ��2��a�Ǹ�����һ�������ĸ���b 3��ͨ����
��������֪����b��������j��k��e��b���ĸ����4���ٻص�ǰ����ǰ��4����㣬��һ�������ĸ��� c5���Դ����ƣ����յõ� a 
Ϊ������һ�㹲�� 3 ��������������������������ǰ�� bejk cfghi d���� jkeb fghic d����һ��һ���Ŀ����Ծ���13����λ�����
3������3����������ô�� �ֿ��ܡ�֮���ٵݹ鴦��b���������bejk|jkeb������bΪ��ʱ��һ���ж��ٿ����������Կ�����ֻ��һ��
��eΪ������������ô�����Ծ�ֻ�� �֡��ٵݹ�ejk|jke����������������Ȼ�� �֣��ݹ�cfghi|fghic���������������� �֡�
����������������ɡ���������������������������⣬������Ҫʵ����������е�C���������
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string> 
#include <tuple> 
#include <list> 
#include <cstdio>

// ��n�Ľ׳� 
long long factorial(int n) { 
	long long r = 1; 
	for (int i = 1; i <= n; i++) { 
		r *= i; 
	}
	return r; 
}

// �� n, m ����� C(n, m) 
// ���� C(n, m) == C(n, n - m) ���ص㣬�������׵� 
long long combination(int n, int m) { 
	int max = m > (n - m) ? m : (n - m);
	long long numerator = 1; 
	for (int i = max + 1; i <= n; i++) { 
		numerator *= i; 
	}
	return numerator / factorial(n - max);
}
// ���������ͣ������� typedef ���� 
using PrePost = std::tuple<std::string, std::string>; 

// ����һ������ǰ��+��������������ע�͵�ԭ�� 
// ��ÿ��������ǰ��+�����зֳ��� 
std::list<PrePost> 
splitSubTrees(std::string const& pre, std::string const& post) { 
	std::list<PrePost> list{}; 
	size_t preIdx = 1; 
	size_t lastPost = 0; 
	while (preIdx < pre.size()) { 
		char rootValue = pre[preIdx]; 
		size_t postIdx = post.find(rootValue);

	int countOfNode = postIdx - lastPost + 1;
	list.emplace_back(std::make_tuple(
		pre.substr(preIdx, countOfNode), 
		post.substr(lastPost, countOfNode)
		)
	);
		preIdx += countOfNode; 
		lastPost += countOfNode;
	}
	return list;
}
// �ݹ�����ÿһ��Ŀ����ԣ�ֱ������ֻʣһ������������ 
long long calculateNumOfPossibilities(int m, std::string const& pre, std::string const& post) { 
	if (pre.size() == 0 || pre.size() == 1) { 
		return 1; 
	}
	std::list<PrePost> 
		subTrees = splitSubTrees(pre, post); 
	long long result = combination(m, subTrees.size());
	for (PrePost const& prePost : subTrees) {
		result *= calculateNumOfPossibilities(m,std::get<0>(prePost), std::get<1>(prePost));
	}
	return result; 
}
int main() {
	int m;
	char pre[30];
	char post[30];
	while (scanf("%d %s %s", &m, pre, post) != EOF) {
		printf("%lld\n", calculateNumOfPossibilities(m, pre, post));
	}
	return 0;
}