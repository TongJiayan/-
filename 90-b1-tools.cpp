/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include "90-b1.h"
#include "cmd_console_tools.h"
using namespace std;

/*��ӡ�˵�*/
void print_menu()
{
	cout << "-------------------------------------" << endl;
	cout << "1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������" << endl;
	cout << "2.�ڲ����飬������ʼ����������0�����䲢��0���" << endl;
	cout << "3.�ڲ����飬������ʼ������������������ʾ" << endl;
	cout << "4.n*n�Ŀ�ܣ��޷ָ��ߣ�����ʾ��ʼ״̬" << endl;
	cout << "5.n*n�Ŀ�ܣ��зָ��ߣ�����ʾ��ʼ״̬" << endl;
	cout << "6.n*n�Ŀ�ܣ��зָ��ߣ�����ʾ��ʼ״̬����ʼ��������" << endl;
	cout << "7.n*n�Ŀ�ܣ��зָ��ߣ���������ʼ�����������ʾ������ʾ" << endl;
	cout << "8.cmdͼ�ν���������" << endl;
	cout << "9.���ļ���ȡ��������֤����������ʾ���㷨����ȷ��" << endl;
	cout << "0.�˳�" << endl;
	cout << "--------------------------------------" << endl;
}


/*�����У���*/
void input_size(struct Size *size)
{
	system("cls");
	cout << "������������5-9��";
	cin >> (*size).rows;
	check_rows_cols(&(size->rows));//��rows�����жϣ���������ʣ�����Ҫ�����룬ͬʱ��������������

	cout << "������������5-9��";
	cin >> (*size).cols;
	check_rows_cols(&(size->cols));
}

//���������н��м��  rc��ָ��
void check_rows_cols(int *rc)
{
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (*rc <5 || *rc>9)
	{
		cout << "�����������������.";
		getxy(hout, x, y);
		gotoxy(hout, 17, y - 1);
		cout << "  ";
		gotoxy(hout, 17, y - 1);
		cin >> *rc;
	}
	cout << endl;
}

void init(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(unsigned int(time(0)));
	for (int i = 0; i < size.rows; i++)
		for (int j = 0; j < size.cols; j++)
			if (ball[i][j].value == 0||ball[i][j].erase ==1)
				(*(ball + i) + j)->value = rand() % 9 + 1;
}

void output_value(struct Ball(*ball)[10], struct Size size, int n)//n�����ж��Ƿ���Ҫ����ɫ���
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "��ʼ����Ϊ��" << endl;
	cout << "  |";
	for (int j = 0; j < size.cols; j++)
		cout << setw(3) << j + 1;
	cout << endl;
	cout << "----";
	for (int i = 0; i < size.cols; i++)
		cout << "---";
	cout << endl;

	for (int i = 0; i < size.rows; i++)
	{
		cout << char(i + 65) << setw(2) << "|";
		for (int j = 0; j < size.cols; j++)
		{
			setcolor(hout, 0, 7);
			cout << "  ";
			if (n && ( ball[i][j].erase == 1 || ball[i][j].value == 0||ball[i][j].remove ==1))
				setcolor(hout, 14, 9);
			if (ball[i][j].value > 90)
			{
				setcolor(hout, 14, 9);
				ball[i][j].value -= 90;
			}
			cout << ball[i][j].value;
			setcolor(hout, 0, 7);
		}
		cout << endl;
	}
}
/*��ӡ���������End�����ж�*/
void end()
{
	struct Place place;
	int &x = place.x, &y = place.y;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	cout << "\n��С�������������End����...";
	char End[4];//���������ַ�
	for (int i = 0; i < 3; i++)
		cin >> End[i];
	End[3] = '\0';//����β���������ַ��������
	if (strcmp("End", End))//�Ƚ��ַ���
	{
		cout << "�����������������";
		while (1)
		{
			getxy(hout, x, y);
			gotoxy(hout, 28, y - 1);
			cout << "        ";
			gotoxy(hout, 28, y - 1);
			for (int i = 0; i < 3; i++)
				cin >> End[i];
			End[3] = '\0';
			if (!(strcmp("End", End)))
				break;
		}
	}
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	setconsoleborder(hout, 80, 21, 21);
	setfontsize(hout, L"������", 15);
}

