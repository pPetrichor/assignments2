#include "Einstein.h"
#include <map>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;
int begin_ = 0; int me;//me为0红方，为1蓝方
int start_ = 0;
int opposite = 0; string te1, te2;
int begin_time; int end_time;
void get()
{
	te1 = "Blue Win!"; te1 += '\n'; te1 += '\n';
    te2 = "Red Win!"; te2 += '\n'; te2 += '\n';
}
struct position
{
	int X;
	int Y;
};
map<int, position> mychess;
int new_chessboard[5][5]; int copy_chessboard[5][5];
struct ope_x
{
	int val;
	int move;
	int operat;
};
Einstein::Einstein()
{
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

string GetSystemTime()
{
	SYSTEMTIME m_time;
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf(szDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth, m_time.wDay, m_time.wHour, m_time.wMinute, m_time.wSecond);
	string time(szDateTime);
	return time;
}
string getSystemTime()
{
	SYSTEMTIME m_time;
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf(szDateTime, "%02d-%02d-%02d-", m_time.wYear, m_time.wMonth, m_time.wDay);
	string time(szDateTime);
	return time;
}
int runtime()
{
	SYSTEMTIME m_time;
	GetLocalTime(&m_time);
	return 60 * m_time.wMinute + m_time.wSecond;
}
bool change_lot()
{
	int different = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (copy_chessboard[i][j] != new_chessboard[i][j]) ++different;
	if (different > 4) return 1;
	else return 0;
}
bool if_i_win()
{
	int opp = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			if (me == 1)
			{
				if (new_chessboard[i][j] > 0 && new_chessboard[i][j] <= 6) ++opp;
			}
			else if (me == 0)
			{
				if (new_chessboard[i][j] > 6) ++opp;
			}
		}
	if (opp == 0) return 1;
	else if (me == 1)
	{
		if (new_chessboard[0][0] > 6) return 1; else return 0;
	}
	else if (me == 0)
	{
		if (new_chessboard[4][4] > 0 && new_chessboard[4][4] < 7) return 1; else return 0;
	}
}
int Einstein::parse(std::string s)
{
	string ss = GetSystemTime(); ss += ' ';
	ss += "current situation(next: my turn)"; ss += '\n';
	int x = 2;
	for(int i=0;i<5;++i)
	{
		for(int j=0;j<5;)
		{
			if ('0' <= s[x] && '9' >= s[x])
			{
				if ('0' <= s[x + 1] && '9' >= s[x + 1])
				{
					new_chessboard[i][j] = (s[x] - '0') * 10 + (s[x + 1] - '0');
					ss += '1'; ss += s[x + 1]; ss += ' '; ++x; ++j;
				}
				else
				{
					new_chessboard[i][j] = s[x] - '0'; ++j;
					ss += s[x]; ss += "  ";
				}
			}
			++x;
		}
		ss += '\n';
	}
	if('1'==s[s.length() - 2])
	{
		dice = s[s.length() - 1] - '0' + 10;
	}
	else dice = s[s.length() - 1] - '0';
	for(int i=0;i<5;++i)
		for(int j=0;j<5;++j)
		{
			position temp;
			if (dice > 6)
			{
				me = 1;
				if (new_chessboard[i][j] > 6) 
				{ temp.X = i; temp.Y = j; mychess[new_chessboard[i][j]] = temp; }
				else if (new_chessboard[i][j] > 0) opposite++;
			}
			else
			{
				me = 0;
				if (new_chessboard[i][j] <= 6 && new_chessboard[i][j] >= 1) 
				{ temp.X = i; temp.Y = j; mychess[new_chessboard[i][j]] = temp; }
				else if (new_chessboard[i][j] > 6) opposite++;

			}
		}
	if(begin_!=0&&change_lot()&&!if_i_win()) 
	{
		end_time = runtime();
		if (me == 0) { cout << "Blue Win! runtime:" << end_time - begin_time<<'s'<< endl << endl; logger.push_back(te1);}
		else if (me == 1) { cout << "Red Win! runtime:" << end_time - begin_time<<'s'<< endl << endl;  logger.push_back(te2);}

	}
	cout << ss; logger.push_back(ss);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			copy_chessboard[i][j] = new_chessboard[i][j];
	
	return 1;
}
int attack(int i,int op)//传入移动棋子编号及操作，返回移动后对应攻击值 竖为x横为y
{
	if(me==0)//红方
	{
		int x, y;
		x = mychess.find(i)->second.X; y = mychess.find(i)->second.Y;
		if (op == 1)//rightdown
		{
			x = mychess.find(i)->second.X + 1; y = mychess.find(i)->second.Y + 1;
		}
		if (op == 2)//right
		{
			y = mychess.find(i)->second.Y + 1;
		}
		if (op == 3)//down
		{
			x = mychess.find(i)->second.X + 1;
		}
		if (x == 0 || y == 0) return 0;
		if ((x == 1 && y >= 1) || (y == 1 && x >= 1)) return 1;
		if ((x == 2 && y >= 2) || (y == 2 && x >= 2)) return 2;
		if ((x == 3 && y >= 3) || (y == 3 && x >= 3)) return 3;
		if (x == 4 && y == 4) return 1000;
	}
	else if (me == 1)//蓝方
	{
		int x, y;
		x = mychess.find(i)->second.X; y = mychess.find(i)->second.Y;
		if (op == 1)//leftup
		{
			x = mychess.find(i)->second.X - 1; y = mychess.find(i)->second.Y - 1;
		}
		if (op == 2)//left
		{
			y = mychess.find(i)->second.Y - 1;
		}
		if (op == 3)//left
		{
			x = mychess.find(i)->second.X - 1;
		}
		if (x == 4 || y == 4) return 0;
		if ((x == 3 && y <= 3) || (y == 3 && x <= 3)) return 1;
		if ((x == 2 && y <= 2) || (y == 2 && x <= 2)) return 2;
		if ((x == 1 && y <= 1) || (y == 1 && x <= 1)) return 3;
		if (x == 0 && y == 0) return 1000;
	}
}
int defend(int i, int op)
{
	int defend1 = 0, defend2 = 0;
	int x, y;
	x = mychess.find(i)->second.X; y = mychess.find(i)->second.Y;
	int n = 0;//记录周围敌人个数
	if (me == 0)
	{
		if (op == 1)//rightdown
		{
			x = mychess.find(i)->second.X + 1; y = mychess.find(i)->second.Y + 1;
		}
		if (op == 2)//right
		{
			y = mychess.find(i)->second.Y + 1;
		}
		if (op == 3)//down
		{
			x = mychess.find(i)->second.X + 1;
		}
		if(x<4&&y<4)//检测三个位置
		{
			if (new_chessboard[x][y + 1] > 6) ++n;//右边有无敌人
			if (new_chessboard[x + 1][y] > 6) ++n;//下边有无敌人
			if (new_chessboard[x + 1][y + 1] > 6) ++n;//右下有无敌人
		}
		else if(x<4)
		{
			if (new_chessboard[x + 1][y] > 6) ++n;//下边有无敌人
		}
		else if(y<4)
		{
			if (new_chessboard[x][y + 1] > 6) ++n;//右边有无敌人
		}
		if (n == 0) defend1 = 30;
		if (n == 1) defend1 = 25;
		if (n == 2) defend1 = 15;//威胁值处理
		if (new_chessboard[x][y] > 6)
		{
			if (x == 4 || y == 4) defend2 = 10;
			if ((x == 3 && y <= 3) || (y == 3 && x <= 3)) defend2 = 20;
			if ((x == 2 && y <= 2) || (y == 2 && x <= 2)) defend2 = 40;
			if ((x == 1 && y <= 1) || (y == 1 && x <= 1)) defend2 = 500;
			if (opposite >= 4) defend2 -= 30;
			if (opposite == 1) defend2 = 1000;
		}
	}
	if (me == 1)
	{
		if (op == 1)//leftup
		{
			x = mychess.find(i)->second.X - 1; y = mychess.find(i)->second.Y - 1;
		}
		if (op == 2)//left
		{
			y = mychess.find(i)->second.Y - 1;
		}
		if (op == 3)//up
		{
			x = mychess.find(i)->second.X - 1;
		}
		if (x > 0 && y > 0)//检测三个位置
		{
			if (new_chessboard[x][y - 1] > 0 && new_chessboard[x][y - 1] <= 6) ++n;//左边有无敌人
			if (new_chessboard[x - 1][y] > 0 && new_chessboard[x - 1][y] <= 6) ++n;//上边有无敌人
			if (new_chessboard[x - 1][y - 1] > 0 && new_chessboard[x - 1][y - 1] <= 6) ++n;//左上有无敌人
		}
		else if (x > 0)
		{
			if (new_chessboard[x - 1][y] > 0 && new_chessboard[x - 1][y] <= 6) ++n;//上边有无敌人
		}
		else if (y > 0)
		{
			if (new_chessboard[x][y - 1] > 0 && new_chessboard[x][y - 1] <= 6) ++n;//左边有无敌人
		}
		if (n == 0) defend1 = 30;
		if (n == 1) defend1 = 25;
		if (n == 2) defend1 = 15;//威胁值处理
		if (new_chessboard[x][y] > 0 && new_chessboard[x][y] <= 6)
		{
			if (x == 0 || y == 0) defend2 = 10;
			if ((x == 1 && y >= 1) || (y == 1 && x >= 1)) defend2 = 20;
			if ((x == 2 && y >= 2) || (y == 2 && x >= 2)) defend2 = 40;
			if ((x == 3 && y >= 3) || (y == 3 && x >= 3)) defend2 = 500;
			if (opposite >= 4) defend2 -= 30;
			if (opposite == 1) defend2 = 1000;
		}
	}
	return defend1 + defend2;
}
int kill(int i, int op)//误伤值
{
	int x, y;
	x = mychess.find(i)->second.X; y = mychess.find(i)->second.Y;
	if (me == 0)//红方
	{
		if (op == 1)//rightdown
		{
			x = mychess.find(i)->second.X + 1; y = mychess.find(i)->second.Y + 1;
		}
		if (op == 2)//right
		{
			y = mychess.find(i)->second.Y + 1;
		}
		if (op == 3)//down
		{
			x = mychess.find(i)->second.X + 1;
		}
		if (new_chessboard[x][y] > 0 && new_chessboard[x][y] <= 6)
		{
			if (mychess.size() > 4) return 0;
			if (mychess.size() >= 3) return -20;
			if (mychess.size() >= 2) return -40;
			if (mychess.size() == 1) return -500;
		}
	}
	if (me == 1)//蓝方
	{
		if (op == 1)//leftup
		{
			x = mychess.find(i)->second.X - 1; y = mychess.find(i)->second.Y - 1;
		}
		if (op == 2)//left
		{
			y = mychess.find(i)->second.Y - 1;
		}
		if (op == 3)//left
		{
			x = mychess.find(i)->second.X - 1;
		}
		if (new_chessboard[x][y] > 6)
		{
			if (mychess.size() > 4) return 0;
			if (mychess.size() >= 3) return -20;
			if (mychess.size() >= 2) return -40;
			if (mychess.size() == 1) return -500;
		}
	}
	return 0;
}
bool debug(int i,int op)
{
	int x, y;
	x = mychess.find(i)->second.X; y = mychess.find(i)->second.Y;
	if(me==0)//红方
	{
		if(op==1)
		{
			if (x < 4 && y < 4) return 1;
			else return 0;
		}
		if(op==2)
		{
			if (y < 4) return 1;
			else return 0;
		}
		if(op==3)
		{
			if (x < 4) return 1;
			else return 0;
		}
	}
	if(me==1)//蓝方
	{
		if (op == 1)
		{
			if (x > 0 && y > 0) return 1;
			else return 0;
		}
		if (op == 2)
		{
			if (y > 0) return 1;
			else return 0;
		}
		if (op == 3)
		{
			if (x > 0) return 1;
			else return 0;
		}
	}
}
int caculate(int a,int d,int k)
{
	return 30 * a + d + k;
}
ope_x judge(int number)//传入色子数
{
	vector<ope_x> judges;
	if(mychess.find(number)!=mychess.end())//存在该棋子
	{
		ope_x a, b, c;
		a.move = number; b.move = number; c.move = number; a.operat = 1; b.operat = 2; c.operat = 3;
		a.val = -1000; b.val = -1000; c.val = -1000;//初始化,以红方为例，a-rightdown b-right c-down
		if(debug(number,1))//可以这样走
		{

			a.val = caculate( attack(number, 1) , defend(number, 1) , kill(number, 1));//先直接取和
			judges.push_back(a);
		}
		if (debug(number, 2))//可以这样走
		{
			b.val = caculate(attack(number, 2), defend(number, 2), kill(number, 2));//先直接取和
			judges.push_back(b);
		}
		if (debug(number, 3))//可以这样走
		{
			c.val = caculate(attack(number, 3), defend(number, 3), kill(number, 3));//先直接取和
			judges.push_back(c);
		}
	}
	else//不存在该棋子
	{
		if (mychess.begin()->first > number)
		{
			ope_x a, b, c; int num = mychess.begin()->first;
			a.move = num; b.move = num; c.move = num; a.operat = 1; b.operat = 2; c.operat = 3;
			a.val = -1000; b.val = -1000; c.val = -1000;//初始化,以红方为例，a-rightdown b-right c-down
			if (debug(num, 1))//可以这样走
			{
				a.val = caculate(attack(num, 1), defend(num, 1), kill(num, 1));//先直接取和
				judges.push_back(a);
			}
			if (debug(num, 2))//可以这样走
			{
				b.val = caculate(attack(num, 2), defend(num, 2), kill(num, 2));//先直接取和
				judges.push_back(b);
			}
			if (debug(num, 3))//可以这样走
			{
				c.val = caculate(attack(num, 3), defend(num, 3), kill(num, 3));//先直接取和
				judges.push_back(c);
			}
		}
		else
		{
			map<int, position>::iterator it;
			it = mychess.end();it--;
			if (it->first < number)
			{
				ope_x a, b, c; int num = it->first;
				a.move = num; b.move = num; c.move = num; a.operat = 1; b.operat = 2; c.operat = 3;
				a.val = -1000; b.val = -1000; c.val = -1000;//初始化,以红方为例，a-rightdown b-right c-down
				if (debug(num, 1))//可以这样走
				{
					a.val = caculate(attack(num, 1), defend(num, 1), kill(num, 1));//先直接取和
					judges.push_back(a);
				}
				if (debug(num, 2))//可以这样走
				{
					b.val = caculate(attack(num, 2), defend(num, 2), kill(num, 2));//先直接取和
					judges.push_back(b);
				}
				if (debug(num, 3))//可以这样走
				{
					c.val = caculate(attack(num, 3), defend(num, 3), kill(num, 3));;//先直接取和
					judges.push_back(c);
				}
			}
			else//存在两颗能走的棋
			{
				it = mychess.begin();
				for(;it!=mychess.end();++it)
				{
					map<int, position>::iterator i; i = it; ++i;
					if (it->first<number&&i->first>number) break;
				}
				int num1 = it->first; ++it; int num2 = it->first;
				ope_x a, b, c, d, e, f;
				a.move = num1; b.move = num1; c.move = num1; a.operat = 1; b.operat = 2; c.operat = 3;
				a.val = -1000; b.val = -1000; c.val = -1000;//初始化,以红方为例，a-rightdown b-right c-down
				d.move = num2; e.move = num2; f.move = num2; d.operat = 1; e.operat = 2; f.operat = 3;
				d.val = -1000; e.val = -1000; f.val = -1000;//初始化,以红方为例，a-rightdown b-right c-down
				if (debug(num1, 1))//可以这样走
				{
					a.val = caculate(attack(num1, 1), defend(num1, 1), kill(num1, 1));//先直接取和
					judges.push_back(a);
				}
				if (debug(num1, 2))//可以这样走
				{
					b.val = caculate(attack(num1, 2), defend(num1, 2), kill(num1, 2));//先直接取和
					judges.push_back(b);
				}
				if (debug(num1, 3))//可以这样走
				{
					c.val = caculate(attack(num1, 3), defend(num1, 3), kill(num1, 3));//先直接取和
					judges.push_back(c);
				}
				if (debug(num2, 1))//可以这样走
				{
					d.val = caculate(attack(num2, 1), defend(num2, 1), kill(num2, 1));//先直接取和
					judges.push_back(d);
				}
				if (debug(num2, 2))//可以这样走
				{
					e.val = caculate(attack(num2, 2), defend(num2, 2), kill(num2, 2));//先直接取和
					judges.push_back(e);
				}
				if (debug(num2, 3))//可以这样走
				{
					f.val = caculate(attack(num2, 3), defend(num2, 3), kill(num2, 3));;//先直接取和
					judges.push_back(f);
				}
			}
		}
		
	}
	sort(judges.begin(), judges.end(), [](ope_x a, ope_x b)->bool {return a.val > b.val; });
	return judges[0];
}
int Einstein::handle()
{
	get();
	clientsocket.recvMsg();
	string temp = clientsocket.getRecvMsg();
	if ( temp == "close") return 0;
	else
	{
		if (start_ == 0)
		{
			filename = getSystemTime(); ++start_;
		}
		if (logger.size() > 0 && (logger.back() == te1 || logger.back() == te2)) begin_ = 0;
		if (begin_ == 0) begin_time = runtime();
		mychess.clear();
		parse(clientsocket.getRecvMsg());
		begin_++;
		int move = judge(dice).move;//要移动棋子编号
		string mes;
		if (move < 10) 
		{
			char c = move + '0';
			mes += c; 
		}
		else if (move == 10) mes += "10";
		else if (move == 11) mes += "11";
		else if (move == 12) mes += "12";
		
		if(dice<=6)
		{
			if (judge(dice).operat == 1) mes += "|rightdown";
			else if (judge(dice).operat == 2) mes += "|right";
			else if (judge(dice).operat == 3) mes += "|down";
		}
		else if (dice > 6)
		{
			if (judge(dice).operat == 1) mes += "|leftup";
			else if (judge(dice).operat == 2) mes += "|left";
			else if (judge(dice).operat == 3) mes += "|up";
		}
		clientsocket.sendMsg(mes.c_str());
		logging(mes);
		return 1;
	}
	
}
int Einstein::logging(std::string s)
{
	if(s!="done!")
	{
		string ss = GetSystemTime();
		ss += " current situation(next: opponent turn)"; ss += '\n';
		int nu = -1;
		if (s[0] > '1'&&s[0] <= '9')
		{
			nu = s[0] - '0';
		}
		else if (s[0] == '1' && (!(s[1] >= '0'&&s[1] < '9'))) nu = s[0] - '0';
		else if (s[1] >= '0'&&s[1] < '9') nu = 10 + s[1] - '0';
		int x = mychess[nu].X; int y = mychess[nu].Y;
		if(me==0)//红方
		{
			if(s.find("rightdown")!=s.npos)
			{
				new_chessboard[x + 1][y + 1] = nu;
				new_chessboard[x][y] = 0;
			}
			else if (s.find("rightdown") == s.npos&&s.find("right")!=s.npos)
			{
				new_chessboard[x][y + 1] = nu;
				new_chessboard[x][y] = 0;
			}
			else if (s.find("rightdown") == s.npos&&s.find("down") != s.npos)
			{
				new_chessboard[x + 1][y] = nu;
				new_chessboard[x][y] = 0;
			}
		}
		else if (me == 1)//蓝方
		{
			if (s.find("leftup") != s.npos)
			{
				new_chessboard[x - 1][y - 1] = nu;
				new_chessboard[x][y] = 0;
			}
			else if (s.find("leftup") == s.npos&&s.find("left") != s.npos)
			{
				new_chessboard[x][y - 1] = nu;
				new_chessboard[x][y] = 0;
			}
			else if (s.find("leftup") == s.npos&&s.find("up") != s.npos)
			{
				new_chessboard[x - 1][y] = nu;
				new_chessboard[x][y] = 0;
			}
		}//棋盘更新完毕
		for(int i=0;i<5;++i)
		{
			for(int j=0;j<5;++j)
			{
				if (new_chessboard[i][j] <= 9) { ss += new_chessboard[i][j] + '0'; ss += "  "; }
				else { ss += '1'; ss += new_chessboard[i][j] - 10 + '0'; ss += ' '; }
			}
			ss += '\n';
		}
		cout << ss;
		logger.push_back(ss);
		if (if_i_win())
		{
			end_time = runtime();
			if (me == 0) { cout << "Red Win! runtime:" <<end_time-begin_time<<'s'<< endl << endl;logger.push_back(te2); }
			else if (me == 1) { cout << "Blue Win! runtime:" << end_time - begin_time<<'s'<< endl << endl; logger.push_back(te1); }
		}
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
				copy_chessboard[i][j] = new_chessboard[i][j];
		
		
	}
	else cout << s << endl;
	return 1;
}
int Einstein::writelog()
{
	filename += "-181860092.log";
	ofstream fout(filename,ios::app);
	if (!fout) { cout << "creat file failed!" << endl; return 0; }
	list<std::string>::iterator it;
	for (it = logger.begin(); it != logger.end(); ++it)
		fout << *it << endl;
	fout.close();
	return 1;
}
