/**
**************************************************
*        版本号：1.2
*        作者：ZYY
*        生成日期：2025
*        说明：d_status函数实现驾驶状态显示
*        更新：增加环形车速进度条显示
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
#define MAX_SPEED 40  // 最大车速40km/h

// 驾驶状态枚举
typedef enum
{
    ENGINE_STATUS,
    SPEED_STATUS,
    WARNING_MSG
} DriveStatus;

// 驾驶状态数据
typedef struct
{
    int engine_on;       // 发动机开关 (0=关闭, 1=开启)
    int speed;          // 车速 (km/h)
    char warning_msg[50]; // 警告信息
    char warning_tip[50]; // 警告提示语
} DriveStatusData;

// 全局变量
static DriveStatus current_view;
static DriveStatusData drive_data;
static int has_warning = 0;

/****************************************
FUNCTION:InitDriveStatus
DESCRIBETION:初始化驾驶状态数据
INPUT:void
REUTRUN:void
****************************************/
void InitDriveStatus()
{
    const char* tips[] = {
        "",
        "请减速并停车冷却发动机",
        "请立即添加机油",
        "请检查充电系统",
        "请立即检修刹车",
        "请减速至安全车速"
    };

    const char* warnings[] =
    {
        "无警告",
        "发动机温度过高",
        "油压过低",
        "电池电压异常",
        "刹车系统故障",
        "车速过高"
    };
    int warning_idx = 0; // 默认为无警告
    srand(time(NULL));

    // 根据车辆状态确定警告信息

    // 车速过高警告 (超过35km/h)
    if (drive_data.speed > 35) {
        warning_idx = 5; // "车速过高"
    }
    // 发动机运行时可能出现的警告
    else if (drive_data.engine_on) {
        // 随机生成一个与发动机状态相关的警告(1-4)
        warning_idx = 1 + (rand() % 4);

        // 如果已经有警告且不是车速过高，保持原警告(避免频繁切换)
        if (has_warning && strcmp(drive_data.warning_msg, "车速过高") != 0) {
            // 保持原警告
            return;
        }
    }
    // 设置警告信息
    strcpy(drive_data.warning_msg, warnings[warning_idx]);
    strcpy(drive_data.warning_tip, tips[warning_idx]);
    has_warning = (warning_idx != 0);
}

/****************************************
FUNCTION:ToggleEngine
DESCRIBETION:引擎切换函数
INPUT:void
REUTRUN:void
****************************************/

void ToggleEngine()
{
    drive_data.engine_on = !drive_data.engine_on;
    if (!drive_data.engine_on)
    {
        drive_data.speed = 0; // 关闭发动机时车速归零
    }
    else
    {
        FILE* fp = fopen(DSTATUS_FILE, "rt");
        if (fp)
        {
            fscanf(fp, "%d ", &drive_data.speed);
            fclose(fp);
            // 确保车速在0-MAX_SPEED范围内
            if (drive_data.speed < 0) drive_data.speed = 0;
            if (drive_data.speed > MAX_SPEED) drive_data.speed = MAX_SPEED;

            // 发动机启动时重新检查警告状态
            InitDriveStatus();
        }
        else
        {
            drive_data.speed = 0; // 文件读取失败时设为0
        }
    }
}


/****************************************
FUNCTION:GetEngineStatus
DESCRIBETION:获取当前发动机状态文本
INPUT:void
REUTRUN:char* 状态文本
****************************************/
char* GetEngineStatus()
{
    if (!drive_data.engine_on) return "已关闭";
    return (drive_data.speed < 10) ? "怠速" : "运行中";
}



/****************************************
FUNCTION:OpenDriveStatus
DESCRIBETION:打开驾驶状态页面
INPUT:void
REUTRUN:void
****************************************/

