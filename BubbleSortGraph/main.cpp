#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;
#include "BGraph.h"
void output(const BGraph& Bubble)//顯示結果
{
	ofstream cout("output.txt");
	cout << "Isolated Point(s):" << endl;
	if (Bubble.Component.front().member.size() == 0)
	{
		cout << "Nope" << endl;
	}
	for (list<BPoint* > ::const_iterator j = Bubble.Component.front().member.begin(); j != Bubble.Component.front().member.end(); j++)
	{
		cout << "Point " + (*j)->ID << endl;
	}
	for (list<BComponent>::const_iterator i = ++Bubble.Component.begin(); i != Bubble.Component.end(); i++)//顯示猜測結果
	{
		bool badingood = false;
		cout << "Component " << i->id << " Contain the following Point(s):" << endl;
		for (list<BPoint* > ::const_iterator j = i->member.begin(); j != i->member.end(); j++)
		{
			cout << "	Point " + (*j)->ID << endl;
			if ((*j)->IsBroken)
			{
				badingood = true;
			}
		}
		cout << "...Ans Contain the following Isolated Point(s):" << endl;
		if (i->Sur_Point.size() == 0)
		{
			cout << "Nope" << endl;
		}
		for (list<BPoint* > ::const_iterator j = i->Sur_Point.begin(); j != i->Sur_Point.end(); j++)
		{
			cout << "	Point " + (*j)->ID << endl;
			if ((*j)->IsBroken)
			{
				badingood = true;
			}
		}
		if (i->member.size() + i->Sur_Point.size() >= Bubble.t*(Bubble.Level - 1) / (Bubble.Level - 3) && !i->Is_Link())//不相鄰
		{
			cout << "^^^^^^^This component is Fault-Free.^^^^^^^^^^^" << endl;
			if (badingood)
			{
				cout << "^^^^^^^^^^^^^^But there is a bad point in it^^^^^" << endl;
			}
		}
	}
	cout.close();
	system("start output.txt");
}
vector<BStruct> Sub_B;
int main()
{
	int Level = 9;//階層數
	int BrokenNum = 10000;//壞點數
	BGraph Bubble(Level);//圖
	Bubble.RandomSetBroken(BrokenNum);

	//system("PAUSE");
	//list<string> pro;//壞點ID
	//prowhypoint(Level, BrokenNum, pro);
	//Bubble.SetBroken(pro);

	//GetSubStruct(Bubble.BS, Sub_B);
	//for (int i = 0; i < Sub_B.size(); i++)
	//{
	//	Subgraph Sub_G(Sub_B[i], Level);
	//	Sub_G.f_comp();
	//	Sub_G.FindGoodComp();
	//}
	//
	//output(Sub_G);
	//system("PAUSE");

	Bubble.f_comp();
	Bubble.FindGoodComp();
	output(Bubble);
	system("PAUSE");
	return 0;
}