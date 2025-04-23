/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—9
*   说明：Wiper类函数实现雨刷功能
**************************************************?
**/

#include"init.h"
#include "page.h"
#include"wiper.h"
#define PI 3.1415926535

/****************************************
FUNCTION:OpenWiper
DESCRIBETION:打开雨刷页
INPUT:void
REUTRUN:void
****************************************/
void OpenWiper()
{
    while(1)
    {
        int i = 0, num[4] = {0}, wiper_ret = 1;
        FILE* wiper_text;
        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);

        wiper_text = fopen("..\\CODE\\text\\wiper.txt", "rt");
        for(i = 0; i < 4; i++)
        {
            fscanf(wiper_text, "%d ", &num[i]);
        
        }
        fclose(wiper_text);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawWiper();
        FillButton(num);
        PutWiperHz();
        DrawChangeWiper(num);

        wiper_ret = WiperMouse(num);

        wiper_text = fopen("..\\CODE\\text\\wiper.txt", "wt");
        for(i = 0; i < 4; i++)
        {
            fprintf(wiper_text, "%d ", num[i]);
        }
        fclose(wiper_text);

        if(!wiper_ret)
            return ;
    }
}


/****************************************
FUNCTION:DrawWiper
DESCRIBETION:绘制雨刷
INPUT:void
RETURN:void
****************************************/
void DrawWiper()
{
  
    puthz(360, 110, "开启", 24, 32, LIGHTBLUE);
    puthz(360, 170, "速度", 24, 32, LIGHTBLUE);
    circle(460, 182, 20);   //快
    circle(530, 182, 20);   //中
    circle(600, 182, 20);   //慢

    puthz(360, 290, "开启", 24, 32, LIGHTBLUE);
    puthz(360, 170 + 180, "速度", 24, 32, LIGHTBLUE);
    circle(460, 182 + 180, 20);   //快
    circle(530, 182 + 180, 20);   //中
    circle(600, 182 + 180, 20);   //慢
 
    //前车窗
	setlinestyle(0, 0, 1);
    setcolor(LIGHTGRAY);
    line(550, 113, 580, 113);
    line(550, 131, 580, 131);
    ellipse(550, 122, 90, 270, 7, 7);
    ellipse(580, 122, -90, 90, 7, 7);

    line(550, 113 + 180, 580, 113 + 180);
    line(550, 131 + 180, 580, 131 + 180);
    ellipse(550, 122 + 180, 90, 270, 7, 7);
    ellipse(580, 122 + 180, -90, 90, 7, 7);
    setlinestyle(0, 0, 3);
    line(100, 90, 240, 90);
    line(30, 230, 310, 230);
    line(100, 92, 240, 92);
    line(30, 228, 310, 228);
    line(100, 90, 30, 230);
	line(240, 90, 310, 230);
    line(102, 90, 32, 230);
    line(238, 90, 308, 230);
    //后车窗
    line(100, 270, 240, 270);
    line(40, 410, 300, 410);
    line(100,270, 40, 410);
    line(240, 270, 300, 410);
    line(100, 272, 240, 272);
    line(40, 408, 300, 408);
    line(102, 270, 42, 410);
    line(238, 270, 298, 410);
    setcolor(LIGHTBLUE);
    setfillstyle(1, LIGHTBLUE);
    floodfill(150, 120, LIGHTGRAY);
    floodfill(150, 300, LIGHTGRAY);



  /*  line(105, 190, 175, 120);
    line(170, 190, 240, 120);*/
}

