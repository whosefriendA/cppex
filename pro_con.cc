#include <memory>
#include<iostream>
#include<vector>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>

// 单生产者消费者队列
template<class T>
class SPSCQueue {
public:
    explicit SPSCQueue(int capacity):capacity_(capacity){};
    bool Push(std::unique_ptr<T> item) {
        std::unique_lock<std::mutex> lock(mutex_);
        //缓冲区容量不够时，阻塞线程;
        cv.wait([this]{return queue_.size()<capacity_;});
        queue_.push(item);
        cv.notify_one();
        return true;
    }
    std::unique_ptr<T> Pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        //生产者没有存入数据或者缓冲区为空时，阻塞线程
        cv.wait([this]{return !queue_.empty();});
        //将数据转移给临时对象，等待消费者使用
        auto item=std::move(queue_.front());
        queue_.pop();
        cv.notify_one();
        return item;
    }
private:
    std::condition_variable cv;
    std::queue<std::unique_ptr<T>> queue_;
    int capacity_;
    std::mutex mutex_;
};

//多生产者消费者队列
template<class T>
class MPMCQueue {
public:
    explicit MPMCQueue(int capacity) : capacity_(capacity) {}

    bool Push(std::unique_ptr<T> item) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 缓冲区满，等待消费者取走数据
        cv.wait(lock, [this] { return queue_.size() < capacity_; });
        queue_.push(std::move(item));
        cv.notify_all(); // 唤醒所有消费者线程
        return true;
    }

    std::unique_ptr<T> Pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        //缓冲区空，等待生产者放入数据
        cv.wait(lock, [this] { return !queue_.empty(); });
        auto item = std::move(queue_.front());
        queue_.pop();
        cv.notify_all(); // 唤醒所有生产者线程
        return item;
    }

private:
    std::queue<std::unique_ptr<T>> queue_;
    std::mutex mutex_;
    std::condition_variable cv;
    int capacity_;
};
