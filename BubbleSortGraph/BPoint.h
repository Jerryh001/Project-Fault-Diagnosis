#include<iostream>
#include<string>
#include<vector>
using namespace std;
#ifndef BPOINT_H
#define BPOINT_H
struct Symptom//點a和b的症狀 壞=true
{
	string a;
	string b;
	bool value;
};
struct Stauts//白箭頭與黑箭頭 黑=true
{
	string ID;
	bool Guess;
};
class BPoint
{
public:
	BPoint();
	BPoint(const string&);
	void ConvertToID();
	void Create_Neighbor();
	~BPoint();
	string ID_Created;
	string ID;
	int Component_ID;
	bool IsBroken;
	int Level;
	bool IsIsolated;
	vector<Symptom> ComparedResult;
	vector<Stauts> Neighbor;
};
string GetCreatedID(string);
class BStruct
{
public:
	BStruct(int);
	~BStruct();
	void Set_Point(BPoint&);
	int level;
	BPoint* point=NULL;
	vector<BStruct> next;
};
BPoint& GetPoint(string, BStruct&);
void prowhypoint(int n, int c, vector<string> &p);
#endif // BPOINT_H

