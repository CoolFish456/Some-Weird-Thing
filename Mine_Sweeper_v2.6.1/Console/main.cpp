/*********************************************************************
    ������: ��˵�öԣ�����ɨ����һ��
    ��Ȩ: ��������
    ����: ���饭��ɥ��ɥ�(CoolFish456)
    ����: 2023-06-07 18:36
    ˵��: �����Ż�����ȫ����
    ��Ҫ�Ķ����޸�һЩbug
*********************************************************************/
#include "image.cpp"
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
//��ֲʱע�⣺�������и�Ϊ����ͷ�ļ�#include <graphics.h>��ȷ����װeazyX��
//pragma��һ���൱��Ԥ�����м��� -llibEasyX -llibgdi32 -llibole32
//�ǵ�Ԥ�����ʱ�����-lwinmm�������ö�Ӧ��pragmaָ�����֮��#pragma comment(lib,"winmm.lib")����֪��Ϊʲô����仰�ܲ�������������ʹ�ò�����������
//�ҵı������ﻹ������-static-libstdc++ -static-libgcc
//�������ļ���Ч
//���У���֪��Ϊʲô����������ezsyx�汾ԭ�򣩣�һЩ��Ϣ������д����̫һ����EX-EM����ע�������ر���ע��һ��
O_GRADES tOG[10];