int judge(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for (int i = 1; i < size.rows - 1; i++)
		for (int j = 0; j < size.cols; j++)
			if (ball[i][j].value == ball[i + 1][j].value &&ball[i][j].value == ball[i - 1][j].value)
			{
				leap = 1;
				ball[i][j].v_leap = 1;
			}
	for (int i = 0; i<size.rows; i++)
		for (int j = 1; j<size.cols - 1; j++)
			if (ball[i][j].value == ball[i][j + 1].value&&ball[i][j].value == ball[i][j - 1].value)
			{
				leap = 1;
				ball[i][j].h_leap = 1;
			}
	return leap;
}

void sign(struct Ball(*ball)[10], struct Size size)
{
	for (int i = 1; i < size.rows - 1; i++)
		for (int j = 0; j < size.cols; j++)
			if (ball[i][j].v_leap == 1)
			{
				ball[i - 1][j].erase = 1;
				ball[i][j].erase = 1;
				ball[i + 1][j].erase = 1;
			}
	for (int i = 0; i<size.rows; i++)
		for (int j = 1; j < size.cols - 1; j++)
			if (ball[i][j].h_leap == 1)
			{
				ball[i][j - 1].erase = 1;
				ball[i][j].erase = 1;
				ball[i][j + 1].erase = 1;
			}
}

void fall(struct Ball(*ball)[10], struct Size size)
{
	for (int j = 0; j<size.cols; j++)
		for (int i = size.rows - 1; i >= 0; i--)
		{
			if (ball[i][j].erase == 1)
			{
				int ii = i - 1;
				for (; ii >= 0; ii--)
					if (ball[ii][j].erase == 0)
						break;
				if (ii >= 0)
				{
					ball[i][j].erase = 0;
					ball[i][j].value = ball[ii][j].value;
					ball[ii][j].erase = 1;

					ball[i][j].h_leap = 0;
					ball[i][j].v_leap = 0;
					
				}
			}
		}
	for (int i = 0; i<size.rows; i++)
		for (int j = 0; j<size.cols; j++)
			if (ball[i][j].erase == 1)
			{
				ball[i][j].value = 0;
				ball[i][j].h_leap = 0;
				ball[i][j].v_leap = 0;
			}
}

/* 0 1 0
   0 1 0
   1 0 1
   0 1 0   �Ը���������ж�
*/
int prompt_1(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for (int i = 0; i < size.rows - 2; i++)
		for (int j = 0; j < size.cols; j++)
		{
			if (ball[i][j].value == ball[i + 1][j].value)
			{
				if (ball[i + 3][j].value == ball[i][j].value && i < size.rows - 3)
				{
					leap = 1;
					ball[i + 2][j].remove = 1;
					ball[i + 3][j].remove = 1;
				}
				if (ball[i + 2][j + 1].value == ball[i][j].value && j < size.cols - 1)
				{
					leap = 1;
					ball[i + 2][j].remove = 1;
					ball[i + 2][j + 1].remove = 1;
				}
				if (ball[i + 2][j - 1].value == ball[i][j].value && j > 0)
				{
					leap = 1;
					ball[i + 2][j].remove = 1;
					ball[i + 2][j - 1].remove = 1;
				}
			}
		}
	return leap;
}
/* 0 1 0
   1 0 1
   0 1 0
   0 1 0   �Ը���������ж�
*/
int prompt_2(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for (int i = size.rows - 1; i > 1; i--)
		for (int j = 0; j < size.cols; j++)
		{
			if (ball[i][j].value == ball[i - 1][j].value)
			{
				if (ball[i - 3][j].value == ball[i][j].value && i > 2)
				{
					leap = 1;
					ball[i - 2][j].remove = 1;
					ball[i - 3][j].remove = 1;
				}
				if (ball[i - 2][j + 1].value == ball[i][j].value && j < size.cols - 1)
				{
					leap = 1;
					ball[i - 2][j].remove = 1;
					ball[i - 2][j + 1].remove = 1;
				}
				if (ball[i - 2][j - 1].value == ball[i][j].value && j > 0)
				{
					leap = 1;
					ball[i - 2][j].remove = 1;
					ball[i - 2][j - 1].remove = 1;
				}
			}
		}
	return leap;
}
/*0 0 1 0
  1 1 0 1
  0 0 1 0
  */
