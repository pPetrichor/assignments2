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
int height = 20, width = 80; // ��Ϸ�����С
int bird_x = 10, bird_y = 5; // С�������,xΪ��yΪ��
BAR bar1 = { width / 5, height / 3, height / 2 };// �ϰ���1���������
BAR bar2 = { 2 * width / 5, height / 6, height / 4 }; // �ϰ���2���������
BAR bar3 = { 3 * width / 5,  height / 5, height / 3 }; // �ϰ���3���������
BAR bar4 = { 4 * width / 5, height / 3, 9 }; // �ϰ���4���������
BAR bar5 = { width, 0, 18 }; // �ϰ���5���������
int score; // �÷֣������ϰ���ĸ���

void gotoxy(int x, int y)//��������������
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void show()  // ��ʾ����
{
	gotoxy(0, 0);  // ����	
	int i, j;

	for (i = 1; i < height; ++i)
	{
		for (j = 1; j < width; ++j)
		{
			if ((i == bird_x) && (j == bird_y))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << "@";  //   ���С��
			}
			else if ((j == bar1.y) && ((i < bar1.down) || (i > bar1.top)))
				cout << "#";  //   ���ǽ��
			else if ((j == bar2.y) && ((i < bar2.down) || (i > bar2.top)))
				cout << "#";  //   ���ǽ��
			else if ((j == bar3.y) && ((i < bar3.down) || (i > bar3.top)))
				cout << "#";  //   ���ǽ��
			else if ((j == bar4.y) && ((i < bar4.down) || (i > bar4.top)))
				cout << "#";  //   ���ǽ��
			else if ((j == bar5.y) && ((i < bar5.down) || (i > bar5.top)))
				cout << "#";  //   ���ǽ��
			else
				cout << " ";  //   ����ո�
		}
		cout << endl;
	}
	cout<<"��ǰ�÷�:"<< score;
}

void updateWithoutInput()  // ���û������޹صĸ���
{
	bird_x++;
	bar1.y--; bar2.y--; bar3.y--; bar4.y--; bar5.y--;
	if (bird_y == bar1.y)
	{
		if ((bird_x >= bar1.down) && (bird_x <= bar1.top))
			score++;
		else
		{
			cout << "��Ϸʧ��" << endl;
			system("pause");
			exit(0);
		}
	}
	if (bar1.y <= 0)  // ��������һ���ϰ���
	{
		bar1 = bar2; bar2 = bar3; bar3 = bar4; bar4 = bar5;//�滻
		bar5.y = width;
		int temp = rand() % 16;
		int a = rand() % 3 + 1, b = rand() % 2 + 1;
		bar5.down = temp - a;
		bar5.top  = temp + b;
	}

	Sleep(150);
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if (_kbhit())  // �ж��Ƿ�������
	{
		input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
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
	while (1)  //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();     // ���û������йصĸ���
	}
}