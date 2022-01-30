#include"Administrator.h"
#include"user.h"
#include<fstream>
Administrator::Administrator(const char*s)//��ʼ�����
{
	ID = "whl"; Keyword = "csSY1";
	fstream fin(s);
	if (!fin) { cerr << "���ļ�ʧ��"; Sleep(1000); exit(-1); }
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
bool Administrator::judge_ID(string s)//�ж�ID�Ϸ���
{
	unsigned int n = s.size();
	if (n > 20) return 0;
	for(int i=0;i<n;++i)
	{
		if (!((s[i] >= 'A'&&s[i] <= 'Z')|| (s[i] >= 'a'&&s[i] <= 'z')|| (s[i] >= '0'&&s[i] <= '9'))) return 0;
	}
	return 1;
}
bool Administrator::judge_Keyword(string s)//�ж�����Ϸ���
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
bool Administrator::login_in()//����Ա��½
{
	int x = 3;//�������������
	while (x > 0)
	{
		x--;
		if (x == 2) cout << "����������ID��"; else cout << "   ����������ID��";
		string ID_get;
		cin >> ID_get;
		cout << "   ��������������:";
		string Keyword_get; char ch; ch = _getch(); Keyword_get += ch;
		while (ch != '\n'&&ch != '\r')
		{
			cout << "*";
			ch = _getch();
			if (ch != '\n'&&ch != '\r') Keyword_get += ch;
		}
		cout << endl;
		if(!judge_ID(ID_get)) cout<<"   ID���Ϸ�,���������루ʣ�����:" << x << ")" << endl;
		if (!judge_Keyword(Keyword_get)) cout << "   ���벻�Ϸ�,���������루ʣ�����:" << x << ")" << endl;
		if (ID == ID_get && Keyword == Keyword_get) { cout << "   " << ID << "    ��ӭ��½!����Ϊ����ת����"; Sleep(1000); return 1; }
		else if (ID != ID_get) cout << "   δ�ҵ����û�ID�����������루ʣ�����:" << x << ")" << endl;
		else cout << "   ����������������루ʣ�����:" << x << ")" << endl;
		Sleep(1000);
	}
	cout << "   ��½ʧ�ܣ�������½ϵͳ!"; Sleep(1000);
	system("cls");
	return 0;
}
bool Administrator::Keyword_change()//����Ա�����޸�
{
	string old_Keyword, new_Keyword1, new_Keyword2;
	cout << "�����뵱ǰ���룺"; cin >> old_Keyword;
	cout << "   �������޸ĺ�����(������12���ַ�������ͬʱ������Сд��ĸ������)��"; cin >> new_Keyword1;
	cout << "   ��ȷ���޸ĺ����룺"; cin >> new_Keyword2;
	if (Keyword != old_Keyword) { cout << "   ������������޸�ʧ�ܣ�"; Sleep(1000); return 0; }
	if(new_Keyword1!= new_Keyword2) { cout << "   �޸ĺ��������벻һ�£��޸�ʧ�ܣ�"; Sleep(1000); return 0; }
	if (Keyword == new_Keyword1) { cout << "   ����δ�����ı䣬�޸�ʧ�ܣ�"; Sleep(1000); return 0; }
	if(!judge_Keyword(new_Keyword1)) { cout << "   ���벻�Ϸ�������������趨���޸�ʧ�ܣ�"; Sleep(1000); return 0; }
	Keyword = new_Keyword1;
	cout << "�޸ĳɹ���"; Sleep(1000); return 1;
}
void Administrator::song_library()//��ѯ���и�����Ϣ
{
	interact a; int n = List_in_library.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch!=27)//27ΪESC��
	{
		l = 2; a.show_all_songs();
		for (int t = 0; t < 10&&i<n; ++t)
		{
			a.gotoxy(7, l); cout << List_in_library[i].id;
			a.gotoxy(24, l); cout << List_in_library[i].song_name;
			a.gotoxy(45, l); cout << List_in_library[i].singer; ++i; ++l;//��ӡ������Ϣ
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
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
void Administrator::add_song()//��Ӹ���
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
			cout << "   ������Ϊ����ӵ���⣬����գ�" << endl;
		}
		else if (!flag&&a.abbre != List_in_library[i].abbre) cout << "   �����Ѵ��ڣ���ƴ����д��һ�£��������������" << endl;
		else cout << "   �����Ѵ��ڣ����ʧ�ܡ�" << endl;
		cout << "   ��������Լ�����ӣ�����ESC����������." << endl;
}
void Administrator::bulk_add()//�����������
{
	string name_txt;
	cin >> name_txt;
	if (name_txt == "1") return;
	int succeed = 0; int fail = 0; int all = 0;
	fstream fin(name_txt);
	if (!fin) { cerr << "   ���ļ�ʧ��"; Sleep(1000); exit(-1); }
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
		cout << "   �������!������" << all << "�׸���" << endl << "   ���е���ɹ�" << succeed << "��" << ",ʧ��" << fail << "�ס�" << endl << "   ԭ�򣺸�����Ѵ���" << endl;
		Sleep(1000);
}
void Administrator::delete_song()//ɾ������+���±��
{
	interact a; int n = List_in_library.size(); int i = 0; int k = 1;
	int page = 0; char ch = 0;
	if (n / 10 == 0) page = n / 10; else page = n / 10 + 1; int l;
	while (ch != 27)//27ΪESC��
	{
		l = 2; a.show_delete_song();
		for (int t = 0; t < 10 && i < n; ++t)
		{
			a.gotoxy(7, l); cout << List_in_library[i].id;
			a.gotoxy(24, l); cout << List_in_library[i].song_name;
			a.gotoxy(45, l); cout << List_in_library[i].singer; ++i; ++l;//��ӡ������Ϣ
		}
		a.gotoxy(0, 12);
		cout << "-------------------------------------------------------------------" << endl;
		cout << "��" << k << "ҳ����" << page << "ҳ����һҳ��w������һҳ��s��,����ESC������ҳ";
		cout << endl << endl << "   ����0�Խ���ɾ������" << endl;
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
			cout << "   ������Ҫɾ���ĸ����ı�ţ�����0�Խ���ɾ����";
			int kill = 0; cin >> kill;
			if (kill == 0) { cout << "���ڷ��������桭��"; Sleep(2000); return; }
			else if (kill < 0 || kill>List_in_library.size()) { cout << "   �����ڴ˱�Ÿ��������������"; i = 0; Sleep(500); system("cls"); }
			else
			{
				cout << "   ȷ��ɾ���𣿣�y/n��";
				char c = _getch();
				while (1)
				{
					if (c == 'y')
					{
						List_in_library.erase(List_in_library.begin() + kill - 1);
						for (int i = 0; i < List_in_library.size(); ++i)
							List_in_library[i].id = i + 1;
						cout << "   ɾ���ɹ���"; Sleep(2000); system("cls"); i = 0; n--;
						break;
					}
					else if (c == 'n') { cout << "   ɾ��ʧ�ܣ�"; Sleep(2000); system("cls"); i = 0; break; }
					else c = _getch();
				}
			}
			break;
		}
		}
	}
}
void Administrator::sort_library()//��������
{
	cout << "��ѡ������ʽ��" << endl << "�������ţ�����1��" << endl << "�����������ţ�����2��" << endl << "���������棨����0��";
	char x = _getch();
	if(x=='1')
	{
		system("cls");
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.score > y.score; });
		interact a; int n = List_in_library.size(); int i = 0; int k = 1;
		int page = 0; char ch = 0;
		if (n / 10 == 0 && n != 0) page = n / 10; else page = n / 10 + 1; int l;
		a.show_sort();
		while (ch != 27)//27ΪESC��
		{
			l = 2; a.show_sort();
			for (int t = 0; t < 10 && i < n; ++t)
			{
				a.gotoxy(7, l); cout << List_in_library[i].score;
				a.gotoxy(24, l); cout << List_in_library[i].id;
				a.gotoxy(45, l); cout << List_in_library[i].song_name;
				a.gotoxy(66, l); cout << List_in_library[i].singer; ++i; ++l;//��ӡ������Ϣ
			}
			a.gotoxy(0, 12);
			cout << "------------------------------------------------------------" << endl;
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
		while (ch != 27)//27ΪESC��
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
				//��ӡ������Ϣ
			}
			a.gotoxy(0, 12);
			cout << "----------------------------------------------------------------------" << endl;
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
		sort(List_in_library.begin(), List_in_library.end(), [](song_in_library x, song_in_library y)->bool {return x.id < y.id; });
	}
	if (x == 0) { cout << "������������"; Sleep(1000); return; }
}
void Administrator::get_comment(const user *l)//���¸��������
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