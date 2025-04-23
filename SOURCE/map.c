/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—4—10
*   说明：Map类函数绘制地图
**************************************************?
**/

#include <graphics.h>
#include <dos.h>
#include <time.h>
#include "hz.h"
#include "map.h"
#include "mouse.h"



/****************************************
FUNCTION:GetBuildingByPoint
DESCRIBETION:根据坐标点获取建筑物编号
INPUT:int x, int y
RETURN:int 建筑物编号(-1表示没有选中建筑物)
****************************************/
int GetBuildingByPoint(int x, int y) {
    // 紫菘
    if (x >= 15 && x <= 200 && y >= 110 && y <= 230) return 0;
    // 居民区
    if (x >= 220 && x <= 335 && y >= 110 && y <= 230) return 1;
    // 西操
    if (x >= 15 && x <= 120 && y >= 245 && y <= 355) return 2;
    // 西十二
    if (x >= 15 && x <= 120 && y >= 370 && y <= 460) return 3;
    // 科技楼
    if (x >= 140 && x <= 265 && y >= 245 && y <= 310) return 4;
    // 主图
    if (x >= 140 && x <= 265 && y >= 340 && y <= 460) return 5;
    // 师生
    if (x >= 290 && x <= 335 && y >= 245 && y <= 460) return 6;
    // 东九
    if (x >= 355 && x <= 515 && y >= 245 && y <= 335) return 7;
    // 东操
    if (x >= 535 && x <= 625 && y >= 245 && y <= 335) return 8;
    // 启明楼
    if (x >= 355 && x <= 515 && y >= 355 && y <= 460) return 9;
    // 东图
    if (x >= 535 && x <= 625 && y >= 355 && y <= 460) return 10;
    // 韵九
    if (x >= 355 && x <= 435 && y >= 185 && y <= 230) return 11;
    // 韵苑
    if ((x >= 355 && x <= 460 && y >= 110 && y <= 175) ||
        (x >= 460 && x <= 625 && y >= 110 && y <= 230)) return 12;

    return -1;
}

/****************************************
FUNCTION:HandleMouseSelection
DESCRIBETION:处理鼠标选择建筑物
INPUT:void
RETURN:void
****************************************/
void HandleMouseSelection() {
    int mx, my, mb;
    int building;

    // 获取鼠标状态
    mread(&mx, &my, &mb);

    // 检查是否左键点击
    if (mb & 1) {
        // 延迟防止多次点击
        delay(200);
        building = GetBuildingByPoint(mx, my);
    }
}

/****************************************
FUNCTION:MainLoop
DESCRIBETION:主循环处理用户交互
INPUT:void
RETURN:void
****************************************/
void MainLoop() {
    // 初始化鼠标
    mouseinit();

    while (!kbhit()) {
        // 绘制鼠标
        newmouse(&MouseX, &MouseY, &press);

        // 处理鼠标选择
        HandleMouseSelection();
    }

    // 关闭鼠标
    regs.x.ax = 0;
    int86(0x33, &regs, &regs);
}

/****************************************
FUNCTION:DrawRoad
DESCRIBETION:绘制道路
INPUT:void
RETURN:void
****************************************/
void DrawRoad()
{
    setlinestyle(0, 0, 1);
    setcolor(LIGHTGRAY);

    DrawVerticalRoad(280, 240, 230);     //华中路 x=280, 240<y<470
    DrawVerticalRoad(125, 240, 230);     //紫菘路 x=125, 240<y<470
    DrawVerticalRoad(340, 110, 360);     //东五路 x=340, 110<y<470
    DrawVerticalRoad(530, 240, 230);    //启明路 x=530, 240<y<470
    DrawVerticalRoad(450, 180, 60);    // 韵苑韵九拐弯x=450, 180<y<240
    DrawVerticalRoad(205, 110, 130);    // 紫菘居民路x=205, 110<y<240

    DrawParallelRoad(15, 240, 615);     //喻园大道 y=240, 15<x<630
    DrawParallelRoad(125, 320, 155);     //红棉路 y=320, 125<x<280
    DrawParallelRoad(340, 180, 110);     //韵九韵苑拐弯y=180, 340<x<450
    DrawParallelRoad(15, 360, 110);     //西操西十二小路y=360, 185<x<125
    DrawParallelRoad(340, 340, 290);     //东九东图东操启明楼路y=340, 340<x<630

    setlinestyle(0, 0, 1);
    setcolor(WHITE);

    DrawCrossing(280, 320, 1, 1, 1, 0); //华中路 红棉路 14
    DrawCrossing(125, 320, 1, 1, 0, 1); //紫菘路 红棉路 14
    DrawCrossing(125, 240, 0, 1, 1, 1); //紫菘路 喻园大道 14
    DrawCrossing(125, 360, 1, 1, 1, 0); //紫菘路 西操西十二小路 14
    DrawCrossing(205, 240, 1, 0, 1, 1); //紫菘居民路 喻园大道 14
    DrawCrossing(280, 240, 0, 1, 1, 1); //华中路 喻园大道 14
    DrawCrossing(340, 240, 1, 1, 1, 1); //东五路 喻园大道 14
    DrawCrossing(340, 180, 1, 1, 0, 1); //东五路 韵九韵苑 14
    DrawCrossing(450, 240, 1, 0, 1, 1); //韵九韵苑 喻园大道 14
    DrawCrossing(450, 180, 0, 1, 1, 0); //紫菘居民路 喻园大道 14
    DrawCrossing(530, 340, 1, 1, 1, 1); //启明路 十字路口 14
    DrawCrossing(530, 240, 0, 1, 1, 1); //启明路 喻园大道 14
    DrawCrossing(340, 340, 1, 1, 0, 1); //东五路 东九东图 14
}

