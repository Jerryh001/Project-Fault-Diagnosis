#include "BGraph.h"
void BGraph::f_comp() {
	for (list<BPoint>::iterator i = Point.begin(); i != Point.end(); i++) {
		for (vector<Stauts>::iterator j = i->Neighbor.begin(); j != i->Neighbor.end(); j++)
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
		}
	}
}