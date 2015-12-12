﻿#include<iostream>
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
	//int com_ID = 1;//temp
	for (list<BComponent>::const_iterator i = ++Bubble.Component.begin(); i != Bubble.Component.end(); i++)//顯示猜測結果
	{
		cout << "Component " << i->id << " Contain the following Point(s):" << endl;
		for (list<BPoint* > ::const_iterator j = i->member.begin(); j != i->member.end(); j++)
		{
			cout << "	Point " + (*j)->ID << endl;
		}
		cout << "...Ans Contain the following Isolated Point(s):" << endl;
		if (i->Sur_Point.size() == 0)
		{
			cout << "Nope" << endl;
		}
		for (list<BPoint* > ::const_iterator j = i->Sur_Point.begin(); j != i->Sur_Point.end(); j++)
		{
			cout << "	Point " + (*j)->ID << endl;
		}
		if (i->member.size() + i->Sur_Point.size() >= Bubble.t*(Bubble.Level - 1) / (Bubble.Level - 3) && !i->Is_Link())//不相鄰
		{
			cout << "^^^^^^^This component is Fault-Free.^^^^^^^^^^^" << endl;
		}
	}
	cout.close();
	system("start output.txt");
}
vector<BStruct> Sub_B;
int main()
{
	
	int Level = 6;//階層數
	int BrokenNum = 40;//壞點數
	BGraph Bubble(Level);//圖
	GetSubStruct(Bubble.BS, Sub_B);
	Subgraph Sub_G(Sub_B[0]);


	system("PAUSE");
	list<string> pro;//壞點ID
	//pro.push_back("1111");
	prowhypoint(Level, BrokenNum, pro);
	Bubble.SetBroken(pro);
	Bubble.Symptom_Get();

	Bubble.f_comp();
	Bubble.FindGoodComp();
	output(Bubble);
	system("PAUSE");
	return 0;
}