#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;
#include "BGraph.h"
int main()
{
	ofstream cout("output.txt");
	int Level = 6;//階層數
	int BrokenNum = 10;//壞點數
	BGraph Bubble(Level);//圖
	list<string> pro;//壞點ID
	//pro.push_back("1111");
	prowhypoint(Level, BrokenNum, pro);
	Bubble.SetBroken(pro);
	Bubble.Symptom_Get();
	/*for (list<BPoint>::iterator i = Bubble.Point.begin(); i != Bubble.Point.end(); i++)//顯示猜測結果
	{
		for (vector<Stauts>::iterator j = i->Neighbor.begin(); j != i->Neighbor.end(); j++)
		{
			//cout << "Point " + i->ID + " consider that point " + j->ID + " is " + (j->Guess ? "Absolutely BAD" : "Maybe GOOD") << endl;
		}
	}*/
	Bubble.f_comp();
	int com_ID = 0;//temp
	for (list<list<BPoint*>>::iterator i = Bubble.Component.begin(); i != Bubble.Component.end(); i++,com_ID++)//顯示猜測結果
	{
		cout << "Component " << com_ID << " Contain the following Point(s):" << endl;
		for (list<BPoint* > ::iterator j = i->begin(); j != i->end(); j++)
		{
			cout << "Point " + (*j)->ID << endl;
		}
	}
	cout.close();
	system("start output.txt");
	system("PAUSE");
	return 0;
}