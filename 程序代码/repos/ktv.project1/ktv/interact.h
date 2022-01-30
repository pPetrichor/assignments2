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
	void gotoxy(int x, int y)//移动光标
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(handle, pos);
	}
	void show_first();//输出主界面
	void show_Administrator();//输出管理员选择界面
	void show_login();//输出登陆界面
	void show_all_songs();//查看所有歌曲界面
	void show_add_song();//输出添加歌曲界面
	void show_bulk_add();//输出导入歌曲界面
	void show_delete_song();//输出删除歌曲界面
	void show_sort();//排序界面
	void show_sort2();
	void show_user();//输出用户选择界面
	void show_Keyword_change();//输出密码修改界面
	void show_search_by_song_name();//输出歌名点歌界面
	void search_by_singer();//歌星点歌界面
	void search_by_abbre();//首拼音点歌界面
	void show_comment();//用户评分
	void show_set_first();//置顶界面
	void show_delete_song_in_play();
	void show_login_();//用户登陆
	void show_user_();//用户登陆后界面
	void show_add_to_love();//添加到我喜欢
	void show_recommend();
	void show_new();//注册界面
};
#endif
