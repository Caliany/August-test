//二分查找
#if 0
#include <iostream>
#include <vector>
using namespace std;

class Solution{
public:
	int binarySearch(vector<int>num, int key){
		int left = 0, right = num.size() - 1, mid;
		while (left <= right){
			mid = (left + right) / 2;
			if (num[mid] == key){
				return mid;
			}
			else if (num[mid] > key){
				right = mid - 1;
			}
			else
				left = mid + 1;
		}
		return -1;
	}
};


//一个字符串中第一个出现N次的字符
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

char FindFirst(string str){
	assert(str.size() > 0);//先判空
	int hashtable[256] = { 0 };//建新数组，并初始化
	for (int i = 0; i < str.size(); i++){ //先遍历一遍数组，将遍历出的新数据放入新建的数组中
		hashtable[str[i]]++;
	}
	for (int i = 0; i < str.size(); i++){ // 在遍历新的数组
		if (hashtable[str[i] == 2]){
			return str[i];
		}
	}
	return 0;
}
int main(){
	string str[] = "absdjhabf";
	char ret = FindFirst(str);
	cout << ret << endl;
	system("pause");
	return 0;
}
#endif

#if 0
//字符串的删除
#include <string>
#include <iostream>
using namespace std;

int main(){
	string str1, str2;
	//cin>>str1;
	//cin>>str2;  //不能使用cin>>s输入，因为cin遇到空格就结束了
	getline(cin, str1);
	getline(cin, str2);//统计元素出现的次数
	int hashtabe[256] = { 0 };
	for (size_t i = 0; i < str2.size(); ++i){
		hashtabe[str2[i]]++;
	}

	//遍历str1表，如果str[1]映射hashtable表对应位置为0，则表示元素在
	string ret;
	for (size_t i = 0; i < str1.size(); ++i){
		if (hashtabe[str1[i]] == 0)
			ret += str1[i];
	}
	cout << ret << endl;
	return 0;
}

#endif

//链表的逆置(反转)利用尾插的思想
typedef struct ListNode Node;
struct ListNode* ReverseList(struct ListNode* Node){
	Node* pPre = NULL;
	Node* pCur = Head;
	Node* pNext = NULL;
	while (pCur){
		pNext = pCur->next;
		pCur->next = pPre;
		pPre = pCur;
		pCur = pNext;
	}
	return pPre;
}

//判断链表带不带环

ListNode* Ring(ListNode* list){
	ListNode *Slow = list;
	ListNode *Fast = list;
	if (list == NULL || list->next == NULL){
		return NULL;
	}
	Slow = Slow->next;
	Fast = Fast->next->next;
	while (Slow != Fast){
		if (Fast->next == NULL || Fast->next->next == NULL){
			return NULL;
		}
		Slow = Slow->next;
		Fast = Fast->next->next;
		
	}
	return Slow;//返回相遇点
}

//冒泡排序

void Swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void BuddleSort(int a[],int size){
	for (int i = 0; i < size - i; ++i){
		for (int j = 0; j < size - i - 1; ++j){
			if (a[j] <a[j + 1]){
				Swap(a,i,i+1);
			}
		}
	}
}

//堆排序
void swap(int data,int data1){
	int temp = data;
	data = data1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	data1 = temp;
}
void HeapSort(int a[],int i,int size){
	int left_child = i * 2 + 1;
	int right_child = i * 2 + 2;
	int max = i;
	if (left_child<size && a[left_child]>a[max])
		max = left_child;
	if (right_child<size && a[right_child]>a[max])
		max = right_child;
	if (max != i)
		swap(i,max);
	HeapSort(a, size, max);
}

/*
