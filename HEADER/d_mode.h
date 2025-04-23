#ifndef _D_MODE_H
#define _D_MODE_H

void OpenDrivemode(void);
void DrawModeButton(int num);
int ModeMouse(int *num);
typedef enum {
    MODE_A = 0,  // 手动模式
    MODE_B = 1,  // 辅助模式
    MODE_C = 2   // 自动模式
} DriveMode;

extern DriveMode current_mode;

#endif