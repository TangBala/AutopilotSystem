/**
**************************************************?
*	版本号：1.0
*	作者：Y
*	生成日期：2024—4—20
*	说明：Display类函数实现显示功能
* xuezhang
**************************************************?
**/

#include"init.h"
#include<time.h>
#include<math.h>
#include"display.h"
#include<stdlib.h>
#include<time.h>
#include"normal.h"

/*********************
FUNCTION:OpenDisplay
DESCRIBETION:打开显示界面
INPUT:void
RETURN:void
*********************/
void OpenDisplay()
{
	while (1)
	{
		int display_ret = -1, num[10] = { 0 }, i;
		FILE* display_text, * battery_text;

		setfillstyle(1, WHITE);
		bar(0, 0, 640, 480);

		display_text = fopen("..\\CODE\\text\\display.txt", "rt");
		for (i = 0; i < 10; i++)
		{
			fscanf(display_text, "%d ", &num[i]);
		}
		fclose(display_text);

		DrawDisplaySButton(num);
		DrawDisplayChangePart(num);
		display_ret = DisplayMouse(num);

		display_text = fopen("..\\CODE\\text\\display.txt", "wt");
		for (i = 0; i < 10; i++)
		{
			fprintf(display_text, "%d ", num[i]);
		}
		fclose(display_text);


		battery_text = fopen("..\\CODE\\text\\battery.txt", "wt");
		fprintf(battery_text, "%d %d %d %d ", num[2], 1, 0, 0);
		fclose(battery_text);
		if (!display_ret)

			return;
	}
}

/****************************************
FUNCTION:DrawDisplaySButton
DESCRIBETION:绘制显示中所有按钮
INPUT:void
RETURN:void
****************************************/

void DrawDisplaySButton(int* num)
{
	int i, j, t;

	num[1] = 0;

	Draw(BLUE);

	DrawDailnumber(num);//表盘

	DrawCar(160, 240, 0.2);
	line(0, 40, 640, 40);
	line(0, 400, 640, 400);

	line(220, 400, 420, 400);//分界
	circle(165, 430, 20);
	line(165, 440, 165, 420);
	line(165, 420, 155, 430);
	line(165, 420, 175, 430);
	puthz(140, 450, "启动", 24, 27, BLUE);//启动

	rectangle(1, 1, 30, 30);
	line(1, 1, 30, 30);
	line(30, 1, 1, 30);

	line(638, 105, 415, 310);
	rectangle(435, 65, 565, 105);
	rectangle(435, 146, 525, 190);
	puthz(450, 75, "手动控制", 24, 27, BLUE);
	puthz(456, 155, "充电", 24, 27, BLUE);//列表按钮

	puthz(525, 215, "天气：晴", 24, 27, BLUE);
	puthz(450, 283, "驾驶模式：", 24, 27, BLUE);
	puthz(425, 345, "温度：", 24, 27, BLUE);
	puthz(525, 345, "湿度：", 24, 27, BLUE);

	line(90, 40, 90, 400);
	line(110, 40, 110, 400);
	line(220, 40, 220, 400);
	line(240, 40, 240, 400);

	line(415, 40, 415, 400);
}


/****************************************
FUNCTION:DrawDailnumber
DESCRIBETION:绘制表盘等上的数据（如温度，湿度等）
INPUT:void
RETURN:void
****************************************/
void DrawDailnumber(int* num)
{
	int i, j, n, a, b, temperature, humidity, battery, front, rear, m[5] = { 1 };
	char* p;
	FILE* ac_text, * battery_text;

	front = rear = 0;

	ac_text = fopen("..\\CODE\\text\\ac.txt", "rt");
	fscanf(ac_text, "%d %d %d %d %d %d %d ", &i, &j, &n, &a, &b, &temperature, &humidity);
	fclose(ac_text);

	battery_text = fopen("..\\CODE\\text\\battery.txt", "rt");
	fscanf(battery_text, "%d %d %d %d ", &battery, &m[0], &m[1], &m[2]);
	fclose(battery_text);
	num[2] = battery;
	DisplayChange(num, num[2]);

	Draw(BLUE);

	p = (int*)malloc(sizeof(int));
	itoa(humidity, p, 10);
	settextstyle(3, 0, 1);
	outtextxy(595, 345, p);
	outtextxy(625, 345, "%");//湿度
	free(p);

	p = (int*)malloc(sizeof(int));
	itoa(temperature, p, 10);
	outtextxy(495, 345, p);//温度
	free(p);


}


