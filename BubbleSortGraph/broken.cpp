﻿#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include <sstream>
#include<ctime>
#include<vector>
#include "BGraph.h"
using namespace std;
void prowhypoint(int n, int c, list<string> &p)//n為階層數 C為產生的壞點數量
{
	bool boo = 0;
	srand(time(NULL));
	cout << "bad point:";
	while (c)
	{
		vector<int> a;
		int b = 0;
		for (int i = 0; i < n; i++)
		{
			a.push_back(rand() % (i + 1) + 1);
			b *= 10;
			b += a[i];
		}
		for (list<string>::iterator i = p.begin(); i!=p.end(); i++)
		{
			if (to_string(b) == *i)
			{
				boo = 1;
				c++;
				break;
			}
		}
		if (boo == 0)
		{
			p.push_back(to_string(b));
			cout << BPoint(p.back()).ID << " ";
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

