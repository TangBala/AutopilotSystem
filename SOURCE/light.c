/* light.c */
#include "init.h"
#include "light.h"
#include "page.h"

// ȫ�ֱ���
LightBrightness light_brightness = {
    {0},
    -1 // ��ʼδѡ���κεƹ�
};
int num[8] = { 0 }; // �ƹ⿪��״̬

/****************************************
- �������ȵ�������Ϊ��ǰѡ�еĵƹ⣩
****************************************/
void DrawBrightnessBar(int x, int y, int level) 
{
    int i = 1;
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + 100, y + 20);

    setcolor(DARKGRAY);
    rectangle(x, y, x + 100, y + 20);

    //// ���Ʒֶ���
    //for (; i < 4; i++) {
    //    line(x + i * 25, y, x + i * 25, y + 20);
    //}
    if (level <0)
		level = 0;
    // ��䵱ǰ����
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(x + 1, y + 1, x + level * 25, y + 19);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x + level * 25-10, y-1 , x + level * 25+10, y + 21);
}

/****************************************
- �����溯��
****************************************/
void OpenLight() 
{
    LightMode current_mode = EXTERNAL_LIGHTS;
    // ��ȡ״̬
    FILE* fp = fopen("light.dat", "rb");
    if (fp) {
        fread(num, sizeof(num), 1, fp);
        fread(&light_brightness, sizeof(light_brightness), 1, fp);
        fclose(fp);
    }

    while (1) {
        int ischange;
        int i = 0;
        ClearGraph();
        // ���ƽ���
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawLightSButton(current_mode);
        DrawLightChangePart(num, current_mode);
        PutLightHz(current_mode);

        // ��������������
        for (; i < 4; i++) 
        {
            int light_idx = (current_mode == EXTERNAL_LIGHTS) ? i : i + 4;
            DrawBrightnessBar(390, 160 + i * 80, light_brightness.level[light_idx]);
        }

        // ��������
        if (LightMouse(&current_mode, &ischange) == 0) {
            fp = fopen("light.dat", "wb");
            if (fp) {
                fwrite(num, sizeof(num), 1, fp);
                fwrite(&light_brightness, sizeof(light_brightness), 1, fp);
                fclose(fp);
            }
            return;
        }

        delay(30);
    }
}

/****************************************
- �޸ĺ��LightMouse����
****************************************/
int LightMouse(LightMode* mode, int* ischange) 
{
    int choice[4] = { 0 };
    *ischange = 0;
    while (1) {
        int i = 0;
        newmouse(&MouseX, &MouseY, &press);

        // ģʽѡ��
        choice[0] = mouse_press(100, 80, 250, 130); // �ⲿ�ƹ�
        choice[1] = mouse_press(350, 80, 500, 130); // �ڲ��ƹ�
        choice[2] = mouse_press(0, 0, 80, 50);//ֱ����ҳ��
        choice[3] = mouse_press(560, 0, 640, 50);//������һ��
        if (choice[0]==1) {
            *mode = EXTERNAL_LIGHTS;
            break;
        }
         else if (choice[1]==1) {
            *mode = INTERNAL_LIGHTS;
            break;
        }
        else if (choice[2] == 1)//ֱ����ҳ��
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[3] == 1)//������һ��
        {
            return 0;
        }
        // �������������
        for (; i < 4; i++) 
        {
            int light_idx = (*mode == EXTERNAL_LIGHTS) ? i : i + 4;
            int y_pos = 160 + i * 80;
            int lvl = 0;
            for (; lvl < 5; lvl++) {
                if (mouse_press(390 + lvl * 25-12, y_pos, 390 + (lvl) * 25+12, y_pos + 20)==1) 
                {
                    light_brightness.level[light_idx] = lvl;
                    if (light_brightness.level[light_idx])
                    {
                        num[light_idx] = 1; // �Զ�����
                    }
                    else
					{
						num[light_idx] = 0; // �Զ��ر�
					}
                    *ischange = 1;
                    delay(200);
                }         
            }
        }

        if (*ischange) break;
    }

    return 1;
}

