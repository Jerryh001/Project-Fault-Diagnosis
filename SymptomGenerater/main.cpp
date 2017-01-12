#include<iostream>
#include"BGraph.h"
int main()
{
	int level = 0;
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
	int broken;
	while (1)
	{
		cout << "If you want to set broken points manually from file \"broken.point\", input a negative number." << endl;
		cout << "Otherwise, input a number to set BubbleSort Graph broken point randomly(at most " << bubble.T_LowerBound << " Points):";
		cin >> broken;
		if (broken < 0)
		{
			cout << "Setting Broken points from file, please wait." << endl;
			bubble.ReadSetBroken();
			break;
		}
		else if (broken > bubble.T_LowerBound)
		{
			cout << "Too large, please try again!" << endl;
		}
		else
		{
			cout << "Setting Broken points, please wait." << endl;
			bubble.RandomSetBroken(broken);
			break;
		}
	}
	cout << "Starting Create Symptom......" << endl;
	bubble.All_Symptom_GetAndWrite();
	cout << "All Done!" << endl;
	system("pause");
}