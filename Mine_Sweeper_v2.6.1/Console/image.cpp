#include <stdio.h>
#include <windows.h>
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
#include "game.h"
#include "GameProcess.cpp"

//一些跟窗口操作有关的函数封装了全丢这里了……main函数太乱了
void WindowInit(int x, int y, HICON hIcon) {
	HWND hWnd = initgraph(x, y, NULL);
//	int ScrHeight = GetSystemMetrics(SM_CYSCREEN), ScrWidth = GetSystemMetrics(SM_CXSCREEN);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SetWindowPos(hWnd, HWND_TOP, 0, 0, x, y, SWP_NOSIZE);
	//不知道为什么MoveWindows()有问题，会使绘制的窗口略小一些，这里用了相同功能的函数SetWindowPos()然后忽略窗口大小参数（最后一个参数）
	SetWindowText(hWnd, _T("你说得对，但是扫雷是一款"));
}//初始化窗口

void ShowDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, IMAGE *DiffTitleImg,

              IMAGE *Tips) {
	ImageLoading2(Diff1, 1);
	ImageLoading2(Diff2, 2);
	ImageLoading2(Diff3, 3);
	ImageLoading2(Diff4, 4);
	loadimage(&ReturnMain[0], "ReturnMain.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
	loadimage(&ReturnMain[1], "ReturnMainDw.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
	ImageLoading3(Tips);
	putimage(DIFF_POS_W, DIFF_POS_I_H, &Diff1[0]);
	putimage(DIFF_POS_W, DIFF_POS_II_H, &Diff2[0]);
	putimage(DIFF_POS_W, DIFF_POS_III_H, &Diff3[0]);
	putimage(DIFF_POS_W, DIFF_POS_IV_H, &Diff4[0]);
	putimage(DIFF_POS_W, DIFF_POS_V_H, &ReturnMain[0]);
	putimage(TIPS_POS_W, TIPS_POS_H, &Tips[0]);
}//展示难度选项图片

int ChooseDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, MOUSEMSG tmsg) {
	int Diff = 0;
	if (tmsg.x >= DIFF_POS_W && tmsg.x <= DIFF_POS_W + DIFF_IMG_WIDTH && tmsg.y >= DIFF_POS_I_H
	        && tmsg.y <= DIFF_POS_I_H + DIFF_IMG_HEIGHT) {
		putimage(DIFF_POS_W, DIFF_POS_I_H, &Diff1[1]);
		if (tmsg.uMsg == WM_LBUTTONDOWN)
			Diff = 1;
	} else
		putimage(DIFF_POS_W, DIFF_POS_I_H, &Diff1[0]);
	if (tmsg.x >= DIFF_POS_W && tmsg.x <= DIFF_POS_W + DIFF_IMG_WIDTH && tmsg.y >= DIFF_POS_II_H
	        && tmsg.y <= DIFF_POS_II_H + DIFF_IMG_HEIGHT) {
		putimage(DIFF_POS_W, DIFF_POS_II_H, &Diff2[1]);
		if (tmsg.uMsg == WM_LBUTTONDOWN)
			Diff = 2;
	} else
		putimage(DIFF_POS_W, DIFF_POS_II_H, &Diff2[0]);
	if (tmsg.x >= DIFF_POS_W && tmsg.x <= DIFF_POS_W + DIFF_IMG_WIDTH && tmsg.y >= DIFF_POS_III_H
	        && tmsg.y <= DIFF_POS_III_H + DIFF_IMG_HEIGHT) {
		putimage(DIFF_POS_W, DIFF_POS_III_H, &Diff3[1]);
		if (tmsg.uMsg == WM_LBUTTONDOWN)
			Diff = 3;
	} else
		putimage(DIFF_POS_W, DIFF_POS_III_H, &Diff3[0]);
	if (tmsg.x >= DIFF_POS_W && tmsg.x <= DIFF_POS_W + DIFF_IMG_WIDTH && tmsg.y >= DIFF_POS_IV_H
	        && tmsg.y <= DIFF_POS_IV_H + DIFF_IMG_HEIGHT) {
		putimage(DIFF_POS_W, DIFF_POS_IV_H, &Diff4[1]);
		if (tmsg.uMsg == WM_LBUTTONDOWN)
			Diff = 4;
	} else
		putimage(DIFF_POS_W, DIFF_POS_IV_H, &Diff4[0]);
	return Diff;
}//响应鼠标（选择难度按钮）

void ShowBkGround(IMAGE *Tile) {
	srand((unsigned int)time(NULL));
	int **bkMap = InitMap(T_COL, T_ROW, 120), tCount = rand() % 20 + 200, tCol2, tRow2, tOpr;
	char **bkMapShow = InitMapShow(T_COL, T_ROW);
	if (bkMap == NULL || bkMapShow == NULL)
		return;
	//随机开格子
	while (tCount > 0) {
		tCol2 = rand() % T_COL + 1;
		tRow2 = rand() % T_ROW + 1;
		tOpr = rand() % 2;
		if (bkMap[tRow2][tCol2] == 0 && JudgeBoundary(tRow2, tCol2, T_ROW, T_COL) && bkMapShow[tRow2][tCol2] == '.') {
			switch (tOpr) {
				case 0: {
					SpreadMine(tRow2, tCol2, bkMap, bkMapShow, T_ROW, T_COL);
					break;
				}
				case 1: {
					CountMark(tCol2, tRow2, bkMapShow);
					break;
				}
			}
			tCount--;
		}
	}
	ShowMine(bkMap, bkMapShow, T_ROW, T_COL);
	DisplayMap(bkMapShow, 20, 30, Tile);
	for (int j = 0; j < 22; j++) {
		free(bkMap[j]);
		free(bkMapShow[j]);
	}
	free(bkMap);
	free(bkMapShow);
}//视觉效果：随机生成一个地图当作背景（已经弃用）