void DrawWiper1(int t)
{
    int i;
    for (i = 1; i < 64; i++)
    {
        setcolor(LIGHTBLUE);
        line(33, 227, 33 + 150 * cos(64 * PI / 180 - i * PI / 180), 227 - 150 * sin(64 * PI / 180 - i * PI / 180));
        line(307, 227, 307 - 150 * cos(64 * PI / 180 - i * PI / 180), 227 - 150 * sin(64 * PI / 180 - i * PI / 180));
        setcolor(WHITE);
        line(33, 227, 33 + 150 * cos(63 * PI / 180 - i * PI / 180), 227 - 150 * sin(63 * PI / 180 - i * PI / 180));
        line(307, 227, 307 - 150 * cos(63 * PI / 180 - i * PI / 180), 227 - 150 * sin(63 * PI / 180 - i * PI / 180));
        delay(t);
    }
    for (i = 1; i < 64; i++)
    {
        setcolor(LIGHTBLUE);
        line(33, 227, 33 + 150 * cos(i * PI / 180 - PI / 180), 227 - 150 * sin(i * PI / 180 - PI / 180));
        line(307, 227, 307 - 150 * cos(i * PI / 180 - PI / 180), 227 - 150 * sin(i * PI / 180 - PI / 180));
        setcolor(WHITE);
        line(33, 227, 33 + 150 * cos(i * PI / 180), 227 - 150 * sin(i * PI / 180));
        line(307, 227, 307 - 150 * cos(i * PI / 180), 227 - 150 * sin(i * PI / 180));
        delay(t);
    }
    for (i = 1; i < 64; i++)
    {
        setcolor(LIGHTBLUE);
        line(33, 227, 33 + 150 * cos(64 * PI / 180 - i * PI / 180), 227 - 150 * sin(64 * PI / 180 - i * PI / 180));
        line(307, 227, 307 - 150 * cos(64 * PI / 180 - i * PI / 180), 227 - 150 * sin(64 * PI / 180 - i * PI / 180));
        setcolor(WHITE);
        line(33, 227, 33 + 150 * cos(63 * PI / 180 - i * PI / 180), 227 - 150 * sin(63 * PI / 180 - i * PI / 180));
        line(307, 227, 307 - 150 * cos(63 * PI / 180 - i * PI / 180), 227 - 150 * sin(63 * PI / 180 - i * PI / 180));
        delay(t);
    }
    for (i = 1; i < 64; i++)
    {
        setcolor(LIGHTBLUE);
        line(33, 227, 33 + 150 * cos(i * PI / 180 - PI / 180), 227 - 150 * sin(i * PI / 180 - PI / 180));
        line(307, 227, 307 - 150 * cos(i * PI / 180 - PI / 180), 227 - 150 * sin(i * PI / 180 - PI / 180));
        setcolor(WHITE);
        line(33, 227, 33 + 150 * cos(i * PI / 180), 227 - 150 * sin(i * PI / 180));
        line(307, 227, 307 - 150 * cos(i * PI / 180), 227 - 150 * sin(i * PI / 180));
        delay(t);
    }


}
void DrawWiper2(int t)
{
	int i;
    for (i = 1; i < 180; i++)
    {
        setcolor(LIGHTBLUE);
        line(170, 407, 170 + 115 * cos(i * PI / 180-PI/180), 407 - 115 * sin(i * PI / 180-PI/180));
        setcolor(WHITE);
        line(170, 407, 170+ 115 * cos(i * PI / 180), 407 - 115 * sin(i * PI / 180));
        delay(t);
    }
    for (i = 1; i < 180; i++)
    {
        setcolor(LIGHTBLUE);
        line(170, 407, 170 - 115 * cos(i * PI / 180 - PI / 180), 407 - 115 * sin(i * PI / 180 - PI / 180));
        setcolor(WHITE);
        line(170, 407, 170 - 115 * cos(i * PI / 180), 407 - 115 * sin(i * PI / 180));
        delay(t);
    }
}
/****************************************
FUNCTION:DrawChangeWiper
DESCRIBETION:绘制变化的雨刷
INPUT:int*num
RETURN:void
****************************************/
void DrawChangeWiper(int* num)
{
    setfillstyle(1, GREEN);
    if (num[0] == 1)//前开
    {
        if (num[1] == 1)
        {
            DrawWiper1(10);
            delay(300);
        }
        if (num[1] == 2)
        {
            DrawWiper1(20);
            delay(300);
        }
        if (num[1] == 3)
        {
            DrawWiper1(30);
            delay(300);
        }
    }
    if (num[2] == 1)//后开
    {
        if (num[3] == 1)
        {
            DrawWiper2(10);
            delay(300);
        }
        if (num[3] == 2)
        {
            DrawWiper2(20);
            delay(300);
        }
        if (num[3] == 3)
        {
            DrawWiper2(30);
            delay(300);
        }

    }

}

