#ifndef __INTERACT_H
#define __INTERRACT_H
#pragma once
#include<iostream>
#include <conio.h>
#include <windows.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
class interact
{
public:
	void gotoxy(int x, int y)//�ƶ����
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(handle, pos);
	}
	void show_first();//���������
	void show_Administrator();//�������Աѡ�����
	void show_login();//�����½����
	void show_all_songs();//�鿴���и�������
	void show_add_song();//�����Ӹ�������
	void show_bulk_add();//��������������
	void show_delete_song();//���ɾ����������
	void show_sort();//�������
	void show_sort2();
	void show_user();//����û�ѡ�����
	void show_Keyword_change();//��������޸Ľ���
	void show_search_by_song_name();//�������������
	void search_by_singer();//���ǵ�����
	void search_by_abbre();//��ƴ��������
	void show_comment();//�û�����
	void show_set_first();//�ö�����
	void show_delete_song_in_play();
	void show_login_();//�û���½
	void show_user_();//�û���½�����
	void show_add_to_love();//��ӵ���ϲ��
	void show_recommend();
	void show_new();//ע�����
};
#endif
