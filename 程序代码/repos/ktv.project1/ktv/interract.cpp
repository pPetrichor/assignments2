#include"interact.h"
void interact::show_first()//���������
{
	gotoxy(10, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  �οͷ���";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  ����Աֱ��";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  �û���¼";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  �û�ע��";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "0.  �˳�ϵͳ";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14);
	for (int i = 0; i < t; ++i) cout << "��_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-��";
	cout << endl;
	cout << "   ����������ѡ��:";
}
void interact::show_Administrator()//�������Աѡ�����
{
	gotoxy(10, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  ���и���";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  ��Ӹ���";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  �����������";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  ɾ������";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  ��������";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  �޸�����";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "0.  ��  ��";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18);
	for (int i = 0; i < t; ++i) cout << "��_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-��";
	cout << endl;
	cout << "   ����������ѡ��:";
}
void interact::show_login()//�����½����
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "����Ա��½";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4);
}
void interact::show_login_()//����û���½����
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�û���½";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
}
void interact::show_all_songs()//�鿴���и�������
{
	gotoxy(5, 0); cout << "���";
	gotoxy(25, 0); cout << "������";
	gotoxy(45, 0); cout << "������";
	gotoxy(0, 1); cout << "-------------------------------------------------------------------"; 
}
void interact::show_sort()//����������
{
	gotoxy(5, 0); cout << "�����÷�";
	gotoxy(25, 0); cout << "���";
	gotoxy(45, 0); cout << "������";
	gotoxy(65, 0); cout << "������";
	gotoxy(0, 1); cout << "-----------------------------------------------------------------------------";
}
void interact::show_sort2()//����������
{
	gotoxy(5, 0); cout << "�����÷�";
	gotoxy(25, 0); cout << "���";
	gotoxy(45, 0); cout << "������";
	gotoxy(65, 0); cout << "������";
	gotoxy(85, 0); cout << "��������";
	gotoxy(0, 1); cout << "---------------------------------------------------------------------------------------";
}
void interact::show_add_song()//�����Ӹ�������
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�������";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4);
	cout << "�����룺" << endl;
	gotoxy(3, 5); cout << "����  ����  ƴ��"; gotoxy(3, 6);
}
void interact::show_bulk_add()//��������������
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "��������";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4);
	cout << "�����뵼����ļ���������1������ҳ" << endl;
	gotoxy(3, 5);
}
void interact::show_delete_song()//���ɾ����������
{
	gotoxy(5, 0); cout << "���";
	gotoxy(25, 0); cout << "������";
	gotoxy(45, 0); cout << "������";
	gotoxy(0, 1); cout << "-------------------------------------------------------------------";
}
void interact::show_Keyword_change()//��������޸Ľ���
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�����޸�";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4);
}
void interact::show_user()//����ο�ѡ�����
{
	gotoxy(10, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  ���ֵ��";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  ��������";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  ƴ�����";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  ���и���";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  �ѵ����";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  �����Ƽ�";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "0.  �˳�";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18);
	for (int i = 0; i < t; ++i) cout << "��_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-��";
	cout << endl;
	cout << "   ����������ѡ��:";
}
void interact::show_user_()//����û�ѡ�����
{
	gotoxy(10, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  ���ֵ��";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  ��������";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  ƴ�����";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  ���и���";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  �ѵ����";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  ��ϲ����";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "7.  �����Ƽ�";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18); cout << "*";
	gotoxy(12, 18); cout << "0.  �˳�";
	gotoxy(35, 18); cout << "*" << endl;
	gotoxy(3, 20);
	for (int i = 0; i < t; ++i) cout << "��_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-��";
	cout << endl;
	cout << "   ����������ѡ��:";
}

void interact::show_search_by_song_name()//�������������
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "��������";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
}
void interact::search_by_singer()//���ǵ�����
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "���ֵ��";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
}
void interact::search_by_abbre()//��ƴ��������
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "ƴ�����";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
}
void interact::show_recommend()//�����Ƽ�����
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�����Ƽ�����������";
	for (int i = 0; i < t; ++i) cout << "��-";
	gotoxy(3, 2); cout << "��������" << '\t' << "������" << '\t'<<'\t' << "������";
	gotoxy(0, 3); cout << "-------------------------------------------------------------------";
	cout << endl;
}
void interact::show_comment()//���ֽ���,��ESC�˳���������
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "��������";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	cout << "   ������Ҫ���������ı�ţ�";
}
void interact::show_set_first()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�����ö�";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	cout << "   ������Ҫ�ö������ı�ţ�����0�˳�����";
}
void interact::show_delete_song_in_play()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "����ɾ��";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	cout << "   ������Ҫɾ�������ı�ţ�����0�˳�����";
}
void interact::show_add_to_love()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�����ղ�";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	cout << "   ������Ҫ��ӵ���ϲ���ĸ�����ţ�����0�˳�����";
}
void interact::show_new()
{
	gotoxy(14, 0);
	cout << "$��ӭʹ��KTV���ϵͳ$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_��";
	cout << "�û�ע��";
	for (int i = 0; i < t; ++i) cout << "��-";
	cout << endl;
	cout << "   �����������õ�ID��";
}