#ifndef __ADMINISTRATOR_H
#define __ADMINISTRATOR_H
#pragma once
#include"interact.h"
using namespace std;
class user;
class interact;
struct song_in_library
{
	int id;//�������
	string song_name;//����
	string singer;//����
	double score;//����
	string abbre;//������ƴ��
	int num;//��¼��������
};
class Administrator
{
	string ID;
	string Keyword;
	vector<song_in_library> List_in_library;
public:
	
	Administrator(const char*s);
	bool judge_ID(string s);//�ж�ID������Ϸ���
	bool judge_Keyword(string s);//�ж�ID������Ϸ���
	friend vector<song_in_library> visit_library(const Administrator *a);//����List_in_library
	bool login_in();//����Ա��½
	bool Keyword_change();//����Ա�����޸�
	void song_library();//��ѯ���и�����Ϣ
	void add_song();//��Ӹ���
	void bulk_add();//�����������
	void delete_song();//ɾ������+���±��
	void sort_library();//��������
	void get_comment(const user *l);//���¸��������
	void Run(bool &log);//��������
};
#endif 

