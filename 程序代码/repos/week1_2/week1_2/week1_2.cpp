#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	//freopen("C:\\article(2).txt", "r", stdin);
	//char a[2000] = { '\0' };
	//while (cin >> a)//gets_s(a,200)����"buff is too small"?getsδ���壿getline�����ã�
	//cout << a<<" ";
	//fclose(stdin);

	freopen("C:\\article(2).txt", "r", stdin);
	char a[200] = { '\0' };
	//gets_s(a, 200);
	while (cin)//��finһ��ֻ��һ��
	{
		cin.getline(a, 200);
		cout << a;
	}
	fclose(stdin); //gets_s(a, 200)����"buff is too small" ?

	//freopen("C:\\article(2)", "a", stdout);
	//cout << "this article has some bugs";//��׷����bug?
	//fclose(stdout);

	//FILE*input = fopen("C:\\article(2).txt", "r");
	//if (input == 0) exit(-1);
	//char buff[500] = { '\0' };
	//fgets(buff, 500, input);
	//cout << buff;
	//fclose(input);

	//FILE*output = fopen("C:\\article(2).txt", "a");
	//if (output == 0) exit(-1);
	//fprintf(output, "something added\n");
	//fputs("something more added",output);
	//fclose(output);

	//ifstream fin("C:\\article(2).txt");
	//char buff[100] = { '\0' };
	//while (fin)
	//{
		//fin.getline(buff,100); 
		//cout << buff << endl; 
	//}
	//fin.close;//Ϊʲôֻ��һ��
	system("pause");//pause��freopen��Ч����fopen����
	return 0;
}