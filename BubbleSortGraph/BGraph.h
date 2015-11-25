#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;
#ifndef BGRAPH_H
#define BGRAPH_H
////////////////////
class BGraph;
class BPoint;
class BStruct;
class BComponent;
////////

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
	bool operator==(Stauts two)
	{
		return (ID == two.ID&&Guess == two.Guess);
	}
};
class BComponent
{
public:
	int id;
	list<BPoint*> member;//這個component裡面有哪些點
	list<BPoint*> Sur_Point;//這個component周圍的孤立點
	BComponent(BPoint*);
	bool Is_Link()const;
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
	BComponent* Component_ID=NULL;
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
	void CreateGraph();//初始化
	BPoint& GetPoint(string);//用ID取得點物件
	void SetBroken(list<string>&);
	void Point_Symptom_Get(BPoint&);//取得單一點症狀
	//設定壞點
	void f_comp();//連接元件
	void FindGoodComp();//找好元件
	int Level;//階層
	int t;
	int k;
	list<BPoint> Point;//點
	BStruct BS;//階層狀結構
	list<BComponent> Component;//元件
};

void prowhypoint(int, int, list<string> &);
void Create(int, string, list<BPoint> &, BStruct &);
#endif // BGRAPH_H

