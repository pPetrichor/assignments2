#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
cout<<"Happy ";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
printf("birthday ");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
printf("liya");
system("pause");
return 0;
}