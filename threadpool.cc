#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
class Task{
    public:
    Task(std::function<void()>func):func_(func){}
    std::opreator()(){func_();}
    private:
    std::function<void()>func_;
}
class Threadpool{
    public:
    Threadpool(int threadnum):threadnum_(threadnum){
    if(threadnum<1)
    std::cerr<<"wrong thread number";
    for(int i=0;i<threadnum;i++){
        workers_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
                        if (stop_ && tasks_.empty())
                            return;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }

    }

}