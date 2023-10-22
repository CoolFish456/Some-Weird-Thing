//本程序实现了基本的链表例程
#include "List.h"

List CreateList(){
    int temp;
    List NewList=NULL;
    Position NewNode=NULL,TmpPos=NULL;
    scanf("%d",&temp);
    while(temp!=FLAG){
        NewNode=new NODE;
        NewNode->num=temp;//输入数据
        if(NewList==NULL){
            NewList=new NODE;
            NewList->Next=NewNode;//头部特判：将头部指针指向第一个节点，这里将头部指针看作一个特殊的节点
        }
        else{
            TmpPos->Next=NewNode;//将新的节点与原有的链表链接
        }
        TmpPos=NewNode;//位置指针向下挪动
        scanf("%d",&temp);
    }
    if(TmpPos!=NULL){
        TmpPos->Next=NULL;
    }
    return NewList;
}

void MakeEmpty(List TmpList){
    Position TmpPos=TmpList->Next,Tmp=NULL;
    while(TmpPos!=NULL){
        Tmp=TmpPos->Next;
        delete TmpPos;
        TmpPos=Tmp;//从第一个节点遍历并清空
    }
    TmpList->Next=NULL;//将头节点的后继清空
}

bool isEmpty(List TmpList){
    return TmpList->Next==NULL;
}

void Insert(List TmpList,int n,Position Pos){
    if(isLastElm(Pos)){
        Pos->Next=new NODE;
        Pos->Next->num=n;
        Pos->Next->Next=NULL;
    }//尾部特判：直接插入
    else{
        Position temp=new NODE;
        temp->num=n;
        temp->Next=Pos->Next;
        Pos->Next=temp;
    }//一般情况：在Pos的后面插入，注意指针的改变
}

void Delete(List TmpList,int n){
    Position Pos=FindPrevious(TmpList,n),temp;
    temp=Pos->Next;
    Pos->Next=temp->Next;
    delete temp;
}//通过元素找到要删除的节点，删除pos后面的一个节点

Position Find(List TmpList,int n){
    Position pos=FindPrevious(TmpList,n);
    return pos->Next;
}

Position FindPrevious(List TmpList,int n){
    Position pos=TmpList;//从头节点开始，而不是第一个节点
    while (pos->Next!=NULL&&pos->Next->num!=n){
        pos=pos->Next;
    }
    return pos;
}//找到pos后面的一个元素

void DeleteList(List TmpList){
    Position pos=TmpList->Next,temp;
    while(pos!=NULL){
        temp=pos->Next;
        delete pos;
        pos=temp;
    }
    delete TmpList;
    printf("Delete the list successfully.\n");
}

bool isLastElm(Position Pos){
    return Pos->Next==NULL;
}

void PrintList(List TmpList){
    Position Pos=TmpList->Next;
    if(isEmpty(TmpList)){
        printf("There is no element in the list!\n");
    }
    else{
        printf("The element(s) in the list are:\n");
        while(Pos!=NULL){
            printf("%d ",Pos->num);
            Pos=Pos->Next;
        }
        printf("\n");
    }
}


int LengthOfList(List TmpList){
    int len=0;
    Position Pos=TmpList->Next;
    while(Pos!=NULL){
        len++;
        Pos=Pos->Next;
    }
    return len;
}