/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—10
*   说明：Page类函数实现打开页面功能
**************************************************?
**/

#include<graphics.h>
#include"display.h"
#include"navigat.h"
#include"hz.h"
#include"setting.h"
#include"carinf.h"
#include"mouse.h"
#include"page.h"
#include"init.h"
#include "d_mode.h"  // 添加头文件包含
/****************************************
FUNCTION:OpenMainPage
DESCRIBETION:打开主页
INPUT:void
RETURN:void
****************************************/
void OpenMainPage()
{
    int main_page_ret = 1,mode;
    ClearGraph();
    DrawHomeMode(&mode);
    DrawMapButton();
    DrawCarinfButton();
    DrawSettingButton();
	DrawTopMid(0);
    DrawHomeRet();
    DrawToHome();

    main_page_ret = MainPageMouse(&mode);
   
    if (!main_page_ret)
        return;
}

void DrawMid(int x, int y)
{
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTBLUE);
    line(23 + x, 0 + y, 0 + x, 20 + y);
    line(0 + x, 20 + y, 0 + x, 75 + y);
    line(0 + x, 75 + y, 20 + x, 75 + y);
    line(20 + x, 75 + y, 24 + x, 65 + y);
    line(24 + x, 65 + y, 135 + x, 65 + y);
    line(135 + x, 65 + y, 135 + x, 75 + y);
    line(135 + x, 75 + y, 155 + x, 75 + y);
    line(155 + x, 75 + y, 175 + x, 55 + y);
    line(175 + x, 55 + y, 175 + x, 15 + y);
    line(175 + x, 15 + y, 184 + x, 0 + y);
    line(184 + x, 0 + y, 23 + x, 0 + y);
}
/****************************************
FUNCTION:DrawHomeMode
DESCRIBETION:绘制主页的三种驾驶模式
INPUT:void
RETURN:void
****************************************/
void DrawHomeMode(int* mode)
{
    // 从文件读取当前模式
    FILE* fp = fopen("..\\CODE\\text\\d_mode.txt", "rt");
    if (fp) {
        int saved_mode;
        if (fscanf(fp, "%d", &saved_mode) == 1 && saved_mode >= MODE_A && saved_mode <= MODE_C) {
            *mode = saved_mode;
        }
        fclose(fp);
    }

    // 画炫酷的框框
    DrawMid(30, 110);
    DrawMid(245 - 23, 110);
    DrawMid(436 - 23, 110);

    // 文字（根据当前模式高亮显示）
    setcolor(*mode == MODE_A ? YELLOW : LIGHTBLUE);
    puthz(68, 130, "手动模式", 24, 26, *mode == MODE_A ? YELLOW : LIGHTBLUE);

    setcolor(*mode == MODE_B ? YELLOW : LIGHTBLUE);
    puthz(263, 130, "辅助模式", 24, 26, *mode == MODE_B ? YELLOW : LIGHTBLUE);

    setcolor(*mode == MODE_C ? YELLOW : LIGHTBLUE);
    puthz(450, 130, "自动模式", 24, 26, *mode == MODE_C ? YELLOW : LIGHTBLUE);
}


/****************************************
FUNCTION:DrawMapButton
DESCRIBETION:绘制地图按钮
INPUT:void
RETURN:void
****************************************/
void DrawMapButton()
{
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTBLUE);

    ellipse(132, 310, 90, 150, 55, 55);
    ellipse(132, 310, 210, 270, 55, 55);
    ellipse(132, 310, -30, 30, 55, 55);

    setlinestyle(0, 0, 3);
    ellipse(132, 310, 60, 120, 60, 60);
    ellipse(132, 310, 180, 240, 60, 60);
    ellipse(132, 310, 300, 360, 60, 60);

    setlinestyle(0, 0, 3);
    ellipse(132, 315, 130, 410, 20, 10);
    ellipse(132, 315, 130, 410, 18, 9);

    setlinestyle(0, 0, 1);
    circle(132, 290, 8);
    ellipse(132, 290, -30, 210, 18, 18);
    line(116, 299, 132, 315);
    line(148, 299, 132, 315);
    floodfill(132, 312, LIGHTBLUE);
	puthz(115, 336, "地图", 16, 18, LIGHTBLUE);//画图标
}

