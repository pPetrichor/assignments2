#include"interact.h"
void interact::show_first()//输出主界面
{
	gotoxy(10, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  游客访问";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  管理员直达";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  用户登录";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  用户注册";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "0.  退出系统";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14);
	for (int i = 0; i < t; ++i) cout << "⊙_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-≈";
	cout << endl;
	cout << "   请输入您的选择:";
}
void interact::show_Administrator()//输出管理员选择界面
{
	gotoxy(10, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  所有歌曲";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  添加歌曲";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  批量导入歌曲";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  删除歌曲";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  歌曲排序";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  修改密码";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "0.  退  出";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18);
	for (int i = 0; i < t; ++i) cout << "⊙_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-≈";
	cout << endl;
	cout << "   请输入您的选择:";
}
void interact::show_login()//输出登陆界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "管理员登陆";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4);
}
void interact::show_login_()//输出用户登陆界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "用户登陆";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
}
void interact::show_all_songs()//查看所有歌曲界面
{
	gotoxy(5, 0); cout << "编号";
	gotoxy(25, 0); cout << "歌曲名";
	gotoxy(45, 0); cout << "歌手名";
	gotoxy(0, 1); cout << "-------------------------------------------------------------------"; 
}
void interact::show_sort()//输出排序界面
{
	gotoxy(5, 0); cout << "歌曲得分";
	gotoxy(25, 0); cout << "编号";
	gotoxy(45, 0); cout << "歌曲名";
	gotoxy(65, 0); cout << "歌手名";
	gotoxy(0, 1); cout << "-----------------------------------------------------------------------------";
}
void interact::show_sort2()//输出排序界面
{
	gotoxy(5, 0); cout << "歌曲得分";
	gotoxy(25, 0); cout << "编号";
	gotoxy(45, 0); cout << "歌曲名";
	gotoxy(65, 0); cout << "歌手名";
	gotoxy(85, 0); cout << "评分人数";
	gotoxy(0, 1); cout << "---------------------------------------------------------------------------------------";
}
void interact::show_add_song()//输出添加歌曲界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲添加";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4);
	cout << "请输入：" << endl;
	gotoxy(3, 5); cout << "歌名  歌手  拼音"; gotoxy(3, 6);
}
void interact::show_bulk_add()//输出导入歌曲界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲导入";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4);
	cout << "请输入导入的文件名，输入1返回主页" << endl;
	gotoxy(3, 5);
}
void interact::show_delete_song()//输出删除歌曲界面
{
	gotoxy(5, 0); cout << "编号";
	gotoxy(25, 0); cout << "歌曲名";
	gotoxy(45, 0); cout << "歌手名";
	gotoxy(0, 1); cout << "-------------------------------------------------------------------";
}
void interact::show_Keyword_change()//输出密码修改界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "密码修改";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4);
}
void interact::show_user()//输出游客选择界面
{
	gotoxy(10, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  歌手点歌";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  歌曲搜索";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  拼音点歌";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  所有歌曲";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  已点歌曲";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  歌曲推荐";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "0.  退出";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18);
	for (int i = 0; i < t; ++i) cout << "⊙_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-≈";
	cout << endl;
	cout << "   请输入您的选择:";
}
void interact::show_user_()//输出用户选择界面
{
	gotoxy(10, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 11;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << endl;
	gotoxy(3, 2);
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	gotoxy(3, 4); cout << "*";
	gotoxy(12, 4); cout << "1.  歌手点歌";
	gotoxy(35, 4); cout << "*" << endl;
	gotoxy(3, 6); cout << "*";
	gotoxy(12, 6); cout << "2.  歌曲搜索";
	gotoxy(35, 6); cout << "*" << endl;
	gotoxy(3, 8); cout << "*";
	gotoxy(12, 8); cout << "3.  拼音点歌";
	gotoxy(35, 8); cout << "*" << endl;
	gotoxy(3, 10); cout << "*";
	gotoxy(12, 10); cout << "4.  所有歌曲";
	gotoxy(35, 10); cout << "*" << endl;
	gotoxy(3, 12); cout << "*";
	gotoxy(12, 12); cout << "5.  已点歌曲";
	gotoxy(35, 12); cout << "*" << endl;
	gotoxy(3, 14); cout << "*";
	gotoxy(12, 14); cout << "6.  我喜欢的";
	gotoxy(35, 14); cout << "*" << endl;
	gotoxy(3, 16); cout << "*";
	gotoxy(12, 16); cout << "7.  歌曲推荐";
	gotoxy(35, 16); cout << "*" << endl;
	gotoxy(3, 18); cout << "*";
	gotoxy(12, 18); cout << "0.  退出";
	gotoxy(35, 18); cout << "*" << endl;
	gotoxy(3, 20);
	for (int i = 0; i < t; ++i) cout << "⊙_";
	cout << endl;
	cout << "   ";
	for (int i = 0; i < t; ++i) cout << "-≈";
	cout << endl;
	cout << "   请输入您的选择:";
}

void interact::show_search_by_song_name()//输出歌名点歌界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲搜索";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
}
void interact::search_by_singer()//歌星点歌界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌手点歌";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
}
void interact::search_by_abbre()//首拼音点歌界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "拼音点歌";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
}
void interact::show_recommend()//歌曲推荐界面
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲推荐——热评榜";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	gotoxy(3, 2); cout << "人气排名" << '\t' << "歌曲名" << '\t'<<'\t' << "歌手名";
	gotoxy(0, 3); cout << "-------------------------------------------------------------------";
	cout << endl;
}
void interact::show_comment()//评分界面,输ESC退出其他继续
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲评分";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	cout << "   请输入要点评歌曲的编号：";
}
void interact::show_set_first()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲置顶";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	cout << "   请输入要置顶歌曲的编号（输入0退出）：";
}
void interact::show_delete_song_in_play()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲删除";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	cout << "   请输入要删除歌曲的编号（输入0退出）：";
}
void interact::show_add_to_love()
{
	int t = 5;
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "歌曲收藏";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	cout << "   请输入要添加到我喜欢的歌曲编号（输入0退出）：";
}
void interact::show_new()
{
	gotoxy(14, 0);
	cout << "$欢迎使用KTV点歌系统$" << endl;
	int t = 5;
	gotoxy(3, 1);
	for (int i = 0; i < t; ++i) cout << "_≈";
	cout << "用户注册";
	for (int i = 0; i < t; ++i) cout << "⊙-";
	cout << endl;
	cout << "   请输入您设置的ID：";
}