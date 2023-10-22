#include "Stack.cpp"

int main(){
    Stack TestStack=CreateStack(100);
    int num;
    for(int i=0;i<5;i++){
        scanf("%d",&num);
        Push(TestStack,num);
    }
    printf("%d\n",TopElement(TestStack));
    Pop(TestStack);
    printf("%d\n",TopElement(TestStack));
    DeleteStack(TestStack);
    system("pause");
    return 0;
}