/****************************************
FUNCTION:DrawCar
DESCRIBETION:绘制车
INPUT:int
RETURN:void
****************************************/
void DrawCar(int x, int y, float k)//x,y确定位置，k可确定大小
{
	int i;

	line((325 - 230) * k + x, (275 - 300) * k + y, (350 - 230) * k + x, (196 - 300) * k + y);
	line((350 - 230) * k + x, (181 - 300) * k + y, (350 - 230) * k + x, (196 - 300) * k + y);
	line((350 - 230) * k + x, (181 - 300) * k + y, (321 - 230) * k + x, (164 - 300) * k + y);
	line((321 - 230) * k + x, (164 - 300) * k + y, (144 - 230) * k + x, (165 - 300) * k + y);
	line((144 - 230) * k + x, (165 - 300) * k + y, (116 - 230) * k + x, (180 - 300) * k + y);
	line((116 - 230) * k + x, (180 - 300) * k + y, (115 - 230) * k + x, (201 - 300) * k + y);
	line((135 - 230) * k + x, (275 - 300) * k + y, (115 - 230) * k + x, (201 - 300) * k + y);
	line((229 - 230) * k + x, (266 - 300) * k + y, (135 - 230) * k + x, (275 - 300) * k + y);
	line((229 - 230) * k + x, (266 - 300) * k + y, (325 - 230) * k + x, (275 - 300) * k + y);//前窗

	line((147 - 230) * k + x, (424 - 300) * k + y, (230 - 230) * k + x, (428 - 300) * k + y);
	line((230 - 230) * k + x, (428 - 300) * k + y, (316 - 230) * k + x, (422 - 300) * k + y);
	line((316 - 230) * k + x, (422 - 300) * k + y, (326 - 230) * k + x, (496 - 300) * k + y);
	line((326 - 230) * k + x, (496 - 300) * k + y, (296 - 230) * k + x, (511 - 300) * k + y);
	line((296 - 230) * k + x, (511 - 300) * k + y, (230 - 230) * k + x, (522 - 300) * k + y);
	line((230 - 230) * k + x, (522 - 300) * k + y, (171 - 230) * k + x, (512 - 300) * k + y);
	line((171 - 230) * k + x, (512 - 300) * k + y, (138 - 230) * k + x, (497 - 300) * k + y);
	line((138 - 230) * k + x, (497 - 300) * k + y, (147 - 230) * k + x, (424 - 300) * k + y);//后窗
	line(x, (428 - 300) * k + y, x, (522 - 300) * k + y);

	for (i = -1; i < 2; i += 2)
	{
		line((150 - 230) * i * k + x, (55 - 300) * k + y, (114 - 230) * i * k + x, (143 - 300) * k + y);
		line((114 - 230) * i * k + x, (143 - 300) * k + y, (107 - 230) * i * k + x, (180 - 300) * k + y);
		line((107 - 230) * i * k + x, (180 - 300) * k + y, (105 - 230) * i * k + x, (207 - 300) * k + y);
		line((105 - 230) * i * k + x, (207 - 300) * k + y, (131 - 230) * i * k + x, (296 - 300) * k + y);
		line((131 - 230) * i * k + x, (296 - 300) * k + y, (132 - 230) * i * k + x, (398 - 300) * k + y);
		line((132 - 230) * i * k + x, (398 - 300) * k + y, (116 - 230) * i * k + x, (444 - 300) * k + y);
		line((116 - 230) * i * k + x, (444 - 300) * k + y, (105 - 230) * i * k + x, (360 - 300) * k + y);
		line((105 - 230) * i * k + x, (360 - 300) * k + y, (104 - 230) * i * k + x, (227 - 300) * k + y);
		line((104 - 230) * i * k + x, (227 - 300) * k + y, (105 - 230) * i * k + x, (214 - 300) * k + y);
		line((105 - 230) * i * k + x, (214 - 300) * k + y, (101 - 230) * i * k + x, (211 - 300) * k + y);
		line((101 - 230) * i * k + x, (211 - 300) * k + y, (105 - 230) * i * k + x, (156 - 300) * k + y);
		line((105 - 230) * i * k + x, (156 - 300) * k + y, (134 - 230) * i * k + x, (84 - 300) * k + y);
		line((134 - 230) * i * k + x, (84 - 300) * k + y, (150 - 230) * i * k + x, (55 - 300) * k + y);
		line((115 - 230) * i * k + x, (82 - 300) * k + y, (105 - 230) * i * k + x, (156 - 300) * k + y);
		line((115 - 230) * i * k + x, (82 - 300) * k + y, (129 - 230) * i * k + x, (39 - 300) * k + y);
		line((129 - 230) * i * k + x, (39 - 300) * k + y, (174 - 230) * i * k + x, (16 - 300) * k + y);
		line((174 - 230) * i * k + x, (16 - 300) * k + y, (230 - 230) * i * k + x, (11 - 300) * k + y);
		line((174 - 230) * i * k + x, (16 - 300) * k + y, (142 - 230) * i * k + x, (23 - 300) * k + y);
		line((142 - 230) * i * k + x, (23 - 300) * k + y, (115 - 230) * i * k + x, (39 - 300) * k + y);
		line((115 - 230) * i * k + x, (39 - 300) * k + y, (111 - 230) * i * k + x, (49 - 300) * k + y);
		line((111 - 230) * i * k + x, (49 - 300) * k + y, (129 - 230) * i * k + x, (38 - 300) * k + y);
		line((112 - 230) * i * k + x, (42 - 300) * k + y, (89 - 230) * i * k + x, (84 - 300) * k + y);
		line((89 - 230) * i * k + x, (84 - 300) * k + y, (104 - 230) * i * k + x, (40 - 300) * k + y);
		line((104 - 230) * i * k + x, (40 - 300) * k + y, (104 - 230) * i * k + x, (40 - 300) * k + y);
		line((104 - 230) * i * k + x, (40 - 300) * k + y, (230 - 230) * i * k + x, (4 - 300) * k + y);
		line((89 - 230) * i * k + x, (84 - 300) * k + y, (89 - 230) * i * k + x, (221 - 300) * k + y);
		line((89 - 230) * i * k + x, (221 - 300) * k + y, (102 - 230) * i * k + x, (211 - 300) * k + y);
		line((94 - 230) * i * k + x, (217 - 300) * k + y, (103 - 230) * i * k + x, (222 - 300) * k + y);
		line((91 - 230) * i * k + x, (221 - 300) * k + y, (103 - 230) * i * k + x, (227 - 300) * k + y);
		line((89 - 230) * i * k + x, (221 - 300) * k + y, (72 - 230) * i * k + x, (232 - 300) * k + y);
		line((72 - 230) * i * k + x, (232 - 300) * k + y, (69 - 230) * i * k + x, (240 - 300) * k + y);
		line((69 - 230) * i * k + x, (240 - 300) * k + y, (78 - 230) * i * k + x, (242 - 300) * k + y);
		line((78 - 230) * i * k + x, (242 - 300) * k + y, (104 - 230) * i * k + x, (231 - 300) * k + y);
		line((89 - 230) * i * k + x, (236 - 300) * k + y, (91 - 230) * i * k + x, (495 - 300) * k + y);
		ellipse((109 - 230) * i * k + x, (495 - 300) * k + y, -90 - 45 * (i + 1), 0 - 45 * (i + 1), 18 * k, 62 * k);
		line((109 - 230) * i * k + x, (557 - 300) * k + y, (230 - 230) * i * k + x, (576 - 300) * k + y);
		ellipse((230 - 230) * i * k + x, (557 - 300) * k + y, -90 - 45 * (i + 1), 0 - 45 * (i + 1), 121 * k, 19 * k);
		line((133 - 230) * i * k + x, (497 - 300) * k + y, (130 - 230) * i * k + x, (559 - 300) * k + y);
		line((104 - 230) * i * k + x, (349 - 300) * k + y, (132 - 230) * i * k + x, (349 - 300) * k + y);
		line((90 - 230) * i * k + x, (352 - 300) * k + y, (104 - 230) * i * k + x, (349 - 300) * k + y);
		line((89 - 230) * i * k + x, (194 - 300) * k + y, (101 - 230) * i * k + x, (197 - 300) * k + y);//左右主体
	}
}

