/*
况不仅仅限于二叉树，M叉树也是一样。
行，格式为m s1 s2，表示树是m叉树，s1是组成。对于所有的输入实例，1<=m<=20，s1是k（当然，s2也是这么长），
那使用的就是历满足该条件的数的个数。输出的范围不会超23561-前序和后序我们都很熟悉二叉树的前序、中序和后
序遍历。在数据结构类中，通常会遇到给定中序和后序的情况下求前序的问题，或是给定前序和中序求后序的问题。
但一般情况下，当给定树的前序和后序时，并不能确定树的中序遍历。例如下面的这四个二叉树：它们都拥有着相同
的前序和后序。其实这种情况不仅仅限于二叉树，M叉树也是一样。输入描述：输入是由多个测试用例组成。每个用例
只有一行，格式为m s1 s2，表示树是m叉树，s1是前序遍历，s2是后序遍历。所有字符串将由小写字母字符组成。对于
所有的输入实例，1<=m<=20，s1和s2的长度将介于1和26之间（含1和26）。如果s1的长度是k（当然，s2也是这么长），
那使用的就是字母表的前K个字母。输入一行0表示终止输入。


【解题思路】：假设我们的前序是abejkcfghid，后序是jkebfghicda，
那么我们根据前序，就能知道：1、最多可以有13颗子树，也就是每一层都有13个可能位置2、a是根，第一课子树的根是b 3、通过后
树我们能知道，b的子树有j、k、e、b共四个结点4、再回到前序，向前走4个结点，下一棵子树的根是 c5、以此类推，最终得到 a 
为根的下一层共有 3 棵子树好了三颗子树长这样：前序 bejk cfghi d后序 jkeb fghic d则这一层一共的可能性就是13个空位随便挑
3个摆这3颗子树，那么有 种可能。之后再递归处理b这棵子树，bejk|jkeb，看以b为根时下一层有多少棵子树。可以看出，只有一棵
以e为根的子树，那么可能性就只有 种。再递归ejk|jke这棵树，可能情况自然是 种，递归cfghi|fghic这棵树，可能情况是 种。
最终算出这个结果即可。所以这道题根本上是排列组合问题，我们需要实现排列组合中的C这个方法。
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string> 
#include <tuple> 
#include <list> 
#include <cstdio>

// 求n的阶乘 
long long factorial(int n) { 
	long long r = 1; 
	for (int i = 1; i <= n; i++) { 
		r *= i; 
	}
	return r; 
}

// 求 n, m 的组合 C(n, m) 
// 利用 C(n, m) == C(n, n - m) 的特点，计算容易的 
long long combination(int n, int m) { 
	int max = m > (n - m) ? m : (n - m);
	long long numerator = 1; 
	for (int i = max + 1; i <= n; i++) { 
		numerator *= i; 
	}
	return numerator / factorial(n - max);
}
// 重命名类型，类似于 typedef 作用 
using PrePost = std::tuple<std::string, std::string>; 

// 给出一棵树的前序+后序，利用最上面注释的原理 
// 把每棵子树的前序+后序切分出来 
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
// 递归的求解每一层的可能性，直到树中只剩一个或者零个结点 
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