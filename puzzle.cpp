#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
#include<assert.h>

void init(char *str, size_t row,size_t size)
{   //在这个函数，将二维数组看作一维数组
	assert(str);
	size_t col = size / row;
	for (size_t i = 0; i < col; i++)
	{
		//将前面两列初始化为‘R’，代表红色
		for (size_t j = 0; j < row/2; j++)
		{
			//i*row是表示到第几行，j表示到第几列，
			str[i*row + j] = 'R';
		}
		//将后面两列初始化为‘B’，代表蓝色
		for (size_t j = row/2; j < row; j++)
		{
			str[i*col + j] = 'B';
		}
	}
	//最后将第一个设置为空‘N’
	str[0] = 'N';
}

//输出函数
void display(char *str,size_t row,size_t size)
{
	assert(str);
	size_t col = size / row;
	for (size_t i = 0; i < size / row; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			cout << str[row*i+j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Move(char *str, size_t row,int &head,int &tail,int &null, size_t size)
{
	size_t col = size / row;
	//空格在头的下一行
	if (head / 10 + 1 == null / 10)
	{
		//如果尾跟头在同一列
		if (head % 10 == tail % 10)
		{
			int i = 0;
			for (i = null / 10; i > tail / 10; i--)
			{
				str[i*row] = str[(i - 1)*row];
			}
			str[i*row] = 'N';
			head = null;
			null = tail;
			tail = tail - 10;
		}
		//如果尾跟头不在同一列
		else
		{
			int i = 0;
			for (i = null / 10; i > tail / 10; i--)
			{
				str[i*row] = str[(i - 1)*row];
			}
			for (i = null % 10; i < tail % 10; i++)
			{
				str[(tail / 10)*row + i] = str[(tail / 10)*row + i + 1];
			}
			str[(tail / 10)*row + i] = 'N';
			head = null;
			null = tail ;
			tail = tail - 1;
		}

	}
	//空格在头的下一个
	else
	{
		//如果尾跟头在同一行
		if (head / 10 == tail / 10)
		{
			int i = 0;
			for (i = null % 10; i > tail % 10;i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(null / 10)*row + i] = 'N';
			null = tail;
			tail = tail - 1;
		}
		//如果尾没有在同一行
		else
		{
			int i = 0;
			for (i = null % 10; i > tail % 10; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			for (i = null / 10; i > tail / 10; i--)
			{
				str[i*row + tail % 10] = str[(i - 1)*row + tail % 10];
			}
			str[(tail/10)*row + tail % 10] = 'N';
			null = tail;
			tail = tail - 10;
		}
	}	
}
void find_move_null(char *str, size_t row, int head, int tail, int &null, size_t size)
{
	size_t col = size / row;
	//当头在每一行的开始
	if (head % 10 == 0)
	{
		//空格跟头的下一行在同一行
		if (null / 10 == head / 10 + 1)
		{
			size_t i = 0;
			for (i = null % 10; i > 1; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(null / 10)*row+i] = 'N';	
		}
		//空格跟头的下一行不在同一行
		else
		{
			int i = 0;
			for (i = null / 10; i < head / 10+1; i++)
			{
				str[i*row + (null % 10)] = str[(i + 1)*row + (null % 10)];
			}
			for (i = null % 10; i>0; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(head / 10)*row + head % 10 + 1] = 'N';
		}
		null = head + 10;
	}
	//当头不在每一行的开始
	else
	{
		//空格跟头在同一行
		if (null / 10 == head / 10)
		{
			int i = 0;
			for (i = null % 10; i > head % 10 - 2; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(null / 10)*row + i] = 'N';
		}
		//空格跟头不在同一行
		else
		{
			int i = 0;
			for (i = null / 10; i < head / 10; i++)
			{
				str[i*row + (null % 10)] = str[(i + 1)*row + (null % 10)];
			}
			for (i = null % 10; i>head % 10 - 2; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(head / 10)*row + head % 10 + 1] = 'N';
		}
		null = head + 1;
	}
	
}
void test()
{
	char str[4][4];
    //初始化这个二维数组
	init((char *)str, 4, 16);
	display((char *)str, 4, 16);

	//定义头为1，表示第0行第一个,尾在刚开始的时候跟头重合，空的位置在第一行第一个
	//如果是第二行第二个则为21
	int head = 1;
	int tail = 1;
	int null = 0;
	size_t row = 4;
	size_t col = 4;
	//用来记录头跟为之间的格子数
	int count = 1;
	//当head到第一行最后一个并且第一个行第一个为空的时候，循环结束
	while (1)
	{
		//首先从头到尾让它靠边缘逆时针走一格

		//如果已经在啊最后一行，那就已经可以结束了
		if (col == 1)
		{
			for (size_t i = row-1; i >0; i--)
			{
				str[0][i] = str[0][i - 1];
			}
			head = row - 1;
			str[0][0] = 'N';
			break;
		}
		//如果头刚好在一行的最后一个，那么这一行已经设置好了，行数就可以减少一行
		if (head % 10 == row-1)
		{
			col--;
			//头就变成是刚刚那一行的上一行的第一个位置
			head = head - 10;
		}
		//如果空格刚好在头的前一个，那整体逆时针走一格
		if ((null == head - 1)||(null== head-10))
		{
			Move((char *)str, row, head, tail, null, row*col);
		}
		else
		{
			find_move_null((char *)str, row, head, tail, null, row*col);
			Move((char *)str, row, head, tail, null, row*col);
		}

		//开始寻找尾巴后面应该要跟的空格


		//从空格的上下左右开始找
		
		//如果空格在第一行
		if (null / 10 == 0)
		{
			//如果空格在第一个

			if (null % 10 == 0)
			{
				//count%4!=0
				//判断空格的下一个是不是要跟的相反的空格

				//count%4==0
				//判断空格的下一个是不是要跟的相同的空格
				if ((str[null / 10 + 1][0] != str[null / 10][1] && count % 4 != 0)
					|| (str[null / 10 + 1][0] == str[null / 10][1] && count % 4 == 0))
				{
					str[null / 10][0] = str[null / 10][1];
					str[null / 10][1] = 'N';
					tail = null;
					null = null + 1;
					count++;
				}
				else
				{
					continue;
				}
			}
			
			//如果空格在最后一个
			if (null % 10 == row)
			{
				if ((str[null / 10][null % 10 - 1] != str[null / 10 + 1][null % 10]&&count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 + 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 + 1][null % 10];
					str[null / 10 + 1][null % 10] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				else
				{
					continue;
				}
			}
			//如果空格在中间位置
			else
			{
				//判断空格的右边
				if ((str[null / 10][null % 10 - 1] != str[null / 10][null % 10 + 1] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10][null % 10 + 1] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10][null % 10 + 1];
					str[null / 10][null % 10 + 1] = 'N';
					tail = null;
					null = null + 1;
					count++;
				}
				//判断空格的下边
				else if ((str[null / 10][null % 10 - 1] != str[null / 10 + 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 + 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 + 1][null % 10];
					str[null / 10 + 1][null % 10] = 'N';
					tail = null;
					null = null + 10;
					count++;
				}
				else
				{
					continue;
				}
			}
		}
		//空格不在第一行
		else
		{
			//空格在每一行的第一个
			if (null % 10 == 0)
			{
				//判断空格的上面
				if ((str[null / 10 + 1][0] != str[null / 10 - 1][0] && count % 4 != 0)
					|| (str[null / 10 + 1][0] == str[null / 10 - 1][0] && count % 4 == 0))
				{
					str[null / 10][0] = str[null / 10 - 1][0];
					str[null / 10 - 1][0] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//判断空格的右边
				if ((str[null / 10 + 1][0] != str[null / 10][1] && count % 4 != 0)
					|| (str[null / 10 + 1][0] == str[null / 10][1] && count % 4 == 0))
				{
					str[null / 10][0] = str[null / 10][1];
					str[null / 10][1] = 'N';
					tail = null;
					null = null + 1;
					count++;
				}
				else
				{
					continue;
				}
			}
			//空格在每一行的最后一个
			else if (null % 10 == row)
			{
				//判断空的上面
				if ((str[null / 10][null % 10 - 1] != str[null / 10 - 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 - 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 - 1][null % 10];
					str[null / 10 - 1][null % 10] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//判断空格的下面
				if ((str[null / 10][null % 10 - 1] != str[null / 10 + 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 + 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 + 1][null % 10];
					str[null / 10 + 1][null % 10] = 'N';
					tail = null;
					null = null + 10;
					count++;
				}
				else
				{
					continue;
				}
			}
			//空格在每一行的中间
			else
			{
				//判断空格的上面
				if ((str[null / 10][null % 10 - 1] != str[null / 10 - 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 - 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 - 1][null % 10];
					str[null / 10 - 1][null % 10] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//判断空格的右面
				if ((str[null / 10][null % 10 - 1] != str[null / 10][null % 10+1] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10][null % 10+1] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10][null % 10 + 1];
					str[null / 10][null % 10 + 1] = 'N';
					tail = null;
					null = null+1;
					count++;
				}
				//判断空格的下面
				if ((str[null / 10][null % 10 - 1] != str[null / 10 + 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 + 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 + 1][null % 10];
					str[null / 10 + 1][null % 10] = 'N';
					tail = null;
					null = null + 10;
					count++;
				}
				else
				{
					continue;
				}
			}
		}
	}
	display((char *)str, 4, 16);
}
int main()
{
	test();
	system("pause");
	return 0;
}