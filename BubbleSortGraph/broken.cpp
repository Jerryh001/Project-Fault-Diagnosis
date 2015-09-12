#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include <sstream>
#include<ctime>
#include<vector>
//#include<cmath>
#include "BGraph.h"
using namespace std;
void prowhypoint(int n, int c, list<string> &p)//n為階層數 C為產生的壞點數量
{
	int i = 0, v = 0, boo = 0;
	srand(time(NULL));
	vector<int> forsav;
	cout << "bad point:";
	while (c)
	{
		vector<int> a;
		int b = 0;
		stringstream ss;
		string convert_str;
		for (int i = 0; i < n; i++)
		{
			a.push_back(rand() % (i + 1) + 1);
			b *= 10;
			b += a[i];
		}
		for (int i = 0; i < v; i++)
		{
			if (b == forsav[i])
			{
				boo = 1;
				c++;
				break;
			}
		}
		if (boo == 0)
		{
			forsav.push_back(b);
			ss << b;
			ss >> convert_str;
			p.push_back(convert_str);
			cout << BPoint(p.back()).ID << " ";
			v++;
		}
		boo = 0;
		//strsav[i]=convert_str;
		c--;
	}
	cout << endl;
}
//int main()
//{
//    int n,c;
//    vector<string> p;
//    cout<<"請輸入階層數(請輸入整數):";
//    cin>>n;
//    cout<<"請輸入錯誤點數量(請輸入整數):";
//    cin>>c;
//    cout<<"標出錯誤點:";
//    prowhypoint(n,c,p);
//    cout<<endl;
//}

