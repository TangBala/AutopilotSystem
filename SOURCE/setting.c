/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—19
*   说明：Menu类函数实现菜单功能
**************************************************?
**/
#include"page.h"
#include"setting.h"
#include"init.h"

#include"ac.h"
#include"battery.h"
#include"door.h"
#include"drive.h"
#include"light.h"
#include"window.h"
#include"wiper.h"
#include"sunroof.h"
#include"tire.h"

/****************************************
FUNCTION:OpenSetting
DESCRIBETION:打开菜单页
INPUT:void
RETURN:void
****************************************/
void OpenSetting()
{
    while(1)
    {
        int setting_ret = 1;
        //绘制界面
        ClearGraph();
        DrawAirconditionButton();
        DrawLightButton();
        DrawDoorButton();
        DrawWindowButton();
        DrawWiperButton();

        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
    
        setting_ret = SettingMouse();

        if(!setting_ret)
            return ;
    }

}


/****************************************
FUNCTION:DrawAirconditionButton
DESCRIBETION:绘制空调按钮
INPUT:void
RETURN:void
****************************************/
void DrawAirconditionButton()
{
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    setfillstyle(1, BLUE);
    rectangle(90, 118,175,159);
	line(98, 128, 122, 128);
	line(131, 128, 155, 128);
    line(98, 138, 122, 138);
    line(131, 138, 155, 138);
    line(98, 148, 155, 148);
	circle(165, 128, 2);

    line(108, 168, 103, 175);
    line(103, 175, 108, 182);
    line(108, 182, 103, 189);
    line(120, 168, 115, 175);
    line(115, 175, 120, 182);
    line(120, 182, 115, 189); 
    line(132, 168, 127, 175);
    line(127, 175, 132, 182);
    line(132, 182, 127, 189);

	line(154, 168, 154, 188);
	line(145, 173, 163, 183);
    line(163, 173, 145, 183);




    
    puthz(108, 195, "空调", 24, 26, LIGHTBLUE);

}

/****************************************
FUNCTION:DrawWiperButton
DESCRIBETION:绘制雨刷按钮
INPUT:void
RETURN:void
****************************************/
void DrawWiperButton()
{
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    setfillstyle(1, WHITE);
    circle(320, 180, 6);
	floodfill(320, 180, WHITE);
    ellipse(320, 190, 45, 60, 70, 70);
    ellipse(320, 190, 80, 135, 70, 70);
    ellipse(343, 129, 150, 390, 5, 5);
    ellipse(320, 190, 45, 135, 30, 30);
    line(270, 140, 298, 169);
	line(370, 140, 342, 169);
    line(320, 180, 295, 125);
    setlinestyle(0, 0, 1);
	line(343, 116, 347, 126);
    line(343, 116, 339, 126);
	floodfill(343, 129, WHITE);

    puthz(288, 195, "雨刷", 24, 26, LIGHTBLUE);
}

/****************************************
FUNCTION:DrawLightButton
DESCRIBETION:绘制灯光按钮
INPUT:void
RETURN:void
****************************************/
void DrawLightButton()
{
    setcolor(WHITE);
    setlinestyle(0, 0, 5);
    line(480, 132,512, 132);
    line(480, 142, 512, 142);
    line(480, 152, 512, 152);
    line(480, 162, 512, 162);
    line(480, 172, 512, 172);
    ellipse(532, 151,240,480, 25, 25);
    line(520, 131, 520, 172);
    puthz(488, 195, "灯光", 24, 26, LIGHTBLUE);

}

/****************************************
FUNCTION:DrawWindowButton
DESCRIBETION:绘制车窗按钮
INPUT:void
RETURN:void
****************************************/
void DrawWindowButton()
{
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
	line(128, 314, 95, 352);
	line(128, 314, 160, 314);
	line(160,314, 160, 390);
	line(95, 352, 128, 352);
    line(95, 352, 95, 390);
	line(109, 352, 129, 328);
	line(129, 328, 160, 328);
    rectangle(95, 352, 160, 390);
	line(128, 361, 123, 367);
    line(128, 361, 133, 367);
    line(128, 382, 123, 376);
    line(128, 382, 133, 376);
    puthz(105, 415, "车窗", 24, 26, LIGHTBLUE);
}

/****************************************
FUNCTION:DrawDoorButton
DESCRIBETION:绘制车门按钮
INPUT:void
RETURN:void
****************************************/
void DrawDoorButton()
{
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    setfillstyle(1, WHITE);
	ellipse(310, 330, 90, 180, 10, 10);
    ellipse(330, 330, 0, 90, 10, 10);
    ellipse(310, 390, 180, 270, 10, 10);
    ellipse(330, 390, 270, 360, 10, 10);
	ellipse(310, 330, 90, 180, 10, 10);
    line(310, 320, 330, 320);
    line(300, 330, 300, 350);
    line(300, 370, 300, 390);
    line(310, 400, 330, 400);
    line(340, 330, 340, 390);
    line(300, 350, 284, 366);
	line(300, 340, 294, 343);
	line(294, 343, 300, 345);
    line(340, 340, 346, 343);
    line(346, 343, 340, 345);
    line(310, 356, 310, 365);
    line(312, 356, 312, 365);
    line(328, 356, 328, 365);
    line(330, 356, 330, 365);

   // rectangle(310, 336, 330, 348);
    //rectangle(310, 374, 330, 386);
    setlinestyle(0,0,1);
    ellipse(320, 376, 70, 110, 30, 30);
    ellipse(320, 353, 60, 120, 21, 21);
    line(310, 336, 310, 347);
	line(330, 336, 330, 347);
    ellipse(320, 406, 70, 110, 30, 30);
    ellipse(320, 370, 240, 300, 23, 21);
    line(309, 378, 309, 388);
    line(331, 378, 331, 388);
	floodfill(320, 340, WHITE);
	floodfill(320, 378, WHITE);
    puthz(294, 415, "车门", 24, 26, LIGHTBLUE);

}

/****************************************
FUNCTION:SettingMouse
DESCRIBETION:菜单页鼠标
INPUT:void
RETURN:int
****************************************/
int SettingMouse()
{
    int choice[7] = {0, 0, 0, 0, 0, 0, 0};
    while(1)
    {
        //绘制鼠标和设置按钮
        newmouse(&MouseX, &MouseY, &press);
        choice[0] = mouse_press(560, 0, 640, 50);
		choice[1] = mouse_press(65, 105, 200, 220);//空调
		choice[2] = mouse_press(455, 105, 585, 220);//灯光
		choice[3] = mouse_press(280, 310, 360, 460);//车门
		choice[4] = mouse_press(65, 310, 200, 460);//车窗
        choice[5] = mouse_press(280, 105, 360, 220);//雨刷
        choice[6] = mouse_press(40, 15, 100, 50);

        //判断选项
        
        if(choice[1] == 1)
        {
            ClearGraph();
			OpenAircondition();//空调
            break;
        }
        else if(choice[2] == 1)
        {
            ClearGraph();
			OpenLight();//灯光
            break;
        }
        else if(choice[3] == 1)
        {
            ClearGraph();
			OpenDoor();//车门 
            break;
        }
        else if(choice[4] == 1)
        {
            ClearGraph();
			OpenWindow();//车窗
            break;
        }
        else if(choice[5] == 1)
        {
            ClearGraph();
			OpenWiper();//雨刷
            break;
        }
        
        else if(choice[6] == 1)
        {
            return 0;
        }
        else if(choice[0] == 1)
        {
            return 0;
        }
    }
    return 1;
}