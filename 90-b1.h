#pragma once
/*1551445 童佳燕 计算机科学与技术1班*/

#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<iomanip>
#include<fstream>

struct Size
{
	int cols;
	int rows;
};

struct Place
{
	int x;
	int y;
};

struct Ball
{
	int value;
	bool v_leap;
	bool h_leap;
	bool erase;
	bool remove;
};



void print_menu();
void input_size(struct Size *size);
void check_rows_cols(int *rc);
void init(struct Ball(*ball)[10], struct Size size);
void output_value(struct Ball(*ball)[10], struct Size size, int n);
void end();

int judge(struct Ball(*ball)[10], struct Size size);
void sign(struct Ball(*ball)[10], struct Size size);
void fall(struct Ball(*ball)[10], struct Size size);

int prompt_1(struct Ball(*ball)[10], struct Size size);
int prompt_2(struct Ball(*ball)[10], struct Size size);
int prompt_3(struct Ball(*ball)[10], struct Size size);
int prompt_4(struct Ball(*ball)[10], struct Size size);
int prompt_5(struct Ball(*ball)[10], struct Size size); 

void print_noline(struct Ball(*ball)[10], struct Size size);
void print_withline(struct Ball(*ball)[10], struct Size size);

void eliminate(struct Ball(*ball)[10], struct Size size, int *sum, int begin_leap);
void fall_block(struct Ball(*ball)[10], struct Size size);
void fill(struct Ball(*ball)[10], struct Size size);
int prompt_block(struct Ball(*ball)[10], struct Size size);
void get_mouse(struct Ball(*ball)[10], struct Size size, struct Place position[2],int Y);
void exchange(struct Ball(*ball)[10], struct Size size, struct Place position[2]);

void one(struct Ball(*ball)[10], struct Size *size);
void two(struct Ball(*ball)[10], struct Size *size);
void three(struct Ball(*ball)[10], struct Size *size);
void four(struct Ball(*ball)[10], struct Size *size);
void five(struct Ball(*ball)[10], struct Size *size);
void six(struct Ball(*ball)[10], struct Size *size);
void seven(struct Ball(*ball)[10], struct Size *size);
void eight(struct Ball(*ball)[10], struct Size *size);
void ninth(struct Ball(*ball)[10], struct Size *size);