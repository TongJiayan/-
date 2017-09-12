/*1551445 童佳燕 计算机科学与技术1班*/
#include "90-b1.h"
#include "cmd_console_tools.h"

using namespace std;

void four(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	output_value(ball, *size, 0);
	cout << "按回车键显示图形..." << endl;
	while (_getch() != '\r')
		;
	print_noline(ball, *size);
}

void five(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	output_value(ball, *size, 0);
	cout << "按回车键显示图形..." << endl;
	while (_getch() != '\r')
		;
	print_withline(ball, *size);
}

void six(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size);
	init(ball, *size);
	if (judge(ball, *size))
		sign(ball, *size);//标记了可消除项
	else
		cout << "未找到初始可消除项" << endl;
	print_withline(ball, *size);//根据可消除项的标记输出
}

void seven(struct Ball(*ball)[10], struct Size *size)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	int m;//炮灰
	int *ptr = &m;
	input_size(size);
	init(ball, *size);
	print_withline(ball, *size);
	getxy(hout, x, y);//为后面输出文字找基准点
	while (1)
	{
		if (!judge(ball, *size))//已经标记了h_leap,v_leap，与sign配合找出可消除项
		{
			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "\n初始已无可消除项" << endl;
			break;
		}
		else
		{
			sign(ball, *size);//可消除项erase=1
			for (int i = 0; i < size->rows; i++)
				for (int j = 0; j < size->cols; j++)
					if (ball[i][j].erase == 1)
						showstr(hout, 2 + j * 4, (i + 1) * 2, "◆", ball[i][j].value + 7, COLOR_WHITE);
			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "按回车键进行数组下降除0的操作：" << endl;
			while (_getch() != '\r')
				;
			eliminate(ball, *size,ptr,0);//erase=1的项消除
			fall_block(ball, *size);//下落，起点除了value继承终点的value，其余回到初始值;终点的erase=1

			gotoxy(hout, 0, y + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			cout << "                                                    ";
			gotoxy(hout, 0, y + 1);
			cout << "按回车键进行新值填充：";
			while (_getch() != '\r')
				;
			fill(ball, *size);//erase=1的项获得新值，并画出伪图形
		}
	}
	gotoxy(hout, 0, y + 1);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	cout << "按回车键显示消除提醒...";
	while (_getch() != '\r')
		;
	prompt_block(ball, *size);//对所有移动可消除项进行remove标记，并进行相应的表示
	gotoxy(hout, 0, y + 1);
}


void eight(struct Ball(*ball)[10], struct Size *size)
{
	struct Place position[2] = { {0,0},{0,0} };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	struct Place place;
	int &x = place.x;
	int &y = place.y;
	int begin_leap = 0,sum=0;//begin_leap用于控制是否开始记录
	int *ptr_sum = &sum;//sum用于分数记录
	input_size(size);
	init(ball, *size);
	print_withline(ball, *size);
	getxy(hout, x, y);
	while (1)
	{
		while (1)
		{
			/*每次进入都重写所有项的值，避免上一轮遗留下未改变的值，虽然有浪费，
			但程序更加直观，更安全*/
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
				cout << "\n初始已无可消除项" << endl;
				break;
			}
			else
			{
				sign(ball, *size);
				for (int i = 0; i < size->rows; i++)
					for (int j = 0; j < size->cols; j++)
						if (ball[i][j].erase == 1)
							showstr(hout, 2 + j * 4, (i + 1) * 2, "◆", ball[i][j].value + 7, COLOR_WHITE);
				eliminate(ball, *size,ptr_sum,begin_leap);//
				gotoxy(hout, 0, y);
				setcolor(hout, 0, COLOR_HWHITE);
				cout << "得分：" << *ptr_sum << endl;
				fall_block(ball, *size);
				fill(ball, *size);
			}	
		}
		begin_leap+=1;//出了初始消除阶段后，开始记录消除球的个数
		if (!prompt_block(ball, *size))
			break;
		get_mouse(ball, *size, position,y);//获得鼠标点击的两颗球的位置（在数组中的位置）
		exchange(ball, *size, position);//交换位置
		
	}
	gotoxy(hout, 0, y + 3);
	cout << "game over！" << endl;
}

void ninth(struct Ball(*ball)[10], struct Size *size)
{
	ifstream fin;
	system("cls");
	cout << "请输入学号" << endl;
	char no[20],file[40]="\0";//加\0，否则字符串数组遇不到尾零会停不下来
	cin >> no;
	strcat_s(file,"test\\");//no数组开的不够大，数组越界，编译器没有提示，只是直接结束
	strcat_s(file, no);
	strcat_s(file, ".dat");
	fin.open(file, ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败" << endl;
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
		cout << "\n可选择的消除提示（不同色块标志）：\n ";
		output_value(ball, *size, 1);
	}
	else
		cout << "没有可以消除的项" << endl;
	cout << "\n答案文件的内容" << endl;
	file[0] = '\0';
	strcat_s(file, "test\\");//no数组开的不够大，数组越界，编译器没有提示，只是直接结束
	strcat_s(file, no);
	strcat_s(file, ".dat");
	fin.open(file, ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	for (int i = 0; i < size->rows; i++)
		for (int j = 0; j < size->cols; j++)
			fin >> ball[i][j].value;
	output_value(ball, *size, 1);
}