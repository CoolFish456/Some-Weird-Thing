#include <stdio.h>
#include <stdlib.h>
#ifndef _ListCursor_H_
#define _ListCursor_H_
#define MAXSIZE 1000
typedef int List,PosNext;//List,PosNext相当于指针（头指针和下一个元素的指针），只不过这里用了数组
void CursorInit();

#endif
struct Node{
    int Element;
    PosNext Next;
};
struct Node Cursor[MAXSIZE];//链表池（所有的链表都存储在这个全局数组中）