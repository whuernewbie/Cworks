#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 500   //地图路的条数
#define A 50000 //测试次数

bool testOut(int c, int r)
{
	if (c == 0 || r == 0 || c == N || r == N)
	{
		return true;
	}
	else
	{
		return false;
	}//测试是否达到地图边界，如果达到边界，则返回true
}

bool testWalk(int c, int r, int n, bool col[N+1][N+1])
{
	switch (n)
	{
	case 0:return col[c - 1][r];
	case 1:return col[c][r + 1];
	case 2:return col[c + 1][r];
	case 3:return col[c][r - 1];
	default:break;
	}
}//测试方向n是否可走

int main()
{
	srand((unsigned)time(0));
	bool col[N + 1][N + 1];//地图数组
	int tways[A];//记录每次成功的步数
	int fways[A];//记录每次失败的步数
	int ways = 0;//路径长度 
	int overTimes = 0;//死胡同次数 
	int oktimes = 0;//成功次数 

	for (int i = 0; i < A; i++)
	{
		for (int i = 0; i < N + 1; i++)
		{
			for (int j = 0; j < N + 1; j++)
			{
				col[i][j] = true;
			}
		}//初始化地图数组
		int c = N / 2;
		int r = N / 2;//初始化狗的位置
		ways = 0;//初始化步数
		bool dric[4];//记录随机出的前进方向，每随机出一个方向则将对应数字置为false，n--，若4个方向均为false，n的值为0，退出循环
		while (true)
		{
			col[c][r] = false;//
			int n = 4;
			for (int i = 0; i < 4; i++) dric[i] = true;//前进方向初始化 
			int num = 0;//前进方向
			do {
				num = (rand() % 100) % 4;
				if (testWalk(c, r, num, col)) break;//如果随机到的方向可走，直接退出
				dric[num] = false;//若方向不可走，标记该方向为false
				n = 4;
				for (int i = 0; i < 4; i++)
				{
					if (!dric[i]) n--;
				}
				if (n == 0)
				{
					break;//若所有方向均不可走，则退出
				}
			} while (1);//找到一个可走的路 

			if (n != 0)
			{
				switch (num)
				{
				case 0:c = c - 1; break;
				case 1:r = r + 1; break;
				case 2:c = c + 1; break;
				case 3:r = r - 1; break;
				}
				ways++;//如果没有陷入死胡同，则向相应方向前进一步
			}
			else if (n == 0)
			{
				fways[overTimes] = ways;
				overTimes++;
				break;//如果陷入死胡同，失败次数加一，记录失败的步数
			}
			if (testOut(c, r))
			{
				tways[oktimes] = ways;
				oktimes++;
				break;
			}
		}
	}

	//开始输出各项信息
	int a = A;
	int n = N;
	printf("本次测试次数为：%d,地图横纵路的条数为：%d\n",a,n);
	int sum = 0;
	for (int i = 0; i < oktimes; i++)
	{
		sum += tways[i];
	}
	if (oktimes != 0) {
		int d = sum / oktimes;
		printf("成功的平均路径长度为：%d\n", d);
	}
	else
	{
		printf("成功次数为0\n");//消除除零异常
	}

	int sum1 = 0;
	for (int i = 0; i < overTimes; i++) 
	{
		sum1 += fways[i];
	}
	if(overTimes!=0) {
		int d = sum1 / overTimes;
		printf("失败的平均路径长度为：%d\n", d);
	}
	else
	{
		printf("失败次数为0\n");//消除除零异常
	}
	printf("总平均路径长度为：%d\n", (sum+sum1) /( overTimes+oktimes));
	printf("成功的概率为：%f\n", (float)oktimes / (overTimes+oktimes));
}