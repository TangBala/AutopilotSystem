/**
**************************************************?
*   �汾�ţ�1.0
*   ���ߣ�X
*   �������ڣ�2024��4��10
*   ˵����Map�ຯ�����Ƶ�ͼ
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
DESCRIBETION:����������ȡ��������
INPUT:int x, int y
RETURN:int ��������(-1��ʾû��ѡ�н�����)
****************************************/
int GetBuildingByPoint(int x, int y) {
    // ��ݿ
    if (x >= 15 && x <= 200 && y >= 110 && y <= 230) return 0;
    // ������
    if (x >= 220 && x <= 335 && y >= 110 && y <= 230) return 1;
    // ����
    if (x >= 15 && x <= 120 && y >= 245 && y <= 355) return 2;
    // ��ʮ��
    if (x >= 15 && x <= 120 && y >= 370 && y <= 460) return 3;
    // �Ƽ�¥
    if (x >= 140 && x <= 265 && y >= 245 && y <= 310) return 4;
    // ��ͼ
    if (x >= 140 && x <= 265 && y >= 340 && y <= 460) return 5;
    // ʦ��
    if (x >= 290 && x <= 335 && y >= 245 && y <= 460) return 6;
    // ����
    if (x >= 355 && x <= 515 && y >= 245 && y <= 335) return 7;
    // ����
    if (x >= 535 && x <= 625 && y >= 245 && y <= 335) return 8;
    // ����¥
    if (x >= 355 && x <= 515 && y >= 355 && y <= 460) return 9;
    // ��ͼ
    if (x >= 535 && x <= 625 && y >= 355 && y <= 460) return 10;
    // �Ͼ�
    if (x >= 355 && x <= 435 && y >= 185 && y <= 230) return 11;
    // ��Է
    if ((x >= 355 && x <= 460 && y >= 110 && y <= 175) ||
        (x >= 460 && x <= 625 && y >= 110 && y <= 230)) return 12;

    return -1;
}

/****************************************
FUNCTION:HandleMouseSelection
DESCRIBETION:�������ѡ������
INPUT:void
RETURN:void
****************************************/
void HandleMouseSelection() {
    int mx, my, mb;
    int building;

    // ��ȡ���״̬
    mread(&mx, &my, &mb);

    // ����Ƿ�������
    if (mb & 1) {
        // �ӳٷ�ֹ��ε��
        delay(200);
        building = GetBuildingByPoint(mx, my);
    }
}

/****************************************
FUNCTION:MainLoop
DESCRIBETION:��ѭ�������û�����
INPUT:void
RETURN:void
****************************************/
void MainLoop() {
    // ��ʼ�����
    mouseinit();

    while (!kbhit()) {
        // �������
        newmouse(&MouseX, &MouseY, &press);

        // �������ѡ��
        HandleMouseSelection();
    }

    // �ر����
    regs.x.ax = 0;
    int86(0x33, &regs, &regs);
}

