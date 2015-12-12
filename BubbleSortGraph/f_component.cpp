#include "BGraph.h"
void BGraph::f_comp()
{
	Component.push_back(NULL);//預留給孤立點的"元件"
	Component.front().member.clear();
	for (list<BPoint>::iterator i = Point.begin(); i != Point.end(); i++)
	{
		if (i->Component_ID == NULL)
		{
			list<BPoint*> todolist = { &*i };
			Component.push_back( &*i );
			i->Component_ID = &Component.back();
			Component.back().id=(++Component.rbegin())->id+1;
			while (todolist.size() > 0)
			{
				BPoint& head = *todolist.front();
				todolist.pop_front();
				for (vector<Stauts>::const_iterator i = head.Neighbor.begin(); i != head.Neighbor.end(); i++)//檢查過去
				{
					if (i->Guess == false)//好點
					{
						BPoint& JPoint = GetPoint(i->ID);
						if (JPoint.Component_ID != NULL) continue;
						vector<Stauts>::const_iterator& J = find(JPoint.Neighbor.begin(), JPoint.Neighbor.end(), Stauts{ head.ID,false });//檢查回來
						if (J != JPoint.Neighbor.end())
						{
							JPoint.Component_ID = head.Component_ID;
							JPoint.Component_ID->member.push_back(&JPoint);
							todolist.push_back(&JPoint);
							//CheckPointComp(JPoint);//會stackoverflow
						}
					}
				}
			}
			i->IsIsolated = true;
			for (vector<Stauts>::const_iterator j = i->Neighbor.begin(); j != i->Neighbor.end(); j++)
			{
				if (j->Guess == false)
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
	for (list<BComponent>::iterator i = ++Component.begin(); i != Component.end(); i++)//每個元件
	{
		for (list<BPoint*>::iterator j = Component.front().member.begin(); j != Component.front().member.end(); j++)//每個孤立點
		{
			BPoint &B = *(*j);//孤立點本身
			for (vector<Stauts>::iterator k =B.Neighbor.begin(); k != B.Neighbor.end(); k++)
			{
				if (GetPoint(k->ID).Component_ID == &*i)
				{
					i->Sur_Point.push_back(&B);
					break;
					//加入
				}
			}
		}
		
	}
}