int prompt_3(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for (int i =0;i<size.rows ;i++)
		for (int j = 0; j < size.cols-2; j++)
		{
			if (ball[i][j].value == ball[i][j+1].value)
			{
				if (ball[i][j+3].value == ball[i][j].value && j<size.cols-3)
				{
					leap = 1;
					ball[i ][j+2].remove = 1;
					ball[i][j+3].remove = 1;
				}
				if (ball[i -1][j + 2].value == ball[i][j].value && i>0)
				{
					leap = 1;
					ball[i ][j+2].remove = 1;
					ball[i - 1][j + 2].remove = 1;
				}
				if (ball[i +1][j +2].value == ball[i][j].value && i<size.rows-1)
				{
					leap = 1;
					ball[i+1][j+2].remove = 1;
					ball[i ][j +2].remove = 1;
				}
			}
		}
	return leap;
}
/*   
  0 1 0 0
  1 0 1 1 
  0 1 0 0
*/
int prompt_4(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for (int i = 0; i<size.rows; i++)
		for (int j = size.cols-1; j >1; j--)
		{
			if (ball[i][j].value == ball[i][j - 1].value)
			{
				if (ball[i][j - 3].value == ball[i][j].value && j>2)
				{
					leap = 1;
					ball[i][j - 2].remove = 1;
					ball[i][j -3].remove = 1;
				}
				if (ball[i - 1][j -2].value == ball[i][j].value && i>0)
				{
					leap = 1;
					ball[i][j -2].remove = 1;
					ball[i - 1][j - 2].remove = 1;
				}
				if (ball[i + 1][j-2].value == ball[i][j].value && i<size.rows - 1)
				{
					leap = 1;
					ball[i + 1][j - 2].remove = 1;
					ball[i][j - 2].remove = 1;
				}
			}
		}
	return leap;
}
/*
   0 1 0
   1 0 1
   0 1 0
*/
int prompt_5(struct Ball(*ball)[10], struct Size size)
{
	int leap = 0;
	for(int i=0;i<size.rows;i++)
		for(int j=1;j<size.cols-1;j++)
			if (ball[i][j - 1].value == ball[i][j + 1].value)
			{
				if (ball[i - 1][j].value == ball[i][j - 1].value &&i>=1)
				{
					leap = 1;
					ball[i][j].remove = 1;
					ball[i - 1][j].remove = 1;
				}
				if (ball[i + 1][j].value == ball[i][j - 1].value && i<size.cols-1)
				{
					leap = 1;
					ball[i][j].remove = 1;
					ball[i+1][j].remove = 1;
				}
			}
	for(int i=1;i<size.rows-1;i++)
		for(int j=0;j<size.cols;j++)
			if (ball[i-1][j ].value == ball[i+1][j].value )
			{
				if (ball[i][j-1].value == ball[i+1][j].value &&j>=1)
				{
					leap = 1;
					ball[i][j - 1].remove = 1;
					ball[i][j].remove = 1;
				}
				if (ball[i + 1][j].value == ball[i][j+1].value &&j<size.cols -1)
				{
					leap = 1;
					ball[i][j].remove = 1;
					ball[i ][j+1].remove = 1;
				}
			}
	return leap;
}

