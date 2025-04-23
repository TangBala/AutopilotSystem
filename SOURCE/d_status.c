/**
**************************************************
*        �汾�ţ�1.2
*        ���ߣ�ZYY
*        �������ڣ�2025
*        ˵����d_status����ʵ�ּ�ʻ״̬��ʾ
*        ���£����ӻ��γ��ٽ�������ʾ
**************************************************
**/

#include "init.h"
#include "d_status.h"
#include "page.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define DSTATUS_FILE "..\\CODE\\text\\d_status.txt"
#define MAX_SPEED 40  // �����40km/h

// ��ʻ״̬ö��
typedef enum
{
    ENGINE_STATUS,
    SPEED_STATUS,
    WARNING_MSG
} DriveStatus;

// ��ʻ״̬����
typedef struct
{
    int engine_on;       // ���������� (0=�ر�, 1=����)
    int speed;          // ���� (km/h)
    char warning_msg[50]; // ������Ϣ
    char warning_tip[50]; // ������ʾ��
} DriveStatusData;

// ȫ�ֱ���
static DriveStatus current_view;
static DriveStatusData drive_data;
static int has_warning = 0;

/****************************************
FUNCTION:InitDriveStatus
DESCRIBETION:��ʼ����ʻ״̬����
INPUT:void
REUTRUN:void
****************************************/
void InitDriveStatus()
{
    const char* tips[] = {
        "",
        "����ٲ�ͣ����ȴ������",
        "��������ӻ���",
        "������ϵͳ",
        "����������ɲ��",
        "���������ȫ����"
    };

    const char* warnings[] =
    {
        "�޾���",
        "�������¶ȹ���",
        "��ѹ����",
        "��ص�ѹ�쳣",
        "ɲ��ϵͳ����",
        "���ٹ���"
    };
    int warning_idx = 0; // Ĭ��Ϊ�޾���
    srand(time(NULL));

    // ���ݳ���״̬ȷ��������Ϣ

    // ���ٹ��߾��� (����35km/h)
    if (drive_data.speed > 35) {
        warning_idx = 5; // "���ٹ���"
    }
    // ����������ʱ���ܳ��ֵľ���
    else if (drive_data.engine_on) {
        // �������һ���뷢����״̬��صľ���(1-4)
        warning_idx = 1 + (rand() % 4);

        // ����Ѿ��о����Ҳ��ǳ��ٹ��ߣ�����ԭ����(����Ƶ���л�)
        if (has_warning && strcmp(drive_data.warning_msg, "���ٹ���") != 0) {
            // ����ԭ����
            return;
        }
    }
    // ���þ�����Ϣ
    strcpy(drive_data.warning_msg, warnings[warning_idx]);
    strcpy(drive_data.warning_tip, tips[warning_idx]);
    has_warning = (warning_idx != 0);
}

/****************************************
FUNCTION:ToggleEngine
DESCRIBETION:�����л�����
INPUT:void
REUTRUN:void
****************************************/

void ToggleEngine()
{
    drive_data.engine_on = !drive_data.engine_on;
    if (!drive_data.engine_on)
    {
        drive_data.speed = 0; // �رշ�����ʱ���ٹ���
    }
    else
    {
        FILE* fp = fopen(DSTATUS_FILE, "rt");
        if (fp)
        {
            fscanf(fp, "%d ", &drive_data.speed);
            fclose(fp);
            // ȷ��������0-MAX_SPEED��Χ��
            if (drive_data.speed < 0) drive_data.speed = 0;
            if (drive_data.speed > MAX_SPEED) drive_data.speed = MAX_SPEED;

            // ����������ʱ���¼�龯��״̬
            InitDriveStatus();
        }
        else
        {
            drive_data.speed = 0; // �ļ���ȡʧ��ʱ��Ϊ0
        }
    }
}


/****************************************
FUNCTION:GetEngineStatus
DESCRIBETION:��ȡ��ǰ������״̬�ı�
INPUT:void
REUTRUN:char* ״̬�ı�
****************************************/
char* GetEngineStatus()
{
    if (!drive_data.engine_on) return "�ѹر�";
    return (drive_data.speed < 10) ? "����" : "������";
}



/****************************************
FUNCTION:OpenDriveStatus
DESCRIBETION:�򿪼�ʻ״̬ҳ��
INPUT:void
REUTRUN:void
****************************************/

