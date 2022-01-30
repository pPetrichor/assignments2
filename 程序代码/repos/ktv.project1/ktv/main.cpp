#include"Administrator.h"
#include"interact.h"
#include"user.h"
#include<fstream>
#pragma once
int main()
{
	Administrator admin("C:\\first.txt");
	user visitor;vector<user> users;
	fstream fin("C:\\users.txt");
	if (!fin) { cerr << "打开文件失败"; Sleep(1000); exit(-1); }
	else
	{
		while (!fin.eof())
		{
			string id, key; string name;
			fin >> id;
			fin >> key;
			fin >> name;
			user a(id, key, name);
			users.push_back(a);
		}
		fin.close();
	}
	interact show;
	char ch = '-1'; bool log = 1;
	while (ch!='0')
	{
		show.show_first();
		ch = _getch();
		switch (ch)
		{
		case '1':visitor.List = visit_library(&admin); system("cls"); visitor.run(); admin.get_comment(&visitor); break;

		case '2':if (log) { system("cls"); admin.Run(log); }
				 else { cout << "管理员登陆已锁死"; Sleep(1000); system("cls"); } break;
		case '3':
		{
			system("cls");
			show.show_login_();
			cout << "   请输入您的ID：";
			string ID_get;
			cin >> ID_get; int i = 0; bool f = 0;
			for(;i<users.size();++i)
			{
				if (ID_get == users[i].getid()) {f = 1; break;}
			}
			if (!f) { cout << "   未查找到该用户!"; Sleep(1000); system("cls"); }
			else
			{
				users[i].List = visit_library(&admin); system("cls"); users[i].run_(); admin.get_comment(&users[i]);
			}

			break;
		}
		case '4':
		{
			system("cls");
			show.show_new();
			string id; string keyword; bool flag = 1; char s[50];
			cin >> id;
			for (int i = 0; i < users.size(); ++i)
			{
				if (id == users[i].getid()) { flag = 0; break; }
			}
			if (!flag) { cout << "   此ID已被使用！";  Sleep(1000);system("cls"); }
			else
			{
				cout << "   请输入您设定的密码："; cin >> keyword;
				cout << "   请输入您设定的存储信息的文件名："; cin >> s;
				FILE *fp;
				fp = fopen(s, "w"); //指定打开的文件路径与文件名，不存在就新建一个.
				if (fp == NULL) { cout << "   创建文件失败!"; return 0; }
				fclose(fp);
				delete fp;
				user a(id, keyword, s);
				users.push_back(a);
				cout << "   注册成功!"; Sleep(1000); system("cls");

				ofstream f("C:\\users.txt", ios::trunc);
				for(int i=0;i<users.size();++i)
				{
					f <<endl<< users[i].getid() << '\t' << users[i].getkeyword() << '\t' << users[i].gettxt_name();
				}
				f.close();
			}
		}break;
		}
	}
	cout << "   欢迎下次使用(*^_^*)";
	Sleep(1000);
	return 0;
}