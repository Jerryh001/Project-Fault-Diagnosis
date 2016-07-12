#include "BGraph.h"
#include<map>
void BGraph::f_comp()
{
	Component.push_back(nullptr);//預留給孤立點的"元件"
	Component.front().member.clear();
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

				for (int j = 2; j <= Level;j++)//檢查過去
				{
					if (head.Neighbor[j-2].Guess == false)//好點
					{
						BPoint& JPoint = GetNeighbor(head,j);
						if (JPoint.Component_ID != nullptr) continue;
						Point_Symptom_Get(JPoint);
						if (JPoint.Neighbor[j-2].Guess==false)
						{
							JPoint.Component_ID = head.Component_ID;
							JPoint.Component_ID->member.push_back(&JPoint);
							todolist.push_back(&JPoint);
						}
					}
				}
			}
			i->IsIsolated = true;
			for (int j = 2; j <= Level;j++)
			{
				if (i->Neighbor[j-2].Guess == false)
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
		BPoint &B = *(*j);//孤立點本身
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
				}else
				{
					KPoint.Component_ID->Sur_Point.push_back(&B);//加入
					complist[id]++;
				}
			}
		}
	}
}
