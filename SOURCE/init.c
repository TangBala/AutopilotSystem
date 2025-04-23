/**
**************************************************
*   �汾�ţ�1.0
*   ���ߣ�X
*   �������ڣ�2024��4��15
*   ˵����Init�ຯ��������ʼ�����˳������صȻ�������
**************************************************
**/

#include<graphics.h>
#include"init.h"
DriveMode current_mode = MODE_C;
int mode = 3;
/****************************************
FUNCTION:ClearGraph
DESCRIBETION:�����Ļ����ָ����ɫ��䣬���³�ʼ�����
INPUT:color
RETURN:void
****************************************/
void ClearGraph(void)
{
    mouseinit();
    setfillstyle(1,BLACK);
    bar(0, 0, 640, 480);
}

/****************************************
FUNCTION:DrawReturnButton
DESCRIBETION:�����˳���ť
INPUT:void
RETURN:void
****************************************/
void DrawReturnButton()
{
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    rectangle(0,0,29,29);
    line(5,15,25,15);
    line(5,15,15,5);
    line(5,15,15,25);
}

/***********************
FUNCTION:Draw
DESCRIBETION:��������
INPUT:void
REUTRUN:void
***********************/
void Draw(int color)
{
	
	setbkcolor(BLACK);
	setcolor(color);
	setlinestyle(0,0,1);
	setviewport(0,0,639,479,0);//set
}

void drawBezierCurve(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int color) 
{
    int prevX = x0, prevY = y0;
	float t = 0.0;
    for (; t <= 1.0; t += 0.01) 
    {  // ����ԽС������Խƽ��
        float u = 1.0 - t;
        float x = u * u * u * x0 + 3 * u * u * t * x1 + 3 * u * t * t * x2 + t * t * t * x3;
        float y = u * u * u * y0 + 3 * u * u * t * y1 + 3 * u * t * t * y2 + t * t * t * y3;

        line(prevX, prevY, (int)x, (int)y);  // �������ڵ�
        prevX = (int)x;
        prevY = (int)y;
    }
}
