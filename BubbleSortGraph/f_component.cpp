#include "BGraph.h"
#include<map>
#include<fstream>
#include<sstream>
void BGraph::f_comp()
{
	for (list<BPoint>::iterator i = Point.begin(); i != Point.end(); i++)
	{
		if (i->Component_ID == nullptr)
		{
			Point_Symptom_Get(*i);
			list<BPoint*> todolist = { &*i };
			Component.push_back(&*i);
			i->Component_ID = &Component.back();
			Component.back().id = (++Component.rbegin())->id + 1;
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
						Point_Symptom_Get(JPoint);
						if (JPoint.Neighbor[j - 2].Guess == false)
						{
							JPoint.Component_ID = head.Component_ID;
							JPoint.Component_ID->member.push_back(&JPoint);
							todolist.push_back(&JPoint);
							LiarCheck(JPoint);
						}
					}
				}
			}
			i->IsIsolated = true;
			for (int j = 2; j <= Level; j++)
			{
				if (i->Neighbor[j - 2].Guess == false)
				{
					i->IsIsolated = false;
					break;
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
void BGraph::FindGoodComp()
{
	for (list<BPoint*>::iterator j = Component.front().member.begin(); j != Component.front().member.end(); j++)//每個孤立點
	{
		BPoint &B = **j;//孤立點本身
		map<int, int> complist;
		for (int k = 2; k <= Level; k++)
		{
			BPoint &KPoint = GetNeighbor(B, k);
			if (KPoint.Neighbor[k - 2].Guess == false)
			{
				int id = KPoint.Component_ID->id;
				if (complist[id] > 0)
				{
					KPoint.Component_ID->SetAsBad();
				}
				else
				{
					KPoint.Component_ID->Sur_Point.push_back(&B);//加入
					complist[id]++;
				}
			}
		}
	}
	for (list<BComponent>::iterator it = ++Component.begin(); it != Component.end(); it++)
	{
		if (it->member.size() > PossibleBadSize)
		{
			it->SetAsGood();
		}
		else if (it->member.size() + it->Sur_Point.size() > PossibleBadSize)
		{
			if (it->Is_Link())
			{
				it->SetAsBad();
			}
			else
			{
				it->SetAsGood();
			}
		}
	}
}

void BGraph::LiarCheck(BPoint& p)
{
	for (int i = 2; i <= Level; i++)
	{
		if (GetNeighbor(p, i).Component_ID == p.Component_ID)
		{
			if (p.Component_ID->GetStatus() != Good && (p.Neighbor[i - 2].Guess == true || GetNeighbor(p, i).Neighbor[i - 2].Guess == true))
			{
				p.Component_ID->SetAsBad();
				cout << "FOUND!!" << endl;
				return;
			}
		}
	}
}

void BGraph::FindBadComponent()
{
	for (list<BComponent>::iterator it = ++Component.begin(); it != Component.end(); it++)
	{
		if (it->GetStatus() == Good)
		{
			for (list<BPoint* > ::iterator p = it->member.begin(); p != it->member.end(); p++)//元件
			{
				for (int i = 2; i <= Level; i++)
				{
					BPoint& N = GetNeighbor(**p, i);
					if ((*p)->Neighbor[i - 2].Guess == true&& N.Component_ID->GetStatus() != Good)//無指向
					{
						if (N.Component_ID == &Component.front())
						{
							N.IsBroken = true;
						}
						else
						{
							N.Component_ID->SetAsBad();
						}
					}
				}
			}
			for (list<BPoint* > ::iterator p = it->Sur_Point.begin(); p != it->Sur_Point.end(); p++)//周圍孤立點
			{
				for (int i = 2; i <= Level; i++)
				{
					BPoint& N = GetNeighbor(**p, i);
					if (N.Component_ID->GetStatus() != Good)
					{
						if (N.Component_ID == &Component.front())
						{
							N.IsBroken = true;
						}
						else
						{
							N.Component_ID->SetAsBad();
						}
					}
				}
			}
		}
	}
}

void BGraph::WritePoint()
{
	ofstream fout;
	stringstream badstream;
	stringstream goodstream;
	int badcount = 0, goodcount = 0;
	cout << "Bad Points:" << endl;
	for (list<BComponent>::iterator it = Component.begin(); it != Component.end(); it++)
	{
		if (&*it == &Component.front())
		{
			for (list<BPoint* > ::iterator p = it->member.begin(); p != it->member.end(); p++)
			{
				if ((*p)->IsBroken == true)
				{
					badcount++;
					cout << (*p)->ID << endl;
					badstream << (*p)->ID << endl;
				}
			}
			continue;
		}
		ComponentStatus S = it->GetStatus();
		for (list<BPoint* > ::iterator p = it->member.begin(); p != it->member.end(); p++)
		{
			switch (S)
			{
			case Bad:
				badcount++;
				cout << (*p)->ID << endl;
				badstream << (*p)->ID << endl;
				break;
			case Good:
				goodcount++;
				goodstream << (*p)->ID << endl;
				break;
			}

		}
		if (S == Good)
		{
			for (list<BPoint* > ::iterator p = it->Sur_Point.begin(); p != it->Sur_Point.end(); p++)
			{
				goodcount++;
				goodstream << (*p)->ID << endl;
			}
		}
	}
	fout.open("bad.point");
	fout << badcount << endl;
	fout << badstream.str();
	fout.close();
	fout.open("good.point");
	fout << goodcount << endl;
	fout << goodstream.str();
	fout.close();
}
