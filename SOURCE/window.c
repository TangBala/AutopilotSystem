/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—8
*   说明：Window类函数实现车窗功能
**************************************************?
**/

#include"init.h"
#include"window.h"
#include "page.h"

/****************************************
FUNCTION:OpenWindow
DESCRIBETION:打开车窗页
INPUT:void
RETURN:void
****************************************/
void OpenWindow()
{
    while(1)
    {
        int i = 0, num[4], window_ret = 1;
        FILE* window_text;

        window_text = fopen("..\\CODE\\text\\window.txt", "rt");
        for(i = 0; i < 4; i++)
        {
            fscanf(window_text, "%d ", &num[i]);
        }
        fclose(window_text);

        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawOneButton(80, 150);    
        DrawOneButton(440, 150);
        DrawOneButton(80, 370);
        DrawOneButton(440, 370);

        DrawWindowChangePart(num);
        DrawCar2();
        PutWindowHz();
        window_ret = WindowMouse(num);

        window_text = fopen("..\\CODE\\text\\window.txt", "wt");
        for(i = 0; i < 4; i++)
        {
            fprintf(window_text, "%d ", num[i]);
        }
        fclose(window_text);

        if(!window_ret) //If zero, then return
            return ;
    }
}

void DrawCar2()
{
    setcolor(LIGHTGRAY);
    line(133, 265, 133, 297);
    line(134, 259, 134, 264);line(134, 298, 134, 305);
    line(135, 254, 135, 258);line(135, 306, 135, 310);
    line(136, 250, 136, 253);line(136, 311, 136, 314);
    line(137, 246, 137, 249);line(137, 315, 137, 318);
    line(138, 243, 138, 245);line(138, 319, 138, 321);
    line(139, 241, 139, 244);line(139, 322, 139, 325);
    line(140, 238, 140, 240);line(140, 326, 140, 328);
    //putpixel(141, 237, BLUE);putpixel(141, 329, BLUE);
    line(142, 234, 142, 236);line(142, 330, 142, 332);
    line(143, 233, 144, 232);line(143, 333, 144, 334);
    line(145, 230, 145, 232);line(145, 335, 145, 337);
    line(146, 229, 153, 222);line(146, 338, 153, 345);
    line(154, 221, 156, 221);line(154, 346, 156, 346);
    line(157, 220, 159, 218);line(157, 347, 159, 349);
    line(160, 217, 163, 214);line(160, 350, 163, 353);
    line(164, 213, 167, 213);line(164, 354, 167, 354);
    line(168, 212, 448, 212);line(168, 355, 448, 355);
    line(449, 213, 469, 213);line(449, 354, 469, 354);
    line(470, 214, 482, 214);line(470, 353, 482, 353);
    line(483, 215, 489, 215);line(483, 352, 489, 352);
    line(490, 216, 493, 216);line(490, 351, 493, 351);
    line(494, 217, 497, 217);line(494, 350, 497, 350);
    line(498, 218, 500, 218);line(498, 349, 500, 351);
    line(501, 219, 501, 221);line(501, 346, 501, 348);
    line(502, 222, 502, 224);line(502, 343, 502, 345);
    line(503, 225, 503, 228);line(503, 339, 503, 342);
    line(504, 229, 504, 232);line(504, 335, 504, 338);
    line(505, 233, 505, 236);line(505, 331, 505, 334);
    line(506, 237, 506, 240);line(506, 327, 506, 330);
    line(507, 241, 507, 245);line(507, 332, 507, 326);
    line(508, 246, 508, 251);line(508, 321, 508, 325);
    line(509, 252, 509, 259);line(509, 313, 509, 320);
    line(510, 260, 510, 271);line(510, 301, 510, 312);
    line(511, 272, 511, 300);//
    line(137, 273, 137, 289);
    line(138, 267, 138, 272);line(138, 290, 138, 295);
    line(139, 261, 139, 266);line(139, 296, 139, 301);
    line(140, 256, 140, 260);line(140, 302, 140, 306);
    line(141, 252, 141, 255);line(141, 307, 141, 310);
    line(142, 251, 148, 239);line(142, 311, 148, 323);
    line(149, 238, 155, 235);line(149, 324, 155, 327);
    line(156, 234, 160, 234);line(156, 328, 160, 328);
    line(161, 233, 167, 233);line(161, 329, 167, 329);
    line(168, 232, 173, 232);line(168, 330, 173, 330);
    line(174, 231, 231, 231);line(174, 331, 231, 331);
    line(232, 232, 237, 232);line(232, 330, 237, 330);
    line(238, 233, 278, 243);line(238, 329, 278, 319);
    line(280, 244, 290, 246);line(280, 318, 290, 316);
    line(291, 247, 355, 247);line(291, 315, 355, 315);
    line(356, 246, 380, 244);line(356, 316, 380, 318);
    line(381, 243, 413, 239);line(381, 319, 413, 323);
    line(414, 238, 434, 238);line(414, 324, 434, 324);
    line(435, 237, 455, 237);line(435, 325, 455, 325);
    line(232, 233, 227, 243);line(232, 329, 227, 319);
    line(226, 244, 221, 259);line(226, 318, 221, 303);
    line(220, 260, 217, 272);line(220, 302, 217, 290);
    line(218, 272, 218, 290);
    line(280, 244, 280, 318);
    line(387, 243, 391, 259);line(387, 319, 391, 299);
    line(391, 259, 391, 299);//
    line(434, 238, 441, 266);line(434, 324, 441, 296);
    line(441, 266, 441, 296);
    line(455, 238, 457, 242);line(455, 324, 457, 320);
    line(458, 243, 461, 246);line(458, 319, 461, 316);
    line(462, 247, 465, 253);line(462, 315, 465, 309);
    line(466, 254, 471, 269);line(466, 308, 471, 293);
    line(471, 269, 471, 293);
    moveto(151, 231);lineto(154, 225);lineto(159, 220);lineto(195, 220);
    lineto(174, 227);lineto(151, 231);line(154, 225, 155, 225);
    moveto(146, 330);lineto(149, 336);lineto(154, 341);lineto(190, 341);
    lineto(169, 334);lineto(146, 330);line(149, 336, 175, 336);
    moveto(248, 216);lineto(408, 216);lineto(358, 236);lineto(298, 236);
    lineto(248, 216);line(328, 216, 328, 236);//c 0 5 10 15 20
    moveto(248, 351);lineto(408, 351);lineto(358, 331);lineto(298, 331);
    lineto(248, 351);line(328, 351, 328, 331);//c
    moveto(471, 221);lineto(491, 221);lineto(501, 231);lineto(471, 221);
    moveto(471, 345);lineto(491, 345);lineto(501, 335);lineto(471, 345);
    rectangle(490, 246, 500, 316);
    moveto(248, 212);lineto(248, 210);lineto(254, 204);lineto(256, 204);
    lineto(256, 202);lineto(254, 212);
    moveto(248, 355);lineto(248, 357);lineto(254, 363);lineto(256, 363);
    lineto(256, 361);lineto(254, 355);
    setfillstyle(1, LIGHTGRAY);
}
/****************************************
FUNCTION:DrawOneButton
DESCRIBETION:绘制一个车窗
INPUT:int x, int y
RETURN:void
****************************************/
void DrawOneButton(int x, int y)
{
    //绘制方框
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    rectangle(x, y, 120+x, 40+y);
	line(60 + x, y, 60 + x, 40 + y);
   // 绘制上下按钮
    setlinestyle(0, 0, 3);
    line(13+x, 32+y, 30+x, 7+y);
    line(31+x, 7+y, 48+x, 32+y);
    line(13+60 + x, 7+ y, 30 +60+ x, 32 + y);
    line(31+60 + x, 32 + y, 48 +60+ x, 7 + y);
 
}

