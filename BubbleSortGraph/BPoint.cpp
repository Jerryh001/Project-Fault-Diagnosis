#include "BPoint.h"
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
	Level = ID_C.length();
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
BPoint::~BPoint()
{
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
		int current = poto.find(*(ID.rbegin()));
		C_ID = char(current + '1') + C_ID;
		poto.erase(poto.begin() + current);
		ID.pop_back();
	}
	return C_ID;
}
BPoint& GetPoint(string ID,BStruct &BS)//用ID找點的物件
{
	ID = GetCreatedID(ID);
	BStruct *p=&BS;
	for (string::reverse_iterator i = ID.rbegin() ; i != ID.rend();i++)
	{
		//cout << *i;
		p = &p->next.at(*i - '1');
	}
	return *p->point;
}
BStruct::BStruct(int l)
{
	level = l;
	for (int i = 0; i < level; i++)
	{
		next.push_back(level - 1);
	}
}

BStruct::~BStruct()
{
}

void BStruct::Set_Point(BPoint &B)
{
	point = &B;
}
