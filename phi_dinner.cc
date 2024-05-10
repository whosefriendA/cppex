#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>
#define phi_num 5
class Phi{
    public:
    void eat(){
        std::thread phieat([this]{std::cout<<this<<"吃得饱饱，放下了他的筷子"<<std::endl;});
        phieat.join();
    }
};
//方案一  使用互斥锁（可能死锁）
int main(){
    std::vector<class Phi> Philo(5);
    std::mutex left_chop;
    std::mutex right_chop;
    for(int i=0;i<phi_num;i++){
        std::unique_lock<std::mutex> lock1(left_chop);
        std::unique_lock<std::mutex> lock2(right_chop);
        Philo[i].eat();
    }
}
//方案二 使用信号量