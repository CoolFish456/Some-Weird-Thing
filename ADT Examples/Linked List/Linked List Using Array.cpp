//这个程序给出了使用数组实现链表的例程
/*
模拟链表的两条特性：
1.每一个节点包括数据本身和下一个数据的地址，还应该有表示链表开头的头指针/头节点
2.每次需要一个新的头节点，都可以通过动态声明得到，并且也可以动态删除
优点：兼顾了数组查找的快速和链表增删元素的快速
应用：用于图和树的表示，比如链式前向星（一种排序的边集数组）的写法
*/
#include "ListCursor.h"
void CursorInit(){
    for(int i=0;i<MAXSIZE;i++){
        Cursor[i].Element=0;
        Cursor[i].Next=-1;
    }
}//初始化链表池