/****************************************
FUNCTION:DrawWindowChangePart
DESCRIBETION:绘制车窗页面可变的部分
INPUT:int* num
RETURN:void
****************************************/
void DrawWindowChangePart(int* num)
{
    setlinestyle(0, 0, 1);
    setfillstyle(1, LIGHTCYAN);
    setcolor(LIGHTBLUE);
    line(248, 216, 328, 216);
    line(248, 216, 248+num[0] * 50.0 / 4, 216 + num[0] * 20.0 / 4);
    line(328, 216, 328, 216 + num[0] * 20.0 / 4);
    line(248 + num[0] * 50.0 / 4, 216 + num[0] * 20.0 / 4, 328, 216 + num[0] * 20.0 / 4);
    if(num[0]!=0)
    {
        floodfill(270, 220, LIGHTBLUE);
    }
    line(408, 216, 328, 216);
    line(408, 216, 408 -num[1] * 50.0 / 4, 216 + num[1] * 20.0 / 4);
    line(328, 216, 328, 216 + num[1] * 20.0 / 4);
    line(408 - num[1] * 50.0 / 4, 216 + num[1] * 20.0 / 4, 328, 216 + num[1] * 20.0 / 4);
    if (num[1] != 0)
    {
        floodfill(358, 220, LIGHTBLUE);
    }
    line(248, 351, 328, 351);
    line(248, 351, 248 + num[2] * 50.0 / 4, 351 - num[2] * 20.0 / 4);
    line(328, 351, 328, 351 - num[2] * 20.0 / 4);
    line(248 + num[2] * 50.0 / 4, 351 - num[2] * 20.0 / 4, 328,351- num[2] * 20.0 / 4);
    if (num[2] != 0)
    {
        floodfill(270, 347, LIGHTBLUE);
    }
    line(408, 351, 328, 351);
    line(408, 351, 408 - num[3] * 50.0 / 4, 351- num[3] * 20.0 / 4);
    line(328, 351, 328, 351- num[3] * 20.0 / 4);
    line(408 - num[3] * 50.0 / 4, 351- num[3] * 20.0 / 4, 328, 351- num[3] * 20.0 / 4);
    if (num[3] != 0)
    {
        floodfill(358, 347, LIGHTBLUE);
    }
    
}

