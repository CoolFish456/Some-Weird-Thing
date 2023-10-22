#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include "mapInit.cpp"
#include <mmsystem.h>
#pragma comment(lib,"libwinmm")//奇怪
static int isWin = PROCESS;
static int OpenBlock = 0;
//记录输赢状态与格子打开数量
static int First = 1;
//First判定是否是第一次打开格子，防止见面杀
static int isRetry = 1;
//判定重新开始的参数（1：第一次游玩；2：更多次游玩；0：退出）
static IMAGE ProcessPic[3];
int timeset = 0;
//计时器
static int CountFail = 0; //彩蛋
GRADES tGrade;

int JudgeBoundary(int yInput, int xInput, int Row, int Col) {
	return xInput >= 1 && yInput >= 1 && xInput <= Col && yInput <= Row;
}

int JudgeNear(int x, int y, int xInput, int yInput) {
	return xInput >= x - 1 && yInput >= y - 1 && xInput <= x + 1 && yInput <= y + 1;
}
//判断条件辅助函数（两个）
int CountMine(int xInput, int yInput, int **Map) {
	int count = 0;

	if (Map[yInput - 1][xInput - 1] == 1)
		count++;
	if (Map[yInput - 1][xInput] == 1)
		count++;
	if (Map[yInput - 1][xInput + 1] == 1)
		count++;
	if (Map[yInput][xInput - 1] == 1)
		count++;
	if (Map[yInput][xInput + 1] == 1)
		count++;
	if (Map[yInput + 1][xInput - 1] == 1)
		count++;
	if (Map[yInput + 1][xInput] == 1)
		count++;
	if (Map[yInput + 1][xInput + 1] == 1)
		count++;
	return count;
}//统计周围八格雷数
void SpreadMine(int xInput, int yInput, int **Map, char **MapShow, int Row, int Col) {
	int count;
	if (xInput >= 1 && yInput >= 1 && xInput <= Col && yInput <= Row) {
		count = CountMine(xInput, yInput, Map);

		if (MapShow[yInput][xInput] == '?' || MapShow[yInput][xInput] == '.') {
			if (count != 0) {
				MapShow[yInput][xInput] = count + '0';
				OpenBlock++;
			} else {
				MapShow[yInput][xInput] = '0';
				OpenBlock++;
				for (int y = yInput - 1; y <= yInput + 1; y++) {
					for (int x = xInput - 1; x <= xInput + 1; x++) {
						if (MapShow[y][x] == '.' || MapShow[y][x]  == '?') {//记得限制条件，防止死递归
							SpreadMine(x, y, Map, MapShow, Row, Col);
						}
					}
				}
			}
		}
	}
}
//统计雷相关函数
int MarkMine(int xInput, int yInput, int Action, char **MapShow, int **Map) {
	int RestChange = 0;
	if (MapShow[yInput][xInput] > '8' || MapShow[yInput][xInput] < '0') {
		switch (Action) {

			case 2: {
				if (MapShow[yInput][xInput] == '.' || MapShow[yInput][xInput]  == '?') {
					MapShow[yInput][xInput]  = '!';
					RestChange = -1;
				}

				break;//标记雷（直接标记某一格/不怀疑了，直接标记！）
			}

			case 3: {
				if (MapShow[yInput][xInput]  == '.') {
					MapShow[yInput][xInput] = '?';
					RestChange = 0;
				} else if (MapShow[yInput][xInput] == '!' ) {
					MapShow[yInput][xInput] = '?';
					RestChange = 1;
				}
				break;//标记雷（怀疑）
			}

			case 4: {
				if ( MapShow[yInput][xInput] == '!') {
					MapShow[yInput][xInput] = '.';
					RestChange = 1;
				} else if (MapShow[yInput][xInput] == '?') {
					MapShow[yInput][xInput] = '.';
					RestChange = 0;
				}
				break;//取消标记
			}
		}
	}
	return RestChange;
}//标记雷（循环点击）
int CountMark(int xInput, int yInput, char **MapShow) {
	int count = 0;

	if (MapShow[yInput - 1][xInput - 1] == '!')
		count++;
	if (MapShow[yInput - 1][xInput] == '!')
		count++;
	if (MapShow[yInput - 1][xInput + 1] == '!')
		count++;
	if (MapShow[yInput][xInput - 1] == '!')
		count++;
	if (MapShow[yInput][xInput + 1] == '!')
		count++;
	if (MapShow[yInput + 1][xInput - 1] == '!')
		count++;
	if (MapShow[yInput + 1][xInput] == '!')
		count++;
	if (MapShow[yInput + 1][xInput + 1] == '!')
		count++;
	return count;
}//统计周围八格标记雷个数
//标记"!"相关函数
void DoubleClickOn(char **MapShow, int xInput, int yInput, IMAGE *img, MOUSEMSG msg, int Row) {
	int tCoordinate[3][3] = {0}; //记录周围八格的摁下信息
	if (MapShow[yInput - 1][xInput - 1] == '.') {
		tCoordinate[0][0] = 1;
		putimage((xInput - 2) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput - 1][xInput] == '.') {
		tCoordinate[0][1] = 1;
		putimage((xInput - 1) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput - 1][xInput + 1] == '.') {
		tCoordinate[0][2] = 1;
		putimage((xInput) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput][xInput - 1] == '.') {
		tCoordinate[1][0] = 1;
		putimage((xInput - 2) * IMG_SIZE, (yInput - 1) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput][xInput + 1] == '.') {
		tCoordinate[1][2] = 1;
		putimage((xInput) * IMG_SIZE, (yInput - 1) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput + 1][xInput - 1] == '.' && yInput + 1 <= Row) {
		tCoordinate[2][0] = 1;
		putimage((xInput - 2) * IMG_SIZE, (yInput) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput + 1][xInput] == '.' && yInput + 1 <= Row) {
		tCoordinate[2][1] = 1;
		putimage((xInput - 1) * IMG_SIZE, (yInput) * IMG_SIZE, &img[0]);
	}
	if (MapShow[yInput + 1][xInput + 1] == '.' && yInput + 1 <= Row) {
		tCoordinate[2][2] = 1;
		putimage((xInput) * IMG_SIZE, (yInput) * IMG_SIZE, &img[0]);
	}
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONUP) {
			break;
		}//检测鼠标弹起
	}
	PlaySound(_T("1.wav"), NULL, SND_ASYNC);//ASYNC：异步播放（播放之后函数立刻返回）
	if (tCoordinate[0][0] == 1)
		putimage((xInput - 2) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[10]);
	if (tCoordinate[0][1] == 1)
		putimage((xInput - 1) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[10]);
	if (tCoordinate[0][2] == 1)
		putimage((xInput) * IMG_SIZE, (yInput - 2) * IMG_SIZE, &img[10]);
	if (tCoordinate[1][0] == 1)
		putimage((xInput - 2) * IMG_SIZE, (yInput - 1) * IMG_SIZE, &img[10]);
	if (tCoordinate[1][2] == 1)
		putimage((xInput) * IMG_SIZE, (yInput - 1) * IMG_SIZE, &img[10]);
	if (tCoordinate[2][0] == 1 && yInput + 1 <= Row)
		putimage((xInput - 2) * IMG_SIZE, (yInput) * IMG_SIZE, &img[10]);
	if (tCoordinate[2][1] == 1 && yInput + 1 <= Row)
		putimage((xInput - 1) * IMG_SIZE, (yInput) * IMG_SIZE, &img[10]);
	if (tCoordinate[2][2] == 1 && yInput + 1 <= Row)
		putimage((xInput) * IMG_SIZE, (yInput) * IMG_SIZE, &img[10]);
	//显示回来原来的格子/打开
}//视觉效果：双击的时候周围八格能够摁下的地方展示出来
int FindMine(int **Map, char **MapShow, int Row, int Col, int Mine, IMAGE *img, int Diff) {
	loadimage(&ProcessPic[0], "20.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	loadimage(&ProcessPic[1], "21.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	loadimage(&ProcessPic[2], "22.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	outtextxy(0, Row * IMG_SIZE + 10, _T("时间："));
	outtextxy((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 10, _T("剩余雷数："));
	putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[1]);
	PlaySound(_T("12.wav"), NULL, SND_ASYNC);
	int tRow = 0, tCol = 0, Opr = 0, tMark = 0, tMine = 0, CountOpr = 0, RestMine = Mine,  tRow2 = 0, tCol2 = 0,
	    tCount = 0, isShowRks = 1;
	FILE *frks = NULL;
	int *argRow = &Row;
	bool isLeft = 0, isRight = 0;
	char chRestMine[20] = {0};
	switch (Diff) {
		case 1: {
			frks = fopen("Diff1\\ranking1.csv", "a+");
			break;
		}
		case 2: {
			frks = fopen("Diff2\\ranking2.csv", "a+");
			break;
		}
		case 3: {
			frks = fopen("Diff3\\ranking3.csv", "a+");
			break;
		}
		default: {
			isShowRks = 0;
			break;
		}
	}//加载对应的胜利表格
	_beginthread(TimeCount, 0, (void *)argRow); //启动时间计时线程
	if (frks == NULL && Diff != 4)
		return 114516;
	OpenBlock = 0;
	isRetry = 1;
	First = 1;
	timeset = 0;
	isWin = PROCESS; //从其他位置重新开始，所有的静态变量需要重新初始化
	//初始化部分
	while (isRetry) {
		if (CountFail == 10)
			MessageBox(NULL, _T("你已经连续输了十次捏~"), _T("杂鱼~杂鱼~"), MB_OK | MB_ICONSTOP);
		if (isRetry == 0)
			break;
		else if (isRetry == 2) {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[1]);
			OpenBlock = 0;
			First = 1;
			timeset = 0;
			isWin = PROCESS;
			for (int i = 0; i < Row + 2; i++) {
				for (int j = 0; j < Col + 2; j++) {
					Map[i][j] = 0;
				}
			}
			MineGenerate(Map, Col, Row, Mine);
			for (int i = 0; i < Row + 2; i++) {
				for (int j = 0; j < Col + 2; j++) {
					MapShow[i][j] = '.';
				}
			}
			solidrectangle((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 60, Col * IMG_SIZE,
			               Row * IMG_SIZE + 30);
			solidrectangle(0, Row * IMG_SIZE + 60, (Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2 - 5,
			               Row * IMG_SIZE + 30);
			RestMine = Mine;
			_beginthread(TimeCount, 0, (void *)argRow);
		}//再次生成雷，再次开启时间线程（从游戏结束位置重新开始）
		sprintf(chRestMine, "%d", RestMine);//转换到字符串
		outtextxy((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 30, chRestMine);
		DisplayMap(MapShow, Row, Col, img);
		while (isWin == PROCESS) {
			flushmessage(EM_MOUSE);//清空鼠标缓冲
			isLeft = 0;
			isRight = 0;
			MOUSEMSG msg = GetMouseMsg(); //注：换用getmessage()函数，因为对应的结构体不再有效
			if (msg.y <= Row * IMG_SIZE) {
				tCol = msg.x / IMG_SIZE + 1;
				tRow = msg.y / IMG_SIZE + 1;
			} else
				continue;
			switch (msg.uMsg) {
				case WM_LBUTTONDOWN: {
					if (MapShow[tRow][tCol] >= '0' && MapShow[tRow][tCol] <= '8') {
						tMark = CountMark(tCol, tRow, MapShow);
						tMine = CountMine(tCol, tRow, Map);
//					printf("%d	%d\n", tMark, tMine);
						DoubleClickOn(MapShow, tCol, tRow, img, msg, Row);

						if (tMark == tMine) {

							for (int y = tRow - 1; y <= tRow + 1 && isWin != LOSE; y++) {
								for (int x = tCol - 1; x <= tCol + 1 && isWin != LOSE; x++) {
									if (Map[y][x] == 1 && MapShow[y][x] != '!') {
										isWin = LOSE; //输掉游戏的第二种可能
										break;
									}
								}
							}

							if (isWin != LOSE) {
								for (int y = tRow - 1; y <= tRow + 1 && isWin != LOSE; y++) {
									for (int x = tCol - 1; x <= tCol + 1 && isWin != LOSE; x++) {
										if (MapShow[y][x] == '.' || MapShow[y][x] == '?') {
											SpreadMine(x, y, Map, MapShow, Row, Col);
										}
									}
								}
							}
						}
					}
					//双击
					/*
					说明：
					已经完成了检测双击的代码，但是实际在游戏中不是很流畅，所以这里用了一个替代方案：
					当左键点击在已经打开的格子内，完成一次双击的操作（手感相似）
					附双击的代码：
					while (1) {
					msg = GetMouseMsg();
					if (msg.uMsg == WM_LBUTTONDOWN) {
					while (1) {
					Sleep(1);
					msg = GetMouseMsg();
					if (msg.uMsg == WM_LBUTTONUP)
					break;
					else if (msg.uMsg == WM_RBUTTONDOWN) {
					***Code***
					break;
					}
					}
					} else if (msg.uMsg == WM_RBUTTONDOWN) {
					while (1) {
					Sleep(1);
					msg = GetMouseMsg();
					if (msg.uMsg == WM_RBUTTONUP)
					break;
					else if (msg.uMsg == WM_LBUTTONDOWN) {
					***Code***
					break;
					}
					}
					}
					}//对称
						*/
					else {

						if (First == 1) {

							if (Row * Col == Mine) {
								isWin = LOSE;
								break;
								//特判极限情况（满雷）

							} else {
								tCount = CountMine(tCol, tRow, Map);
								if (tCount == 0 && Map[tRow][tCol] == 0) {
									SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
									First = 0;
								}//正常情况：踩到一个0（直接打开就可以了）
								else if (tCount != 0 || Map[tRow][tCol] != 0) {
									if (Row * Col - Mine >= 9) {
										tCount += Map[tRow][tCol];
//								printf("%d\n", tCount);
										while (tCount > 0) {
											tCol2 = rand() % Col + 1;
											tRow2 = rand() % Row + 1;
											if (Map[tRow2][tCol2] == 0 && JudgeBoundary(tRow2, tCol2, Row, Col) && !JudgeNear(tCol, tRow, tCol2, tRow2)) {
												Map[tRow2][tCol2] = 1;
												tCount--;
											}
//									ShowMine(Map, MapShow, Row, Col);
//									DisplayMap(MapShow, Row, Col);
											if (tCount == 0)
												break;
										}
										for (int i = tRow - 1; i <= tRow + 1; i++) {
											for (int j = tCol - 1; j <= tCol + 1; j++) {
												Map[i][j] = 0;
											}
										}
//								ShowMine(Map, MapShow, Row, Col);
										for (int i = 1; i <= Row; i++) {
											for (int j = 1; j <= Col; j++) {
												if (Map[i][j] == 0 && MapShow[i][j] == '*') {
													MapShow[i][j] = '.';
												}
											}
										}//重新同步
										SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
										First = 0;
									} else {
										if (Map[tRow][tCol] == 0) {
											SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
											First = 0;
										} else {
											tCount = 1;
											while (tCount > 0) {
												tCol2 = rand() % Col + 1;
												tRow2 = rand() % Row + 1;
												if (Map[tRow2][tCol2] == 0 && JudgeBoundary(tRow2, tCol2, Row, Col) && !JudgeNear(tCol, tRow, tCol2, tRow2)) {
													Map[tRow2][tCol2] = 1;
													tCount--;
												}
//									ShowMine(Map, MapShow, Row, Col);
//									DisplayMap(MapShow, Row, Col);
												if (tCount == 0)
													break;
											}
											Map[tRow][tCol] = 0;
											SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
											First = 0;
//								ShowMine(Map, MapShow, Row, Col);
										}
									}//特判极限情况：空位不足->只移走一个
								}
							}
//踩到雷/踩到非0格时，优化为0（Win7版本规则）
						}

						else if (MapShow[tRow][tCol] != '!') {
							if (Map[tRow][tCol] == 1)
								isWin = LOSE;//输掉游戏的第一种可能
							else if (MapShow[tRow][tCol] == '?' || MapShow[tRow][tCol] == '.')
								SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
						}//一般情况
						PlaySound(_T("2.wav"), NULL, SND_ASYNC);
					}//左键单击
					break;
				}//左键（注：包含双击操作，点击打开的格子即可双击）


				case WM_RBUTTONDOWN: {

					switch (MapShow[tRow][tCol]) {

						case '.': {
							RestMine += MarkMine(tCol, tRow, 2, MapShow, Map);
							PlaySound(_T("1.wav"), NULL, SND_ASYNC);
							break;
						}

						case '!': {
							RestMine += MarkMine(tCol, tRow, 3, MapShow, Map);
							PlaySound(_T("1.wav"), NULL, SND_ASYNC);
							break;
						}

						case '?': {
							RestMine += MarkMine(tCol, tRow, 4, MapShow, Map);
							PlaySound(_T("1.wav"), NULL, SND_ASYNC);
							break;
						}
					}
					break;
				}//右键单击循环变化
				default: {
					continue;
				}
			}
			if (isWin != LOSE) {
				isWin = GameWin(Map, MapShow, Row, Col, Mine);
			}
			if (isWin == PROCESS) {
				DisplayMap(MapShow, Row, Col, img);
			} else {
				ShowMine(Map, MapShow, Row, Col);
				DisplayMap(MapShow, Row, Col, img);
			}

			if (isWin != PROCESS) {
				PrintWin(isWin, ProcessPic, Col, Row);
				break;
			} else
				PrintWin(PROCESS, ProcessPic, Col, Row);
			solidrectangle((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 60, Col * IMG_SIZE,
			               Row * IMG_SIZE + 30);
			sprintf(chRestMine, "%d", RestMine);//转换到字符串
			outtextxy((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 30, chRestMine);
		}
		rewind(frks);
		tGrade.Winning = isWin;
		tGrade.Diff = Diff;
		fputs(tGrade.name, frks);
		fputc(',', frks);
		fprintf(frks, "%d,%d,%d", tGrade.using_time, tGrade.Winning, tGrade.Diff);
		fputc('\n', frks);
		fflush(frks);
		//开发中：通过不同的难度，打开不同难度的排行榜
	}
	fclose(frks);
	return isShowRks;
}
//游戏核心进程
int GameWin(int **Map, char **MapShow, int Row, int Col, int Mine) {
	if (Row * Col - OpenBlock == Mine)
		return WIN;
	else
		return PROCESS;
}
//判定输赢：所有没有开过的格子都只能是雷（做差）
void PrintWin(int Win, IMAGE *img, int Col, int Row) {
	int JudgeRetry = 1;
	switch (Win) {
		case LOSE: {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[0]);
			PlaySound(_T("11.wav"), NULL, SND_ASYNC);
			JudgeRetry = MessageBox(NULL, "你寄了！重开吧小辣鸡！", "杂鱼~杂鱼~",
			                        MB_OKCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL);
			CountFail++;
			break;
		}
		case WIN: {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[2]);
			PlaySound(_T("10.wav"), NULL, SND_ASYNC);
			JudgeRetry = MessageBox(NULL, "您赢了！我尊敬的扫雷之王，要不要再玩一次？", "大佬！别卷了！！",
			                        MB_OKCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL);
			CountFail = 0;
			break;
		}
		case PROCESS: {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[1]);
			break;
		}
	}
	if (JudgeRetry == IDOK) {
		isRetry = 2;
	}//选择“确定”重新开始
	else {
		isRetry = 0;
		MessageBox(NULL, "点击小图标，查看当前难度排行榜！（自定义无法参与排名）",
		           "点击其他部分结束游戏！",
		           MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	}//选择“取消”或者关闭框图结束游戏，并可以查看排行榜
}
//输赢相关函数（用图片表示输赢的情况）
void TimeCount(void *argRow) {
	int Row = *(int *)argRow;
	char timeshow[16] = {'0'};
	while (First);
	while (isWin == PROCESS) {
		sprintf(timeshow, "%d", timeset);
		outtextxy(0, Row * IMG_SIZE + 30, timeshow);
		Sleep(1000);
		timeset++;
//		printf("%d\n", timeset);
	}
	tGrade.using_time = timeset;
	_endthread();
}//计时函数（多线程）