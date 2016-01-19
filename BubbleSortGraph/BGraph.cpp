#include "BGraph.h"
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
	for (int i = 0; i < Level - 1; i++)
	{
		swap(ID[i], ID[i + 1]);
		Neighbor.push_back({ ID,true });
		swap(ID[i], ID[i + 1]);
	}
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
	k = Level - 1;//單次最少找出K個點
	t = static_cast<int>(round(pow(2, Level - 2))*(Level - 3) / (Level - 1));
	BS.Create(Level);
	CreateGraph();
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
void BGraph::Point_Symptom_Get(BPoint& p)//取得單一點完整症狀
{
	int mode = 1;//5=一般壞點 1=在座的各位都是壞點 8=沒甚麼壞的點
	//BPoint* GoodStandard = NULL;
	for (vector<Stauts>::iterator a = p.Neighbor.begin(); (p.GoodStandard == NULL) && a != p.Neighbor.end() - 1; a++)
	{
		for (vector<Stauts>::iterator b = a + 1; b != p.Neighbor.end(); b++)
		{
			if (p.IsBroken)
			{
				if (rand() % 10 < mode)
				{
					a->Guess = false;
					p.GoodStandard = &GetPoint(a->ID);
					break;
				}
			}
			else
			{
				if (GetPoint(a->ID).IsBroken || GetPoint(b->ID).IsBroken)
				{
					continue;
				}
				else
				{
					a->Guess = false;
					p.GoodStandard = &GetPoint(a->ID);
					break;
				}
			}
		}
	}
	for (vector<Stauts>::iterator a = p.Neighbor.begin(); (p.GoodStandard != NULL) && a != p.Neighbor.end() - 1; a++)
	{
		if (a->ID == p.GoodStandard->ID)
		{
			continue;
		}
		else
		{
			if (p.IsBroken)
			{
				if (rand() % 10 < mode)
				{
					a->Guess = false;
				}
			}
			else
			{
				if (GetPoint(a->ID).IsBroken || p.GoodStandard->IsBroken)
				{
					continue;
				}
				else
				{
					a->Guess = false;
				}
			}
		}
	}
}
void BGraph::Point_Symptom_Discover(BPoint& p)//取得單一點中 未取得的症狀(只能在f_camp中呼叫)
{
	int mode = 1;//5=一般壞點 1=在座的各位都是壞點 8=沒甚麼壞的點
	BPoint* GoodStandard = NULL;
	for (vector<Stauts>::iterator a = p.Neighbor.begin(); (GoodStandard == NULL) && a != p.Neighbor.end() - 1; a++)
	{
		for (vector<Stauts>::iterator b = a + 1; b != p.Neighbor.end(); b++)
		{
			if (GetPoint(a->ID).Component_ID == p.Component_ID)//a和p屬於同一Component
			{
				GoodStandard = &GetPoint(a->ID);
				break;
			}
			if (p.IsBroken)
			{
				if (rand() % 10 < mode)
				{
					a->Guess = false;
					GoodStandard = &GetPoint(a->ID);
					break;
				}
			}
			else
			{
				if (GetPoint(a->ID).IsBroken || GetPoint(b->ID).IsBroken)
				{
					continue;
				}
				else
				{
					a->Guess = false;
					GoodStandard = &GetPoint(a->ID);
					break;
				}
			}
		}
	}
	for (vector<Stauts>::iterator a = p.Neighbor.begin(); a != p.Neighbor.end() - 1; a++)
	{
		if (&GetPoint(a->ID) == GoodStandard|| GetPoint(a->ID).Component_ID==p.Component_ID)
		{
			continue;
		}
		else
		{
			if (p.IsBroken)
			{
				if (rand() % 10 < mode)
				{
					a->Guess = false;
				}
			}
			else
			{
				if (GetPoint(a->ID).IsBroken || GoodStandard->IsBroken)
				{
					continue;
				}
				else
				{
					a->Guess = false;
				}
			}
		}
	}
}
BComponent::BComponent(BPoint *B)
{
	member.push_back(B);
	id = 0;
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
				if (k->ID == (*j)->ID)//maybe?
					return true;
			}
		}
	}
	return false;
}
/*做local*/
int Unitlevel = 4;

void GetSubStruct(const BStruct& Bubble,vector<BStruct>& b)
{
	if (Bubble.level > Unitlevel)
	{
		for (int i = 0; i < Bubble.next.size(); i++)
		{
			GetSubStruct(Bubble.next[i], b);
		}
	}
	else if (Bubble.level==Unitlevel)
	{
		b.push_back(Bubble);
	}
}

Subgraph::Subgraph(BStruct &S,const int& l)
{
	/*t,k有待修正*/
	Level = Unitlevel;
	k = l - 1;//單次最少找出K個點
	t = round(pow(2, l - 2))*(l - 3) / (l - 1);
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
		string club_ID = string(BP.back().ID, Unitlevel);
		for (vector<Stauts>::iterator i = BP.back().Neighbor.begin(); i!=BP.back().Neighbor.end();)
		{
			string My_club=string(i->ID, Unitlevel);
			if (My_club != club_ID)
			{
				i=BP.back().Neighbor.erase(i);//接住下一個的位子 不要讓iterator跑掉
			}
			else
				i++;
		}
	}
}