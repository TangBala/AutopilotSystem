#ifndef _INIT_H_
#define _INIT_H_

#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include"hz.h"
#include"mouse.h"
#include"page.h"

void ClearGraph(void);
void Draw(int color);
void drawBezierCurve(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int color);
void DrawHomeMode(int* mode);
#include "d_mode.h"  // 包含模式定义

extern DriveMode current_mode;  // 全局模式变量

#endif