/****************************************
FUNCTION:PutWindowHz
DESCRIBETION:显示车窗页汉字
INPUT:void
RETURN:void
****************************************/
void PutWindowHz()
{
    puthz(40, 100, "右前窗", 32, 38, LIGHTBLUE);
    puthz(492, 100, "右后窗", 32, 38, LIGHTBLUE);
    puthz(40, 420, "左前窗", 32, 38, LIGHTBLUE);
    puthz(492, 420, "左前窗", 32, 38, LIGHTBLUE);
    puthz(304-8, 100, "一键", 24, 26, LIGHTBLUE);
    puthz(290-8, 150-8, "开", 16, 0, LIGHTBLUE);
    puthz(350-8, 150-8, "关", 16, 0, LIGHTBLUE);
    setcolor(LIGHTBLUE);
    circle(290, 150, 20);
    circle(350, 150, 20);

}

/****************************************
FUNCTION:WindowMouse
DESCRIBETION:车窗页的鼠标功能
INPUT:int*
RETURN:int
****************************************/
int WindowMouse(int* num)
{
    int choice[12] = {0};
    while(1)
        {
            //绘制鼠标和设置按钮
            newmouse(&MouseX,&MouseY,&press);
            choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
            choice[11] = mouse_press(560, 0, 640, 50);//返回上一层

            choice[1] = mouse_press(80,150,140,190);   
            choice[2] = mouse_press(141,150,200,190); 
            choice[3] = mouse_press(440, 150, 500, 190);
            choice[4] = mouse_press(501, 150, 560, 190);
            choice[5] = mouse_press(80, 370, 140, 410);
            choice[6] = mouse_press(141, 370, 200, 410);
            choice[7] = mouse_press(440, 370, 500,410);
            choice[8] = mouse_press(501, 370, 560,410);

            choice[9] = mouse_press(270, 130, 310, 170);  //一键
            choice[10] = mouse_press(330, 130, 370, 170);  //一键
            //判断选项
            if (choice[0] == 1)//直达主页面
            {
                ClearGraph();
                OpenMainPage();
                break;
            }
            else if (choice[11] == 1)//返回上一层
            {
                return 0;
            }
            else if(choice[1]==1)
            {
                if(num[0]<4)
                    num[0]+=1;
                delay(300);
                break;
            }
            else if(choice[2]==1)
            {
                if(num[0]>0)
                    num[0]-=1;
                delay(300);
                break;
            }
            else if (choice[3] == 1)
            {
                if (num[1] < 4)
                    num[1] += 1;
                delay(300);
                break;
            }
            else if (choice[4] == 1)
            {
                if (num[1] > 0)
                    num[1] -= 1;
                delay(300);
                break;
            }
            else if (choice[5] == 1)
            {
                if (num[2] < 4)
                    num[2] += 1;
                delay(300);
                break;
            }
            else if (choice[6] == 1)
            {
                if (num[2] > 0)
                    num[2] -= 1;
                delay(300);
                break;
			}
			else if (choice[7] == 1)
			{
				if (num[3] < 4)
					num[3] += 1;
                delay(300);
                break;
			}
			else if (choice[8] == 1)
			{
				if (num[3] > 0)
					num[3] -= 1;
                delay(300);
                break;
			}
		
            else if(choice[9]==1)
            {
                num[0] = 0, num[1] = 0, num[2] = 0, num[3] = 0;
                break;
            }
            else if (choice[10] == 1)
            {
                num[0] = 4, num[1] = 4, num[2] = 4, num[3] = 4;
                break;
            }

       /*     else if(choice[11]==1)
            {
                if(num[3]>0)
                    num[3]-=1;
                break;
            }*/
           /* else if(choice[12]==1)
            {
                num[7]^=1;
                num[3]=10;
                break;
            }*/
        }
    return 1;
}