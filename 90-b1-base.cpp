/*1551445 童佳燕 计算机科学与技术1班*/
#include "90-b1.h"
#include "cmd_console_tools.h"
using namespace std;

void one(struct Ball(*ball)[10], struct Size *size)
{
	input_size(size); //输入行，列
	init(ball, *size);//对所有ball.value=0或者erase=1的球随机赋值value  （erase代表满足消去的条件）
	output_value(ball, *size, 0);//输出内部数组

	cout << "\n按回车键进行寻找初始可消除项的操作...";
	while (_getch() != '\r')
		;

	/*对满足条件的一排/一列三个小球中间的一个做标记  h_leap=1或者v_leap=1,
	方便 后边用sign函数对所有满足条件的球进行erase=1的标记*/

	/*存在的问题：有重复判断的冗余，但是为了程序的可读性，冗余也不是很多，因此没有修改*/
	if (!judge(ball, *size))
		cout << "初始已无可消除项" << endl;
	else
	{
		cout << "\n初始可消除项（不同色标志）：\n";

        /*遍历，遇到h_leap或者v_leap为1的小球，上下或者左右相邻的小球进行标记 erase=1*/
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
		cout << "\n按回车键进行寻找初始可消除项的操作...";
		while (_getch() != '\r')
			;
		if (!judge(ball, *size))
		{
			cout << "\n初始已无可消除项" << endl;
			break;
		}
		else
		{
			cout << "\n初始可消除项（不同色标志）：\n";
			sign(ball, *size);
			output_value(ball, *size, 1);

			cout << "\n按回车键进行数组下降除0的操作：" << endl;
			while (_getch() != '\r')
				;

			//从下往上遍历，遇到erase=1，即满足消去要求的，作为起点，
			//以erase=0为要求找到终点，终点与起点的erase值对换,将起点除了value都恢复到初始值
			fall(ball, *size);

			output_value(ball, *size, 0);
			cout << "\n按回车键进行新值补充：" << endl;
			while (_getch() != '\r')
				;
			init(ball, *size);//进行新值填充
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
	//prompt系列函数返回值代表是否有移动可消除情况；同时对满足情况的小球的remove值改变=1，作为可移动消除的标志
	if (prompt_1(ball, *size) + prompt_2(ball, *size) + prompt_3(ball, *size) + prompt_4(ball, *size) + prompt_5(ball, *size))
	{
		cout << "\n可选择的消除提示（不同色块标志）：\n ";
		output_value(ball, *size, 1);
	}
	else
		cout << "没有可以消除的项" << endl;
}

