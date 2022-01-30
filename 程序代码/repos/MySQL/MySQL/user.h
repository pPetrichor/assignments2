#ifndef _USER__H
#define _USER__H
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<time.h>
#include<cstdio>
#pragma once
using namespace std;
struct admission//用于记录授予权限记录
{
	int num;//记录被授权次数
	vector<string> kids;//记录将此项权限给了谁，之后可递归操作
};
struct operat//表示对某个表的操作权限
{
	string table_name;//表名
	admission powers[4];//四项权限的记录:0_drop 1_insert 2_delete 3_select
	bool owner;//是否为本人creat
	string table_txtname;//记录表对应的文件名
};
class user
{
public:
	string id;
	string key;
	string filename;
	string journalname;
	vector<operat> user_holds;//用户对表的权限
	user(string ID, string keyword) { id = ID; key = keyword; filename = id + ".txt"; journalname = id + "j.txt"; }
	bool login();//登陆：成功登陆后，会将user中内容按照相应文件中信息更新_不必了，在system对象定义时进行了导入
	void creattable_tofile(string order, vector<user> &xx, int n);//创建table与文件
	void creattable_fromfile(string order, vector<user> &xx, int n);//从文件创建table
	void drop(string order, vector<user> &all_users);//删除name文件
	void list();//展示用户访问表集合
	void insert_all(string order, vector<user>& all_users);//插入完整一行
	void insert(string order, vector<user>& all_users);//插入不完整一行
	void Delete_part(string order, vector<user>& all_users);//删除部分表格内容
	void Delete_all(string order, vector<user>& all_users);//删除表格全部内容：无需读入，直接更改文件
	void select_part(string order, vector<user>& all_users);//若干列展示
	void select_all(string name, vector<user>& all_users);//展示整个table
	void select_distinct(string order, vector<user>& all_users);//不同值展示
	void select_order(string order, vector<user>& all_users);//按序展示
	void select_keyword(string order, vector<user>& all_users);//按关键词展示
	void select_tofile_1(string order, vector<user>& all_users);//filename不应与已有文件名冲突
	void select_tofile_2(string order, vector<user>& all_users);//filename不应与已有文件名冲突
	void select_tofile_3(string order, vector<user>& all_users);
	//以上操作均会先判断当前用户是否有相应权限
	bool get_data(string name, vector<vector<string>> &x);//数据读取函数
	void compare(string order);
};
#endif