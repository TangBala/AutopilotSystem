/**
**************************************************?
*	版本号：1.0
*	作者：Y
*	生成日期：2024—3—18
*	说明：Ac类函数实现空调功能
**************************************************?
**/

#include"ac.h"
#include"init.h"
#include "page.h"
#define PI 3.1415926535
/****************************************
FUNCTION:OpenAircondition
DESCRIBETION:打开菜单中空调页
INPUT:void
REUTRUN:void
****************************************/

void OpenAircondition()
{
	while (1)
	{
		int aircondition_ret = 1, i = 0;
		int num[8];
		FILE* ac_text;

		setfillstyle(1, BLACK);
		bar(0, 0, 640, 490);

		ac_text = fopen("..\\CODE\\text\\ac.txt", "rt");
		for (i = 0; i < 8; i++)
		{
			fscanf(ac_text, "%d ", &num[i]);
		}
		fclose(ac_text);
		DrawTopMid(0);
		DrawHomeRet();
		DrawToHome();
		DrawAirconditionSButton(num);
		DrawAirconditionChangePart(num);
		aircondition_ret = AirconditionMouse(num);

		ac_text = fopen("..\\CODE\\text\\ac.txt", "wt");
		for (i = 0; i < 8; i++)
		{
			fprintf(ac_text, "%d ", num[i]);
		}
		fclose(ac_text);

		if (!aircondition_ret)
			return;
	}
}


/****************************************
FUNCTION:DrawAirconditionChangePart
DESCRIBETION:绘制空调页的可变部分
INPUT:int* num
RETURN:void
****************************************/
void DrawAirconditionChangePart(int* num)
{
	if (num[0] == 1)
	{
		setfillstyle(1, GREEN);
		floodfill(145, 370, LIGHTBLUE);
	}
	if (num[0] == 2)
	{
		setfillstyle(1, GREEN);
		floodfill(472, 370, LIGHTBLUE);
	}
	if (num[1] == 1)
	{
		setfillstyle(1, GREEN);
		floodfill(171, 171, LIGHTBLUE);
		num[1] = 0;
		num[2] = 0;
	}
	if (num[2] == 1)
	{
		setfillstyle(1, GREEN);
		floodfill(471, 171, LIGHTBLUE);
		num[1] = 0;
		num[2] = 0;
	}
}

