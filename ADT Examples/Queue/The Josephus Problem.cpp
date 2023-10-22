/*
问题描述：丢手绢问题
N个人拥有从1~N的编号围坐为一个圈圈，从一号开始顺次传递手绢，每次传递M次后，当前拿着手绢的人被淘汰，然后从淘汰者的下一位继续游戏
（或者说：从一号开始报数，报到M的下一个人被淘汰）
（原始问题是报数报到M，实际上与丢手绢相差不大（相差一个1））
总会剩下最后一个人，这个人则获胜
给定N、M，输出获胜者的编号，计算时间复杂度
*/
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;
#define POS pos%n
int Josephus1(int,int);//解法1
int Josephus2(int,int);//解法2

int main(){
    int n,m,winner;
    scanf("%d%d",&n,&m);
    winner=Josephus1(n,m);
    printf("%d\n",winner);
    system("pause");
    return 0;
}

int Josephus1(int n,int m){
    int *queue=(int *)malloc(n*sizeof(int)),pos=-1,RestNum=n,win,num=0,temp;
    if(queue==NULL)exit(0);
    for(int i=0;i<n;i++)queue[i]=1;
    while(RestNum>1){
        pos++;
        if(queue[POS])num++;
        //i为报数，pos为当前位置
        if(num==m){
            num=0;
            temp=POS+1;//暂存当前位置，以查找到最终答案；游标要一直遍历
            do{
                pos++;
            }while(!queue[POS]);//报数结束后，查找没有出列的下一个
            // printf("%d ",POS+1);
            queue[POS]=0;
            RestNum--;
        }
    }
    printf("\n");
    win=temp;
    free(queue);
    return win;//注意游标比实际位置要减1
}//第一个算法
/*
算法思路：用一个循环数组模拟围圈坐的人，用游标不断遍历数组直到只剩下一个元素，输出这个元素
每一次淘汰一个人，相当于对应数组元素置0，下一次遍历跳过之（但是仍然会被遍历到）
时间复杂度：O(NlogN)（证明略），空间复杂度：O(N)
注意到这个事实：每一次剔除队后，都会剩下一个仍然会遍历到的0元素，这是没有必要的。我们需要一个“真正能将元素踢出”的算法
*/
int Josephus2(int n,int m){
    queue<int> people;
    int win;
    for(int i=0;i<n;i++){
        people.push(i+1);
    }
    while(!people.empty()){
        for(int i=0;i<m;i++){
            people.push(people.front());
            people.pop();//模拟循环
        }
        // printf("%d ",people.front());
        win=people.front();//每一次淘汰前记录当前解，因为这个算法实际也踢出了最后一个元素
        people.pop();
    }
    printf("\n");
    return win;
}//第二个算法
/*
算法思路：用队列实现这个算法
每一次都读取头元素，如果不是要踢出的人则将头元素出队并入队，否则则出队。模拟循环的同时逐渐缩小数据量，基于stl的队列大大简化了代码量
我们不想象所有人围成一圈，而是所有人排成一队，每次报数就走到最后（除了应该淘汰的那个人）
时间复杂度：O(MN)，空间复杂度：O(N)
*/
//这个问题存在递推公式