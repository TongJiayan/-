/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include "90-b1.h"
#include "cmd_console_tools.h"

using namespace std;

void four(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	output_value(ball, *size, 0);
	cout << "���س�����ʾͼ��..." << endl;
	while (_getch() != '\r')
		;
	print_noline(ball, *size);
}

void five(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	output_value(ball, *size, 0);
	cout << "���س�����ʾͼ��..." << endl;
	while (_getch() != '\r')
		;
	print_withline(ball, *size);
}

void six(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	if (judge(ball, *size))
		sign(ball, *size);//����˿�������
	else
		cout << "δ�ҵ���ʼ��������" << endl;
	print_withline(ball, *size);//���ݿ�������ı�����
}

void seven(struct Ball(*ball)[10], struct Size *size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	int m;//�ڻ�
	int *ptr = &m;
	input_size(size);
	init(ball, *size);
	print_withline(ball, *size);
	getxy(hout, x, y);//Ϊ������������һ�׼��
	while (1)
	{
		if (!judge(ball, *size))//�Ѿ������h_leap,v_leap����sign����ҳ���������
		{
			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "\n��ʼ���޿�������" << endl;
			break;
		}
		else
		{
			sign(ball, *size);//��������erase=1
			for (int i = 0; i < size->rows; i++)
				for (int j = 0; j < size->cols; j++)
					if (ball[i][j].erase == 1)
						showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "���س������������½���0�Ĳ�����" << endl;
			while (_getch() != '\r')
				;
			eliminate(ball, *size,ptr,0);//erase=1��������
			fall_block(ball, *size);//���䣬������value�̳��յ��value������ص���ʼֵ;�յ��erase=1

			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "                                                    ";
			gotoxy(hout, 0, y + 1);
			cout << "���س���������ֵ��䣺";
			while (_getch() != '\r')
				;
			fill(ball, *size);//erase=1��������ֵ��������αͼ��
		}
	}
	gotoxy(hout, 0, y + 1);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	cout << "���س�����ʾ��������...";
	while (_getch() != '\r')
		;
	prompt_block(ball, *size);//�������ƶ������������remove��ǣ���������Ӧ�ı�ʾ
	gotoxy(hout, 0, y + 1);
}


void eight(struct Ball(*ball)[10], struct Size *size)
{
	struct Place position[2] = { {0,0},{0,0} };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	int begin_leap = 0,sum=0;//begin_leap���ڿ����Ƿ�ʼ��¼
	int *ptr_sum = &sum;//sum���ڷ�����¼
	input_size(size);
	init(ball, *size);
	print_withline(ball, *size);
	getxy(hout, x, y);
	while (1)
	{
		while (1)
		{
			/*ÿ�ν��붼��д�������ֵ��������һ��������δ�ı��ֵ����Ȼ���˷ѣ�
			���������ֱ�ۣ�����ȫ*/
			for (int i = 0; i < size->rows; i++)
				for (int j = 0; j < size->cols; j++)
				{
					ball[i][j].erase = 0;
					ball[i][j].h_leap = 0;
					ball[i][j].v_leap = 0;
					ball[i][j].remove = 0;
				}
			if (!judge(ball, *size))
			{
				gotoxy(hout, 0, y + 1);
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
				cout << "\n��ʼ���޿�������" << endl;
				break;
			}
			else
			{
				sign(ball, *size);
				for (int i = 0; i < size->rows; i++)
					for (int j = 0; j < size->cols; j++)
						if (ball[i][j].erase == 1)
							showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
				eliminate(ball, *size,ptr_sum,begin_leap);//
				gotoxy(hout, 0, y);
				setcolor(hout, 0, COLOR_HWHITE);
				cout << "�÷֣�" << *ptr_sum << endl;
				fall_block(ball, *size);
				fill(ball, *size);
			}	
		}
		begin_leap+=1;//���˳�ʼ�����׶κ󣬿�ʼ��¼������ĸ���
		if (!prompt_block(ball, *size))
			break;
		get_mouse(ball, *size, position,y);//�����������������λ�ã��������е�λ�ã�
		exchange(ball, *size, position);//����λ��
		
	}
	gotoxy(hout, 0, y + 3);
	cout << "game over��" << endl;
}

void ninth(struct Ball(*ball)[10], struct Size *size)
{
	ifstream fin;
	system("cls");
	cout << "������ѧ��" << endl;
	char no[20],file[40]="\0";//��\0�������ַ�������������β���ͣ������
	cin >> no;
	strcat_s(file,"test\\");//no���鿪�Ĳ���������Խ�磬������û����ʾ��ֻ��ֱ�ӽ���
	strcat_s(file, no);
	strcat_s(file, ".dat");
	fin.open(file, ios::in);
	if (!fin.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	//fin.close();
	fin >> size->rows;
	fin >> size->cols;

	for (int i = 0; i < size->rows; i++)
		for (int j = 0; j < size->cols; j++)
		    fin >> ball[i][j].value;
	output_value(ball, *size, 0);
	if (prompt_1(ball, *size) + prompt_2(ball, *size) + prompt_3(ball, *size) + prompt_4(ball, *size) + prompt_5(ball, *size))
	{
		cout << "\n��ѡ���������ʾ����ͬɫ���־����\n ";
		output_value(ball, *size, 1);
	}
	else
		cout << "û�п�����������" << endl;
	cout << "\n���ļ�������" << endl;
	file[0] = '\0';
	strcat_s(file, "test\\");//no���鿪�Ĳ���������Խ�磬������û����ʾ��ֻ��ֱ�ӽ���
	strcat_s(file, no);
	strcat_s(file, ".dat");
	fin.open(file, ios::in);
	if (!fin.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	for (int i = 0; i < size->rows; i++)
		for (int j = 0; j < size->cols; j++)
			fin >> ball[i][j].value;
	output_value(ball, *size, 1);
}