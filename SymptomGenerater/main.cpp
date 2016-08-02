#include<iostream>
#include"BGraph.h"
int main()
{
	int level=0;
	while (level < 4)
	{
		cout << "Set BubbleSort Graph Level(at least 4):";
		cin >> level;
		if (level < 4)
		{
			cout << "Too small, please Try again!" << endl;
		}
	}
	cout << "Initializing a level " << level << " BubbleSort Graph, please wait." << endl;
	BGraph bubble(level);
	cout << "Initialized." << endl;
	int broken=INT_MAX;
	while (broken<0 || broken>bubble.T_LowerBound)
	{
		cout << "Set BubbleSort Graph Broken Point amount(at most "<< bubble.T_LowerBound<<" Points):";
		cin >> broken;
		if (broken<0)
		{
			cout << "Of course it can\'t smaller than ZERO, please try again!" << endl;
		}
		else if (broken > bubble.T_LowerBound)
		{
			cout << "Too large, please try again!" << endl;
		}
	}
	cout << "Setting Broken points, please wait." << endl;
	bubble.RandomSetBroken(broken);
	cout << "Starting Create Symptom......" << endl;
	bubble.All_Symptom_GetAndWrite();
	cout << "All Done!" << endl;
	system("pause");
}