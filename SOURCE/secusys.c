/**

---
-        �汾�ţ�2.1
-        ���ߣ�ZYY
-        �������ڣ�2025
-        ˵����secusys����ʵ�ְ�ȫϵͳѡ�񼰹��ϼ��
-        ���£����͹��ϸ�����10%

---
**/

#include "init.h"
#include "secusys.h"
#include "page.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SECUSYS_FILE "..\\CODE\\text\\secusys.txt"
#define FAULT_PROBABILITY 10  // 10%���ϸ���

// ģʽö��
typedef enum
{
    ABS,
    ESP
} SecuSys;

// ��ϵͳ״̬
typedef struct
{
    int wheel_sensor;    // ���ٴ�����
    int ecu;             // ECU���Ƶ�Ԫ
    int brake_pressure;  // �ƶ�ѹ������
    int steering_angle;  // ת��Ǵ�����
    int yaw_rate;        // ��ڽ��ٶ�
    int lateral_accel;   // ������ٶ�
} SubSystemStatus;

// ȫ�ֱ���
static SecuSys current_sys = ABS;
static SubSystemStatus sys_status;
static int system_fault = 0;

/****************************************
FUNCTION:InitSystemStatus
DESCRIBETION:��ʼ��ϵͳ״̬��10%���ϸ��ʣ�
INPUT:void
REUTRUN:void
****************************************/
void InitSystemStatus()
{
    srand(time(NULL));

    // ABSϵͳ״̬ (0=����, 1=����)
    sys_status.wheel_sensor = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.ecu = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.brake_pressure = (rand() % 100) < FAULT_PROBABILITY;

    // ESPϵͳ״̬
    sys_status.steering_angle = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.yaw_rate = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.lateral_accel = (rand() % 100) < FAULT_PROBABILITY;

    // ����Ƿ��й���
    system_fault = sys_status.wheel_sensor || sys_status.ecu || sys_status.brake_pressure ||
        sys_status.steering_angle || sys_status.yaw_rate || sys_status.lateral_accel;
}

/****************************************
FUNCTION:RepairSystem
DESCRIBETION:�޸���ǰϵͳ�Ĺ���
INPUT:void
REUTRUN:void
****************************************/
void RepairSystem()
{
    if (current_sys == ABS) {
        sys_status.wheel_sensor = 0;
        sys_status.ecu = 0;
        sys_status.brake_pressure = 0;
    }
    else {
        sys_status.steering_angle = 0;
        sys_status.yaw_rate = 0;
        sys_status.lateral_accel = 0;
    }

    // ���¼���Ƿ��й���
    system_fault = sys_status.wheel_sensor || sys_status.ecu || sys_status.brake_pressure ||
        sys_status.steering_angle || sys_status.yaw_rate || sys_status.lateral_accel;
}

/****************************************
FUNCTION:DrawKk
DESCRIBETION:�����
INPUT:void
REUTRUN:void
****************************************/
void DrawKk()
{
    setcolor(LIGHTBLUE);
    setlinestyle(0, 0, 1);
    line(85, 90, 310, 90);
    line(85, 125, 310, 125);
    line(85, 90, 52, 107);
    line(85, 125, 52, 107);
    line(71, 90, 38, 107);
    line(71, 125, 38, 107);
    line(57, 90, 24, 107);
    line(57, 125, 24, 107);
    line(310, 90, 343, 107);
    line(310, 125, 343, 107);
    line(324, 90, 357, 107);
    line(324, 125, 357, 107);
    line(338, 90, 371, 107);
    line(338, 125, 371, 107);

    line(85, 155, 310, 155);
    line(85, 190, 310, 190);
    line(85, 155, 52, 172);
    line(85, 190, 52, 172);
    line(71, 155, 38, 172);
    line(71, 190, 38, 172);
    line(57, 155, 24, 172);
    line(57, 190, 24, 172);
    line(310, 155, 343, 172);
    line(310, 190, 343, 172);
    line(324, 155, 357, 172);
    line(324, 190, 357, 172);
    line(338, 155, 371, 172);
    line(338, 190, 371, 172);
    line(85, 250, 310, 250);
    line(85, 305, 310, 305);
    line(85, 360, 310, 360);
   // line(85, 415, 310, 415);

}

