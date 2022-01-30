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
struct admission//���ڼ�¼����Ȩ�޼�¼
{
	int num;//��¼����Ȩ����
	vector<string> kids;//��¼������Ȩ�޸���˭��֮��ɵݹ����
};
struct operat//��ʾ��ĳ����Ĳ���Ȩ��
{
	string table_name;//����
	admission powers[4];//����Ȩ�޵ļ�¼:0_drop 1_insert 2_delete 3_select
	bool owner;//�Ƿ�Ϊ����creat
	string table_txtname;//��¼���Ӧ���ļ���
};
class user
{
public:
	string id;
	string key;
	string filename;
	string journalname;
	vector<operat> user_holds;//�û��Ա��Ȩ��
	user(string ID, string keyword) { id = ID; key = keyword; filename = id + ".txt"; journalname = id + "j.txt"; }
	bool login();//��½���ɹ���½�󣬻Ὣuser�����ݰ�����Ӧ�ļ�����Ϣ����_�����ˣ���system������ʱ�����˵���
	void creattable_tofile(string order, vector<user> &xx, int n);//����table���ļ�
	void creattable_fromfile(string order, vector<user> &xx, int n);//���ļ�����table
	void drop(string order, vector<user> &all_users);//ɾ��name�ļ�
	void list();//չʾ�û����ʱ���
	void insert_all(string order, vector<user>& all_users);//��������һ��
	void insert(string order, vector<user>& all_users);//���벻����һ��
	void Delete_part(string order, vector<user>& all_users);//ɾ�����ֱ������
	void Delete_all(string order, vector<user>& all_users);//ɾ�����ȫ�����ݣ�������룬ֱ�Ӹ����ļ�
	void select_part(string order, vector<user>& all_users);//������չʾ
	void select_all(string name, vector<user>& all_users);//չʾ����table
	void select_distinct(string order, vector<user>& all_users);//��ֵͬչʾ
	void select_order(string order, vector<user>& all_users);//����չʾ
	void select_keyword(string order, vector<user>& all_users);//���ؼ���չʾ
	void select_tofile_1(string order, vector<user>& all_users);//filename��Ӧ�������ļ�����ͻ
	void select_tofile_2(string order, vector<user>& all_users);//filename��Ӧ�������ļ�����ͻ
	void select_tofile_3(string order, vector<user>& all_users);
	//���ϲ����������жϵ�ǰ�û��Ƿ�����ӦȨ��
	bool get_data(string name, vector<vector<string>> &x);//���ݶ�ȡ����
	void compare(string order);
};
#endif