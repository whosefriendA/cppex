#include<iostream>
#include<vetor>
#include<thread>
#include<random>
void randomdata(std::vector<int>&data,int datasize,int maxnum,int minnum){
std::random_device rd;//随机种子
std::mt19937 gen(rd());//随机数引擎
//分布函数
std::uniform_int_distribution dis(minnum,maxnum);
for(int i=0;i<datasize;i++){
    data.push_back(dis(gen))
}
}
int main(){
    int datasize=100000;
    int maxnum=100000;
    int minnum=0;
    std::vector<int> data;
    
}