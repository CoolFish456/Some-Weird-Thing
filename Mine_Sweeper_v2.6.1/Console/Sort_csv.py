#这个脚本简单实现了对排行榜的处理：甄别当前难度，根据时间排序和删除输掉的数据并计算胜率（主程序会调用这个脚本）
import pandas as pd
from sys import argv
script,Diff=argv
# Diff=input()
Diff=int(Diff)
lose=0
if(Diff==1):
    rks=pd.read_csv('Diff1/ranking1.csv',encoding='utf-8',header=0)
elif(Diff==2):
    rks=pd.read_csv('Diff2/ranking2.csv',encoding='utf-8',header=0)
elif(Diff==3):
    rks=pd.read_csv('Diff3/ranking3.csv',encoding='utf-8',header=0)
# print(rks)
for i in rks.index:
    if(rks["Winning"][i]==0):
        lose+=1
rankP=(i+1-lose)/(i+1)
#胜率
rks.drop(rks[rks["Winning"]==0].index,inplace=True)
data=rks.sort_values(by="Time",ascending=True)
if(Diff==1):
    data.to_csv("Diff1/sorted_ranking1.csv",index=False)
elif(Diff==2):
    data.to_csv("Diff2/sorted_ranking2.csv",index=False)
elif(Diff==3):
    data.to_csv("Diff3/sorted_ranking3.csv",index=False)
f=open('RankP.txt','w')
rankP=str(rankP*100)
f.write(rankP)