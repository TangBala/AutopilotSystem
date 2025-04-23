/**

---
-        版本号：2.1
-        作者：ZYY
-        生成日期：2025
-        说明：secusys函数实现安全系统选择及故障检测
-        更新：降低故障概率至10%

---
**/

#include "init.h"
#include "secusys.h"
#include "page.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SECUSYS_FILE "..\\CODE\\text\\secusys.txt"
#define FAULT_PROBABILITY 10  // 10%故障概率

// 模式枚举
typedef enum
{
    ABS,
    ESP
} SecuSys;

// 子系统状态
typedef struct
{
    int wheel_sensor;    // 轮速传感器
    int ecu;             // ECU控制单元
    int brake_pressure;  // 制动压力调节
    int steering_angle;  // 转向角传感器
    int yaw_rate;        // 横摆角速度
    int lateral_accel;   // 侧向加速度
} SubSystemStatus;

// 全局变量
static SecuSys current_sys = ABS;
static SubSystemStatus sys_status;
static int system_fault = 0;

/****************************************
FUNCTION:InitSystemStatus
DESCRIBETION:初始化系统状态（10%故障概率）
INPUT:void
REUTRUN:void
****************************************/
void InitSystemStatus()
{
    srand(time(NULL));

    // ABS系统状态 (0=正常, 1=故障)
    sys_status.wheel_sensor = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.ecu = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.brake_pressure = (rand() % 100) < FAULT_PROBABILITY;

    // ESP系统状态
    sys_status.steering_angle = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.yaw_rate = (rand() % 100) < FAULT_PROBABILITY;
    sys_status.lateral_accel = (rand() % 100) < FAULT_PROBABILITY;

    // 检查是否有故障
    system_fault = sys_status.wheel_sensor || sys_status.ecu || sys_status.brake_pressure ||
        sys_status.steering_angle || sys_status.yaw_rate || sys_status.lateral_accel;
}

/****************************************
FUNCTION:RepairSystem
DESCRIBETION:修复当前系统的故障
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

    // 重新检查是否有故障
    system_fault = sys_status.wheel_sensor || sys_status.ecu || sys_status.brake_pressure ||
        sys_status.steering_angle || sys_status.yaw_rate || sys_status.lateral_accel;
}

/****************************************
FUNCTION:DrawKk
DESCRIBETION:画框框
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
DESCRIBETION:绘制系统状态信息
INPUT:void
REUTRUN:void
****************************************/
void DrawSystemStatus()
{
    int y_pos = 220;
    if (current_sys == ABS)
    {
        // 轮速传感器状态
        puthz(87, y_pos, "轮速传感器", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.wheel_sensor ? "故障" : "正常",
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

        // ECU控制单元状态
        y_pos += 55;
        setcolor(LIGHTBLUE);
        outtextxy(87, y_pos - 2, "ECU");
        puthz(137, y_pos, "控制单元", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.ecu ? "故障" : "正常",
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
        // 制动压力调节状态
        y_pos += 55;
        puthz(87, y_pos, "制动压力调节", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.brake_pressure ? "故障" : "正常",
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
        // ESP系统状态
        // 转向角传感器状态
        puthz(87, y_pos, "转向角传感器", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.steering_angle ? "故障" : "正常",
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
        // 横摆角速度状态
        y_pos += 55;
        puthz(87, y_pos, "横摆角速度", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.yaw_rate ? "故障" : "正常",
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
        // 侧向加速度状态
        y_pos += 55;
        puthz(87, y_pos, "侧向加速度", 24, 26, LIGHTBLUE);
        puthz(337, y_pos, sys_status.lateral_accel ? "故障" : "正常",
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

    // 总体状态显示
    y_pos += 55;
    puthz(87, y_pos, "总体状态", 24, 26, LIGHTBLUE);
    puthz(337, y_pos, system_fault ? "故障" : "正常",
        24, 26, system_fault ? RED : GREEN);

    // 修复按钮
    setcolor(WHITE);
    rectangle(540, 375, 610, 419);
    puthz(550, 385, "修复", 24, 26, WHITE);
}

/* 其余函数(OpenSystem, DrawSysButton, SysMouse)保持不变 */

/****************************************
FUNCTION:OpenSystem
DESCRIBETION:打开安全系统页面
INPUT:void
REUTRUN:void
****************************************/
void OpenSystem()
{
    // 读取保存的系统
    FILE* fp = fopen(SECUSYS_FILE, "rt");
    if (fp) {
        fscanf(fp, "%d", &current_sys);
        fclose(fp);
    }

    // 初始化系统状态
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
DESCRIBETION:绘制安全系统界面所有按钮
INPUT:int
REUTRUN:void
****************************************/
void DrawSysButton(int current_sys) {
    // 顶部显示当前模式
    puthz(150, 20, "查看安全系统", 24, 26, LIGHTBLUE);
    setcolor(LIGHTBLUE);
    settextstyle(3, 0, 2);
    outtextxy(330, 20, current_sys == ABS ? "ABS" : "ESP");

    // 绘制两个选择按钮
    outtextxy(94, 95, "ABS");
    puthz(134, 96, "防抱死制动系统", 24, 27, LIGHTBLUE);
    outtextxy(94, 160, "ESP");
    puthz(134, 161, "电子稳定程序", 24, 27, LIGHTBLUE);
}

/****************************************
FUNCTION:SysMouse
DESCRIBETION:安全系统页的鼠标功能
INPUT:int* num
REUTRUN:int
****************************************/
int SysMouse(int* current_sys) {
    int choice[5] = { 0 };

    while (1) {
        // 绘制鼠标和设置按钮
        newmouse(&MouseX, &MouseY, &press);

        choice[1] = mouse_press(80, 95, 200, 125);  // ABS按钮
        choice[2] = mouse_press(80, 160, 500, 190); // ESP按钮
        choice[3] = mouse_press(435, 15, 615, 45);    // 返回按钮
        choice[0] = mouse_press(40, 15, 100, 50);     // 主页按钮
        choice[4] = mouse_press(540, 375, 610, 419);   // 修复按钮

        // 判断选项
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