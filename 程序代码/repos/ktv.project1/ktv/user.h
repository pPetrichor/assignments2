#ifndef __USER_H
#define __USER_H
#include"interact.h"
#include<fstream>
#pragma once
using namespace std;
struct song_in_library;
class Administrator;
struct song_play
{
	int id;//�������
	string song_name;//����
	string singer;//����
	bool state;//����״̬
	string abbre;//������ƴ��
	int n;//�������
};
class user
{
	vector<song_play> List_in_play;
	vector<song_play> List_liked;//�û��ղظ���
	string id;//�û���¼id
	string keyword;//�û���½����
	string txt_name;//��ϲ���ĸ�洢�ļ���
public:
	string getid()
	{
		return id;
	}
	string getkeyword()
	{
		return keyword;
	}
	string gettxt_name()
	{
		return txt_name;
	}
	user(string Id,string Keyword,string Txt_nmae)
	{
		id = Id;
		keyword = Keyword;
		txt_name = Txt_nmae;
		fstream fin(txt_name);
		if (!fin) { cerr << "���ļ�ʧ��"; Sleep(1000); exit(-1); }
		else
		{
			while (fin.peek()!=EOF)
			{
				song_play a;
				fin >> a.song_name;
				fin >> a.singer;
				fin >> a.abbre;
				a.id = 0; a.n = 0; a.state = 0;
				List_liked.push_back(a);
			}
			fin.close();
		}
	}
	user(){}
	vector<song_in_library> List;//�洢����и���
	void song_library();//��ѯ���и�����Ϣ
	void search_by_song_name();//���������
	void search_by_singer();//���ǵ��
	void search_by_abbre();//��ƴ�����
	void check_song_play();//�鿴�ѵ����
	void check_song_play_();//�鿴�û��ѵ����
	void comment();//�û�����
	friend vector<song_in_library> get_comment(const user *l);//����user::comment(int id)���صķ���������Ӧ�������ֽ��м���,�����ִ�������Ա
	void set_first();//�ö��������û������ţ����ø��ö�
	void delete_song();//�Ƴ��������û������ţ����ø��Ƴ�
	void next();//�и�
	void run();//��������
	void run_();//�û���½�����̿���
	void i_like();//��ӵ���ϲ��
	void recommend();//�����Ƽ�
	bool login_in_();//�û���½
	void show_love();//չʾ��ϲ����
};

#endif
