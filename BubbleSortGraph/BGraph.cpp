#include "BGraph.h"
#include <fstream>
#include<ctime>
BPoint::BPoint()
{
	IsBroken = false;
	Level = 0;
	IsIsolated = false;
}
BPoint::BPoint(const string &ID_C)
{
	IsBroken = false;
	Level = 0;
	IsIsolated = false;
	ID_Created = ID_C;
	Level = static_cast<int>(ID_C.length());
	ConvertToID();
	Create_Neighbor();
}
void BPoint::Create_Neighbor()//記錄相鄰點
{
	Neighbor.clear();
	Neighbor.resize(Level - 1, { nullptr,true });
}
BPoint& BGraph::GetNeighbor(BPoint& B, const int& l)//2<=l<=Level
{
	if (B.Neighbor[l - 2].Point == nullptr)
	{
		SetNeighber(B, l);
	}
	return *B.Neighbor[l - 2].Point;
}
void BGraph::SetNeighber(BPoint& B, const int& l)
{
	int i = Level - 1;
	BStruct *p = &BS;
	while (i >= 0)
	{
		if (i == l - 1)
		{
			if (B.ID_Created[i - 1] < B.ID_Created[i])
			{
				p = &p->next[B.ID_Created[i - 1] - '1'];
				p = &p->next[B.ID_Created[i] - '1' - 1];
			}
			else
			{
				p = &p->next[B.ID_Created[i - 1] - '1' + 1];
				p = &p->next[B.ID_Created[i] - '1'];
			}
			i -= 2;
		}
		else
		{
			p = &p->next[B.ID_Created[i] - '1'];
			i--;
		}
	}
	B.Neighbor[l - 2].Point = p->point;
}
void BPoint::ConvertToID()//創造用ID轉一般ID
{
	ID = "";
	string poto;
	for (int i = Level; i > 0; i--)
	{
		poto += char(i + '0');
	}
	string Temp_Created = ID_Created;
	while (poto.length() > 0)
	{
		int current = *(Temp_Created.rbegin()) - '1';
		ID = poto.at(current) + ID;
		poto.erase(poto.begin() + current);
		Temp_Created.pop_back();
	}
}
string GetCreatedID(string ID)//一般ID轉創造用ID
{
	string C_ID;
	string poto;
	int Level = static_cast<int>(ID.length());
	for (int i = Level; i > 0; i--)
	{
		poto += char(i + '0');
	}
	while (poto.length() > 0)
	{
		int current = static_cast<int>(poto.find(ID.back()));
		C_ID = char(current + '1') + C_ID;
		poto.erase(poto.begin() + current);
		ID.pop_back();
	}
	return C_ID;
}
BPoint& BGraph::GetPoint(string ID)//用ID找點的物件
{
	ID = GetCreatedID(ID);
	BStruct *p = &BS;
	for (int i = Level - 1; i >= 0; i--)
	{
		p = &p->next.at(ID[i] - '1');
	}
	return *p->point;
}

BPoint & BGraph::GetPoint2(string ID)
{
	BStruct *p = &BS;
	for (int i = Level - 1; i >= 0; i--)
	{
		p = &p->next[ID[i] - '1'];
	}
	return *p->point;
}



BStruct::BStruct()
{

}
BStruct::BStruct(int L)
{
	Create(L);
}
void BStruct::Set_Point(BPoint &B)
{
	point = &B;
}

