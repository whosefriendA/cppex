#include<iostream>
#include<functional>
//使用标准库定义的函数对象（函数对象为用重载函数调用符实现的对象）
std::plus<int> intadd;
std::negate<int> intnegate;
int main(){
    int a=1;
    int b=2;
    std::cout<<intadd(a,b)<<std::endl;
    std::cout<<intnegate(a) <<intnegate(b)<<std::endl;
    return 0;
}