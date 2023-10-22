#include <cstdio>
#include <cstdlib>
#include <list>
#include <cmath>
using namespace std;
#define BUCKET_NUM 1000
/*
题目简述：
对于若干个九位数的学生学号，只使用三次桶排序将学号排为有序
*/
void radix_sort(int[],int);
int main(){
    system("chcp 65001");
    printf("题目要求：输入的学号为九位数：\n");
    int StudentID[1000];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&StudentID[i]);
    }
    radix_sort(StudentID,n);
    printf("输出如下：\n");
    for(int i=0;i<n;i++){
        printf("%d ",StudentID[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}
void radix_sort(int num[], int n) {
	int MaxBit = 9;
	list<int>bucket[BUCKET_NUM];
	for (int i = 0, d = 1; i < MaxBit; i+=log10(BUCKET_NUM), d *= BUCKET_NUM) {
		for (int j = 0; j < n; j++)
			bucket[(num[j] / d) % BUCKET_NUM].push_back(num[j]);
		for (int j = 0, k = 0; j < BUCKET_NUM; j++) {
			while (!bucket[j].empty()) { 
				num[k] = bucket[j].front();
				k++;
				bucket[j].pop_front();
			}
		}
		// for (int i = 0; i < n; i++)
		// 	printf("%d ", num[i]);
		// printf("\n");
	}
}//开long就爆了，好啊你