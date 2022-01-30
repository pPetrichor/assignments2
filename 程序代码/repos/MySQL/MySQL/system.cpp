#include"system_.h"
int system_::analysis(string order)
{
	if (order[0] == 'l'&&order[1] == 'o'&&order[2] == 'g'&&order[3] == 'i'&&order[4] == 'n'&&order[5] == ':') return 1;
	istringstream ss(order);
	vector<string> columns;
	string name;
	while (ss >> name) columns.push_back(name);
	if(columns[0]=="CREATE"&&columns[1]=="TABLE"&&columns[columns.size()-2]=="TO")
	{
		columns.erase(columns.begin()); columns.erase(columns.begin()); columns.erase(columns.begin()); columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
		bool flag = 1;
		if(columns.size()==1)
		{if (columns[0][0] != '('|| columns[0][columns[0].length()-1] != ')') flag = 0; }
		else
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length()-1] != ',') flag = 0;
			for(int i=1;i<columns.size()-1;++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (columns[columns.size() - 1][columns[columns.size() - 1].length() - 1] != ')') flag = 0;
		}
		if (flag) return 2;
	}
	if (columns[0] == "CREATE"&&columns[1] == "TABLE"&&columns[3] == "FROM"&&columns.size() == 5) return 3;
	if (columns[0] == "DROP"&&columns[1] == "TABLE"&&columns.size() == 3) return 4;
	if (columns[0] == "TABLE"&&columns[1] == "LIST"&&columns.size()==2) return 5;
	if(columns[0] == "INSERT"&&columns[1] == "INTO"&&columns[3] == "VALUES")
	{
		columns.erase(columns.begin());
		columns.erase(columns.begin());
		columns.erase(columns.begin());
		columns.erase(columns.begin());
		bool flag = 1;
		if (columns.size() == 1)
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ')') flag = 0;
		}
		else
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ',') flag = 0;
			for (int i = 1; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (columns[columns.size() - 1][columns[columns.size() - 1].length() - 1] != ')') flag = 0;
		}
		if (flag) return 6;
	}
	if (columns[0] == "INSERT"&&columns[1] == "INTO")
	{
		columns.erase(columns.begin()); columns.erase(columns.begin()); columns.erase(columns.begin());
		if (columns[columns.size() / 2] != "VALUES") { cout << "error input!Please check the number data insert and data input" << endl; return -1; }
		columns.erase(columns.begin() + columns.size() / 2);
		vector<string> columns_;
		int c = columns.size() / 2;
		for(int i=0;i<c;++i)
		{
			columns_.push_back(columns[0]);
			columns.erase(columns.begin());
		}
		bool flag1 = 1;
		if (columns.size() == 1)
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ')') flag1 = 0;
		}
		else
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ',') flag1 = 0;
			for (int i = 1; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag1 = 0; break;
				}
			}
			if (columns[columns.size() - 1][columns[columns.size() - 1].length() - 1] != ')') flag1 = 0;
		}
		bool flag = 1;
		if (columns.size() == 1)
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ')') flag = 0;
		}
		else
		{
			if (columns[0][0] != '(' || columns[0][columns[0].length() - 1] != ',') flag = 0;
			for (int i = 1; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (columns[columns.size() - 1][columns[columns.size() - 1].length() - 1] != ')') flag = 0;
		}
		if (flag1&&flag) return 7;
	}
	if (columns[0] == "DELETE"&&columns[1] == "FROM"&&columns[3] == "WHERE"&&columns[5] == "="&&columns.size() == 7) return 8;
	if (columns[0] == "DELETE"&&columns[1] == "*"&&columns[2] == "FROM"&&columns.size() == 4) return 9;
	if(columns[0]=="SELECT"&&columns[1] != "*"&&columns[1] != "DISTINCT"&&columns[columns.size()-2]=="FROM")
	{
		columns.erase(columns.begin());
		columns.erase(columns.end()-1); columns.erase(columns.end()-1);
		bool flag = 1;
		if (columns.size() == 1)
			return 10;
		else
		{
			for (int i = 0; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (flag) return 10;
		}
	}
	if (columns[0] == "SELECT"&&columns[1] == "*"&&columns[2] == "FROM"&&columns.size() == 4) return 11;
	if (columns[0] == "SELECT"&&columns[1] == "DISTINCT"&&columns[columns.size() - 2] == "FROM")
	{
		columns.erase(columns.begin()); columns.erase(columns.begin());
		columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
		bool flag = 1;
		if (columns.size() == 1)
			return 12;
		else
		{
			for (int i = 0; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (flag) return 12;
		}
	}
	if (columns[0] == "SELECT"&&columns[1] == "*"&&columns[2] == "FROM"&&columns[4]=="ORDER"&&columns[5] == "BY")
	{
		for(int i=0;i<6;++i) columns.erase(columns.begin());
		bool flag = 1;
		if (columns.size() % 2 == 1)
		{
			cout << "the number of data input and data sort don't match!"<<endl;
		}
		else
		{
			for (int i = 1; i < columns.size() - 1; i+=2)
			{
				if (columns[i] != "ASC"&& columns[i] != "DESC"&&columns[i] != "ASC," && columns[i] != "DESC,") {
					flag = 0;
					cout << "error position of ASC or DESC"<<endl;
					break;
				}
			}
			if (flag) return 13;
		}
	}
	if(columns[0]=="SELECT"&&columns[columns.size()-2]=="=")
	{
		bool flag = 1;
		columns.erase(columns.begin());
		columns.erase(columns.end() - 1);columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
		if(columns[columns.size() - 1] == "WHERE"&&columns[columns.size() - 3] == "FROM")
		{
			columns.erase(columns.end() - 1); columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
			for (int i = 0; i < columns.size() - 1; ++i)
			{
				if (columns[i][columns[i].length() - 1] != ',') {
					flag = 0; break;
				}
			}
			if (flag) return 14;
		}
	}
	if (columns[0] == "SELECT"&&columns[columns.size() - 2] == "TO"&&columns[columns.size() - 4] == "FROM") return 15;
	if (columns[0] == "SELECT"&&columns[1]!="*"&&columns[columns.size() - 2] == "TO"&&columns[columns.size() - 4] == "="&&columns[columns.size() - 6] == "WHERE"&&columns[columns.size() - 8] == "FROM") return 16;
	if (columns[0] == "SELECT"&&columns[1] == "*"&&columns[2] == "FROM"&&columns[4] == "WHERE"&&columns[6] == "="&&columns[8]=="TO") return 17;
	if (columns[0] == "quit"&&columns.size() == 1) return 18;
	if (columns[0] == "GRANT"&&columns[columns.size() - 2] == "to") return 19;
	if (columns[0] == "REVOKE"&&columns[2] == "on"&&columns[4] == "from") return 20;
	if(columns[0]=="SELECT"&&columns[1]=="*"&&columns[2]=="from"&&columns[4]=="WHERE"&&columns[6]!="=") return 21;
	return -1;
}
void system_::run()
{
	bool bug = 1;
	cout << "(mysql)==> ";
	string order_input; getline(cin, order_input);
	int chose = analysis(order_input);
	int user_login_in = -1;
	while(1)
	{
		switch(chose)
	{
		case -1: {cout << "error input!" << endl; break; }
	case 1://login
	{
		string username;
		for (int i = 6; i < order_input.length(); ++i) username += order_input[i];
		int n = 0;
		for (; n < all_users.size(); ++n)
		{
			if (username == all_users[n].id) break;
		}
		if (n == all_users.size()) cout << "can't find the user!" << endl;
		else if (n < all_users.size())
		{
			if (all_users[n].login())
			{
				user_login_in = n;
				ifstream fi(all_users[n].journalname);
				if (!fi) { cerr << "   open file failure!" << endl; }
				else
				{
					string order__;
					getline(fi, order__);
					if (order__.length() == 0) cout << "welcome!" << endl;
					else
					{
						cout << order__<< endl;
						string ord; cin >> ord;
						if (ord == "Y")
						{
							istringstream ss(order__);
							vector<string> columns;
							string nam;
							while (ss >> nam) columns.push_back(nam);
							string receiver = columns[2];
							string power_ = columns[4];
							string table_ = columns[9];
							string order_make;
							order_make += "GRANT "; order_make += power_; order_make += " on "; order_make += table_; order_make += " to ";
							order_make += receiver;
							grant(user_login_in, order_make);
							cout << "grant successfully!" << endl;
						
						}
					fstream file___(all_users[n].journalname, ios::out);
	
					}
				}
			}
			else cout << "wrong keyword!login fall!" << endl;
		}
		break;
	}
	case 2://creattable_tofile
	{
		if (user_login_in == -1) { cout << "Please login first!" << endl; break; }
		all_users[user_login_in].creattable_tofile(order_input, all_users,user_login_in); break;
	}
	case 3://creattable_fromfile
	{
		if (user_login_in == -1) { cout << "Please login first!" << endl; break; }
		all_users[user_login_in].creattable_fromfile(order_input, all_users,user_login_in); break;
	}
	case 4://drop
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].drop(order_input, all_users); }
		break;
	}
	case 5://list
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].list(); }
		break;
	}
	case 6://insert_all
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].insert_all(order_input, all_users); }
		break;
	}
	case 7://insert
	{
		if (user_login_in == -1) cout <<"Please login first!" << endl;
		else { all_users[user_login_in].insert(order_input, all_users); }
		break;
	}
	case 8://delete_part
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].Delete_part(order_input, all_users); }
		break;
	}
	case 9://delete_all
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].Delete_all(order_input, all_users); }
		break;
	}
	case 10://select_part
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_part(order_input, all_users); }
		break;
	}
	case 11://select_all
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_all(order_input, all_users); }
		break;
	}
	case 12://select distinct
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_distinct(order_input, all_users); }
		break;
	}
	case 13://select_in_order
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_order(order_input, all_users); }
		break;
	}
	case 14://keyword show
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_keyword(order_input, all_users); }
		break;
	}
	case 15://to file 1
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_tofile_1(order_input, all_users); }
		break;
	}
	case 16://to file 2
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_tofile_2(order_input, all_users); }
		break;
	}
	case 17://to file 3
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else { all_users[user_login_in].select_tofile_3(order_input, all_users); }
		break;
	}
	case 18://quit
	{
		user_login_in = -1;//quit
		for(int i=0;i<all_users.size();++i)
		{
			ofstream f(all_users[i].filename, ios::trunc);
			for(int j=0;j<all_users[i].user_holds.size();++j)
			{
				f << all_users[i].user_holds[j].table_txtname << '\t' << all_users[i].user_holds[j].table_name << '\t' << all_users[i].user_holds[j].powers[0].num
					<< '\t' << all_users[i].user_holds[j].powers[1].num << '\t' << all_users[i].user_holds[j].powers[2].num << '\t' << all_users[i].user_holds[j].powers[3].num
					<< '\t' << all_users[i].user_holds[j].owner << endl;
				int n = 0;
				while (n < all_users[i].user_holds[j].powers[0].kids.size())
				{
					f << all_users[i].user_holds[j].powers[0].kids[n] << '\t'; ++n;
				}
				f << "#" << endl;
				n = 0;
				while (n < all_users[i].user_holds[j].powers[1].kids.size())
				{
					f << all_users[i].user_holds[j].powers[1].kids[n] << '\t'; ++n;
				}
				f << "#" << endl;
				n = 0;
				while (n < all_users[i].user_holds[j].powers[2].kids.size())
				{
					f << all_users[i].user_holds[j].powers[2].kids[n] << '\t'; ++n;
				}
				f << "#" << endl;
				n = 0;
				while (n < all_users[i].user_holds[j].powers[3].kids.size())
				{
					f << all_users[i].user_holds[j].powers[3].kids[n] << '\t'; ++n;
				}
				if (j == all_users[i].user_holds.size() - 1) f << "#";
				else f << "#" << endl;
			}
			f.close();
		}
		return;
	}//information put in file
	case 19://GRANT   
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else grant(user_login_in, order_input);
		break;
	}
	case 20:
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else revoke(user_login_in, order_input); 
		break;
	}
	case 21:
	{
		if (user_login_in == -1) cout << "Please login first!" << endl;
		else all_users[user_login_in].compare(order_input); 
		break;
	}
}
	cout << "(mysql)==> ";
	getline(cin, order_input);
	if(order_input.size()==0) getline(cin, order_input);
	chose = analysis(order_input);
	}
}
void system_::grant(int giver, string order)
{
	istringstream ss(order);
	vector<string> columns;  string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 3];
	string receiver = columns[columns.size() - 1];
	int x = 0;
	while (all_users[giver].user_holds[x].table_name != name && x < all_users[giver].user_holds.size()) x++;
	if (x == all_users[giver].user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	columns.erase(columns.begin());
	columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
	columns.erase(columns.end() - 1); columns.erase(columns.end() - 1);
	while (columns.size() > 0)
	{
		int n = 0;
		if (columns[0] == "DROP" || columns[0] == "DROP,") n = 0;
		if (columns[0] == "INSERT" || columns[0] == "INSERT,") n = 1;
		if (columns[0] == "DELETE" || columns[0] == "DELETE,") n = 2;
		if (columns[0] == "SELECT" || columns[0] == "SELECT,") n = 3;
		if (all_users[giver].user_holds[x].powers[n].num <= 0) cout << "You don't get the power, can't grant!" << endl;
		else
		{
			int i = 0;
			for (; i < all_users[giver].user_holds[x].powers[n].kids.size(); ++i)
				if (receiver == all_users[giver].user_holds[x].powers[n].kids[i]) break;
			
			if (i < all_users[giver].user_holds[x].powers[n].kids.size() && all_users[giver].user_holds[x].powers[n].kids.size()!=0) cout << "You have granted the receiver this power!" << endl;
			else
			{
				all_users[giver].user_holds[x].powers[n].kids.push_back(receiver);
				for (int i = 0; i < all_users.size(); ++i)
				{
					if (all_users[i].id == receiver)
					{
						all_users[i].user_holds[x].powers[n].num++; break;
					}
				}
			}
		}
		columns.erase(columns.begin());
	}
}
void system_::REVOKE(admission &a,string kill,int x,int n)
{
	if (a.kids.size() == 0) return;int i = 0;
	for ( ;i < a.kids.size(); ++i)
	{
		if(a.kids[i]==kill||a.kids[i]+',' == kill)
		{
			 break;
		}
	}
	if (i == a.kids.size()) {
		cout << "didn't find this user at grant list!" << endl; return;
	}
	a.kids.erase(a.kids.begin() + i);
	int l = 0;
	for(;l<all_users.size();++l)
	{
		if (all_users[l].id == kill|| all_users[l].id+',' == kill)
			break;
	}
	all_users[l].user_holds[x].powers[n].num--;
	for(int k=0;k<all_users[l].user_holds[x].powers[n].kids.size();++k)
	{
		REVOKE(all_users[l].user_holds[x].powers[n], all_users[l].user_holds[x].powers[n].kids[k], x, n);
	}
}
void system_::revoke(int giver, string order)
{
	istringstream ss(order);
	vector<string> columns;  string name;
	while (ss >> name) columns.push_back(name);
	name = columns[3];
	string power_ = columns[1];
	int n = 0;
	if (power_ == "DROP") n = 0;
	if (power_ == "INSERT") n = 1;
	if (power_ == "DELETE") n = 2;
	if (power_ == "SELECT") n = 3;
	int x = 0;
	while (all_users[giver].user_holds[x].table_name != name && x < all_users[giver].user_holds.size()) x++;
	if (x == all_users[giver].user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	for(int y=0;y<5;++y)
	columns.erase(columns.begin());
	while (columns.size() > 0)
	{
		REVOKE(all_users[giver].user_holds[x].powers[n],columns[0],x,n);
		columns.erase(columns.begin());
	}
}
