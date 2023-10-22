#include <iostream>
#include <stack>
using namespace std;
//这个程序可以将一个非负十进制数转化为最高十六进制数(做除法->求余数->倒序输出所有余数，很适合使用栈)
static char NumTrans[21]="0123456789ABCDEFGHIJ";
int main(){
    unsigned long long num;
    int scale;
    stack<char> rest;
    char temp;
    cout<<"Input the number and the scale(up to 16)"<<endl;
    cin>>num>>scale;
    while(num>0){
        temp=NumTrans[num%scale];
        rest.push(temp);
        num/=scale;
    }
    while(!rest.empty()){
        cout<<rest.top();
        rest.pop();
    }
    cout<<endl;
    system("pause");
    return 0;
}
