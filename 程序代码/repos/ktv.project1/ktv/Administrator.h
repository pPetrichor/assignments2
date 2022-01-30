#ifndef __ADMINISTRATOR_H
#define __ADMINISTRATOR_H
#pragma once
#include"interact.h"
using namespace std;
class user;
class interact;
struct song_in_library
{
	int id;//歌曲编号
	string song_name;//歌名
	string singer;//歌手
	double score;//评分
	string abbre;//歌曲名拼音
	int num;//记录评分人数
};
class Administrator
{
	string ID;
	string Keyword;
	vector<song_in_library> List_in_library;
public:
	
	Administrator(const char*s);
	bool judge_ID(string s);//判断ID、密码合法性
	bool judge_Keyword(string s);//判断ID、密码合法性
	friend vector<song_in_library> visit_library(const Administrator *a);//返回List_in_library
	bool login_in();//管理员登陆
	bool Keyword_change();//管理员密码修改
	void song_library();//查询所有歌曲信息
	void add_song();//添加歌曲
	void bulk_add();//批量导入歌曲
	void delete_song();//删除歌曲+重新编号
	void sort_library();//歌曲排序
	void get_comment(const user *l);//更新歌库中评分
	void Run(bool &log);//控制流程
};
#endif 

