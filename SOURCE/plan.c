/**
**************************************************?
*   版本号：1.0
*   作者：X
*   生成日期：2024—3—30
*   说明：Plan类函数实现路径规划功能
**************************************************?
**/

#include<graphics.h>
#include<stdio.h>
#include"plan.h"
#define MAX 9999
#define N 26
char* buildingNames[] = {
    "紫菘", "居民区", "西操", "西十二", "科技楼",
    "主图", "师生", "东九", "东操", "启明楼",
    "东图", "韵九", "韵苑" "请选择"
};//13+1

/****************************************
FUNCTION:PlanPath
DESCRIBETION:规划路线
INPUT:int start, int end
RETURN:int
****************************************/
int PlanPath(int start, int end)
{
    int distance[N][N] =
    {
        //0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
       {  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,25},  // 0
       {MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,MAX, 25,MAX, 60,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  // 1
       {MAX,MAX,  0,MAX,MAX, 25,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX,MAX, 25,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  // 2
       {MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 10, 50,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50},  // 3
       {MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  // 4
       {MAX,MAX, 25,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,MAX,MAX, 50,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  // 5
       {MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  // 6
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,MAX,MAX, 25,MAX,MAX,MAX,MAX},  // 7
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 60, 25,MAX,MAX,MAX},  // 8
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,MAX,MAX, 25,MAX,MAX,MAX,MAX},  // 9
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX, 25,MAX},  //10
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX},  //11
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX},  //12
       {MAX, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0,MAX,MAX,25,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,50},  //13
       {MAX,MAX,25, 10, MAX,50, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,  0, 25,MAX, 50,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50},  //14
       {MAX,MAX,MAX,50, 25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 25,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  //15
       {MAX,25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,25, MAX,MAX,  0, 50, 25,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  //16
       {MAX,MAX,25, MAX,MAX, 50,25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,50,MAX, 50,  0,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},  //17
       {MAX,60, MAX,MAX,MAX,MAX,MAX, 50,MAX, 50,MAX,MAX,MAX,MAX,MAX,MAX, 25,MAX,  0, 50,MAX, 50,MAX, 75,MAX,MAX},  //18
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,  0, 50,MAX,MAX,MAX,MAX,MAX},  //19
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,  0, 50,MAX,MAX,MAX,MAX},  //20
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,25, 60, 25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,MAX, 50,  0, 30,MAX,MAX,MAX},  //21
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,25, MAX, 25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 30,  0,MAX, 50,MAX},  //22
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 75,MAX,MAX,MAX,MAX,  0,100,MAX},  //23
       {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,25, 25, 25, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 50,100,  0,MAX},  //24
       {25, MAX,MAX,50, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,50, 50, MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX, 0 },  //25
    };
    return Dijkstra(start, end, distance);
}

/****************************************
FUNCTION:Dijkstra
DESCRIBETION:实现迪杰斯特拉算法
INPUT:int start, int end, int distance[][34]
RETURN:int
****************************************/
int Dijkstra(int start, int end, int distance[][26])
{
    int start_distance[N], vertex[N] = { 0 };
    int i, u, v;
    FILE* path_text;
    PathNode path_node[N], * temp = &path_node[end];

    for (i = 0; i < N; i++)
    {
        start_distance[i] = MAX;
        path_node[i].node = i;
        path_node[i].next = NULL;
    }
    start_distance[start] = 0;

    while (!vertex[end])
    {
        u = MinDistance(start_distance, vertex);
        vertex[u] = 1;



        for (v = 0; v < N; v++)
        {
            if ((u != 5 && u != 8 && start != 5 && start != 8) || start == 5 || start == 8)
            {
                if (!vertex[v] && distance[u][v] != MAX && start_distance[u] + distance[u][v] < start_distance[v])
                {
                    start_distance[v] = start_distance[u] + distance[u][v];
                    path_node[v].next = &path_node[u];
                }
            }
        }
    }

    path_text = fopen("..\\CODE\\text\\path.txt", "wt");
    do
    {
        fprintf(path_text, "%d %d ", (*temp).node, distance[(*temp).node][(*((*temp).next)).node]);
        temp = (*temp).next;
    } while ((*temp).next != NULL);
    fprintf(path_text, "%d %d ", start, 1000);
    fclose(path_text);
    return start_distance[end];
}

