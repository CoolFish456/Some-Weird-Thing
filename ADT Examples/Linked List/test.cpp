#include "Linked_List.cpp"
//一个测试例程的样例程序
int main(){
    printf("Please input elements. Use -1 to complete your input.\n");
    List TestList=CreateList();
    Position pos=TestList;
    PrintList(TestList);
    for(int i=0;i<3;i++){
        pos=pos->Next;
    }
    Insert(TestList,8888,pos);
    PrintList(TestList);
    printf("%d\n",LengthOfList(TestList));
    Delete(TestList,8888);
    PrintList(TestList);
    DeleteList(TestList);
    system("pause");
}