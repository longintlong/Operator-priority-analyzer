// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "�������ķ����ļ�·��:(���س�����������)" << endl;
	string path;
	cin >> path;
	ifstream fin(path);
	if (!fin) { cout << "���ļ�ʧ�ܣ�����·���Ƿ���ȷ�����ļ�Ȩ���Ƿ�ɶ�" << endl; exit(-1); }
	printf("���ļ��ɹ�,��ȡ�ķ���......\n");
	string s;
	int i = 0;
	G* g = new G();
	while (getline(fin,s))
	{
		g->product(s);
	}
	cout << "*******************************************" << endl;
	cout << endl;

	cout << "��ȡ��ɣ����ڿ�ʼ����" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "�ķ�Ϊ" << endl;
	for (int i = 0; i < g->p_l; i++)
	{
		cout << g->left[i] << " -> " << g->right[i] << endl;;
	}
	cout << "*******************************************" << endl;
	cout  << endl;
	g->pro_tn();
	cout << "*******************************************" << endl;
	cout << "VT��" << endl;
	for (int i = 0; i < g->t_l; i++)
	{
		cout << g->T[i] << " ";
	}
	cout << endl;
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "VN��" << endl;
	for (int i = 0; i < g->n_l; i++)
	{
		cout << g->N[i] << " ";
	}
	cout << endl;
	g->first();
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "FIRSTVT��" << endl;
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
	cout << "LASTVT��" << endl;
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
	cout << "��������Ⱦ���Ϊ" << endl;
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
	cout << "�����ķ����" << endl;
	cout << endl;
	string in;
	g->convert();
	cout << "������Ҫ��Լ�ľ���:" << endl;
	while (cin >> in)
	{
		g->reduction(in);
		cout << "������Ҫ��Լ�ľ���:" << endl;
	}

}