/****************************************
FUNCTION:MinDistance
DESCRIBETION:返回尚未包含在最短路径树中的最小距离的顶点的索引
INPUT:int* distance, int* vertex
RETURN:int
****************************************/
int MinDistance(int* start_distance, int* vertex)
{
    int min = MAX, min_index, v;

    for (v = 0; v < N; v++)
        if (vertex[v] == 0 && start_distance[v] <= min)
            min = start_distance[v], min_index = v;

    return min_index;
}
/****************************************
FUNCTION:DrawRoute
DESCRIBETION:绘制路线
INPUT:void
RETURN:void
****************************************/
void DrawRoute()
{
    int place[26] = { 0 }, i = -1;//?
    int x_1, x_2, y_1, y_2;
    FILE* path_text;
    path_text = fopen("..\\CODE\\text\\path.txt", "rt");
    do
    {
        i++;
        fscanf(path_text, "%d %d ", &place[i], &place[i + 1]);
    } while (place[i + 1] != 1000);
    fclose(path_text);

    i = 0;
    setcolor(BLUE);
    DrawStartEnd(place[i]);     //end
    //PutHz(180+30, 80-10, 2, place[i]);
    puthz(270+20, 70, buildingNames[place[i]], 24, 25, WHITE);

    while (place[i + 1] != 1000)
    {
        ReturnCoordinates(i, place, &x_1, &y_1);
        ReturnCoordinates(i + 1, place, &x_2, &y_2);
        line(x_1, y_1, x_2, y_2);
        i++;
    }
    //PutUpperHz(start, end);
    puthz(100+20, 70, buildingNames[place[i]], 24, 25, WHITE);
    setfillstyle(1, RED);
    setcolor(RED);
    bar(550, 82 - 14, 620, 82 + 14);
    puthz(560, 70, "导航", 24, 25, WHITE);
    //PutHz(40,80-10, 1, place[i]);
    DrawStartEnd(place[i]);     //start
    return;

}

/****************************************
FUNCTION:ReturnCoordinates
DESCRIBETION:返回路线的坐标
INPUT:int i, int* place, int* x, int* y
RETURN:void
****************************************/
void ReturnCoordinates(int i, int* place, int* x, int* y)
{
    switch (place[i])
    {
    case 0:
        *x = 100, *y = 240;//紫菘
        break;
    case 1:
        *x = 270, *y = 240;
        break;
    case 2:
        *x = 200, *y = 320;
        break;
    case 3:
        *x = 110, *y = 310;
        break;
    case 4:
        *x = 70, *y = 360;
        break;
    case 5:
        *x = 200, *y = 320;
        break;
    case 6:
        *x = 280, *y = 330;
        break;
    case 7:
        *x = 400, *y = 240;
        break;
    case 8:
        *x = 540, *y = 240;
        break;
    case 9:
        *x = 440, *y = 240;
        break;
    case 10:
        *x = 530, *y = 290;
        break;
    case 11:
        *x = 530, *y = 410;
        break;
    case 12:
        *x = 530, *y = 405;
        break;
    case 13:
        *x = 205, *y = 240;
        break;
    case 14:
        *x = 125, *y = 320;
        break;
    case 15:
        *x = 125, *y = 360;
        break;
    case 16:
        *x = 280, *y = 240;
        break;
    case 17:
        *x = 280, *y = 320;
        break;
    case 18:
        *x = 340, *y = 240;
        break;
    case 19:
        *x = 340, *y = 180;
        break;
    case 20:
        *x = 450, *y = 180;
        break;
    case 21:
        *x = 450, *y = 240;
        break;
    case 22:
        *x = 530, *y = 240;
        break;
    case 23:
        *x = 340, *y = 340;
        break;
    case 24:
        *x = 530, *y = 340;
        break;
    case 25:
        *x = 125, *y = 240;
        break;
    }

    return;
}

/****************************************
FUNCTION:DrawStartEnd
DESCRIBETION:绘制起点或终点处的路线
INPUT:int num
RETURN:void
****************************************/
void DrawStartEnd(int num)
{
    setcolor(GREEN);
    switch (num)
    {
    case 0:
        line(100, 230, 100, 240);
        break;
    case 1:
        line(270, 230, 270, 240);
        break;
    case 2:
        line(200, 315, 200, 325);
        break;
    case 3:
        line(110, 310, 110, 320);
        break;
    case 4:
        line(70, 360, 70, 380);
        break;
    case 5:
        line(200, 320, 200, 350);
        break;
    case 6:
        line(290, 320, 290, 330);
        break;
    case 7:
        line(400, 220, 400, 230);
        break;
    case 8:
        line(540, 230, 540, 240);
        break;
    case 9:
        line(440, 240, 440, 250);
        break;
    case 10:
        line(535, 290, 545, 290);
        break;
    case 11:
        line(510, 410, 520, 410);
        break;
    case 12:
        line(535, 405, 545, 405);
        break;
    }
}