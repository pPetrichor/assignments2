#include"Prolog.h"
bool if_consult = 1;//判断consult是否成功
void word_analyse::analyse(char ch)
{
	if (ch == '(') { current.content = "("; current.variety = "symbol"; token_list.push_back(current); current.content.clear(); flag = 1; location = "start"; return; }
	if (ch == ',') { current.content = ","; current.variety = "symbol"; token_list.push_back(current); current.content.clear(); location = "start"; return; }
	if (ch == ')') { current.content = ")"; current.variety = "symbol"; token_list.push_back(current); current.content.clear(); flag = 0; location = "start"; return; }
	if (ch == '.') { current.content = "."; current.variety = "symbol"; token_list.push_back(current); current.content.clear(); location = "start"; return; }
	if(location=="start")
	{
		if (ch >= 'A'&&ch <= 'Z') 
		{ 
			current.variety = "variable"; current.content += ch;
			if (!((next >= 'a'&&next <= 'z') || (next >= 'A'&&next <= 'Z') || (next == '_' || next >= '0'&&next <= '9')))
			{
				token_list.push_back(current); current.content.clear(); location = "start";
			}
			location = "va";
		}
		else if ((ch >= 'a'&&ch <= 'z') && !flag) 
		{ 
			current.variety = "atom"; current.content += ch;
			if (!((next >= 'a'&&next <= 'z') || (next >= 'A'&&next <= 'Z') || (next == '_' || next >= '0'&&next <= '9')))
			{
				token_list.push_back(current); current.content.clear(); location = "start";
			}
			location = "atom";
		}
		else if ((ch >= 'a'&&ch <= 'z') && flag) 
		{
			current.variety = "constant"; current.content += ch;
			if (!((next >= 'a'&&next <= 'z') || (next >= 'A'&&next <= 'Z') || (next == '_' || next >= '0'&&next <= '9')))
			{
				token_list.push_back(current); current.content.clear(); location = "start";
			}
			location = "co";
		}
		else {
			cout << "word error :line " << current.number << " can't idenfy symbol " << ch << endl; if_consult = 0;
		}
	}
	else 
	{
		if (!((next >= 'a'&&next <= 'z') || (next >= 'A'&&next <= 'Z') || (next == '_' || next >= '0'&&next <= '9')))
		{
			current.content += ch;
			token_list.push_back(current); current.content.clear(); location = "start";
		}
		else current.content += ch;
	}
}
void word_analyse::run(string filename)
{
	string file = filename + ".pl";
	ifstream fin(file);
	if (!fin) { cout << "file can't open" << endl; if_consult = 0; }
	else
	{
		string s; int line = 0;
		std::getline(fin, s);
		while (s.length() != 0)
		{
			++line;
			current.number = line;
			int n = 0;
			while (n < s.length())
			{
				if (n < s.length() - 1) next = s[n + 1]; else next = ' ';
				if (s[n] == '-') {
					cout << "word error :line " << line << " can't idenfy symbol '-'  remind:right symbol: ':-'" << endl;  if_consult = 0;
				}
				else if (s[n] == ':')
				{

					++n;
					if (s[n] != '-') {
						cout << "word error :line " << line << " can't idenfy symbol ':'  remind:right symbol: ':-'" << endl;  if_consult = 0;
					}
					else
					{
						current.content = ":-"; current.variety = "symbol"; token_list.push_back(current); current.content.clear();
					}
				}
				else if (s[n] == ' ') { if (current.content.size() != 0) token_list.push_back(current); current.content.clear(); }
				else if (s[n] == '/')//注释
				{
					++n;
					if (s[n] != '*') {
						cout << "word error :line " << line << " can't idenfy symbol '/'  remind:right symbol: '/* */'" << endl;  if_consult = 0;
					}
					else
					{
						++n;
						while (n < s.length() && s[n] != '*') ++n;
						if (n >= s.length() - 1 || (s[n + 1] != '/'&&s[n + 1] != '*')) {
							if ((s[s.length() - 1] == '/'&&s[s.length() - 2] == '*')) break;
							else
							cout << "structure error :line " << line << " wrong note:lack of */  remind:right symbol: '/* */'" << endl;  if_consult = 0;
						}
						else if (s[n + 1] == '*')
						{
							while (n < s.length() - 1 && s[n + 1] == '*') ++n;
							if (n == s.length() - 1 && s[n] != '/') {
								cout << "structure error :line " << line << " wrong note:lack of */  remind:right symbol: '/* */'" << endl; if_consult = 0;
							}
							else
							{
								if (s[n + 1] != '/') {
									cout << "structure error :line " << line << " wrong note:lack of */  remind:right symbol: '/* */'" << endl;  if_consult = 0;
								}
								else ++n;
							}
						}
						else ++n;
					}
				}
				else analyse(s[n]);
				++n;
			}
			if (fin.peek() == EOF) break;
			std::getline(fin, s);
			if (s.length() == 0) std::getline(fin, s);//处理下一句
			flag = 0;
		}
	}
	
}
void rules_analyse::Wrongs()
{
	bool wrong = 0;//最后检测
	list<token>::iterator it = words.token_list.begin();
	list<token>::iterator t = it; ++t;
	while (t != words.token_list.end()) { ++it; ++t; }
	int n = (*it).number;
	list<fact>::iterator fa = all_facts.begin();
	for(;fa!=all_facts.end();++fa)
	{
		for(t = (*fa).arguments.begin();t!= (*fa).arguments.end();++t)
		{
			if ((*t).variety != "constant")
			{
				wrong = 1;
				cout << "structure error :line " << (*t).number << " variable appear in facts" << endl;
				if_consult = 0;
			}
		}
	}
	list<rule>::iterator ru;
	for(ru=all_rules.begin();ru!=all_rules.end();++ru)
	{
		list<fact>::iterator f;
		for(f=(*ru).facts.begin();f!=(*ru).facts.end();++f)
		{
			list<fact>::iterator fa_ = all_facts.begin();
			while(fa_!=all_facts.end())
			{
				if ((*f).atom == (*fa_).atom && (*f).arguments.size() == (*fa_).arguments.size()) break;
				else ++fa_;
			}
			if(fa_==all_facts.end())
			{
				wrong = 1;
				it = (*f).arguments.begin();
				cout << "structure error :line " << (*it).number << " can't find the fact "<<(*f).atom<<"(with "<<(*f).arguments.size()<<" arguments)" << endl;
				if_consult = 0;
			}
		}
	}
	if (location == "Start"&&if_consult)
	{
		cout << "true." << endl;
		ofstream fout("token.txt", ios::trunc);
		fout << "content" << '\t' << "variety" << endl;
		list<token>::iterator i;
		for (i = words.token_list.begin(); i != words.token_list.end(); ++i)
		{
			fout << (*i).content << '\t' << (*i).variety << endl;
		}
		fout.close();
	}
	else if_consult = 0;
	if (location == "Atom") cout << "structure error :line " << n << "ended with atom, lack '(……).'!" << endl;
	if (location == "(") cout << "structure error :line " << n << "ended with '(', lack '……).'!" << endl;
	if (location == "Va") cout << "structure error :line " << n << "ended with variable, lack ').'!" << endl;
	if (location == "Co") cout << "structure error :line " << n << "ended with constant, lack ').'!" << endl;
	if (location == ",") cout << "structure error :line " << n << "ended with ',', lack '……).'!" << endl;
	if (location == ")") cout << "structure error :line " << n << "ended with ')', lack '.'!" << endl;
	if (location == ":-") cout << "structure error :line " << n << "ended with ':-', lack facts after it!" << endl;
	
}
void rules_analyse::Run(string filename)
{
	words.run(filename);
	if (words.token_list.size() != 0)
	{
		list<token>::iterator it;
		for (it = words.token_list.begin(); it != words.token_list.end(); ++it)
		{
			list<token>::iterator temp = it;
			temp++;
			Analyse(*it);
			if (temp != words.token_list.end() && (*temp).number - (*it).number != 0)//换行
			{
				if ((*it).content == ")") { cout << "structure error :line " << (*it).number << " a sentence should ended with '.', lack '.'!" << endl; if_consult = 0; }
				else if ((*it).content != ".") { cout << "structure error :line " << (*it).number << " a sentence should ended with ').', lack ').'!" << endl; if_consult = 0; }
				else
				{
					list<token>::iterator t = it; t--;
					if ((*t).content != ")") { cout << "structure error :line " << (*it).number << " a sentence should ended with ').', lack ')' before '.'!" << endl; if_consult = 0; }
				}
				location = "Start";
				Flag = 0;
				a.arguments.clear();
				b.arguments.clear();
				b.facts.clear();
			}
		}//重写，结束循环后，用wrongs结合当前停止状态判断
		Wrongs();
	}
}
void rules_analyse::Analyse(token x)
{
	if(location=="Start")
	{
		if(x.variety=="atom")
		{
			location = "Atom";
			a.atom = x.content; b.atom = x.content;
		}
		else {
			cout << "structure error :line " << x.number << " a sentence should begin with an atom! Not a " << x.variety<< endl;  if_consult = 0; location = "Atom";
		}
	}
	else if(location=="Atom")
	{
		if(x.content=="(")
		{
			location = "(";
		}
		else { cout << "structure error :line " << x.number << " lack of '(' after atom!" << endl; if_consult = 0; }
	}
	else if(location=="(")
	{
		if(x.variety=="variable")
		{
			location = "Va";
			if(!Flag)//不是rule后的fact
			{
				a.arguments.push_back(x);
				b.arguments.push_back(x);
			}
			else
			{
				a.arguments.push_back(x);
			}
		}
		else if(x.variety=="constant")
		{
			location = "Co";
			if (!Flag)//不是rule后的fact
			{
				a.arguments.push_back(x);
				b.arguments.push_back(x);
			}
			else
			{
				a.arguments.push_back(x);
			}
		}
		else
		{
			cout << "structure error :line " << x.number << " "<<x.variety<<" is placed after '(' ,an argument should be placed after '('!" << endl;
			if_consult = 0;
		}
	}
	else if(location=="Va")
	{
		if(x.content==",")  location = ",";
		else if (x.content == ")") location = ")";
		else
		{
			if (x.variety == "variable" || x.variety == "constant")
			{
				cout << "structure error :line " << x.number << " arguments should be divided by ',' ,please check and add the ',' or check whether ' ' should be deleted!" << endl; if_consult = 0;
			}
			else if (x.variety == "symbol")
			{
				cout << "structure error :line " << x.number << " arguments should be divided by ',' or ended by ')'!" << endl; if_consult = 0;
			}
		}
	}
	else if(location=="Co")
	{
		if (x.content == ",")  location = ",";
		else if (x.content == ")") location = ")";
		else
		{
			if (x.variety == "variable" || x.variety == "constant")
			{
				cout << "structure error :line " << x.number << " arguments should be divided by ',' ,please check and add the ',' or check whether ' ' should be deleted!" << endl; if_consult = 0;
			}
			else if (x.variety == "symbol")
			{
				cout << "structure error :line " << x.number << " arguments should be divided by ',' or ended by ')'!" << endl; if_consult = 0;
			}
		}
	}
	else if(location==",")
	{
		if(x.variety=="variable")
		{
			location = "Va";
			if (!Flag)//不是rule后的fact
			{
				a.arguments.push_back(x);
				b.arguments.push_back(x);
			}
			else
			{
				a.arguments.push_back(x);
			}
		}
		if (x.variety == "constant")
		{
			location = "Co";
			if (!Flag)//不是rule后的fact
			{
				a.arguments.push_back(x);
				b.arguments.push_back(x);
			}
			else
			{
				a.arguments.push_back(x);
			}
		}
		else { cout << "structure error :line " << x.number << " arguments should be divided by ',' or ended by ')'!" << endl; if_consult = 0; }
	}
	else if(location==")")
	{
		if(x.content==".")
		{
			location = "Start";
			if (Flag) {
				b.facts.push_back(a); all_rules.push_back(b); b.arguments.clear(); b.facts.clear(); b.atom.clear(); a.arguments.clear(); a.atom.clear();
			}
			else { all_facts.push_back(a); a.arguments.clear(); a.atom.clear(); b.arguments.clear(); b.facts.clear(); b.atom.clear();
			}
		}
		else if(x.content==":-")
		{
			location = ":-";
			if(Flag)
			{
				cout<< "structure error :line " << x.number << " find repeated ':-' , please check whether mistake ',' '.' as ':-'!" << endl;
				if_consult = 0;
			}
			else
			{
				Flag = 1; a.arguments.clear();
			}
		}
		else if(x.content==","&&Flag)
		{
			location = ",&&-:";
			b.facts.push_back(a);
			a.arguments.clear();
			a.atom.clear();
		}
		else 
		{
			if (x.content == ",")
			{
				cout << "structure error :line " << x.number << " error ','! only :- and . can be placed here!" << endl; if_consult = 0;
			}
			else if (Flag)
			{
				cout << "structure error :line " << x.number << " error ','! only :-  . and , can be placed here!" << endl; if_consult = 0;
			}
			else
			{
				cout << "structure error :line " << x.number << " error '" << x.content << "'! only :-  . and , can be placed here!" << endl; if_consult = 0;
			}
		}
	}
	else if(location==":-")
	{
		if(x.variety=="atom")
		{
			location = "Atom";
			a.atom = x.content;
		}
		else { cout << "structure error :line " << x.number << " " << x.variety << " is after ':-' ,an atom should be after it!" << endl; if_consult = 0; }
	}
	else if(location==",&&:-")
	{
	if (x.variety == "atom")
	{
		location = "Atom";
		a.atom = x.content;
	}
	else { cout << "structure error :line " << x.number << " " << x.variety << " is after ',' ,an atom should be after it!" << endl; if_consult = 0; }
	}
}
struct result
{
	string wa;//查询变量
	string ge;//变量查询结果
};
int main()
{
	string s; bool has_con = 0;
	cout << "?-";
	std::getline(cin, s);
	string s1, s2;
	rules_analyse my_analyse;
	while(1)
	{
		if (s == "halt.") break;
		else
		{
			if ((!(s[0] >= 'a'&&s[0] <= 'z')) || s[s.length() - 1] != '.') 
			{
				printf("\033[31;1merror input!\n"); 
				printf("\033[37;1m");
				if(!has_con)
				if_consult = 0;
			}
			else
			{
				s1.clear();
				for (int t = 0; t < 8; ++t) s1.push_back(s[t]);
				if (s1 == "consult("&&s[s.length() - 2] == ')')//合法consult
				{
					s2.clear();
					for (int t = 8; t< s.length() - 2; ++t) s2.push_back(s[t]);
					has_con = 1; if_consult = 1;
					my_analyse.clean();
					my_analyse.Run(s2);
				}
				else
				{
					s1.clear();
					for (int t = 0; t < 7; ++t) s1.push_back(s[t]);
					if(s1=="insert ")//增加fact操作
					{
						for (int t = 0; t < 7; ++t) s.erase(s.begin());
						bool type = 0;//判断查询类型
						int i = 1;
						while ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z') || (s[i] == '_' || s[i] >= '0'&&s[i] <= '9')) ++i;//先不考虑空格影响
						if (s[i] != '(') {
							printf("\033[31;1merror input!\n");
							printf("\033[37;1m");
						}
						else
						{
							++i;
							if (s[i] >= 'A'&&s[i] <= 'Z') type = 1;
							while (s[i] != ')')
							{
								while ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z') || (s[i] == '_' || s[i] >= '0'&&s[i] <= '9')) ++i;
								if (s[i] != ','&&s[i] != ')') {
									printf("\033[31;1merror input!\n");
									printf("\033[37;1m"); break;
								}
								else if (s[i] == ',') { ++i; if (s[i] >= 'A'&&s[i] <= 'Z') type = 1; }
							}
							if (s[i] == ')')//查询语句合法
							{
								if (!if_consult || !has_con)
									cout << "no .pl has been consulted successfully" << endl;
								else if (type)
								{ 
									printf("\033[31;1merror:variable in fact!\n");
									printf("\033[37;1m");
								}
								else
								{
									fact input;
									i = 0;
									while (s[i] != '(') { input.atom += s[i]; ++i; }
									++i; token argument_;
									while (s[i] != '.')
									{
										argument_.content.clear();
										while (s[i] != ','&&s[i] != ')')
										{
											argument_.content += s[i]; ++i;
										}
										input.arguments.push_back(argument_); ++i;
									}//读入输入fact
									my_analyse.all_facts.push_back(input);
									string file = s2 + ".pl";
									ofstream fout(file,ios::app);
									if(!fout)
									{
										cout << "file can't open" << endl;
									}
									else { fout << endl << s ; fout.close(); }
									ofstream fo("token.txt", ios::app);
									if (!fo)
									{
										cout << "file can't open" << endl;
									}
									else
									{
										fo << input.atom << '\t' << "atom" << endl;
										fo << '(' << '\t' << "symbol" << endl;
										list<token>::iterator q; int o = 1;
										for(q=input.arguments.begin();q!=input.arguments.end();++q)
										{
											fo << (*q).content << '\t' << (*q).variety << endl;
											if(o==input.arguments.size()) fo << '(' << '\t' << "symbol" << endl;
											else fo << ',' << '\t' << "symbol" << endl;
											++o;
										}
										cout << "insert successfully!" << endl; 
									}
								}
							}
						}
					}
					else
					{
						
						
							bool type = 0;//判断查询类型
							int i = 1;
							while ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z') || (s[i] == '_' || s[i] >= '0'&&s[i] <= '9')) ++i;//先不考虑空格影响
							if (s[i] != '(') {
								printf("\033[31;1merror input!\n");
								printf("\033[37;1m");
							}
							else
							{
								++i;
								if (s[i] >= 'A'&&s[i] <= 'Z') type = 1;
								while (s[i] != ')')
								{
									while ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z') || (s[i] == '_' || s[i] >= '0'&&s[i] <= '9')) ++i;
									if (s[i] != ','&&s[i] != ')') {
										printf("\033[31;1merror input!\n");
										printf("\033[37;1m"); break;
									}
									else if (s[i] == ',') { ++i; if (s[i] >= 'A'&&s[i] <= 'Z') type = 1; }
								}
								if (s[i] == ')')//查询语句合法
								{
									if (!if_consult || !has_con)
										cout << "no .pl has been consulted successfully" << endl;
									else
									{
										fact input;
										i = 0;
										while (s[i] != '(') { input.atom += s[i]; ++i; }
										++i; token argument_;
										while (s[i] != '.')
										{
											argument_.content.clear();
											while (s[i] != ','&&s[i] != ')')
											{
												argument_.content += s[i]; ++i;
											}
											input.arguments.push_back(argument_); ++i;
										}
										if (!type)
										{
											list<fact>::iterator search; bool get = 0;
											for (search = my_analyse.all_facts.begin(); search != my_analyse.all_facts.end(); ++search)
											{

												if (input.atom == (*search).atom&&input.arguments.size() == (*search).arguments.size())
												{
													list<token>::iterator visit = (*search).arguments.begin();
													list<token>::iterator input_ = input.arguments.begin();
													while (visit != (*search).arguments.end())
													{
														if ((*input_).content != (*visit).content) break;
														++visit; ++input_;
													}
													if (visit == (*search).arguments.end()) { get = 1; break; }
												}
											}
											if (get) cout << "true." << endl;
											else {
												//进入rules查找

												printf("\033[31;1mfalse\n");
												printf("\033[37;1m");
											}
										}
										else//有变量查询
										{
											list<fact>::iterator search;  bool get = 0;//判断其余常量是否完全一致
											result out; list<result> all_outs; out.ge = "nothing_get_now";
											for (search = my_analyse.all_facts.begin(); search != my_analyse.all_facts.end(); ++search)
											{

												if (input.atom == (*search).atom&&input.arguments.size() == (*search).arguments.size())
												{
													list<token>::iterator visit = (*search).arguments.begin();
													list<token>::iterator input_ = input.arguments.begin();
													while (visit != (*search).arguments.end())
													{
														if ((*input_).content[0] >= 'a' && (*input_).content[0] <= 'z')
														{
															if ((*input_).content != (*visit).content) break;
														}
														else
														{
															out.ge = (*visit).content;
															out.wa = (*input_).content;
															all_outs.push_back(out);

														}
														++visit; ++input_;
													}
													if (visit == (*search).arguments.end() && out.ge != "nothing_get_now") { get = 1; }

												}

											}
											if (!get)
											{
												cout << "can't find the searching ";
												list<result>::iterator q;
												for (q = all_outs.begin(); q != all_outs.end(); ++q)
												{
													cout << (*q).wa << " ";
												}
												cout << endl;
											}
											else
											{
												list<result>::iterator q;
												for (q = all_outs.begin(); q != all_outs.end(); ++q)
												{
													cout << (*q).wa << " = " << (*q).ge << " ";
												}
												cout << endl;
											}
										}
									}
								}
							}
						
					}
				}
			}
			
			
		}
		cout << "?-";
		std::getline(cin, s);
		if(s.length()==0) std::getline(cin, s);
	}
	return 0;
}