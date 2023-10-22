#include <iostream>
#include <stack>
#include <string>
using namespace std;
//本程序实现了左右大/中/小括号的匹配
bool BucketMatching(string);

int main(){
    string s;
    system("chcp 65001");
    cout<<"请输入一个字符串："<<endl;
    getline(cin,s);//输入一行字符串，使用string类
    if(BucketMatching(s)){
        cout<<"Matched!"<<endl;
    }
    else cout<<"Unmatched!"<<endl;
    system("pause");
    return 0;
}
bool BucketMatching(string str){
    stack<char> bucket;
    for(int i=0;i<str.length();i++){
        switch (str[i]){
            case '(':
            case '[':
            case '{':
                bucket.push(str[i]);
                break;
            case ')':
                if(bucket.top()!='(')
                    return false;
                else{
                    bucket.pop();
                    break;
                } 
            case ']':
                if(bucket.top()!='[')
                    return false;
                else{
                    bucket.pop();
                    break;
                } 
            case '}':
                if(bucket.top()!='{')
                    return false;
                else{
                    bucket.pop();
                    break;
                }
            default:
                break;
        }
    }
    return bucket.empty();
}