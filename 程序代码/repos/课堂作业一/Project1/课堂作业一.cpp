#include<iostream>
using namespace std;
int main()
{
	int n = 0;
	while (n < 4)
	{
		cout << "ÊäÈëËÄ¸ö×Ö·û´®"<<endl;
		char str1[60] = { '\0' }, str2[60] = { '\0' }, str3[60] = { '\0' }, str4[60] = { '\0' };
		char date, hour; int minute;
		cin >> str1 >> str2 >> str3 >> str4;
		int i;
		for (i = 0; i < strlen(str1); ++i)
			if (str1[i] == str2[i] && 'A' <= str1[i] && 'G' >= str1[i])
			{
				date = str1[i]; break;
			}
		for (++i; i < strlen(str1); ++i)
			if (str1[i] == str2[i] && (('A' <= str1[i] && 'N' >= str1[i]) || (0 <= str1[i] - '0' && 9 >= str1[i] - '0')))
			{
				hour = str1[i]; break;
			}
		for (i = 0; i < strlen(str3); ++i)
			if (str3[i] == str4[i] && (('A' <= str3[i] && 'Z' >= str3[i]) || ('a' <= str3[i] && 'z' >= str3[i])))
			{
				minute = i; break;
			}
		switch (date)
		{
		case 'A':cout << "MON "; break;
		case 'B':cout << "TUE "; break;
		case 'C':cout << "WES "; break;
		case 'D':cout << "THU "; break;
		case 'E':cout << "FRI "; break;
		case 'F':cout << "SAT "; break;
		case 'G':cout << "SUN "; break;
		}
		switch(hour)
		{
		case '0':cout << "00:"; break;
		case '1':cout << "01:"; break;
		case '2':cout << "02:"; break;
		case '3':cout << "03:"; break;
		case '4':cout << "04:"; break;
		case '5':cout << "05:"; break;
		case '6':cout << "06:"; break;
		case '7':cout << "07:"; break;
		case '8':cout << "08:"; break;
		case '9':cout << "09:"; break;
		case 'A':cout << "10:"; break;
		case 'B':cout << "11:"; break;
		case 'C':cout << "12:"; break;
		case 'D':cout << "13:"; break;
		case 'E':cout << "14:"; break;
		case 'F':cout << "15:"; break;
		case 'G':cout << "16:"; break;
		case 'H':cout << "17:"; break;
		case 'I':cout << "18:"; break;
		case 'J':cout << "19:"; break;
		case 'K':cout << "20:"; break;
		case 'L':cout << "21:"; break;
		case 'M':cout << "22:"; break;
		case 'N':cout << "23:"; break;
		}
		if (minute < 10) cout << "0" << minute<<endl;
		else cout << minute<<endl;
		++n;
	}
	system("pause");
	return 0;
}