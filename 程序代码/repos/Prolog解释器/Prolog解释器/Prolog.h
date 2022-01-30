#ifndef _PROLOG__H
#define _PROLOG__H
#include<iostream>
#include<list>
#include<string>
#include<fstream>
using namespace std;
struct token
{
	string content;//内容
	string variety;//类型
	int number;//行数
};
struct fact
{
	string atom;//fact的谓词
	list <token> arguments;//记录括号中所有元素内容及类型
};
struct rule
{
	string atom;//rule的谓词
	list <token> arguments;//记录rule括号中所有元素内容及类型
	list <fact> facts;//记录该规则涉及到的所有fact
};

class word_analyse
{
private:
	string location;//当前位置
	char next;//记录下一步走向
	token current;//记录下当前产生的token,之后添加到token_list中
	bool flag;
public:
	list<token> token_list;
	word_analyse() { location = "start"; current.number = 0; flag = 0; }//从起点出发
	void analyse(char ch);//走状态机，改变token,根据当前的location与next进行报错，即如果next记录无法与状态机任一路径匹配，则有非法字符或注释
	void run(string filename);//流程控制函数，读文件
	void clean()//每处理完一句之后更新至初始状态
	{
		location = "start"; current.number = 0; flag = 0;
		token_list.clear();
	}
};
class rules_analyse
{
private:
	string location;//当前位置
	fact a;
	rule b;//a用于存储rule中的fact,b用于将一句rule的所有变量存储下来
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
	list<fact> all_facts;//fact记录表
	list<rule> all_rules;//rule记录表
	rules_analyse() { location = "Start"; Flag = 0; }
	void Analyse(token x);//走状态机，改变current
	void Wrongs();//根据结束时的location进行报错
	void Run(string filename);//流程控制函数
};
#endif // ! _PROLOG__H

