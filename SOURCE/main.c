/**
**************************************************?
*	版本号：1.0
*	作者：X
*	生成日期：2024-2-28
*	说明：Main函数（主函数）
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
	setpalette(9, LIGHTBLUE);  // LIGHTBLUE（索引9）
	//setrgbpalette(LIGHTBLUE, 0, 228, 255);//未调色的LIGHTCYAN
	//setrgbpalette(LIGHTBLUE, 0, 242, 255);//夺目风格
	setrgbpalette(LIGHTBLUE, 214, 243, 255);//清淡风格
	mouseinit();
	clrmous(MouseX, MouseY);
	while(1)
	{
		ClearGraph();
		OpenMainPage();		
	}
}
