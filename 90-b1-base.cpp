/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include "90-b1.h"
#include "cmd_console_tools.h"
using namespace std;

void one(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size); //�����У���
	init(ball, *size);//������ball.value=0����erase=1���������ֵvalue  ��erase����������ȥ��������
	output_value(ball, *size, 0);//����ڲ�����

	cout << "\n���س�������Ѱ�ҳ�ʼ��������Ĳ���...";
	while (_getch() != '\r')
		;

	/*������������һ��/һ������С���м��һ�������  h_leap=1����v_leap=1,
	���� �����sign�������������������������erase=1�ı��*/

	/*���ڵ����⣺���ظ��жϵ����࣬����Ϊ�˳���Ŀɶ��ԣ�����Ҳ���Ǻܶ࣬���û���޸�*/
	if (!judge(ball, *size))
		cout << "��ʼ���޿�������" << endl;
	else
	{
		cout << "\n��ʼ���������ͬɫ��־����\n";

        /*����������h_leap����v_leapΪ1��С�����»����������ڵ�С����б�� erase=1*/
		sign(ball, *size);

		output_value(ball, *size, 1);
	}
}

void two(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	output_value(ball, *size, 0);
	while (1)
	{
		cout << "\n���س�������Ѱ�ҳ�ʼ��������Ĳ���...";
		while (_getch() != '\r')
			;
		if (!judge(ball, *size))
		{
			cout << "\n��ʼ���޿�������" << endl;
			break;
		}
		else
		{
			cout << "\n��ʼ���������ͬɫ��־����\n";
			sign(ball, *size);
			output_value(ball, *size, 1);

			cout << "\n���س������������½���0�Ĳ�����" << endl;
			while (_getch() != '\r')
				;

			//�������ϱ���������erase=1����������ȥҪ��ģ���Ϊ��㣬
			//��erase=0ΪҪ���ҵ��յ㣬�յ�������eraseֵ�Ի�,��������value���ָ�����ʼֵ
			fall(ball, *size);

			output_value(ball, *size, 0);
			cout << "\n���س���������ֵ���䣺" << endl;
			while (_getch() != '\r')
				;
			init(ball, *size);//������ֵ���
			output_value(ball, *size, 1);

			for (int i = 0; i < size->rows; i++)
				for (int j = 0; j < size->cols; j++)
					if (ball[i][j].erase == 1)
						ball[i][j].erase = 0;		
		}
	}
}

void three(struct Ball(*ball)[10], struct Size *size)
{
	two(ball, size);
	//promptϵ�к�������ֵ�����Ƿ����ƶ������������ͬʱ�����������С���removeֵ�ı�=1����Ϊ���ƶ������ı�־
	if (prompt_1(ball, *size) + prompt_2(ball, *size) + prompt_3(ball, *size) + prompt_4(ball, *size) + prompt_5(ball, *size))
	{
		cout << "\n��ѡ���������ʾ����ͬɫ���־����\n ";
		output_value(ball, *size, 1);
	}
	else
		cout << "û�п�����������" << endl;
}

