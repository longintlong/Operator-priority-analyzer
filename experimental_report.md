

# 			语法分析实验报告

## 实验目的

- 理解算符优先分析的过程，并用程序实现表达式文法的算符优先分析器，并输入句子进行测试看是否归约过程。
- 知道如何根据一个文法建立FIRSTVT集、LASTVT集、算符优先矩阵，并用程序实现，要求文件输入，输出文法的FIRSTVT集、LASTVT集、算符优先矩阵，最后在加入之前写的算符优先分析的程序，合成一个完整的算符优先分析器。
- 在程序里还要有适当的错误处理

​    

## 实验难点

- 在实现算符优先分析过程中，我认为难点在于如何归约时如何找到最左素短语
- 求FIRSTVT集LASTVT集时我认为难点在于如何抽象出合适的数据结构来保存这个文法，实现遍历文法这个过程

## 实验步骤

为了降低难度，我首先完成了已知优先矩阵，打印出分析归约过程的程序。

随后用程序实现根据一个文法建立FIRSTVT集、LASTVT集、算符优先矩阵，并实现归约。

提前说明，我在初步的分析器里并没有处理错误，但在最后完整的分析器加入了错误处理。

### 1.表达式文法的算符优先分析器的构建

我首先实现了表达式文法的算符优先分析器。

***实验环境： Visual studio 2017***

***编程语言： C++***

这个文法是：

E:=E+T|T

T:=T*F|F

F:=(E)|i



FIRSTVT集：

|      |  +   |  *   |  (   |  )   |  i   |
| :--: | :--: | :--: | :--: | :--: | :--: |
|  E   |  1   |  1   |  1   |  0   |  1   |
|  T   |  0   |  1   |  1   |  0   |  1   |
|  F   |  0   |  0   |  1   |  0   |  1   |

LASTVT集:

|      |  +   |  *   |  (   |  )   |  i   |
| :--: | :--: | :--: | :--: | :--: | :--: |
|  E   |  1   |  1   |  0   |  1   |  1   |
|  T   |  0   |  1   |  0   |  1   |  1   |
|  F   |  0   |  0   |  0   |  1   |  1   |

算符优先矩阵:

|       |  +   |  *   |  i   |  (   |  )   |  #   |
| :---: | :--: | :--: | :--: | :--: | :--: | :--: |
| **+** |  >   |  <   |  <   |  <   |  >   |  >   |
| ***** |  >   |  >   |  <   |  <   |  >   |  >   |
| **i** |  >   |  >   |      |      |  >   |  >   |
| **(** |  <   |  <   |  <   |  <   |  =   |      |
| **)** |  >   |  >   |      |      |  >   |  >   |
| **#** |  <   |  <   |  <   |  <   |      |  >   |

然后进行算符优先算法：

下面是对程序中的重要的函数或者变量说明：

```C#
/*变量说明*/
int pri[][];//int类型的二维数组，用来存储优先矩阵，优先关系用整数2(>)、1(=)、0(<)、-1( )来表示。
string input;//表示输入要归约的句子
int top;//设置的分析栈的栈顶指针
int i;//遍历输入串的指针，表示当前栈外的字符
int j;//找栈顶或者次栈顶的终结符，因为栈顶有可能是非终结符
int prior;//比较栈外字符和栈顶终结符优先关系的结果，结果一共四个数：2(>)、1(=)、0(<)、-1( )
int step;//计算归约的步骤数
string stack;//分析栈，为了方便，我用了string代替stack


/*函数说明*/
int find(char c)//当要查找优先矩阵时，需要知道比较字符在优先矩阵的索引，这个函数用来返回那个索引，另外还可以判定是否为终结符，用来找栈顶或者次栈顶终结符用。

```



下面贴一下各个优先关系(> < = ' ')的处理函数

