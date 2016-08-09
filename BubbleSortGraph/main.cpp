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
			cout << "	Point " + (*j)->ID;
			if ((*j)->IsBroken)
			{
				cout << 'x';
				badingood = true;
			}
			cout << endl;
		}
		cout << "...Ans Contain the following Isolated Point(s):" << endl;
		if (i->Sur_Point.size() == 0)
		{
			cout << "Nope" << endl;
		}
		for (list<BPoint* > ::const_iterator j = i->Sur_Point.begin(); j != i->Sur_Point.end(); j++)
		{
			cout << "	Point " + (*j)->ID;
			if ((*j)->IsBroken)
			{
				cout << 'x';
				badingood = true;
			}
			cout << endl;
		}
		if (i->member.size() + i->Sur_Point.size() > Bubble.PossibleBadSize && !i->Is_Link()&& i->GetStatus()!=Bad)//不相鄰
		{
			cout << "^^^^^^^This component is Fault-Free.^^^^^^^^^^^" << endl;
			if (badingood)
			{
				cout << "^^^^^^^^^^^^^^But there is a bad point in it^^^^^" << endl;
			}
		}
		if (i->GetStatus() == Bad)
		{
			cout << "^^^^^^^This component is Faulty.(by new algorithm)^^^^^^^^^^^" << endl;
		}
	}
	cout.close();
	system("start output.txt");
}
vector<BStruct> Sub_B;
int main()
{
	/*int Level = 9;//階層數
	int BrokenNum = 17;//壞點數
	BGraph Bubble(Level);//圖
	//Bubble.ReadSetBroken(BrokenNum);
	Bubble.RandomSetBroken(Bubble.T_LowerBound);
	Bubble.f_comp();
	Bubble.FindGoodComp();
	output(Bubble);*/
	cout << "Start reading symptom." << endl;
	BGraph Bubble("symptom.all");
	cout << "All symptom readed." << endl;
	cout << "Finding Component." << endl;
	Bubble.ComponentGet();
	cout << "Component done." << endl;
	Bubble.FindGoodComp();
	Bubble.FindBadComponent();
	Bubble.WritePoint();
	//output(Bubble);
	system("PAUSE");

	return 0;
}