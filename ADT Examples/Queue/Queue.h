#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#define EOQ -1
typedef struct QueueRecord *Queue,QUEUE;

Queue CreateQueue(int);
void DeleteQueue(Queue);
bool isEmpty(Queue);
void MakeEmpty(Queue);
bool isFull(Queue);
void Enqueue(Queue,int);
void Dequeue(Queue);
int Front(Queue);
int FrontAndDequeue(Queue);
int LengthOfQueue(Queue);
void PrintQueue(Queue);
#endif
struct QueueRecord{
    int *Array;
    int Front;
    int Rear;
    int Capacity;
};//要求：用循环数组实现队列