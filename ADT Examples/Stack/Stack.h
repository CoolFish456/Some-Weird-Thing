#include <stdio.h>
#include <stdlib.h>
#ifndef __STACK_H__
#define __STACK_H__
typedef struct StackRecord *Stack,STACK;

Stack CreateStack(int);//用数组实现栈的时候，注意规定栈的大小
void MakeEmpty(Stack);
bool isEmpty(Stack);
bool isFull(Stack);
void DeleteStack(Stack);
int TopElement(Stack);
void Push(Stack,int);
void Pop(Stack);
int TopAndPop(Stack);

#define EOS -1//当Stack空时，Top游标的位置
#endif
struct StackRecord{
    int *Array;
    int Top;
    int Capacity;
};//要求：用数组实现栈
//提示：用数组实现栈比用链表实现简单一些