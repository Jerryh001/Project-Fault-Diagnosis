#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
using namespace std;
int main()
{
	map<string, int> count;
	ifstream ansin("broken.point");
	ifstream guessin("bad.point");
	if (!ansin.is_open())
	{
		cout << "Can\'t open file\"broken.point\"" << endl;
		return 0;
	}
	if (!guessin.is_open())
	{
		cout << "Can\'t open file\"bad.point\"" << endl;
		return 0;
	}
	int num;
	string s;
	ansin >> num;
	while (num--)
	{
		ansin >> s;
		count[s]++;
	}
	ansin.close();
	guessin >> num;
	while (num--)
	{
		guessin >> s;
		count[s]--;
	}
	guessin.close();
	
	stringstream tempout;
	num = 0;
	for (map<string, int>::iterator it = count.begin(); it != count.end(); it++)
	{
		if (it->second == 0)
		{
			continue;
		}
		else if(it->second>0)
		{
			tempout << it->first << endl;
			num++;
		}
		else
		{
			cout << "Point " + it->first + "IS NOT a broken point!!!" << endl;
		}
	}
	if (num == 0)
	{
		cout << "All broken point founded,congratulations!" << endl;
	}
	else
	{
		ofstream ansout("broken.point");
		ansout << num << endl;
		ansout << tempout.str();
		cout << "Replaced with new \"broken.point\"" << endl;
		cout << "To start new round,send it to SymptomGenerator again" << endl;
	}
}