#include"user.h"
bool user::login()
{
	string keyword;
	cout << "(mysql)==> password:";
	cin >> keyword;
	if (key == keyword) return 1;
	else return 0;
}
void user::creattable_tofile(string order,vector<user> &xx,int num)
{
	vector< vector<string> > table; vector<string> x;
	x.push_back("ID");
	string tablename;
	int i = 13;
	while (order[i] != ' ') { tablename += order[i]; ++i; }
	i += 2;
	while (order[i] != ')')
	{
		string y;
		while (order[i] != ','&&order[i] != ')') { y += order[i]; ++i; }
		x.push_back(y);
		if (order[i] == ',') i += 2;
	}
	table.push_back(x);
	i += 5;
	string file; int n = 0;
	while (i < order.length()) { file += order[i]; ++n; ++i; }
	for (int i = 0; i < xx[num].user_holds.size(); ++i) { if (xx[num].user_holds[i].table_name == tablename) { cout << "the table name has been used!" << endl; return; } }
	for (int i = 0; i < xx[num].user_holds.size(); ++i) { if (xx[num].user_holds[i].table_txtname == file) { cout << "the txt name has been used!" << endl; return; } }
	ofstream fout(file);
	if (!fout) { cout << "creat file failed!"<< endl; return; }
	fout << table[0].size() - 1 << '\t' << table.size() - 1 << endl;
	for (int i = 0; i < table[0].size(); ++i)
	{
		fout << table[0][i] << '\t';
	}
	fout.close();
	operat newtable; newtable.owner = 1; newtable.table_name = tablename; newtable.table_txtname = file;
	newtable.powers[0].num = 1; newtable.powers[1].num = 1; newtable.powers[2].num = 1; newtable.powers[3].num = 1;
	xx[num].user_holds.push_back(newtable);
	operat newtable_; newtable_.owner = 0; newtable_.table_name = tablename; newtable_.table_txtname = file;
	newtable_.powers[0].num = 0; newtable_.powers[1].num = 0; newtable_.powers[2].num = 0; newtable_.powers[3].num = 0;
	for(int i=0;i<xx.size();++i)
	{
		if (i != num) xx[i].user_holds.push_back(newtable_);
	}
}
void user::creattable_fromfile(string order, vector<user> &xx,int n)
{
	string tablename;
	int i = 13;
	while (order[i] != ' ') { tablename += order[i]; ++i; }
	i += 6;
	char file[50] = { '\0' }; int n_ = 0;
	while (i < order.length()) { file[n_] = order[i]; ++n_; ++i; }
	for (int i = 0; i < xx.size(); ++i) { if (xx[n].user_holds[i].table_name == tablename) { cout << "the table name has been used!" << endl; return; } }
	fstream _file; _file.open(file, ios::in);
	if (!_file) { cout << "the file doesn't exit!"<< endl; return; }
	cout << "Please input the txt name of the new table:"; 
	while(1)
	{
		string filename; 
		cin >> filename;
		fstream _file; _file.open(filename, ios::in);
		if (_file) { cout << "the txt name has been used!" << endl; }
		else
		{
			ofstream fout(filename);
			if (!fout) { cout << "creat table failed!" << endl; return; }
			ifstream fin(file); char dataline[50];
			while (fin.getline(dataline, 50)) fout << dataline << endl;
			fin.close(); fout.close();
			operat newtable; newtable.owner = 1; newtable.table_name = tablename; newtable.table_txtname = filename;
			newtable.powers[0].num = 1; newtable.powers[1].num = 1; newtable.powers[2].num = 1; newtable.powers[3].num = 1;
			xx[n].user_holds.push_back(newtable);
			operat newtable_; newtable_.owner = 0; newtable_.table_name = tablename; newtable_.table_txtname = filename;
			newtable_.powers[0].num = 0; newtable_.powers[1].num = 0; newtable_.powers[2].num = 0; newtable_.powers[3].num = 0;
			for (int i = 0; i < xx.size(); ++i)
			{
				if (i != n) xx[i].user_holds.push_back(newtable_);
			}
			break;
		}
	}
}
void user::drop(string order,vector<user>& all_users)
{
	string name; int i = 11;
	while (i < order.length()) { name += order[i]; ++i; }
	int l = 0;
	for(;l<user_holds.size();++l)
	{
		if (user_holds[l].table_name == name) break;
	}
	if (l == user_holds.size()) {
		cout << "didn't find the table!" << endl; return;
	}
	char kill[20] = { '\0' };
	for (int i = 0; i < user_holds[l].table_txtname.length(); ++i)
	{
		kill[i] = user_holds[l].table_txtname[i];
	}
	if (user_holds[l].powers[0].num <= 0)
	{
		cout << "Permission denied!"<<endl;
		for(int m=0;m<all_users.size();++m)
		{
			if (all_users[m].user_holds[l].owner)
			{
				time_t now_time = time(NULL);   
				tm*  t_tm = localtime(&now_time);      
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request DROP TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	for (int i = 0; i < all_users.size(); ++i)
		for (int j = 0; j < all_users[i].user_holds.size(); ++j)
		{
			if (all_users[i].user_holds[j].table_name == name)
			{
				all_users[i].user_holds.erase(all_users[i].user_holds.begin() + j); break;
			}
		}
			
	if (remove(kill)) cout << "drop failed!" << endl;
}
void user::list()
{
	int total = 0;
	for(int i=0;i<user_holds.size();++i)
	{
		if (user_holds[i].powers[0].num > 0 || user_holds[i].powers[1].num > 0 || user_holds[i].powers[2].num > 0 || user_holds[i].powers[3].num > 0)
			++total;
	}
	cout << '\t' << "total:" << total << endl;
	for(int i=0;i<user_holds.size();++i)
	{
		if (user_holds[i].powers[0].num > 0 || user_holds[i].powers[1].num > 0 || user_holds[i].powers[2].num > 0 || user_holds[i].powers[3].num > 0)
		{
			cout << '\t' << '\t' << user_holds[i].table_name << ": ";
			fstream fin(user_holds[i].table_txtname);
			if (!fin) { cout << "open file failed!" << endl; }
			else
			{
				int x, y;
				fin >> x >> y;
				cout << '(' << x << ',' << y << ") [";
				string columni; fin >> columni;
				for (int i = 0; i < x - 1; ++i)
				{
					fin >> columni; cout << columni << ", ";
				}
				fin >> columni; cout << columni << "] ";
				fin.close();
				if (user_holds[i].owner) cout << "DROP, INSERT, DELETE, SELECT [OWNER]" << endl;
				else
				{
					if (user_holds[i].powers[0].num > 0) cout << "DROP, ";
					if (user_holds[i].powers[1].num > 0) cout << "INSERT, ";
					if (user_holds[i].powers[2].num > 0) cout << "DELETE, ";
					if (user_holds[i].powers[3].num > 0) cout << "SELECT ";
					cout << endl;
				}
			}
		}
	}
}
void user::insert_all(string order, vector<user>& all_users)
{
	vector<vector<string>> w;
	istringstream ss(order);
	vector<string> columns;
	string nam;
	while (ss >> nam) columns.push_back(nam);
	int i = 12; int x = 0; string name;
	while (order[i] != ' ') { name += order[i]; ++i; }
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size()) 
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[1].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);   
				tm*  t_tm = localtime(&now_time);     
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request INSERT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	fstream fin(user_holds[x].table_txtname);
	int n = 0;
	if (!fin) { cout << "open file failed" << endl; }
	else
	{
		fin >> n;
		if (n != columns.size() - 4) { cout << "number of columns doesn't match the table!" << endl; return; }
		fin >> n;
	}
	ofstream f(user_holds[x].table_txtname, ios::trunc);
	f << w[0].size() - 1 << '\t' << w.size()<< endl;
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
			f << w[i][j] << '\t';
		f << endl;
	}
	f  << n + 1 << '\t';
	while (order[i] != '(') ++i; ++i;
	while (order[i] != ')')
	{
		string y;
		while (order[i] != ','&&order[i] != ')') { y += order[i]; ++i; }
		f << y << '\t';
		if (order[i] == ',') i += 2;
	}
	f.close();
}
void user::insert(string order, vector<user>& all_users)
{
	vector< vector<string> > w;
	int i = 12; int x = 0; string name;
	while (order[i] != ' ') { name += order[i]; ++i; }
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[1].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);  
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request INSERT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	fstream fin(user_holds[x].table_txtname);
	int n1, n2; string column; vector<string>columns;
	if (!fin) { cout << "open file failed!" << endl; }
	else
	{
		fin >> n1; fin >> n2;
		fin >> column;
		for(int i=0;i<n1;++i)
		{
			fin >> column; columns.push_back(column);
		}
	}
	vector<string> select; vector<string> data;
	while (order[i] != '(') ++i; ++i;
	while (order[i] != ')')
	{
		string y;
		while (order[i] != ','&&order[i] != ')') { y += order[i]; ++i; }
		select.push_back(y);
		if (order[i] == ',') i += 2;
	}
	while (order[i] != '(') ++i; ++i;
	while (order[i] != ')')
	{
		string y;
		while (order[i] != ','&&order[i] != ')') { y += order[i]; ++i; }
		data.push_back(y);
		if (order[i] == ',') i += 2;
	}
	ofstream f(user_holds[x].table_txtname, ios::trunc);
	f << w[0].size() - 1 << '\t' << w.size() << endl;
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
			f << w[i][j] << '\t';
		f << endl;
	}
	f << n2 + 1 << '\t';
	for(int i=0;i<n1;++i)
	{
		bool flag = 0; int j = 0;
		for(;j<select.size();++j)
		{
			if (select[j] == columns[i]) { flag = 1; break; }
		}
		if (flag) f << data[j] << '\t';
		else f << "EOF!" << '\t';
	}
	f.close();
}
bool user::get_data(string name, vector<vector <string> > &x)
{
	string o=" "; 
	fstream fin(name);if (!fin) { cout << "open file failed!" << endl; return 0; }
	else
	{
	int n1, n2;
	fin >> n1 >> n2;
	for (int i = 0; i < n2+1; ++i)
	{
		vector<string> line;
		for (int j = 0; j < n1+1; ++j)
		{
			line.push_back(o);
		}
		x.push_back(line);
	}
		for (int i = 0; i < n2+1; ++i)
		{
			for (int j = 0; j < n1+1; ++j)
			{
				fin >> x[i][j];
			}
		}
	}
	return 1;
}
void user::Delete_part(string order, vector<user>& all_users)
{
	vector<vector< string> > w;
	int i = 12; int x = 0; string name;
	while (order[i] != ' ') { name += order[i]; ++i; }
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[2].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);  
				tm*  t_tm = localtime(&now_time);   
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request DELETE TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	i += 7; string column;
	while (order[i] != ' ') { column += order[i]; ++i; }
	i += 3;
	string select;
	while (i < order.length()) { select += order[i]; ++i; }
	int k = 0; int t = 0;
	for (; k < w[0].size(); ++k)
	{
		if (w[0][k] == column) break;
	}
	if (k == w[0].size()) { cout << "didn't find the column in table!" << endl; return; }
	for (; t < w.size(); ++t)
	{
		if (w[t][k] == select) break;
	}
	if (t == w.size()) { cout << "didn't find the element in table!" << endl; return; }
	w.erase(w.begin() + t);
	ofstream f(user_holds[x].table_txtname, ios::trunc);
	f << w[0].size()-1 << '\t' << w.size()-1 << endl;
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
		{
			if (j == 0 && i > 0) 
			{
				char s = i + 48;
				string ss; ss += s;
				f << ss<<'\t';
			}
			else f << w[i][j] << '\t';
		}
		f << endl;
	}
	f.close();
}
void user::Delete_all(string order, vector<user>& all_users)
{
	int i = 14; int x = 0; string name;
	while (i<order.length()) { name += order[i]; ++i; }
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[2].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);  
				tm*  t_tm = localtime(&now_time);    
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request DELETE TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	fstream fin(user_holds[x].table_txtname);
	int n1, n2; string id;
	fin >> n1 >> n2;
	vector<string> columns; 
	int o = 0;
	while (o < n1+1) { fin >> id; columns.push_back(id); ++o; }
	ofstream f(user_holds[x].table_txtname, ios::trunc); o = 0;
	f << columns.size()-1 << '\t' << '0' << endl;
	while (o < columns.size()) { f << columns[o] << '\t'; ++o; }
	f.close();
}
void user::select_part(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns;int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 1];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL); 
				tm*  t_tm = localtime(&now_time);    
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	columns.erase(columns.begin());
	columns.erase(columns.end()-1); columns.erase(columns.end()-1);
	for (int i=0; i < w.size(); ++i)
	{
		for(int j=0;j<w[0].size();++j)
		{
			bool flag = 0;
			for(int t=0;t<columns.size();++t)
			{
				if (columns[t] == w[0][j]|| columns[t] == w[0][j]+',') { flag = 1; break; }
			}
			if (flag&&w[i][j]!="EOF!") cout << w[i][j] << '\t';
			else if (flag) cout << '\t';
		}
		cout << endl;
	}
}
void user::select_all(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 1];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
		{
			if (w[i][j] != "EOF!") cout << w[i][j] << '\t';
			else cout << '\t';
		}
		cout << endl;
	}
}
void user::select_distinct(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 1];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	columns.erase(columns.begin()); columns.erase(columns.begin());
	columns.erase(columns.end()-1); columns.erase(columns.end()-1);
	for(int i = 0;i<w[0].size();++i) 
	{
		int j = 0;
		for ( ;j < columns.size(); ++j)
		{
			if (w[0][i] == columns[j]|| w[0][i]+',' == columns[j]) break;
		}
		if (j == columns.size())
		{
			for (int r = 0; r < w.size(); ++r)
			{
				w[r].erase(w[r].begin() + i);
			}
			--i;
		}
	}
	for(int i=0;i<w.size();++i)
	{
		for (int j = i+1;j<w.size();++j)
		{
			bool flag = 1;
			for(int t=0;t<w[0].size();++t)
			{
				if (w[i][t] != w[j][t]) { flag = 0; break; }
			}
			if(flag)
			{
				w.erase(w.begin() + j);
			}
		}
	}
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
		{
			if (w[i][j] != "EOF!") cout << w[i][j] << '\t';
			else cout << '\t';
		}
		cout << endl;
	}
}
void user::select_order(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[3];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	for (int i = 0; i < 6; ++i) { columns.erase(columns.begin()); }
	while (columns.size() > 0)
	{
		string x, y;
		x = columns[columns.size() - 2];
		y = columns[columns.size() - 1];
		columns.erase(columns.end()-1); columns.erase(columns.end()-1);
		int num = 0;
		for (;num < w[0].size()&& w[0][num] != x && w[0][num] + ',' != x  ; ++num);
		if (num == w[0].size()) { cout << "some elements to be sorted can't be find in table!" << endl; return; }
		if (y == "DESC"|| y == "DESC,")
			sort(w.begin()+1, w.end(), [=](vector<string> x, vector<string> y)->bool {return x[num] > y[num]; });
		else
			if (y == "ASC"|| y == "ASC,") sort(w.begin()+1, w.end(), [=](vector<string> x, vector<string> y)->bool {return x[num] < y[num]; });
	}
	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[0].size(); ++j)
		{
			if (w[i][j] != "EOF!") cout << w[i][j] << '\t';
			else cout << '\t';
		}
		cout << endl;
	}
}
void user::select_keyword(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 5];
	string value = columns[columns.size() - 1];
	string column = columns[columns.size() - 3];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	columns.erase(columns.begin());
	for(int u=0;u<6;++u)
	columns.erase(columns.end()-1); 
	for (int i = 0; i < w[0].size(); ++i)
	{
		int j = 0;
		for (; j < columns.size(); ++j)
		{
			if (w[0][i] == columns[j] || w[0][i] + ',' == columns[j]) break;
		}
		if (j == columns.size())
		{
			for (int r = 0; r < w.size(); ++r)
			{
				w[r].erase(w[r].begin() + i);
			}
			--i;
		}
	}
	int k = 0; int t = 0;
	for (; k < w[0].size(); ++k)
	{
		if (w[0][k] == column) break;
	}
	if (k == w[0].size()) { cout << "didn't find the element in table!" << endl; return; }
	for (; t < w.size(); ++t)
	{
		if (w[t][k] == value) break;
	}
	if(t==w.size()) { cout << "didn't find any element right!" << endl; return; }
	for(int l=0;l<w[0].size();++l)
	{
		cout << w[0][l] << '\t';
	}
	cout << endl;
	for (int l = 0; l < w[0].size(); ++l)
	{
		if (w[t][l] == "EOF!") cout << '\t';
		else cout << w[t][l] << '\t';
	}
	cout << endl;
}
void user::compare(string order)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[3];
	string value = columns[columns.size() - 1];
	string op=columns[6];
	string column = columns[columns.size() - 3];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return; 
	int k = 0; int t = 0;
	for (; k < w[0].size(); ++k)
	{
		if (w[0][k] == column) break;
	}
	if (k == w[0].size()) { cout << "didn't find the element in table!" << endl; return; }
	for (; t < w.size(); ++t)
	{
		if (w[t][k] == value) break;
	}
	if(t==w.size()) { cout << "didn't find any element right!" << endl; return; }
	for(int l=0;l<w[0].size();++l)
	{
		cout << w[0][l] << '\t';
	}
	cout << endl;
	if(op==">")
	{
	for (int l = 1; l < w.size(); ++l)
	{
		if(w[l][k]>value)
		{
		for(int u=0;u<w[0].size();++u)
		{
		if (w[l][u] == "EOF!") cout << '\t';
		else cout << w[l][u] << '\t';
		}
		}
	}
	}
	if(op=="<")
	{
	for (int l = 1; l < w.size(); ++l)
	{
		if(w[l][k]<value)
		{
		for(int u=0;u<w[0].size();++u)
		{
		if (w[l][u] == "EOF!") cout << '\t';
		else cout << w[l][u] << '\t';
		}
		cout << endl;
		}
	}
	}

	cout << endl;
}

