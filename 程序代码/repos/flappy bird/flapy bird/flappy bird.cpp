#include<iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
struct BAR
{
	int y;
	int down;
	int top;
};
int height = 20, width = 80; // 游戏画面大小
int bird_x = 10, bird_y = 5; // 小鸟的坐标,x为纵y为横
BAR bar1 = { width / 5, height / 3, height / 2 };// 障碍物1的相关坐标
BAR bar2 = { 2 * width / 5, height / 6, height / 4 }; // 障碍物2的相关坐标
BAR bar3 = { 3 * width / 5,  height / 5, height / 3 }; // 障碍物3的相关坐标
BAR bar4 = { 4 * width / 5, height / 3, 9 }; // 障碍物4的相关坐标
BAR bar5 = { width, 0, 18 }; // 障碍物5的相关坐标
int score; // 得分，经过障碍物的个数

void gotoxy(int x, int y)//类似于清屏函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void show()  // 显示画面
{
	gotoxy(0, 0);  // 清屏	
	int i, j;

	for (i = 1; i < height; ++i)
	{
		for (j = 1; j < width; ++j)
		{
			if ((i == bird_x) && (j == bird_y))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << "@";  //   输出小鸟
			}
			else if ((j == bar1.y) && ((i < bar1.down) || (i > bar1.top)))
				cout << "#";  //   输出墙壁
			else if ((j == bar2.y) && ((i < bar2.down) || (i > bar2.top)))
				cout << "#";  //   输出墙壁
			else if ((j == bar3.y) && ((i < bar3.down) || (i > bar3.top)))
				cout << "#";  //   输出墙壁
			else if ((j == bar4.y) && ((i < bar4.down) || (i > bar4.top)))
				cout << "#";  //   输出墙壁
			else if ((j == bar5.y) && ((i < bar5.down) || (i > bar5.top)))
				cout << "#";  //   输出墙壁
			else
				cout << " ";  //   输出空格
		}
		cout << endl;
	}
	cout<<"当前得分:"<< score;
}

void updateWithoutInput()  // 与用户输入无关的更新
{
	bird_x++;
	bar1.y--; bar2.y--; bar3.y--; bar4.y--; bar5.y--;
	if (bird_y == bar1.y)
	{
		if ((bird_x >= bar1.down) && (bird_x <= bar1.top))
			score++;
		else
		{
			cout << "游戏失败" << endl;
			system("pause");
			exit(0);
		}
	}
	if (bar1.y <= 0)  // 再新生成一个障碍物
	{
		bar1 = bar2; bar2 = bar3; bar3 = bar4; bar4 = bar5;//替换
		bar5.y = width;
		int temp = rand() % 16;
		int a = rand() % 3 + 1, b = rand() % 2 + 1;
		bar5.down = temp - a;
		bar5.top  = temp + b;
	}

	Sleep(150);
}

void updateWithInput()  // 与用户输入有关的更新
{
	char input;
	if (_kbhit())  // 判断是否有输入
	{
		input = _getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == ' ')
		{
			bird_x = bird_x - 2;
		}
	}
}

void main()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
}