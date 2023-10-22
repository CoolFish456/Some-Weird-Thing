//本例子用单循环链表实现了一个队列，并且只用了一个尾指针和链表自身的头节点
#include <stdio.h>
#include <stdlib.h>
typedef int Element;
typedef struct queue{
    Element data;
    struct queue *next;
    struct queue *rear;//尾指针
}*QNode,*Queue;
//Initializing
Queue InitQueue(){
    Queue L=(Queue)malloc(sizeof(struct queue));//头节点
    if(L==NULL){
        fprintf(stderr,"Out of memory!\n");
        exit(666);
    }
    else{
        L->rear=L;
        L->next=L;
    }
    return L;
}
//Enqueueing
void EnQueue(Element e,Queue L){
    QNode p=(QNode)malloc(sizeof(struct queue));
    if(p==NULL)fprintf(stderr,"Out of memory!\n");
    else{
        p->data=e;
        if(L->rear==L){//空队列
            L->rear=p;
        }
        p->next=L->next;
        L->next=p;
    }

}
//Dequeueing
void DeQueue(Element *e,Queue L){
    *e=L->rear->data;
    QNode p=L,temp=L->rear;
    if(L->next==L)fprintf(stderr,"The queue is empty!\n");
    else{
        while(p->next!=L->rear)p=p->next;//找尾指针节点的前驱
        L->rear=p;
        p->next=L;
        free(temp);
    }
}
void DeleteQueue(Queue L){
    Queue temp=L->next,ttemp;
    if(L->next!=L){
        while(temp->next!=L){
            ttemp=temp->next;
            free(temp);
            temp=ttemp;
        }
        free(temp);
        free(L);
    }
}
int main(){
    Queue test;
    int e;
    test=InitQueue();
    EnQueue(1,test);
    EnQueue(2,test);
    EnQueue(3,test);
    EnQueue(4,test);
    EnQueue(5,test);
    DeQueue(&e,test);
    printf("%d\n",e);
    DeQueue(&e,test);
    printf("%d\n",e);
    DeQueue(&e,test);
    printf("%d\n",e);
    DeQueue(&e,test);
    printf("%d\n",e);
    DeQueue(&e,test);
    printf("%d\n",e);
    DeQueue(&e,test);
    DeleteQueue(test);
    system("pause");
    return 0;
}