void user::select_tofile_1(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 3]; string filename = columns[columns.size() - 1];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time); 
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	fstream _file; _file.open(filename, ios::in);
	if (_file) { cout << "the txt name has been used,please input again!" << endl; }
	else
	{
		if (!get_data(user_holds[x].table_txtname, w)) return;
		ofstream f(filename);
		if (!f) { cout << "creat txt failed!" << endl; return; }
		columns.erase(columns.begin());
		for (int u = 0; u < 4; ++u)
			columns.erase(columns.end() - 1);
		for (int i = 0; i < w[0].size(); ++i)
		{
			int j = 0;
			for (; j < columns.size(); ++j)
			{
				if (w[0][i] == columns[j] || w[0][i] + ',' == columns[j]) break;
			}
			if (j == columns.size())
			{
				for (int r = 0; r < w.size(); ++r)
				{
					w[r].erase(w[r].begin() + i);
				}
				--i;
			}
		}
		f << w[0].size() << '\t' << w.size() << endl;
		for (int i = 0; i < w.size(); ++i)
		{
			for (int j = 0; j < w[0].size(); ++j)
			{
				f << w[i][j] << '\t';
			}
			f << endl;
		}
	}
}
void user::select_tofile_2(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 7]; string filename = columns[columns.size() - 1];
	string value = columns[columns.size() - 3];
	string column = columns[columns.size() - 5];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	fstream _file; _file.open(filename, ios::in);
	if (_file) { cout << "the txt name has been used,please input again!" << endl; }
	else
	{
		ofstream f(filename);
		if (!f) { cout << "creat txt failed!" << endl; return; }
		columns.erase(columns.begin());
		for (int u = 0; u < 8; ++u)
			columns.erase(columns.end() - 1);
		for (int i = 0; i < w[0].size(); ++i)
		{
			int j = 0;
			for (; j < columns.size(); ++j)
			{
				if (w[0][i] == columns[j] || w[0][i] + ',' == columns[j]) break;
			}
			if (j == columns.size())
			{
				for (int r = 0; r < w.size(); ++r)
				{
					w[r].erase(w[r].begin() + i);
				}
				--i;
			}
		}
		f << w[0].size() << '\t' << "1" << endl;
		int k = 0; int t = 0;
		for (; k < w[0].size(); ++k)
		{
			if (w[0][k] == column) break;
		}
		if (k == w[0].size()) { cout << "didn't find the target in table!" << endl; return; }
		for (; t < w.size(); ++t)
		{
			if (w[t][k] == value) break;
		}
		if (t == w.size()) { cout << "didn't find the right element!" << endl; return; }
		for (int l = 0; l < w[0].size(); ++l)
		{
			f << w[0][l] << '\t';
		}
		f << endl;
		for (int l = 0; l < w[0].size(); ++l)
		{
			f << w[t][l] << '\t';
		}
		f << endl;
	}
}
void user::select_tofile_3(string order, vector<user>& all_users)
{
	vector<vector <string> > w;
	istringstream ss(order);
	vector<string> columns; int x = 0; string name;
	while (ss >> name) columns.push_back(name);
	name = columns[columns.size() - 7];string filename = columns[columns.size() - 1];
	string value = columns[columns.size() - 3];
	string column = columns[columns.size() - 5];
	while (user_holds[x].table_name != name && x < user_holds.size()) x++;
	if (x == user_holds.size())
	{
		cout << "didn't find the table!" << endl; return;
	}
	if (user_holds[x].powers[3].num <= 0)
	{
		cout << "Permission denied!" << endl;
		for (int m = 0; m < all_users.size(); ++m)
		{
			if (all_users[m].user_holds[x].owner)
			{
				time_t now_time = time(NULL);
				tm*  t_tm = localtime(&now_time);
				ofstream f(all_users[m].journalname, ios::trunc);
				f << "[System information] " << id << " request SELECT TABLE permission on table " << name << " at " << asctime(t_tm) << ",grant permission? (Y/N)";
				f.close();
			}
		}
		return;
	}
	if (!get_data(user_holds[x].table_txtname, w)) return;
	ofstream f(filename);
	if (!f) { cout << "create txt failed!" << endl; return; }
	f << w[0].size() << '\t' << "1" << endl;
	int k = 0; int t = 0;
	for (; k < w[0].size(); ++k)
	{
		if (w[0][k] == column) break;
	}
	if (k == w[0].size()) { cout << "didn't find the target in table!" << endl; return; }
	for (; t < w.size(); ++t)
	{
		if (w[t][k] == value) break;
	}
	if (t == w.size()) { cout << "didn't find the right element!" << endl; return; }
	for (int l = 0; l < w[0].size(); ++l)
	{
		f << w[0][l] << '\t';
	}
	f << endl;
	for (int l = 0; l < w[0].size(); ++l)
	{
		f << w[t][l] << '\t';
	}
	f << endl;
}
