#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;
const bool USE_SUITS = false;
const int N_CARD_VALUES = 15;
struct card
{
	int n;
	string s;
	card *next;
};
card*current_card = 0;
int judge(const card*a)
{
	int m[20] = { 0 };
	int i = 0;
	while (a)
	{
		m[i] = a->n;
		a = a->next;
		++i;
	}
	if (m[1] == 0 && m[0] == 1) return 1;//单牌
	if (m[1] == 0 && m[0] == 2) return 2;//对子
	if (m[1] == 0 && m[0] == 3) return 3;//三带零
	if (m[1] == 0 && m[0] == 4) return 4;//炸弹
	if (m[2] == 0 && ((m[0] == 1 && m[1] == 3) || (m[0] == 3 && m[1] == 1))) return 5;//三带一
	if (m[2] == 0 && ((m[0] == 2 && m[1] == 3) || (m[0] == 3 && m[1] == 2))) return 6;//三带二
	if (m[2] == 0 && (m[0] == 1 && m[1] == 1)) return 7;//王炸
	if (m[2] == 0 && ((m[0] == 4 && m[1] == 2) || (m[0] == 2 && m[1] == 4))) return 8;
	bool flag1 = 1; bool flag2 = 1; bool flag3 = 1; int k = 0;
	while (m[k])
	{
		if (m[k] != 2) flag2 = 0;
		if (m[k] != 1) flag1 = 0;
		if (m[k] != 3) flag3 = 0;
		++k;
	}
	if (flag2) return 10;//连对
	if (flag1) return 11;//顺子
	if (flag3) return 12;//飞机不带翼
}
int s_to_n(string s)
{
	if (s == "3") return 1;
	if (s == "4") return 2;
	if (s == "5") return 3;
	if (s == "6") return 4;
	if (s == "7") return 5;
	if (s == "8") return 6;
	if (s == "9") return 7;
	if (s == "10") return 8;
	if (s == "J") return 9;
	if (s == "Q") return 10;
	if (s == "K") return 11;
	if (s == "A") return 12;
	if (s == "2") return 13;
	if (s == "joker") return 19;
	if (s == "JOKER") return 20;
}
void sort1(card*h, int x)//从大到小排序
{
	card*m = h;
	m = h;
	for (int i = 0; i < x - 1; ++i)
	{
		for (int j = 0; j < x - i - 1; ++j)
		{
			if (s_to_n(m->s) < s_to_n(m->next->s))
			{
				int a = m->n; string b = m->s;
				m->n = m->next->n; m->s = m->next->s;
				m->next->n = a; m->next->s = b;
			}
			m = m->next;
		}
		m = h;
	}
}
int length(card*h)
{
	int n = 0;//n记录结点个数
	card*m = h;
	while (m) { m = m->next; ++n; }
	return n;
}
void sort2(card*h)//按牌型排
{
	card*m = h;
	for (int i = 0; i < length(h) - 1; ++i)
	{
		for (int j = 0; j < length(h) - i - 1; ++j)
		{
			if (m->n < m->next->n)
			{
				int a = m->n; string b = m->s;
				m->n = m->next->n; m->s = m->next->s;
				m->next->n = a; m->next->s = b;
			}
			m = m->next;
		}
		m = h;
	}
}
void sort_cout(string *s, int x)//从大到小排序并输出
{
	for (int i = 0; i < x - 1; ++i)
	{
		for (int j = 0; j < x - i - 1; ++j)
		{
			if (s_to_n(s[j]) < s_to_n(s[j + 1]))
			{
				string a = s[j];
				s[j] = s[j + 1];
				s[j + 1] = a;
			}
		}
	}
	int i = 0;
	while (i < x) { cout << s[i] << " "; ++i; } cout << endl;
}
int num_over_x(int x, card*h)
{
	int n = 0;
	sort2(h);
	while (h->n > x) { ++n; h = h->next; }
	return n;
}
card*cut(int n, card*&h)//截断链表，返回截断点处地址
{
	if (h->n < n) { card*r = h; h = 0; return r; }
	card*m = h;
	while (m->next) m = m->next;
	if (m->n == n) return 0;//无需截断
	else if (m->n < n)
	{
		if (!h->next) { h = 0; return m; }
		m = h;
		while (m->next->n >= n) m = m->next;
		card*p = m->next;
		m->next = 0;
		return p;
	}
	else return 0;
}
void get_card(string s, card* &holds)//整牌
{
	card *p = holds;
	while (p)
	{
		if (s == p->s) { p->n++; break; }
		else  p = p->next;
	}
	if (!p)
	{
		card*q = new card;
		q->n = 1;
		q->s = s;
		q->next = 0;
		p = holds;
		if (!p) holds = q;
		else
		{
			while (p->next) p = p->next;
			p->next = q;
		}
	}
}
void show(card*h)
{
	sort1(h, length(h)); sort2(h);
	while(h)
	{
		for (int i = 0; i < h->n; ++i) cout << h->s << " ";
		h = h->next;
	}
	cout << endl;
}
card *copy__(card *a)//复制链表
{
	if (a == 0) return 0;
	card *h = new card;
	card *head = h;
	h->n = a->n; h->s = a->s; h->next = 0;
	if (a->next != 0) a = a->next; else return head;
	bool flag = 1;
	while (flag)
	{
		card *p = new card;
		p->n = a->n; p->s = a->s;
		h->next = p;
		if (a->next != 0) a = a->next; else flag = 0;
		h = h->next;
	}
	h->next = 0;
	return head;
}
void clear(card* &head)
{
	card*p = head;
	if (!p) return;
	else
	{
		card* q;
		card*m = p->next;p = 0;
		while (m)
		{
			
			q = m->next;
			delete m;
			m = q;
		}
		
		head = 0; m = 0; q = 0;
	}
}
const string CARD_VALUES[] = {
	"3", "4", "5", "6",
	"7", "8", "9", "10",
	"J", "Q", "K", "A", "2",
	"joker", "JOKER"
};
const int N_CARD_SUITS = 4;
const string CARD_SUITS[] = {
	"Spade", "Heart", "Diamond", "Club"
};
int my_random(int i) {
	return std::rand() % i;
}
vector<string> get_new_deck() {
	vector<string> deck;
	for (int i = 0; i < N_CARD_VALUES - 2; ++i) {
		for (int j = 0; j < N_CARD_SUITS; ++j) {
			string card = CARD_VALUES[i];
			if (USE_SUITS) card = CARD_SUITS[j] + "_" + card;
			deck.push_back(card);
		}
	}
	deck.push_back(CARD_VALUES[13]);
	deck.push_back(CARD_VALUES[14]);
	return deck;
}
bool case1_3(card*&holds, card*&input, int x)//单牌、对子、三带零出牌
{
	sort1(holds, length(holds));
	sort2(holds);
	card*p = holds;
	while (p) { if (p->n != x)  p = p->next; else break; }
	if (p)//有单牌、对子、三带零
	{
		card*m = cut(x, holds);
		if (!p->next && (s_to_n(p->s) > s_to_n(input->s)))
		{
			clear(current_card);
			for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
			cout << endl;
			p->n -= x;
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		if (p->next)
		{
			while (p->next)
			{
				if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
				else break;
			}
			if (p->next)
			{
				clear(current_card);
				for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
				cout << endl;
				p->n -= x;
				p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//补好
				return 1;
			}
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				clear(current_card);
				for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
				cout << endl;
				p->n -= x; p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//补好
				return 1;
			}
		}
		sort1(holds, num_over_x(x, holds)); p = holds;
		if (!p->next)
		{
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 0;
		}
		while (p->next->n > x)
		{
			if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
			else break;
		}
		if (p->next->n > x)
		{
			clear(current_card);
			for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
			cout << endl;
			p->n -= x; p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			clear(current_card);
			for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
			cout << endl;
			p->n -= x; p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//补好
	}
		sort1(holds, length(holds)); sort2(holds); p = holds;
		card*m = cut(x, holds);
		if(p->n<=x)
		{
			holds = p;
			return 0;
		}
		while (p->next)
		{
			if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
			else break;
		}
		if (p->next)
		{
			clear(current_card);
			for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
			cout << endl;
			p->n -= x; p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			clear(current_card);
			for (int i = 0; i < x; ++i) { cout << p->s << " "; get_card(p->s, current_card); }
			cout << endl;
			p->n -= x; p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//补好
		return 0;//在不出炸弹和王炸前提下出牌成功返回1，否则0
}
bool case4(card*&holds, card*&input)//炸弹出牌
{
	bool flag = 0;
	sort1(holds, length(holds));
	if (holds->s == "JOKER"&&holds->next) { if (holds->next->s == "joker") flag = 1; }
	sort2(holds);
	card*m=cut(4, holds);
	if (!holds&&flag == 1) 
	{ 
		card*p = holds;
		if (!p) holds = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//补好

		clear(current_card);
		sort1(holds, length(holds));
		cout << holds->s << " "; holds->n--; get_card(holds->s, current_card); holds = holds->next;
		cout << holds->s << " "; holds->n--; get_card(holds->s, current_card);
		 return 1;
	}
	else if (!holds&&flag != 1) { cout << "pass"; return 0; }
	else
	{
		card*p = holds;
		while (p->next)
		{
			if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
			else break;
		}
		if (p->next)
		{
			clear(current_card);
			int o = 0;
			while (o < 4)
			{
				cout << p->s << " "; p->n--; get_card(p->s, current_card);
				++o;
			}
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			clear(current_card);
			int o = 0;
			while (o < 4)
			{
				cout << p->s << " "; p->n--; get_card(p->s, current_card);
				++o;
			}
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		else if (flag == 1) 
		{
			if (!p) p = m;
			else 
			{
				while (p->next) p = p->next; p->next = m;
			}//补好
			sort1(m, length(m));
			cout << m->s << " "; m->n--; get_card(m->s, current_card); m = m->next;
			cout << m->s << " "; m->n--; get_card(m->s, current_card); return 1;
		}
		else { cout << "pass"; return 0; }
	}
}
bool case5_6(card*holds, card*input, int x)//三带一及三带二
{
	string flag3 = "null"; string flagx = "null";
	sort1(holds, length(holds));
	sort2(holds);
	card*m = cut(3, holds);
	card*p = holds;
	if (!holds) 
	{
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//补好
		return 0; 
	}
	while (p) { if (p->n != 3)  p = p->next; else break; }
	if (p)//有三
	{
		if (!p->next && (s_to_n(p->s) > s_to_n(input->s)))
		{
			flag3 = p->s; p->n -= 3;
		}
		else if (p->next)
		{
			while (p->next)
			{
				if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
				else break;
			}
			if (p->next) flag3 = p->s;
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				flag3 = p->s; p->n -= 3;
			}
		}
		else
		{
			sort1(holds, num_over_x(3, holds)); p = holds;
			if (p->n == 3&&p->next) { while (p->next) p = p->next; p->next = m; return 0; }
			else if (p->n == 3) { p->next = m; return 0; }
			while (p->next->n > 3)
			{
				if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
				else break;
			}
			if (p->next->n > x)
			{
				flag3 = p->s; p->n -= 3;
			}
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				flag3 = p->s; p->n -= 3;
			}
		}
	}
	else
	{
		sort1(holds, length(holds)); p = holds;
		while (p->next)
		{
			if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
			else break;
		}
		if (p->next)
		{
			flag3 = p->s; p->n -= 3;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			flag3 = p->s; p->n -= 3;
		}
	}
	if (flag3 == "null")
	{
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//补好
		return 0;
	}
	sort1(holds, length(holds)); sort2(holds); 
	p = holds;
	if (!p) p = m;
	else {
		while (p->next) p = p->next; p->next = m;
	}//补好
	sort2(holds);
	p = holds;
	m=cut(x, holds);
	if (p)
	{
		if (!p->next) { flagx = p->s; p->n -= x; }
		else
		{
			while (p->next) p = p->next;
			flagx = p->s; p->n -= x;
		}
	}
	if (flag3 != "null"&&flagx != "null")
	{
		clear(current_card);
		for (int i = 0; i < 3; ++i)  get_card(flag3, current_card);
		if (s_to_n(flag3) > s_to_n(flagx))
		{
			cout << flag3 << " " << flag3 << " " << flag3 << " ";
			for (int i = 0; i < x; ++i) { cout << flagx << " "; get_card(flagx, current_card); }
			cout << endl;
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
		else
		{
			clear(current_card);
			for (int i = 0; i < 3; ++i)  get_card(flag3, current_card);
			for (int i = 0; i < x; ++i) {cout << flagx << " "; get_card(flagx, current_card);}
			cout << flag3 << " " << flag3 << " " << flag3 << " ";
			cout << endl;
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//补好
			return 1;
		}
	}
	p = holds;
	if (!p) p = m;
	else {
		while (p->next) p = p->next; p->next = m;
	}//补好
	return 0;//在不出炸弹和王炸前提下出牌成功返回1，否则0
}
string str3 = "null"; int number = 0;
bool panduan(card*holds, card*input, int x, int l, string*d)
{
	sort2(holds);
	card*j = cut(x, holds);
	sort1(holds, length(holds));
	if (holds->s == "JOKER" || holds->s == "joker") holds = holds->next;
	card*h = holds;
	if (length(h) < length(input)) { if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 0; } }
	sort1(input, length(input));
	string s = input->s;
	if (s_to_n(h->s) <= s_to_n(s)) { if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 0; } }
	card*e = holds; int i = 0;
	while (i < length(input) - 1) { e = e->next; ++i; }
	while (e->next)
	{
		if (s_to_n(h->s) - s_to_n(e->s) == length(input) - 1)
		{
			if (!e->next) break;
			if (s_to_n(h->next->s) - s_to_n(e->next->s) == length(input) - 1 && s_to_n(h->next->s) > s_to_n(s))
			{
				h = h->next; e = e->next;
			}
			else break;
		}
		else { h = h->next; e = e->next; }
	}
	if ((e->next) || (s_to_n(h->s) - s_to_n(e->s) == length(input) - 1))
	{
		if (l == 1)
		{
			clear(current_card);
			while (h != e)
			{
				for (int i = 0; i < x; ++i) {
					cout << h->s << " "; h->n--; get_card(h->s, current_card);
				}
				h = h->next;
			}
			for (int i = 0; i < x; ++i) { cout << e->s << " "; get_card(e->s, current_card);} e->n -= x;
			cout << endl;
			h = holds;
			{ if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 1; } }
		}
	}
	else { h = holds; if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; }return 0; }
}
bool case10_12(card*holds, card*input, int x)//连对、顺子和飞机不带翼
{
	sort2(holds);
	card*t = holds;
	if (t->n < x) return 0;
	while (t)
	{
		if (t->n > x) t = t->next;
		else break;
	}
	if (t->n != x) return 0;
	if (panduan(t, input, x, 1, 0)) return 1;
	else if (panduan(holds, input, x, 1, 0)) return 1;
	else return 0;
}//在不出炸弹和王炸前提下出牌成功返回1，否则0
string s0;
bool case_1(card*m,int t,int p)//t表类型,飞机连对或顺子
{
	sort1(m, length(m)); sort2(m);
	card*h = copy__(m);
	if (h->n < t) return 0;
	while(h)
	{ if (h->n > t) h = h->next;
	else break;
	}
	if (t == 1 && !h) return 0;
	cut(t, h);
	if(h)
	{
		int num = 1; int count = 1;
		card*k = h;
		while (k->next) { ++num; k = k->next; }
		while (num >= p)
		{
			if (s_to_n(h->s) - s_to_n(h->next->s) == 1)
			{
				s0 = h->s; count++; h = h->next;
				if (count >= p) return 1;
			}
			else { h = h->next; count = 1; }
			num--;
		}
	}
	return 0;
}
bool case_2(card*m,int t)//三带1/2/0
{
	sort1(m, length(m)); sort2(m);
	card*h = copy__(m);
	card*p=cut(3, h);
	if (!h) return 0;
	if(h->n>=3)
	{
		while (h) { if ((h->n) > 3) h = h->next; else break; }
		if(h)
		{
			if (t == 0) return 1;
			while (h->next) h = h->next; h->next = p;
			while (h->n > t) h = h->next;
			if (h)
			{
				if (h->n == t) return 1;
			}
		}
	}
	return 0;
}
bool case_3(card*m)
{
	sort1(m, length(m)); sort2(m);
	while (m->n > 2) m = m->next;
	if(m)
	{
		if (m->n == 2) return 1;
	}
	return 0;
}
bool case_4(card*m)
{
	sort1(m, length(m)); sort2(m);
	if (m->n == 4) return 1;
	return 0;
}
bool case_5(card*m)
{
	sort1(m, length(m));
	if(m->s=="JOKER"&&m->next)
	{
		if (m->next->s == "joker") return 1;
	}
	return 0;
}
void chupai(card*m)//顺序：飞机、连对、顺子、三带、对子、炸弹、单牌
{
	sort1(m, length(m)); sort2(m);
	card*t = m; clear(current_card);
	if (case_1(m, 3, 2)) 
	{
		while (t->s != s0) t = t->next;
		int o = 0;
		while (o < 3)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		while(t->next)
		{
			if(t->next->n==3)
			{
				if (s_to_n(t->s) - s_to_n(t->next->s) == 1)
				{
					o = 0; t = t->next;
					while (o < 3)
					{
						cout << t->s << " "; t->n--; get_card(t->s, current_card);
						++o;
					}
				}
				else break;
			}
			else break;
		}
		cout << endl;
		return;
	}
	if (case_1(m, 2, 3))
	{
		while (t->s != s0) t = t->next;
		int o = 0;
		while (o < 2)
		{
			cout << t->s << " "; t->n--;get_card(t->s, current_card);
			++o;
		}
		while (t->next)
		{
			if (t->next->n == 2)
			{
				if (s_to_n(t->s) - s_to_n(t->next->s) == 1)
				{
					o = 0; t = t->next;
					while (o < 2)
					{
						cout << t->s << " "; t->n--; get_card(t->s, current_card);
						++o;
					}
				}
				else break;
			}
			else break;
		}
		cout << endl;
		return;
	}
	if (case_1(m, 1, 5))
	{
		while (t->s != s0) t = t->next;
		cout << t->s << " "; t->n--; get_card(t->s, current_card);
		while (t->next)
		{
			if (s_to_n(t->s) - s_to_n(t->next->s) == 1)
			{
				cout << t->s << " "; t->n--; get_card(t->s, current_card);
			}
			else break;
		}
		cout << endl;
		return;
	}
	if (case_2(m, 2))
	{
		while (t->n > 3) t = t->next; int o = 0;
		while (o < 3)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		while (t->n != 2) t = t->next; o = 0;
		while (o < 2)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		cout << endl;
		return;
	}
	if (case_2(m, 1))
	{
		while (t->n > 3) t = t->next; int o = 0;
		while (o < 3)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		while (t->n != 1) t = t->next;
		cout << t->s << " "; t->n--; get_card(t->s, current_card);
		cout << endl;
		return;
	}
	if (case_2(m, 0)) 
	{
		while (t->n > 3) t = t->next;
		int o = 0;
		while (o < 3)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		cout << endl;
		return;
	}
	if (case_3(m)) 
	{
		while (t->n > 2) t = t->next;
		int o = 0;
		while (o < 2)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		cout << endl;
		return;
	}
	if (case_4(m)) 
	{
		int o = 0;
		while (o < 4)
		{
			cout << t->s << " "; t->n--; get_card(t->s, current_card);
			++o;
		}
		cout << endl; return;
	}
	if (case_5(m)) 
	{
		sort1(m, length(m));
		cout << m->s << " "; m->n--; get_card(m->s, current_card); m = m->next;
		cout << m->s << " "; m->n--; get_card(m->s, current_card);
		cout << endl;
		return;
	}
	while (t->next) t = t->next;
	cout << t->s << endl; get_card(t->s, current_card); t->n--; cout << endl;
}
bool zhata(card*holds)
{
	bool flag = 0;//判断有无王炸
	sort1(holds, length(holds));
	if ((holds->s == "JOKER") && holds->next) { if (holds->next->s == "joker") flag = 1; }
	sort2(holds);
	if (holds->n == 4)
	{
		clear(current_card);
		int o = 0;
		while (o < 4)
		{
			cout << holds->s << " "; holds->n--; get_card(holds->s, current_card);
			++o;
		}
		return 1;
	}
	else
	{
		if (flag == 1) 
		{
			clear(current_card);
			sort1(holds, length(holds));
			cout << holds->s << " "; holds->n--; get_card(holds->s, current_card); holds = holds->next;
			cout << holds->s << " "; holds->n--; get_card(holds->s, current_card); return 1; }
		else return 0;
	}
}
bool play(card*holds, card*input)
{
	int f = judge(input);
	switch (f)
	{
	case 1:
		if (case1_3(holds, input, 1)) return 1;
		else if (zhata(holds)) return 1;
		else {
			cout << "pass" ; return 0;
		}
		break;
	case 2:
		if (case1_3(holds, input, 2)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	case 3:
		if (case1_3(holds, input, 3)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	case 4:case4(holds, input); break;
	case 5:
		if (case5_6(holds, input, 1)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	case 6:
		if (case5_6(holds, input, 2)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	case 7:cout << "pass" ; return 0; break;
	case 10:
		if (case10_12(holds, input, 2)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
		if (case10_12(holds, input, 1)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	case 12:
		if (case10_12(holds, input, 3)) return 1;
		else if (zhata(holds)) return 1;
		else { cout << "pass" ; return 0; }
		break;
	}
}
int main(int argc, char* argv[]) {
	unsigned int random_seed;
	cin >> random_seed;
	srand(random_seed);
	vector<string> deck = get_new_deck();
	random_shuffle(deck.begin(), deck.end(), my_random);
	//for (int i = 0; i < deck.size(); ++i) {
		//cout << deck[i] << ((i == 19 || i == 36 || i == 53) ? "\n" : " ");
	//}
	card*player1 = 0; card*player2 = 0; card*player3 = 0;
	for(int i=0;i<54;++i)
	{
		if (i < 20) get_card(deck[i],player1);
		if (i < 37 && i>19) get_card(deck[i], player2);
		if (i > 36) get_card(deck[i], player3);
	}
	bool f = 1, s = 0, t = 0;
	cout << "player1 holds "; show(player1); cout << "player1 plays "; chupai(player1);cout << endl;
	cout << "player2 holds ";
	show(player2); 
	cout << "player2 plays ";
	s = play(player2, current_card);
	cout << endl;
	sort2(player1); sort2(player2);
	while (player1 && player2 && player3)
	{
		cout << "player3 holds "; show(player3); cout << "player3 plays ";
		if (!f && !s) { chupai(player3); t = 1; }
		else { t = play(player3, current_card); cout << endl; } sort2(player3); cut(1, player3);
		if (!player3) { cout << "game over! player3 wins! " << endl; break; }
		cout << "player1 holds "; show(player1); cout << "player1 plays ";
		if (!s && !t) {chupai(player1); f = 1;}
		else { f = play(player1, current_card); cout << endl; }	sort2(player1); cut(1, player1);
		if (!player1) { cout << "game over! player1 wins! " << endl; break; }
		cout << "player2 holds "; show(player2); cout << "player2 plays ";
		if (!f && !t) { chupai(player2); s = 1; }
		else { s = play(player2, current_card); cout << endl; } sort2(player2); cut(1, player2);
		if (!player2) { cout << "game over! player2 wins! " << endl; break; }

	}
	system("pause");
	return 0;
}