#ifndef __GAME_H__
#define __GAME_H__
//声明所有函数和宏定义
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
//移植时注意：将这两行改为声明头文件#include <graphics.h>，确保安装eazyX库
int DetDiff(int Diff, int *x, int *y, int *MineNum);
int **InitMap(int col, int row, int Mine);
char **InitMapShow(int col, int row);
void DisplayMap(char **MapShow, int Row, int Col, IMAGE *img);
void MineGenerate(int **Map, int Col, int Row, int Mine);
void ShowMine(int **Map, char **MapShow, int Row, int Col);
void ImageLoading(char *filename, IMAGE *Tile);
void ImageLoading2(IMAGE *img, int Diff);
void SetFont(LOGFONT f, int Height);
void RankScore(int Diff);
//mapInit.cpp
int JudgeBoundary(int yInput, int xInput, int Row, int Col);
int JudgeNear(int x, int y, int xInput, int yInput);
int CountMine(int xInput, int yInput, int **Map);
int MarkMine(int xInput, int yInput, int Action, char **MapShow, int **Map);
int CountMark(int xInput, int yInput, char **MapShow);
void SpreadMine(int xInput, int yInput, int **Map, char **MapShow, int Row, int Col);
void DoubleClickOn(char **MapShow, int xInput, int yInput, IMAGE *img, MOUSEMSG msg, int Row);
int GameWin(int **Map, char **MapShow, int Row, int Col, int Mine);
int FindMine(int **Map, char **MapShow, int Row, int Col, int Mine, IMAGE *img, int Diff);
void PrintWin(int isWin, IMAGE *img, int Col, int Row);
void TimeCount(void *);
//GameProcess.cpp
void Plot1();//（已经弃用）
//StoryTelling.cpp
void WindowInit(int x, int y, HICON hIcon);
void ShowDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, IMAGE *DiffTitleImg,
              IMAGE *Tips);
int ChooseDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, MOUSEMSG tmsg);
void ShowBkGround(IMAGE *Tile);
//image.cpp
//不同难度（初级到高级）下地图各项数据的设置：
//初级
#define EASY_ROW 9
#define EASY_COL 9
#define EASY_MINE 10
//中级
#define MED_ROW 16
#define MED_COL 16
#define MED_MINE 40
//高级
#define HIGH_ROW 16
#define HIGH_COL 30
#define HIGH_MINE 99
//检测输赢的常量
#define WIN 1
#define LOSE 0
#define PROCESS 2
//图片大小
#define IMG_SIZE 35
#define IS_WIN_IMG_SIZE 40
#define DIFF_IMG_WIDTH 221
#define DIFF_IMG_HEIGHT 46
#define TIPS_WIDTH 299
#define TIPS_HEIGHT 86
#define SENPAI_WIDTH 302
#define SENPAI_HEIGHT 272
//选关界面图片位置
#define DIFF_POS_W 69
#define DIFF_POS_I_H 439
#define DIFF_POS_II_H 491
#define DIFF_POS_III_H 544
#define DIFF_POS_IV_H 598
#define DIFF_POS_V_H 651
#define TIPS_POS_W 28
#define TIPS_POS_H 333
#define TIPS_NUM 25
#define SENPAI_POS_W 28
#define SENPAI_POS_H 52
//窗口大小
#define WINDOWS_MAIN_W 400
#define WINDOWS_MAIN_H 400
#define WINDOWS_DIFF_W 360
#define WINDOWS_DIFF_H 720
#define WINDOWS_GAME_W col * IMG_SIZE
#define WINDOWS_GAME_H row * IMG_SIZE + 60
#define WINDOWS_RANK_W 400
#define WINDOWS_RANK_H 650
//背景雷区的长宽（已弃用）
#define T_COL 30
#define T_ROW 20

//用户成绩信息结构体
typedef struct Grades {
	char name[114]; //用户名
	int using_time; //时间
	int Winning;//输赢
	int Diff;//难度
} GRADES;

//用于输出的成绩信息
typedef struct OutGrades {
	int Index;//列数
	char name[114];
	int using_time;
} O_GRADES;
#endif