/****************************************
FUNCTION:DrawArrow
DESCRIBETION:绘制箭头
INPUT:void
RETURN:void
****************************************/
void DrawArrow()
{
	setcolor(BLUE);
	setlinestyle(0, 0, 1);
	rectangle(25, 35, 175, 85);
	rectangle(75, 35, 125, 85);

	moveto(30, 60);
	lineto(50, 40);
	lineto(50, 55);
	lineto(70, 55);
	lineto(70, 65);
	lineto(50, 65);
	lineto(50, 80);
	lineto(30, 60);

	moveto(100, 40);
	lineto(120, 60);
	lineto(105, 60);
	lineto(105, 80);
	lineto(95, 80);
	lineto(95, 60);
	lineto(80, 60);
	lineto(100, 40);

	moveto(170, 60);
	lineto(150, 40);
	lineto(150, 55);
	lineto(130, 55);
	lineto(130, 65);
	lineto(150, 65);
	lineto(150, 80);
	lineto(170, 60);
}

/****************************************
FUNCTION:DrawTime
DESCRIBETION:显示时间
INPUT:int
now[0]=info->tm_sec;
RETURN:void
****************************************/
void DrawTime(int x, int y, int k)//x,y确定位置，k可确定大小
{
	time_t curtime;

	setfillstyle(1, WHITE);
	time(&curtime);
	bar(x, y, x + 270 * k, y + 20 * k);
	settextstyle(3, 0, k);
	setcolor(BLUE);
	outtextxy(x, y, ctime(&curtime));
	bar(x + 160 * k, y, x + 270 * k, y + 20);
	delay(100);

}

