#include "BGraph.h"
#include <fstream>
#include<ctime>
#include<map>
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
int BGraph::GetNeighborLevel(const string& point_IDC, const string& nei_IDC)//未完全驗證
{
	int level = Level - 1;
	for (; level >= 0 && point_IDC[level] == nei_IDC[level]; level--);
	return level + 1;

}
void BGraph::SetNeighber(BPoint& B, const int& l)
{
	string Neighber_ID_Created = B.ID_Created;
	if (B.ID_Created[l - 2] < B.ID_Created[l - 1])//不確定對不對 需要驗證
	{
		Neighber_ID_Created[l - 1]--;
	}
	else
	{
		Neighber_ID_Created[l - 2]++;
	}
	swap(Neighber_ID_Created[l - 2], Neighber_ID_Created[l - 1]);
	B.Neighbor[l - 2].Point = &GetPointByCreateID(Neighber_ID_Created);
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
BPoint& BGraph::GetPoint(const string& ID)//用ID找點的物件
{
	return GetPointByCreateID(GetCreatedID(ID));
}

BPoint & BGraph::GetPointByCreateID(const string& ID)
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
BGraph::BGraph(const int& L)
{
	Level = L;
	BS.Create(Level);
	CreateGraph();
	CalculateValue();
}
BGraph::BGraph(const string& filename)
{
	ifstream fin(filename);
	fin >> Level;
	BS.Create(Level);
	CreateGraph();
	CalculateValue();
	AllStatusSet(fin);
}
void BGraph::SetTrustPoint(const string& filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "\"" + filename + "\" is not exist or can\'t open" << endl;
		return;
	}
	cout << "Detected \"" + filename + "\", Setting trust points......" << endl;
	int count;
	string s;
	fin >> count;
	if (count > 0)
	{
		Component.push_back(nullptr);
		Component.back().member.pop_back();
		Component.back().SetAsGood();
	}
	while (count--)
	{
		BComponent& BC = Component.back();
		fin >> s;
		BPoint& BP = GetPoint(s);
		BC.member.push_back(&BP);
		BP.Component_ID = &BC;
	}
	cout << "Setting done." << endl;
}
void BGraph::CalculateValue()
{
	int CN;
	switch (Level)
	{
	case 4:
		CN = 3;
		break;
	case 5:
		CN = 6;
		break;
	case 6:
		CN = 8;
		break;
	default:
		CN = 10;
		break;
	}
	int a = 3 * Level - 8 - CN;
	int b = CN;
	int c = 8 - 3 * Level + 2 * CN - static_cast<int>(Point.size());
	int max_comps = static_cast<int>(ceil((sqrt(b * b - 4 * a * c) - b) / (2 * a) - 1));
	k = Level - 1;//單次最少找出K個點
	T_UpperBound = static_cast<int>(ceil((Point.size() / (max_comps + 1)) - 1));
	T_LowerBound = static_cast<int>(floor((max_comps - 1) * (3 * Level - 8) - (max_comps - 2) * CN));
	PossibleBadSize = T_UpperBound;
}
void BGraph::CreateGraph()//產生點的呼叫
{
	Component.push_back(nullptr);//預留給孤立點的"元件"
	Component.front().member.clear();
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
	ofstream fout("broken.point");
	fout << num << endl;
	srand(static_cast<unsigned int>(time(nullptr)));
	cout << "Bad points:" << endl;
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
		cout << p->point->ID << endl;
		fout << p->point->ID << endl;
		num--;
	}
	fout.close();
	cout << "File \"broken.point\" saved." << endl;
}
void BGraph::ReadSetBroken()
{
	ifstream fin("broken.point");
	if (!fin.is_open())
	{
		cout << "Can'\t open file \"broken.point\"" << endl;
		return;
	}
	string BrokenID;
	int num;
	fin >> num;
	if (num > T_LowerBound)
	{
		cout << "Too many points! Only the first " << T_LowerBound << " will be set" << endl;
		num = T_LowerBound;
	}
	cout << "Bad points:" << endl;
	for (; num > 0; num--)
	{
		fin >> BrokenID;
		if (BrokenID.length() != Level)
		{
			cout << BrokenID << " is not a level " << Level << " point ID." << endl;
			continue;
		}
		GetPoint(BrokenID).IsBroken = true;
		cout << BrokenID << endl;
	}
}
void BGraph::Point_Symptom_Get(BPoint& p)//取得單一點完整症狀
{
	for (int a = 2; a < Level; a++)
	{
		for (int b = a + 1; b <= Level; b++)
		{
			if (p.IsBroken)
			{
				p.Neighbor[a - 2].Guess = false;//必定挑第一個點
				p.GoodStandard = &GetNeighbor(p, a);
				break;
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
				p.Neighbor[a - 2].Guess = rand() % 10 > 2 ? false : true;//隨機壞點症狀 產生位置在這裡
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
void BGraph::AllStatusSet(ifstream& fin)
{
	BPoint* BP = nullptr;
	string point, N1, N2;
	int guess;
	map<string, bool> temp;
	while (1)
	{
		fin >> point >> N1 >> N2;
		if (fin.eof()) return;
		fin >> guess;
		if (guess == 0)
		{
			if (BP == nullptr || BP->ID_Created != point)
			{
				BP = &GetPointByCreateID(point);
			}
			BP->Neighbor[GetNeighborLevel(point, N1) - 2].Guess = BP->Neighbor[GetNeighborLevel(point, N2) - 2].Guess = false;
		}
	}

}
void BGraph::All_Symptom_GetAndWrite()
{
	ofstream fout("symptom.all");
	fout << Level << endl;
	srand(static_cast<unsigned int>(time(nullptr)));
	bool ans = false;
	for (list<BPoint>::iterator it = Point.begin(); it != Point.end(); it++)
	{
		for (int a = 2; a < Level; a++)
		{
			for (int b = a + 1; b <= Level; b++)
			{
				BPoint& N1 = GetNeighbor(*it, a);
				BPoint& N2 = GetNeighbor(*it, b);
				if (it->IsBroken)
				{
					//ans = (rand() % 10 > 5) ? true : false;
					ans = true;//暫時的
				}
				else
				{
					ans = N1.IsBroken || N2.IsBroken;
				}
				fout << it->ID_Created << " " << N1.ID_Created << " " << N2.ID_Created << " " << ans << endl;
			}
		}
	}
	cout << "All symptom saved to file \"symptom.all\"" << endl;
}
void BGraph::ComponentGet()//與f_comp相同 但是少了取得症狀的步驟
{
	if (Component.size() == 2)//有前一輪的好點
	{
		list<BPoint*> todolist = Component.back().member;
		while (todolist.size() > 0)
		{
			BPoint& head = *todolist.front();
			todolist.pop_front();

			for (int j = 2; j <= Level; j++)//檢查過去
			{
				if (head.Neighbor[j - 2].Guess == false)//好點
				{
					BPoint& JPoint = GetNeighbor(head, j);
					if (JPoint.Component_ID == nullptr&&JPoint.Neighbor[j - 2].Guess == false)
					{
						JPoint.Component_ID = head.Component_ID;
						JPoint.Component_ID->member.push_back(&JPoint);
						todolist.push_back(&JPoint);
					}
				}
			}
		}
	}
	for (list<BPoint>::iterator i = Point.begin(); i != Point.end(); i++)
	{
		if (i->Component_ID == nullptr)
		{
			list<BPoint*> todolist = { &*i };
			Component.push_back(&*i);
			i->Component_ID = &Component.back();
			while (todolist.size() > 0)
			{
				BPoint& head = *todolist.front();
				todolist.pop_front();

				for (int j = 2; j <= Level; j++)//檢查過去
				{
					if (head.Neighbor[j - 2].Guess == false)//好點
					{
						BPoint& JPoint = GetNeighbor(head, j);
						if (JPoint.Component_ID != nullptr) continue;
						//Point_Symptom_Get(JPoint);
						if (JPoint.Component_ID == nullptr&&JPoint.Neighbor[j - 2].Guess == false)
						{
							JPoint.Component_ID = head.Component_ID;
							JPoint.Component_ID->member.push_back(&JPoint);
							todolist.push_back(&JPoint);
							LiarCheck(JPoint);
						}
					}
				}
				head.IsIsolated = true;
				for (int j = 2; j <= Level; j++)
				{
					if (head.Neighbor[j - 2].Guess == false)
					{
						head.IsIsolated = false;
						break;
					}
				}
			}
			if (Component.back().member.size() == 1 && i->IsIsolated)//清掉孤立元件 應該是這樣做
			{
				i->Component_ID = &Component.front();
				i->Component_ID->member.push_back(&*i);
				Component.pop_back();
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