//��ȡǰʮ���ĳɼ����ṹ�壩
int main() {
	int Diff, MineNum = -1, row = 0, col = 0, **Map = NULL, *argRow, tLen = 0, isReturn = 0, isReturnMain = 1,
	          isShowRks = 1, tRTips = 0, tLeftClick = 0, isRetryMain = 1, isQuit; //���ֿ��Ƶı����������֣�
	/*
	isReturn�����ƴ��ѶȽ��浽�ѶȽ��棨��ֹ�Զ���������룩
	isReturnMain�����ƴ��ѶȽ��浽������
	isShowRks�����ƴ���Ϸ���浽���а����
	isRetryMain��isQuit�������Ƿ������Ϸ
	����˳���ո�Ҫ�е����
	*/
	char **MapShow = NULL;
	IMAGE Tile[13], TitleImg, ReturnTitleImg, Rks, bkDiff;
	IMAGE Diff1[2], Diff2[2], Diff3[2], Diff4[2], ReturnMain[2], DiffTitleImg, Tips[50];
	char filename[100] = {0}, Rk[10] = {0};//ʤ��
	char GetLine[150] = {0};//��ȡ��ÿһ��
	HWND hWnd;
	HICON hIcon = ExtractIcon(NULL, _T("MineSweeper.ico"), 0);
	MOUSEMSG tmsg;
	if (hIcon == NULL)
		return 114514;
	ImageLoading(filename, Tile);
	loadimage(&TitleImg, "start.jpg", 400, 400);
	loadimage(&bkDiff, "bkDiff.jpg", 0, 0);
	loadimage(&Rks, "Rks.jpg", 400, 100);
	//��һ�����ڣ������汳������ʼ
	while (isRetryMain) {
		isReturnMain = 1;
		while (isReturnMain) {
			WindowInit(WINDOWS_MAIN_W, WINDOWS_MAIN_H, hIcon);
			putimage(0, 0, &TitleImg);
			if (!InputBox(tGrade.name, 100, _T("�������ϡ���ֻ������Ӣ�ģ�������һ�ٸ���ĸ��"), _T("��ӭ����ɨ��~"),
			              "Developer_COOL", 0, 0,
			              false)) {
				MessageBox(NULL, "�ѵ�����������ֶ�����֪����QWQ", "�����ˣ�", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
				return 114514;
			}
			tLen = strlen(tGrade.name);
			tGrade.name[tLen] = '\0';
			closegraph();
			//��һ�����ڣ������汳��������
			//�ڶ������ڣ�ѡ���Ѷȣ���ʼ
			WindowInit(WINDOWS_DIFF_W, WINDOWS_DIFF_H, hIcon);
			putimage(0, 0, &bkDiff);
			ShowDiff(Diff1, Diff2, Diff3, Diff4, ReturnMain, &DiffTitleImg, Tips);
			isReturn = 0;
			while (isReturn == 0) {
				MOUSEMSG tmsg = GetMouseMsg();
				Diff = ChooseDiff(Diff1, Diff2, Diff3, Diff4, ReturnMain, tmsg);
				if (tmsg.x >= DIFF_POS_W && tmsg.x <= DIFF_POS_W + DIFF_IMG_WIDTH && tmsg.y >= DIFF_POS_V_H
				        && tmsg.y <= DIFF_POS_V_H + DIFF_IMG_HEIGHT) {
					putimage(DIFF_POS_W, DIFF_POS_V_H, &ReturnMain[1]);
					if (tmsg.uMsg == WM_LBUTTONDOWN) {
						isReturnMain = 1;
						break;
					}
				} else
					putimage(DIFF_POS_W, DIFF_POS_V_H, &ReturnMain[0]);
				if (tmsg.x >= SENPAI_POS_W && tmsg.x <= SENPAI_POS_W + SENPAI_WIDTH && tmsg.y >= SENPAI_POS_H
				        && tmsg.y <= SENPAI_POS_H + SENPAI_HEIGHT && tmsg.uMsg == WM_LBUTTONDOWN) {
					srand((unsigned int)time(NULL));
					PlaySound(_T("Tips.wav"), NULL, SND_ASYNC);
					int tRTips2 = tRTips;
					while (tRTips2 == tRTips)
						tRTips = rand() % TIPS_NUM + 1;
					putimage(TIPS_POS_W, TIPS_POS_H, &Tips[tRTips]);
					tLeftClick++;
				}
				if (tLeftClick >= 100) {
					MessageBox(NULL, _T("���Ѿ�����ȱ�����100�Σ����е�̫���ȱ���"), _T("�㱻�����ˣ�"),
					           MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
					return 114518;
				}
				isReturn = DetDiff(Diff, &col, &row, &MineNum);
				isReturnMain = 0;
			}
		}
		closegraph();
		//�ڶ������ڣ�ѡ���Ѷȣ�����
		argRow = &row;
		MapShow = InitMapShow(col, row);
		Map = InitMap(col, row, MineNum);
		//���������ڣ���Ϸ���棩��ʼ
		WindowInit(WINDOWS_GAME_W, WINDOWS_GAME_H, hIcon);
		setbkcolor(RGB(191, 191, 191));
		cleardevice();
		LOGFONT f;//����ṹ��
		SetFont(f, 16);
		setlinecolor(RGB(191, 191, 191));
		setfillcolor(RGB(191, 191, 191));
		isShowRks = FindMine(Map, MapShow, row, col, MineNum, Tile, Diff);
		DisplayMap(MapShow, row, col, Tile);
		//չʾʤ��
		while (1) {
			MOUSEMSG tmsg = GetMouseMsg();
			if (tmsg.uMsg == WM_LBUTTONDOWN) {
				if (tmsg.x >= (col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2 && tmsg.y >= row * IMG_SIZE + 10
				        && tmsg.x <= (col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 && tmsg.y <= row * IMG_SIZE + 10 + IS_WIN_IMG_SIZE) {
					MessageBox(NULL, "�����У����Եȡ���", "������", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
					RankScore(Diff);
					isShowRks = 1;
					break;
				} else {
					isShowRks = 0;
					break;
				}
			}
		}
		closegraph();
		flushmessage(EM_MOUSE);
		//���������ڣ���Ϸ���棩����
		//���ĸ����ڣ����а񣩿�ʼ
		if (isShowRks) {
			FILE *RkP, *GradeImfo;
			char tIndex[3], tTime[10];
			WindowInit(WINDOWS_RANK_W, WINDOWS_RANK_H, hIcon);
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			putimage(0, 0, &Rks);
			if (Diff == 3 || Diff == 4)
				SetFont(f, 28);
			else
				SetFont(f, 36);
			RkP = fopen("RankP.txt", "r");
			switch (Diff) {
				case 1: {
					GradeImfo = fopen("Diff1\\sorted_ranking1.csv", "r");
					break;
				}
				case 2: {
					GradeImfo = fopen("Diff2\\sorted_ranking2.csv", "r");
					break;
				}
				case 3: {
					GradeImfo = fopen("Diff3\\sorted_ranking3.csv", "r");
					break;
				}
				default: {
					break;
				}
			}
			if (RkP == NULL)
				return 114515;
			if (fgets(Rk, 6, RkP) != NULL) {
				outtextxy(0, 100, _T("ʤ�ʣ�"));
				outtextxy(200, 100, Rk);
				outtextxy(200 + 36 * 2 + 18, 100, "%");
			}//��ȡʤ��
			if (Diff != 4 && GradeImfo == NULL)
				return 114517;
			rewind(GradeImfo);
			fgets(GetLine, 149, GradeImfo); //��ȡ��һ�в�����
			for (int i = 1; i <= 10; i++) {
				memset(GetLine, 0, sizeof(GetLine));
				tOG[i - 1].Index = i;
				if (fgets(GetLine, 149, GradeImfo) == NULL)
					break;
				strcpy(tOG[i - 1].name, strtok(GetLine, ","));
				sscanf(strtok(NULL, ","), "%d", &tOG[i - 1].using_time);//Ϊʲô��NULL???
				sprintf(tIndex, "%d", tOG[i - 1].Index);
				sprintf(tTime, "%d", tOG[i - 1].using_time);
				outtextxy(0, 100 + 50 * i, tIndex);
				outtextxy(40, 100 + 50 * i, tOG[i - 1].name);
				outtextxy(400 - 18 * 3, 100 + 50 * i, tTime);
			}
			//��ֹ�����
			while (1) {
				tmsg = GetMouseMsg();
				if (tmsg.uMsg == WM_LBUTTONDOWN && tmsg.x >= 0 && tmsg.y >= 0 && tmsg.x <= 400 && tmsg.y <= 100) {
					isRetryMain = 0;
					break;
				} else if (tmsg.uMsg == WM_LBUTTONDOWN) {
					isQuit = MessageBox(NULL, _T("�Ƿ����¿�ʼ��"), _T("����������"), MB_OKCANCEL | MB_ICONQUESTION);
					if (isQuit != IDOK)
						continue;
					else
						break;
				}
			}
			//�ٰ�һ���������˳�
			closegraph();
			fclose(RkP);
			fclose(GradeImfo);
		} else {
			isRetryMain = 0;
		}
		for (int j = 0; j < row + 2; j++) {
			free(Map[j]);
			free(MapShow[j]);
		}
		free(Map);
		free(MapShow);//��βfree��׼������/������һ��
	}
	//���ĸ����ڣ����а񣩽���
	return 0;
}