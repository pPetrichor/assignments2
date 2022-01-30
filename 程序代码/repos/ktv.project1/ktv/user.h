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
	int id;//歌曲编号
	string song_name;//歌名
	string singer;//歌手
	bool state;//播放状态
	string abbre;//歌曲名拼音
	int n;//歌曲序号
};
class user
{
	vector<song_play> List_in_play;
	vector<song_play> List_liked;//用户收藏歌曲
	string id;//用户登录id
	string keyword;//用户登陆密码
	string txt_name;//我喜欢的歌存储文件名
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
		if (!fin) { cerr << "打开文件失败"; Sleep(1000); exit(-1); }
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
	vector<song_in_library> List;//存储歌库中歌曲
	void song_library();//查询所有歌曲信息
	void search_by_song_name();//歌曲名点歌
	void search_by_singer();//歌星点歌
	void search_by_abbre();//首拼音点歌
	void check_song_play();//查看已点歌曲
	void check_song_play_();//查看用户已点歌曲
	void comment();//用户评分
	friend vector<song_in_library> get_comment(const user *l);//接受user::comment(int id)传回的分数，对相应歌曲评分进行计算,将评分传给管理员
	void set_first();//置顶歌曲：用户输入编号，将该歌置顶
	void delete_song();//移除歌曲：用户输入编号，将该歌移除
	void next();//切歌
	void run();//控制流程
	void run_();//用户登陆后流程控制
	void i_like();//添加到我喜欢
	void recommend();//歌曲推荐
	bool login_in_();//用户登陆
	void show_love();//展示我喜欢的
};

#endif
