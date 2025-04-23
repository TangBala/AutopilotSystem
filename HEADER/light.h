/* light.h */
#ifndef LIGHT_H
#define LIGHT_H

// 灯光模式枚举
typedef enum {
    EXTERNAL_LIGHTS,  // 外部灯光模式
    INTERNAL_LIGHTS   // 内部灯光模式
} LightMode;

// 灯光亮度结构体

typedef struct {
    int level[5]; // 每个灯光的亮度级别 0-3
    int current_light; // 当前选中的灯光索引
} LightBrightness;
// 函数声明
void OpenLight();
void DrawLightSButton(LightMode mode);
void DrawLightChangePart(int* num, LightMode mode);
void PutLightHz(LightMode mode);
int LightMouse(LightMode* mode,int*ischange);
void DrawBrightnessBar(int x, int y, int level);

#endif