```C++
//当栈顶终结符>栈外字符时，求出最左素短语。就是j指针一直向前循环，知道栈内j所指向的终结符的优先级小于j右边的终结符为止。
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
	cout << step << "\t" << output <<"\t\t" <<input[i] << "\t\t\t" << stack[rel] << " >" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "归约" << endl;
	step++;
	top = j + 1;
	stack[top] = 'N'; 
	stack.erase(top + 1);
	continue;
}
```
```C++
//当栈顶终结符<栈外字符时，将栈外字符移进分析栈内即可。
else if (prior == 0)
{
    output = stack;
	cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " <" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "移进" << endl;
	top++;
	stack += input[i];
	step++;
	i++; 
    continue;
}
```
```c++
//当栈顶终结符=栈外字符时，先判断栈外字符是否为#，如果是说明此时归约成功；如果不是#，还需要判断是不是top是否等于j，如果是就说明()内没有符号，不能退出，报出错误。否则就移进分析栈内。代码和<的一样
else if (prior == 1)
{
	if (stack[j] == '#')
	{
		output = stack;
		cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " =" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "接受" << endl;
		cout<<"归约成功"<<endl;
		break;
	}
	else
	{
		if (top == j)
		{
			cout << "归约失败" << endl; 
			break;
		}
		output = stack;
		cout << step << "\t" << output << "\t\t" << input[i] << "\t\t\t" << stack[rel] << " =" << input[i] << "\t\t" << input.substr(i + 1) << "\t\t\t" << "移进" << endl;
		step++;
		top++;
		stack += input[i];
		i++; continue;
	}
}
```
以上第一步就完成了。



## 完成一个完整的算符优先分析器

### 建立FIRSTVT集合 LASTVT集

前面说 这部分的难点在于如何抽象出合适的数据结构来保存这个文法，实现遍历文法这个过程。

针对这一个问题，我用了类G表示该该文法，将文法的产生式根据“:=”隔开，记为左部和右部，遍历文法遍历这两个数组就可以。另外在用两个数组存储文法的终结符和非终结符。

***实验环境： Visual studio 2017***

***编程语言： C++工程项目***

#### 算法描述

完整的分析流程应该是 ：

​	创建终结符和非终结符集合

​	创建算符优先矩阵

​	进行归约

##### （1）生成终结符集合非终结符集合

产生式左部的符号就是非终结符，产生式右部将非终结符去掉剩下的都是终结符。

1. 遍历左部产生式数组，生成非终结符。
2. 遍历产生式右部数组，除去非终结符，将剩下的加入终结符数组中

另外此时我在生成终结符集合时，同时也生成了运算符集合，就判断产生式右部该终结符左右是否都有非终结。

##### （2）生成FIRSTVT和LASTVT

FIRSTVT 和LASTVT生成算法几乎一样，这里只说明生成FIRSTVT的算法

有一个bool类型firstvt矩阵，一个栈stack存储一个pair<char,char>，即（VN,VT）

