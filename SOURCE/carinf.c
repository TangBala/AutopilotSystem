/**
**************************************************?
*   �汾�ţ�1.0
*   ���ߣ�X
*   �������ڣ�2025-4-20
*   ˵����carinf��ĺ���ʵ�ֲ鿴������Ϣ����
**************************************************?
**/

#include"init.h"
#include"carinf.h"
#include"page.h"
#include"drive.h"
#include"battery.h"
#include"mouse.h"
#include"d_mode.h"
#include"secusys.h"





/****************************************
FUNCTION:OpenCarinf
DESCRIBETION:�򿪲˵�ҳ
INPUT:void
RETURN:void
****************************************/
void OpenCarinf()
{
    //mouse_press(250, 160, 390, 300);
    while (1)
    {
        int carinf_ret = 1;
        //���ƽ���
        ClearGraph();
        DrawDriMode();
        DrawStatus();
        DrawSecuSys();
        //DrawCarinfBackButton();
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        //delay(1000);

        //newmouse(&MouseX, &MouseY, &press);

        carinf_ret = CarinfMouse();

        if (!carinf_ret)
            return;

    }
    

}
/****************************************
FUNCTION:DrawDriMode
DESCRIBETION:���Ƽ�ʻģʽ��ť
INPUT:void
RETURN:void
****************************************/
void DrawDriMode()
{
    setlinestyle(0, 0, 1);
    setcolor(LIGHTGRAY);
    setfillstyle(1, LIGHTGRAY);
    fillellipse(124, 230, 80, 80);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    fillellipse(124, 230, 75, 75);
    setcolor(WHITE);
    setfillstyle(1, WHITE);
    fillellipse(124, 230, 65, 65);
    setcolor(DARKGRAY);
    setfillstyle(1, DARKGRAY);
    ellipse(99, 225, 90, 210, 18, 18);
    ellipse(149, 225, -30, 90, 18, 18);
    ellipse(124, 260, 210, 330, 18, 18);
    line(99, 207, 149, 207);
    line(81, 225, 59, 225);
    line(167, 225, 189, 225);
    line(84, 236, 57, 236);
    line(164, 236, 190, 236);
    line(118, 277, 118, 295);
    line(130, 277, 130, 295);
    line(84, 234, 108, 269);
    line(164, 234, 140, 269);
    floodfill(122, 233, DARKGRAY);
    floodfill(68, 230, DARKGRAY);
    floodfill(173, 230, DARKGRAY);
    floodfill(124, 282, DARKGRAY);

    puthz(65, 350, "��ʻģʽ", 24, 26, LIGHTBLUE);
}

/****************************************
FUNCTION:DrawStatus
DESCRIBETION:���Ƽ�ʻ״̬��ť
INPUT:void
RETURN:void
****************************************/
void DrawStatus()
{
    

    setcolor(DARKGRAY);
    setfillstyle(1, LIGHTGRAY);
    fillellipse(320, 230, 80, 80);
    setfillstyle(1, DARKGRAY);
    fillellipse(320, 230, 75, 75);
    setfillstyle(1, LIGHTGRAY);
    fillellipse(320, 230, 73, 73);
    fillellipse(320, 230, 67, 67);
    fillellipse(320, 230, 60, 60);

    setcolor(WHITE);
    setfillstyle(1, WHITE);
    ellipse(320, 213, 120, 420, 17, 17);
    ellipse(320, 213, 110, 430, 27, 27);
    bar(315, 178, 325, 208);
    line(311, 187, 311, 198);
    line(329, 187, 329, 198);
    floodfill(320, 235, WHITE);
    settextstyle(3, 0, 2);
    outtextxy(290, 242, "Driving");
    outtextxy(293, 260, "Status");
    puthz(268, 350, "��ʻ״̬", 24, 26, LIGHTBLUE);

}

/****************************************
FUNCTION:DrawSecuSys
DESCRIBETION:���ư�ȫϵͳ״̬��ť
INPUT:void
RETURN:void
****************************************/
void DrawSecuSys ()
{
    int x0 = 444, y0 = 193;  // ���
    int x1 = 550, y1 = 105;  // ���Ƶ�1��Ӱ�����ʣ�
    int x2 = 564, y2 = 253;  // ���Ƶ�2
    int x3 = 587, y3 = 193;  // �յ�
    int x4 = 588, y4 = 267;  // ���
    int x5 = 482, y5 = 355;  // ���Ƶ�1��Ӱ�����ʣ�
    int x6 = 468, y6 = 207;  // ���Ƶ�2
    int x7 = 445, y7 = 267;  // �յ�
    setcolor(YELLOW);
    setlinestyle(0, 0, 1);
    setfillstyle(1, YELLOW);
    fillellipse(516, 230, 80, 80);
    setcolor(GREEN);
    setfillstyle(1, GREEN);
    ellipse(516, 230, 25,155,80, 80);
    ellipse(516, 230, 205, 335, 80, 80);
    drawBezierCurve(x0, y0, x1, y1, x2, y2, x3, y3, GREEN);
	drawBezierCurve(x4, y4, x5, y5, x6, y6, x7, y7, GREEN);
    floodfill(560, 188, GREEN);
    bar(508, 198, 524, 262);
    bar(484, 222, 548, 238);

   floodfill(466, 271, GREEN);

   
    puthz(440,350,"��ȫϵͳ״̬",24,26,LIGHTBLUE);
}




/***************************************
FUNCTION:CarinfMouse
DESCRIBETION:������Ϣҳ���
INPUT:void
RETURN:int
***************************************/
int CarinfMouse()
{
    int choice[5] = {0};
    //mouse_press(250, 160, 390, 300);

    while(1)
    {
        //�������ͳ�����Ϣ��ť
        //clrmous(MouseX, MouseY);//������
           
        //mouseinit();
        newmouse(&MouseX, &MouseY, &press);
        choice[0] = mouse_press(40, 15, 100, 50);//ֱ����ҳ
        choice[1] = mouse_press(54, 160, 194, 300);//��ʻģʽ
        choice[2] = mouse_press(250, 260, 390, 300);//��ʻ״̬
		choice[3] = mouse_press(446, 160, 586, 300);//��ȫϵͳ״̬
        choice[4] = mouse_press(435, 15, 615, 45);//������һ��

        //�ж�ѡ��
        if(choice[1] == 1)//��ʻģʽ
        {
            ClearGraph();
            OpenDrivemode();
            break;
        }
        else if(choice[2] == 1)//��ʻ״̬
        {
            ClearGraph();
            OpenDriveStatus();
            break;
        }
        else if(choice[3] == 1)//��ȫϵͳ״̬
        {
            ClearGraph();
            OpenSystem();
            break;
        }
		else if (choice[4] == 1)//������һ��
		{
            return 0;
		}
		else if (choice[0] == 1)//ֱ����ҳ
		{
			return 0;
		}
       
    }
    return 1;
}