void print_noline(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const int r = size.rows  + 6;
	setconsoleborder(hout, 35, r, 35);
	setfontsize(hout, L"������", 20);
	cout << "��Ļ��" << size.rows + 6 << "��" << 35 << "��" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < size.cols + 2; i++)
	{
		Sleep(1);
		if (i == 0)
			showstr(hout, 2 * i, 1, "��", COLOR_HWHITE, COLOR_BLACK);
		else if (i == size.cols + 1)
			showstr(hout, 2 * i, 1, "��", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, 1, "��", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i <size.cols + 2; i++)
	{
		Sleep(1);
		if (i == 0)
			showstr(hout, 2 * i, size.rows + 2, "��", COLOR_HWHITE, COLOR_BLACK);
		else if (i == size.cols + 1)
			showstr(hout, 2 * i, size.rows + 2, "��", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, size.rows + 2, "��", COLOR_HWHITE, COLOR_BLACK);
	}

	for (int j = 0; j < size.rows; j++)
	{
		Sleep(1);
		showstr(hout, 0, 2 + j, "��", COLOR_HWHITE, COLOR_BLACK);
		showstr(hout, 2 * (size.cols + 1), 2 + j, "��", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i < size.rows; i++)
		for (int j = 0; j < size.cols; j++)
		{
			Sleep(1);
			showstr(hout, 2 * (j + 1), i + 2, "��", ball[i][j].value + 7, COLOR_WHITE);
		}
	cout << endl << endl;
}

/*���зָ��ߵ�����*/
void print_withline(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int r = size.rows * 2 + 5;
	int c = size.cols * 2 + 21;
	int bf_c, bf_r;
	getconsoleborder(hout, c, r, bf_c, bf_r);
	int x, y;
	setconsoleborder(hout, c, r, c);
	setfontsize(hout, L"������", 20);
	cout << "��Ļ��" << r << "��" << c << "��" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < 2 * size.rows + 1; i++)
		for (int j = 0; j < 2 * size.cols + 1; j++)
		{
			Sleep(1);
			if (i == 0)
			{
				if (j == 0)
					showstr(hout, 0, 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols)
					showstr(hout, j * 2, 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols - 1)
					showstr(hout, j * 2, 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, 1, "��", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, 1, "��", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else if (i == 2 * size.rows)
			{
				if (j == 0)
					showstr(hout, 0, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols)
					showstr(hout, j * 2, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols - 1)
					showstr(hout, j * 2, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else
			{
				if (j == 0)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else if (j == size.cols * 2)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
				else
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "  ", COLOR_HWHITE, COLOR_BLACK);
						else
							showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
					}
					else
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
						else if (j != 0 && j != size.cols * 2)
							showstr(hout, 2 * j, i + 1, "��", COLOR_HWHITE, COLOR_BLACK);
					}
			}
			getxy(hout, x, y);
		}
	for (int i = 0; i < size.rows; i++)
		for (int j = 0; j < size.cols; j++)
		{
			Sleep(1);
			if(ball[i][j].erase ==1)
				showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
			else
				showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
		}
				
	gotoxy(hout, 0, y + 1);
	setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
}
void eliminate(struct Ball(*ball)[10], struct Size size,int *ptr_sum,int begin_leap)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i<size.rows; i++)
		for (int j = 0; j < size.cols; j++)
			if (ball[i][j].erase == 1)
			{
				showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
				if(begin_leap!=0)
					(*ptr_sum)++;
				Sleep(200);
				showstr(hout, 2 + j * 4, (i + 1) * 2, "  ", COLOR_HWHITE, COLOR_WHITE);
			}
}