/****************************************
FUNCTION:DrawDisplayChangePart
DESCRIBETION:显示页可变部分
INPUT:int* num
RETURN:int
****************************************/
void DrawDisplayChangePart(int* num)
{
	if (num[0] == 1)
	{
		if (num[2] > 20 && num[2] <= 100)
		{
			Run(num);
			num[0] = 0;
		}
		else if (num[2] <= 20)
		{
			puthz(410, 40, "电量不足", 16, 27, BLUE);
			num[0] = 0;
		}
		else
		{
			puthz(410, 40, "电量异常", 16, 27, BLUE);
			Run(num);
			num[0] = 0;
		}
	}
}

/****************************************
FUNCTION:DisplayMouse
DESCRIBETION:显示页鼠标
INPUT:int* num
RETURN:int
****************************************/
int DisplayMouse(int* num)
{
	int choice[10] = { 0 };

	time_t current_time;
	DrawTime(32, 2, 1);
	while (1)
	{
		//绘制鼠标和设置按钮
		newmouse(&MouseX, &MouseY, &press);

		choice[1] = mouse_press(140, 415, 185, 450);
		choice[0] = mouse_press(0, 0, 29, 29);

		current_time = time(NULL);

		if (current_time % 60 == 0)
		{
			DrawTime(32, 2, 1);//显示时间
		}

		//判断选项
		if (choice[0] == 1)
		{
			num[0] = 0;
			ClearGraph();
			return 0;
		}
		else if (choice[1] == 1)
		{
			num[0] ^= 1;
			break;
		}
		while (mouse_press(435, 146, 525, 190) == 1) {
			OpenBattery();
		}

	}
	delay(100);
	return 1;
}

