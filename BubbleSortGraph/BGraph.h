#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;
#ifndef BGRAPH_H
#define BGRAPH_H

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
class BPoint//可能可以改用map做
{
public:
	BPoint();
	BPoint(const string&);
	void ConvertToID();
	void Create_Neighbor();
	string ID_Created;
	string ID;
	list<BPoint*>* Component_ID=NULL;
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
	BStruct();
	BStruct(int);
	void Set_Point(BPoint&);
	void Create(int);
	int level;
	BPoint* point = NULL;
	vector<BStruct> next;
};
class BGraph
{
public:
	BGraph(int);
	void CreateGraph();
	BPoint& GetPoint(string);
	void SetBroken(list<string>&);
	void Symptom_Get();
	void f_comp();

	int Level;
	list<BPoint> Point;
	BStruct BS;
	list<list<BPoint*>> Component;
};
void prowhypoint(int, int, list<string> &);
void Create(int, string, list<BPoint> &, BStruct &);
#endif // BGRAPH_H