/****************************************
FUNCTION:DrawAirconditionSButton
DESCRIBETION:绘制菜单中空调所有按钮
INPUT:void
REUTRUN:void
****************************************/
void DrawAirconditionSButton(int* num)
{
	float a, b;
	char* p;
	int i, k;
	a = -PI / 2;
	b = PI / 100;
	Draw(LIGHTBLUE);
	setfillstyle(1, WHITE);
	fillellipse(372 + 100, 375 - 30, 30, 30);
	fillellipse(245 - 100, 375 - 30, 30, 30);
	fillellipse(300, 345, 30, 30);
	fillellipse(170, 210 - 40, 20, 20);
	fillellipse(470, 210 - 40, 20, 20);
	circle(320, 210 - 40, 60);
	circle(320, 210 - 40, 75);
	circle(320, 210 - 40, 90);
	floodfill(320, 210 - 40 - 80, LIGHTBLUE);
	/*line(160,210 - 40,180,210 - 40);
	circle(320,210 - 40,60);
	circle(320,210 - 40,75);
	circle(320,210 - 40,90);
	line(460,210 - 40,480,210 - 40);
	line(470,200 - 40,470,220 - 40);
	setfillstyle(1,GREEN);
	floodfill(320,210 - 40,LIGHTBLUE);*/

	setlinestyle(0, 0, 2);
	circle(245 - 100, 375 - 30, 30);
	circle(372 + 100, 375 - 30, 30);
	circle(300, 345, 30);
	circle(170, 210 - 40, 20);
	circle(470, 210 - 40, 20);
	line(160, 210 - 40, 180, 210 - 40);
	line(460, 210 - 40, 480, 210 - 40);
	line(470, 200 - 40, 470, 220 - 40);
	setfillstyle(1, GREEN);
	floodfill(320, 210 - 40, LIGHTBLUE);
	setlinestyle(0, 0, 1);
	puthz(220 - 100, 410 - 30, "温度", 24, 27, LIGHTBLUE);
	ellipse(245 - 100, 380 - 30, -230, 50, 10, 10);
	ellipse(245 - 100, 380 - 30, -230, 50, 6, 6);
	line(250 - 100, 378 - 30, 250 - 100, 373 - 30);
	line(240 - 100, 378 - 30, 240 - 100, 373 - 30);
	line(250 - 100, 373 - 30, 240 - 100, 373 - 30);
	line(251 - 100, 376 - 30, 251 - 100, 366 - 30);
	line(239 - 100, 376 - 30, 239 - 100, 366 - 30);
	ellipse(245 - 100, 366 - 30, 0, 180, 6, 6);
	setfillstyle(1, DARKGRAY);
	floodfill(245 - 100, 380 - 30, LIGHTBLUE);//温度按钮

	ellipse(372 + 100, 380 - 30, -180, 0, 8, 8);
	ellipse(372 + 100, 380 - 30 - 4, -40, 210, 8, 20);
	ellipse(372 + 100, 380 - 30, 180, 260, 4, 4);
	puthz(352 + 100, 410 - 30, "湿度", 24, 27, LIGHTBLUE);//湿度按钮

	if (num[0] == 2)
	{
		k = (num[4] - 20) / 60.0 * 200;
		p = (int*)malloc(11 * sizeof(int));
		itoa(num[4], p, 10);

		settextstyle(3, 0, 5);
		outtextxy(285, 180 - 40, p);
		settextstyle(3, 0, 3);
		outtextxy(345, 180 - 40, "%");
		puthz(284, 240 - 40, "预设湿度", 16, 20, LIGHTBLUE);//湿度显示
		free(p);
	}
	else
	{

		k = (num[3] - 16) / 14.0 * 200;
		p = (int*)malloc(11 * sizeof(int));
		itoa(num[3], p, 10);

		settextstyle(3, 0, 5);
		outtextxy(285, 180 - 40, p);
		puthz(284, 240 - 40, "预设温度", 16, 20, LIGHTBLUE);
		free(p);

	}

	for (i = 0;i < k;i++)
	{
		line(320 + 75 * cos(a - b * i), 210 - 40 - 75 * sin(a - b * i), 320 + 90 * cos(a - b * i), 210 - 40 - 90 * sin(a - b * i));
	}

	settextstyle(3, 0, 3);
	ellipse(300, 345, -180, 0, 15, 15);
	line(300, 330, 300, 350);
	puthz(275, 380, "开关", 24, 27, LIGHTBLUE);
	puthz(50, 410, "当前温度", 24, 27, LIGHTBLUE);

	p = (int*)malloc(11 * sizeof(int));
	itoa(num[5], p, 10);
	outtextxy(155, 405, ":");
	outtextxy(165, 405, p);
	free(p);

	puthz(205, 410, "摄氏度", 24, 27, LIGHTBLUE);
	puthz(350, 410, "当前湿度", 24, 27, LIGHTBLUE);

	p = (int*)malloc(11 * sizeof(int));
	itoa(num[6], p, 10);
	outtextxy(460, 405, ":");
	outtextxy(470, 405, p);
	outtextxy(520, 405, "%");
	free(p);

}

/****************************************
FUNCTION:AirconditionMouse
DESCRIBETION:空调页鼠标功能
INPUT:int* num
REUTRUN:int
****************************************/
int AirconditionMouse(int* num)
{
	int choice[10] = { 0 };

	while (1)
	{
		//绘制鼠标和设置按钮
		newmouse(&MouseX, &MouseY, &press);
		choice[1] = mouse_press(150, 150, 190, 190);
		choice[2] = mouse_press(450, 150, 490, 190);
		choice[3] = mouse_press(115, 315, 175, 375);
		choice[4] = mouse_press(442, 315, 502, 375);
		choice[5] = mouse_press(270, 315, 330, 375);
		choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
		choice[6] = mouse_press(560, 0, 640, 50);//返回上一层

		//判断选项
		if (choice[0] == 1)//直达主页面
		{
			ClearGraph();
			OpenMainPage();
			break;
		}
		else if (choice[6] == 1)//返回上一层
		{
			return 0;
		}
		else if (choice[1] == 1)  // 温度减按钮
		{
			num[1] = 1;
			if (num[0] == 1 && num[3] > 16) {
				num[3]--;
			}
			if (num[0] == 2 && num[4] > 20) {
				num[4]--;
			}
			delay(300);
			break;
		}
		else if (choice[2] == 1)  // 温度加按钮
		{
			num[2] = 1;
			if (num[0] == 1 && num[3] < 30) {
				num[3]++;
			}
			if (num[0] == 2 && num[4] < 80) {
				num[4]++;
			}
			delay(300);
			break;
		}

		else if (choice[3] == 1)
		{
			num[0] = 1;
			break;
		}
		else if (choice[4] == 1)
		{
			num[0] = 2;
			break;
		}
		else if (choice[5] == 1)
		{
			num[7] ^= 1;
			Aircondition(num);
			break;
		}
	}
	delay(100);
	return 1;
}