/****************************************
FUNCTION:DrawLightSButton
DESCRIBETION:���Ƶƹ�ҳ��ť(����ģʽ��ʾ��ͬ��ť)
INPUT:LightMode mode - ��ǰ�ƹ�ģʽ
REUTRUN:void
****************************************/
void DrawLightSButton(LightMode mode)
{
    int point1[24] = { 110,80, 86,100, 86,145, 106,145, 110,135, 221,135, 221,145, 241,145, 261,125, 261,95, 270,80, 110,80 };
    int point2[24] = {360,80, 336,100,  336,145,  356,145, 360,135,  471,135,  471,145,  491,145, 511,125,  511,95,   520,80,   360,80 };
    Draw(LIGHTBLUE);
    // ģʽѡ��ť
    setcolor(LIGHTBLUE);
    drawpoly(12, point1); // �ⲿ�ƹⰴť
	drawpoly(12, point2);// �ڲ��ƹⰴť
    // ������ǰģʽ
    if (mode == EXTERNAL_LIGHTS)
    {
        setcolor(YELLOW);
        drawpoly(12, point1); // �ⲿ�ƹⰴť
    }
    else {
        setcolor(YELLOW);
        drawpoly(12, point2);// �ڲ��ƹⰴť
    }

    setcolor(LIGHTBLUE);
    puthz(120, 100, "�ⲿ�ƹ�", 24, 26, WHITE);
    puthz(370, 100, "�ڲ��ƹ�", 24, 26, WHITE);

    // ���ݵ�ǰģʽ���Ʋ�ͬ��ť
    if (mode == EXTERNAL_LIGHTS)
    {
        // �ⲿ�ƹ���ư�ť
        rectangle(150, 150, 250, 200);   // ǰ���
        rectangle(150, 150 + 80, 250, 200 + 80);  // ���
        rectangle(150, 150 + 2 * 80, 250, 200 + 2 * 80);  // β��
        rectangle(150, 150 + 3 * 80, 250, 200 + 3 * 80);  // ת���

        puthz(160, 170, "ǰ���", 24, 26, LIGHTBLUE);
        puthz(172, 170+80, "���", 24, 26, LIGHTBLUE);
        puthz(172, 170+2*80, "β��", 24, 26, LIGHTBLUE);
        puthz(160, 170+3*80, "ת���", 24, 26, LIGHTBLUE);
    }
    else {
        // �ڲ��ƹ���ư�ť
        rectangle(150, 150, 250, 200);  // ����
        rectangle(150, 150+80, 250, 200+80);  // �Ǳ��
        rectangle(150, 150+2*80, 250, 200+2*80);  // �ŵ�
        rectangle(150, 150+3*80, 250, 200+3*80);  // ��Χ��

        puthz(172, 170, "����", 24, 26, LIGHTBLUE);
        puthz(160, 170+80, "�Ǳ��", 24, 26, LIGHTBLUE);
        puthz(172, 170+2*80, "�ŵ�", 24, 26, LIGHTBLUE);
        puthz(160, 170+3*80, "��Χ��", 24, 26, LIGHTBLUE);
    }
}

/****************************************
FUNCTION:DrawLightChangePart
DESCRIBETION:���Ƶƹ�ҳ�Ŀɱ䲿��(����ģʽ������ͬ��ť)
INPUT:int* num - �ƹ�״̬����
      LightMode mode - ��ǰ�ƹ�ģʽ
RETURN:void
****************************************/
void DrawLightChangePart(int* num, LightMode mode)
{
    if (mode == EXTERNAL_LIGHTS)
    {
        // �����ⲿ�ƹⰴť
        if (num[0])
        {  // ǰ���
            setfillstyle(1, GREEN);
            bar(151, 151, 249, 199);
            puthz(160, 170, "ǰ���", 24, 26, LIGHTBLUE);
        }
        if (num[1])
        {  // ���
            setfillstyle(1, GREEN);
            bar(151, 151+80, 249, 199+80);
            puthz(172, 170+80, "���", 24, 26, LIGHTBLUE);
        }
        if (num[2])
        {  // β��
            setfillstyle(1, GREEN);
            bar(151, 151+160, 249, 199+160);
            puthz(172, 170+160, "β��", 24, 26, LIGHTBLUE);
        }
        if (num[3])
        {  // ת���
            setfillstyle(1, GREEN);
            bar(151, 151+240, 249, 199+240);
            puthz(160, 170+240, "ת���", 24, 26, LIGHTBLUE);
        }
    }
    else
    {
        // �����ڲ��ƹⰴť
        if (num[4])
        {  // ����
            setfillstyle(1, GREEN);
            bar(151, 151, 249, 199);
            puthz(172, 170, "����", 24, 26, LIGHTBLUE);
        }
        if (num[5])
        {  // �Ǳ��
            setfillstyle(1, GREEN);
            bar(151, 151+80, 249, 199+80);
            puthz(160, 170+80, "�Ǳ��", 24, 26, LIGHTBLUE);
        }
        if (num[6])
        {  // �ŵ�
            setfillstyle(1, GREEN);
            bar(151, 151+160, 249, 199+160);
            puthz(172, 170+160, "�ŵ�", 24, 26, LIGHTBLUE);
        }
        if (num[7])
        {  // ��Χ��
            setfillstyle(1, GREEN);
            bar(151, 151+240, 249, 199+240);
            puthz(160, 170+240, "��Χ��", 24, 26, LIGHTBLUE);
        }
    }
}

/****************************************
FUNCTION:PutLightHz
DESCRIBETION:��ʾ�ƹ�ҳ����(����ģʽ��ʾ��ͬ����)
INPUT:LightMode mode - ��ǰ�ƹ�ģʽ
RETURN:void
****************************************/
void PutLightHz(LightMode mode)
{
    if (mode == EXTERNAL_LIGHTS)
    {
        puthz(175, 20, "�ⲿ�ƹ����", 32, 54, LIGHTBLUE);
    }
    else {
        puthz(175, 20, "�ڲ��ƹ����", 32, 54, LIGHTBLUE);
    }
}