void OpenDriveStatus()
{

    while (1)
    {
        // ���浱ǰ״̬���ļ�
        FILE* fp = fopen(DSTATUS_FILE, "wt");
        FILE* fp_write = fopen(DSTATUS_FILE, "wt");
        int status_ret;
        if (fp)
        {
            // ��ȡ��ǰ����״̬����
            int warning_idx = 0;
            if (strcmp(drive_data.warning_msg, "�������¶ȹ���") == 0) warning_idx = 1;
            else if (strcmp(drive_data.warning_msg, "��ѹ����") == 0) warning_idx = 2;
            else if (strcmp(drive_data.warning_msg, "��ص�ѹ�쳣") == 0) warning_idx = 3;
            else if (strcmp(drive_data.warning_msg, "ɲ��ϵͳ����") == 0) warning_idx = 4;

            fprintf(fp, "%d %d %d %d",
                current_view,
                drive_data.engine_on,
                drive_data.speed,
                warning_idx);
            fclose(fp);
        }
        InitDriveStatus();  // ���ļ���ʼ��״̬
        // ���ƽ���
        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawDriveStatus();

        // �����û�����
        status_ret = DriveStatusMouse(&current_view);
        if (fp_write)
        {
            // ��ȡ��ǰ����״̬����
            int warning_idx = 0;
            if (strcmp(drive_data.warning_msg, "�������¶ȹ���") == 0) warning_idx = 1;
            else if (strcmp(drive_data.warning_msg, "��ѹ����") == 0) warning_idx = 2;
            else if (strcmp(drive_data.warning_msg, "��ص�ѹ�쳣") == 0) warning_idx = 3;
            else if (strcmp(drive_data.warning_msg, "ɲ��ϵͳ����") == 0) warning_idx = 4;

            fprintf(fp_write, "%d %d %d %d",
                current_view,
                drive_data.engine_on,
                drive_data.speed,
                warning_idx);
            fclose(fp_write);
        }
        if (!status_ret) return;
    }
}


/****************************************
FUNCTION:DrawSpeedGauge
DESCRIBETION:���Ƴ��ٻ��ν�����(����λ��)
INPUT:int speed - ��ǰ����(0-40)
REUTRUN:void
****************************************/
void DrawSpeedGauge(int speed)
{
    const int centerX = 160;  // ��������X���굽���
    const int centerY = 180;  // ����Y����
    const int innerRadius = 50;  // �ڰ뾶
    const int outerRadius = 70;  // ��뾶
    const float startAngle = -M_PI / 2;  // ��ʼ�Ƕ�(-90��)
    const float maxAngle = M_PI * 3 / 2;   // ���Ƕ�(270��)
    char speedStr[10];
    int i=0;
    float angleStep = M_PI / 100;  // �ǶȲ���
    int steps = (speed * 250) / MAX_SPEED;  // ���㲽��(0-250��Ӧ0-40km/h)

    // ���Ʊ���Բ��
    setcolor(LIGHTGRAY);
    circle(centerX, centerY, innerRadius);
    circle(centerX, centerY, outerRadius);

    // ���ƽ�����
    setcolor(GREEN);
    for (; i < steps; i++) 
    {
        float angle = startAngle + (maxAngle * i) / 250;
        line(centerX + innerRadius * cos(angle), centerY + innerRadius * sin(angle),
            centerX + outerRadius * cos(angle), centerY + outerRadius * sin(angle));
    }

    // �������복������
    sprintf(speedStr, "%d", speed);
    settextstyle(3, 0, 5);  
    setcolor(WHITE);
    outtextxy(centerX-textwidth(speedStr)/2+5, centerY-10-textheight(speedStr)/2, speedStr);

    // ���Ƶ�λ
    settextstyle(3, 0, 2);
    outtextxy(centerX - 25, centerY+10,"km/h");
}

