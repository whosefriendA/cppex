#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>
#define phi_num 5
class Phi{
    public:
    eat(){
        std::thread phieat([this]{std::cout<<this<<"吃得饱饱，放下了他的筷子";})
    }
    ~Phi(){
        phieat,join();
    }
}
//方案一  使用互斥锁（可能死锁）
int main(){
    std::vector<class Phi>(5);
    std::mutex left_chop;
    std::mutex right_chop;
    std::unique_lock<mutex> lock(left_chop);
    std::unique_lock<mutex> lock(right_chop);
    for(int i=0;i<phi_num;i++){
        std::unique_lock<mutex> lock(left_chop);
        std::unique_lock<mutex> lock(right_chop);
        
    }
}