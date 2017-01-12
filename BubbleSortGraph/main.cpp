#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<cctype>
using namespace std;
#include "BGraph.h"
vector<BStruct> Sub_B;
int main()
{
	cout << "Start creating graph and reading symptom." << endl;
	BGraph Bubble("symptom.all");
	cout << "All symptom readed." << endl;
	cout << "Do you want to use \"good.point\" from previous round?(y/N):";
	char c;
	cin.get(c);
	if (tolower(c) == 'y')
	{
		Bubble.SetTrustPoint("good.point");
	}
	cout << "Finding Component." << endl;
	Bubble.ComponentGet();
	cout << "Component done." << endl;
	Bubble.FindGoodComp();
	Bubble.FindBadComponent();
	Bubble.WritePoint();
	system("PAUSE");

	return 0;
}