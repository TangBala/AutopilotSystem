/**************************************************
-版本号：1.0
- 作者：Y
- 生成日期：2024—3—17
- 说明：Battery类函数实现电池功能
* *************************************************
**/

#include"init.h"
#include"d_mode.h"
#include"page.h"

#define MODE_FILE "..\\CODE\\text\\d_mode.txt"

// 模式枚举，明确指定对应的整数值

// 当前模式（默认C）
static DriveMode current_mode;

/****************************************
FUNCTION:OpenBattery
DESCRIBETIO N:打开菜单中电池页
INPUT:void
REUTRUN:void
****************************************/
void OpenDrivemode()
{
    // 读取保存的模式
    FILE* fp = fopen(MODE_FILE, "rt");
    if (fp)
    {
        int saved_mode;
        if (fscanf(fp, "%d", &saved_mode) == 1)
        {
            // 确保读取的值有效
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

        // 写入文件（每次循环都尝试保存）
        fp = fopen(MODE_FILE, "w");
        if (fp == NULL)
        {
            perror("Failed to write mode file"); // 打印错误信息
        }
        else
        {
            fprintf(fp, "%d", (int)current_mode); // 显式转换为 int
            fflush(fp); // 强制刷新缓冲区
            fclose(fp);
        }

        if (!mode_ret)
            return;
    }
}

/****************************************
FUNCTION:DrawModeButton
DESCRIBETION:绘制菜单中电池所有按钮
INPUT:int
REUTRUN:void
****************************************/

void DrawModeButton(int current_mode)
{
    // 顶部显示当前模式
    char* mode_text[] = { "手动模式", "辅助模式", "自动模式" };
    puthz(280, 20, mode_text[current_mode], 24, 26, LIGHTBLUE);
    DrawMid(30, 130);
    DrawMid(245 - 23, 130);
    DrawMid(436 - 23, 130);

    // 绘制三个选择按钮
    setcolor(LIGHTBLUE);

    // 按钮A（矩形区域示例）
    puthz(50 + 10, 155, "手动模式", 24, 27, LIGHTBLUE);
    puthz(245 - 23 + 10 + 20, 155, "辅助模式", 24, 27, LIGHTBLUE);
    puthz(436 - 23 + 20 + 10, 155, "自动模式", 24, 27, LIGHTBLUE);
    fillellipse(35, 250 + 8, 5, 5);
    fillellipse(35, 310 + 8, 5, 5);
    fillellipse(35, 370 + 8, 5, 5);
    /* fillellipse(242-15, 250 + 8, 5, 5);
     fillellipse(242-15, 310 + 8, 5, 5);
     fillellipse(242-15, 370 + 8, 5, 5);
     fillellipse(433 - 15, 250 + 8, 5, 5);
     fillellipse(433 - 15, 340 + 8, 5, 5);*/

    puthz(50, 250, "驾驶员完全控制车", 16, 18, LIGHTBLUE);
    puthz(50, 280, "辆", 16, 18, LIGHTBLUE);
    puthz(50, 310, "系统仅提供基础", 16, 18, LIGHTBLUE);
    puthz(50, 340, "仪表显示", 16, 18, LIGHTBLUE);
    puthz(50, 370, "适合复杂路况或", 16, 18, LIGHTBLUE);
    puthz(50, 400, "追求操控体验时", 16, 18, LIGHTBLUE);
    puthz(50, 430, "使用", 16, 18, LIGHTBLUE);

    puthz(242, 250, "系统自动控制加", 16, 18, LIGHTBLUE);
    puthz(242, 280, "减速和方向", 16, 18, LIGHTBLUE);
    puthz(242, 310, "驾驶员需保持手", 16, 18, LIGHTBLUE);
    puthz(242, 340, "扶方向盘", 16, 18, LIGHTBLUE);
    puthz(242, 370, "适用于高速巡航", 16, 18, LIGHTBLUE);
    puthz(242, 400, "等标准化场景", 16, 18, LIGHTBLUE);

    puthz(433, 250, "车辆自主完成所", 16, 18, LIGHTBLUE);
    puthz(433, 280, "有驾驶操作", 16, 18, LIGHTBLUE);
    puthz(433, 310, "乘客无需干预", 16, 18, LIGHTBLUE);
    puthz(433, 340, "请在封闭道路或", 16, 18, LIGHTBLUE);
    puthz(433, 370, "法规允许区域启", 16, 18, LIGHTBLUE);
    puthz(433, 400, "用。", 16, 18, LIGHTBLUE);
}



/****************************************
FUNCTION:ModeMouse
DESCRIBETION:电池页的鼠标功能
INPUT:int* num
REUTRUN:int
****************************************/
int ModeMouse(int* current_mode)
{
    int choice[5] = { 0 };

    while (1)
    {
        //绘制鼠标和设置按钮
        newmouse(&MouseX, &MouseY, &press);

        choice[1] = mouse_press(50, 135, 214, 210);
        choice[2] = mouse_press(240, 135, 400, 210);
        choice[3] = mouse_press(420, 135, 600, 210);
        choice[0] = mouse_press(0, 0, 80, 50);//直达主页面
        choice[4] = mouse_press(560, 0, 640, 50);//返回上一层
        //判断选项
        if (choice[0] == 1)//直达主页面
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
        else if (choice[4] == 1)//返回上一层
        {
            return 0;
        }
    }
    delay(100);
    return 1;
}