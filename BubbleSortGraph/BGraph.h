#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
#ifndef BGRAPH_H
#define BGRAPH_H
////////////////////
class BGraph;
class BPoint;
class BStruct;
class BComponent;
class Subgraph;
////////

struct Symptom//點a和b的症狀 壞=true
{
	string a;
	string b;
	bool value;
};
struct Stauts//白箭頭與黑箭頭 黑=true
{
	//string ID;
	BPoint* Point;
	bool Guess;
};
enum ComponentStatus { Undefined = -1, Good = 0, Bad = 1 };
class BComponent
{
	ComponentStatus Status;
public:
	int id;
	list<BPoint*> member;//這個component裡面有哪些點
	list<BPoint*> Sur_Point;//這個component周圍的孤立點
	BComponent(BPoint*);
	void SetAsGood();
	void SetAsBad();
	ComponentStatus GetStatus() const;
	bool Is_Link()const;
};
class BPoint
{
public:
	BPoint();
	BPoint(const string&);
	void ConvertToID();
	void Create_Neighbor();

	string ID_Created;
	string ID;
	BComponent* Component_ID = nullptr;
	bool IsBroken;
	int Level;
	bool IsIsolated;
	BPoint* GoodStandard = nullptr;
	//vector<Symptom> ComparedResult;//貌似沒用到
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
	BPoint* point = nullptr;
	vector<BStruct> next;
};

class BGraph
{
public:
	int Level;//階層
	//int t;
	int T_UpperBound;
	int T_LowerBound;
	int k;
	int PossibleBadSize;
	list<BPoint> Point;//點
	BStruct BS;//階層狀結構
	list<BComponent> Component;

	//元件
	BGraph();
	BGraph(const int&);
	BGraph(const string&);
	void SetTrustPoint(const string&);
	void CalculateValue();
	void CreateGraph();//初始化
	BPoint& GetPoint(const string&);//用ID取得點物件
	BPoint& GetPointByCreateID(const string&);
	BPoint& GetNeighbor(BPoint&, const int&);
	int GetNeighborLevel(const string&, const string&);
	void SetNeighber(BPoint&, const int&);
	void SetBroken(list<string>&);//設定壞點
	void ReadSetBroken();
	void RandomSetBroken(int);//設定壞點
	void Point_Symptom_Get(BPoint&);
	void AllStatusSet(ifstream&);
	//取得單一點症狀
	void All_Symptom_GetAndWrite();
	void ComponentGet();
	void f_comp();//連接元件
	void FindGoodComp();//找好元件
	void LiarCheck(BPoint&);
	void FindBadComponent();
	void WritePoint();
};
void GetSubStruct(const BStruct& Bubble, vector<BStruct>& b);//複製原圖結構到子圖(複製結構)
void prowhypoint(int, int, list<string> &);
void Create(int, string, list<BPoint> &, BStruct &);
#endif // BGRAPH_H

