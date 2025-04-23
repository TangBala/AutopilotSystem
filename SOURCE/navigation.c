/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—28
*   说明：Navigation类函数实现导航功能
**************************************************?
**/

#include"init.h"
#include"map.h"
#include"navigat.h"
#include "page.h"
#include "display.h"

/****************************************
FUNCTION:OpenNavigation
DESCRIBETION:打开导航页
INPUT:void
RETURN:void
****************************************/
void OpenNavigation()
{
    int mode[2] = { 1, 1 };
    while (1)
    {
        int navigation_ret = 1;
        ClearGraph();
        DrawTopMid(-15);
        DrawHomeRet();
        DrawToHome();
        DrawMap();
        DrawNavigationTopButton(mode);
        navigation_ret = NavigationMouse(mode);
        if (!navigation_ret)
            return;
    }
}


/****************************************
FUNCTION:DrawNavigationTopButton
DESCRIBETION:绘制导航页顶部按钮
INPUT:void
RETURN:void
****************************************/
void DrawNavigationTopButton(int* mode)
{
	int s, e;
    if (mode[0] == 1)s = 13;
    if (mode[1] == 1)e = 13;
    puthz(210+20, 70, "终点", 24, 25, LIGHTBLUE);
    puthz(40+20, 70, "起点", 24, 25, LIGHTBLUE);
    setfillstyle(1, RED);
    setcolor(RED);
    fillellipse(210, 92 - 10, 8, 8);
    setfillstyle(1, GREEN);
    setcolor(GREEN);
    fillellipse(40, 92 - 10, 8, 8);
	bar(350 + 20, 82 - 14, 440, 82 + 14);
    puthz(360 + 20, 70, "重选", 24, 25, WHITE);
    bar(460, 82 - 14, 530, 82 + 14);
    puthz(470, 70, "规划", 24, 25, WHITE);

   /* if (mode[0] == 0 && mode[1] == 0)
    {
        rectangle(550 , 82 - 14, 590, 82 + 14);
        puthz(560, 70, "导航", 24, 25, WHITE);
    }*/

}

/****************************************
FUNCTION:NavigationMouse
DESCRIBETION:导航页鼠标
INPUT:int* mode
RETURN:int
****************************************/
int NavigationMouse(int* mode)
{
    int choice[7] = { 0 }, start = -1, end = -1, distance = 0;
    char dist[10];
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
        choice[6] = mouse_press(560, 0, 640, 50);//返回上一层
        choice[1] = mouse_press(32, 70,160,94);
        choice[2] = mouse_press(202, 70, 330, 94);
        choice[3] = mouse_press(370, 70, 440, 94);
        choice[4] = mouse_press(460, 70, 530, 94);
        choice[5] = mouse_press(550, 70, 620, 94);

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
        if (choice[1] == 1)
        {
            if (mode[0])
            {
                start = ChoosePlace();
                mode[0] = 0;
            }
        }
        if (choice[2] == 1)
        {
            if (mode[1])
            {
                end = ChoosePlace();
                mode[1] = 0;
            }
        }
        if (choice[3] == 1)
        {
            mode[0] = 1;
            mode[1] = 1;
            break;
        }
        if (choice[4] == 1 && start != -1 && end != -1)
        {
            distance = PlanPath(start, end);
            DrawRoute();
            setcolor(RED);
            settextstyle(2, 0, 6);

            itoa(distance, dist, 10);
            puthz(3, 33, "预", 24, 0, BLUE);
            puthz(3, 63, "计", 24, 0, BLUE);
            puthz(3, 93, "里", 24, 0, BLUE);
            puthz(3, 123, "程", 24, 0, BLUE);
            outtextxy(0, 150, dist);
            puthz(3, 170, "米", 24, 0, BLUE);

            itoa(distance / 5, dist, 10);
            puthz(3, 233, "预", 24, 0, BLUE);
            puthz(3, 263, "计", 24, 0, BLUE);
            puthz(3, 293, "用", 24, 0, BLUE);
            puthz(3, 323, "时", 24, 0, BLUE);
            outtextxy(0, 350, dist);
            puthz(3, 370, "秒", 24, 0, BLUE);

            start = -1, end = -1;
        }
        if (choice[5] == 1 )
        {
            ClearGraph();
            OpenDisplay();
            break;
        }
    }
    return 1;
}

/****************************************
FUNCTION:ChoosePlace
DESCRIBETION:选择地点
INPUT:void
RETURN:int
****************************************/
int ChoosePlace()
{
    int place[14] = { 0 }, i = 0;
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        place[0] = mouse_press(15, 115, 185, 240);        //紫菘
        place[1] = mouse_press(210, 115, 330, 235);       //居民区
        place[2] = mouse_press(140, 250, 250, 300);        //科技楼
        place[3] = mouse_press(20, 255, 110, 345);       //西操
        place[4] = mouse_press(25, 340, 110, 450);        //西十二
        place[5] = mouse_press(155, 360, 255, 450);       //主图
        place[6] = mouse_press(295, 255, 330, 450);        //师生
        place[7] = mouse_press(360, 190, 430, 225);       //韵九
        place[8] = mouse_press(360, 115, 460, 170) + mouse_press(455, 120, 620, 220);        //韵苑
        place[9] = mouse_press(360, 255, 510, 330);       //东九
        place[10] = mouse_press(540, 250, 620, 330);        //东操
        place[11] = mouse_press(360, 365, 510, 455);       //启明楼
        place[12] = mouse_press(540, 360, 620, 455);       //东图


        setfillstyle(1, GREEN);
        if (place[0] == 1)
        {
            fillellipse(100, 230, 5, 5);
        }
        else if (place[1] == 1)
        {
            fillellipse(270, 230, 5, 5);
        }
        else if (place[2] == 1)
        {
            fillellipse(200, 300, 5, 5);
        }
        else if (place[3] == 1)
        {
            fillellipse(110, 310, 5, 5);
        }
        else if (place[4] == 1)
        {
            fillellipse(70, 380, 5, 5);
        }
        else if (place[5] == 1)
        {
            fillellipse(200, 350, 5, 5);
        }
        else if (place[6] == 1)
        {
            fillellipse(290, 330, 5, 5);
        }
        else if (place[7] == 1)
        {
            fillellipse(400, 230, 5, 5);
        }
        else if (place[8] == 1)
        {
            fillellipse(540, 230, 5, 5);
        }
        else if (place[9] == 1)
        {
            fillellipse(440, 250, 5, 5);
        }
        else if (place[10] == 1)
        {
            fillellipse(545, 290, 5, 5);
        }
        else if (place[11] == 1)
        {
            fillellipse(510, 410, 5, 5);
        }
        else if (place[12] == 1)
        {
            fillellipse(545, 405, 5, 5);
        }
        for (i = 0; i < 13; i++)
        {
            if (place[i] == 1)
                return i;
        }
    }
}