1. 将firstvt矩阵全部置零
2. 遍历每个文法，如果存在产生式右部第一个字符t是VT或者第一个字符n是VN但第二个字符t是VN，就将此产生式左部U和该终结符记为（U，t）压栈，并且将对应位置的firstvt矩阵置1
3. 当栈不空时：栈顶出栈，记为（V,t），遍历所有文法，当找到某个文法U：=V····时，就将(U，t）y压栈。

##### （3）生成算符优先矩阵

直接上伪代码吧

```
FPR 每个产生式 A->X1X2...Xn  DO
    FOR i := 1 TO n-1  DO
        BEGIN 
            IF Xi和X(i+1)均为终结符
            THEN 置 Xi优先级等于X(i+1);
            IF i<=n-2 且Xi和X(i+2)都为终结符，但X(i+1)为非终结符
            THEN 置 Xi优先级等于X(i+2);
            IF Xi为终结符而X(i+1)为非终结符
            THEN FOR FIRSTVT(X(i+1))中的每个b DO 置 Xi优先级低于b;
            IF Xi为非终结符而X(i+1)为终结符
            THEN FOR LASTVT(Xi)中的每个a DO 置 a优先级高于X(i+1);
        END
```

##### （4）归约

第一步已经详细说明这里就不再赘述。唯一的区别就是我在归约的时候加入了错误处理。错误处理详见其算法描述。



#### 项目目录：

G.h是类的头文件，G.cpp是类的实现文件，ConsoleApplication.cpp是主函数

![1543197135943](1543197135943.png)



#### 程序的结构和实现

- **string left[50],right[50]：**文法的产生式 分为左部和右部，每个部分用string数组来保存，因为有索引，所以可以用索引就对应了第几个文法，并且就把左部和右部联系了起来。
- **string  T, N：**  T用来存放文法中的终结符，N用来存放文法的非终结符。
- **bool firstvt[][] lastvt[][]**  ：bool类型的二维数组，用来存储文法FIRSTVT集和LASTVT集
- **char priority[][]**：  char 类型的二维数组，存储算符优先关系矩阵，是字符类型，矩阵都是用< > = ' '来表示
- **int pri[][]** ： int 类型的二维数组,该数组和priority作用一样，只不过矩阵是用整数2,1,0，-1表示

以上是类变量存储文法

下面说明一下类方法及其作用：

- **void product(string s);** 该函数接受文件输入的每一行文法，生成left数组和right数组，该函数里有对文法中如果有‘|’的处理，直接新生成一个新的产生式就可以。
- **bool exist_N(char c);**该函数接受一个字符参数，判断这个字符是不是非终结符
- **bool exist_T(char  c);**该函数接受一个字符参数，判断这个字符是不是终结符
- **void pro_tn();**该函数生成文法的终结符和非终结符表，
- **void first();**该函数求文法的FIRSTVT集
- **void last();**该函数求文法的LASTVT集
- **void priori();**该函数求文法的算符优先矩阵
- **void convert();**该函数用来根据字符型的优先矩阵转化为整数型的算符优先矩阵
- **void reduction(string s);**该函数就是归约过程
- **bool judge(string s);**该函数用来当要归约时，的出错处理的函数，返回一个bool，如果返回0，说明出错归约失败。

下面这是类的头文件G.h

```C++
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
	bool exist_op(char  c);
	void pro_tn();
	void first();
	void last();
	void priori();
	void convert();
	void reduction(string s);
    bool judge(string s);
};

```

这是生成FIRSTVT的源代码

```C++
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
```



这是生成运算符优先矩阵的源代码

```C++
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
```



##### 错误处理

在第一部分里，我虽然实现了算符优先分析，但是没有进行错误处理，现在要加入错误处理，但是这里不能针对于某个文法，而是根据输入的任意的文法都能进行错误处理。

方法就是在归约的时候，将要归约那一串字符串s，和每个产生式右部right[i]比较：

​	如果两者长度都不一样肯定不行

​	如果长度一样：当s[j]是非终结符时，要求right[i，j]也为非终结符

​				   当s[j]是终结符，要求right[i，j==s[j]

下面贴出错误处理的代码：

```C++
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
					flag = 0; 
                    break;
				}
			}
			else if (exist_T(s[j]) && s[j] != right[i][j])
			{
				flag = 0; 
                break;
			}
		}
		if (flag == 1)return 1;
	}
	return flag;
}
```



## 运行截图

文件输入，如果正确会打印出分析结果

![1543209487027](1543209487027.png)

![1543209545954](1543209545954.png)

如果文件打不开会出抛出错误

![1543209584493](1543209584493.png)



分析完成后，提示输入要归约的句子，输入句子后会显示归约过程；如果有错误，会出现归约失败

![1543209693160](1543209693160.png)



## 实验感想

通过这次实验，我加深了算符优先分析的理解，并且用程序完整的实现了他。

锻炼了自己的代码能力，培养了自己的抽象能力，比如如何将一个文法抽象成怎样的数据结构。