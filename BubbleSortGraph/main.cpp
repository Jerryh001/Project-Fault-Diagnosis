#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;
#include "BGraph.h"
int main()
{
	//ofstream cout("output.txt");
	int Level = 4;//階層數
	int BrokenNum = 2;//壞點數
	BGraph Bubble(Level);//圖
	list<string> pro;//壞點ID
	prowhypoint(Level, BrokenNum, pro);
	Bubble.SetBroken(pro);
	Bubble.Symptom_Get();
	for (list<BPoint>::iterator i = Bubble.Point.begin(); i != Bubble.Point.end(); i++)//顯示猜測結果
	{
		for (vector<Stauts>::iterator j = i->Neighbor.begin(); j != i->Neighbor.end(); j++)
		{
			cout << "Point " + i->ID + " consider that point " + j->ID + " is " + (j->Guess ? "Absolutely BAD" : "Maybe GOOD") << endl;
		}
	}
	Bubble.f_comp();
	for (list<BPoint>::iterator i = Bubble.Point.begin(); i != Bubble.Point.end(); i++)//顯示猜測結果
	{
		cout << "Point " + i->ID + " Component_ID=  " << i->Component_ID << endl;
	}
	system("PAUSE");
	return 0;
}

