#ifndef _SYSTEM___H
#define _SYSTEM___H
#include"user.h"
class system_
{
	vector<user> all_users;
public:
	system_()//��users.txt��ÿһ���û����ļ�����������Ϣ����
	{
		fstream fin("users.txt");
		if (!fin) { cerr << "   ���ļ�ʧ��" << endl; }
		else
		{
			string id, key;
			while (fin >> id >> key)
			{
				user user_(id, key);
				fstream fi(user_.filename);
				if (!fi) { cerr << "   ���ļ�ʧ��" << endl; }
				else
				{
					while (fi)
					{
						operat x;
						fi >> x.table_txtname >> x.table_name;
						fi >> x.powers[0].num >> x.powers[1].num >> x.powers[2].num >> x.powers[3].num;
						fi >> x.owner;
						string u; fi >> u;
						if (!fi) break;
						while (u != "#")
						{
							x.powers[0].kids.push_back(u); fi >> u;
						}
						fi >> u;
						while (u != "#")
						{
							x.powers[1].kids.push_back(u); fi >> u;
						}
						fi >> u;
						while (u != "#")
						{
							x.powers[2].kids.push_back(u); fi >> u;
						}
						fi >> u;
						while (u != "#")
						{
							x.powers[3].kids.push_back(u); fi >> u;
						}
						user_.user_holds.push_back(x);
					}
					all_users.push_back(user_);
				}
				
			}
		}
	}
	int analysis(string order);//�����н�������,����һ�У�����������Ϊ�������
	void run();//���̿��ƺ���
	void grant(int giver, string order);
	void revoke(int giver, string order);
	void REVOKE(admission &a, string kill, int x, int n);
};
#endif // !_SYSTEM__H

