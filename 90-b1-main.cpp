/*1551445 童佳燕 计算机科学与技术1班*/
#include "90-b1.h"
#include "cmd_console_tools.h"
using namespace std;
int main()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(unsigned int(time(0)));
	setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
	struct Ball ball[10][10];
	struct Size s;
	struct Size *size = &s;
	char choice = '1';
	while (choice != '0')
	{
		system("cls");
		setfontsize(hout, L"新宋体", 15);
		print_menu();

		for (int i = 0; i<10; i++)
			for (int j = 0; j < 10; j++)
			{
				ball[i][j].v_leap = 0;
				ball[i][j].h_leap = 0;
				ball[i][j].value = 0;
				ball[i][j].erase = 0;
				ball[i][j].remove = 0;
			}

		cout << "请输入[0-9] ";
		cin >> choice;
		if (!(choice >= '0'&&choice <= '9'))
			continue;
		switch (choice)
		{
		case '1':
			one(ball, size);
			end();//?为啥没有这句话运行完input后就结束了，后面不管了？？？？
			break;
		case '2':
			two(ball, size);
			end();
			break;
		case '3':
			three(ball, size);
			end();
			break;
		case '4':
			four(ball, size);
			end();
			break;
		case '5':
			five(ball, size);
			end();
			break;
		case '6':
			six(ball, size);
			end();
			break;
		case '7':
			seven(ball, size);
			end();
			break;
		case '8':
			eight(ball, size);
			end();
			break;
		case'9':
			ninth(ball, size);
			end();
			break;
		default:break;
		}
	}
	return 0;
}