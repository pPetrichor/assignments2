#include<iostream>
#include<fstream>
using namespace std;
struct Word
{
	char word[20] = { '\0' };
	Word *next;
};
void to_lower(char *s)
{
	while ((*s) != '\0')
	{
		if ((*s) >= 'A' && (*s) <= 'Z')
			(*s) += 'a' - 'A';
		++s;
	}
}
bool str_equal(char *s1,char*s2)
{
	to_lower(s1); to_lower(s2);
	bool flag = 1;
	while((*s1)!='\0')
	{
		if (*s1 != *s2) { flag = 0; break; }
		s1++; s2++;
	}
	if (flag == 1 && *s2 != '\0') flag = 0;
	return flag;
}
int main()
{
	FILE *input=fopen("C:\\article.txt", "r");
	if (input == 0) { cerr << "文件打开失败\n"; system("pause"); exit(-1); }
	else
	{
		char article= fgetc(input);
		Word *head = new Word;
		int i = 0;
		while ((article >= 'a'&&article <= 'z') || (article >= 'A'&&article <= 'Z')) { head->word[i] = article; article = fgetc(input); ++i; }
		Word *h = head;
		while (article!=EOF)
		{
			while (!((article >= 'a'&&article <= 'z') || (article >= 'A'&&article <= 'Z'))&& article != EOF)
				article = fgetc(input);
			Word *p = new Word;
			i = 0;
			while ((article >= 'a'&&article <= 'z') || (article >= 'A'&&article <= 'Z')) { p->word[i] = article; article = fgetc(input); ++i; }
			h->next = p;
			h = p;
		}
		fclose(input);
		h->next = 0;
		char str[20] = { '\0' };
		cin >> str;
		for (; head != 0; head = head->next)
		{
			if (str_equal(head->word, str)) { cout << "True"; break; }
		}
		if (head == 0) cout << "False";
		system("pause");
		return 0;
	}
}