/****************************************
FUNCTION:DrawDriveStatus
DESCRIBETION:���Ƽ�ʻ״̬��Ϣ(���²���)
INPUT:void
REUTRUN:void
****************************************/
void DrawDriveStatus()
{
    int contentX = 300;  // ��������ʼX����
    int contentY = 100;  // ��������ʼY����
    int buttonY = 350;
    char* p = (char*)malloc(10);

    // ��������
    puthz(250, 20, "��ǰ��ʻ״̬", 24, 26, LIGHTBLUE);

    // ���̶���ʾ���ٻ�
    DrawSpeedGauge(drive_data.speed);

    // �Ҳ���������(���ݵ�ǰģʽ��ʾ��ͬ����)
    switch (current_view)
    {
    case ENGINE_STATUS:
    {
        puthz(contentX, contentY, "������״̬", 24, 26, LIGHTBLUE);
        puthz(contentX + 180, contentY, GetEngineStatus(), 24, 26,
            drive_data.engine_on ? GREEN : RED);

        // ֻ�ڷ����������ҵ�ǰ��ʾENGINE_STATUSʱ��ʾ���ٿ��ư�ť
        if (drive_data.engine_on)
        {
            // �������Ӱ�ť (+)
            setcolor(GREEN);
            circle(contentX + 150, contentY + 65, 20);
           // rectangle(contentX + 200, contentY + 50, contentX + 230, contentY + 80);
            settextstyle(3, 0, 4);
            outtextxy(contentX + 147-5, contentY + 44-2, "+");

            // ���ټ��ٰ�ť (-)
            setcolor(RED);
            circle(contentX + 50, contentY + 65, 20);
            //rectangle(contentX + 100, contentY + 50, contentX + 130, contentY + 80);
            settextstyle(3, 0, 4);
            outtextxy(contentX + 47-5, contentY + 44-2, "-");

            // ��ʾ��ǰ����
            puthz(contentX + 50, contentY + 100, "����", 24, 26, WHITE);
            itoa(drive_data.speed, p, 10);
            settextstyle(3, 0, 4);
            outtextxy(contentX + 105, contentY + 90, p);
            setcolor(WHITE);
            settextstyle(3, 0, 3);
            outtextxy(contentX + 155, contentY +95 , "km/h");
        }
        break;
    }

    case SPEED_STATUS:
    {
        // ���ٻ����������ʾ���˴�����ʾ������Ϣ
        puthz(contentX, contentY, "��ǰ��������", 24, 26, LIGHTBLUE);
        itoa(drive_data.speed, p, 10);
        settextstyle(3, 0, 4);
        outtextxy(contentX + 180, contentY, p);
        puthz(contentX + 220, contentY, "����ÿСʱ", 24, 26, WHITE);
        break;
    }

    case WARNING_MSG:
    {
        puthz(contentX, contentY, "������Ϣ", 24, 26, has_warning ? RED : LIGHTBLUE);
        puthz(contentX + 100, contentY, drive_data.warning_msg, 24, 26,
            has_warning ? RED : GREEN);

        if (has_warning)
        {
            puthz(contentX, contentY + 40, "�������", 24, 26, YELLOW);
            puthz(contentX + 100, contentY + 40, drive_data.warning_tip, 24, 26, YELLOW);
        }
        break;
    }
    }

    free(p);

    // �ײ�������ť��
    // ���������ذ�ť(������ʾ)
    if (drive_data.engine_on) {
        setcolor(GREEN);
    }
    else {
        setcolor(RED);
    }
    circle(320, buttonY + 30, 30);
    ellipse(320, buttonY + 30, -180, 0, 15, 15);
    line(320, buttonY + 15, 320, buttonY + 45);
    puthz(270, buttonY + 70, drive_data.engine_on ? "�ر�����" : "��������", 24, 26, WHITE);

    // ģʽ�л���ť(��������)
    setcolor(LIGHTBLUE);
    puthz(120, buttonY, "������״̬", 24, 26,
        current_view == ENGINE_STATUS ? YELLOW : LIGHTBLUE);
    puthz(420, buttonY, "������Ϣ", 24, 26,
        current_view == WARNING_MSG ? YELLOW : LIGHTBLUE);
}

/****************************************
FUNCTION:DriveStatusMouse
DESCRIBETION:�������������
INPUT:int* view
REUTRUN:int
****************************************/
int DriveStatusMouse(int* current_view)
{
    int choice[7] = { 0 };

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        choice[0] = mouse_press(0, 0, 80, 50);//ֱ����ҳ��
        choice[6] = mouse_press(560, 0, 640, 50);//������һ��
        choice[1] = mouse_press(100, 350, 220, 380); // ������״̬��ť
        choice[2] = mouse_press(400, 350, 520, 380); // ������Ϣ��ť
        choice[3] = mouse_press(290, 350, 350, 410); // ���濪�ذ�ť

        // �������Ӱ�ť��� (ֻ�ڷ�����������ENGINE_STATUSʱ��Ч)
        if (drive_data.engine_on && *current_view == ENGINE_STATUS)
        {
            choice[4] = mouse_press(430, 150, 470, 180); // ����+
            choice[5] = mouse_press(330, 165-15, 370, 165+15); // ����-
        }
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
        else if (choice[1] == 1) 
        {
            *current_view = ENGINE_STATUS;
            break;
        }
        else if (choice[2] == 1)
        {
            *current_view = WARNING_MSG;
            break;
        }
        else if (choice[3] == 1)
        {
            ToggleEngine();
            delay(300);
            break;
        }
        else if (choice[4] == 1 && drive_data.engine_on)
        {
            // ���ӳ���(������MAX_SPEED)
            if (drive_data.speed < MAX_SPEED)
            {
                drive_data.speed++;
                delay(300);
            }
            break;
        }
        else if (choice[5] == 1 && drive_data.engine_on)
        {
            // ���ٳ���(��С��0)
            if (drive_data.speed > 0) 
            {
                drive_data.speed--;
                delay(300);
            }
            break;
        }
        else continue;
        InitDriveStatus();
        delay(300);
        break;
    }
    return 1;
}
