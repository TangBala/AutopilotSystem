/**
**************************************************?
*	�汾�ţ�1.0
*	���ߣ�Y
*	�������ڣ�2024��3��15
*	˵����Door�ຯ��ʵ�ֳ��Ź���
**************************************************?
**/

#include"init.h"
#include"display.h"
#include"door.h"
#include "page.h"

/****************************************
FUNCTION:OpenDoor
DESCRIBETION:�򿪲˵��г���ҳ
INPUT:void
REUTRUN:void
****************************************/
void OpenDoor()
{
	while(1)
    {
        int door_ret = 1, num[9], i = 0;
        FILE* door_text;

	    setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);

		door_text = fopen("..\\CODE\\text\\door.txt", "rt");
        for(i = 0; i < 9; i++)
        {
            fscanf(door_text, "%d ", &num[i]);
        }
        fclose(door_text);
		DrawTopMid(0);
		DrawHomeRet();
		DrawToHome();
		DrawDoorSButton();
		DrawDoorChangePart(num);
		door_ret = DoorMouse(num);

        door_text = fopen("..\\CODE\\text\\door.txt", "wt");
        for(i = 0; i < 9; i++)
        {
            fprintf(door_text, "%d ", num[i]);
        }
        fclose(door_text);
        if(!door_ret)
            return ;
    }
}

/****************************************
FUNCTION:DrawDoorSButton
DESCRIBETION:���Ʋ˵��г������а�ť
INPUT:void
REUTRUN:void
****************************************/
void DrawDoorSButton()
{
	Draw(LIGHTBLUE);	
	puthz(248,30,"���ſ���",32,36,LIGHTBLUE);
	line(140,174,180,174);
	line(140,204,180,204);
	ellipse(140,189,90,270,15,15);
	ellipse(180,189,-90,90,15,15);
	puthz(130, 180, "һ������", 16, 15, LIGHTBLUE);
	circle(388, 216, 10);
	circle(388, 290, 10);
	circle(570, 216, 10);
	circle(570, 290, 10);
	
	DrawCar(480,240,0.45);
}

/****************************************
FUNCTION:DrawDoorChangePart
DESCRIBETION:���Ƴ���ҳ�Ŀɱ䲿��
INPUT:int* num
RETURN:void
****************************************/
void DrawDoorChangePart(int* num)
{
	int i;
	if(num[0] == 0)
    {
		setcolor(LIGHTBLUE);
		line(386, 216, 389, 212);
		line(386, 216, 389, 220);
    }
	if (num[0] == 1)
	{
		setcolor(LIGHTBLUE);
		line(390, 216, 387, 212);
		line(390, 216, 387, 220);
		setcolor(RED);
		setlinestyle(0, 0, 3);
		line(415, 191, 415, 204);
		line(415, 212, 415, 263);

	}
	if (num[1] == 1)
	{
		setcolor(LIGHTBLUE);
		line(568, 216, 571, 212);
		line(568, 216, 571, 220);
		setcolor(RED);
		setlinestyle(0, 0, 3);
		line(545, 191, 545, 204);
		line(545, 212, 545, 263);
	}
	if (num[1] == 0)
	{
		setcolor(LIGHTBLUE);
		line(572, 216, 569, 212);
		line(572, 216, 569, 220);
	}
	if (num[2] == 0)
	{
		setcolor(LIGHTBLUE);
		line(386, 290, 389, 286);
		line(386, 290, 389, 294);
	}
	if (num[2] == 1)
	{
		setcolor(LIGHTBLUE);
		line(390, 290, 387, 286);
		line(390, 290, 387, 294);
		setcolor(RED);
		setlinestyle(0, 0, 3);
		line(415, 265, 416, 335);
	}
	if (num[3] == 1)
	{
		setcolor(LIGHTBLUE);
		line(568, 290, 571, 286);
		line(568, 290, 571, 294);
		setcolor(RED);
		setlinestyle(0, 0, 3);
		line(545, 265, 544, 335);
	}
	if (num[3] == 0)
	{
		setcolor(LIGHTBLUE);
		line(572, 290, 569, 286);
		line(572, 290, 569, 294);
	}
	if (num[0] == 1 || num[1] == 1 || num[2] == 1 || num[3] == 1)
	{
		setcolor(RED);
		settextstyle(3, 0, 3);
		outtextxy(135, 295, ":");
		puthz(80, 300, "����", 24, 26, RED);
		puthz(80, 335, "����δ�ر�", 24, 26, RED);
	}
}

/****************************************
FUNCTION:DoorMouse
DESCRIBETION:����ҳ���
INPUT:int* num
REUTRUN:int
****************************************/
int DoorMouse(int* num)
{
	int choice[6]={0};
	while(1)
    {
        //�����������ð�ť
        newmouse(&MouseX, &MouseY, &press);
		choice[1]=mouse_press(378,206,398,226);//��ǰ
		choice[2] = mouse_press(560, 206, 580, 226);//��ǰ
		choice[3]=mouse_press(378, 280, 398, 300);//���
		choice[4] = mouse_press(560, 280, 580, 300);//�Һ�
		choice[5]=mouse_press(125,174,195,204);//
		
		choice[0] = mouse_press(0, 0, 80, 50);//ֱ����ҳ��
		choice[6] = mouse_press(560, 0, 640, 50);//������һ��

		//�ж�ѡ��
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
		else if(choice[1] == 1)
		{
            num[0]^=1;
			delay(300);
			break;
		}
		else if(choice[2] == 1)
		{
		    num[1]^=1;
			delay(300);
			break;
		}
		else if(choice[3] == 1)
		{
			num[2]^=1;
			delay(300);
			break;
		}
		else if(choice[4] == 1)
		{
			num[3]^=1;
			delay(300);
			break;
		}
		else if(choice[5] == 1)
		{
			num[0] = 0, num[1] = 0, num[2] = 0, num[3] = 0;
            break;
		}
		
    }
	delay(100);
	return 1;
}