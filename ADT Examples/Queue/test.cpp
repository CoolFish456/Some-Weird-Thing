#include "Queue.cpp"

int main(){
    Queue TestQueue=CreateQueue(10);
    int num;
    for(int i=0;i<8;i++){
        scanf("%d",&num);
        Enqueue(TestQueue,num);
    }
    PrintQueue(TestQueue);
    Dequeue(TestQueue);
    Dequeue(TestQueue);
    Dequeue(TestQueue);
    PrintQueue(TestQueue);
    Enqueue(TestQueue,8989);
    PrintQueue(TestQueue);
    DeleteQueue(TestQueue);
    system("pause");
    return 0;
}