/****************************************
FUNCTION:DrawCarinfButton()
DESCRIBETION:绘制车辆信息按钮
INPUT:void
RETURN:void
****************************************/
void DrawCarinfButton()
{
    int point_carout[46] = { 305,314,305,323,299,323,299,314,296,314,296,300,298,296,295,296,295,292,300,292,305,285,
                     335,285,340,292,345,292,345,296,342,296,344,296,344,314,341,314,341,323,335,323,335,314,305,314 };
	int point_carin1[10] = {307,288,303,297,337,297,333,288,307,288 };
	int point_carin2[10] = { 302,302,302,305,307,305,307,302,302,302 };
	int point_carin3[10] = { 333,302,333,305,338,305,338,302,333,302 };
    drawpoly(23, point_carout);
	drawpoly(5, point_carin1);
	drawpoly(5, point_carin2);
	drawpoly(5, point_carin3);
	floodfill(320, 310, LIGHTBLUE);//画图标

    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTBLUE);

    ellipse(320, 310, 90, 150, 55, 55);
    ellipse(320, 310, 210, 270, 55, 55);
    ellipse(320, 310, -30, 30, 55, 55);

    setlinestyle(0, 0, 3);
    ellipse(320, 310, 60, 120, 60, 60);
    ellipse(320, 310, 180, 240, 60, 60);
    ellipse(320, 310, 300, 360, 60, 60);

    puthz(285, 336, "车辆信息", 16, 18, LIGHTBLUE);

    
}

/****************************************
FUNCTION:DrawSettingButton
DESCRIBETION:绘制设置按钮
INPUT:void
RETURN:void
****************************************/
void DrawSettingButton()
{
    int point_wrench[32] = { 486,287,494,295,499,290,491,282,498,282,507,290,507,295,531,319,533,325,531,329,526,329,524,328,498,302,492,302,486,295,486,287 };
    int point_1[16] = { 513,294,521,302,535,288,535,283,533,280,531,278,527,280,513,294 };
	int point_2[18] = { 495,317,502,310,505,313,498,320,497,323,488,330,485,327,491,318,495,317 };
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTBLUE);
    drawpoly(16, point_wrench);
	drawpoly(8, point_1);
	drawpoly(9, point_2);
	circle(527, 323, 2);
	floodfill(508,304, LIGHTBLUE);
	floodfill(532,282, LIGHTBLUE);
	floodfill(492,322, LIGHTBLUE);//画图标

    ellipse(508, 310, 90, 150, 55, 55);
    ellipse(508, 310, 210, 270, 55, 55);
    ellipse(508, 310, -30, 30, 55, 55);

    setlinestyle(0, 0, 3);
    ellipse(508, 310, 60, 120, 60, 60);
    ellipse(508, 310, 180, 240, 60, 60);
    ellipse(508, 310, 300, 360, 60, 60);
    puthz(491, 336, "设置", 16, 18, LIGHTBLUE);

}

/****************************************
FUNCTION:DrawTopMid()
DESCRIBETION:绘制顶部中间
INPUT:void
RETURN:void
****************************************/
void DrawTopMid(int y)
{
   /* int point_upmid[32] = { 94, 0,  99, 8, 103, 8, 112, 20, 112, 56, 125, 72, 140, 72, 145, 68,
                            495,68,500,72, 515,72, 528, 56, 528, 20, 537,  8, 541,  8, 546, 0 };*/
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    line(94, 0 + y, 99, 8+y);
    line(99, 8+y, 103, 8+y);
    line(103, 8+y, 112, 20+y);
    line(112, 20+y, 112, 56+y);
    line(112, 56+y, 125, 72 + y);
    line(125, 72 + y, 140, 72 + y);
    line(140, 72 + y, 145, 68 + y);
    line(145, 68 + y,495, 68 + y);
    line(495, 68 + y, 500, 72 + y);
    line(500, 72 + y, 515, 72 + y);
    line(515, 72 + y, 528, 56 + y);
    line(528, 56 + y, 528, 20 + y);
    line(528, 20 + y, 537, 8 + y);
    line(537, 8 + y, 541, 8 + y);
    line(541, 8 + y, 546, 0 + y);
   /* setfillstyle(1, BLACK);
    drawpoly(16, point_upmid);
	floodfill(320, 36, LIGHTBLUE);*/
}

