/* light.h */
#ifndef LIGHT_H
#define LIGHT_H

// �ƹ�ģʽö��
typedef enum {
    EXTERNAL_LIGHTS,  // �ⲿ�ƹ�ģʽ
    INTERNAL_LIGHTS   // �ڲ��ƹ�ģʽ
} LightMode;

// �ƹ����Ƚṹ��

typedef struct {
    int level[5]; // ÿ���ƹ�����ȼ��� 0-3
    int current_light; // ��ǰѡ�еĵƹ�����
} LightBrightness;
// ��������
void OpenLight();
void DrawLightSButton(LightMode mode);
void DrawLightChangePart(int* num, LightMode mode);
void PutLightHz(LightMode mode);
int LightMouse(LightMode* mode,int*ischange);
void DrawBrightnessBar(int x, int y, int level);

#endif