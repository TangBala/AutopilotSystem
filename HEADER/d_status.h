#ifndef D_STATUS_H
#define D_STATUS_H

void InitDriveStatus();//
void DrawDriveStatus();
void OpenDriveStatus();
int DriveStatusMouse(int* current_view);
void DrawSpeedGauge(int speed);
void ToggleEngine();//
char* GetEngineStatus();

#endif