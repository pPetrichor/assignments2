#include<iostream>
#include<string>
using namespace std;
struct card
{
	int n;
	string s;
	card *next;
};
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
void get_card(int n,card* &holds)//整牌
{
	int i = 0;
	card *p = holds;
	while (i < n)
	{
		string s;
		cin >> s;
		p = holds;
		while (p)
		{
			if (s == p->s) { p->n++; break; }
			else  p = p->next;
		}
		if(!p)
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
		++i;
	}
}

int judge(const card*a)
{
	int m[20] = { 0 };
	int i = 0;
	while(a)
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
	if (m[3] == 0 && ((m[0] == 1 && m[1] == 1 && m[2] == 4) || (m[0] == 1 && m[1] == 4 && m[2] == 1) || (m[0] == 4 && m[1] == 1 && m[2] == 1))) return 8;//四带两张牌
	if (m[3] == 0 && ((m[0] == 2 && m[1] == 2 && m[2] == 4) || (m[0] == 2 && m[1] == 4 && m[2] == 2) || (m[0] == 4 && m[1] == 2 && m[2] == 2))) return 9;//四带两对
	bool flag1 = 1; bool flag2 = 1; bool flag3 = 1; int k = 0;
	int n1 = 0, n2 = 0, n3 = 0;
	while (m[k]) 
	{ 
		if (m[k] != 2) flag2 = 0; 
		if (m[k] != 1) flag1 = 0;
		if (m[k] != 3) flag3 = 0;
		if (m[k] == 2) ++n2;
		if (m[k] == 1) ++n1;
		if (m[k] == 3) ++n3;
		++k;
	}
	if (flag2) return 10;//连对
	if (flag1) return 11;//顺子
	if (flag3) return 12;//飞机不带翼
	if (n1 == n3) return 13;//飞机带小翼
	if (n2 == n3) return 14;//飞机带大翼
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
int length(card*h)
{
	int n = 0;//n记录结点个数
	card*m = h;
	while (m) { m = m->next; ++n; }
	return n;
}
void sort_cout(string *s, int x)//从大到小排序并输出
{
	for (int i = 0; i < x - 1; ++i)
	{
		for (int j = 0; j < x - i - 1; ++j)
		{
			if (s_to_n(s[j]) < s_to_n(s[j+1]))
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
void sort1(card*h,int x)//从大到小排序
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
int num_over_x(int x,card*h)
{
	int n = 0;
	sort2(h);
	while (h->n > x) { ++n; h = h->next; }
	return n;
}
card*cut(int n,card*&h)//截断链表，返回截断点处地址
{
	if (h->n < n) {
		h = 0; return 0;
	}
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
}
bool case1_3(card*&holds, card*&input,int x)//单牌、对子、三带零出牌
{
	sort1(holds, length(holds));
	sort2(holds);
	card*p = holds;
	while (p) { if (p->n != x)  p = p->next; else break; }
	if (p)//有单牌、对子、三带零
	{
		cut(x, holds);
		if (!p->next && (s_to_n(p->s) > s_to_n(input->s)))
		{
			for (int i = 0; i < x; ++i) cout << p->s << " ";
			cout << endl;
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
				for (int i = 0; i < x; ++i) cout << p->s << " ";
				cout << endl;
				return 1;
			}
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				for (int i = 0; i < x; ++i) cout << p->s << " ";
				cout << endl;
				return 1;
			}
		}
		sort1(holds, num_over_x(x, holds)); p = holds;
		while (p->next->n > x)
		{
			if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
			else break;
		}
		if (p->next->n > x) 
		{
			for (int i = 0; i < x; ++i) cout << p->s << " ";
			cout << endl;
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			for (int i = 0; i < x; ++i) cout << p->s << " ";
			cout << endl;
			return 1;
		}
	}
	sort1(holds, length(holds)); sort2(holds); p = holds;
	cut(x, holds);
	if (p->n <= x) return 0;
	while (p->next)
	{
		if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
		else break;
	}
	if (p->next)
	{
		for (int i = 0; i < x; ++i) cout << p->s << " ";
		cout << endl;
		return 1;
	}
	else if (s_to_n(p->s) > s_to_n(input->s))
	{
		for (int i = 0; i < x; ++i) cout << p->s << " ";
		cout << endl;
		return 1;
	}
	return 0;//在不出炸弹和王炸前提下出牌成功返回1，否则0
}
bool case4(card*&holds, card*&input)//炸弹出牌
{
	bool flag = 0;
	sort1(holds, length(holds));
	if (holds->s == "JOKER"&&holds->next) { if (holds->next->s == "joker") flag = 1; }
	sort2(holds);
	cut(4, holds);
	if (!holds&&flag == 1) { cout << "JOKER" << " " << "joker" << endl; return 1; }
	else if (!holds&&flag != 1) { cout << "YAO BU QI" << endl; return 0; }
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
			for (int i = 0; i < p->n; ++i) cout << p->s << " ";
			cout << endl;
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			for (int i = 0; i < p->n; ++i) cout << p->s << " ";
			cout << endl;
			return 1;
		}
		else if(flag==1) { cout << "JOKER" << " " << "joker" << endl; return 1; }
		else { cout << "YAO BU QI" << endl; return 0; }
	}
}
bool case5_6(card*holds, card*input, int x)//三带一及三带二
{
	string flag3 = "null"; string flagx = "null";
	sort1(holds, length(holds));
	sort2(holds);
	card*m = cut(3, holds);
	card*p = holds;
	if (!holds) return 0;
	while (p) { if (p->n != 3)  p = p->next; else break; }
	if(p)//有三
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
			if (p->n == 3) return 0;
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
	if (flag3 == "null") return 0;
	p = holds; while (p->next) p = p->next; p->next = m;//补好
	sort1(holds, length(holds)); sort2(holds); cut(1, holds);
	p = holds;
	cut(x, holds);
	if (p)
	{
		if(!p->next) flagx = p->s;
		else
		{
			while (p->next) p = p->next;
			flagx = p->s;
		}
	}
	if(flag3!="null"&&flagx!="null")
	{
		if(s_to_n(flag3)>s_to_n(flagx))
		{
			cout << flag3 << " " << flag3 << " " << flag3 << " ";
			for (int i = 0; i < x; ++i) cout << flagx << " ";
			cout << endl;
			return 1;
		}
		else 
		{
			for (int i = 0; i < x; ++i) cout << flagx << " ";
			cout << flag3 << " " << flag3 << " " << flag3 << " ";
			cout << endl;
			return 1;
		}
	}
	return 0;//在不出炸弹和王炸前提下出牌成功返回1，否则0
}
bool case8_9(card*holds, card*input, int x)
{
	string flag4 = "null"; string flagx1 = "null"; string flagx2 = "null";
	sort1(holds, length(holds));
	sort2(holds);
	card*m = cut(4, holds);
	card*p = holds;
	if (!holds) return 0;
	while (p) { if (p->n != 4)  p = p->next; else break; }
	if (p)//有四
	{
		if (!p->next && (s_to_n(p->s) > s_to_n(input->s)))
		{
			flag4 = p->s; p->n -= 4;
		}
		else if (p->next)
		{
			while (p->next)
			{
				if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
				else break;
			}
			if (p->next) { flag4 = p->s; p->n -= 4; }
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				flag4 = p->s; p->n -= 4;
			}
		}
	}
	if (flag4 == "null") return 0;
	p = holds; while (p->next) p = p->next; p->next = m;
	sort2(holds); cut(1, holds); sort1(holds, length(holds));
	p = holds;
	cut(x, holds);
	if (p)
	{
		if (!p->next) { flagx1 = p->s; p->n -= x; }
		else
		{
			while (p->next) p = p->next;
			flagx1 = p->s; p->n -= x;
		}
		sort2(holds); cut(1, holds); sort1(holds, length(holds));
		p = holds;
		cut(x, holds);
		if (p)
		{
			if (!p->next) { flagx2 = p->s; p->n -= x; }
			else
			{
				while (p->next) p = p->next;
				flagx2 = p->s; p->n -= x;
			}
		}
	}
	if (flag4 != "null"&&flagx1 != "null"&&flagx2 != "null")
	{
		if (x == 1)
		{
			string s[] = { flag4,flag4,flag4,flag4,flagx1,flagx2};
			sort_cout(s, 6);
			return 1;
		}
		else
		{
			string s[] = { flag4,flag4,flag4,flag4,flagx1,flagx1,flagx2,flagx2};
			sort_cout(s, 8);
			return 1;
		}
		return 0;//在不出炸弹和王炸前提下出牌成功返回1，否则0
	}
}
string str3 = "null"; int number = 0;
bool panduan(card*holds, card*input, int x, int l, string*d)
{
	sort2(holds);
	card*j=cut(x, holds);
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
			while (h != e)
			{
				for (int i = 0; i < x; ++i) cout << h->s << " ";
				h = h->next;
			}
			for (int i = 0; i < x; ++i) cout << e->s << " ";
			cout << endl;
			h = holds;
			{ if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 1; } }
		}
		else if (l == 2)
		{
			str3 = h->s;
			for (; h != e; h = h->next) { h->n -= 3; d[number] = h->s; d[number + 1] = h->s; d[number + 2] = h->s; number += 3; }
			e->n -= 3; d[number] = e->s; d[number + 1] = e->s; d[number + 2] = e->s; number += 3;
		}
		h = holds; { if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 1; } }
	}
	else{ h = holds; if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; }return 0; }
}
bool case10_12( card*holds,card*input,int x)//连对、顺子和飞机不带翼
{
	sort2(holds);
	card*t = holds;
	if (t->n < x) return 0;
	while (t)
	{
		if (t->n > x) t = t->next;
		else break;
	}
	if (panduan(t, input, x, 1, 0)) return 1;
	else if (panduan(holds, input, x, 1, 0)) return 1;
	else return 0;
}//在不出炸弹和王炸前提下出牌成功返回1，否则0
bool case13_14(card*holds, card*input, int x)//飞机带小/大翼
{
	sort2(holds); sort2(input);
	card*k = input;
	int num = 1; card*g = k; while (k->n == 3 && k->next)
	{ ++num; k = k->next;if(k->next->n!=3) k->next = 0; }
	string *d = new string[(3 + x)*num+1];
	card*t = holds;
	while (t->n != 3) t = t->next;
	if (panduan(t, g, 3, 2, d));
	else if (panduan(holds, g, 3, 2, d));
	if (str3=="null") return 0;
	sort2(holds); 
	cut(x, holds);
	sort1(holds, length(holds));
	sort2(holds);
	card*u = holds;
	int v = 0;
	for(;v<num;++v)
	{
		if (!holds) break;
		while (holds->next) holds = holds->next;
		for (int i = 0; i < x; ++i) { d[number] = holds->s; number++; holds->n--; }
		holds = u;
		cut(1, holds);
	}
	if (v == num) sort_cout(d, (3 + x)*num);
	else return 0;
	
}//在不出炸弹和王炸前提下出牌成功返回1，否则0
bool zhata(card*holds)
{
	bool flag = 0;//判断有无王炸
	sort1(holds, length(holds));
	if ((holds->s == "JOKER") && holds->next) { if (holds->next->s == "joker") flag = 1; }
	sort2(holds);
	cut(4, holds);
	card*p = holds;
	if(p)
	{
		while (p->next) p = p->next;
		cout << p->s << " " << p->s << " " << p->s << " " << p->s << endl;
		return 1;
	}
	else
	{
		if (flag == 1) { cout << "JOKER joker" << endl; return 1; }
		else return 0;
	}
}
void play(card*holds,card*input)
{
	card*y = copy__(holds);
	int f = judge(input);
	switch(f)
	{
	case 1: 
		if (case1_3(holds, input, 1)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 2:
		if (case1_3(holds, input, 2)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 3: 
		if (case1_3(holds, input, 3)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 4:case4(holds, input); break;
	case 5: 
		if (case5_6(holds, input, 1)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 6: 
		if (case5_6(holds, input, 2)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 7:cout << "YAO BU QI" << endl; break;
	case 8:
		if (case8_9(holds, input, 1)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 9: 
		if (case8_9(holds, input, 2)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 10:  
		if (case10_12(holds, input, 2)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 11:
		if (case10_12(holds, input, 1)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 12:
		if (case10_12(holds, input, 3)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 13:
		if (case13_14(holds, input, 1)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	case 14:
		if (case13_14(holds, input, 2)) return;
		else if (zhata(y)) return;
		else cout << "YAO BU QI" << endl;
		break;
	}
}
int main()
{
	int x, y;
	cin >> x >> y;
	if (x == 0) cout << "YAO BU QI" << endl;
	else
	{
		card *a = 0, *b = 0;
		get_card(x, a); get_card(y, b);
		play(a, b);
	}
	system("pause");
	return 0;
}