/****************************************
FUNCTION:Run
DESCRIBETION:运行,车辆行进
INPUT:int *num
RETURN:void
****************************************/
void Run(int* num)
{
	int i, j, k, n[5] = { 1 }, battery;
	FILE* battery_text, * display_text;
	NormalRun(num);

	line(220, 400, 420, 400);//分界
	circle(165, 430, 20);
	line(165, 440, 165, 420);
	line(165, 420, 155, 430);
	line(165, 420, 175, 430);
	puthz(140, 450, "启动", 24, 27, BLUE);//启动
	num[3] = num[4] = num[5] = 0;
	num[0] = num[1] = 0;
}

/****************************************
FUNCTION:DrawBackground
DESCRIBETION:绘制背景，设置障碍物
INPUT:int *num
RETURN:void
****************************************/
void DrawBackground(int* num)
{
	int i = 0, j, k, n[5] = { 1 }, m, s = 5;
	FILE* battery_text;

	i = num[3];
	j = num[4];
	k = num[5];
	Draw(BLUE);
	setfillstyle(1, WHITE);
	line(90, 40, 90, 400);
	line(110, 40, 110, 400);
	line(220, 40, 220, 400);
	line(240, 40, 240, 400);

	srand((unsigned)time(NULL));
	m = rand() % 20;
	while (1)
	{
		DisplayChange(num, num[2]);

		while (1)
		{
			Draw(BLUE);
			setfillstyle(1, WHITE);

			delay(30);
			bar(140, 48, 180, 398);
			bar(20, 41, 70, 405);
			bar(250, 41, 290, 405);

			DrawCar(160, 240, 0.2);
			for (k = 0; k < 200; k++)
			{
				int buildingHeightLEFT = 50 + rand() % 80;
				int buildingWidthLEFT = 50;
				int buildingXLEFT = 20;                      // 左侧固定位置
				int buildingYLEFT = -200 + s * j - 150 * k; // 垂直位置随j变化

				int buildingHeightRIGHT_1 = 50 + rand() % 80;
				int buildingWidthRIGHT_1 = 40;
				int buildingXRIGHT_1 = 250;                    // 右侧固定位置
				int buildingYRIGHT_1 = -200 + s * j - 180 * k; // 垂直位置随j变化


				bar(250, -200 + s * j - 180 * k, buildingXRIGHT_1 + buildingWidthRIGHT_1, buildingYRIGHT_1 + buildingHeightRIGHT_1);
				bar(20, -200 + s * j - 150 * k, buildingXLEFT + buildingWidthLEFT, buildingYLEFT + buildingHeightLEFT);// 绘制外框和结构线
				setfillstyle(1, LIGHTGRAY);
				rectangle(buildingXLEFT, buildingYLEFT, buildingXLEFT + buildingWidthLEFT, buildingYLEFT + buildingHeightLEFT);


				setfillstyle(1, LIGHTGRAY);
				rectangle(buildingXRIGHT_1, buildingYRIGHT_1,
					buildingXRIGHT_1 + buildingWidthRIGHT_1,
					buildingYRIGHT_1 + buildingHeightRIGHT_1);


				setfillstyle(1, WHITE);
				rectangle(150, -100 + s * j - 110 * k, 170, 0 + s * j - 110 * k);
			}
			srand((unsigned)time(NULL));
			if (m < 30)
			{
				n[i] = rand() % 12000;//不可避开障碍物
				setfillstyle(1, RED);
				fillellipse(160, -fabs(n[i]) + s * j, 20, 20);
			}
			setfillstyle(1, WHITE);

			bar(31, 0, 80, 40);
			bar(0, 31, 31, 39);
			bar(0, 405, 80, 480);

			bar(240, 0, 350, 40);
			bar(245, 405, 350, 480);

			bar(80, 0, 250, 39);
			bar(80, 401, 250, 479);
			bar(125, 182, 200, 292);
			DrawCar(160, 240, 0.2);
			if (j % 200 == 0)
			{
				num[2]--;
			}

			num[1] = s * 6;
			DisplayChange(num, num[2]);
			if (m < 30)
			{
				if (-fabs(n[i]) + s * j + 20 > 42 && -fabs(n[i]) + s * j - 20 < 160)
				{
					s = 0;
					num[1] = s * 6;
					goto end;
				}
				else if (-fabs(n[i]) + s * j + 20 > 160 && -fabs(n[i]) + s * j - 20 < 295)
				{
					bar(300, -fabs(n[i]) + s * j - 20, 340, -fabs(n[i]) + s * j + 20);
				}
				else;
			}
			j++;
			if (j % 5 == 0)
			{
				break;
			}
		}
		DisplayChange(num, num[2]);

	end:
		if (!s)
		{
			DisplayChange(num, num[2]);
			rectangle(140, 410, 200, 450);
			puthz(140, 420, "清除", 16, 27, BLUE);
			puthz(500, 10, "发现障碍物", 16, 27, RED);
			do
			{
				newmouse(&MouseX, &MouseY, &press);

			} while (!(mouse_press(140, 410, 200, 450) == 1));

			setfillstyle(1, WHITE);
			bar(500, 10, 640, 30);
			bar(300, -fabs(n[i]) + s * j - 20, 340, -fabs(n[i]) + s * j + 20);
			s = 5;
		}
		else
		{
			num[3] = i; num[4] = j; num[5] = k;
			break;
		}
	}
}

