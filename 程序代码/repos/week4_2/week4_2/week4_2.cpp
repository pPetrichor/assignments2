#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <functional>

using namespace std;


class Card : public string {
public:
	static const int N_CARD_VALUES;
	static const int N_CARD_SUITS;
	static const string CARD_VALUES[];
	static const string CARD_SUITS[];

	Card(const char* str) :string(str) {};
	Card() :string() {};
	Card(string str) :string(str) {};

	static vector<Card> get_new_deck();

	// ���ز�������ʹ��������ԱȽϴ�С
	bool operator <(const Card &other) const;
	bool operator >(const Card &other) const;
};
struct card
{
	int n;
	string s;
	card*next;
};

class DDZPlayer {
protected:
	string name;  // �����
	int position;  // ���λ�ñ�ţ�0Ϊ������1Ϊ�����¼ң�2Ϊ�����ϼ�
	vector<Card> hand;  // ����

	int prePos;  //��һ�����Ƶ���λ�ñ�ţ�-1��ʾ��û���˳�����
	vector<Card> prePlay;  // ��һ�����Ƶ��˳���ʲô�ƣ�

	bool legal(vector<Card> cards);  // �жϵ�ǰ���cards�Ƿ�Ϸ�
	void substractFromHand(vector<Card> cards);  // �ӵ�ǰ������ɾȥcards�е���
public:
	DDZPlayer(string name);  // ���캯������ʼ�������
	string getName();
	int getNumber();
	virtual void draw(Card card);  // ��cards�е��Ƽ�������
	virtual void draw(vector<Card> cards);  // ��cards�е��Ƽ�������
	virtual void setPosition(int pos);  // ��ʼ���ã���������������
	virtual void showHand();  // ��ӡ����
	virtual void observed(int pos, vector<Card> cards);  // �۲⵽��ҳ���
	virtual vector<Card> play();  // �ֵ��Լ�ʱ������ʲô��
	bool leftNoCard();  // �����Ƿ�������ƣ�
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
		if (m[1] == 0 && m[0] == 1) return 1;//����
		if (m[1] == 0 && m[0] == 2) return 2;//����
		if (m[1] == 0 && m[0] == 3) return 3;//������
		if (m[1] == 0 && m[0] == 4) return 4;//ը��
		if (m[2] == 0 && ((m[0] == 1 && m[1] == 3) || (m[0] == 3 && m[1] == 1))) return 5;//����һ
		if (m[2] == 0 && ((m[0] == 2 && m[1] == 3) || (m[0] == 3 && m[1] == 2))) return 6;//������
		if (m[2] == 0 && (m[0] == 1 && m[1] == 1)) return 7;//��ը
		if (m[2] == 0 && ((m[0] == 4 && m[1] == 2) || (m[0] == 2 && m[1] == 4))) return 8;
		bool flag1 = 1; bool flag2 = 1; bool flag3 = 1; int k = 0;
		while (m[k])
		{
			if (m[k] != 2) flag2 = 0;
			if (m[k] != 1) flag1 = 0;
			if (m[k] != 3) flag3 = 0;
			++k;
		}
		if (flag2) return 10;//����
		if (flag1) return 11;//˳��
		if (flag3) return 12;//�ɻ�������
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
	void sort1(card*h, int x)//�Ӵ�С����
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
		int n = 0;//n��¼������
		card*m = h;
		while (m) { m = m->next; ++n; }
		return n;
	}
	void sort2(card*h)//��������
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
	void sort_cout(string *s, int x)//�Ӵ�С�������
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
	card*cut(int n, card*&h)//�ض��������ؽضϵ㴦��ַ
	{
		if (h->n < n) { card*r = h; h = 0; return r; }
		card*m = h;
		while (m->next) m = m->next;
		if (m->n == n) return 0;//����ض�
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
	card* hand_to_mycard(card*mycard)//ת��
	{
		int len = hand.size();
		card*p = mycard;
		for (int i = 0; i < len; ++i)
		{
			p = mycard;
			while (p)
			{
				if (hand[i] == p->s) { p->n++; break; }
				else  p = p->next;
			}
			if (!p)
			{
				card*q = new card;
				q->n = 1;
				q->s = hand[i];
				q->next = 0;
				p = mycard;
				if (!p) mycard = q;
				else
				{
					while (p->next) p = p->next;
					p->next = q;
				}
			}
		}
		return mycard;
	}
	card* prePlay_to_precard(card*mycard)//ת��
	{
		int len = prePlay.size();
		card*p;
		for (int i = 0; i < len; ++i)
		{
			p = mycard;
			while (p)
			{
				if (prePlay[i] == p->s) { p->n++; break; }
				else  p = p->next;
			}
			if (!p)
			{
				card*q = new card;
				q->n = 1;
				q->s = prePlay[i];
				q->next = 0;
				p = mycard;
				if (!p) mycard = q;
				else
				{
					while (p->next) p = p->next;
					p->next = q;
				}
			}
		}
		return mycard;
	}
	card* turn(vector<Card> d,card*mycard)//ת��
	{
		int len = d.size();
		card*p;
		for (int i = 0; i < len; ++i)
		{
			p = mycard;
			while (p)
			{
				if (d[i] == p->s) { p->n++; break; }
				else  p = p->next;
			}
			if (!p)
			{
				card*q = new card;
				q->n = 1;
				q->s = d[i];
				q->next = 0;
				p = mycard;
				if (!p) mycard = q;
				else
				{
					while (p->next) p = p->next;
					p->next = q;
				}
			}
		}
		return mycard;
	}
	card *copy__(card *a)//��������
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
	bool case1_3(card*&holds, card*&input, int x, vector<Card> &d)//���ơ����ӡ����������
	{
		sort1(holds, length(holds));
		sort2(holds);
		card*p = holds;
		while (p) { if (p->n != x)  p = p->next; else break; }
		if (p)//�е��ơ����ӡ�������
		{
			card*m = cut(x, holds);
			if (!p->next && (s_to_n(p->s) > s_to_n(input->s)))
			{
				for (int i = 0; i < x; ++i) { d.push_back(p->s); }
				p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
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
					for (int i = 0; i < x; ++i) { d.push_back(p->s); }
					p = holds;
					if (!p) p = m;
					else {
						while (p->next) p = p->next; p->next = m;
					}//����
					return 1;
				}
				else if (s_to_n(p->s) > s_to_n(input->s))
				{
					for (int i = 0; i < x; ++i) { d.push_back(p->s); }
					p = holds;
					if (!p) p = m;
					else {
						while (p->next) p = p->next; p->next = m;
					}//����
					return 1;
				}
			}
			sort1(holds, num_over_x(x, holds)); p = holds;
			if (!p->next)
			{
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
				return 0;
			}
			while (p->next->n > x)
			{
				if (!((s_to_n(p->s) > s_to_n(input->s)) && (s_to_n(p->next->s) <= s_to_n(input->s)))) p = p->next;
				else break;
			}
			if (p->next->n > x)
			{
				for (int i = 0; i < x; ++i) { d.push_back(p->s); }
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
				return 1;
			}
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				for (int i = 0; i < x; ++i) { d.push_back(p->s); }
				p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
				return 1;
			}
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//����
		}
		sort1(holds, length(holds)); sort2(holds); p = holds;
		card*m = cut(x, holds);
		if (p->n <= x)
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
			for (int i = 0; i < x; ++i) { d.push_back(p->s); }
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//����
			return 1;
		}
		else if (s_to_n(p->s) > s_to_n(input->s))
		{
			for (int i = 0; i < x; ++i) { d.push_back(p->s); }
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//����
			return 1;
		}
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//����
		return 0;//�ڲ���ը������ըǰ���³��Ƴɹ�����1������0
	}
	bool case4(card*&holds, card*&input, vector<Card> &d)//ը������
	{
		bool flag = 0;
		sort1(holds, length(holds));
		if (holds->s == "JOKER"&&holds->next) { if (holds->next->s == "joker") flag = 1; }
		sort2(holds);
		card*m = cut(4, holds);
		if (!holds&&flag == 1)
		{
			card*p = holds;
			if (!p) holds = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//����
			sort1(holds, length(holds));
			d[0] = holds->s; holds = holds->next;
			d[1] = holds->s;
			return 1;
		}
		else if (!holds&&flag != 1) return 0;
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
				int o = 0;
				while (o < 4)
				{
					d.push_back(p->s);
					++o;
				}
				p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
				return 1;
			}
			else if (s_to_n(p->s) > s_to_n(input->s))
			{
				int o = 0;
				while (o < 4)
				{
					d.push_back(p->s);
					++o;
				}
				p = holds;
				if (!p) p = m;
				else {
					while (p->next) p = p->next; p->next = m;
				}//����
				return 1;
			}
			else if (flag == 1)
			{
				if (!p) p = m;
				else
				{
					while (p->next) p = p->next; p->next = m;
				}//����
				sort1(m, length(m));
				d.push_back(m->s); m = m->next;
				d.push_back(m->s); return 1;
			}
			else return 0;
		}
	}
	bool case5_6(card*holds, card*input, int x, vector<Card> &d)//����һ��������
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
			}//����
			return 0;
		}
		while (p) { if (p->n != 3)  p = p->next; else break; }
		if (p)//����
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
				if (p->n == 3 && p->next) { while (p->next) p = p->next; p->next = m; return 0; }
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
			}//����
			return 0;
		}
		sort1(holds, length(holds)); sort2(holds);
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//����
		sort2(holds);
		p = holds;
		m = cut(x, holds);
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
			for (int i = 0; i < 3; ++i)  d.push_back(flag3);
			for (int i = 0; i < x; ++i) d.push_back(flagx);
			p = holds;
			if (!p) p = m;
			else {
				while (p->next) p = p->next; p->next = m;
			}//����
			return 1;
		}
		p = holds;
		if (!p) p = m;
		else {
			while (p->next) p = p->next; p->next = m;
		}//����
		return 0;//�ڲ���ը������ըǰ���³��Ƴɹ�����1������0
	}
	string str3 = "null"; int number = 0;
	bool panduan(card*holds, card*input, int x, int l, vector<Card> &d)
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
				while (h != e)
				{
					for (int i = 0; i < x; ++i) {
						d.push_back(h->s);
					}
					h = h->next;
				}
				for (int i = 0; i < x; ++i) { d.push_back(e->s); }
				h = holds;
				{ if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; return 1; } }
			}
		}
		else { h = holds; if (!h) holds = j; else { while (h->next) h = h->next; h->next = j; }return 0; }
	}
	bool case10_12(card*holds, card*input, int x, vector<Card> &d)//���ԡ�˳�Ӻͷɻ�������
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
		if (panduan(t, input, x, 1, d)) return 1;
		else if (panduan(holds, input, x, 1, d)) return 1;
		else return 0;
	}//�ڲ���ը������ըǰ���³��Ƴɹ�����1������0
	string s0;
	bool case_1(card*m, int t, int p)//t������,�ɻ����Ի�˳��
	{
		sort1(m, length(m)); sort2(m);
		card*h = copy__(m);
		if (h->n < t) return 0;
		while (h)
		{
			if (h->n > t) h = h->next;
			else break;
		}
		if (t == 1 && !h) return 0;
		cut(t, h);
		if (h)
		{
			bool y = 0;
			int num = 1; int count = 1;
			card*k = h;
			while (k->next) { ++num; k = k->next; }
			while (num >= p)
			{
				if (s_to_n(h->s) - s_to_n(h->next->s) == 1)
				{
					if (y == 0) s0 = h->s;
					count++; h = h->next; y = 1;
					if (count >= p) { return 1; }
				}
				else { h = h->next; count = 1; y = 0; }
				num--;
			}
		}
		return 0;
	}
	bool case_2(card*m, int t)//����1/2/0
	{
		sort1(m, length(m)); sort2(m);
		card*h = copy__(m);
		card*p = cut(3, h);
		if (!h) return 0;
		if (h->n >= 3)
		{
			while (h) { if ((h->n) > 3) h = h->next; else break; }
			if (h)
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
		if (m)
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
		if (m->s == "JOKER"&&m->next)
		{
			if (m->next->s == "joker") return 1;
		}
		return 0;
	}
	void chupai(card*m, vector<Card> &d)//˳�򣺷ɻ������ԡ�˳�ӡ����������ӡ�ը��������
	{
		sort1(m, length(m)); sort2(m);
		card*t = m;
		if (case_1(m, 3, 2))
		{
			while (t->s != s0) t = t->next;
			int o = 0;
			while (o < 3)
			{
				d.push_back(t->s);
				++o;
			}
			while (t->next)
			{
				if (t->next->n == 3)
				{
					if (s_to_n(t->s) - s_to_n(t->next->s) == 1)
					{
						o = 0; t = t->next;
						while (o < 3)
						{
							d.push_back(t->s);
							++o;
						}
					}
					else break;
				}
				else break;
			}
			return;
		}
		if (case_1(m, 2, 3))
		{
			while (t->s != s0) t = t->next;
			int o = 0;
			while (o < 2)
			{
				d.push_back(t->s);
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
							d.push_back(t->s);
							++o;
						}
					}
					else break;
				}
				else break;
			}
			return;
		}
		if (case_1(m, 1, 5))
		{
			while (t->s != s0) t = t->next;
			d.push_back(t->s);
			while (t->next)
			{
				if (s_to_n(t->s) - s_to_n(t->next->s) == 1)
				{
					d.push_back(t->s);
				}
				else break;
			}
			return;
		}
		if (case_2(m, 2))
		{
			while (t->n > 3) t = t->next; int o = 0;
			while (o < 3)
			{
				d.push_back(t->s);
				++o;
			}
			while (t->n != 2) t = t->next; o = 0;
			while (o < 2)
			{
				d.push_back(t->s);
				++o;
			}
			return;
		}
		if (case_2(m, 1))
		{
			while (t->n > 3) t = t->next; int o = 0;
			while (o < 3)
			{
				d.push_back(t->s);
				++o;
			}
			while (t->n != 1) t = t->next;
			d.push_back(t->s);
			return;
		}
		if (case_2(m, 0))
		{
			while (t->n > 3) t = t->next;
			int o = 0;
			while (o < 3)
			{
				d.push_back(t->s); ++o;
			}
			return;
		}
		if (case_3(m))
		{
			while (t->n > 2) t = t->next;
			int o = 0;
			while (o < 2)
			{
				d.push_back(t->s);
				++o;
			}
			return;
		}
		if (case_4(m))
		{
			int o = 0;
			while (o < 4)
			{
				d.push_back(t->s);
				++o;
			}
			return;
		}
		if (case_5(m))
		{
			sort1(m, length(m));
			d.push_back(m->s); m = m->next;
			d.push_back(m->s);
			return;
		}
		while (t->next) t = t->next;
		d.push_back(t->s);
	}
	bool zhata(card*holds, vector<Card> d)
	{
		bool flag = 0;//�ж�������ը
		sort1(holds, length(holds));
		if ((holds->s == "JOKER") && holds->next) { if (holds->next->s == "joker") flag = 1; }
		sort2(holds);
		if (holds->n == 4)
		{
			int o = 0;
			while (o < 4)
			{
				d.push_back(holds->s);
				++o;
			}
			return 1;
		}
		else
		{
			if (flag == 1)
			{
				sort1(holds, length(holds));
				d.push_back(holds->s); holds = holds->next;
				d.push_back(holds->s); return 1;
			}
			else return 0;
		}
	}
	bool play(card*holds, card*input, vector<Card> &d)
	{
		int f = judge(input);
		switch (f)
		{
		case 1:
			if (case1_3(holds, input, 1, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
		case 2:
			if (case1_3(holds, input, 2, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else return 0;
			break;
		case 3:
			if (case1_3(holds, input, 3, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
		case 4:case4(holds, input, d); break;
		case 5:
			if (case5_6(holds, input, 1, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else return 0;
			break;
		case 6:
			if (case5_6(holds, input, 2, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
		case 7: return 0; break;
		case 10:
			if (case10_12(holds, input, 2, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
			if (case10_12(holds, input, 1, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
		case 12:
			if (case10_12(holds, input, 3, d)) return 1;
			else if (zhata(holds, d)) return 1;
			else  return 0;
			break;
		}
	}
};


class DDZGame {
private:
	static int my_random(int i);  // ϴ��ʱ�õ����������
	vector<DDZPlayer*> players;  // ����������ҵ�ָ��
	void showCards(vector<Card> cards);  // ���һ����

public:
	DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // ���캯��
	void run();  // ִ����Ϸ����
};


class DDZHumanPlayer : public DDZPlayer {
public:
	DDZHumanPlayer(string name) : DDZPlayer(name) {};
	vector<Card> play();

};

int main() {
	string name;
	cout << "Please input your name:" << endl;
	getline(cin, name);

	srand(0x0217B);

	DDZPlayer p1("Alice"), p2("Bob");
	DDZHumanPlayer p3(name);
	DDZGame g(&p1, &p2, &p3);
	g.run();
	system("pause");
	return 0;
}


bool Card::operator <(const Card &other) const {
	int a = -1, b = -1;
	for (int i = 0; i < N_CARD_VALUES; ++i) {
		if (*this == CARD_VALUES[i]) a = i;
		if (other == CARD_VALUES[i]) b = i;
	}
	return a < b;
}

bool Card::operator >(const Card &other) const {
	return other < *this;
}

DDZPlayer::DDZPlayer(string name) : name(name) {
	// �����Ĺ��캯��
	prePos = -1;
}

string DDZPlayer::getName() {
	return name;
}
int DDZPlayer::getNumber()
{
	return hand.size();
}
bool DDZPlayer::legal(vector<Card> cards) {
	// ͨ���ϼҴ������prePlay������hand�ж�cards��Ϊ������Ƿ�Ϸ�
	// TODO�����ڶ��⣩�벹ȫ�������
	card *hands_ = 0; card*t = hand_to_mycard(hands_); hands_ = t;
	sort(cards.begin(), cards.end(), greater<Card>());
	card*play = 0;play = turn(cards, play);
	int n = cards.size(); bool flag = 0; int m = prePlay.size();
	card*precard = 0;precard = prePlay_to_precard(precard);
	sort1(t, length(t)); sort2(t);
	sort1(precard, length(precard)); sort2(precard);
	sort1(play, length(play)); sort2(play);
	if (n == 0) return 1; int K = 0;
	for(int i=0;i<n;++i)
	{
		t = hands_;
		while (t)
		{
			if (t->s == cards[i])
			{
				if (t->n > 0) { flag = 1; t->n--; break; }
				else return 0;
			}
			else t = t->next;
		}
		if (flag == 1) ++K; flag = 0;
	}
	if (K != n) return 0;//������Ƿ����
	if(m==0||prePos==position || prePos == -1)//�Լ�����
	{
		int j = cards.size();
		int f = judge(play);
		switch (f)
		{
		case 1: return 1; break;
		case 2: return 1; break;
		case 3: return 1; break;
		case 4: return 1; break;
		case 5: return 1; break;
		case 6: return 1; break;
		case 7: {if (play->s == "JOKER"&&play->next->s == "joker") return 1; else return 0; break; }
		case 10:
		{
			int c = j / 2;//�������Ը���
			card*u;
			for (int i = 0; i < c; ++i)
			{
				u = play;
				if (u->n != 2) return 0;
				u = u->next;
			}
			u = play; while (u->next) u = u->next;
			if (s_to_n(play->s) - s_to_n(u->s) != c - 1) return 0; else return 1; break;
		}
		case 11:
		{
			card*u;
			for (int i = 0; i < j; ++i)
			{
				u = play;
				if (u->n != 1) return 0;
				u = u->next;
			}
			u = play; while (u->next) u = u->next;
			if (s_to_n(play->s) - s_to_n(u->s) != j - 1) return 0; else return 1; break;
		}
		case 12:
		{int c = j / 3;//����ɻ�����
		card*u;
		for (int i = 0; i < c; ++i)
		{
			u = play;
			if (u->n != 2) return 0;
			u = u->next;
		}
		u = play; while (u->next) u = u->next;
		if (s_to_n(play->s) - s_to_n(u->s) != c - 1) return 0; else return 1; break;
		}
		}
	}
	
	if(n!=m)
	{
		if (n == 2 && cards[0] == "joker"&&cards[1] == "JOKER") return 1;
		if (n == 4 && cards[0] == cards[1] && cards[1] == cards[2] && cards[0] == cards[3]) return 1;
		else return 0;
	}
	int f = judge(precard);
		switch (f)
		{
		case 1:if (!(n == 1 && s_to_n(cards[0]) > s_to_n(prePlay[0]))) return 0;
			   else return 1; break;
		case 2:if (!(n == 2 && s_to_n(cards[0]) > s_to_n(prePlay[0])&&cards[0]==cards[1])) return 0;
			   else return 1; break;
		case 3:if (!(n == 3 && s_to_n(cards[0]) > s_to_n(prePlay[0]) && cards[0] == cards[1]&&cards[1]==cards[2])) return 0;
			   else return 1; break;
		case 4:if (!((n == 4 && s_to_n(cards[0]) > s_to_n(prePlay[0]) && cards[0] == cards[1] && cards[1] == cards[2] && cards[0] == cards[3]))) return 0;
			   else return 1; break;
		case 5:if (!(n == 4 && play->n == 3 && s_to_n(play->s) > s_to_n(precard->s))) return 0;
			   else return 1; break;
		case 6:if (!(n == 5 && play->n == 3 && s_to_n(play->s) > s_to_n(precard->s))) return 0;
			   else return 1; break;
		case 7:if (n) return 0; else return 1; break;
		case 10:
		{
			int c = m / 2;//�������Ը���
			if (s_to_n(play->s) <= s_to_n(precard->s)) return 0; card*u;
			for (int i = 0; i < c; ++i)
			{
				u = play;
				if (u->n != 2) return 0;
				u = u->next;
			}
			u = play; while (u->next) u = u->next;
			if (s_to_n(play->s) - s_to_n(u->s) != c - 1) return 0; else return 1; break;
		}
		case 11:
		{
			if (s_to_n(play->s) <= s_to_n(precard->s)) return 0; card*u;
			for (int i = 0; i < m; ++i)
			{
				u = play;
				if (u->n != 1) return 0;
				u = u->next;
			}
			u = play; while (u->next) u = u->next;
			if (s_to_n(play->s) - s_to_n(u->s) != m - 1) return 0; else return 1; break;
		}
		case 12:
		{int c = m / 3;//����ɻ�����
		if (s_to_n(play->s) <= s_to_n(precard->s)) return 0; card*u;
		for (int i = 0; i < c; ++i)
		{
			u = play;
			if (u->n != 2) return 0;
			u = u->next;
		}
		u = play; while (u->next) u = u->next;
		if (s_to_n(play->s) - s_to_n(u->s) != c - 1) return 0; else return 1; break;
		}
		}
	return true;
}

void DDZPlayer::substractFromHand(vector<Card> cards) {
	// ���������hand��ɾ��cards������cards�е���hand�����õó���������������
	sort(hand.begin(), hand.end(), greater<Card>());
	sort(cards.begin(), cards.end(), greater<Card>());
	vector<Card>::iterator i = hand.begin(), k = cards.begin();
	for (vector<Card>::iterator j = hand.begin(); j != hand.end(); ++j) {
		if (k == cards.end() || *k != *j) *(i++) = *j;
		else if (k != cards.end()) ++k;
	}
	hand.erase(i, hand.end());
}

void DDZPlayer::showHand() {
	// �������������ơ�
	cout << name << " holds: ";
	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

void DDZPlayer::draw(Card card) {
	// ��card��������
	hand.push_back(card);
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
	// ��cards�е��Ƽ�������
	hand.insert(hand.end(), cards.begin(), cards.end());
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
	position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
	// ����һ�����Ƶ��˺ͳ���ʲô�Ƽ�¼������
	// ��������¼�������Ϣ����Ĳ���ʹ�ã����ԸĶ����������
	// ���磬��¼�Ѿ�����Щ�Ʊ�������������������Ʋⳡ���Ƿ���ܻ�����ը����
	if (cards.size() == 0) return;
	prePos = pos;
	prePlay = cards;
}

vector<Card> DDZPlayer::play() {
	// �ֵ�����ƣ����ش�����ơ�
	// TODO������һ�⣩�������������
	// �����ʹ�ò�ͬ�����ݽṹ���д���������ֽ�hand����ת��Ϊ��ʹ�õĽṹ��
	// ��������ٽ��������ת��Ϊvector<Card>������card������
	vector<Card> cards; card *hands = 0; card*precard = 0;
	hands = hand_to_mycard(hands); precard = prePlay_to_precard(precard);
	if (prePos == position || prePos == -1) {
		// ��������
		chupai(hands, cards);
	}
	else {
		// λ��prePos����Ҵ����prePlay���ƣ�����Ҫ��ʲô�ƣ�
		play(hands, precard, cards);
	}
	// ����Ҫ��֤��������ǺϷ���
	// assert�����ڲ���Ϊfalse��ʱ���ʹ���򱨴��˳���
	// �������ĺô��ǣ��������ûע�⵽�Ĵ����³����ڴ˱����˳���
	// ���֪�����ڳ��ƵĺϷ����ϳ������⣬�������Ų������������֡�
	// assert(legal(cards));

	// ��������ƴ�������ɾȥ
	substractFromHand(cards);
	return cards;
}

bool DDZPlayer::leftNoCard() {
	// ���ص�ǰ����Ϊ��
	return hand.empty();
}

const int Card::N_CARD_VALUES = 15;

const int Card::N_CARD_SUITS = 4;

const string Card::CARD_VALUES[] = {
	"3", "4", "5", "6",
	"7", "8", "9", "10",
	"J", "Q", "K", "A", "2",
	"joker", "JOKER"
};

const string Card::CARD_SUITS[] = {
	"Spades", "Hearts", "Diamonds", "Clubs"
};

vector<Card> Card::get_new_deck() {
	// ����һ������
	vector<Card> deck;
	for (int i = 0; i < N_CARD_VALUES - 2; ++i) {
		for (int j = 0; j < N_CARD_SUITS; ++j) {
			Card card(CARD_VALUES[i]);
			deck.push_back(card);
		}
	}
	deck.push_back(Card(CARD_VALUES[13]));
	deck.push_back(Card(CARD_VALUES[14]));
	return deck;
}

int DDZGame::my_random(int i) {
	return std::rand() % i;
}

DDZGame::DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3) {
	// �ƾ���Ĺ��캯������Ҫ�������������Ϊ����
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);
}

void DDZGame::showCards(vector<Card> cards) {
	sort(cards.begin(), cards.end(), greater<Card>());
	for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i) {
		cout << *i << " ";
	}
	if (cards.size() == 0) cout << "YAO BU QI";
	cout << endl << endl;
}

void DDZGame::run() {
	// ��������Ϸ����Ҫ����

	// ȡһ�����Ʋ�ϴ��
	vector<Card> deck = Card::get_new_deck();
	random_shuffle(deck.begin(), deck.end(), my_random);

	// ÿ����ҳ�17���ƣ��������ŵ���
	for (int i = 0; i < 54 - 3; ++i)
		players[i % 3]->draw(deck[i]);

	// ���ѡȡ�����������������������
	// * �����ʵ���Լ��Ľе������̣�
	// * ����Ҫ��DDZPlayer�����������Ӧ�ı������洢������ҽе����������
	// * �ͺ���bool DDZPlayer::bid()�������Լ��Ƿ�Ҫ�е�������
	// * �����play()�����ͽе����Ĺ������������̡�
	int landlordPos = my_random(3);
	for (int i = 54 - 3; i < 54; ++i)
		players[landlordPos]->draw(deck[i]);
	for (int i = 0; i < 3; ++i)
		players[i]->setPosition((i + 3 - landlordPos) % 3); // ��������������λ��
	cout << players[landlordPos]->getName() << " is the landlord." << endl;


	int currentPlayer = landlordPos;
	while (true) {
		// ��ǰ��Ҵ���
		vector<Card> currentCards = players[currentPlayer]->play();
		cout << players[currentPlayer]->getName() << " plays:";
		showCards(currentCards);
		cout << "ʣ��������" << players[currentPlayer]->getNumber() << endl;
		// ������ҿ����˴�����ơ���������ֻ���¼ҿ������ϼ�Ҳ�ܿ�����
		for (int i = 0; i < 3; ++i) {
			// ��ҿ�����λ�ñ�Ŷ��Ǵӵ���Ϊ0��ʼ��
			int relativePos = (currentPlayer + 3 - landlordPos) % 3;
			players[i]->observed(relativePos, currentCards);
		}

		// ����ճ����Ƶ����û��������Ϸ����
		if (players[currentPlayer]->leftNoCard()) {
			bool landlordwins = (currentPlayer == landlordPos);
			cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
			break;
		}

		// ������һ����ҵ��±�
		currentPlayer = (currentPlayer + 1) % 3;
	}
}

vector<Card> DDZHumanPlayer::play() {
	vector<Card> cards;
	string s, c;
	while (true) {
		showHand();
		cout << "Please input the cards you want to play." << endl;
		getline(cin, s);
		istringstream iss(s);
		while (iss >> c) {
			cards.push_back(Card(c));
		}
		// ����cards��һ��vector<Card>���洢���û��������
		// ����Ҫ�����������ǳ��е��ƣ����ҺϷ��������legal������
		if (legal(cards)) {
			break;
		}
		else {
			cout << "Illegal cards. Input again." << endl;
			cards.clear();
		}
	}
	substractFromHand(cards);
	return cards;
}