#include"stdafx.h"
#include<iostream>
#include<stack>
#include"G.h"

using namespace std;


G::G()
{
	p_l = 0;
	t_l = 0; 
	n_l = 0;
	N = ""; T = "";
	memset(pri, 0, sizeof(pri));
	for (int i = 0; i < 50; i++)
	{
		left[i] = "";
		right[i] = "";
		for (int j = 0; j < 50; j++)
			priority[i][j] = ' ';
	}
}

G::~G()
{
}
void G::product(string s)
{
	if (p_l == 0)
	{
		left[0] = "S";
		right[0] = "#?#";
		right[0][1] = s[0];
		p_l++;
	}
	string str = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')continue;
		if (i == s.length() - 1)
		{
			right[p_l++] = str + s[i]; continue;
		}
		if (s[i] == '|')
		{  
			right[p_l] = str; str = "";
			left[p_l + 1] = left[p_l]; 
			p_l++; continue;
		}
		if (s[i] == ':'&&s[i + 1] == '=') { left[p_l] = str; str = ""; i++; continue; }			
		str += s[i];
	}
}

bool G::exist_N(char c)
{
	for (int i = 0; i < n_l; i++)
	{
		if (c == N[i])return 1;
	}
	return false;
}

bool G::exist_T(char  c)
{
	for (int i = 0; i < t_l; i++)
	{
		if (c == T[i])return 1;
	}
	return false;
}


void G::pro_tn()
{
	for (int i = 0; i < p_l; i++)
	{
		if (!exist_N(left[i][0]))
		{
			N += left[i][0]; n_l++;
		}
	}
	for (int i = 0; i < p_l; i++)
	{
		for (int j = 0; j < right[i].length();j++)
		{
			if (exist_N(right[i][j])==0)
			{
				if(!exist_T(right[i][j]))
				{
					T += right[i][j]; t_l++;
				}
			}
		}
	}
}

void G::first()
{
	stack<pair<char, char>> st;
	memset(firstvt, 0, sizeof(firstvt));
	pair<char,char> p;
	char x, y, z;
	for (int i=0; i < p_l; i++)
	{
		x = left[i][0];
		if (exist_T(right[i][0]))
		{
		     y = right[i][0];
			if (!firstvt[N.find(x)][T.find(y)])
			{
				firstvt[N.find(x)][T.find(y)] = 1;
				p = make_pair(x, y);
				st.push(p);
			}
		}
		else if ((exist_T(right[i][1]) && exist_N(right[i][0])))
		{
			 y = right[i][1];
			if (!firstvt[N.find(x)][T.find(y)])
			{
				firstvt[N.find(x)][T.find(y)] = 1;
				p = make_pair(x, y);
				st.push(p);
			}
		}
	}
	while (!st.empty())
	{
		x = st.top().first; y = st.top().second;
		st.pop();
		for (int i = 0; i < p_l; i++)
		{
			if (right[i][0]==x)
			{
				z = left[i][0];
				if (!firstvt[N.find(z)][T.find(y)])
				{	
					firstvt[N.find(z)][T.find(y)] = 1;
					p = make_pair(z, y);
					st.push(p);
				}
			}
		}
	}
}

void G::last()
{
	stack<pair<char, char>> st;
	memset(lastvt, 0, sizeof(lastvt));
	pair<char, char> p;
	char x, y, z;
	int l;
	for (int i = 0; i < p_l; i++)
	{
		x = left[i][0]; l = right[i].length() - 1;
		if (exist_T(right[i][l]))
		{
			y = right[i][l];
			if (!lastvt[N.find(x)][T.find(y)])
			{
				lastvt[N.find(x)][T.find(y)] = 1;
				p = make_pair(x, y);
				st.push(p);
			}
		}
		else if (l>1&&(exist_T(right[i][l-1]) && exist_N(right[i][l])))
		{
			y = right[i][l-1];
			if (!lastvt[N.find(x)][T.find(y)])
			{
				lastvt[N.find(x)][T.find(y)] = 1;
				p = make_pair(x, y);
				st.push(p);
			}
		}
	}
	while (!st.empty())
	{
		x = st.top().first; y = st.top().second;
		st.pop();
		for (int i = 0; i < p_l; i++)
		{
			l = right[i].length()-1;
			if (right[i][l] == x)
			{
				z = left[i][0];
				if (!lastvt[N.find(z)][T.find(y)])
				{
					lastvt[N.find(z)][T.find(y)] = 1;
					p = make_pair(z, y);
					st.push(p);
				}
			}
		}
	}
}

