#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include "mapInit.cpp"
#include <mmsystem.h>
#pragma comment(lib,"libwinmm")//���
static int isWin = PROCESS;
static int OpenBlock = 0;
//��¼��Ӯ״̬����Ӵ�����
static int First = 1;
//First�ж��Ƿ��ǵ�һ�δ򿪸��ӣ���ֹ����ɱ
static int isRetry = 1;
//�ж����¿�ʼ�Ĳ�����1����һ�����棻2����������棻0���˳���
static IMAGE ProcessPic[3];
int timeset = 0;
//��ʱ��
static int CountFail = 0; //�ʵ�
GRADES tGrade;

int JudgeBoundary(int yInput, int xInput, int Row, int Col) {
	return xInput >= 1 && yInput >= 1 && xInput <= Col && yInput <= Row;
}

int JudgeNear(int x, int y, int xInput, int yInput) {
	return xInput >= x - 1 && yInput >= y - 1 && xInput <= x + 1 && yInput <= y + 1;
}
//�ж���������������������
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
}//ͳ����Χ�˸�����
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
						if (MapShow[y][x] == '.' || MapShow[y][x]  == '?') {//�ǵ�������������ֹ���ݹ�
							SpreadMine(x, y, Map, MapShow, Row, Col);
						}
					}
				}
			}
		}
	}
}
//ͳ������غ���
int MarkMine(int xInput, int yInput, int Action, char **MapShow, int **Map) {
	int RestChange = 0;
	if (MapShow[yInput][xInput] > '8' || MapShow[yInput][xInput] < '0') {
		switch (Action) {

			case 2: {
				if (MapShow[yInput][xInput] == '.' || MapShow[yInput][xInput]  == '?') {
					MapShow[yInput][xInput]  = '!';
					RestChange = -1;
				}

				break;//����ף�ֱ�ӱ��ĳһ��/�������ˣ�ֱ�ӱ�ǣ���
			}

			case 3: {
				if (MapShow[yInput][xInput]  == '.') {
					MapShow[yInput][xInput] = '?';
					RestChange = 0;
				} else if (MapShow[yInput][xInput] == '!' ) {
					MapShow[yInput][xInput] = '?';
					RestChange = 1;
				}
				break;//����ף����ɣ�
			}

			case 4: {
				if ( MapShow[yInput][xInput] == '!') {
					MapShow[yInput][xInput] = '.';
					RestChange = 1;
				} else if (MapShow[yInput][xInput] == '?') {
					MapShow[yInput][xInput] = '.';
					RestChange = 0;
				}
				break;//ȡ�����
			}
		}
	}
	return RestChange;
}//����ף�ѭ�������
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
}//ͳ����Χ�˸����׸���
//���"!"��غ���
void DoubleClickOn(char **MapShow, int xInput, int yInput, IMAGE *img, MOUSEMSG msg, int Row) {
	int tCoordinate[3][3] = {0}; //��¼��Χ�˸��������Ϣ
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
		}//�����굯��
	}
	PlaySound(_T("1.wav"), NULL, SND_ASYNC);//ASYNC���첽���ţ�����֮�������̷��أ�
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
	//��ʾ����ԭ���ĸ���/��
}//�Ӿ�Ч����˫����ʱ����Χ�˸��ܹ����µĵط�չʾ����
int FindMine(int **Map, char **MapShow, int Row, int Col, int Mine, IMAGE *img, int Diff) {
	loadimage(&ProcessPic[0], "20.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	loadimage(&ProcessPic[1], "21.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	loadimage(&ProcessPic[2], "22.jpg", IS_WIN_IMG_SIZE, IS_WIN_IMG_SIZE);
	outtextxy(0, Row * IMG_SIZE + 10, _T("ʱ�䣺"));
	outtextxy((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 10, _T("ʣ��������"));
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
	}//���ض�Ӧ��ʤ�����
	_beginthread(TimeCount, 0, (void *)argRow); //����ʱ���ʱ�߳�
	if (frks == NULL && Diff != 4)
		return 114516;
	OpenBlock = 0;
	isRetry = 1;
	First = 1;
	timeset = 0;
	isWin = PROCESS; //������λ�����¿�ʼ�����еľ�̬������Ҫ���³�ʼ��
	//��ʼ������
	while (isRetry) {
		if (CountFail == 10)
			MessageBox(NULL, _T("���Ѿ���������ʮ����~"), _T("����~����~"), MB_OK | MB_ICONSTOP);
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
		}//�ٴ������ף��ٴο���ʱ���̣߳�����Ϸ����λ�����¿�ʼ��
		sprintf(chRestMine, "%d", RestMine);//ת�����ַ���
		outtextxy((Col * IMG_SIZE) / 2 + IS_WIN_IMG_SIZE / 2 + 5, Row * IMG_SIZE + 30, chRestMine);
		DisplayMap(MapShow, Row, Col, img);
		while (isWin == PROCESS) {
			flushmessage(EM_MOUSE);//�����껺��
			isLeft = 0;
			isRight = 0;
			MOUSEMSG msg = GetMouseMsg(); //ע������getmessage()��������Ϊ��Ӧ�Ľṹ�岻����Ч
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
										isWin = LOSE; //�����Ϸ�ĵڶ��ֿ���
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
					//˫��
					/*
					˵����
					�Ѿ�����˼��˫���Ĵ��룬����ʵ������Ϸ�в��Ǻ�������������������һ�����������
					�����������Ѿ��򿪵ĸ����ڣ����һ��˫���Ĳ������ָ����ƣ�
					��˫���Ĵ��룺
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
					}//�Գ�
						*/
					else {

						if (First == 1) {

							if (Row * Col == Mine) {
								isWin = LOSE;
								break;
								//���м�����������ף�

							} else {
								tCount = CountMine(tCol, tRow, Map);
								if (tCount == 0 && Map[tRow][tCol] == 0) {
									SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
									First = 0;
								}//����������ȵ�һ��0��ֱ�Ӵ򿪾Ϳ����ˣ�
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
										}//����ͬ��
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
									}//���м����������λ����->ֻ����һ��
								}
							}
//�ȵ���/�ȵ���0��ʱ���Ż�Ϊ0��Win7�汾����
						}

						else if (MapShow[tRow][tCol] != '!') {
							if (Map[tRow][tCol] == 1)
								isWin = LOSE;//�����Ϸ�ĵ�һ�ֿ���
							else if (MapShow[tRow][tCol] == '?' || MapShow[tRow][tCol] == '.')
								SpreadMine(tCol, tRow, Map, MapShow, Row, Col);
						}//һ�����
						PlaySound(_T("2.wav"), NULL, SND_ASYNC);
					}//�������
					break;
				}//�����ע������˫������������򿪵ĸ��Ӽ���˫����


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
				}//�Ҽ�����ѭ���仯
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
			sprintf(chRestMine, "%d", RestMine);//ת�����ַ���
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
		//�����У�ͨ����ͬ���Ѷȣ��򿪲�ͬ�Ѷȵ����а�
	}
	fclose(frks);
	return isShowRks;
}
//��Ϸ���Ľ���
int GameWin(int **Map, char **MapShow, int Row, int Col, int Mine) {
	if (Row * Col - OpenBlock == Mine)
		return WIN;
	else
		return PROCESS;
}
//�ж���Ӯ������û�п����ĸ��Ӷ�ֻ�����ף����
void PrintWin(int Win, IMAGE *img, int Col, int Row) {
	int JudgeRetry = 1;
	switch (Win) {
		case LOSE: {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[0]);
			PlaySound(_T("11.wav"), NULL, SND_ASYNC);
			JudgeRetry = MessageBox(NULL, "����ˣ��ؿ���С������", "����~����~",
			                        MB_OKCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL);
			CountFail++;
			break;
		}
		case WIN: {
			putimage((Col * IMG_SIZE) / 2 - IS_WIN_IMG_SIZE / 2, Row * IMG_SIZE + 10, &ProcessPic[2]);
			PlaySound(_T("10.wav"), NULL, SND_ASYNC);
			JudgeRetry = MessageBox(NULL, "��Ӯ�ˣ����𾴵�ɨ��֮����Ҫ��Ҫ����һ�Σ�", "���У�����ˣ���",
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
	}//ѡ��ȷ�������¿�ʼ
	else {
		isRetry = 0;
		MessageBox(NULL, "���Сͼ�꣬�鿴��ǰ�Ѷ����а񣡣��Զ����޷�����������",
		           "����������ֽ�����Ϸ��",
		           MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	}//ѡ��ȡ�������߹رտ�ͼ������Ϸ�������Բ鿴���а�
}
//��Ӯ��غ�������ͼƬ��ʾ��Ӯ�������
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
}//��ʱ���������̣߳