#ifndef _PROLOG__H
#define _PROLOG__H
#include<iostream>
#include<list>
#include<string>
#include<fstream>
using namespace std;
struct token
{
	string content;//����
	string variety;//����
	int number;//����
};
struct fact
{
	string atom;//fact��ν��
	list <token> arguments;//��¼����������Ԫ�����ݼ�����
};
struct rule
{
	string atom;//rule��ν��
	list <token> arguments;//��¼rule����������Ԫ�����ݼ�����
	list <fact> facts;//��¼�ù����漰��������fact
};

class word_analyse
{
private:
	string location;//��ǰλ��
	char next;//��¼��һ������
	token current;//��¼�µ�ǰ������token,֮����ӵ�token_list��
	bool flag;
public:
	list<token> token_list;
	word_analyse() { location = "start"; current.number = 0; flag = 0; }//��������
	void analyse(char ch);//��״̬�����ı�token,���ݵ�ǰ��location��next���б��������next��¼�޷���״̬����һ·��ƥ�䣬���зǷ��ַ���ע��
	void run(string filename);//���̿��ƺ��������ļ�
	void clean()//ÿ������һ��֮���������ʼ״̬
	{
		location = "start"; current.number = 0; flag = 0;
		token_list.clear();
	}
};
class rules_analyse
{
private:
	string location;//��ǰλ��
	fact a;
	rule b;//a���ڴ洢rule�е�fact,b���ڽ�һ��rule�����б����洢����
	word_analyse words;
	bool Flag;
public:
	void clean()
	{
		location = "Start";
		a.atom.clear(); a.arguments.clear();
		b.atom.clear(); b.arguments.clear(); b.facts.clear();
		Flag = 0;
		words.clean();
		all_facts.clear();
		all_rules.clear();
	}
	list<fact> all_facts;//fact��¼��
	list<rule> all_rules;//rule��¼��
	rules_analyse() { location = "Start"; Flag = 0; }
	void Analyse(token x);//��״̬�����ı�current
	void Wrongs();//���ݽ���ʱ��location���б���
	void Run(string filename);//���̿��ƺ���
};
#endif // ! _PROLOG__H

