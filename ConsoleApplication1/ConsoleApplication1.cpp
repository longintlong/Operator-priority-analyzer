// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "G.h"
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<utility>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	cout << "*******************************************" << endl;
	cout << "请输入文法的文件路径:(按回车键结束输入)" << endl;
	string path;
	cin >> path;
	ifstream fin(path);
	if (!fin) { cout << "打开文件失败，请检查路径是否正确或者文件权限是否可读" << endl; exit(-1); }
	printf("打开文件成功,读取文法中......\n");
	string s;
	int i = 0;
	G* g = new G();
	while (getline(fin,s))
	{
		g->product(s);
	}
	cout << "*******************************************" << endl;
	cout << endl;

	cout << "读取完成，现在开始分析" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "文法为" << endl;
	for (int i = 0; i < g->p_l; i++)
	{
		cout << g->left[i] << " -> " << g->right[i] << endl;;
	}
	cout << "*******************************************" << endl;
	cout  << endl;
	g->pro_tn();
	cout << "*******************************************" << endl;
	cout << "VT集" << endl;
	for (int i = 0; i < g->t_l; i++)
	{
		cout << g->T[i] << " ";
	}
	cout << endl;
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "VN集" << endl;
	for (int i = 0; i < g->n_l; i++)
	{
		cout << g->N[i] << " ";
	}
	cout << endl;
	g->first();
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "FIRSTVT集" << endl;
	for (int i = -1; i < g->n_l; i++)
	{
		if (i == -1)
		{
			cout << "  ";
			for (int j = 0; j < g->t_l; j++)cout << g->T[j] << " ";
			cout << endl; continue;
		}
		for (int j = -1; j < g->t_l; j++)
		{
			if (j == -1)
				cout << g->N[i] << " ";
			else 
				cout << g->firstvt[i][j] << " ";
		}
		cout << endl;
	}
	g->last();
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "LASTVT集" << endl;
	for (int i = -1; i < g->n_l; i++)
	{
		if (i == -1)
		{
			cout << "  ";
			for (int j = 0; j < g->t_l; j++)cout << g->T[j] << " ";
			cout << endl; continue;
		}
		for (int j = -1; j < g->t_l; j++)
		{
			if (j == -1)
				cout << g->N[i] << " ";
			else
				cout << g->lastvt[i][j] << " ";
		}
		cout << endl;
	}
	g->priori();
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "运算符优先矩阵为" << endl;
	for (int i = -1; i < g->t_l; i++)
	{
		if (i == -1)
		{
			cout << "  ";
			for (int j = 0; j < g->t_l; j++)cout << g->T[j] << " ";
			cout << endl; continue;
		}
		for (int j = -1; j < g->t_l; j++)
		{
			if (j == -1)
				cout << g->T[i] << " ";
			else
				cout << g->priority[i][j] << " ";
		}
		cout << endl;
	}
	cout << "*******************************************" << endl;
	cout << "分析文法完毕" << endl;
	cout << endl;
	string in;
	g->convert();
	cout << "请输入要归约的句子:" << endl;
	while (cin >> in)
	{
		g->reduction(in);
		cout << "请输入要归约的句子:" << endl;
	}

}

