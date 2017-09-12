/*1551445 童佳燕 计算机科学与技术1班*/
#include "90-b1.h"
#include "cmd_console_tools.h"
using namespace std;

/*打印菜单*/
void print_menu()
{
	cout << "-------------------------------------" << endl;
	cout << "1.内部数组，生成初始状态，寻找是否有初始可消除项" << endl;
	cout << "2.内部数组，消除初始可消除项后非0项下落并用0填充" << endl;
	cout << "3.内部数组，消除初始可消除项后查找消除提示" << endl;
	cout << "4.n*n的框架（无分割线），显示初始状态" << endl;
	cout << "5.n*n的框架（有分割线），显示初始状态" << endl;
	cout << "6.n*n的框架（有分割线），显示初始状态及初始可消除项" << endl;
	cout << "7.n*n的框架（有分割线），消除初始可消除项后显示消除提示" << endl;
	cout << "8.cmd图形界面完整版" << endl;
	cout << "9.从文件读取数据以验证查找消除提示的算法的正确性" << endl;
	cout << "0.退出" << endl;
	cout << "--------------------------------------" << endl;
}


/*输入行，列*/
void input_size(struct Size *size)
{
	system("cls");
	cout << "请输入行数（5-9）";
	cin >> (*size).rows;
	check_rows_cols(&(size->rows));//对rows进行判断，如果不合适，重新要求输入，同时更新行数和列数

	cout << "请输入列数（5-9）";
	cin >> (*size).cols;
	check_rows_cols(&(size->cols));
}

