#include "Stack.h"

Stack CreateStack(int MaxNum){
    Stack NewStack;
    NewStack=(Stack)malloc(sizeof(STACK));//申请结构体的位置
    if(NewStack==NULL){
        fprintf(stderr,"Out of space!\n");
        exit(-1);
    }
    else{
        NewStack->Array=(int*)malloc(MaxNum*sizeof(int));
        if(NewStack->Array==NULL){
            fprintf(stderr,"Out of space!\n");
            exit(-1);
        }
        NewStack->Capacity=MaxNum;
        MakeEmpty(NewStack);
    }
    return NewStack;
}
void MakeEmpty(Stack S){
    S->Top=EOS;
}
bool isEmpty(Stack S){
    return S->Top==EOS;
}
bool isFull(Stack S){
    return S->Top==S->Capacity-1;
}
void DeleteStack(Stack S){
    if(S!=NULL){
        free(S->Array);
        free(S);
    }
}
int TopElement(Stack S){
    if(isEmpty(S)){
        fprintf(stderr,"The stack is empty.\n");
        return EOS;
    }
    return S->Array[S->Top];
}
void Push(Stack S,int n){
    if(isFull(S)){
        fprintf(stderr,"The stack is full.\n");
        exit(-2);
    }
    S->Top++;
    S->Array[S->Top]=n;
}
void Pop(Stack S){
    if(isEmpty(S)){
        fprintf(stderr,"The stack is empty.\n");
        exit(-3);
    }
    S->Top--;
}//不用管已经插入的元素，因为栈只能访问栈顶元素
int TopAndPop(Stack S){
        if(isEmpty(S)){
        fprintf(stderr,"The stack is empty.\n");
        return EOS;
    }
    int temp=S->Array[S->Top];
    S->Top--;
    return temp;
}