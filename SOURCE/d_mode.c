/**************************************************
-�汾�ţ�1.0
- ���ߣ�Y
- �������ڣ�2024��3��17
- ˵����Battery�ຯ��ʵ�ֵ�ع���
* *************************************************
**/

#include"init.h"
#include"d_mode.h"
#include"page.h"

#define MODE_FILE "..\\CODE\\text\\d_mode.txt"

// ģʽö�٣���ȷָ����Ӧ������ֵ

// ��ǰģʽ��Ĭ��C��
static DriveMode current_mode;

/****************************************
FUNCTION:OpenBattery
DESCRIBETIO N:�򿪲˵��е��ҳ
INPUT:void
REUTRUN:void
****************************************/
void OpenDrivemode()
{
    // ��ȡ�����ģʽ
    FILE* fp = fopen(MODE_FILE, "rt");
    if (fp)
    {
        int saved_mode;
        if (fscanf(fp, "%d", &saved_mode) == 1)
        {
            // ȷ����ȡ��ֵ��Ч
            if (saved_mode >= MODE_A && saved_mode <= MODE_C)
            {
                current_mode = (DriveMode)saved_mode;
            }
        }
        fclose(fp);
    }

    while (1)
    {
        int mode_ret=1;

        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawModeButton(current_mode);
        mode_ret = ModeMouse(&current_mode);

        // д���ļ���ÿ��ѭ�������Ա��棩
        fp = fopen(MODE_FILE, "w");
        if (fp == NULL)
        {
            perror("Failed to write mode file"); // ��ӡ������Ϣ
        }
        else
        {
            fprintf(fp, "%d", (int)current_mode); // ��ʽת��Ϊ int
            fflush(fp); // ǿ��ˢ�»�����
            fclose(fp);
        }

        if (!mode_ret)
            return;
    }
}

/****************************************
FUNCTION:DrawModeButton
DESCRIBETION:���Ʋ˵��е�����а�ť
INPUT:int
REUTRUN:void
****************************************/

void DrawModeButton(int current_mode)
{
    // ������ʾ��ǰģʽ
    char* mode_text[] = { "�ֶ�ģʽ", "����ģʽ", "�Զ�ģʽ" };
    puthz(280, 20, mode_text[current_mode], 24, 26, LIGHTBLUE);
    DrawMid(30, 130);
    DrawMid(245 - 23, 130);
    DrawMid(436 - 23, 130);

    // ��������ѡ��ť
    setcolor(LIGHTBLUE);

    // ��ťA����������ʾ����
    puthz(50 + 10, 155, "�ֶ�ģʽ", 24, 27, LIGHTBLUE);
    puthz(245 - 23 + 10 + 20, 155, "����ģʽ", 24, 27, LIGHTBLUE);
    puthz(436 - 23 + 20 + 10, 155, "�Զ�ģʽ", 24, 27, LIGHTBLUE);
    fillellipse(35, 250 + 8, 5, 5);
    fillellipse(35, 310 + 8, 5, 5);
    fillellipse(35, 370 + 8, 5, 5);
    /* fillellipse(242-15, 250 + 8, 5, 5);
     fillellipse(242-15, 310 + 8, 5, 5);
     fillellipse(242-15, 370 + 8, 5, 5);
     fillellipse(433 - 15, 250 + 8, 5, 5);
     fillellipse(433 - 15, 340 + 8, 5, 5);*/

    puthz(50, 250, "��ʻԱ��ȫ���Ƴ�", 16, 18, LIGHTBLUE);
    puthz(50, 280, "��", 16, 18, LIGHTBLUE);
    puthz(50, 310, "ϵͳ���ṩ����", 16, 18, LIGHTBLUE);
    puthz(50, 340, "�Ǳ���ʾ", 16, 18, LIGHTBLUE);
    puthz(50, 370, "�ʺϸ���·����", 16, 18, LIGHTBLUE);
    puthz(50, 400, "׷��ٿ�����ʱ", 16, 18, LIGHTBLUE);
    puthz(50, 430, "ʹ��", 16, 18, LIGHTBLUE);

    puthz(242, 250, "ϵͳ�Զ����Ƽ�", 16, 18, LIGHTBLUE);
    puthz(242, 280, "���ٺͷ���", 16, 18, LIGHTBLUE);
    puthz(242, 310, "��ʻԱ�豣����", 16, 18, LIGHTBLUE);
    puthz(242, 340, "��������", 16, 18, LIGHTBLUE);
    puthz(242, 370, "�����ڸ���Ѳ��", 16, 18, LIGHTBLUE);
    puthz(242, 400, "�ȱ�׼������", 16, 18, LIGHTBLUE);

    puthz(433, 250, "�������������", 16, 18, LIGHTBLUE);
    puthz(433, 280, "�м�ʻ����", 16, 18, LIGHTBLUE);
    puthz(433, 310, "�˿������Ԥ", 16, 18, LIGHTBLUE);
    puthz(433, 340, "���ڷ�յ�·��", 16, 18, LIGHTBLUE);
    puthz(433, 370, "��������������", 16, 18, LIGHTBLUE);
    puthz(433, 400, "�á�", 16, 18, LIGHTBLUE);
}



/****************************************
FUNCTION:ModeMouse
DESCRIBETION:���ҳ����깦��
INPUT:int* num
REUTRUN:int
****************************************/
int ModeMouse(int* current_mode)
{
    int choice[5] = { 0 };

    while (1)
    {
        //�����������ð�ť
        newmouse(&MouseX, &MouseY, &press);

        choice[1] = mouse_press(50, 135, 214, 210);
        choice[2] = mouse_press(240, 135, 400, 210);
        choice[3] = mouse_press(420, 135, 600, 210);
        choice[0] = mouse_press(0, 0, 80, 50);//ֱ����ҳ��
        choice[4] = mouse_press(560, 0, 640, 50);//������һ��
        //�ж�ѡ��
        if (choice[0] == 1)//ֱ����ҳ��
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[1] == 1)
        {
            *current_mode = MODE_A;
            break;
        }
        else if (choice[2] == 1)
        {
            *current_mode = MODE_B;
            break;
        }
        else if (choice[3] == 1)
        {
            *current_mode = MODE_C;
            break;
        }
        else if (choice[4] == 1)//������һ��
        {
            return 0;
        }
    }
    delay(100);
    return 1;
}