/****************************************
FUNCTION:DrawRoad
DESCRIBETION:���Ƶ�·
INPUT:void
RETURN:void
****************************************/
void DrawRoad()
{
    setlinestyle(0, 0, 1);
    setcolor(LIGHTGRAY);

    DrawVerticalRoad(280, 240, 230);     //����· x=280, 240<y<470
    DrawVerticalRoad(125, 240, 230);     //��ݿ· x=125, 240<y<470
    DrawVerticalRoad(340, 110, 360);     //����· x=340, 110<y<470
    DrawVerticalRoad(530, 240, 230);    //����· x=530, 240<y<470
    DrawVerticalRoad(450, 180, 60);    // ��Է�ϾŹ���x=450, 180<y<240
    DrawVerticalRoad(205, 110, 130);    // ��ݿ����·x=205, 110<y<240

    DrawParallelRoad(15, 240, 615);     //��԰��� y=240, 15<x<630
    DrawParallelRoad(125, 320, 155);     //����· y=320, 125<x<280
    DrawParallelRoad(340, 180, 110);     //�Ͼ���Է����y=180, 340<x<450
    DrawParallelRoad(15, 360, 110);     //������ʮ��С·y=360, 185<x<125
    DrawParallelRoad(340, 340, 290);     //���Ŷ�ͼ��������¥·y=340, 340<x<630

    setlinestyle(0, 0, 1);
    setcolor(WHITE);

    DrawCrossing(280, 320, 1, 1, 1, 0); //����· ����· 14
    DrawCrossing(125, 320, 1, 1, 0, 1); //��ݿ· ����· 14
    DrawCrossing(125, 240, 0, 1, 1, 1); //��ݿ· ��԰��� 14
    DrawCrossing(125, 360, 1, 1, 1, 0); //��ݿ· ������ʮ��С· 14
    DrawCrossing(205, 240, 1, 0, 1, 1); //��ݿ����· ��԰��� 14
    DrawCrossing(280, 240, 0, 1, 1, 1); //����· ��԰��� 14
    DrawCrossing(340, 240, 1, 1, 1, 1); //����· ��԰��� 14
    DrawCrossing(340, 180, 1, 1, 0, 1); //����· �Ͼ���Է 14
    DrawCrossing(450, 240, 1, 0, 1, 1); //�Ͼ���Է ��԰��� 14
    DrawCrossing(450, 180, 0, 1, 1, 0); //��ݿ����· ��԰��� 14
    DrawCrossing(530, 340, 1, 1, 1, 1); //����· ʮ��·�� 14
    DrawCrossing(530, 240, 0, 1, 1, 1); //����· ��԰��� 14
    DrawCrossing(340, 340, 1, 1, 0, 1); //����· ���Ŷ�ͼ 14
}

/****************************************
FUNCTION:DrawParallelRoad
DESCRIBETION:���ƺ����·
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
DESCRIBETION:���������·
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
DESCRIBETION:��������ʮ��·��
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
DESCRIBETION:���ƽ�����
INPUT:void
RETURN:void
****************************************/
void DrawBuilding()
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 110, 200, 230);  //��ݿ    0
    floodfill(105, 170, DARKGRAY);
    puthz(57, 160, "��ݿ", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(220, 110, 335, 230);  //������    0
    floodfill(275, 170, DARKGRAY);
    puthz(240, 150, "������", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 245, 120, 355);  //����    0
    floodfill(65, 310, DARKGRAY);
    puthz(30, 290, "����", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(15, 370, 120, 460);  //��ʮ��    0
    floodfill(65, 430, DARKGRAY);
    puthz(30, 410, "��ʮ��", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(140, 245, 265, 310);  //�Ƽ�¥    0
    floodfill(200, 285, DARKGRAY);
    puthz(175, 260, "�Ƽ�¥", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(140, 340, 265, 460);  //��ͼ    0
    floodfill(195, 400, DARKGRAY);
    puthz(170, 380, "��ͼ", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(290, 245, 335, 460);  //ʦ��    0
    floodfill(315, 335, DARKGRAY);
    puthz(290, 335, "ʦ��", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 245, 515, 335);  //����    0
    floodfill(400, 290, DARKGRAY);
    puthz(400, 280, "����", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(535, 245, 625, 335);  //����    0
    floodfill(555, 280, DARKGRAY);
    puthz(555, 280, "����", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 355, 515, 460);  //����¥    0
    floodfill(400, 400, DARKGRAY);
    puthz(400, 400, "����¥", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(535, 355, 625, 460);  //��ͼ    0
    floodfill(555, 390, DARKGRAY);
    puthz(555, 390, "��ͼ", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 185, 435, 230);  //�Ͼ�    0
    floodfill(370, 200, DARKGRAY);
    puthz(370, 200, "�Ͼ�", 24, 25, WHITE);

    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(355, 110, 460, 175);  //��Է    0
    floodfill(400, 145, DARKGRAY);
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    rectangle(460, 110, 625, 230);  //��Է    0
    floodfill(535, 185, DARKGRAY);
    puthz(490, 145, "��Է", 24, 25, WHITE);
}

/****************************************
FUNCTION:DrawMap
DESCRIBETION:���Ƶ�ͼ
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