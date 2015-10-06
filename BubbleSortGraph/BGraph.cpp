#include "BGraph.h"
BPoint::BPoint()
{
	Component_ID = 0;
	IsBroken = false;
	Level = 0;
	IsIsolated = false;
}
BPoint::BPoint(const string &ID_C)
{
	Component_ID = 0;
	IsBroken = false;
	Level = 0;
	IsIsolated = false;
	ID_Created = ID_C;
	Level =ID_C.length();
	ConvertToID();
	Create_Neighbor();
}
void BPoint::Create_Neighbor()//記錄相鄰點
{
	//cout<<"Point"<<ID<<endl;
	Neighbor.clear();
	for (int i = 0; i < Level - 1; i++)
	{
		swap(ID[i], ID[i + 1]);
		Neighbor.push_back({ ID,true });
		//cout<<ID_Temp<<"is Neighbor"<<endl;
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
	int Level = ID.length();
	for (int i = Level; i > 0; i--)
	{
		poto += char(i + '0');
	}
	while (poto.length() > 0)
	{
		int current = poto.find(ID.back());
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
	for (string::reverse_iterator i = ID.rbegin(); i != ID.rend(); i++)
	{
		//cout << *i;
		p = &p->next.at(*i - '1');
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
BGraph::BGraph(int L)
{
	Level = L;
	k = Level - 1;
	t = round(pow(2, Level - 2))*(Level - 3) / (Level - 1);
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
		//cout << tail << " " << BP.rbegin()->ID << " " << GetCreatedID(BP.rbegin()->ID) << endl;
	}
}
void BGraph::SetBroken(list<string> &P)//將壞點放入
{
	for (list<string>::iterator i = P.begin(); i != P.end(); i++)
	{
		GetPoint(BPoint(*i).ID).IsBroken = true;
	}
}
void BGraph::Symptom_Get()//取得完整症狀
{
	for (list<BPoint>::iterator i = Point.begin(); i != Point.end(); i++)
	{
		for (vector<Stauts>::iterator a = i->Neighbor.begin(); a != i->Neighbor.end() - 1; a++)
		{
			for (vector<Stauts>::iterator b = a + 1; b != i->Neighbor.end(); b++)
			{
				i->ComparedResult.push_back({ a->ID, b->ID, false });
				int mode = 5;//5=一般壞點 1=在座的各位都是壞點 8=沒甚麼壞的點
				if (i->IsBroken && (rand() % 10) > mode)
				{
					i->ComparedResult.back().value = true;
				}
				else if (GetPoint(a->ID).IsBroken || GetPoint(b->ID).IsBroken)
				{
					i->ComparedResult.back().value = true;
				}
				else
				{
					a->Guess = false;
					b->Guess = false;
				}
				//cout << "symptom " << i->ComparedResult.rbegin()->a << " and " << i->ComparedResult.rbegin()->b << " compared by " << i->ID << " is " << i->ComparedResult.rbegin()->value << endl;
			}
		}
	}
}