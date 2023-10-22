/*********************************************************************
    程序名: 你说得对，但是扫雷是一款
    版权: ————
    作者: キラキラドキドキ(CoolFish456)
    日期: 2023-06-07 18:36
    说明: 美术优化，补全动线
    主要改动：修复一些bug
*********************************************************************/
#include "image.cpp"
#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
//移植时注意：将这两行改为声明头文件#include <graphics.h>，确保安装eazyX库
//pragma这一句相当于预编译中加入 -llibEasyX -llibgdi32 -llibole32
//记得预编译的时候加入-lwinmm，或者用对应的pragma指令替代之（#pragma comment(lib,"winmm.lib")（不知道为什么我这句话跑不动））以正常使用播放声音功能
//我的编译器里还加入了-static-libstdc++ -static-libgcc
//对所有文件有效
//还有，不知道为什么（可能是我ezsyx版本原因），一些消息常量的写法不太一样（EX-EM），注如果有相关报错注意一下
O_GRADES tOG[10];

//读取前十名的成绩（结构体）
int main() {
	int Diff, MineNum = -1, row = 0, col = 0, **Map = NULL, *argRow, tLen = 0, isReturn = 0, isReturnMain = 1,
	          isShowRks = 1, tRTips = 0, tLeftClick = 0, isRetryMain = 1, isQuit; //各种控制的变量（看名字）
	/*
	isReturn：控制从难度界面到难度界面（防止自定义错误输入）
	isReturnMain：控制从难度界面到主界面
	isShowRks：控制从游戏界面到排行榜界面
	isRetryMain、isQuit：控制是否结束游戏
	控制顺序按照概要中的设计
	*/
	char **MapShow = NULL;
	IMAGE Tile[13], TitleImg, ReturnTitleImg, Rks, bkDiff;
	IMAGE Diff1[2], Diff2[2], Diff3[2], Diff4[2], ReturnMain[2], DiffTitleImg, Tips[50];
	char filename[100] = {0}, Rk[10] = {0};//胜率
	char GetLine[150] = {0};//读取的每一行
	HWND hWnd;
	HICON hIcon = ExtractIcon(NULL, _T("MineSweeper.ico"), 0);
	MOUSEMSG tmsg;
	if (hIcon == NULL)
		return 114514;
	ImageLoading(filename, Tile);
	loadimage(&TitleImg, "start.jpg", 400, 400);
	loadimage(&bkDiff, "bkDiff.jpg", 0, 0);
	loadimage(&Rks, "Rks.jpg", 400, 100);
	//第一个窗口（主界面背景）开始
	while (isRetryMain) {
		isReturnMain = 1;
		while (isReturnMain) {
			WindowInit(WINDOWS_MAIN_W, WINDOWS_MAIN_H, hIcon);
			putimage(0, 0, &TitleImg);
			if (!InputBox(tGrade.name, 100, _T("君の名は。（只能输入英文，不超过一百个字母）"), _T("欢迎来到扫雷~"),
			              "Developer_COOL", 0, 0,
			              false)) {
				MessageBox(NULL, "难道我连你的名字都不配知道吗QWQ", "崩溃了！", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
				return 114514;
			}
			tLen = strlen(tGrade.name);
			tGrade.name[tLen] = '\0';
			closegraph();
			//第一个窗口（主界面背景）结束
			//第二个窗口（选择难度）开始
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
					MessageBox(NULL, _T("你已经点击先辈超过100次！你有点太爱先辈了"), _T("你被臭死了！"),
					           MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
					return 114518;
				}
				isReturn = DetDiff(Diff, &col, &row, &MineNum);
				isReturnMain = 0;
			}
		}
		closegraph();
		//第二个窗口（选择难度）结束
		argRow = &row;
		MapShow = InitMapShow(col, row);
		Map = InitMap(col, row, MineNum);
		//第三个窗口（游戏界面）开始
		WindowInit(WINDOWS_GAME_W, WINDOWS_GAME_H, hIcon);
		setbkcolor(RGB(191, 191, 191));
		cleardevice();
		LOGFONT f;//字体结构体
		SetFont(f, 16);
		setlinecolor(RGB(191, 191, 191));
		setfillcolor(RGB(191, 191, 191));
		isShowRks = FindMine(Map, MapShow, row, col, MineNum, Tile, Diff);
		DisplayMap(MapShow, row, col, Tile);
		//展示胜率
		while (1) {
			MOUSEMSG tmsg = GetMouseMsg();
			if (tmsg.uMsg == WM_LBUTTONDOWN) {
				if (tmsg.x >= (col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2 && tmsg.y >= row * IMG_SIZE + 10
				        && tmsg.x <= (col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 && tmsg.y <= row * IMG_SIZE + 10 + IS_WIN_IMG_SIZE) {
					MessageBox(NULL, "加载中，请稍等……", "略略略", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
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
		//第三个窗口（游戏界面）结束
		//第四个窗口（排行榜）开始
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
				outtextxy(0, 100, _T("胜率："));
				outtextxy(200, 100, Rk);
				outtextxy(200 + 36 * 2 + 18, 100, "%");
			}//读取胜率
			if (Diff != 4 && GradeImfo == NULL)
				return 114517;
			rewind(GradeImfo);
			fgets(GetLine, 149, GradeImfo); //读取第一行并丢掉
			for (int i = 1; i <= 10; i++) {
				memset(GetLine, 0, sizeof(GetLine));
				tOG[i - 1].Index = i;
				if (fgets(GetLine, 149, GradeImfo) == NULL)
					break;
				strcpy(tOG[i - 1].name, strtok(GetLine, ","));
				sscanf(strtok(NULL, ","), "%d", &tOG[i - 1].using_time);//为什么是NULL???
				sprintf(tIndex, "%d", tOG[i - 1].Index);
				sprintf(tTime, "%d", tOG[i - 1].using_time);
				outtextxy(0, 100 + 50 * i, tIndex);
				outtextxy(40, 100 + 50 * i, tOG[i - 1].name);
				outtextxy(400 - 18 * 3, 100 + 50 * i, tTime);
			}
			//防止误操作
			while (1) {
				tmsg = GetMouseMsg();
				if (tmsg.uMsg == WM_LBUTTONDOWN && tmsg.x >= 0 && tmsg.y >= 0 && tmsg.x <= 400 && tmsg.y <= 100) {
					isRetryMain = 0;
					break;
				} else if (tmsg.uMsg == WM_LBUTTONDOWN) {
					isQuit = MessageBox(NULL, _T("是否重新开始？"), _T("继续继续！"), MB_OKCANCEL | MB_ICONQUESTION);
					if (isQuit != IDOK)
						continue;
					else
						break;
				}
			}
			//再按一次鼠标左键退出
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
		free(MapShow);//结尾free，准备结束/开启下一局
	}
	//第四个窗口（排行榜）结束
	return 0;
}