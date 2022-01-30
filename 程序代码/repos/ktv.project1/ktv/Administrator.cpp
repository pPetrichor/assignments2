#include"Administrator.h"
#include"user.h"
#include<fstream>
Administrator::Administrator(const char*s)//初始化歌库
{
	ID = "whl"; Keyword = "csSY1";
	fstream fin(s);
	if (!fin) { cerr << "打开文件失败"; Sleep(1000); exit(-1); }
	else
	{
		while (!fin.eof())
		{
			song_in_library a;
			fin >> a.song_name;
			fin >> a.singer;
			fin >> a.abbre;
			a.id = List_in_library.size() + 1; a.num = 0; a.score = 0;
			List_in_library.push_back(a);
		}
		fin.close();
		for(int i=0;i<List_in_library.size();++i)
		{
			double n = (rand() % 5), m = (rand() % 10), q = (rand() % 10);
			double a = n + m / 10 + q / 100;
			List_in_library[i].score = a;
			List_in_library[i].num = rand() % 100;
		}
	}
}
bool Administrator::judge_ID(string s)//判断ID合法性
{
	unsigned int n = s.size();
	if (n > 20) return 0;
	for(int i=0;i<n;++i)
	{
		if (!((s[i] >= 'A'&&s[i] <= 'Z')|| (s[i] >= 'a'&&s[i] <= 'z')|| (s[i] >= '0'&&s[i] <= '9'))) return 0;
	}
	return 1;
}
bool Administrator::judge_Keyword(string s)//判断密码合法性
{
	unsigned int n = s.size(); bool flag1 = 0; bool flag2 = 0; bool flag3 = 0;
	if (n > 12) return 0;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] >= 'A'&&s[i] <= 'Z') flag1 = 1;
		if (s[i] >= 'a'&&s[i] <= 'z') flag2 = 1;
		if (s[i] >= '0'&&s[i] <= '9') flag3 = 1;
	}
	if (flag1&&flag2&&flag3) return 1;
	else return 0;
}
bool Administrator::login_in()//管理员登陆
{
	int x = 3;//共三次输入机会
	while (x > 0)
	{
		x--;
		if (x == 2) cout << "请输入您的ID："; else cout << "   请输入您的ID：";
		string ID_get;
		cin >> ID_get;
		cout << "   请输入您的密码:";
		string Keyword_get; char ch; ch = _getch(); Keyword_get += ch;
		while (ch != '\n'&&ch != '\r')
		{
			cout << "*";
			ch = _getch();
			if (ch != '\n'&&ch != '\r') Keyword_get += ch;
		}
		cout << endl;
		if(!judge_ID(ID_get)) cout<<"   ID不合法,请重新输入（剩余机会:" << x << ")" << endl;
		if (!judge_Keyword(Keyword_get)) cout << "   密码不合法,请重新输入（剩余机会:" << x << ")" << endl;
		if (ID == ID_get && Keyword == Keyword_get) { cout << "   " << ID << "    欢迎登陆!正在为您跳转……"; Sleep(1000); return 1; }
		else if (ID != ID_get) cout << "   未找到此用户ID，请重新输入（剩余机会:" << x << ")" << endl;
		else cout << "   密码错误，请重新输入（剩余机会:" << x << ")" << endl;
		Sleep(1000);
	}
	cout << "   登陆失败！锁定登陆系统!"; Sleep(1000);
	system("cls");
	return 0;
}
bool Administrator::Keyword_change()//管理员密码修改
{
	string old_Keyword, new_Keyword1, new_Keyword2;
	cout << "请输入当前密码："; cin >> old_Keyword;
	cout << "   请输入修改后密码(不超过12个字符，必须同时包括大小写字母和数字)："; cin >> new_Keyword1;
	cout << "   请确认修改后密码："; cin >> new_Keyword2;
	if (Keyword != old_Keyword) { cout << "   密码输入错误！修改失败！"; Sleep(1000); return 0; }
	if(new_Keyword1!= new_Keyword2) { cout << "   修改后密码输入不一致，修改失败！"; Sleep(1000); return 0; }
	if (Keyword == new_Keyword1) { cout << "   密码未发生改变，修改失败！"; Sleep(1000); return 0; }
	if(!judge_Keyword(new_Keyword1)) { cout << "   密码不合法，请检查后重新设定，修改失败！"; Sleep(1000); return 0; }
	Keyword = new_Keyword1;
	cout << "修改成功！"; Sleep(1000); return 1;
}
void Administrator::song_library()//查询所有歌曲信息
{
	interact a; int n = List_in_library.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch!=27)//27为ESC键
	{
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10&&i<n; ++t)
		{
			a.gotoxy(7, l); cout << List_in_library[i].id;
			a.gotoxy(24, l); cout << List_in_library[i].song_name;
			a.gotoxy(45, l); cout << List_in_library[i].singer; ++i; ++l;//打印歌曲信息
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
		ch= _getch();
		switch(ch)
		{
		case 'w':
		{
			if (k > 1 && k < page) { i -= 20; k--; }
			else if (i % 10 != 0&&k==1) i -= i % 10; 
			else if(k==1) i -= 10;
			else {i -= (i % 10 + 10); --k;}
			system("cls");
			break;
		}
		case 's': 
		{if (k < page) { k++; } else if (i % 10 != 0)i -= i % 10; else i -= 10; system("cls");  break; }
		}
	}
}
void Administrator::add_song()//添加歌曲
{
		song_in_library a; bool flag = 1; int i;
		cin >> a.song_name >> a.singer >> a.abbre; a.score = 0; a.num = 0;
		for (i = 0; i < List_in_library.size(); ++i)
		{
			if (a.song_name == List_in_library[i].song_name&&a.singer == List_in_library[i].singer) { flag = 0; break; }
		}
		if (flag)
		{
			a.id = List_in_library.size() + 1;
			List_in_library.push_back(a);
			cout << "   歌曲已为您添加到歌库，请查收！" << endl;
		}
		else if (!flag&&a.abbre != List_in_library[i].abbre) cout << "   歌曲已存在，但拼音缩写不一致，请检查后重新输入" << endl;
		else cout << "   歌曲已存在，添加失败。" << endl;
		cout << "   按任意键以继续添加，输入ESC返回主界面." << endl;
}
void Administrator::bulk_add()//批量导入歌曲
{
	string name_txt;
	cin >> name_txt;
	if (name_txt == "1") return;
	int succeed = 0; int fail = 0; int all = 0;
	fstream fin(name_txt);
	if (!fin) { cerr << "   打开文件失败"; Sleep(1000); exit(-1); }
	else
	{
		while (!fin.eof())
		{
			song_in_library a; int i = 0; bool flag = 1;
			fin >> a.song_name;
			fin >> a.singer;
			fin >> a.abbre;
			for (i = 0; i < List_in_library.size(); ++i)
			{
				if (a.song_name == List_in_library[i].song_name&&a.singer == List_in_library[i].singer) { flag = 0; break; }
			}
			if (flag)
			{
				succeed++; a.id = List_in_library.size() + 1;
				double n = (rand() % 5), m = (rand() % 10), q = (rand() % 10);
				double b = n + m / 10 + q / 100;
				a.score = b;
				a.num = rand() % 100;
				List_in_library.push_back(a);
			}
			else fail++;
			++all;
		}
		fin.close();
	}
		cout << "   导入完成!共导入" << all << "首歌曲" << endl << "   其中导入成功" << succeed << "首" << ",失败" << fail << "首。" << endl << "   原因：歌库中已存在" << endl;
		Sleep(1000);
}
void Administrator::delete_song()//删除歌曲+重新编号
{
	interact a; int n = List_in_library.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27为ESC键
	{
		l = 2; a.show_delete_song();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List_in_library[i].id;
			a.gotoxy(24, l); cout << List_in_library[i].song_name;
			a.gotoxy(45, l); cout << List_in_library[i].singer; ++i; ++l;//打印歌曲信息
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
		cout << endl << endl << "   输入0以进行删除操作" << endl;
		ch = _getch();
		switch (ch)
		{
		case 'w':
		{
			if (k > 1 && k < page) { i -= 20; k--; }
			else if (i % 10 != 0 && k == 1) i -= i % 10;
			else if (k == 1) i -= 10;
			else { i -= (i % 10 + 10); --k; }
			system("cls");
			break;
		}
		case 's':
		{if (k < page) { k++; } else if (i % 10 != 0)i -= i % 10; else i -= 10; system("cls");  break; }
		case '0':
		{
			cout << "   请输入要删除的歌曲的编号，输入0以结束删除：";
			int kill = 0; cin >> kill;
			if (kill == 0) { cout << "正在返回主界面……"; Sleep(2000); return; }
			else if (kill < 0 || kill>List_in_library.size()) { cout << "   不存在此编号歌曲，请检查后输入"; i = 0; Sleep(500); system("cls"); }
			else
			{
				cout << "   确认删除吗？（y/n）";
				char c = _getch();
				while (1)
				{
					if (c == 'y')
					{
						List_in_library.erase(List_in_library.begin() + kill - 1);
						for (int i = 0; i < List_in_library.size(); ++i)
							List_in_library[i].id = i + 1;
						cout << "   删除成功！"; Sleep(2000); system("cls"); i = 0; n--;
						break;
					}
					else if (c == 'n') { cout << "   删除失败！"; Sleep(2000); system("cls"); i = 0; break; }
					else c = _getch();
				}
			}
			break;
		}
		}
	}
}
void Administrator::sort_library()//歌曲排序
{
	cout << "请选择排序方式：" << endl << "按评分排（输入1）" << endl << "按评价人数排（输入2）" << endl << "返回主界面（输入0）";
	char x = _getch();
	if(x=='1')
	{
		system("cls");
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.score > y.score; });
		interact a; int n = List_in_library.size(); int i = 0; int k = 1;
		int page = 0; char ch = 0;
		if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
		a.show_sort();
		while (ch != 27)//27为ESC键
		{
			l = 2; a.show_sort();
			for (int t = 0; t < 10 && i < n; ++t)
			{
				a.gotoxy(7, l); cout << List_in_library[i].score;
				a.gotoxy(24, l); cout << List_in_library[i].id;
				a.gotoxy(45, l); cout << List_in_library[i].song_name;
				a.gotoxy(66, l); cout << List_in_library[i].singer; ++i; ++l;//打印歌曲信息
			}
			a.gotoxy(0, 12);
			cout << "------------------------------------------------------------" << endl;
			cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
			ch = _getch();
			switch (ch)
			{
			case 'w':
			{
				if (k > 1 && k < page) { i -= 20; k--; }
				else if (i % 10 != 0 && k == 1) i -= i % 10;
				else if (k == 1) i -= 10;
				else { i -= (i % 10 + 10); --k; }
				system("cls");
				break;
			}
			case 's':
			{if (k < page) { k++; } else if (i % 10 != 0)i -= i % 10; else i -= 10; system("cls");  break; }
			}
		}
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.id < y.id; });
	}
	if (x == '2')
	{
		system("cls");
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.num > y.num; });
		interact a; int n = List_in_library.size(); int i = 0; int k = 1;
		int page = 0; char ch = 0;
		if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
		a.show_sort2();
		while (ch != 27)//27为ESC键
		{
			l = 2; a.show_sort2();
			for (int t = 0; t < 10 && i < n; ++t)
			{
				a.gotoxy(7, l); cout << List_in_library[i].score;
				a.gotoxy(24, l); cout << List_in_library[i].id;
				a.gotoxy(45, l); cout << List_in_library[i].song_name;
				a.gotoxy(66, l); cout << List_in_library[i].singer;
				a.gotoxy(87, l); cout << List_in_library[i].num;
				++i; ++l;
				//打印歌曲信息
			}
			a.gotoxy(0, 12);
			cout << "----------------------------------------------------------------------" << endl;
			cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
			ch = _getch();
			switch (ch)
			{
			case 'w':
			{
				if (k > 1 && k < page) { i -= 20; k--; }
				else if (i % 10 != 0 && k == 1) i -= i % 10;
				else if (k == 1) i -= 10;
				else { i -= (i % 10 + 10); --k; }
				system("cls");
				break;
			}
			case 's':
			{if (k < page) { k++; } else if (i % 10 != 0)i -= i % 10; else i -= 10; system("cls");  break; }
			}
		}
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.id < y.id; });
	}
	if (x == 0) { cout << "正在跳传……"; Sleep(1000); return; }
}
void Administrator::get_comment(const user *l)//更新歌库中评分
{
	for (int i = 0; i < List_in_library.size(); ++i)
	{
		List_in_library[i].score = (*l).List[i].score;
		List_in_library[i].num = (*l).List[i].num;
	}

}
void Administrator::Run(bool &log)
{
	interact a;
	a.show_login();
	if (!login_in()) { log = 0; Sleep(100); return; }
	else 
	{
		system("cls");
		a.show_Administrator();
		char ch = _getch(); char c = '-1';
		while (ch != '0')
		{
			system("cls");
			switch (ch)
			{
			case '1':a.show_all_songs();
				song_library(); system("cls"); break;
			case '2':a.show_add_song(); add_song();
				 c=_getch();
				while (c != 27) 
				{
					system("cls");
					a.show_add_song();
					add_song(); c = _getch();
				} 
				system("cls"); break;
			case '3':a.show_bulk_add(); bulk_add(); system("cls"); break;
			case '4':a.show_delete_song(); delete_song(); system("cls"); break;
			case '5':sort_library(); system("cls"); break;
			case '6':a.show_Keyword_change(); Keyword_change(); system("cls"); break;
			}
			a.show_Administrator(); ch = _getch();
		}
		system("cls");
	}

}
vector<song_in_library> visit_library(const Administrator *a)
{
	return a->List_in_library;
}