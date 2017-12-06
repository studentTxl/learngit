#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<string>
#include<conio.h>
#include<cstdio>
using namespace std;



void printleft(int x,int cardnum);
void printright(int x,int cardnum);
void changecolor();
int fun_num=0;
int fun_card=0;
int turn=0;

class card  
{

	private:
		char color;
		string number;
		int place;
	public:
		virtual ~card();
		char getcolor() const{
			return color;}
		string getnumber() const{
			return number;}
		int   getplace() {
			return place;}
		void restart();
		void set(int i);
		void set1(int i);
		void set(card &);
		bool operator ==(const card &c)const;
		card(char ch=3,string s="A",int i=6); 
		friend class cards;
};

card::card(char ch,string s,int i)
{

	color=ch;
	number=s;
	place=i;
}

card::~card()
{


}
void card::set(int i)
{
	place=i;}
void card::set1(int i)
{

	color=i;
}
void card::set(card &c)
{

	color=c.color;
	number=c.number;
	place=c.place;
}
bool card::operator ==(const card &c) const
{

	if(number=="9")   return false;
	else if(number==c.number ||   color==c.color)
		return true;
	else return false;
}
void card::restart()
{

	color=3;
	number="A";
	place=6;
}

card temp;

class cards  
{

	private:    
		void wash();

	public:
		card pcard[104];
		cards();
		virtual ~cards();    
		void give(int person);
		friend class player;
		friend class AI_player;
};

cards::cards()
{

	int i,j;
	string sh;
	for(i=0;i<26;i++)   pcard[i].color=3;
	for(i=26;i<52;i++) pcard[i].color=4;
	for(i=52;i<78;i++) pcard[i].color=5;
	for(i=78;i<104;i++)pcard[i].color=6;
	for(i=0;i<8;i++)
	{

		for(j=0;j<13;j++)
		{

			switch(j)
			{

				case 0:sh="A";break;
				case 1:sh="2";break;
				case 2:sh="3";break;
				case 3:sh="4";break;
				case 4:sh="5";break;
				case 5:sh="6";break;
				case 6:sh="7";break;
				case 7:sh="8";break;
				case 8:sh="9";break;
				case 9:sh="10";break;
				case 10:sh="J";break;
				case 11:sh="Q";break;
				case 12:sh="K";break;
			}
			pcard[i*13+j].number=sh;
		}
	}
}

cards::~cards()
{


}
void cards::give(int person)
{

	int i=rand()%104;
	int ii=i;
	while(pcard[i].place!=5)
	{

		i++;
		if(i==104) i=0;
		if(i==ii) wash();
	}
	pcard[i].place=person;
}
void cards::wash()
{

	for(int i=0;i<104;i++)
	{

		if(pcard[i].place==6)
			pcard[i].place=5;
	}
}

class player  
{

	private:
		int player_card;
	public:
		player();
		virtual ~player();
		int player_choose(cards&);
		int get_player_card(){
			return player_card;};
};
player::player()
{

	player_card=7;
}

player::~player()
{


}

int player::player_choose(cards &c)  
{

	int i;
	if(temp.getnumber()=="8"&&fun_num!=0)
	{

		for(i=0;i<104;i++)
		{

			if(c.pcard[i].getplace()==1&&c.pcard[i].getnumber()=="8") break;
		}
		if(i==104)
		{

			fun_num=0;
			fun_card=0;
			return 0;  
		}
	}
	if(temp.getnumber()=="7"&&fun_num!=0)
	{

		for(i=0;i<104;i++)
		{

			if(c.pcard[i].getplace()==1&&c.pcard[i].getnumber()=="7") break;
		}
		if(i==104)
		{

			for(int k=0;k<2*fun_num;k++) c.give(1);
			player_card+=fun_num*2;
			fun_num=0;
			fun_card=0;
			return 0; 
		}
	}

	int x=0;
Lable1:     int key=0;
			while(key!=32)
			{

				while( kbhit() ) {
					getch(); }
				key=getch();        
				if (key == 224)
					key = getch();
				switch(key)
				{

					case 77:x++;
							if(x==player_card+1)
								x=0;
							printright(x,player_card);   
							break;
					case 75:x--;
							if(x<0)
								x=player_card;
							printleft(x,player_card); 
							break;
				}
			}
			if(x==0&&fun_card==0)
			{

				c.give(1);
				player_card++;
				return 0; 
			}
			else if(x==0&&fun_card!=0)   goto Lable1;
			int ii;
			for(i=0,ii=0;i<104&&x!=0;i++)
			{

				if(c.pcard[i].getplace()==1)
				{

					ii++;
					if(ii==x)
						break;            
				}
			}
			if(fun_card!=0&&c.pcard[i].getnumber()!=temp.getnumber())   goto Lable1;

			if(c.pcard[i]==temp)
			{

				c.pcard[i].set(6);
				temp.set(c.pcard[i]);
				player_card--;
				if(c.pcard[i].getnumber()=="7")
				{

					fun_num++;
					fun_card=7;
				}
				if(c.pcard[i].getnumber()=="8")
				{

					fun_num++;
					fun_card=8;
				}        

			}
			else if(c.pcard[i].getnumber()=="9")
			{

				c.pcard[i].set(6);
				temp.set(c.pcard[i]);
				changecolor();   
				player_card--;
			}
			else goto Lable1;
			return 0; 
}

