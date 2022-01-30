#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
using namespace std;
struct Node
{
	char str[20] = { '\0' };
	Node *next;
};//解决冲突
struct HASH
{
	bool flag = 0;
	Node *a;
};//哈希数组的一个元素
HASH ha[2333];
void to_lower(char *s)
{
	while ((*s) != '\0')
	{
		if ((*s) >= 'A' && (*s) <= 'Z')
			(*s) += 'a' - 'A';
		++s;
	}
}
bool str_equal(char *s1, char*s2)
{
	to_lower(s1); to_lower(s2);
	bool flag = 1;
	while ((*s1) != '\0')
	{
		if (*s1 != *s2) { flag = 0; break; }
		s1++; s2++;
	}
	if (flag == 1 && *s2 != '\0') flag = 0;
	return flag;
}
namespace A
{
	int hash(char*s)
	{
		int res = 0;
		for (char*c = s; *c != '\0'; ++c) {
			res = res * 26 + (*c - 'a');
			res = res % 2333;
		}
		return res;
	}
}
void hit_insert(char *s)
{
	to_lower(s);
	int n = A::hash(s);
	Node *p = ha[n].a;
	if (str_equal(p->str, s)) return;
	else
	{
		while (p->next != 0)
		{
			if (str_equal(p->str, s)) return;
			else p = p->next;
		}
		Node *m = new Node;
		p->next = m; m->next = 0;
		int i = 0;
		while (s[i] != '\0') { m->str[i] = s[i]; ++i; }
	}

}
bool ht_find(char *s)
{
	to_lower(s);
	int n = A::hash(s);
	if (ha[n].flag == 0) return 0;
	else
	{
		bool flag_ = 0;
		while (ha[n].a != 0)
		{
			if (str_equal(ha[n].a->str, s)) { flag_ = 1; break; }
			else ha[n].a = ha[n].a->next;
		}
		return flag_;
	}
}
int main()
{
	FILE *fp = fopen("C://article(2).txt", "r");
	if (fp == 0) { cerr << "文件打开失败\n"; system("pause"); exit(-1); }
	else
	{
		char ch = fgetc(fp);
		while (ch != EOF)
		{
			int i = 0; char word[20] = { '\0' };
			while (!((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) && ch != EOF) ch = fgetc(fp);
			while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) { word[i] = ch; ++i; ch = fgetc(fp); }
			to_lower(word);
			int n = A::hash(word);
			if (ha[n].flag == 0)
			{
				ha[n].flag = 1; ha[n].a = new Node;
				ha[n].a->next = 0;
				int x = 0;
				while (word[x] != '\0') { ha[n].a->str[x] = word[x]; ++x; }
			}
			else if (ha[n].flag == 1)
			{
				hit_insert(word);
			}
		}
		fclose(fp);
		char str_[20] = { '\0' };
		while (cin >> str_)
		{
			if (ht_find(str_)) cout << "True" << endl;
			else cout << "False" << endl;
		}
		system("pause");
		return 0;
	}

}