/**
**************************************************?
*   �汾�ţ�1.0
*   ���ߣ�X
*   �������ڣ�2024��3��28
*   ˵����Navigation�ຯ��ʵ�ֵ�������
**************************************************?
**/

#include"init.h"
#include"map.h"
#include"navigat.h"
#include "page.h"
#include "display.h"

/****************************************
FUNCTION:OpenNavigation
DESCRIBETION:�򿪵���ҳ
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
DESCRIBETION:���Ƶ���ҳ������ť
INPUT:void
RETURN:void
****************************************/
void DrawNavigationTopButton(int* mode)
{
	int s, e;
    if (mode[0] == 1)s = 13;
    if (mode[1] == 1)e = 13;
    puthz(210+20, 70, "�յ�", 24, 25, LIGHTBLUE);
    puthz(40+20, 70, "���", 24, 25, LIGHTBLUE);
    setfillstyle(1, RED);
    setcolor(RED);
    fillellipse(210, 92 - 10, 8, 8);
    setfillstyle(1, GREEN);
    setcolor(GREEN);
    fillellipse(40, 92 - 10, 8, 8);
	bar(350 + 20, 82 - 14, 440, 82 + 14);
    puthz(360 + 20, 70, "��ѡ", 24, 25, WHITE);
    bar(460, 82 - 14, 530, 82 + 14);
    puthz(470, 70, "�滮", 24, 25, WHITE);

   /* if (mode[0] == 0 && mode[1] == 0)
    {
        rectangle(550 , 82 - 14, 590, 82 + 14);
        puthz(560, 70, "����", 24, 25, WHITE);
    }*/

}

/****************************************
FUNCTION:NavigationMouse
DESCRIBETION:����ҳ���
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
        choice[0] = mouse_press(0, 0, 80, 50);//ֱ����ҳ��
        choice[6] = mouse_press(560, 0, 640, 50);//������һ��
        choice[1] = mouse_press(32, 70,160,94);
        choice[2] = mouse_press(202, 70, 330, 94);
        choice[3] = mouse_press(370, 70, 440, 94);
        choice[4] = mouse_press(460, 70, 530, 94);
        choice[5] = mouse_press(550, 70, 620, 94);

        if (choice[0] == 1)//ֱ����ҳ��
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[6] == 1)//������һ��
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
            puthz(3, 33, "Ԥ", 24, 0, BLUE);
            puthz(3, 63, "��", 24, 0, BLUE);
            puthz(3, 93, "��", 24, 0, BLUE);
            puthz(3, 123, "��", 24, 0, BLUE);
            outtextxy(0, 150, dist);
            puthz(3, 170, "��", 24, 0, BLUE);

            itoa(distance / 5, dist, 10);
            puthz(3, 233, "Ԥ", 24, 0, BLUE);
            puthz(3, 263, "��", 24, 0, BLUE);
            puthz(3, 293, "��", 24, 0, BLUE);
            puthz(3, 323, "ʱ", 24, 0, BLUE);
            outtextxy(0, 350, dist);
            puthz(3, 370, "��", 24, 0, BLUE);

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
DESCRIBETION:ѡ��ص�
INPUT:void
RETURN:int
****************************************/
int ChoosePlace()
{
    int place[14] = { 0 }, i = 0;
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        place[0] = mouse_press(15, 115, 185, 240);        //��ݿ
        place[1] = mouse_press(210, 115, 330, 235);       //������
        place[2] = mouse_press(140, 250, 250, 300);        //�Ƽ�¥
        place[3] = mouse_press(20, 255, 110, 345);       //����
        place[4] = mouse_press(25, 340, 110, 450);        //��ʮ��
        place[5] = mouse_press(155, 360, 255, 450);       //��ͼ
        place[6] = mouse_press(295, 255, 330, 450);        //ʦ��
        place[7] = mouse_press(360, 190, 430, 225);       //�Ͼ�
        place[8] = mouse_press(360, 115, 460, 170) + mouse_press(455, 120, 620, 220);        //��Է
        place[9] = mouse_press(360, 255, 510, 330);       //����
        place[10] = mouse_press(540, 250, 620, 330);        //����
        place[11] = mouse_press(360, 365, 510, 455);       //����¥
        place[12] = mouse_press(540, 360, 620, 455);       //��ͼ


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