//对输入行列进行检查  rc是指向
void check_rows_cols(int *rc)
{
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (*rc <5 || *rc>9)
	{
		cout << "输入错误，请重新输入.";
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

void output_value(struct Ball(*ball)[10], struct Size size, int n)//n用于判断是否需要有颜色标记
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "初始数组为：" << endl;
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
/*打印结束语，输入End进行判断*/
void end()
{
	struct Place place;
	int &x = place.x, &y = place.y;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	cout << "\n本小题结束，请输入End继续...";
	char End[4];//存放输入的字符
	for (int i = 0; i < 3; i++)
		cin >> End[i];
	End[3] = '\0';//加入尾零来控制字符串的输出
	if (strcmp("End", End))//比较字符串
	{
		cout << "输入错误，请重新输入";
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
	setfontsize(hout, L"新宋体", 15);
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
   0 1 0   对该情况进行判断
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
   0 1 0   对该情况进行判断
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
	setfontsize(hout, L"新宋体", 20);
	cout << "屏幕：" << size.rows + 6 << "行" << 35 << "列" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < size.cols + 2; i++)
	{
		Sleep(1);
		if (i == 0)
			showstr(hout, 2 * i, 1, "┍", COLOR_HWHITE, COLOR_BLACK);
		else if (i == size.cols + 1)
			showstr(hout, 2 * i, 1, "┑", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, 1, "─", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i <size.cols + 2; i++)
	{
		Sleep(1);
		if (i == 0)
			showstr(hout, 2 * i, size.rows + 2, "┕", COLOR_HWHITE, COLOR_BLACK);
		else if (i == size.cols + 1)
			showstr(hout, 2 * i, size.rows + 2, "┙", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, size.rows + 2, "─", COLOR_HWHITE, COLOR_BLACK);
	}

	for (int j = 0; j < size.rows; j++)
	{
		Sleep(1);
		showstr(hout, 0, 2 + j, "┃", COLOR_HWHITE, COLOR_BLACK);
		showstr(hout, 2 * (size.cols + 1), 2 + j, "┃", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i < size.rows; i++)
		for (int j = 0; j < size.cols; j++)
		{
			Sleep(1);
			showstr(hout, 2 * (j + 1), i + 2, "○", ball[i][j].value + 7, COLOR_WHITE);
		}
	cout << endl << endl;
}

/*画有分割线的棋盘*/
void print_withline(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int r = size.rows * 2 + 5;
	int c = size.cols * 2 + 21;
	int bf_c, bf_r;
	getconsoleborder(hout, c, r, bf_c, bf_r);
	int x, y;
	setconsoleborder(hout, c, r, c);
	setfontsize(hout, L"新宋体", 20);
	cout << "屏幕：" << r << "行" << c << "列" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < 2 * size.rows + 1; i++)
		for (int j = 0; j < 2 * size.cols + 1; j++)
		{
			Sleep(1);
			if (i == 0)
			{
				if (j == 0)
					showstr(hout, 0, 1, "┍", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols)
					showstr(hout, j * 2, 1, "┑", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols - 1)
					showstr(hout, j * 2, 1, "─", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, 1, "─", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, 1, "┯", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else if (i == 2 * size.rows)
			{
				if (j == 0)
					showstr(hout, 0, i + 1, "┕", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols)
					showstr(hout, j * 2, i + 1, "┙", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * size.cols - 1)
					showstr(hout, j * 2, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┷", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else
			{
				if (j == 0)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "┃", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┝", COLOR_HWHITE, COLOR_BLACK);
				else if (j == size.cols * 2)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "┃", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┥", COLOR_HWHITE, COLOR_BLACK);
				else
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "  ", COLOR_HWHITE, COLOR_BLACK);
						else
							showstr(hout, 2 * j, i + 1, "│", COLOR_HWHITE, COLOR_BLACK);
					}
					else
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
						else if (j != 0 && j != size.cols * 2)
							showstr(hout, 2 * j, i + 1, "┿", COLOR_HWHITE, COLOR_BLACK);
					}
			}
			getxy(hout, x, y);
		}
	for (int i = 0; i < size.rows; i++)
		for (int j = 0; j < size.cols; j++)
		{
			Sleep(1);
			if(ball[i][j].erase ==1)
				showstr(hout, 2 + j * 4, (i + 1) * 2, "◆", ball[i][j].value + 7, COLOR_WHITE);
			else
				showstr(hout, 2 + j * 4, (i + 1) * 2, "○", ball[i][j].value + 7, COLOR_WHITE);
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
				showstr(hout, 2 + j * 4, (i + 1) * 2, "※", ball[i][j].value + 7, COLOR_WHITE);
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
						showstr(hout, 2 + j * 4, (k + 2) * 2, "○", ball[i][j].value + 7, COLOR_WHITE);
					}
					
				}
			}
		}
}
//remove相当于可消除提示   erase表示满足已经满足消除，也就是已成直线
void fill(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	init(ball, size);
	for(int i=0;i<size.rows ;i++)
		for(int j=0;j<size.cols;j++)
			if (ball[i][j].erase == 1)
			{
				Sleep(100);
				showstr(hout, 2 + j * 4, (i + 1) * 2, "○", ball[i][j].value + 7, COLOR_WHITE);
			}
}

int prompt_block(struct Ball(*ball)[10], struct Size size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int leap = 0;
	for (int i = 0; i<size.rows; i++)
		for (int j = 0; j<size.cols; j++)
				showstr(hout, 2 + j * 4, (i + 1) * 2, "○", ball[i][j].value + 7, COLOR_WHITE);
	if (prompt_1(ball, size) + prompt_2(ball,size) + prompt_3(ball, size) + prompt_4(ball, size) + prompt_5(ball, size))
	{
		leap = 1;
		for(int i=0;i<size.rows ;i++)
			for(int j=0;j<size.cols;j++)
				if(ball[i][j].remove ==1)
					showstr(hout, 2 + j * 4, (i + 1) * 2, "◎", ball[i][j].value + 7, COLOR_WHITE);
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
		action = read_mouse(hin, x, y);//读取鼠标的动作和位置
		gotoxy(hout, 0, Y+1);
		setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
		int y_i = (y - 1) / 2;//0-rows-1
		int x_j = x / 4;//0-cols-1
		if ((y - 1) / 2 + 1 > 0 && (y - 1) / 2 + 1 <= size.rows && (x / 4 + 1) > 0 && (x / 4 + 1) <= size.cols)
		{
			cout << "[当前坐标]" << char(y_i + 'A') << "行" << x_j + 1 << "列";
			switch (action)
			{
			case MOUSE_RIGHT_BUTTON_CLICK:
				end();
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (ball[y_i][x_j].remove ==1&& click_begin == 0)
				{
					position[0] = {x_j,y_i};
					showstr(hout, 2 + position[0].x * 4, position[0].y * 2 + 2, "●", ball[y_i][x_j].value + 7, COLOR_WHITE);
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
	showstr(hout, 2 + position[1].x * 4, position[1].y * 2 + 2, "○", ball[position[0].y ][position[0].x].value + 7, COLOR_WHITE);
	showstr(hout, 2 + position[0].x * 4, position[0].y * 2 + 2, "○", ball[position[1].y ][position[1].x].value + 7, COLOR_WHITE);
	int v = ball[position[0].y][position[0].x].value;
	ball[position[0].y][position[0].x].value = ball[position[1].y][position[1].x].value;
	ball[position[1].y][position[1].x].value = v;
}



