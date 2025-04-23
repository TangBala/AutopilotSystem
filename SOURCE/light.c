/* light.c */
#include "init.h"
#include "light.h"
#include "page.h"

// 全局变量
LightBrightness light_brightness = {
    {0},
    -1 // 初始未选中任何灯光
};
int num[8] = { 0 }; // 灯光开关状态

/****************************************
- 绘制亮度调节条（为当前选中的灯光）
****************************************/
void DrawBrightnessBar(int x, int y, int level) 
{
    int i = 1;
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + 100, y + 20);

    setcolor(DARKGRAY);
    rectangle(x, y, x + 100, y + 20);

    //// 绘制分段线
    //for (; i < 4; i++) {
    //    line(x + i * 25, y, x + i * 25, y + 20);
    //}
    if (level <0)
		level = 0;
    // 填充当前亮度
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(x + 1, y + 1, x + level * 25, y + 19);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x + level * 25-10, y-1 , x + level * 25+10, y + 21);
}

/****************************************
- 主界面函数
****************************************/
void OpenLight() 
{
    LightMode current_mode = EXTERNAL_LIGHTS;
    // 读取状态
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
        // 绘制界面
        DrawTopMid(0);
        DrawHomeRet();
        DrawToHome();
        DrawLightSButton(current_mode);
        DrawLightChangePart(num, current_mode);
        PutLightHz(current_mode);

        // 绘制所有亮度条
        for (; i < 4; i++) 
        {
            int light_idx = (current_mode == EXTERNAL_LIGHTS) ? i : i + 4;
            DrawBrightnessBar(390, 160 + i * 80, light_brightness.level[light_idx]);
        }

        // 处理输入
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
- 修改后的LightMouse函数
****************************************/
int LightMouse(LightMode* mode, int* ischange) 
{
    int choice[4] = { 0 };
    *ischange = 0;
    while (1) {
        int i = 0;
        newmouse(&MouseX, &MouseY, &press);

        // 模式选择
        choice[0] = mouse_press(100, 80, 250, 130); // 外部灯光
        choice[1] = mouse_press(350, 80, 500, 130); // 内部灯光
        choice[2] = mouse_press(0, 0, 80, 50);//直达主页面
        choice[3] = mouse_press(560, 0, 640, 50);//返回上一层
        if (choice[0]==1) {
            *mode = EXTERNAL_LIGHTS;
            break;
        }
         else if (choice[1]==1) {
            *mode = INTERNAL_LIGHTS;
            break;
        }
        else if (choice[2] == 1)//直达主页面
        {
            ClearGraph();
            OpenMainPage();
            break;
        }
        else if (choice[3] == 1)//返回上一层
        {
            return 0;
        }
        // 处理亮度条点击
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
                        num[light_idx] = 1; // 自动开启
                    }
                    else
					{
						num[light_idx] = 0; // 自动关闭
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
DESCRIBETION:绘制灯光页按钮(根据模式显示不同按钮)
INPUT:LightMode mode - 当前灯光模式
REUTRUN:void
****************************************/
void DrawLightSButton(LightMode mode)
{
    int point1[24] = { 110,80, 86,100, 86,145, 106,145, 110,135, 221,135, 221,145, 241,145, 261,125, 261,95, 270,80, 110,80 };
    int point2[24] = {360,80, 336,100,  336,145,  356,145, 360,135,  471,135,  471,145,  491,145, 511,125,  511,95,   520,80,   360,80 };
    Draw(LIGHTBLUE);
    // 模式选择按钮
    setcolor(LIGHTBLUE);
    drawpoly(12, point1); // 外部灯光按钮
	drawpoly(12, point2);// 内部灯光按钮
    // 高亮当前模式
    if (mode == EXTERNAL_LIGHTS)
    {
        setcolor(YELLOW);
        drawpoly(12, point1); // 外部灯光按钮
    }
    else {
        setcolor(YELLOW);
        drawpoly(12, point2);// 内部灯光按钮
    }

    setcolor(LIGHTBLUE);
    puthz(120, 100, "外部灯光", 24, 26, WHITE);
    puthz(370, 100, "内部灯光", 24, 26, WHITE);

    // 根据当前模式绘制不同按钮
    if (mode == EXTERNAL_LIGHTS)
    {
        // 外部灯光控制按钮
        rectangle(150, 150, 250, 200);   // 前大灯
        rectangle(150, 150 + 80, 250, 200 + 80);  // 雾灯
        rectangle(150, 150 + 2 * 80, 250, 200 + 2 * 80);  // 尾灯
        rectangle(150, 150 + 3 * 80, 250, 200 + 3 * 80);  // 转向灯

        puthz(160, 170, "前大灯", 24, 26, LIGHTBLUE);
        puthz(172, 170+80, "雾灯", 24, 26, LIGHTBLUE);
        puthz(172, 170+2*80, "尾灯", 24, 26, LIGHTBLUE);
        puthz(160, 170+3*80, "转向灯", 24, 26, LIGHTBLUE);
    }
    else {
        // 内部灯光控制按钮
        rectangle(150, 150, 250, 200);  // 顶灯
        rectangle(150, 150+80, 250, 200+80);  // 仪表灯
        rectangle(150, 150+2*80, 250, 200+2*80);  // 脚灯
        rectangle(150, 150+3*80, 250, 200+3*80);  // 氛围灯

        puthz(172, 170, "顶灯", 24, 26, LIGHTBLUE);
        puthz(160, 170+80, "仪表灯", 24, 26, LIGHTBLUE);
        puthz(172, 170+2*80, "脚灯", 24, 26, LIGHTBLUE);
        puthz(160, 170+3*80, "氛围灯", 24, 26, LIGHTBLUE);
    }
}

/****************************************
FUNCTION:DrawLightChangePart
DESCRIBETION:绘制灯光页的可变部分(根据模式高亮不同按钮)
INPUT:int* num - 灯光状态数组
      LightMode mode - 当前灯光模式
RETURN:void
****************************************/
void DrawLightChangePart(int* num, LightMode mode)
{
    if (mode == EXTERNAL_LIGHTS)
    {
        // 高亮外部灯光按钮
        if (num[0])
        {  // 前大灯
            setfillstyle(1, GREEN);
            bar(151, 151, 249, 199);
            puthz(160, 170, "前大灯", 24, 26, LIGHTBLUE);
        }
        if (num[1])
        {  // 雾灯
            setfillstyle(1, GREEN);
            bar(151, 151+80, 249, 199+80);
            puthz(172, 170+80, "雾灯", 24, 26, LIGHTBLUE);
        }
        if (num[2])
        {  // 尾灯
            setfillstyle(1, GREEN);
            bar(151, 151+160, 249, 199+160);
            puthz(172, 170+160, "尾灯", 24, 26, LIGHTBLUE);
        }
        if (num[3])
        {  // 转向灯
            setfillstyle(1, GREEN);
            bar(151, 151+240, 249, 199+240);
            puthz(160, 170+240, "转向灯", 24, 26, LIGHTBLUE);
        }
    }
    else
    {
        // 高亮内部灯光按钮
        if (num[4])
        {  // 顶灯
            setfillstyle(1, GREEN);
            bar(151, 151, 249, 199);
            puthz(172, 170, "顶灯", 24, 26, LIGHTBLUE);
        }
        if (num[5])
        {  // 仪表灯
            setfillstyle(1, GREEN);
            bar(151, 151+80, 249, 199+80);
            puthz(160, 170+80, "仪表灯", 24, 26, LIGHTBLUE);
        }
        if (num[6])
        {  // 脚灯
            setfillstyle(1, GREEN);
            bar(151, 151+160, 249, 199+160);
            puthz(172, 170+160, "脚灯", 24, 26, LIGHTBLUE);
        }
        if (num[7])
        {  // 氛围灯
            setfillstyle(1, GREEN);
            bar(151, 151+240, 249, 199+240);
            puthz(160, 170+240, "氛围灯", 24, 26, LIGHTBLUE);
        }
    }
}

/****************************************
FUNCTION:PutLightHz
DESCRIBETION:显示灯光页汉字(根据模式显示不同标题)
INPUT:LightMode mode - 当前灯光模式
RETURN:void
****************************************/
void PutLightHz(LightMode mode)
{
    if (mode == EXTERNAL_LIGHTS)
    {
        puthz(175, 20, "外部灯光控制", 32, 54, LIGHTBLUE);
    }
    else {
        puthz(175, 20, "内部灯光控制", 32, 54, LIGHTBLUE);
    }
}
