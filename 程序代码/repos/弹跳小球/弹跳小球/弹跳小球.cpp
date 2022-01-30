#include<iostream>
#include<windows.h>
#include <conio.h>
using namespace std;
int score = 0;
int random1_x, random1_y, random2_x, random2_y,random3_x, random3_y, random4_x, random4_y, random5_x, random5_y;
int x = 3, y = 5, vx1 = 1, vy1 = 1;
//int x2 = 6, y2 = 6, vx2 = 1, vy2 = 1;
int head = 1, bottom = 15;
int bottom_x = 10;//反弹板初始位置
char input; bool flag = 1;
void set(int a, int b,int n)//生成障碍
{
	HANDLE hout;
	COORD coord;
	coord.X = a;
	coord.Y = b;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
	cout << "_____" << n;
}

void turn(int x1, int y1, int bottom_x)//碰到障碍反弹
{
	if (((vy1 == -1 && y1 == random1_y+2) || (vy1 == 1 && y1 == random1_y+1)) && x1 >= random1_x&& x1 <= random1_x + 5) vy1 = -vy1;
	if (((vy1 == -1 && y1 == random2_y+2) || (vy1 == 1 && y1 == random2_y+1)) && x1 >= random2_x&& x1 <= random2_x + 5) vy1 = -vy1;
	if (((vy1 == -1 && y1 == random3_y+2) || (vy1 == 1 && y1 == random3_y+1)) && x1 >= random3_x && x1 <= random3_x + 5) vy1 = -vy1;
	if (((vy1 == -1 && y1 == random4_y+2) || (vy1 == 1 && y1 == random4_y+1)) && x1 >= random4_x && x1 <= random4_x + 5) vy1 = -vy1;
	if (((vy1 == -1 && y1 == random5_y+2) || (vy1 == 1 && y1 == random5_y+1)) && x1 >= random5_x && x1 <= random5_x + 5) vy1 = -vy1;
	if (y1 == bottom + 1 && x1 >= bottom_x - 1 && x1 <= bottom_x + 6) { vy1 = -vy1; score++; flag = 1; }
}
int move(int bottom_x)//移动反弹板
{
	if (_kbhit())  // 判断是否有输入
	{
		input = _getch();
		if (input == 'a') bottom_x--;
		else if (input == 'd') bottom_x++;
	}
	return bottom_x;
}
int main()
{
	int left = 1, right = 50;
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //0表示隐藏 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏光标
	HANDLE hout;
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	while (1)
	{
		SetConsoleCursorPosition(hout, coord);//光标回到原点,重输可以覆盖，相当于清屏
		for (int j = 0; j <= bottom; ++j)
		{
			for (int i = 0; i < right; ++i) cout << " ";
			cout << "|" << endl;
		}//打边界
		SetConsoleCursorPosition(hout, coord);//光标回到原点
		for (int j = 0; j < bottom; ++j) cout << endl;
		
		for (int i = 0; i < bottom_x; ++i) cout << " ";
		cout << "_____";//打底板
		if (flag)
		{
			random1_x = rand() % 45, random1_y = rand() % 10;
			random2_x = rand() % 45, random2_y = rand() % 10;
			random3_x = rand() % 45, random3_y = rand() % 10;
			random4_x = rand() % 45, random4_y = rand() % 10;
			random5_x = rand() % 45, random5_y = rand() % 10;//制造随机障碍
			flag = 0;
		}
		set(random1_x, random1_y,1);
		set(random2_x, random2_y,2);
		set(random3_x, random3_y,3);
		set(random4_x, random4_y,4);
		set(random5_x, random5_y,5);//生成障碍
		SetConsoleCursorPosition(hout, coord);//光标回到原点
		for (int j = 0; j < y - 1; ++j) cout << endl;
		for (int i = 0; i < x - 1; ++i) cout << " ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		cout << "@";
		turn(x, y, bottom_x);
		//SetConsoleCursorPosition(hout, coord);//光标回到原点
		//for (int j = 0; j < y2 - 1; ++j) cout << endl;
		//for (int i = 0; i < x2 - 1; ++i) cout << " ";
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		//cout << "@";
		x += vx1; y += vy1;
		if (x <= left || x >= right)
		{vx1 = -vx1; printf("\a");}
		if(y<=head) {vy1 = -vy1; printf("\a");}
		for (int t = 0; t < 50; ++t)
		{
			bottom_x = move(bottom_x);
			SetConsoleCursorPosition(hout, coord);//光标回到原点
			for (int j = 0; j < bottom; ++j) cout << endl;
			for (int j = 1; j < right; ++j) cout << " ";//清行
			SetConsoleCursorPosition(hout, coord);//光标回到原点
			for (int j = 0; j < bottom; ++j) cout << endl;
			for (int i = 0; i < bottom_x; ++i) cout << " ";
			cout << "_____";//打底板
		}
		if (y > bottom+2) break;
		//Sleep(50);
		//x2 += vx2; y2 += vy2;
		//if (x2 <= left || x2 > right)
		//{vx2 = -vx2; printf("\a");}
		//if (y2 <= head || y2 > bottom)
		//{vy2 = -vy2; printf("\a");}
		
	}
	cout << endl<< "game over!你的得分为"<<score;
	system("pause");
	return 0;
}
