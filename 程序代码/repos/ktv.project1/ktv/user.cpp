#include"user.h"
#include"Administrator.h"
#include"AudioClip.h"
AudioClip audio; string x;
void user::song_library()//��ѯ���и�����Ϣ
{
	interact a; int n = List.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27ΪESC��
	{
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List[i].id;
			a.gotoxy(24, l); cout << List[i].song_name;
			a.gotoxy(45, l); cout << List[i].singer; ++i; ++l;//��ӡ������Ϣ
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
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
void user::show_love()//��ѯ��ϲ������Ϣ
{
	interact a; int n = List_liked.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27ΪESC��
	{
		l = 2; 
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List_liked[i].song_name;
			a.gotoxy(24, l);  cout << List_liked[i].singer;
			a.gotoxy(45, l); cout << List_liked[i].abbre; ++i; ++l;//��ӡ������Ϣ
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
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
	cout << "   ��������������:";
	string Keyword_get; char ch; ch = _getch(); Keyword_get += ch;
	while (ch != '\n'&&ch != '\r')
	{
		cout << "*";
		ch = _getch();
		if (ch != '\n'&&ch != '\r') Keyword_get += ch;
	}
	cout << endl;
	if (keyword == Keyword_get) { cout << "   " << id << "    ��ӭ��½!����Ϊ����ת����"; Sleep(1000); system("cls"); return 1; }
	else { cout << "   ��½ʧ�ܣ�"; Sleep(1000); system("cls"); return 0; }
}
void user::search_by_song_name()//���������,���������Ӹ������ʱ������������ĸ
{
	cout << "   ������Ҫ���ҵĸ�����������1���������棨��ģ�����ң�:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   ���ڷ��ء���"; Sleep(500); return; }
	for(int i=0;i<List.size();++i)
	{
		if (List[i].song_name.find(name) != string::npos)
		{
			cout << "   " << List[i].id <<'\t'<< List[i].song_name <<'\t'<< List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   ����в��Ҳ������׸裬���Ա�ĸ�����(������) ����Ϊ��������ҳ����"; Sleep(2000); return; }
	cout << "   ��������ӵ��б�ĸ�����ţ�����0������";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   ����в��Ҳ����ñ�Ÿ��������Ա�ĸ�����(������)" << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
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
					cout << "   �����ѳɹ���ӵ������б�" << endl;
				}
				else
				{
					cout << "   ���ʧ�ܣ�ԭ�򣺸ø������ڲ����б���" << endl;
				}
			}
			else cout << "   ����������ƺ�û�����׸�o_o ...." << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
		}
	}
	cout << "   ����������ȥ�赥������O(��_��)O"; Sleep(1000); system("cls");
}
void user::search_by_singer()//���ǵ��
{
	cout << "   ������Ҫ���ҵĸ�����������1����������:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   ���ڷ��ء���"; Sleep(500); return; }
	for (int i = 0; i < List.size(); ++i)
	{
		if (List[i].singer.find(name) != string::npos)
		{
			cout << "   " << List[i].id << '\t' << List[i].song_name << '\t' << List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   ����в��Ҳ����ø�����Ʒ�����Ա�ĸ�����(������) ����Ϊ��������ҳ����"; Sleep(2000); return; }
	cout << "   ��������ӵ��б�ĸ�����ţ�����0������";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{ 
			cout << "   ����в��Ҳ����ñ�Ÿ��������Ա�ĸ�����(������)" << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
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
					cout << "   �����ѳɹ���ӵ������б�" << endl;
				}
				else
				{
					cout << "   ���ʧ�ܣ�ԭ�򣺸ø������ڲ����б���" << endl;
				}
			}
			else cout << "   ����������ƺ�û�����׸�o_o ...." << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
		}
	}
	cout << "   ����������ȥ�赥������O(��_��)O"; Sleep(1000); system("cls");
}
void user::search_by_abbre()//��ƴ�����
{
	cout << "   ������Ҫ���ҵĸ���ƴ��������1����������:";
	string name; cin >> name;
	int rem[10] = { 0 }; int r = 0;
	if (name == "1") { cout << "   ���ڷ��ء���"; Sleep(500); return; }
	for (int i = 0; i < List.size(); ++i)
	{
		if (List[i].abbre.find(name) != string::npos)
		{
			cout << "   " << List[i].id << '\t' << List[i].song_name << '\t' << List[i].singer << endl;
			rem[r] = List[i].id; ++r;
		}
	}
	if (r == 0) { cout << "   ����в��Ҳ������׸裬���Ա�ĸ�����(������) ����Ϊ��������ҳ����"; Sleep(2000); return; }
	cout << "   ��������ӵ��б�ĸ�����ţ�����0������";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   ����в��Ҳ����ñ�Ÿ��������Ա�ĸ�����(������)" << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
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
					cout << "   �����ѳɹ���ӵ������б�" << endl;
				}
				else
				{
					cout << "   ���ʧ�ܣ�ԭ�򣺸ø������ڲ����б���" << endl;
				}
			}
			else cout << "   ����������ƺ�û�����׸�o_o ...." << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
		}
	}
	cout << "   ����������ȥ�赥������O(��_��)O"; Sleep(1000); system("cls");
}
void user::check_song_play()//�鿴�ѵ����
{
	interact a; int n = List_in_play.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27ΪESC��
	{
		n = List_in_play.size();
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n&&i>=0; ++t)
		{
			if (List_in_play[i].state)
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer<<"�������ڲ���"; ++i; ++l;//��ӡ������Ϣ
			}
			else
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer; ++i; ++l;//��ӡ������Ϣ 
			}
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
		cout << endl << endl << "   ����1-->�ö�����" << endl << "   ����2-->�Ƴ�����" << endl << "   ����3-->�и�" << endl << "   ����0-->��������" << endl;
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
void user::check_song_play_()//�鿴�û��ѵ����
{
	interact a; int n = List_in_play.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27ΪESC��
	{
		n = List_in_play.size();
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			if (List_in_play[i].state)
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer << "�������ڲ���"; ++i; ++l;//��ӡ������Ϣ
			}
			else
			{
				a.gotoxy(7, l); cout << List_in_play[i].n;
				a.gotoxy(24, l); cout << List_in_play[i].song_name;
				a.gotoxy(45, l); cout << List_in_play[i].singer; ++i; ++l;//��ӡ������Ϣ 
			}
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
		cout << endl << endl << "   ����1-->�ö�����" << endl << "   ����2-->�Ƴ�����" << endl << "   ����3-->�и�" << endl << "   ����4-->��ӵ���ϲ����" << endl << "   ����0-->��������" << endl;
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
void user::comment()//�û�����
{
	interact a;
		int judgement; cin >> judgement;
		if (judgement <= 0 || judgement > List_in_play.size()) { cout << "   δ�ڲ����б����ҵ��ø����i�n�i..."; Sleep(1000); }
		else
		{
			cout << "   �������������֣�1��5����";
			int score_get; cin >> score_get;
			if (score_get < 1 || score_get > 5) { cout << "   �ݲ��ṩ�÷�ֵ������������" << endl; Sleep(1000); }
			else
			{
				int number = List_in_play[judgement - 1].id;
				List[number - 1].score = (List[number - 1].score*List[number - 1].num + score_get) / (List[number - 1].num + 1);
				List[number - 1].num++;
				cout << "   ���ֳɹ�����л���ķ��������ǻ�Ŭ�����ø���^_^";
				Sleep(1000);
			}
		}
}
void user::set_first()//�ö��������û������ţ����ø��ö�,0����
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   �����ڸñ�Ÿ�����"; Sleep(500); return; }
	
	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{
		cout << endl << "   ȷ�����˸��ö���(y/n)";ch = _getch();
		if (ch == 'y')
		{
			
			song_play temp = List_in_play[n - 1];
			List_in_play[n - 1] = List_in_play[0];
			List_in_play[0] = temp;
			for(int i=0;i<List_in_play.size();++i)
			{
				List_in_play[i].n = i + 1;
			}
			cout << endl << "   �ö��ɹ���"; Sleep(500);
		}
		else if (ch == 'n') return;
	}
}
void user::i_like()//��ӵ���ϲ��
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   �����ڸñ�Ÿ�����"; Sleep(500); return; }

	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{
		cout << endl << "   ȷ�����˸���ӵ���ϲ����(y/n)"; ch = _getch();
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
				cout << endl << "   ��ӳɹ���"; Sleep(500);
			}
			else
			{
				cout << endl << "   ���ʧ�ܣ�ԭ����ϲ���������д˸�����"; Sleep(500);
			}
		}
		else if (ch == 'n') return;
	}
}
void user::delete_song()//�Ƴ��������û������ţ����ø��Ƴ�
{
	int n; cin >> n;
	if (n == 0) return;
	if (n < 0 || n > List_in_play.size()) { cout << "   �����ڸñ�Ÿ�����"; Sleep(500); return; }
	
	char ch = '0';
	while (ch != 'y'&&ch != 'n')
	{	cout << endl << "   ȷ�����˸��Ƴ���(y/n)";
		ch = _getch();
		if (ch == 'y')
		{
			if(List_in_play[n-1].state==1)
			{
				List_in_play.erase(List_in_play.begin() + n - 1);
				audio.stop();  x = "Songs//" + List_in_play[0].song_name + ".mp3";
				audio.load(x); audio.play();
				List_in_play[0].state = 1;
			}//�Ƴ������ڲ�����ص���һ��
			else List_in_play.erase(List_in_play.begin() + n - 1);
			for (int i = 0; i < List_in_play.size(); ++i)
			{
				List_in_play[i].n = i + 1;
			}
			cout << "   ɾ���ɹ���"; Sleep(1000);
		}
		else if (ch == 'n') return;
	}
}
void user::next()//�и�
{
	if (List_in_play.size() == 0)
	{
		cout << "   �����б��ѿգ�ȥ�������Ӽ��װ�*^____^*"; Sleep(1000); return;
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
		}//���һ���и�ص���һ��
		for (int i = 0; i < List_in_play.size(); ++i)
		{
			List_in_play[i].n = i + 1;
		}
	}
	cout << "   �и�ɹ���";
}
void user::recommend()//�����Ƽ�
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
	cout << "   ��������ӵ��б�ĸ�����ţ�����0������";
	int n; cin >> n;
	while (n != 0)
	{
		if (n<0 || n>List.size())
		{
			cout << "   ����в��Ҳ����ñ�Ÿ��������Ա�ĸ�����(������)" << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
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
					cout << "   �����ѳɹ���ӵ������б�" << endl;
				}
				else cout<< "   ���ʧ�ܣ��б������д˸�����" << endl;
			}
			else cout << "   ����������ƺ�û�����׸�o_o ...." << endl;
			cout << "   ��������ӵ��б�ĸ�����ţ�����0������"; cin >> n;
		}
	}
	cout << "   ��Ӹ�����������ȥ�赥������O(��_��)O"; Sleep(1000); system("cls");
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
				cout << "   �����б�տ���Ҳ����ȥ�������Ӱɣ�"; Sleep(1000);
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
					cout << "   �����б�տ���Ҳ����ȥ�������Ӱɣ�"; Sleep(1000);
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
					cout << "   ��û�����ϲ���ĸ�������ȥ�������Ӱɣ�"; Sleep(1000);
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