/****************************************
FUNCTION:DrawParallelRoad
DESCRIBETION:绘制横向道路
INPUT:int x, int y, int d
RETURN:void
****************************************/
void DrawParallelRoad(int x, int y, int d)
{
    line(x, y - 2, x + d, y - 2);
    line(x, y + 2, x + d, y + 2);

}

/****************************************
FUNCTION:DrawVerticalRoad
DESCRIBETION:绘制纵向道路
INPUT:int x, int y, int d
RETURN:void
****************************************/
void DrawVerticalRoad(int x, int y, int d)
{
    line(x - 2, y, x - 2, y + d);
    line(x + 2, y, x + 2, y + d);
}

/****************************************
FUNCTION:DrawCrossing
DESCRIBETION:绘制纵向十字路口
INPUT:int x, int y, int north, int south, int west, int east
RETURN:void
****************************************/
void DrawCrossing(int x, int y, int north, int south, int west, int east)
{
    if (north)
        line(x - 1, y - 2, x + 1, y - 2);
    if (south)
        line(x - 1, y + 2, x + 1, y + 2);
    if (west)
        line(x - 2, y - 1, x - 2, y + 1);
    if (east)
        line(x + 2, y - 1, x + 2, y + 1);
}

/****************************************
FUNCTION:DrawBuilding
DESCRIBETION:绘制建筑物
INPUT:void
RETURN:void
****************************************/
void DrawBuilding()
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 110, 200, 230);  //紫菘    0
    floodfill(105, 170, DARKGRAY);
    puthz(57, 160, "紫菘", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(220, 110, 335, 230);  //居民区    0
    floodfill(275, 170, DARKGRAY);
    puthz(240, 150, "居民区", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 245, 120, 355);  //西操    0
    floodfill(65, 310, DARKGRAY);
    puthz(30, 290, "西操", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 370, 120, 460);  //西十二    0
    floodfill(65, 430, DARKGRAY);
    puthz(30, 410, "西十二", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(140, 245, 265, 310);  //科技楼    0
    floodfill(200, 285, DARKGRAY);
    puthz(175, 260, "科技楼", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(140, 340, 265, 460);  //主图    0
    floodfill(195, 400, DARKGRAY);
    puthz(170, 380, "主图", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(290, 245, 335, 460);  //师生    0
    floodfill(315, 335, DARKGRAY);
    puthz(290, 335, "师生", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 245, 515, 335);  //东九    0
    floodfill(400, 290, DARKGRAY);
    puthz(400, 280, "东九", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(535, 245, 625, 335);  //东操    0
    floodfill(555, 280, DARKGRAY);
    puthz(555, 280, "东操", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 355, 515, 460);  //启明楼    0
    floodfill(400, 400, DARKGRAY);
    puthz(400, 400, "启明楼", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(535, 355, 625, 460);  //东图    0
    floodfill(555, 390, DARKGRAY);
    puthz(555, 390, "东图", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 185, 435, 230);  //韵九    0
    floodfill(370, 200, DARKGRAY);
    puthz(370, 200, "韵九", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 110, 460, 175);  //韵苑    0
    floodfill(400, 145, DARKGRAY);
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(460, 110, 625, 230);  //韵苑    0
    floodfill(535, 185, DARKGRAY);
    puthz(490, 145, "韵苑", 24, 25, WHITE);
}

/****************************************
FUNCTION:DrawMap
DESCRIBETION:绘制地图
INPUT:void
RETURN:void
****************************************/
void DrawMap()
{

    DrawRoad();
    DrawBuilding();
    //SelectStatus();
    setlinestyle(0, 0, 3);
    setcolor(DARKGRAY);

}