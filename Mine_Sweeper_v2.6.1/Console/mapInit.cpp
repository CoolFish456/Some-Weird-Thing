#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")

void ImageLoading(char *filename, IMAGE *Tile) {
	for (int i = 0; i <= 9; i++) {
		filename[0] = '0' + i;
		strcpy(filename + 1, ".jpg");
		loadimage(&Tile[i], (LPCTSTR)filename, IMG_SIZE, IMG_SIZE);
	}
	loadimage(&Tile[10], "10.jpg", IMG_SIZE, IMG_SIZE);
	loadimage(&Tile[11], "11.jpg", IMG_SIZE, IMG_SIZE);
	loadimage(&Tile[12], "12.jpg", IMG_SIZE, IMG_SIZE);
}

void ImageLoading2(IMAGE *img, int Diff) {
	switch (Diff) {
		case 1: {
			loadimage(&img[0], "Diff1.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			loadimage(&img[1], "DiffDw1.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			break;
		}
		case 2: {
			loadimage(&img[0], "Diff2.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			loadimage(&img[1], "DiffDw2.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			break;
		}
		case 3: {
			loadimage(&img[0], "Diff3.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			loadimage(&img[1], "DiffDw3.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			break;
		}
		case 4: {
			loadimage(&img[0], "Diff4.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			loadimage(&img[1], "DiffDw4.jpg", DIFF_IMG_WIDTH, DIFF_IMG_HEIGHT);
			break;
		}
	}
}

void ImageLoading3(IMAGE *img) {
	char filename[50] = {0};
	for (int i = 0; i <= TIPS_NUM; i++) {
		sprintf(filename, "tips%d.jpg", i);
		loadimage(&img[i], filename, TIPS_WIDTH, TIPS_HEIGHT);
//		printf("%s\n", filename);
		memset(filename, '\0', sizeof(filename));
	}
}

//图片载入（三个，只是简单的封装）
void SetFont(LOGFONT f, int Height) {
	gettextstyle(&f);
	f.lfHeight = Height;
	_tcscpy(f.lfFaceName, _T("宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(RGB(0, 0, 0));
}

//字体设置
int DetDiff(int Diff, int *x, int *y, int *MineNum) {
	int isReturn = 0;//1代表操作合法
	switch (Diff) {
		case 1: {//Eazy
			*x = EASY_COL;
			*y = EASY_ROW;
			*MineNum = EASY_MINE;
			isReturn = 1;
			break;
		}
		case 2: {//Normal
			*x = MED_COL;
			*y = MED_ROW;
			*MineNum = MED_MINE;
			isReturn = 1;
			break;
		}
		case 3: {//Hard
			*x = HIGH_COL;
			*y = HIGH_ROW;
			*MineNum = HIGH_MINE;
			isReturn = 1;
			break;
		}
		case 4: {//Other
			char chx[3], chy[3], chmm[3];
			InputBox(chx, 4, _T("请输入雷区的宽度~"), _T("自定义Time~"), "0");
			InputBox(chy, 4, _T("请输入雷区的高度~"), _T("自定义Time~"), "0");
			InputBox(chmm, 4, _T("请输入雷区的雷数~"), _T("自定义Time~"), "0");
			sscanf(chx, "%d", x);
			sscanf(chy, "%d", y);
			sscanf(chmm, "%d", MineNum);
			if (*MineNum >= (*x) * (*y) || *x >= 30 || *y >= 24 || x == NULL || y == NULL || MineNum == NULL) {
				MessageBox(NULL, _T("你有点太极端了！"), _T("一次警告"), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
				isReturn = 0;
			} else
				isReturn = 1;
			break;
		}
		default: {
			isReturn = 0;
			break;
		}
	}
	return isReturn;
}
//难度设置函数
char **InitMapShow(int x, int y) {
	char **ptrMapShow = (char **)malloc((y + 2) * sizeof(char *));

	if (ptrMapShow) {
		for (int i = 0; i < y + 2; i++) {
			ptrMapShow[i] = (char *)malloc((x + 2) * sizeof(char));
		}
		for (int i = 0; i < y + 2; i++) {
			for (int j = 0; j < x + 2; j++) {
				ptrMapShow[i][j] = '.';
			}
		}

	}
	return ptrMapShow;
}
int **InitMap(int x, int y, int Mine) {
	srand((unsigned int)time(NULL));
	char temp;
	int count = Mine;
	int **ptrMap = (int **)malloc((y + 2) * sizeof(int *));
	if (ptrMap) {

		for (int i = 0; i < y + 2; i++) {
			ptrMap[i] = (int *)malloc((x + 2) * sizeof(int));
		}

		for (int i = 0; i < y + 2; i++) {
			for (int j = 0; j < x + 2; j++) {
				ptrMap[i][j] = 0;
			}
		}
		MineGenerate(ptrMap, x, y, count);
	}
	return ptrMap;
}
void MineGenerate(int **Map, int Col, int Row, int Mine) {
	while (Mine > 0) {
		int xInput = rand() % Col + 1;
		int yInput = rand() % Row + 1;
		if (Map[yInput][xInput] == 0 && xInput >= 1 && yInput >= 1 && xInput <= Col && yInput <= Row) {
			Map[yInput][xInput] = 1;
			Mine--;
		}
//			printf("%d %d %d\n", tRow, tCol, count);
//			Sleep(100);
		if (Mine <= 0)
			break;
	}//随机生成雷
}
//生成雷区相关函数
void DisplayMap(char **MapShow, int Row, int Col, IMAGE *img) {
	int tShowNum = 0;
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
//			printf("%c ", MapShow[i][j]);

			switch (MapShow[i][j]) {

				case '.': {
					putimage((j - 1) * IMG_SIZE, (i - 1) * IMG_SIZE, &img[10]);
					break;
				}

				case '*': {
					putimage((j - 1) * IMG_SIZE, (i - 1) * IMG_SIZE, &img[9]);
					break;
				}

				case '!': {
					putimage((j - 1) * IMG_SIZE, (i - 1) * IMG_SIZE, &img[11]);
					break;
				}

				case '?': {
					putimage((j - 1) * IMG_SIZE, (i - 1) * IMG_SIZE, &img[12]);
					break;
				}

				default: {
					tShowNum = MapShow[i][j] - '0';
					putimage((j - 1) * IMG_SIZE, (i - 1) * IMG_SIZE, &img[tShowNum]);
					break;
				}
			}
		}
//		printf("%d\n", i);
//		printf("\n");
	}
	/*	for (int j = 1; j <= Col; j++)
			printf("%d ", j);*/
//	printf("\n");
}
void ShowMine(int **Map, char **MapShow, int Row, int Col) {
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			if (Map[i][j] == 1)
				MapShow[i][j] = '*';
			else if (Map[i][j] == 0 && MapShow[i][j] == '*') {
				MapShow[i][j] = '.';
			}
		}
	}
}
//输出函数
void RankScore(int Diff) {
	switch (Diff) {
		case 1: {
			system("Sort_csv.exe 1");//对目标csv文件排序，调用外部程序并传参（使用python编写，传参的方法：from sys import argv）
			break;
		}
		case 2: {
			system("Sort_csv.exe 2");
			break;
		}
		case 3: {
			system("Sort_csv.exe 3");
			break;
		}
		default: {
			break;
		}
	}
}
//处理数据