#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
#include<assert.h>

void init(char *str, size_t row,size_t size)
{   //���������������ά���鿴��һά����
	assert(str);
	size_t col = size / row;
	for (size_t i = 0; i < col; i++)
	{
		//��ǰ�����г�ʼ��Ϊ��R���������ɫ
		for (size_t j = 0; j < row/2; j++)
		{
			//i*row�Ǳ�ʾ���ڼ��У�j��ʾ���ڼ��У�
			str[i*row + j] = 'R';
		}
		//���������г�ʼ��Ϊ��B����������ɫ
		for (size_t j = row/2; j < row; j++)
		{
			str[i*col + j] = 'B';
		}
	}
	//��󽫵�һ������Ϊ�ա�N��
	str[0] = 'N';
}

//�������
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
	//�ո���ͷ����һ��
	if (head / 10 + 1 == null / 10)
	{
		//���β��ͷ��ͬһ��
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
		//���β��ͷ����ͬһ��
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
	//�ո���ͷ����һ��
	else
	{
		//���β��ͷ��ͬһ��
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
		//���βû����ͬһ��
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
	//��ͷ��ÿһ�еĿ�ʼ
	if (head % 10 == 0)
	{
		//�ո��ͷ����һ����ͬһ��
		if (null / 10 == head / 10 + 1)
		{
			size_t i = 0;
			for (i = null % 10; i > 1; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(null / 10)*row+i] = 'N';	
		}
		//�ո��ͷ����һ�в���ͬһ��
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
	//��ͷ����ÿһ�еĿ�ʼ
	else
	{
		//�ո��ͷ��ͬһ��
		if (null / 10 == head / 10)
		{
			int i = 0;
			for (i = null % 10; i > head % 10 - 2; i--)
			{
				str[(null / 10)*row + i] = str[(null / 10)*row + i - 1];
			}
			str[(null / 10)*row + i] = 'N';
		}
		//�ո��ͷ����ͬһ��
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
    //��ʼ�������ά����
	init((char *)str, 4, 16);
	display((char *)str, 4, 16);

	//����ͷΪ1����ʾ��0�е�һ��,β�ڸտ�ʼ��ʱ���ͷ�غϣ��յ�λ���ڵ�һ�е�һ��
	//����ǵڶ��еڶ�����Ϊ21
	int head = 1;
	int tail = 1;
	int null = 0;
	size_t row = 4;
	size_t col = 4;
	//������¼ͷ��Ϊ֮��ĸ�����
	int count = 1;
	//��head����һ�����һ�����ҵ�һ���е�һ��Ϊ�յ�ʱ��ѭ������
	while (1)
	{
		//���ȴ�ͷ��β��������Ե��ʱ����һ��

		//����Ѿ��ڰ����һ�У��Ǿ��Ѿ����Խ�����
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
		//���ͷ�պ���һ�е����һ������ô��һ���Ѿ����ú��ˣ������Ϳ��Լ���һ��
		if (head % 10 == row-1)
		{
			col--;
			//ͷ�ͱ���Ǹո���һ�е���һ�еĵ�һ��λ��
			head = head - 10;
		}
		//����ո�պ���ͷ��ǰһ������������ʱ����һ��
		if ((null == head - 1)||(null== head-10))
		{
			Move((char *)str, row, head, tail, null, row*col);
		}
		else
		{
			find_move_null((char *)str, row, head, tail, null, row*col);
			Move((char *)str, row, head, tail, null, row*col);
		}

		//��ʼѰ��β�ͺ���Ӧ��Ҫ���Ŀո�


		//�ӿո���������ҿ�ʼ��
		
		//����ո��ڵ�һ��
		if (null / 10 == 0)
		{
			//����ո��ڵ�һ��

			if (null % 10 == 0)
			{
				//count%4!=0
				//�жϿո����һ���ǲ���Ҫ�����෴�Ŀո�

				//count%4==0
				//�жϿո����һ���ǲ���Ҫ������ͬ�Ŀո�
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
			
			//����ո������һ��
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
			//����ո����м�λ��
			else
			{
				//�жϿո���ұ�
				if ((str[null / 10][null % 10 - 1] != str[null / 10][null % 10 + 1] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10][null % 10 + 1] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10][null % 10 + 1];
					str[null / 10][null % 10 + 1] = 'N';
					tail = null;
					null = null + 1;
					count++;
				}
				//�жϿո���±�
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
		//�ո��ڵ�һ��
		else
		{
			//�ո���ÿһ�еĵ�һ��
			if (null % 10 == 0)
			{
				//�жϿո������
				if ((str[null / 10 + 1][0] != str[null / 10 - 1][0] && count % 4 != 0)
					|| (str[null / 10 + 1][0] == str[null / 10 - 1][0] && count % 4 == 0))
				{
					str[null / 10][0] = str[null / 10 - 1][0];
					str[null / 10 - 1][0] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//�жϿո���ұ�
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
			//�ո���ÿһ�е����һ��
			else if (null % 10 == row)
			{
				//�жϿյ�����
				if ((str[null / 10][null % 10 - 1] != str[null / 10 - 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 - 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 - 1][null % 10];
					str[null / 10 - 1][null % 10] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//�жϿո������
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
			//�ո���ÿһ�е��м�
			else
			{
				//�жϿո������
				if ((str[null / 10][null % 10 - 1] != str[null / 10 - 1][null % 10] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10 - 1][null % 10] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10 - 1][null % 10];
					str[null / 10 - 1][null % 10] = 'N';
					tail = null;
					null = null - 10;
					count++;
				}
				//�жϿո������
				if ((str[null / 10][null % 10 - 1] != str[null / 10][null % 10+1] && count % 4 != 0)
					|| (str[null / 10][null % 10 - 1] == str[null / 10][null % 10+1] && count % 4 == 0))
				{
					str[null / 10][null % 10] = str[null / 10][null % 10 + 1];
					str[null / 10][null % 10 + 1] = 'N';
					tail = null;
					null = null+1;
					count++;
				}
				//�жϿո������
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