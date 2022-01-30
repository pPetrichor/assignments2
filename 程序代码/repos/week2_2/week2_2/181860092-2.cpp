#include<iostream>
using namespace std;
struct TNode {
	int x;
	TNode* a[10];
};
TNode*head = 0;
void init(TNode*p)
{
	p->x = 0;
	for (int i = 0; i < 10; ++i)  p->a[i] = 0;
}
void insert_at_root(int x)
{
	if (head)
	{
		TNode*h = new TNode;
		init(h);
		h->x = x;
		h->a[0] = head;
		head = h;
	}
	else 
	{
		head = new TNode;
		init(head);
		head->x = x;
	}
}
void insert_after(TNode *node, int x, int y)
{
	if (node == 0) return;
	bool flag = 0;
	if(node->x==x)
	{
		TNode*p = new TNode;
		init(p);
		p->x = y;
		int i = 0;
		while (node->a[i] != 0) ++i;
		node->a[i] = p;
		flag = 1;
	}
	else
	{
		for (int i = 0; node->a[i] != 0; ++i)
		{
			if (flag == 1) break;
			insert_after(node->a[i], x, y);
		}
	}
}
bool flag = 0;
void delete_node(TNode *node, int x)
{
	if (node == 0 || flag == 1) return;
	int n = 0;
	if (node->x == x && node->a[0] == 0) { delete head; head = 0; return; }
	while (node->a[n] != 0)
	{
		if (node->a[n]->x == x) {
			flag = 1; break;
		}
		++n;
	}
	if (flag)
	{
		if (node->a[n]->a[0]) return;
		else
		{
			TNode*p = node->a[n];
			delete p;
			p = 0;
			node->a[n] = 0;
			while(node->a[n+1])
			{
				node->a[n] = node->a[n + 1];
				++n;
			}
			node->a[n] = node->a[n + 1];//将所有子节点位置调整，仍占a[0]-a[n-1]的位置
		}
	}
	else
	{
		for (int i = 0; node->a[i] != 0; ++i)
		{
			delete_node(node->a[i], x);
		}
	}
}
void print(TNode *node, int n)
{
	if (!node||n<-1||n==0) {
		return;
	}
	if(n==-1){
		cout << node->x << " ";
		for (int i = 0; node->a[i] != 0; ++i)
			print(node->a[i], n);
	}
	else {
		cout << node->x << " ";
		for (int i = 0; node->a[i] != 0; ++i)
			print(node->a[i],n-1);
	}
}
bool str_equal(char *s1, const char*s2)
{
	bool flag = 1;
	while ((*s1) != '\0')
	{
		if (*s1 != *s2) { flag = 0; break; }
		s1++; s2++;
	}
	return flag;
}
int main()
{
	char str[30] = { '\0' };
	int a = 0, b = 0;
	while (cin >> str)
	{

		if (str_equal(str, "insert_at_root"))
		{
			cin >> a;
			insert_at_root(a);
		}
		else if (str_equal(str, "delete"))
		{
			cin >> a;
			delete_node(head,a);
			flag = 0;
		}
		else if (str_equal(str, "insert_after"))
		{
			cin >> a >> b;
			insert_after(head, a, b);
		}
		else if (str_equal(str, "print"))
		{
			cin >> a;
			print(head,a);
			cout << endl;
		}
	}
	return 0;
}