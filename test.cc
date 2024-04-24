#include <iostream>
#include <thread>

// 线程函数，打印一条消息
void threadFunction() {
    std::cout << "Hello from thread!\n";
}

int main() {
    // 创建一个新线程，并将 threadFunction 作为线程函数
    std::thread myThread(threadFunction);

    // 主线程继续执行自己的任务
    std::cout << "Hello from main!\n";

    // 等待新线程执行结束
    myThread.join();

    return 0;
}
