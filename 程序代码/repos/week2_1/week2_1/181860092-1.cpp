//#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
using namespace std;
struct Node
{
	int x;
	Node *next;
};
Node*head = 0;
void insert_at_beginning(int x)
{
	Node*h = new Node;
	h->x = x;
	h->next = head;
	head = h;
	h = 0;
}
void insert_at_ending(int x)
{
	Node*p = head;
	if (!p) insert_at_beginning(x);
	else
	{
		while (p->next) p = p->next;
		Node*h = new Node;
		h->x = x;
		p->next = h;
		h->next = 0;
		h = 0;
	}
}
void insert_after(int x,int y)
{
	Node*p = head;
	if (!p) return;
	while (p->x != x && p->next!= 0) p = p->next;
	if (p->x == x)
	{
		Node*h = new Node;
		h->x = y;
		Node*m = p->next;
		p->next = h;
		h->next = m;
	}
	}
void delete_node(int x)
{
	Node*p = head;
	if (!p) return;
	if (p->x == x) { Node*m = head; head = head->next; delete m; }
	else
	{
		while (p->next)
		{
			if (p->next->x != x)
				p = p->next;
			else break;
		}
		if (p->next || p->x == x)
		{
			Node*m = p->next;
			p->next = m->next;
			delete m;
		}
		else return;
	}
}

void print(int n)
{
	if (n < -1) {
		cout << endl; return;
	}
	else if(n==-1)
	{
		Node*p = head;
		while (p) {
			cout << p->x << " "; p=p->next;
		}
		cout << endl;
	}
	else
	{
		int i = 0; Node*p = head;
		while (p != 0) { p = p->next; ++i; }
		if (n >= i) print(-1);
		else 
		{
			i = 1; p = head;
			while (n >= i) { cout << p->x << " "; p = p->next; ++i; }
			cout << endl;
		}
	}
}
int length(Node*node)
{
	Node*p = head;
	if (!p) return 0;
	int i = 1;
	while (p->next) { p = p->next; ++i; }
	return i;
}
void reverse_print(Node*node, int n)
{
	Node*p = node;
	if (n < -1 || !p || n == 0)
		return;
	else
	{
		if (n == -1) {
			int y = length(node);
			reverse_print(node, y);
		}
	    else
		{
		reverse_print(node->next, n - 1);
		cout << p->x << " ";
		}
	}
}
bool str_equal(char *s1,const char*s2)
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

		if (str_equal(str,"insert_at_beginning"))
		{
			cin >> a;
			insert_at_beginning(a);
		}
		else if (str_equal(str, "insert_at_ending"))
		{
			cin >> a;
			insert_at_ending(a);
		}
		else if (str_equal (str, "delete"))
		{
			cin >> a;
			delete_node(a);
		}
		else if (str_equal(str,"insert_after"))
		{
			cin >> a >> b;
			insert_after(a, b);
		}
		else if (str_equal(str,"print"))
		{
			cin >> a;
			print(a);
		}
		else if (str_equal(str,"reverse_print"))
		{
			cin >> a;
			reverse_print(head, a);
			cout << endl;
		}
	}
	return 0;
}