class AI_player 
{

	private:
		int AI_num;
		int AI_card;
	public:
		AI_player(int i);
		virtual ~AI_player();
		int AI(cards&);
		int get_AI_num(){
			return AI_num;}
		int get_AI_card(){
			return AI_card;}
};

AI_player::AI_player(int i=0)
{

	AI_num=i;
	AI_card=7;
}

AI_player::~AI_player()
{


}

bool compare(int a,int b[4])
{

	for(int i=0;i<4;i++)
	{

		if(b[a]<b[i])
			break;
	}
	if(i==4) return true;
	else return false;
}
int compare(int b[4])
{

	int s=b[0];
	int colormark=0;
	for(int i=0;i<4;i++)
	{

		if(b[i]>s)
			s=b[i];
		colormark=i;
	}
	return colormark;
}

int AI_player::AI(cards &c)
{

	int i;
	int color[4]={
		0};
	int num=0;
	int p[30];
	if(temp.getnumber()=="8"&&fun_num!=0)
	{

		for(i=0;i<104;i++)
		{

			if(c.pcard[i].getplace()==get_AI_num()&&c.pcard[i].getnumber()=="8")
			{

				p[num]=i;
				num++;
			}
			if(c.pcard[i].getplace()==AI_num)
				color[c.pcard[i].getcolor()-3]++;
		}
		if(num==0)
		{



			fun_num=0;
			fun_card=0;
			return 0; 
		}
		else if(num==1)
		{

			c.pcard[p[0]].set(6);
			AI_card--;
			temp.set(c.pcard[p[0]]);
			return 0; 
		}
		else
		{

			for(i=0;i<num;i++)
			{

				if(compare(c.pcard[p[i]].getcolor()-3,color))
				{

					c.pcard[p[i]].set(6);
					AI_card--;
					temp.set(c.pcard[p[i]]);
					return 0; 
				}
			}
		}
	}
	if(temp.getnumber()=="7"&&fun_num!=0)
	{

		for(i=0;i<104;i++)
		{

			if(c.pcard[i].getplace()==get_AI_num()&&c.pcard[i].getnumber()=="7")
			{

				p[num]=i;
				num++;
			}
			if(c.pcard[i].getplace()==AI_num)
				color[c.pcard[i].getcolor()-3]++;
		}
		if(num==0)
		{

			for(i=0;i<2*fun_num;i++) c.give(AI_num);
			AI_card+=fun_num*2;
			fun_num=0;
			fun_card=0;
			return 0; 
		}
		else if(num==1)
		{

			c.pcard[p[0]].set(6);
			AI_card--;
			fun_num++;
			fun_card=7;
			temp.set(c.pcard[p[0]]);
			return 0; 
		}
		else
		{

			for(i=0;i<num;i++)
			{

				if(compare(c.pcard[p[i]].getcolor()-3,color))
				{

					c.pcard[p[i]].set(6);
					AI_card--;
					fun_num++;
					fun_card=7;
					temp.set(c.pcard[p[i]]);
					return 0; 
				}
			}
		}
	}
	for(i=0;i<104;i++)
	{

		if(c.pcard[i].getplace()==AI_num)
		{

			color[c.pcard[i].getcolor()-3]++;
			p[num]=i;
			num++;
		}
	}
	for(i=0;i<num;i++) 
	{

		if(c.pcard[p[i]]==temp)
		{

			c.pcard[p[i]].set(6);
			AI_card--;
			if(c.pcard[p[i]].getnumber()=="7"){
				fun_num++;fun_card=7;}
			if(c.pcard[p[i]].getnumber()=="8"){
				fun_num++;fun_card=8;}
			temp.set(c.pcard[p[i]]);
			return 0; 
		}
	}

	for(i=0;i<num;i++)
	{

		if(c.pcard[p[i]].getnumber()=="9")
		{

			temp.set(c.pcard[p[i]]);
			c.pcard[p[i]].set(6);
			temp.set1(compare(color)+3);
			AI_card--;
			return 0; 
		}
	}
	if(i==num)
	{

		c.give(AI_num);
		AI_card++;
		return 0; 
	}
	return 0; 
}
void gotoxy(int x,int y)
{

	COORD c;
	c.X=x-1;              
	c.Y=y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void changecolor(int i)
{

	switch(i)
	{

		case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);break;
		case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);break;
		case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);break;
		case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);break;
	}
}
void changecolor()
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	char a=3,b=4,c=5,d=6,direct=25;
	gotoxy(40,25);
	cout<<"哇，万能牌，那么要变成什么花色呢？";
	gotoxy(40,29);
	cout<<"┏━━━━━━━━━━━━━━━┓";
	gotoxy(40,30);
	cout<<"┃       ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	cout<<a<<"      ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	cout<<b<<"      ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	cout<<c<<"      ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<d<<"      ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	cout<<"┃";
	gotoxy(40,31);    
	cout<<"┗━━━━━━━━━━━━━━━┛";
	int key=0;//记录按键动作
	int x=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gotoxy(48,28);
	cout<<direct<<direct;
	while(key!=32)
	{

		while( kbhit() )    {
			getch(); }
		key=getch();    
		if (key == 224)
			key = getch();
		switch(key)
		{

			case 77: x++;
					 if(x==4)
					 {

						 gotoxy(66,28);
						 cout<<"   ";
						 gotoxy(48,28);
						 cout<<direct<<direct;

						 x=0;
					 }
					 else
					 {

						 gotoxy(42+x*6,28);
						 cout<<"   ";
						 gotoxy(48+x*6,28);
						 cout<<direct<<direct;
					 }
					 break;
			case 75:x--;
					if(x<0)
					{

						gotoxy(48,28);
						cout<<"   ";
						gotoxy(66,28);
						cout<<direct<<direct;
						x=3; 
					}
					else
					{

						gotoxy(54+6*x,28);
						cout<<"   ";
						gotoxy(48+6*x,28);
						cout<<direct<<direct;


					}
					break;
		}
	}
	temp.set1(x+3);
}
void print(AI_player a1,AI_player a2,AI_player a3,player p,cards c)
{

	system("cls");
	system("doskey/overstrike");
	int i=0;
	int j=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);

	for(int marki=0;marki<a1.get_AI_card();marki++)
	{

		gotoxy(113,9+marki);
		cout<<"┏━━━━━━┓";
	}
	gotoxy(113,9+marki);
	if(a1.get_AI_card()) 
	{

		for(i=0;i<3;i++)
		{

			gotoxy(113,9+marki+i);
			cout<<"┃             ┃";
		}
		gotoxy(113,9+marki+i);
		cout<<"┗━━━━━━┛";
		gotoxy(119,7+marki+i);
		cout<<"uno";
	}   
	gotoxy(1,1);
	for(i=0;i<a2.get_AI_card();i++)
		cout<<"┏━";
	if(a2.get_AI_card()) cout<<"━━┓";
	for(j=0;j<5;j++)
	{

		gotoxy(1,j+2);
		for(i=0;i<a2.get_AI_card();i++)
			cout<<"┃   ";
		if(a2.get_AI_card()) cout<<"     ┃";
	}
	gotoxy(1,7);
	for(i=0;i<a2.get_AI_card();i++)
		cout<<"┗━";
	if(a2.get_AI_card()) cout<<"━━┛";
	gotoxy(a2.get_AI_card()*4+1,4); 
	if(a2.get_AI_card()) cout<<"uno";    
	for(marki=0;marki<a3.get_AI_card();marki++)
	{

		gotoxy(1,9+marki);
		cout<<"┏━━━━━━┓";
	}
	gotoxy(1,9+marki);
	if(a3.get_AI_card()) 
	{

		for(i=0;i<3;i++)
		{

			gotoxy(1,9+marki+i);
			cout<<"┃             ┃";
		}
		gotoxy(1,9+marki+i);
		cout<<"┗━━━━━━┛";
		gotoxy(7,7+marki+i);
		cout<<"uno";
	}
	gotoxy(57,15);   cout<<"┏━━━┓";
	gotoxy(57,16);   cout<<"┃       ┃";
	gotoxy(57,17);   cout<<"┃       ┃";
	gotoxy(57,18);   cout<<"┃       ┃";
	gotoxy(57,19);   cout<<"┃       ┃";
	gotoxy(57,20);   cout<<"┃       ┃";
	gotoxy(57,21);   cout<<"┗━━━┛";
	changecolor(temp.getcolor());
	gotoxy(59,16);   cout<<temp.getnumber();
	gotoxy(59,17);   cout<<temp.getcolor();
	gotoxy(15,38);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	for(i=0;i<p.get_player_card();i++)
		cout<<"┏━";
	if(p.get_player_card()) cout<<"━━┓";
	for(j=0;j<5;j++)
	{

		gotoxy(15,38+j+1);
		for(i=0;i<p.get_player_card();i++)
			cout<<"┃   ";
		if(p.get_player_card()) cout<<"     ┃";
	}
	gotoxy(15,44);
	for(i=0;i<p.get_player_card();i++)
		cout<<"┗━";
	if(p.get_player_card()) cout<<"━━┛";
	for(i=0,marki=0;i<104;i++)
	{

		if(c.pcard[i].getplace()==1)
		{

			changecolor(c.pcard[i].getcolor());
			gotoxy(17+marki*4,39);    
			cout<<c.pcard[i].getnumber();
			gotoxy(17+marki*4,40);
			cout<<c.pcard[i].getcolor();
			marki++;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gotoxy(5,38);   cout<<"┏━━━┓";
	gotoxy(5,39);   cout<<"┃       ┃";
	gotoxy(5,40);   cout<<"┃       ┃";
	gotoxy(5,41);   cout<<"┃       ┃";
	gotoxy(5,42);   cout<<"┃       ┃";
	gotoxy(5,43);   cout<<"┃       ┃";
	gotoxy(5,44);   cout<<"┗━━━┛";
	gotoxy(8,41);   cout<<"抽牌";
	char mark=15;
	switch(turn)
	{

		case 1:     gotoxy(98,19);
					cout<<"it's my turn";
					for(i=0;i<2;i++)
					{

						gotoxy(103,20);
						for(j=0;j<3;j++)
						{


							cout<<"。";    
							_sleep(200);                    
						}
						gotoxy(103,20);
						cout<<"      ";
					}
					break;
		case 2:
					gotoxy(59,8);
					cout<<"该出什么呢";
					for(i=0;i<2;i++)
					{

						gotoxy(59,9);
						for(j=0;j<3;j++)
						{

							cout<<"。";    
							_sleep(200);                    
						}
						gotoxy(59,9);
						cout<<"      ";
					}
					break;
		case 3:
					gotoxy(18,19);
					cout<<"哈哈，我要赢啦~~";
					for(i=0;i<2;i++)
					{

						gotoxy(20,20);
						for(j=0;j<3;j++)
						{

							cout<<"。";    
							_sleep(200);                    
						}
						gotoxy(20,20);
						cout<<"      ";
					}
					break;
	}

}
void printright(int x=0,int cardnum=0)
{

	char direct=25;
	system("doskey/overstrike");
	gotoxy(9,36);
	cout<<direct<<direct;
	if(x==0)  
	{

		gotoxy(13+4*cardnum,36); 
		cout<<"   ";  
		gotoxy(9,36);
		cout<<direct<<direct;
	}
	else if(x==1) 
	{

		gotoxy(9,36);
		cout<<"   "; 
		gotoxy(17,36);
		cout<<direct<<direct;
	}
	else 
	{

		gotoxy(9,36);
		cout<<"   ";
		gotoxy(9+4*x,36);
		cout<<"   ";
		gotoxy(13+4*x,36);
		cout<<direct<<direct;
	}
}
void printleft(int x=0,int cardnum=0)
{

	char direct=25;
	system("doskey/overstrike");
	if(x==0)  
	{

		gotoxy(17,36);
		cout<<"   ";  
		gotoxy(9,36);
		cout<<direct<<direct;
	}
	else if(x==cardnum)
	{

		gotoxy(9,36);
		cout<<"   ";
		gotoxy(13+4*cardnum,36);
		cout<<direct<<direct;
	}
	else
	{

		gotoxy(17+4*x,36);
		cout<<"   ";
		gotoxy(13+4*x,36);
		cout<<direct<<direct;
	}
}
void direct_show()
{

	cout<<"温馨提示："<<endl<<"正式开始游戏前，请点击这个方框左上角的菜单"<<endl<<"选择属性,布局"<<endl<<"将窗口大小设置为宽128,高44"<<endl<<"设置完后按任意键继续..."<<endl;
	while( kbhit() ) {
		getch(); }
	getch();
}
void lose_show()
{

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gotoxy(47,19);   cout<<"╔═════════════════════╗"<<endl;
	gotoxy(47,20);   cout<<"║                 you lose!                  ║"<<endl;
	gotoxy(47,21);   cout<<"╚═════════════════════╝"<<endl;
	while( kbhit() ) {
		getch(); }
	getch();
}
void win_show()
{

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gotoxy(47,19);   cout<<"╔═════════════════════╗"<<endl;
	gotoxy(47,20);   cout<<"║                  you win!                  ║"<<endl;
	gotoxy(47,21);   cout<<"╚═════════════════════╝"<<endl;
	while( kbhit() ) {
		getch(); }
	getch();
}
void load_show()
{

	system("doskey/overstrike");
	system("cls");
	gotoxy(50,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	cout<<"洗牌，发牌中。。。";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gotoxy(47,19);   cout<<"╔════════════════════╗"<<endl;
	gotoxy(47,20);   cout<<"║                                          ║"<<endl;
	gotoxy(47,21);   cout<<"╚════════════════════╝"<<endl;
	for(int i=1;i<=100;i++)
	{

		_sleep(40);
		gotoxy(47,23);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
		cout<<i<<"%";
		if(i%5==0)
		{

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gotoxy(47+i/5*2,20);
			cout<<"█";
		}
	}
	gotoxy(49,20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	cout<<"████████████████████";
	gotoxy(47,28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	cout<<"发牌完毕，按任意键开始游戏。。。"<<endl;
	while(_kbhit())
		getch();
	getch();
}
void end_show()
{

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gotoxy(1,43);
	cout<<"                                                         游戏结束"<<endl; _sleep(100);
	gotoxy(1,42);
	cout<<"                                                         游戏结束"<<endl;
	cout<<"                                                      感谢游戏开发人员"<<endl;

	for(int i=41;i>15;i--)
	{

		_sleep(100);
		system("cls");
		gotoxy(1,i);
		cout<<"                                                         游戏结束"<<endl;
		cout<<"                                                      感谢游戏开发人员"<<endl;
	}
	getch();
}
void help_show()
{

	system("cls");
	cout<<"                                             uno纸牌"<<endl<<endl<<endl<<endl;
	cout<<"   1.   本游戏由方向键和空格键控制，若出牌无效则不会有反应（不会玩的可以一张一张牌试着出）；"<<endl;
	cout<<"   2.   每人开局发七张牌，并以红桃A为开始时的明牌;"<<endl;
	cout<<"   3.   按顺序出牌，只能出与上一张打出牌一样的花色或数字的牌;"<<endl;
	cout<<"   4.   无法出牌则摸一张牌，跳过自己的回合;"<<endl;
	cout<<"   5.   功能牌：数字7，下家要摸两张牌；数字8，跳过下家的回合；数字9：万能牌，可任意出而不受上一张牌的约束，并指定接着的出牌花色;"<<endl; cout<<"   6.   功能牌可顶牌，即上家出了功能牌，可出相同的功能牌把效果转移给下家;"<<endl;
	cout<<"   7.   有一玩家出完牌游戏即结束;"<<endl;
	cout<<"   8.   游戏有两副牌（去掉大王小王）;"<<endl<<endl<<endl<<endl<<endl;
	cout<<"       按任意键返回主菜单..."<<endl;
	while( kbhit() ) {
		getch(); }
	getch();
}
void menu_show()
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	system("cls");
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                     UUUU            UUUU                NNNNNN            NNNN                        OOOOO"<<endl;
	cout<<"                      UUU            UUU                 NNN NN            NNN                       OO      OO"<<endl;
	cout<<"                      UUU            UUU                 NNN   NN           NNN                     OO          OO"<<endl;
	cout<<"                      UUU            UUU                 NNN    NN          NNN                    OO            OO"<<endl;
	cout<<"                      UUU            UUU                 NNN     NN         NNN                   OO              OO"<<endl;
	cout<<"                      UUU            UUU                 NNN      NN        NNN                  OO                OO"<<endl;
	cout<<"                      UUU            UUU                 NNN       NN       NNN                 OO                  OO"<<endl;
	cout<<"                      UUU            UUU                 NNN        NN      NNN                  OO                OO"<<endl;
	cout<<"                      UUU            UUU                 NNN         NN     NNN                   OO              OO"<<endl;


	cout<<"                      UUU            UUU                 NNN          NN    NNN                    OO            OO"<<endl;
	cout<<"                       UU            UU                  NNN           NN   NNN                     OO          OO"<<endl;
	cout<<"                        UUUUUUUUUUUUU                   NNN            NN NNN                       OO      OO"<<endl;
	cout<<"                         UUUUUUUUUUU                   NNNN            NNNNNN                         OOOOO "<<endl;
	gotoxy(63,26);
	cout<<"Start";
	gotoxy(63,29);
	cout<<"Help";
	gotoxy(63,32);
	cout<<"Exit"<<endl;
}
void playgame()
{

	temp.restart();
	srand(time(0));
	AI_player ai2(2),ai3(3),ai4(4);
	player wl;
	cards puke;
	int i;
	int flag=0;
	for(i=0;i<7;i++)
	{

		puke.give(1);puke.give(2);
		puke.give(3);
		puke.give(4);
	}
	load_show();
	print(ai2,ai3,ai4,wl,puke);
	while(flag==0)
	{

		switch(turn)
		{

			case 0:printright(0,wl.get_player_card());
				   wl.player_choose(puke);
				   if(wl.get_player_card()==0)
					   flag=1;
				   turn++;
				   print(ai2,ai3,ai4,wl,puke);
				   break;
			case 1:ai2.AI(puke);
				   if(ai2.get_AI_card()==0)
					   flag=2;
				   turn++;
				   print(ai2,ai3,ai4,wl,puke);
				   break;    
			case 2:ai3.AI(puke);
				   if(ai3.get_AI_card()==0)
					   flag=2;
				   turn++;
				   print(ai2,ai3,ai4,wl,puke);
				   break;
			case 3:ai4.AI(puke);
				   if(ai4.get_AI_card()==0)
					   flag=2;
				   turn=0;
				   print(ai2,ai3,ai4,wl,puke);
				   break;
		}
	}
	if(flag==1) {
		system("cls");win_show();}
	if(flag==2) {
		system("cls");lose_show();}


}
int main()
{

	direct_show();
	int key=0;
	int x=57,y=26;
Start:
	turn=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	key=0;
	x=57,y=26;
	menu_show();
	gotoxy(57,26);
	cout<<">>>"<<endl;
	while(key!=32)
	{

		system("doskey/overstrike");
		while( kbhit() ) {
			getch(); }
		key=getch();        
		if (key == 224)
			key = getch();
		if(key==80)
		{

			gotoxy(x,y);
			cout<<"    ";
			y+=3;
			if(y==35) y=26;
		}
		if(key==72)
		{

			gotoxy(x,y);
			cout<<"    ";
			y-=3;
			if(y==23) y=32;
		}
		gotoxy(x,y);
		cout<<">>>"<<endl;
	}
	if(y==26)
	{

		playgame();
		goto Start;
	}
	else if(y==29)
	{

		help_show();
		goto Start;
	}
	else if(y==32)
	{

		end_show();
	}
	return 0;
}
