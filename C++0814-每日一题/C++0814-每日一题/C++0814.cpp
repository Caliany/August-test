/*
ĳ�̵�涨����������ˮƿ���Ի�һƿ��ˮ��С��������ʮ������ˮƿ���������Ի�����ƿ��ˮ�ȣ�
����5ƿ���������£�����9����ƿ�ӻ�3ƿ��ˮ���ȵ�3ƿ���ģ������Ժ�4����ƿ�ӣ���3���ٻ�һƿ��
�ȵ���ƿ���ģ���ʱ��ʣ2����ƿ�ӡ�Ȼ�������ϰ��Ƚ����һƿ��ˮ���ȵ���ƿ���ģ������Ժ���3��
��ƿ�ӻ�һƿ���Ļ����ϰ塣���С��������n������ˮƿ�������Ի�����ƿ��ˮ�ȣ�

�⣺����һ������ѧ�⡣���ǿ��Զһ������ˮ��ƿ�ӱ��棬�ٰ�ʣ�µĿ�ƿ�ӱ��档Ȼ��ȵ���ˮ��
��ô�ȵ�����ˮ���ƿ�ƿ���ˣ�����֮ǰ�Ŀ�ƿ�ӣ����ܲ��ܼ����һ���ע�⵱��ǰ��ƿ�ӵ������� 2 ��ʱ�򣬿������ϰ���Ŷ��
*/
#include<iostream> 
#include<string> 
using namespace std;
int calculateNum(int num)
{ //�ܶһ��� 
	int sum = 0;
	while (num > 1)
	{ //ÿ��ƿ��һƿ 
		int result = num / 3;
		//ʣ�಻����ƿ���ȱ��� 
		int reminder = num % 3;
		sum = sum + result;
		//��һ�ο��Զһ��Ŀ�ƿ 
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
���������ַ���a,b�е�������Ӵ�
�������������ַ�a,b�е�������Ӵ������ж��������ڽ϶̴������ȳ��ֵ��Ǹ���
�⣺������Ƕ�̬�滮�ľ����⣬�����ҵ�ʱ�������ñ��������ķ�ʽ�����⡣����������Ĺ����ִ���
Ȼ����ĳ����ж����������ȳ��ֵ��Ǹ����ҵ�˼·�ǣ��ڳ����ַ������Ҷ̵��ַ�����û�ҵ�����
���̵��ַ���ȥ��β���� 1 ���ַ��������ң�û���ҵ�����ȥ��β���� 2 ���ַ���������ֱ��ֻ��һ��
�ַ�����û�ҵ���ȥ���ײ���һ���ַ�������ǰ��Ĳ�����ȥ��β���� 1 ���ַ��������ң�û���ҵ�����
ȥ��β���� 2 ���ַ�������������
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
