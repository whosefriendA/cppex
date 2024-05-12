#include<iostream>
#include<semaphore.h>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>
#define phi_num 5
class Phi{
    public:
    void eat(){
        std::thread phieat([this]{std::cout<<this<<"吃完饭，放下了他的筷子"<<std::endl;});
        phieat.join();
    }
};
//方案一  使用互斥锁
// int main(){
//     std::vector<class Phi> Philo(5);
//     std::mutex left_chop;
//     std::mutex right_chop;
//     for(int i=0;i<phi_num;i++){
//         std::unique_lock<std::mutex> lock1(left_chop);
//         std::unique_lock<std::mutex> lock2(right_chop);
//         Philo[i].eat();
//     }
// }
//方案二 使用信号量(这里只能使用c语言的信号量，c++标准库中没有对信号量的直接定义)
int main(){
    sem_t chop(5);
    std::vector<class Phi> Philo(5);
    for(int i=0;i<phi_num;i++){
        sem_wait(&chop[i]);
        sem_wait(&chop[i+1]);
        Philo[i].eat();
        sem_post(&chop[i]);
        sem_post(&chop[i+1]);
    }

}
