#ifndef _D_MODE_H
#define _D_MODE_H

void OpenDrivemode(void);
void DrawModeButton(int num);
int ModeMouse(int *num);
typedef enum {
    MODE_A = 0,  // �ֶ�ģʽ
    MODE_B = 1,  // ����ģʽ
    MODE_C = 2   // �Զ�ģʽ
} DriveMode;

extern DriveMode current_mode;

#endif