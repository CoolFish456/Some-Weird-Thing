//本程序能够判断回文字符串
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
void inputStr(char str[]){
    int i=0;
    char ch;
    while(scanf("%c",&ch)&&ch!='\n')str[i++]=ch;
    str[i]='\0';
}
char* reverse(char s[]){
    int i=0,j=strlen(s)-1;
    static char r[1000];
    while(i<=j){
        r[i]=s[j];
        r[j]=s[i];
        i++;
        j--;
    }
    return r;
}
int alg1(char str[]){
    int i=0,j=strlen(str)-1;
    while(i<=j && str[i]==str[j]){
        i++;
        j--;
    }
    if(i<=j)return 0;
    else return 1;
}
int alg2(char str[]){
    char* rstr;
    rstr=reverse(str);
    int i=0,j=0;
    while(i<strlen(str)&&j<strlen(str)&&str[i]==rstr[j]){
        i++;
        j++;
    }
    if(i<strlen(str)||j<strlen(str))return 0;
    else return 1;
}
int main(){
    char test[1000]={0};
    inputStr(test);
    if(alg2(test))printf("OK\n");
    else printf("Not OK\n");
    system("pause");
    return 0;
}