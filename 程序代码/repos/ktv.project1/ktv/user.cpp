#include"user.h"
#include"Administrator.h"
#include"AudioClip.h"
AudioClip audio; string x;
void user::song_library()//查询所有歌曲信息
{
	interact a; int n = List.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27为ESC键
	{
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List[i].id;
			a.gotoxy(24, l); cout << List[i].song_name;
			a.gotoxy(45, l); cout << List[i].singer; ++i; ++l;//打印歌曲信息
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
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
}
void user::show_love()//查询我喜欢的信息
{
	interact a; int n = List_liked.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27为ESC键
	{
		l = 2; 
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List_liked[i].song_name;
			a.gotoxy(24, l);  cout << List_liked[i].singer;
			a.gotoxy(45, l); cout << List_liked[i].abbre; ++i; ++l;//打印歌曲信息
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
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
}
bool user::login_in_()
{
	interact a; a.show_login_();
	cout << "   请输入您的密码:";
	string Keyword_get; char ch; ch = _getch(); Keyword_get += ch;
	while (ch != '\n'&&ch != '\r')
	{
		cout << "*";
		ch = _getch();
		if (ch != '\n'&&ch != '\r') Keyword_get += ch;
	}
	cout << endl;
	if (keyword == Keyword_get) { cout << "   " << id << "    欢迎登陆!正在为您跳转……"; Sleep(1000); system("cls"); return 1; }
	else { cout << "   登陆失败！"; Sleep(1000); system("cls"); return 0; }
}
void user::search_by_song_name()//歌曲名点歌,点歌输入添加歌曲编号时不可以输入字母
{
	cout << "   请输入要查找的歌曲名，输入1返回主界面（可模糊查找）:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   正在返回……"; Sleep(500); return; }
	for(int i=0;i<List.size();++i)
	{
		if (List[i].song_name.find(name) != string::npos)
		{
			cout << "   " << List[i].id <<'\t'<< List[i].song_name <<'\t'<< List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   歌库中查找不到这首歌，试试别的歌曲吧(￣▽￣) 即将为您返回主页……"; Sleep(2000); return; }
	cout << "   请输入添加到列表的歌曲编号，输入0结束：";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   歌库中查找不到该编号歌曲，试试别的歌曲吧(￣▽￣)" << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
		else
		{
			bool t = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (rem[i] == List[n - 1].id) t = 1;
			}
			if (t)
			{
				cout << "   " << List[n - 1].id << '\t'<< List[n - 1].song_name << '\t'<< List[n - 1].singer << endl;
				bool flag = 1;
				for (int i = 0; i < List_in_play.size(); ++i)
				{
					if (List[n - 1].id == List_in_play[i].id) { flag = 0; break; }
				}
				if (flag)
				{
					song_play a; a.id = List[n - 1].id; a.abbre = List[n - 1].abbre; a.singer = List[n - 1].singer; a.song_name = List[n - 1].song_name; a.state = 0;
					a.n = List_in_play.size() + 1; List_in_play.push_back(a);
					cout << "   歌曲已成功添加到播放列表！" << endl;
				}
				else
				{
					cout << "   添加失败！原因：该歌曲已在播放列表中" << endl;
				}
			}
			else cout << "   搜索结果中似乎没有这首歌o_o ...." << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
	}
	cout << "   点歌结束！快去歌单看看吧O(∩_∩)O"; Sleep(1000); system("cls");
}
void user::search_by_singer()//歌星点歌
{
	cout << "   请输入要查找的歌手名，输入1返回主界面:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   正在返回……"; Sleep(500); return; }
	for (int i = 0; i < List.size(); ++i)
	{
		if (List[i].singer.find(name) != string::npos)
		{
			cout << "   " << List[i].id << '\t' << List[i].song_name << '\t' << List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   歌库中查找不到该歌手作品，试试别的歌曲吧(￣▽￣) 即将为您返回主页……"; Sleep(2000); return; }
	cout << "   请输入添加到列表的歌曲编号，输入0结束：";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{ 
			cout << "   歌库中查找不到该编号歌曲，试试别的歌曲吧(￣▽￣)" << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
		else
		{
			bool t = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (rem[i] == List[n - 1].id) t = 1;
			}
			if (t)
			{
				cout << "   " << List[n - 1].id << '\t' << List[n - 1].song_name << '\t' << List[n - 1].singer << endl;
				bool flag = 1;
				for (int i = 0; i < List_in_play.size(); ++i)
				{
					if (List[n - 1].id == List_in_play[i].id) { flag = 0; break; }
				}
				if (flag)
				{
					song_play a; a.id = List[n - 1].id; a.abbre = List[n - 1].abbre; a.singer = List[n - 1].singer; a.song_name = List[n - 1].song_name; a.state = 0;
					a.n = List_in_play.size() + 1; List_in_play.push_back(a);
					cout << "   歌曲已成功添加到播放列表！" << endl;
				}
				else
				{
					cout << "   添加失败！原因：该歌曲已在播放列表中" << endl;
				}
			}
			else cout << "   搜索结果中似乎没有这首歌o_o ...." << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
	}
	cout << "   点歌结束！快去歌单看看吧O(∩_∩)O"; Sleep(1000); system("cls");
}
void user::search_by_abbre()//首拼音点歌
{
	cout << "   请输入要查找的歌曲拼音，输入1返回主界面:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   正在返回……"; Sleep(500); return; }
	for (int i = 0; i < List.size(); ++i)
	{
		if (List[i].abbre.find(name) != string::npos)
		{
			cout << "   " << List[i].id << '\t' << List[i].song_name << '\t' << List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   歌库中查找不到这首歌，试试别的歌曲吧(￣▽￣) 即将为您返回主页……"; Sleep(2000); return; }
	cout << "   请输入添加到列表的歌曲编号，输入0结束：";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   歌库中查找不到该编号歌曲，试试别的歌曲吧(￣▽￣)" << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
		else
		{
			bool t = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (rem[i] == List[n - 1].id) t = 1;
			}
			if (t)
			{
				cout << "   " << List[n - 1].id << '\t' << List[n - 1].song_name << '\t' << List[n - 1].singer << endl;
				bool flag = 1;
				for (int i = 0; i < List_in_play.size(); ++i)
				{
					if (List[n - 1].id == List_in_play[i].id) { flag = 0; break; }
				}
				if (flag)
				{
					song_play a; a.id = List[n - 1].id; a.abbre = List[n - 1].abbre; a.singer = List[n - 1].singer; a.song_name = List[n - 1].song_name; a.state = 0;
					a.n = List_in_play.size() + 1; List_in_play.push_back(a);
					cout << "   歌曲已成功添加到播放列表！" << endl;
				}
				else
				{
					cout << "   添加失败！原因：该歌曲已在播放列表中" << endl;
				}
			}
			else cout << "   搜索结果中似乎没有这首歌o_o ...." << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
	}
	cout << "   点歌结束！快去歌单看看吧O(∩_∩)O"; Sleep(1000); system("cls");
}
void user::check_song_play()//查看已点歌曲
{
	interact a; int n = List_in_play.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27为ESC键
	{
		n = List_in_play.size();
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n&&i>=0; ++t)
		{
			if (List_in_play[i].state)
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer<<"——正在播放"; ++i; ++l;//打印歌曲信息
			}
			else
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer; ++i; ++l;//打印歌曲信息 
			}
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
		cout << endl << endl << "   输入1-->置顶歌曲" << endl << "   输入2-->移除歌曲" << endl << "   输入3-->切歌" << endl << "   输入0-->歌曲评分" << endl;
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
		case '1':
		{ a.show_set_first(); set_first(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		case '2':
		{ a.show_delete_song_in_play(); delete_song(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		case '3':
		{ next(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10;  break; }
		case '0':
		{ a.show_comment(); comment(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		}
	}
}
void user::check_song_play_()//查看用户已点歌曲
{
	interact a; int n = List_in_play.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27为ESC键
	{
		n = List_in_play.size();
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			if (List_in_play[i].state)
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer << "——正在播放"; ++i; ++l;//打印歌曲信息
			}
			else
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer; ++i; ++l;//打印歌曲信息 
			}
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "第" << k << "页，共" << page << "页，上一页（w），下一页（s）,输入ESC返回主页";
		cout << endl << endl << "   输入1-->置顶歌曲" << endl << "   输入2-->移除歌曲" << endl << "   输入3-->切歌" << endl << "   输入4-->添加到我喜欢的" << endl << "   输入0-->歌曲评分" << endl;
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
		case '1':
		{ a.show_set_first(); set_first(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		case '2':
		{ a.show_delete_song_in_play(); delete_song(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		case '3':
		{ next(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10;  break; }
		case '4':
		{ a.show_add_to_love();i_like(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10;  break; }
		case '0':
		{ a.show_comment(); comment(); system("cls"); if (i % 10 != 0) i -= i % 10; else i -= 10; break; }
		}
	}
}
void user::comment()//用户评分
{
	interact a;
		int judgement; cin >> judgement;
		if (judgement <= 0 || judgement > List_in_play.size()) { cout << "   未在播放列表中找到该歌曲╥﹏╥..."; Sleep(1000); }
		else
		{
			cout << "   请输入您的评分（1到5）：";
			int score_get; cin >> score_get;
			if (score_get < 1 || score_get > 5) { cout << "   暂不提供该分值，请重新输入" << endl; Sleep(1000); }
			else
			{
				int number = List_in_play[judgement - 1].id;
				List[number - 1].score = (List[number - 1].score*List[number - 1].num + score_get) / (List[number - 1].num + 1);
				List[number - 1].num++;
				cout << "   评分成功！感谢您的反馈，我们会努力做得更好^_^";
				Sleep(1000);
			}
		}
}
void user::set_first()//置顶歌曲：用户输入编号，将该歌置顶,0返回
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   不存在该编号歌曲！"; Sleep(500); return; }
	
	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{
		cout << endl << "   确定将此歌置顶吗？(y/n)";ch = _getch();
		if (ch == 'y')
		{
			
			song_play temp = List_in_play[n - 1];
			List_in_play[n - 1] = List_in_play[0];
			List_in_play[0] = temp;
			for(int i=0;i<List_in_play.size();++i)
			{
				List_in_play[i].n = i + 1;
			}
			cout << endl << "   置顶成功！"; Sleep(500);
		}
		else if (ch == 'n') return;
	}
}
void user::i_like()//添加到我喜欢
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   不存在该编号歌曲！"; Sleep(500); return; }

	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{
		cout << endl << "   确定将此歌添加到我喜欢吗？(y/n)"; ch = _getch();
		if (ch == 'y')
		{
			bool flag = 1;
			for(int i=0;i<List_liked.size();++i)
			{
				if(List_in_play[n-1].song_name==List_liked[i].song_name&&List_in_play[n - 1].singer == List_liked[i].singer) 
				{
					flag = 0; break;
				}
			}
			if (flag)
			{
				song_play a = List_in_play[n - 1];
				List_liked.push_back(a);
				cout << endl << "   添加成功！"; Sleep(500);
			}
			else
			{
				cout << endl << "   添加失败！原因：我喜欢的中已有此歌曲！"; Sleep(500);
			}
		}
		else if (ch == 'n') return;
	}
}
void user::delete_song()//移除歌曲：用户输入编号，将该歌移除
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   不存在该编号歌曲！"; Sleep(500); return; }
	
	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{	cout << endl << "   确定将此歌移除吗？(y/n)";
		ch = _getch();
		if (ch == 'y')
		{
			if(List_in_play[n-1].state==1)
			{
				List_in_play.erase(List_in_play.begin() + n - 1);
				audio.stop();  x = "Songs//" + List_in_play[0].song_name + ".mp3";
				audio.load(x); audio.play();
				List_in_play[0].state = 1;
			}//移除歌曲在播放则回到第一首
			else List_in_play.erase(List_in_play.begin() + n - 1);
			for (int i = 0; i < List_in_play.size(); ++i)
			{
				List_in_play[i].n = i + 1;
			}
			cout << "   删除成功！"; Sleep(1000);
		}
		else if (ch == 'n') return;
	}
}
void user::next()//切歌
{
	if (List_in_play.size() == 0)
	{
		cout << "   播放列表已空，去歌库中添加几首吧*^____^*"; Sleep(1000); return;
	}
	else if (List_in_play.size() == 1) { List_in_play.erase(List_in_play.begin()); audio.stop(); }
	else
	{
		int i = 0;
		for(;i<List_in_play.size();++i)
		{
			if (List_in_play[i].state == 1) break;
		}
		if (i + 1 < List_in_play.size())
		{
			 List_in_play[i+1].state = 1;
			 audio.stop();
			 x = "Songs//" + List_in_play[i+1].song_name + ".mp3";
			 audio.load(x); audio.play();List_in_play.erase(List_in_play.begin()+i);
		}
		else 
		{ 
			
			List_in_play[0].state = 1;
			audio.stop();
			x = "Songs//" + List_in_play[0].song_name + ".mp3";
			audio.load(x); audio.play();List_in_play.erase(List_in_play.begin() + i); 
		}//最后一首切歌回到第一首
		for (int i = 0; i < List_in_play.size(); ++i)
		{
			List_in_play[i].n = i + 1;
		}
	}
	cout << "   切歌成功！";
}
void user::recommend()//歌曲推荐
{
	sort(List.begin(), List.end(), [](song_in_library x, song_in_library y)->bool {return x.score > y.score; });
	int add = 0;
	int rem[5] = { 0 }; int r = 0;
	for(int i=0;i<List.size()&&add<5;++i)
	{
		bool flag = 1;
		for(int j=0;j<List_in_play.size();++j)
		{
			if (List[i].song_name == List_in_play[j].song_name&&List[i].singer == List_in_play[j].singer) flag = 0;
		}
		if(flag) 
		{
			cout << "   " << i+1 << '\t'<<'\t' << List[i].song_name << '\t'<<'\t' << List[i].singer << endl;
			rem[r] = List[i].id; ++r; ++add;
		}
	}
	cout << "   请输入添加到列表的歌曲编号，输入0结束：";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   歌库中查找不到该编号歌曲，试试别的歌曲吧(￣▽￣)" << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
		else
		{
			bool t = 0;
			for (int i = 0; i < 5; ++i)
			{
				if (rem[i] == List[n - 1].id) t = 1;
			}
			if (t)
			{
				bool f = 1;
				for (int i = 0; i < List_in_play.size(); ++i)
				{
					if (List[n - 1].id == List_in_play[i].id) { f = 0; break; }
				}
				if (f)
				{
					cout << "   " << n << '\t' << List[n - 1].song_name << '\t' << List[n - 1].singer << endl;
					song_play a; a.id = List[n - 1].id; a.abbre = List[n - 1].abbre; a.singer = List[n - 1].singer; a.song_name = List[n - 1].song_name; a.state = 0;
					a.n = List_in_play.size() + 1; List_in_play.push_back(a);
					cout << "   歌曲已成功添加到播放列表！" << endl;
				}
				else cout<< "   添加失败！列表中已有此歌曲！" << endl;
			}
			else cout << "   搜索结果中似乎没有这首歌o_o ...." << endl;
			cout << "   请输入添加到列表的歌曲编号，输入0结束："; cin >> n;
		}
	}
	cout << "   添加歌曲结束！快去歌单看看吧O(∩_∩)O"; Sleep(1000); system("cls");
	sort(List.begin(), List.end(), [](song_in_library x, song_in_library y)->bool {return x.id < y.id; });
}
void user::run()
{
	interact a;
	a.show_user();
	char ch = _getch();
	while (ch != '0')
	{
		system("cls");
		switch (ch)
		{
		case '1':a.search_by_singer();
			search_by_singer(); system("cls"); break;
		case '2':a.show_search_by_song_name(); search_by_song_name();
			system("cls"); break;
		case '3':a.search_by_abbre(); search_by_abbre(); system("cls"); break;
		case '4':a.show_all_songs(); song_library(); system("cls"); break;
		case '5':
			if (List_in_play.size() == 0)
			{
				system("cls");
				cout << "   播放列表空空如也，快去歌库中添加吧！"; Sleep(1000);
				system("cls");
			}
			else 
			{ 
				bool t = 1;
				for(int i=0;i<List_in_play.size();++i)
				{
					if (List_in_play[i].state == 1) { t = 0; break; }
				}
				if (t) 
				{
					List_in_play[0].state = 1;  x = "Songs//" + List_in_play[0].song_name + ".mp3"; 
					audio.load(x); audio.play();
				}
				 a.show_all_songs(); check_song_play(); system("cls"); 
			}
			break;
		case '6':a.show_recommend(); recommend(); system("cls"); break;
		}
		a.show_user(); ch = _getch();
	}
	audio.stop();
	system("cls");
}
void user::run_()
{
	interact a;
	if (!(login_in_())) return;
	else
	{
		a.show_user_();
		char ch = _getch();
		while (ch != '0')
		{
			system("cls");
			switch (ch)
			{
			case '1':a.search_by_singer();
				search_by_singer(); system("cls"); break;
			case '2':a.show_search_by_song_name(); search_by_song_name();
				system("cls"); break;
			case '3':a.search_by_abbre(); search_by_abbre(); system("cls"); break;
			case '4':a.show_all_songs(); song_library(); system("cls"); break;
			case '5':
				if (List_in_play.size() == 0)
				{
					system("cls");
					cout << "   播放列表空空如也，快去歌库中添加吧！"; Sleep(1000);
					system("cls");
				}
				else 
				{
					bool t = 1;
					for (int i = 0; i < List_in_play.size(); ++i)
					{
						if (List_in_play[i].state == 1) { t = 0; break; }
					}
					if (t)
					{
						List_in_play[0].state = 1; x = "Songs//" + List_in_play[0].song_name + ".mp3";
						audio.load(x); audio.play();
					}
					a.show_all_songs(); check_song_play_(); system("cls");
				}break;
			case '6':
				if (List_liked.size() == 0)
				{
					system("cls");
					cout << "   还没有添加喜欢的歌曲，快去歌库中添加吧！"; Sleep(1000);
					system("cls");
				}
				else { show_love(); system("cls");  }break;
			case '7':a.show_recommend(); recommend(); system("cls"); break;
			}
			a.show_user_(); ch = _getch();
		}
		audio.stop();
		ofstream f(txt_name, ios::trunc);
		for (int i = 0; i < List_liked.size(); ++i)
		{
			f  << endl<< List_liked[i].song_name << '\t' << List_liked[i].singer << '\t' << List_liked[i].abbre;
		}
		f.close();
		system("cls");
	}
}
vector<song_in_library> get_comment(const user *l)
{
	return l->List;
}