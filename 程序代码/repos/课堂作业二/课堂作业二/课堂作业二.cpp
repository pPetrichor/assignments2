#include<iostream>
#include<math.h>
using namespace std;
struct Po
{
	int xishu;
	int cishu;
	Po *next;
};
int get_Po(char*str, int m, Po*p)
{
	char shu[20] = { '\0' };
	int j = 0, k = 0;
	while (str[m] != 'x') { shu[j] = str[m]; ++m; ++j; }
	int n = strlen(shu) - 2; int sum = 0;
	for (int i = 1; n >= 0; ++i) { sum += (shu[i] - '0') * pow(10, n); --n; }
	if (shu[0] == '-') p->xishu = -sum;
	else p->xishu = sum;
	int x = strlen(shu);
	for (int i = 0; i < x; ++i) shu[i] = '\0';
	m += 2;
	while (str[m] != '+'&&str[m] != '-'&&str[m] != '\0')
	{
		shu[k] = str[m];
		++m; ++k;
	}
	if (shu[0] == '-') n = strlen(shu) - 2; else n = strlen(shu) - 1; sum = 0;
	for (int i = 0; n >= 0; ++i) { if (shu[0] == '-') ++i; sum += (shu[i] - '0') * pow(10, n); --n; }
	if (shu[0] == '-') p->cishu = -sum;
	else p->cishu = sum;
	for (int i = 0; i < strlen(shu); ++i) shu[i] = '\0';
	return m;
}
Po InitPo(char*str)
{
	int m = 0;
	Po *h = new Po;
	Po *p = h;
	m = get_Po(str, m, h);
	h->next = 0;
	while (str[m] != '\0')
	{
		Po *q = new Po;
		m = get_Po(str, m, q);
		bool flag = 0;
		for (Po*t = h; t != 0; t = t->next)
		{
			if (q->cishu == t->cishu)
			{
				t->xishu += q->xishu;
				flag = 1;
				delete q;
				break;
			}
		}
		if (!flag)
		{
			p->next = q;
			q->next = 0;
			p = p->next;
		}
	}
	return *h;
}
void swap(Po *h, Po *&head)
{
	if (h == head)
	{
		Po *t = h->next;
		h->next = t->next;
		t->next = h;
		head = t;
	}
	else
	{
		Po *t = head;
		while (t->next != h) t = t->next;
		t->next = h->next;
		h->next = t->next->next;
		t->next->next = h;
	}
}
Po *copy__(Po a)//复制链表
{
	if (&a == 0) return 0;
	Po *h = new Po;
	Po *head = h;
	h->cishu = a.cishu; h->xishu = a.xishu; h->next = 0;
	if (a.next != 0) a = *a.next; else return head;
	bool flag = 1;
	while(flag)
	{
		Po *p = new Po;
		p->cishu = a.cishu; p->xishu = a.xishu;
		h->next = p; 
		if (a.next != 0) a = *a.next; else flag = 0;
		h = h->next;
	}
	h->next = 0;
	return head;
}
void kill(Po *a)
{
	while(a!=0)
	{
		Po*t = a;
		a = a->next;
		delete t;
	}
}
void PrintPo(Po hi)
{

	Po *h = copy__(hi);
	Po *head = h;
	int len = 0;
	while (h != 0) { ++len; h = h->next; }
	h = head;//还原头指针
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (h->cishu < h->next->cishu) swap(h, head); //交换后h指的是交换后后面的结点，不必再h=h->next
			else h = h->next;
		}
		h = head;
	}
	cout << "多项式为：";
	for (; head != 0; head = head->next)
	{
		if (head->xishu > 0) cout << "+" << head->xishu << "x^" << head->cishu;
		else if (head->xishu < 0) cout << head->xishu << "x^" << head->cishu;
	}
	cout << endl;
	kill(h);
}
Po Add(Po a,Po b)
{
	Po *ap = copy__(a);
	Po *bp = copy__(b);
	Po *h = bp, *m = ap;
	for(;ap!=0;ap=ap->next)
		for(bp=h;bp!=0;)
		{
		if(bp->cishu==ap->cishu)
		{
			ap->xishu += bp->xishu;
			if (bp == h)
			{
				h = h->next;
				bp = h;
			}
			else
			{
				Po *t = &b;
				while (t->next != bp) t = t->next;
				t->next = bp->next;
				bp = bp->next;
			}
		}
		else bp = bp->next;
		}
	ap = m;
	while (ap->next != 0) ap = ap->next;
	ap->next = h;
	return *m;
}
Po Minus(Po a, Po b)
{
	Po *ap = copy__(a);
	Po *bp = copy__(b);
	Po *h = bp, *m = ap;
	for (; ap != 0; ap = ap->next)
		for (bp = h; bp != 0;)
		{
			if (bp->cishu == ap->cishu)
			{
				ap->xishu -= bp->xishu;
				if(bp==h) { h = h->next; bp = h; }
				else
				{
					Po *t = &b;
					while (t->next != bp) t = t->next;
					t->next = bp->next;
					bp = bp->next;
				}
			}
			else 
			{
				bp->xishu = -bp->xishu; bp = bp->next;
			}
		}
	ap = m;
	while (ap->next != 0) ap = ap->next;
	ap->next = h;
	return *m;
}
int main()
{
	const int nMaxLen = 200;
	char str1[nMaxLen], str2[nMaxLen], str3[nMaxLen], str4[nMaxLen];
	cin >> str1>> str2 >> str3 >> str4;
	Po poly1 = InitPo(str1); 
	Po poly2 = InitPo(str2);
	Po poly3 = InitPo(str3);
	Po poly4 = InitPo(str4);
	PrintPo(poly1);
	PrintPo(poly2);
	PrintPo(poly3);  
	PrintPo(poly4);  
	PrintPo(Add(poly1, poly2));
	PrintPo(Minus(poly2, poly1));
	PrintPo(Add(poly1, poly1));
	PrintPo(Minus(poly1, poly1));
	system("pause");
	return 0;
}