#include <easyxgraphics.h>  //<graphics.h>
#pragma comment(lib, "libEasyX libgdi32 libole32")
#include "game.h"

//一些小剧情
void Plot1() {
	MessageBox(NULL, _T("正在启动……"), _T(" "), MB_OK | MB_ICONINFORMATION);
}//提示：设计密码：114514，实现“注入”功能，而这需要改动所有的提示框