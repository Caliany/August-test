//���ֲ���
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


//һ���ַ����е�һ������N�ε��ַ�
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

char FindFirst(string str){
	assert(str.size() > 0);//���п�
	int hashtable[256] = { 0 };//�������飬����ʼ��
	for (int i = 0; i < str.size(); i++){ //�ȱ���һ�����飬���������������ݷ����½���������
		hashtable[str[i]]++;
	}
	for (int i = 0; i < str.size(); i++){ // �ڱ����µ�����
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
//�ַ�����ɾ��
#include <string>
#include <iostream>
using namespace std;

int main(){
	string str1, str2;
	//cin>>str1;
	//cin>>str2;  //����ʹ��cin>>s���룬��Ϊcin�����ո�ͽ�����
	getline(cin, str1);
	getline(cin, str2);//ͳ��Ԫ�س��ֵĴ���
	int hashtabe[256] = { 0 };
	for (size_t i = 0; i < str2.size(); ++i){
		hashtabe[str2[i]]++;
	}

	//����str1�����str[1]ӳ��hashtable���Ӧλ��Ϊ0�����ʾԪ����
	string ret;
	for (size_t i = 0; i < str1.size(); ++i){
		if (hashtabe[str1[i]] == 0)
			ret += str1[i];
	}
	cout << ret << endl;
	return 0;
}

#endif

//���������(��ת)����β���˼��
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

//�ж������������

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
	return Slow;//����������
}

//ð������

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

//������
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