/****************************************
FUNCTION:Aircondition
DESCRIBETION:空调页温度湿度的改变
INPUT:int* num
REUTRUN:void
****************************************/
void Aircondition(int* num)
{
	char* p;
	int i;
	while (num[7])
	{
		setfillstyle(1, BLACK);
		Draw(LIGHTBLUE);
		if (num[3] > num[5])//升温
		{
			for (i = 0;i <= num[3] - num[5];i++)
			{
				bar(165, 405, 200, 430);
				num[5]++;

				p = (int*)malloc(11 * sizeof(int));
				itoa(num[5], p, 10);
				outtextxy(155, 405, ":");
				outtextxy(165, 405, p);
				free(p);
				for (i = 0; i < 650; i++)
				{
					setcolor(RED);
					moveto(i, 50 * sin(0.03 * i) + 280);
					lineto(i, 50 * sin(0.03 * i) + 280);
					moveto(i, 50 * sin(0.03 * i + PI / 3) + 200);
					lineto(i, 50 * sin(0.03 * i + PI / 3) + 200);
					line(i - 10, 50 * sin(0.03 * i - 0.3) + 280, i, 50 * sin(0.03 * i + PI / 3) + 200);
					delay(10);
				}
				delay(300);
			}
		}
		else if (num[3] < num[5])//降温
		{
			for (i = 0;i <= num[5] - num[3];i++)
			{
				bar(165, 405, 200, 430);
				num[5]--;
				p = (int*)malloc(11 * sizeof(int));
				itoa(num[5], p, 10);
				outtextxy(155, 405, ":");
				outtextxy(165, 405, p);
				free(p);
				for (i = 120; i < 400; i += 30)
				{
					setcolor(LIGHTBLUE);
					line(100 + 15 * sin(PI / 200 * i), i + 15 - 15 * cos(PI / 200 * i), 100 - 15 * sin(PI / 200 * i), i + 15 + 15 * cos(PI / 200 * i));
					line(100 + 15 * sin(PI / 200 * i + PI / 3), i + 15 - 15 * cos(PI / 200 * i + PI / 3), 100 - 15 * sin(PI / 200 * i + PI / 3), i + 15 + 15 * cos(PI / 200 * i + PI / 3));
					line(100 + 15 * sin(PI / 200 * i - PI / 3), i + 15 - 15 * cos(PI / 200 * i - PI / 3), 100 - 15 * sin(PI / 200 * i - PI / 3), i + 15 + 15 * cos(PI / 200 * i - PI / 3));
					line(540 + 15 * sin(PI / 200 * i), i + 15 - 15 * cos(PI / 200 * i), 540 - 15 * sin(PI / 200 * i), i + 15 + 15 * cos(PI / 200 * i));
					line(540 + 15 * sin(PI / 200 * i + PI / 3), i + 15 - 15 * cos(PI / 200 * i + PI / 3), 540 - 15 * sin(PI / 200 * i + PI / 3), i + 15 + 15 * cos(PI / 200 * i + PI / 3));
					line(540 + 15 * sin(PI / 200 * i - PI / 3), i + 15 - 15 * cos(PI / 200 * i - PI / 3), 540 - 15 * sin(PI / 200 * i - PI / 3), i + 15 + 15 * cos(PI / 200 * i - PI / 3));
					line(212 + 12 * sin(PI / 200 * i), i + 12 - 12 * cos(PI / 200 * i), 212 - 12 * sin(PI / 200 * i), i + 12 + 12 * cos(PI / 200 * i));
					line(212 + 12 * sin(PI / 200 * i + PI / 3), i + 12 - 12 * cos(PI / 200 * i + PI / 3), 212 - 12 * sin(PI / 200 * i + PI / 3), i + 12 + 12 * cos(PI / 200 * i + PI / 3));
					line(212 + 12 * sin(PI / 200 * i - PI / 3), i + 12 - 12 * cos(PI / 200 * i - PI / 3), 212 - 12 * sin(PI / 200 * i - PI / 3), i + 12 + 12 * cos(PI / 200 * i - PI / 3));
					line(428 + 12 * sin(PI / 200 * i), i + 12 - 12 * cos(PI / 200 * i), 428 - 12 * sin(PI / 200 * i), i + 12 + 12 * cos(PI / 200 * i));
					line(428 + 12 * sin(PI / 200 * i + PI / 3), i + 12 - 12 * cos(PI / 200 * i + PI / 3), 428 - 12 * sin(PI / 200 * i + PI / 3), i + 12 + 12 * cos(PI / 200 * i + PI / 3));
					line(428 + 12 * sin(PI / 200 * i - PI / 3), i + 12 - 12 * cos(PI / 200 * i - PI / 3), 428 - 12 * sin(PI / 200 * i - PI / 3), i + 12 + 12 * cos(PI / 200 * i - PI / 3));
					setfillstyle(1, BLACK);
					bar(85, i - 30, 115, i);
					bar(525, i - 30, 555, i);
					bar(200, i - 30, 224, i);
					bar(416, i - 30, 440, i);

					delay(200);
				}
				delay(300);
			}
		}
		if (num[4] > num[6])//加湿
		{
			for (i = 0;i <= num[4] - num[6];i++)
			{
				bar(470, 405, 520, 430);
				num[6]++;
				p = (int*)malloc(11 * sizeof(int));
				itoa(num[6], p, 10);
				outtextxy(460, 405, ":");
				outtextxy(470, 405, p);
				free(p);
				for (i = 84; i < 400; i += 30)
				{
					setcolor(LIGHTBLUE);
					setfillstyle(1, LIGHTBLUE);
					line(100, i, 112, i + 20);
					line(100, i, 88, i + 20);
					ellipse(100, i + 20, 180, 360, 10, 10);
					floodfill(100, 20 + i, LIGHTBLUE);
					line(540, i, 552, i + 20);
					line(540, i, 528, i + 20);
					ellipse(540, i + 20, 180, 360, 10, 10);
					floodfill(540, 20 + i, LIGHTBLUE);
					line(212, i + 45, 224, i + 20 + 45);
					line(212, i + 45, 200, i + 20 + 45);
					ellipse(212, i + 20 + 45, 180, 360, 10, 10);
					floodfill(212, 20 + i + 45, LIGHTBLUE);
					line(428, i + 45, 440, i + 20 + 45);
					line(428, i + 45, 416, i + 20 + 45);
					ellipse(428, i + 20 + 45, 180, 360, 10, 10);
					floodfill(428, 20 + i + 45, LIGHTBLUE);
					setfillstyle(1, BLACK);
					bar(88, i - 30, 112, i);
					bar(528, i - 30, 552, i);
					bar(200, i + 15, 224, i + 45);
					bar(416, i + 15, 440, i + 45);
					delay(200);
				}
				outtextxy(520, 395, "%");
				delay(300);
			}
		}
		else if (num[4] < num[6])//干燥
		{
			for (i = 0;i <= num[6] - num[4];i++)
			{
				bar(470, 405, 520, 430);
				num[6]--;
				p = (int*)malloc(11 * sizeof(int));
				itoa(num[6], p, 10);
				outtextxy(460, 405, ":");
				outtextxy(470, 405, p);
				free(p);
				for (i = 0; i < 650; i++)
				{
					setcolor(YELLOW);
					moveto(i, 50 * sin(0.03 * i) + 280);
					lineto(i, 50 * sin(0.03 * i) + 280);
					moveto(i, 50 * sin(0.03 * i + PI / 3) + 200);
					lineto(i, 50 * sin(0.03 * i + PI / 3) + 200);
					line(i - 10, 50 * sin(0.03 * i - 0.3) + 280, i, 50 * sin(0.03 * i + PI / 3) + 200);
					delay(10);
				}
				outtextxy(520, 395, "%");
				delay(300);
			}
		}
		if (num[3] == num[5] && num[4] == num[6])
		{
			num[7] = 0;
		}
	}
}