void fall_block(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int j = 0; j<size.cols; j++)
		for (int i = size.rows - 1; i >= 0; i--)
		{
			if (ball[i][j].erase == 1)
			{
				int ii = i - 1;
				for (; ii >= 0; ii--)
					if (ball[ii][j].erase == 0)
						break;
				if (ii >= 0)
				{
					ball[i][j].erase = 0;
					ball[i][j].value = ball[ii][j].value;
					ball[ii][j].erase = 1;
	
					ball[i][j].h_leap = 0;
					ball[i][j].v_leap = 0;
					ball[i][j].remove = 0;
					
					for (int k = ii; k < i; k++)
					{
						Sleep(60);
						showstr(hout, 2 + j * 4, (k + 1) * 2, "  ", COLOR_HWHITE, COLOR_WHITE);
						Sleep(30);
						showstr(hout, 2 + j * 4, (k + 2) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
					}
					
				}
			}
		}
}
//remove�൱�ڿ�������ʾ   erase��ʾ�����Ѿ�����������Ҳ�����ѳ�ֱ��
void fill(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	init(ball, size);
	for(int i=0;i<size.rows ;i++)
		for(int j=0;j<size.cols;j++)
			if (ball[i][j].erase == 1)
			{
				Sleep(100);
				showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
			}
}

int prompt_block(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int leap = 0;
	for (int i = 0; i<size.rows; i++)
		for (int j = 0; j<size.cols; j++)
				showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
	if (prompt_1(ball, size) + prompt_2(ball,size) + prompt_3(ball, size) + prompt_4(ball, size) + prompt_5(ball, size))
	{
		leap = 1;
		for(int i=0;i<size.rows ;i++)
			for(int j=0;j<size.cols;j++)
				if(ball[i][j].remove ==1)
					showstr(hout, 2 + j * 4, (i + 1) * 2, "��", ball[i][j].value + 7, COLOR_WHITE);
	}
	return leap;
}


void get_mouse(struct Ball(*ball)[10], struct Size size,struct Place position[2],int Y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	int loop = 1;
	int click_begin = 0;
	enable_mouse(hin);
	int x,y,action;
	setcursor(hout, CURSOR_INVISIBLE);
	while (loop)
	{
		action = read_mouse(hin, x, y);//��ȡ���Ķ�����λ��
		gotoxy(hout, 0, Y+1);
		setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
		int y_i = (y - 1) / 2;//0-rows-1
		int x_j = x / 4;//0-cols-1
		if ((y - 1) / 2 + 1 > 0 && (y - 1) / 2 + 1 <= size.rows && (x / 4 + 1) > 0 && (x / 4 + 1) <= size.cols)
		{
			cout << "[��ǰ����]" << char(y_i + 'A') << "��" << x_j + 1 << "��";
			switch (action)
			{
			case MOUSE_RIGHT_BUTTON_CLICK:
				end();
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (ball[y_i][x_j].remove ==1&& click_begin == 0)
				{
					position[0] = {x_j,y_i};
					showstr(hout, 2 + position[0].x * 4, position[0].y * 2 + 2, "��", ball[y_i][x_j].value + 7, COLOR_WHITE);
					click_begin++;
					break;
				}
				else if (ball[y_i][x_j].remove == 1&& abs(y_i-position[0].y +x_j-position[0].x)==1)//
				{
					position[1] = { x_j,y_i };
					loop = 0;
					break;
				}

			}
		}
	}
}

void exchange(struct Ball(*ball)[10], struct Size size, struct Place position[2])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	showstr(hout, 2 + position[1].x * 4, position[1].y * 2 + 2, "��", ball[position[0].y ][position[0].x].value + 7, COLOR_WHITE);
	showstr(hout, 2 + position[0].x * 4, position[0].y * 2 + 2, "��", ball[position[1].y ][position[1].x].value + 7, COLOR_WHITE);
	int v = ball[position[0].y][position[0].x].value;
	ball[position[0].y][position[0].x].value = ball[position[1].y][position[1].x].value;
	ball[position[1].y][position[1].x].value = v;
}