/***************************
FUNCTION:DisplayChange
DESCRIBETION:改变速度和电量
INPUT:int *num,int battery
RETURN:void
***************************/
void DisplayChange(int* num, int battery)
{
	FILE* battery_text;
	const int BATTERY_BAR_X = 440;
	const int BATTERY_BAR_Y = 10;
	const int BATTERY_BAR_WIDTH = 100; // 总宽度100像素对应100%
	const int BATTERY_BAR_HEIGHT = 20;
	int speed, a, n[5] = { 1 };

	char* p;

	speed = num[1];

	if (battery > 100 || battery < 0)
	{
		battery = 0;
	}

	Draw(BLUE);



	// 限制电量值范围
	battery = (battery < 0) ? 0 : (battery > 100) ? 100 : battery;

	// 绘制背景（全量范围）
	setfillstyle(1, LIGHTGRAY);
	bar(BATTERY_BAR_X, BATTERY_BAR_Y,
		BATTERY_BAR_X + BATTERY_BAR_WIDTH,
		BATTERY_BAR_Y + BATTERY_BAR_HEIGHT);

	// 绘制当前电量（动态部分）
	setfillstyle(1, (battery <= 20) ? RED : GREEN); // 低电量变红
	bar(BATTERY_BAR_X, BATTERY_BAR_Y,
		BATTERY_BAR_X + battery, // 直接使用电量值作为宽度
		BATTERY_BAR_Y + BATTERY_BAR_HEIGHT);

	// 绘制边框
	setcolor(BLUE);
	rectangle(BATTERY_BAR_X, BATTERY_BAR_Y,
		BATTERY_BAR_X + BATTERY_BAR_WIDTH,
		BATTERY_BAR_Y + BATTERY_BAR_HEIGHT);

	Draw(BLUE);
	p = (int*)malloc(sizeof(int));
	itoa(num[2], p, 10);
	settextstyle(3, 0, 1);
	setfillstyle(1, WHITE);
	bar(365, 10, 420, 30);
	outtextxy(380, 10, p);
	outtextxy(415, 10, "%");//电量
	free(p);


}
