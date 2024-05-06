#include<iostream>
#include<queue>
#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
//任务类
class Task{
    public:
    Task(std::function<void()>func):func_(func){}
    void operator()() {func_();}
    private:
    std::function<void()>func_;
};
//线程池类
class ThreadPool{
    public:
    ThreadPool(int threadnum):stop_(false){
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

    template<class F>
    void enqueue(F&& task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            tasks_.emplace(std::forward<F>(task));
        }
        condition_.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread &worker : workers_)
            worker.join();
    }

    private:
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;
    std::condition_variable condition_;
    std::mutex queue_mutex_;
    bool stop_;
};

//任务调度类
class TaskScheduler {
public:
    TaskScheduler(size_t numThreads) : threadPool_(numThreads) {}
    template<class F>
        void addTask(F&& task) {
            threadPool_.enqueue(Task(std::forward<F>(task)));
        }

private:
    ThreadPool threadPool_;
};

int main() {
    TaskScheduler scheduler(10); // 创建一个拥有10个线程的任务调度程序

    // 添加一些计算矩阵的任务到任务队列
    for (int i = 1; i <=10; ++i) {
        scheduler.addTask([i]() {
            // 这里模拟一个简单的任务，计算i的阶乘
            int result = 1;
            for (int j = 1; j <= i; ++j) {
                result *= j;
            }
            std::cout << "Factorial of " << i << " is " << result << std::endl;
        });
    }

    return 0;
}