/****************************************
FUNCTION:DrawToHome()
DESCRIBETION:绘制直达主页面按钮
INPUT:void
RETURN:void
****************************************/
void DrawToHome()
{
    int point_upleft[14] = { 0,   12,  22, 38,  33, 38,  46, 54, 104, 54, 104, 28,  81, 0 };
    int point_house[20] = { 65,19,54,30,54,40,61,40,61,34,69,34,69,40,76,40,76,30,65,19 };
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    setfillstyle(1, BLACK);
    drawpoly(7, point_upleft);
    floodfill(50, 20, LIGHTBLUE);
    line(65, 14, 51, 28);
    line(65, 14, 79, 28);
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTBLUE);
    drawpoly(10, point_house);
    floodfill(65, 27, LIGHTBLUE);
}

/****************************************
FUNCTION:DrawHomeRet()
DESCRIBETION:绘制返回上一层按钮
INPUT:void
RETURN:void
****************************************/
void DrawHomeRet()
{
    int point_upright[14] = { 640, 12, 618, 38, 607, 38, 594, 54, 536, 54, 536, 28, 559, 0 };
    int point_ang[8] = {568,17,568,23,563,20,568,18};
    setlinestyle(0, 0, 1);
    drawpoly(7, point_upright);
    setfillstyle(1, BLACK);
	floodfill(620, 20,LIGHTBLUE);
    setlinestyle(0, 0, 3);
	line(568, 20, 582, 20);
    ellipse(582, 30, 270, 450, 9, 10);
    line(564, 40, 582, 40);
	drawpoly(4, point_ang);

}



/****************************************
FUNCTION:MainPageMouse
DESCRIBETION:主页鼠标
INPUT:void
RETURN:int
****************************************/
int MainPageMouse(int *mode)
{
    int page[5] = { 0, 0, 0, 0, 0 };
    char* mode_texts[] = { "手动模式", "辅助模式", "自动模式" };

    // 显示当前模式
    setfillstyle(1, BLACK);
    bar(252, 15, 388, 48);
    puthz(252, 15, mode_texts[*mode], 32, 34, LIGHTBLUE);
    while (1)
    {

        //绘制鼠标和设置按钮
        newmouse(&MouseX, &MouseY, &press);
        page[0] = mouse_press(0, 0, 80, 50);//直达主页面
        page[1] = mouse_press(560, 0, 640, 50);//返回上一层
        page[2] = mouse_press(72, 250, 192, 370);//地图
        page[3] = mouse_press(260, 250, 380, 370);//车辆信息
        page[4] = mouse_press(448, 250, 568, 370);//设置
        if (mouse_press(50, 110, 210, 180) == 1) 
        {
            // 写入文件
            FILE* fp = fopen("..\\CODE\\text\\d_mode.txt", "w");
            *mode = MODE_A;
            if (fp) {
                fprintf(fp, "%d", *mode);
                fclose(fp);
            }
            return 1;  // 刷新界面
        }
        else if (mouse_press(240, 110, 400, 180) == 1) 
        {
            // 写入文件
            FILE* fp = fopen("..\\CODE\\text\\d_mode.txt", "w");
            *mode = MODE_B;
            if (fp) {
                fprintf(fp, "%d", *mode);
                fclose(fp);
            }
            return 1;
        }
        else if (mouse_press(430, 110, 600, 180) == 1) 
        {
            // 写入文件
            FILE* fp = fopen("..\\CODE\\text\\d_mode.txt", "w");
            *mode = MODE_C;
            if (fp) {
                fprintf(fp, "%d", *mode);
                fclose(fp);
            }
            return 1;
        }
        
        //判断选项
        if (page[2] == 1)//地图
        {
            ClearGraph();
            OpenNavigation();
            break;
        }
		else if (page[3] == 1)//车辆信息
        {
            ClearGraph();
			//clrmous(MouseX, MouseY);
            //mouseinit();
            //OpenCarinf();
            //mouse_press(260, 250, 380, 370);
            OpenCarinf();

            //delay(1000);
            break;
        }
		else if (page[4] == 1)//设置
        {
            ClearGraph();
            OpenSetting();
            break;
        }
        else if (page[0] == 1)//直达主页面
        {
			ClearGraph();
			OpenMainPage();
			break;
		}
		else if (page[1] == 1)//返回上一层
		{
            closegraph();
            return 0;
		}
    }
    return 1;
}

