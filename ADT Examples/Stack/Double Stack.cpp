//这个程序定义了一个在同一个数组内的两个栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCAP 10
#define FULL 1
#define OK 0
typedef int State;
typedef struct{
    int *arr;
    int max,topl,topr;
}tws;
//a
State InitStack(tws *S){
    int maxnum=MAXCAP;
    S->max=maxnum;
    S->arr=(int*)malloc(sizeof(int)*maxnum);
    if(S->arr==NULL){
        fprintf(stderr,"Out of space!!\n");
        return FULL;
    }
    memset(S->arr,0,sizeof(int)*maxnum);
    // for(int i=0;i<S->max;i++)printf("%d ",S->arr[i]);
    S->topl=-1;
    S->topr=maxnum;
    return OK;
}
//b
void push(tws *S,int i,int e){
    if(S->topr-S->topl<=1)fprintf(stderr,"The stack is full!\n");
    else{
        switch(i){
            case 0:
                S->topl++;
                S->arr[S->topl]=e;
                break;
            case 1:
                S->topr--;
                S->arr[S->topr]=e;
                break;
            default:
                break;
        }
    }
}
//c
void pop(tws *s,int i,int *e){
    if((i==0&&s->topl==-1)||(i==1&&s->topr==s->max))fprintf(stderr,"The stack is empty!\n");
    else{
        switch(i){
            case 0:
                *e=s->arr[s->topl];
                s->arr[s->topl]=0;
                s->topl--;
                break;
            case 1:
                *e=s->arr[s->topr];
                s->arr[s->topr]=0;
                s->topr++;
                break;
            default:
                break;
        }
    }
}
int main(){
    tws Test;
    if(InitStack(&Test)==FULL){
        system("pause");
        return -1;
    }
    int e;
    // push(&Test,0,1);
    // push(&Test,1,2);
    // push(&Test,0,3);
    // push(&Test,0,4);
    // push(&Test,1,5);
    // push(&Test,1,6);
    // push(&Test,1,7);
    // for(int i=0;i<Test.max;i++)printf("%d ",Test.arr[i]);
    // printf("\n");
    // pop(&Test,0,&e);
    // printf("%d\n",e);
    // pop(&Test,1,&e);
    // printf("%d\n",e);
    // for(int i=0;i<Test.max;i++)printf("%d ",Test.arr[i]);
    push(&Test,1,7);
    pop(&Test,1,&e);
    pop(&Test,1,&e);
    push(&Test,0,4);
    pop(&Test,0,&e);
    pop(&Test,0,&e);
    printf("\n");
    system("pause");
    return 0;
}