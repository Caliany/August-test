/*
某商店规定：三个空汽水瓶可以换一瓶汽水。小张手上有十个空汽水瓶，她最多可以换多少瓶汽水喝？
答案是5瓶，方法如下：先用9个空瓶子换3瓶汽水，喝掉3瓶满的，喝完以后4个空瓶子，用3个再换一瓶，
喝掉这瓶满的，这时候剩2个空瓶子。然后你让老板先借给你一瓶汽水，喝掉这瓶满的，喝完以后用3个
空瓶子换一瓶满的还给老板。如果小张手上有n个空汽水瓶，最多可以换多少瓶汽水喝？

解：这是一个纯数学题。我们可以兑换后的汽水的瓶子保存，再把剩下的空瓶子保存。然后喝掉汽水，
那么喝掉的汽水优势空瓶子了，加上之前的空瓶子，看能不能继续兑换。注意当当前空瓶子的数量是 2 的时候，可以向老板借的哦！
*/
#include<iostream> 
#include<string> 
using namespace std;
int calculateNum(int num)
{ //总兑换数 
	int sum = 0;
	while (num > 1)
	{ //每三瓶换一瓶 
		int result = num / 3;
		//剩余不足三瓶的先保留 
		int reminder = num % 3;
		sum = sum + result;
		//下一次可以兑换的空瓶 
		num = result + reminder;
		if (num == 2)
		{
			++sum;
			break;
		}
	}
	return sum;
}
int main()
{
	int number;
	while (cin >> number)
	{
		cout << calculateNum(number) << endl;
	}
	return 0;
}


/*
abcdefghijklmnop
abcsafjklmnopqrstuv
查找两个字符串a,b中的最长公共子串
查找两个两个字符a,b中的最长公共子串。若有多个，输出在较短串中最先出现的那个。
解：这道题是动态规划的经典题，但是我当时解题是用暴力搜索的方式来解题。首先是找最长的公共字串，
然后最长的长度有多个，输出最先出现的那个。我的思路是：在长的字符串中找短的字符串，没找到，则
将短的字符串去掉尾部的 1 个字符，继续找，没有找到，则去掉尾部的 2 个字符，继续，直到只有一个
字符；还没找到就去掉首部的一个字符，继续前面的操作，去掉尾部的 1 个字符，继续找，没有找到，则
去掉尾部的 2 个字符，继续……。
*/

#include<iostream>	
#include<string>
using namespace std;
void Solution(string& str1, string& str2)
{
	string minstr;
	string maxstr;
	if (str1.size() > str2.size())
	{
		minstr = str2;
		maxstr = str1;
	}
	else
	{
		minstr = str1;
		maxstr = str2;
	}
	string res;
	for (int i = 0; i < minstr.size(); ++i)
	{
		for (int j = minstr.size(); j >= 0; --j)
		{
			string tmp = minstr.substr(i, j);
			if (maxstr.find(tmp) != string::npos)
			{
				if (tmp.size() > res.size())
				{
					res = tmp;
				}
			}
		}
	}
	cout << res << endl;
}
int main()
{
	string str1;
	string str2;
	while (cin >> str1 >> str2)
	{
		Solution(str1, str2);
	}
	return 0;
}
