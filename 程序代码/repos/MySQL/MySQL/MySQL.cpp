#include"system_.h"
int main()
{
	cout << "~$ ";
	string order;
	getline(cin, order);
	if (order == "over") return 0;
	while(order!="over")
	{
		
		if(order=="mySQL")
		{
			system_ a;
			a.run();
		}
		else if(order[0]=='c'&&order[1] == 'a'&&order[2] == 't')
		{
			istringstream ss(order);
			string txt;
			ss >> txt; ss >> txt;
			fstream fin(txt);
			int n1, n2; string column;
			fin >> n1 >> n2;
			while (fin>>column)
			{
				for (int i = 0; i < n1+1; ++i)
				{
					if(column!="EOF!") cout << column<<'\t'; 
					else cout << '\t';
					fin >> column;
				}
				cout << endl;
			}
				
		}
		else cout << "未找到该指令！（输入mySQL以运行程序，输入over结束）" << endl; 
		cout << "~$ ";
		getline(cin, order);
		if (order.size() == 0) getline(cin, order);
	}
	
	return 0;
}