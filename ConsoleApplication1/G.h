#pragma once
#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;
class G 
{
public :
	int p_l, t_l, n_l;
	string pro[50];
	string left[50],right[50];
	string  T, N;
	G();
	~G();
	bool firstvt[50][50], lastvt[50][50];
	char priority[50][50];
	int pri[50][50];
	void product(string s);
	bool exist_N(char c);
	bool exist_T(char  c);
	void pro_tn();
	void first();
	void last();
	void priori();
	void convert();
	void reduction(string s);
	bool judge(string s);
};
