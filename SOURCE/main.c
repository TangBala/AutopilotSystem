/**
**************************************************?
*	�汾�ţ�1.0
*	���ߣ�X
*	�������ڣ�2024-2-28
*	˵����Main��������������
**************************************************?
**/

#include<graphics.h>
#include"init.h"
#include"page.h"


int main()
{
	int gd = VGA, gm = VGAHI; 
	initgraph(&gd, &gm, "..\\BORLANDC\\BGI");
	//setrgbpalette(LIGHTBLUE, 1, 4, 9);//BLACK
	setrgbpalette(BLACK, 1, 4, 9);//BLACK
	setpalette(9, LIGHTBLUE);  // LIGHTBLUE������9��
	//setrgbpalette(LIGHTBLUE, 0, 228, 255);//δ��ɫ��LIGHTCYAN
	//setrgbpalette(LIGHTBLUE, 0, 242, 255);//��Ŀ���
	setrgbpalette(LIGHTBLUE, 214, 243, 255);//�嵭���
	mouseinit();
	clrmous(MouseX, MouseY);
	while(1)
	{
		ClearGraph();
		OpenMainPage();		
	}
}
