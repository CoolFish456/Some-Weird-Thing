#include <stdio.h>
#include <stdlib.h>
#ifndef _List_H_
#define _List_H_
#define FLAG -1
typedef struct Node *PtrNode,NODE;//用于生成节点
typedef PtrNode Position,List;//分别定义元素位置指针和元素头节点指针

List CreateList();
void MakeEmpty(List);
bool isEmpty(List);
bool isLastElm(Position);
void Insert(List,int,Position);
void Delete(List,int);
Position Find(List,int);
Position FindPrevious(List,int);
void DeleteList(List);
void PrintList(List);
int LengthOfList(List);

#endif
struct Node{
    int num;
    Position Next;
};