void OpenDriveStatus()
{

    while (1)
    {
        // 保存当前状态到文件
        FILE* fp = fopen(DSTATUS_FILE, "wt");
        FILE* fp_write = fopen(DSTATUS_FILE, "wt");
        int status_ret;
        if (fp)
        {
            // 获取当前警告状态索引
            int warning_idx = 0;
            if (strcmp(drive_data.warning_msg, "发动机温度过高") == 0) warning_idx = 1;
            else if (strcmp(drive_data.warning_msg, "油压过低") == 0) warning_idx = 2;
            else if (strcmp(drive_data.warning_msg, "电池电压异常") == 0) warning_idx = 3;
            else if (strcmp(drive_data.warning_msg, "刹车系统故障") == 0) warning_idx = 4;

            fprintf(fp, "%d %d %d %d",
                current_view,
                drive_data.engine_on,
                drive_data.speed,
                warning_idx);
            fclose(fp);
        }
        InitDriveStatus();  // 从文件初始化状态
        // 绘制界面
        setfillstyle(1, BLACK);
        bar(0, 0, 640, 480);
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawDriveStatus();

        // 处理用户输入
        status_ret = DriveStatusMouse(&current_view);
        if (fp_write)
        {
            // 获取当前警告状态索引
            int warning_idx = 0;
            if (strcmp(drive_data.warning_msg, "发动机温度过高") == 0) warning_idx = 1;
            else if (strcmp(drive_data.warning_msg, "油压过低") == 0) warning_idx = 2;
            else if (strcmp(drive_data.warning_msg, "电池电压异常") == 0) warning_idx = 3;
            else if (strcmp(drive_data.warning_msg, "刹车系统故障") == 0) warning_idx = 4;

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
DESCRIBETION:绘制车速环形进度条(调整位置)
INPUT:int speed - 当前车速(0-40)
REUTRUN:void
****************************************/
void DrawSpeedGauge(int speed)
{
    const int centerX = 160;  // 调整中心X坐标到左侧
    const int centerY = 180;  // 中心Y坐标
    const int innerRadius = 50;  // 内半径
    const int outerRadius = 70;  // 外半径
    const float startAngle = -M_PI / 2;  // 起始角度(-90度)
    const float maxAngle = M_PI * 3 / 2;   // 最大角度(270度)
    char speedStr[10];
    int i=0;
    float angleStep = M_PI / 100;  // 角度步长
    int steps = (speed * 250) / MAX_SPEED;  // 计算步数(0-250对应0-40km/h)

    // 绘制背景圆环
    setcolor(LIGHTGRAY);
    circle(centerX, centerY, innerRadius);
    circle(centerX, centerY, outerRadius);

    // 绘制进度条
    setcolor(GREEN);
    for (; i < steps; i++) 
    {
        float angle = startAngle + (maxAngle * i) / 250;
        line(centerX + innerRadius * cos(angle), centerY + innerRadius * sin(angle),
            centerX + outerRadius * cos(angle), centerY + outerRadius * sin(angle));
    }

    // 绘制中央车速数字
    sprintf(speedStr, "%d", speed);
    settextstyle(3, 0, 5);  
    setcolor(WHITE);
    outtextxy(centerX-textwidth(speedStr)/2+5, centerY-10-textheight(speedStr)/2, speedStr);

    // 绘制单位
    settextstyle(3, 0, 2);
    outtextxy(centerX - 25, centerY+10,"km/h");
}

/****************************************
FUNCTION:DrawDriveStatus
DESCRIBETION:绘制驾驶状态信息(重新布局)
INPUT:void
REUTRUN:void
****************************************/
void DrawDriveStatus()
{
    int contentX = 300;  // 主内容起始X坐标
    int contentY = 100;  // 主内容起始Y坐标
    int buttonY = 350;
    char* p = (char*)malloc(10);

    // 顶部标题
    puthz(250, 20, "当前驾驶状态", 24, 26, LIGHTBLUE);

    // 左侧固定显示车速环
    DrawSpeedGauge(drive_data.speed);

    // 右侧主内容区(根据当前模式显示不同内容)
    switch (current_view)
    {
    case ENGINE_STATUS:
    {
        puthz(contentX, contentY, "发动机状态", 24, 26, LIGHTBLUE);
        puthz(contentX + 180, contentY, GetEngineStatus(), 24, 26,
            drive_data.engine_on ? GREEN : RED);

        // 只在发动机开启且当前显示ENGINE_STATUS时显示车速控制按钮
        if (drive_data.engine_on)
        {
            // 车速增加按钮 (+)
            setcolor(GREEN);
            circle(contentX + 150, contentY + 65, 20);
           // rectangle(contentX + 200, contentY + 50, contentX + 230, contentY + 80);
            settextstyle(3, 0, 4);
            outtextxy(contentX + 147-5, contentY + 44-2, "+");

            // 车速减少按钮 (-)
            setcolor(RED);
            circle(contentX + 50, contentY + 65, 20);
            //rectangle(contentX + 100, contentY + 50, contentX + 130, contentY + 80);
            settextstyle(3, 0, 4);
            outtextxy(contentX + 47-5, contentY + 44-2, "-");

            // 显示当前车速
            puthz(contentX + 50, contentY + 100, "车速", 24, 26, WHITE);
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
        // 车速环已在左侧显示，此处可显示额外信息
        puthz(contentX, contentY, "当前车速详情", 24, 26, LIGHTBLUE);
        itoa(drive_data.speed, p, 10);
        settextstyle(3, 0, 4);
        outtextxy(contentX + 180, contentY, p);
        puthz(contentX + 220, contentY, "公里每小时", 24, 26, WHITE);
        break;
    }

    case WARNING_MSG:
    {
        puthz(contentX, contentY, "警告信息", 24, 26, has_warning ? RED : LIGHTBLUE);
        puthz(contentX + 100, contentY, drive_data.warning_msg, 24, 26,
            has_warning ? RED : GREEN);

        if (has_warning)
        {
            puthz(contentX, contentY + 40, "建议操作", 24, 26, YELLOW);
            puthz(contentX + 100, contentY + 40, drive_data.warning_tip, 24, 26, YELLOW);
        }
        break;
    }
    }

    free(p);

    // 底部操作按钮区
    // 发动机开关按钮(居中显示)
    if (drive_data.engine_on) {
        setcolor(GREEN);
    }
    else {
        setcolor(RED);
    }
    circle(320, buttonY + 30, 30);
    ellipse(320, buttonY + 30, -180, 0, 15, 15);
    line(320, buttonY + 15, 320, buttonY + 45);
    puthz(270, buttonY + 70, drive_data.engine_on ? "关闭引擎" : "启动引擎", 24, 26, WHITE);

    // 模式切换按钮(分列两侧)
    setcolor(LIGHTBLUE);
    puthz(120, buttonY, "发动机状态", 24, 26,
        current_view == ENGINE_STATUS ? YELLOW : LIGHTBLUE);
    puthz(420, buttonY, "警告信息", 24, 26,
        current_view == WARNING_MSG ? YELLOW : LIGHTBLUE);
}

/****************************************
FUNCTION:DriveStatusMouse
DESCRIBETION:调整鼠标检测区域
INPUT:int* view
REUTRUN:int
****************************************/
int DriveStatusMouse(int* current_view)
{
    int choice[7] = { 0 };

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
        choice[6] = mouse_press(560, 0, 640, 50);//返回上一层
        choice[1] = mouse_press(100, 350, 220, 380); // 发动机状态按钮
        choice[2] = mouse_press(400, 350, 520, 380); // 警告信息按钮
        choice[3] = mouse_press(290, 350, 350, 410); // 引擎开关按钮

        // 车速增加按钮检测 (只在发动机开启且ENGINE_STATUS时有效)
        if (drive_data.engine_on && *current_view == ENGINE_STATUS)
        {
            choice[4] = mouse_press(430, 150, 470, 180); // 车速+
            choice[5] = mouse_press(330, 165-15, 370, 165+15); // 车速-
        }
        if (choice[0] == 1)//直达主页面
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[6] == 1)//返回上一层
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
            // 增加车速(不超过MAX_SPEED)
            if (drive_data.speed < MAX_SPEED)
            {
                drive_data.speed++;
                delay(300);
            }
            break;
        }
        else if (choice[5] == 1 && drive_data.engine_on)
        {
            // 减少车速(不小于0)
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
