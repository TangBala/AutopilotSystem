#ifndef _MAP_H_
#define _MAP_H_

void DrawMap(void);
void DrawRoad(void);
void DrawRoad(void);
void DrawParallelRoad(int x, int y, int d);
void DrawVerticalRoad(int x, int y, int d);
void DrawCrossing(int x, int y, int north, int south, int west, int east);
void DrawBuilding(void);
//void DrawSouthBuildingOne(void);
//void DrawParkingLot(void);
int GetBuildingByPoint(int x, int y);
void HandleMouseSelection(void);
//void PutUpperHz();
#endif