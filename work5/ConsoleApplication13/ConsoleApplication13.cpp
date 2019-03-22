#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <exception>
using namespace std;


#define MaxSize 100
typedef char ElemType;


typedef struct node
{
	ElemType data;              //数据元素
	struct node *lchild;        //指向左孩子
	struct node *rchild;        //指向右孩子
} BTNode;


BTNode *FindNode(BTNode *b, ElemType x)  //返回data域为x的节点指针
{
	BTNode *p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}

BTNode *LchildNode(BTNode *p)   //返回*p节点的左孩子节点指针
{
	return p->lchild;
}
BTNode *RchildNode(BTNode *p)   //返回*p节点的右孩子节点指针
{
	return p->rchild;
}

void DispBTNode(BTNode *b)  //以括号表示法输出二叉树
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);
			if (b->rchild != NULL) printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}

void DestroyBTNode(BTNode *&b)   //销毁二叉树
{
	if (b != NULL)
	{
		DestroyBTNode(b->lchild);
		DestroyBTNode(b->rchild);
		free(b);
	}
}

//用s[i]到s[j]之间的字符串，构造二叉树的表示形式
BTNode *CRTree(char s[], int i, int j)
{
	BTNode *p;
	int k, plus = 0, posi, x = 0;
	if (i == j)    //i和j相同，意味着只有一个字符，构造的是一个叶子节点
	{
		p = (BTNode *)malloc(sizeof(BTNode));   //分配存储空间
		p->data = s[i];                         //值为s[i]
		p->lchild = NULL;
		p->rchild = NULL;
		return p;
	}
	if (s[i] == '(')
	{
		x = i;
		while (s[x] != ')') x++;
		if (x == j)
		{
			p = (BTNode *)malloc(sizeof(BTNode));
			p = CRTree(s, i + 1, x - 1);
			return p;
		}
	}
	//以下为i!=j的情况
	for (k = i; k <= j; k++)
	{
		if (s[k] == '+' || s[k] == '-')
		{
			plus++;
			posi = k;              //最后一个+或-的位置
		}
		else if (s[k] == '(')
		{
			while (s[k] != ')') k++;
		}
	}
	if (plus == 0)                 //没有+或-的情况(因为若有+、-，前面必会执行plus++)
		for (k = i; k <= j; k++)
		{
			if (s[k] == '*' || s[k] == '/')
			{
				plus++;
				posi = k;
			}
			else if (s[k] == '(')
			{
				while (s[k] != ')') k++;
			}
		}
	//以上的处理考虑了优先将+、-放到二叉树较高的层次上
	//由于将来计算时，运用的是后序遍历的思路
	//处于较低层的乘除会优先运算
	//从而体现了“先乘除后加减”的运算法则
	//创建一个分支节点，用检测到的运算符作为节点值
	if (plus != 0)
	{
		p = (BTNode *)malloc(sizeof(BTNode));
		p->data = s[posi];                //节点值是s[posi]
		p->lchild = CRTree(s, i, posi - 1);   //左子树由s[i]至s[posi-1]构成
		p->rchild = CRTree(s, posi + 1, j);   //右子树由s[posi+1]到s[j]构成
		return p;
	}
	else       //若没有任何运算符，返回NULL
		return NULL;
}

void last(BTNode *b)//后序遍历输出后缀表达式
{
	if (b != NULL)
	{
		if (b->lchild != NULL || b->rchild != NULL)
		{
			last(b->lchild);
			last(b->rchild);
		}
		printf("%c", b->data);
	}
}

int main()
{
	BTNode *b;
	char s[MaxSize];
	printf("请输入中缀表达式\n");
	try
	{
		scanf_s("%s",s,MaxSize-1);
	}
	catch (exception ex)
	{
		printf("输入错误\n");
	}
	b = CRTree(s, 0, strlen(s) - 1);
	printf("对应二叉树为:");
	DispBTNode(b);
	printf("\n后缀表达式");
	last(b);
	printf("\n");
	DestroyBTNode(b);
	system("pause");
	return 0;
}