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
		/*for (list<BPoint>::iterator i = Isolated_Neighbor.begin(); i != Isolated_Neighbor.end();i++) {
		//找孤立點附近的component
		}*/
			//先放著以防萬一
			/*for (vector<Stauts>::iterator j = i->Neighbor.begin(); j != i->Neighbor.end(); j++)
			{
				if (j->Guess == false)
				{
					BPoint &pointJ = GetPoint(j->ID);
					for (vector<Stauts>::iterator k = pointJ.Neighbor.begin(); k != pointJ.Neighbor.end(); k++)
					{
						if (k->ID == i->ID)//改用find做
						{
							if (k->Guess == false)//這裡感覺怪怪的
							{
								if (i->Component_ID == NULL && pointJ.Component_ID == NULL)
								{
									Component.push_back({ &*i ,&pointJ });
									i->Component_ID = pointJ.Component_ID = &Component.back();
								}
								else if (i->Component_ID == NULL)
								{
									i->Component_ID=pointJ.Component_ID;
									pointJ.Component_ID->push_back(&*i);
								}
								else if (pointJ.Component_ID == NULL)
								{
									 pointJ.Component_ID= i->Component_ID;
									 i->Component_ID->push_back(&pointJ);
								}
								else if (i->Component_ID != pointJ.Component_ID)//連起來
								{
									list<BPoint*>* temp = pointJ.Component_ID;//可能沒問題了
									for (list<BPoint*>::iterator l = temp->begin(); l != temp->end(); l++)
									{
										(*l)->Component_ID = i->Component_ID;
									}
									i->Component_ID->splice(i->Component_ID->end(),*temp);
								}
							}
							break;
						}
					}
				}
			}*/
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
/*
void BGraph::CheckPointComp(const BPoint& B,list<BPoint>& todolist)//BFS(吧)
{
	//if (B.Component_ID != NULL) return;
	for (vector<Stauts>::const_iterator i = B.Neighbor.begin(); i != B.Neighbor.end(); i++)//檢查過去
	{
		if (i->Guess == false)//好點
		{
			BPoint& JPoint = GetPoint(i->ID);
			if (JPoint.Component_ID != NULL) continue;
			vector<Stauts>::const_iterator& J = find(JPoint.Neighbor.begin(), JPoint.Neighbor.end(), Stauts{ B.ID,false });//檢查回來
			if (J != JPoint.Neighbor.end())
			{
				JPoint.Component_ID = B.Component_ID;
				JPoint.Component_ID->push_back(&JPoint);
				CheckPointComp(JPoint);//會stackoverflow
			}
		}
	}
}*/