/****************************************
FUNCTION:FillButton
DESCRIBETION:画变化的按钮
INPUT:int* num
RETURN:void
****************************************/
void FillButton(int* num)
{
    setfillstyle(1, GREEN);
    if(num[0] == 1 )//前开
    {
        int i;
        setcolor(LIGHTGRAY);
        setfillstyle(1, LIGHTGRAY);
        fillellipse(580, 122, 6, 6);
        setfillstyle(1, LIGHTBLUE);
        setfillstyle(1, GREEN);
		if (num[1] == 1)
		{
            floodfill(460, 182, LIGHTBLUE);
		}
        if (num[1] == 2)
        {
            floodfill(530, 182, LIGHTBLUE);
        }
        if (num[1] == 3)
        {
            floodfill(600, 182, LIGHTBLUE);
        }
    }
    if(num[0] == 0)//前关
    {
        setcolor(LIGHTGRAY);
        setfillstyle(1, LIGHTGRAY);
        fillellipse(550, 122, 6, 6);
        setfillstyle(1, LIGHTBLUE);
        //floodfill(580, 122, LIGHTGRAY);

    }
    if(num[2] == 1)//后开
    {
        int i;
        setcolor(LIGHTGRAY);
        setfillstyle(1, LIGHTGRAY);
        fillellipse(580, 122+180, 6, 6);
        setfillstyle(1, LIGHTBLUE);
        setfillstyle(1, GREEN);
        if (num[3] == 1)
        {
            floodfill(460, 182+180, LIGHTBLUE);
        }
        if (num[3] == 2)
        {
            floodfill(530,182+180, LIGHTBLUE);
        }
        if (num[3] == 3)
        {
            floodfill(600, 182+180, LIGHTBLUE);
        }

    }
    if(num[2] == 0)//后关
    {
        setcolor(LIGHTGRAY);
        setfillstyle(1, LIGHTGRAY);
        fillellipse(550, 122+180, 6, 6);
        setfillstyle(1, LIGHTBLUE);
    }
}

/****************************************
FUNCTION:PutWiperHz
DESCRIBETION:显示雨刷页汉字
INPUT:void
RETURN:void
****************************************/
void PutWiperHz()
{
    setcolor(LIGHTBLUE);
    puthz(460 - 8, 182 - 8, "快", 16, 32, LIGHTBLUE);
    puthz(530 - 8, 174, "中", 16, 32, LIGHTBLUE);
    puthz(600 - 8, 174, "慢", 16, 32, LIGHTBLUE);
    puthz(460 - 8, 182 - 8 + 180, "快", 16, 32, LIGHTBLUE);
    puthz(530 - 8, 174 + 180, "中", 16, 32, LIGHTBLUE);
    puthz(600 - 8, 174 + 180, "慢", 16, 32, LIGHTBLUE);
}

/****************************************
FUNCTION:WiperMouse
DESCRIBETION:雨刷页的鼠标功能
INPUT:int*
RETURN:int
****************************************/
int WiperMouse(int* num)
{
    int choice[10] = {0};
    while(1)
    {
        
        newmouse(&MouseX,&MouseY,&press);
        choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
        choice[9] = mouse_press(560, 0, 640, 50);//返回上一层
        choice[1] = mouse_press(543, 113, 587, 131);  //fore on or off
        choice[2]=mouse_press(543, 113+180, 587, 131+180);  //
        choice[3] = mouse_press(440, 162, 480, 202);  //快
        choice[4] = mouse_press(510, 162, 550, 202);  //中
        choice[5]=mouse_press(580, 162, 620, 202);  //慢
        choice[6] = mouse_press(440, 162+180, 480, 202+180);  //快
        choice[7] = mouse_press(510, 162+180, 550, 202+180);  //中
        choice[8] = mouse_press(580, 162+180, 620, 202+180);  //慢
  
        if (choice[0] == 1)//直达主页面
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[9] == 1)//返回上一层
        {
            return 0;
        }
        else if(choice[1]==1)
        {
            num[0] ^= 1;
			num[1] = 0;
            delay(300);
            break;
        }
		else if(choice[2]==1)
        {
            num[2] ^= 1;
            num[3] = 0;
            delay(300);
            break;
        }
        else if(choice[3]==1)
        {
            num[1] = 1;
            break;
        }
        else if(choice[4]==1)
        {
            num[1] = 2;
            break;
        }
        else if(choice[5]==1)
        {
            num[1] = 3;
            break;
        }
        else if(choice[6]==1)
        {
            num[3] = 1;
            break;
        }
        else if(choice[7]==1)
        {
            num[3] = 2;
            break;
        }
        else if(choice[8]==1)
        {
            num[3] = 3;
            break;
        }
    }
    return 1;
}