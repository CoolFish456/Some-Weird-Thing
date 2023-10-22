#include "Queue.h"

Queue CreateQueue(int max){
    Queue NewQueue;
    NewQueue=(Queue)malloc(sizeof(QUEUE));
    if(NewQueue==NULL){
        fprintf(stderr,"Out of space!\n");
        exit(-1);
    }
    else{
        NewQueue->Array=(int*)malloc(max*sizeof(int));
        if(NewQueue->Array==NULL){
            fprintf(stderr,"Out of space!\n");
            exit(-1);        
        }
        NewQueue->Capacity=max;
        MakeEmpty(NewQueue);
    }
    return NewQueue;
}
void DeleteQueue(Queue Q){
    if(Q!=NULL){
        free(Q->Array);
        free(Q);
    }
    printf("Deleted seccessfully.\n");
}
bool isEmpty(Queue Q){
    return Q->Rear-Q->Front==-1;
}
void MakeEmpty(Queue Q){
    Q->Front=0;
    Q->Rear=-1;
}
bool isFull(Queue Q){
    return Q->Rear-Q->Front==Q->Capacity-1;
}
void Enqueue(Queue Q,int n){
    if(isFull(Q)){
        fprintf(stderr,"The queue is full.\n");
        exit(-2);
    }
    Q->Rear++;
    Q->Array[Q->Rear%Q->Capacity]=n;
}
void Dequeue(Queue Q){
    if(isEmpty(Q)){
        fprintf(stderr,"The queue is empty.\n");
        exit(-3);
    }
    Q->Front++;
}
int Front(Queue Q){
    if(isEmpty(Q)){
        fprintf(stderr,"The queue is empty.\n");
        return EOQ;
    }
    return Q->Array[Q->Front%Q->Capacity];
}
int FrontAndDequeue(Queue Q){
    if(isEmpty(Q)){
        fprintf(stderr,"The queue is empty.\n");
        return EOQ;
    }
    int temp=Q->Array[Q->Front%Q->Capacity];
    Q->Front++;
    return temp;
}
int LengthOfQueue(Queue Q){
    if(isEmpty(Q)){
        fprintf(stderr,"The queue is empty.\n");
        return EOQ;
    }
    return Q->Rear-Q->Front;
}
void PrintQueue(Queue Q){
    if(isEmpty(Q)){
        fprintf(stderr,"The queue is empty.\n");
        exit(-3);
    }
    printf("The element(s) of the queue are:");
    for(int i=Q->Front;i<=Q->Rear;i++){
        printf("%d ",Q->Array[i%Q->Capacity]);
    }
    printf("\n");
}