void G::priori()
{
	int x, y;
	for (int i = 0; i < p_l; i++)
	{
		string r = right[i];
		for (int j = 0; j < r.length()-1; j++)
		{
			if (j < r.length() - 1&&exist_T(r[j]) && exist_T(r[j + 1]))
			{
				x = T.find(r[j]); y = T.find(r[j+1]);
				priority[x][y] = '=';
			}
			 if (j < r.length() - 2 && exist_T(r[j]) && exist_T(r[j + 2]) && exist_N(r[j + 1]))
			{
				x = T.find(r[j]); y = T.find(r[j + 2]);
				priority[x][y] = '=';
			}
			if (j < r.length() - 1&&exist_T(r[j]) && exist_N(r[j + 1]))
			{
				x = T.find(r[j]); y = N.find(r[j + 1]);
				for (int p = 0; p < t_l; p++)
				{
					if (firstvt[y][p] == 1)
						priority[x][p] = '<';
				}
			}
			 if (j < r.length() - 1 && exist_N(r[j]) && exist_T(r[j + 1]))
			{
				x = T.find(r[j+1]); y = N.find(r[j]);
				for (int p = 0; p < t_l; p++)
				{
					if (lastvt[y][p] == 1)
						priority[p][x] = '>';
				}
			}
		}
	}
}

void G::convert()
{
	for (int i = 0; i < t_l; i++)
	{
		for (int j = 0; j < t_l; j++)
		{
			if (priority[i][j] == '>')
				pri[i][j] = 2;
			else if (priority[i][j] == '=')
				pri[i][j] = 1;
			else if (priority[i][j] == '<')
				pri[i][j] = 0;
			else
				pri[i][j] = -1;
		}
	}
}

void G::reduction(string input)
{
	//cout << op[0] << endl;
	input += '#';
	int top,i, j;//Õ»Ö¸Õë/ÕÒÕ»¶¥´ÎÕ»¶¥µÄÖÕ½á·û
	int prior;
	int step;
	string output="";
	char q;
	int rel;
	string stack = "#";
	top = 0; i = 0; step = 0;
	cout << "²½Öè" <<"\t" << "·ÖÎöÕ»" <<"\t\t" << "Õ»Íâ×Ö·û " <<"\t\t" <<"¹ØÏµ" <<"\t\t"<< "Ê£Óà×Ó´®" <<"\t\t"<< "²Ù×÷" << endl;
	//if (step == 0 && exist_op(input[i])) { cout << "¹éÔ¼Ê§°Ü" << endl; return; }
	while (1)
	{
		//cout << stack << endl;
		//if (exist_op(input[i]) && exist_op(stack[top])) { cout << "¹éÔ¼Ê§°Ü" << endl; break; }
		j = top;
		if (exist_T(stack[top]) == 0) j = top - 1;
		else j = top;
		rel = j;
		prior = pri[T.find(stack[j])][T.find(input[i])];
		if (prior == 2)
		{
			do
			{
				q = stack[j];
				if (exist_T(stack[j-1]) != 0)
					j--;
				else
					j = j - 2;
				//Console.WriteLine(j);
			} while (pri[T.find(stack[j])][T.find(q)] != 0);
			output = (stack);
			cout << step << "\t" << output <<"\t\t" <<input[i] << "\t\t\t" << stack[rel] << " >" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "¹éÔ¼" << endl;
			step++;
			if (!judge(stack.substr(j + 1, top)))
			{
				cout << "¹éÔ¼Ê§°Ü" << endl; break;
			}
			top = j + 1;
			stack[top] = 'N'; 
			stack.erase(top + 1);
			continue;
		}
		else if (prior == 0)
		{
			output = stack;
			cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " <" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "ÒÆ½ø" << endl;
			top++;
			stack += input[i];
			step++;
			i++; continue;
		}
		else if (prior == 1)
		{
			if (stack[j] == '#')
			{
				output = stack;
				cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " =" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "½ÓÊÜ" << endl;
				cout<<"¹éÔ¼³É¹¦"<<endl;
				break;
			}
			else
			{
				//if (top == j)
				//{
				//	cout << "¹éÔ¼Ê§°Ü" << endl; 
				//	break;
				//}
				output = stack;
				cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " =" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "ÒÆ½ø" << endl;
				step++;
				top++;
				stack += input[i];
				i++; continue;
			}
		}
		else
		{
			cout << "¹éÔ¼Ê§°Ü" << endl;
			break;
		}
	}

}

bool G::judge(string s)
{
	bool flag =0;
	for (int i = 0; i < p_l; i++)
	{
		if (s.length() != right[i].length())continue;
		flag = 1;
		for (int j = 0; j < s.length(); j++) 
		{
			if (exist_N(s[j]))
			{
				if (!exist_N(right[i][j]))
				{
					flag = 0; break;
				}
			}
			else if (exist_T(s[j]) && s[j] != right[i][j])
			{
				flag = 0; break;
			}
		}
		if (flag == 1)return 1;
	}
	return flag;
}