/****************************************
FUNCTION:DrawSystemStatus
DESCRIBETION:����ϵͳ״̬��Ϣ
INPUT:void
REUTRUN:void
****************************************/
void DrawSystemStatus()
{
    int y_pos = 220;
    if (current_sys == ABS)
    {
        // ���ٴ�����״̬
        puthz(87, y_pos, "���ٴ�����", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.wheel_sensor ? "����" : "����",
            24, 26, sys_status.wheel_sensor ? RED : GREEN);
		if (sys_status.wheel_sensor)
		{
			setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos+15, 5, 5);
		}
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }

        // ECU���Ƶ�Ԫ״̬
        y_pos += 55;
        setcolor(LIGHTBLUE);
        outtextxy(87, y_pos - 2, "ECU");
        puthz(137, y_pos, "���Ƶ�Ԫ", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.ecu ? "����" : "����",
            24, 26, sys_status.ecu ? RED : GREEN);
        if (sys_status.ecu)
        {
            setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        // �ƶ�ѹ������״̬
        y_pos += 55;
        puthz(87, y_pos, "�ƶ�ѹ������", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.brake_pressure ? "����" : "����",
            24, 26, sys_status.brake_pressure ? RED : GREEN);
        if (sys_status.brake_pressure)
        {
            setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }
    }
    else
    {
        // ESPϵͳ״̬
        // ת��Ǵ�����״̬
        puthz(87, y_pos, "ת��Ǵ�����", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.steering_angle ? "����" : "����",
            24, 26, sys_status.steering_angle ? RED : GREEN);
        if (sys_status.steering_angle)
        {
            setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        // ��ڽ��ٶ�״̬
        y_pos += 55;
        puthz(87, y_pos, "��ڽ��ٶ�", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.yaw_rate ? "����" : "����",
            24, 26, sys_status.yaw_rate ? RED : GREEN);
        if (sys_status.yaw_rate)
        {
            setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        // ������ٶ�״̬
        y_pos += 55;
        puthz(87, y_pos, "������ٶ�", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.lateral_accel ? "����" : "����",
            24, 26, sys_status.lateral_accel ? RED : GREEN);
        if (sys_status.lateral_accel)
        {
            setcolor(RED);
            setfillstyle(1, RED);
            fillellipse(50, y_pos + 15, 5, 5);
        }
        else
        {
            setcolor(GREEN);
            setfillstyle(1, GREEN);
            fillellipse(50, y_pos + 15, 5, 5);
        }
    }

    // ����״̬��ʾ
    y_pos += 55;
    puthz(87, y_pos, "����״̬", 24, 26, LIGHTBLUE);
    puthz(337, y_pos, system_fault ? "����" : "����",
        24, 26, system_fault ? RED : GREEN);

    // �޸���ť
    setcolor(WHITE);
    rectangle(540, 375, 610, 419);
    puthz(550, 385, "�޸�", 24, 26, WHITE);
}

/* ���ຯ��(OpenSystem, DrawSysButton, SysMouse)���ֲ��� */

/****************************************
FUNCTION:OpenSystem
DESCRIBETION:�򿪰�ȫϵͳҳ��
INPUT:void
REUTRUN:void
****************************************/
void OpenSystem()
{
    // ��ȡ�����ϵͳ
    FILE* fp = fopen(SECUSYS_FILE, "rt");
    if (fp) {
        fscanf(fp, "%d", &current_sys);
        fclose(fp);
    }

    // ��ʼ��ϵͳ״̬
    InitSystemStatus();

    while (1)
    {
        FILE* fp = fopen(SECUSYS_FILE, "w");
        int sys_ret = 1;

        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawKk();
        DrawSysButton(current_sys);
        DrawSystemStatus();

        sys_ret = SysMouse(&current_sys);

        if (fp == NULL) { return; }
        fprintf(fp, "%d", current_sys);
        fclose(fp);

        if (!sys_ret)
            return;
    }
}

/****************************************
FUNCTION:DrawSysButton
DESCRIBETION:���ư�ȫϵͳ�������а�ť
INPUT:int
REUTRUN:void
****************************************/
void DrawSysButton(int current_sys) {
    // ������ʾ��ǰģʽ
    puthz(150, 20, "�鿴��ȫϵͳ", 24, 26, LIGHTBLUE);
    setcolor(LIGHTBLUE);
    settextstyle(3, 0, 2);
    outtextxy(330, 20, current_sys == ABS ? "ABS" : "ESP");

    // ��������ѡ��ť
    outtextxy(94, 95, "ABS");
    puthz(134, 96, "�������ƶ�ϵͳ", 24, 27, LIGHTBLUE);
    outtextxy(94, 160, "ESP");
    puthz(134, 161, "�����ȶ�����", 24, 27, LIGHTBLUE);
}

/****************************************
FUNCTION:SysMouse
DESCRIBETION:��ȫϵͳҳ����깦��
INPUT:int* num
REUTRUN:int
****************************************/
int SysMouse(int* current_sys) {
    int choice[5] = { 0 };

    while (1) {
        // �����������ð�ť
        newmouse(&MouseX, &MouseY, &press);

        choice[1] = mouse_press(80, 95, 200, 125);  // ABS��ť
        choice[2] = mouse_press(80, 160, 500, 190); // ESP��ť
        choice[3] = mouse_press(435, 15, 615, 45);    // ���ذ�ť
        choice[0] = mouse_press(40, 15, 100, 50);     // ��ҳ��ť
        choice[4] = mouse_press(540, 375, 610, 419);   // �޸���ť

        // �ж�ѡ��
        if (choice[0] == 1) {
            return 0;
        }
        else if (choice[1] == 1) {
            *current_sys = ABS;
            break;
        }
        else if (choice[2] == 1) {
            *current_sys = ESP;
            break;
        }
        else if (choice[3] == 1) {
            return 0;
        }
        else if (choice[4] == 1) {
            RepairSystem();
            break;
        }
    }
    delay(100);
    return 1;
}