void BStruct::Create(int l)//產生結構(空)
{
	next.clear();
	level = l;
	for (int i = 0; i < level; i++)
	{
		next.push_back(level - 1);
	}
}
BGraph::BGraph()
{
}
BGraph::BGraph(int L)
{
	Level = L;
	BS.Create(Level);
	CreateGraph();
	int a = 3 * Level - 10;
	int c = 12 - 3 * Level - Point.size();
	int max_comps = floor((sqrt(4 - 4 * a*c) - 2) / (2 * a));
	k = Level - 1;//單次最少找出K個點
	T_UpperBound = Point.size() / (max_comps + 1);
	T_LowerBound = (max_comps - 1)*(3 * Level - 10) + 2;
	PossibleBadSize = T_UpperBound+1;

}
void BGraph::CreateGraph()//產生點的呼叫
{
	Create(Level, "", Point, BS);
}
void Create(int n, string tail, list<BPoint> &BP, BStruct &BS)//遞迴產生點及結構
{
	for (int i = 1; i <= n; i++)
	{
		Create(n - 1, char('0' + i) + tail, BP, BS.next.at(i - 1));
	}
	if (n == 0) {
		BP.push_back(tail);
		BS.Set_Point(BP.back());
	}
}
void BGraph::SetBroken(list<string> &P)//將壞點放入
{
	for (list<string>::iterator i = P.begin(); i != P.end(); i++)
	{
		GetPoint(BPoint(*i).ID).IsBroken = true;
	}
}
void BGraph::RandomSetBroken(int num)
{
	srand(time(NULL));
	cout << "bad point:";
	while (num)
	{
		BStruct *p = &BS;
		for (int i = Level - 1; i >= 0; i--)
		{
			p = &p->next.at(rand() % (i + 1));
		}
		if (p->point->IsBroken == true)
		{
			continue;
		}
		p->point->IsBroken = true;
		//cout << p->point->ID << " ";
		num--;
	}
}
void BGraph::ReadSetBroken(int num)
{
	ifstream fin("whypointfile.txt");
	string BrokenID;
	cout << "bad point:";
	while (fin >> BrokenID && num)
	{
		GetPoint(BrokenID).IsBroken = true;
		cout << BrokenID << " ";
		num--;
	}
}
void BGraph::Point_Symptom_Get(BPoint& p)//取得單一點完整症狀
{
	int mode = 5;//5=一般壞點 1=在座的各位都是壞點 8=沒甚麼壞的點
	//BPoint* GoodStandard = NULL;
	for (int a = 2; a < Level; a++)
	{
		for (int b = a + 1; b <= Level; b++)
		{
			if (p.IsBroken)
			{
				if (GetNeighbor(p, a).IsBroken)
				{
					p.Neighbor[a - 2].Guess = false;
					p.GoodStandard = &GetNeighbor(p, a);
					break;
				}
			}
			else
			{
				if (GetNeighbor(p, a).IsBroken || GetNeighbor(p, b).IsBroken)
				{
					continue;
				}
				else
				{
					p.Neighbor[a - 2].Guess = false;
					p.GoodStandard = &GetNeighbor(p, a);
					break;
				}
			}
		}
	}
	for (int a = 2; a <= Level&&p.GoodStandard != nullptr; a++)
	{
		if (&GetNeighbor(p, a) == p.GoodStandard)
		{
			continue;
		}
		else
		{
			if (p.IsBroken)
			{
					p.Neighbor[a - 2].Guess = false;
			}
			else
			{
				if (GetNeighbor(p, a).IsBroken || p.GoodStandard->IsBroken)
				{
					continue;
				}
				else
				{
					p.Neighbor[a - 2].Guess = false;
				}
			}
		}
	}
}
BComponent::BComponent(BPoint *B)
{
	member.push_back(B);
	id = 0;
	Status = Undefined;
}
void BComponent::SetAsGood()
{
	Status = Good;
}
void BComponent::SetAsBad()
{
	Status = Bad;
}
ComponentStatus BComponent::GetStatus() const
{
	return Status;
}
bool BComponent::Is_Link()const
{
	for (list<BPoint*>::const_iterator i = Sur_Point.begin(); i != Sur_Point.end(); i++)
	{
		for (list<BPoint*>::const_iterator j = Sur_Point.begin(); j != Sur_Point.end(); j++)
		{
			if (i == j)continue;
			for (vector<Stauts>::iterator k = (*i)->Neighbor.begin(); k != (*i)->Neighbor.end(); k++)
			{
				if (k->Point->ID == (*j)->ID)//maybe?
					return true;
			}
		}
	}
	return false;
}
/*做local*/
int Unitlevel = 4;

void GetSubStruct(const BStruct& Bubble, vector<BStruct>& b)
{
	if (Bubble.level > Unitlevel)
	{
		for (int i = 0; i < Bubble.next.size(); i++)
		{
			GetSubStruct(Bubble.next[i], b);
		}
	}
	else if (Bubble.level == Unitlevel)
	{
		b.push_back(Bubble);
	}
}

Subgraph::Subgraph(BStruct &S, const int& l)
{
	/*t,k有待修正*/
	Level = Unitlevel;
	k = l - 1;//單次最少找出K個點
	T_LowerBound = T_UpperBound = round(pow(2, l - 2))*(l - 3) / (l - 1);
	BS = S;
	CopyGraphPoint(S.level, Point, BS);
}

void Subgraph::CopyGraphPoint(int n, list<BPoint> &BP, BStruct &BS)//因為Subgraph無法直接繼承BGraph的點 所以再建一個list<BPoint> 把點複製過來
{
	for (int i = 1; i <= n; i++)
	{
		CopyGraphPoint(n - 1, BP, BS.next.at(i - 1));
	}
	if (n == 0) {
		BP.push_back(*BS.point);
		BS.point = &BP.back();
		string club_ID = string(BP.back().ID, Unitlevel);
		for (vector<Stauts>::iterator i = BP.back().Neighbor.begin(); i != BP.back().Neighbor.end();)
		{
			string My_club = string(i->Point->ID, Unitlevel);
			if (My_club != club_ID)
			{
				i = BP.back().Neighbor.erase(i);//接住下一個的位子 不要讓iterator跑掉
			}
			else
				i++;
		}
	}
}