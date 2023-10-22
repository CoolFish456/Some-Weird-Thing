#ifndef __GAME_H__
#define __GAME_H__
//�������к����ͺ궨��
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
//��ֲʱע�⣺�������и�Ϊ����ͷ�ļ�#include <graphics.h>��ȷ����װeazyX��
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
void Plot1();//���Ѿ����ã�
//StoryTelling.cpp
void WindowInit(int x, int y, HICON hIcon);
void ShowDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, IMAGE *DiffTitleImg,
              IMAGE *Tips);
int ChooseDiff(IMAGE *Diff1, IMAGE *Diff2, IMAGE *Diff3, IMAGE *Diff4, IMAGE *ReturnMain, MOUSEMSG tmsg);
void ShowBkGround(IMAGE *Tile);
//image.cpp
//��ͬ�Ѷȣ��������߼����µ�ͼ�������ݵ����ã�
//����
#define EASY_ROW 9
#define EASY_COL 9
#define EASY_MINE 10
//�м�
#define MED_ROW 16
#define MED_COL 16
#define MED_MINE 40
//�߼�
#define HIGH_ROW 16
#define HIGH_COL 30
#define HIGH_MINE 99
//�����Ӯ�ĳ���
#define WIN 1
#define LOSE 0
#define PROCESS 2
//ͼƬ��С
#define IMG_SIZE 35
#define IS_WIN_IMG_SIZE 40
#define DIFF_IMG_WIDTH 221
#define DIFF_IMG_HEIGHT 46
#define TIPS_WIDTH 299
#define TIPS_HEIGHT 86
#define SENPAI_WIDTH 302
#define SENPAI_HEIGHT 272
//ѡ�ؽ���ͼƬλ��
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
//���ڴ�С
#define WINDOWS_MAIN_W 400
#define WINDOWS_MAIN_H 400
#define WINDOWS_DIFF_W 360
#define WINDOWS_DIFF_H 720
#define WINDOWS_GAME_W col * IMG_SIZE
#define WINDOWS_GAME_H row * IMG_SIZE + 60
#define WINDOWS_RANK_W 400
#define WINDOWS_RANK_H 650
//���������ĳ��������ã�
#define T_COL 30
#define T_ROW 20

//�û��ɼ���Ϣ�ṹ��
typedef struct Grades {
	char name[114]; //�û���
	int using_time; //ʱ��
	int Winning;//��Ӯ
	int Diff;//�Ѷ�
} GRADES;

//��������ĳɼ���Ϣ
typedef struct OutGrades {
	int Index;//����
	char name[114];
	int using_time;
} O_GRADES;
#endif