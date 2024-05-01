#include<iostream>
#include<vetor>
#include<thread>
#include<random>
#include<mutex>

void randomdata(std::vector<int>&data,int datasize,int maxnum,int minnum){
std::srand(std::time(nullptr)); // 设置随机数种子为当前时间，以便每次生成的随机数序列不同
    for (int i = 0; i < size; ++i) {
        arr.push_back(std::rand() % 1000); 
    }
}

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        int pivotIndex = i + 1;

        std::thread tLeft(quickSort, std::ref(arr), left, pivotIndex - 1);
        std::thread tRight(quickSort, std::ref(arr), pivotIndex + 1, right);

        tLeft.join();
        tRight.join();
    }
}

void mergeSortedSubarrays(const std::vector<std::vector<int>>& subarrays, std::vector<int>& sortedData) {
    int dataSize = sortedData.size();
    int currentIndex = 0;
    std::vector<int> indexes(subarrays.size(), 0);
    while (currentIndex < dataSize) {
        int minIndex = -1;
        int minValue = INT_MAX;
        for (int i = 0; i < subarrays.size(); ++i) {
            if (indexes[i] < subarrays[i].size() && subarrays[i][indexes[i]] < minValue) {
                minIndex = i;
                minValue = subarrays[i][indexes[i]];
            }
        }
        sortedData[currentIndex++] = minValue;
        ++indexes[minIndex];
    }
}

void mergeThread(const std::vector<std::vector<int>>& subarrays, std::vector<int>& sortedData) {
    // Wait until sorting is done
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });

    mergeSortedSubarrays(subarrays, sortedData);
}


int main(){
    int datasize=100000;
    int maxnum=100000;
    int minnum=0;
    std::vector<int> data;

    randomdata(data,datasize,maxnum,minnum);
    int numthread=std::thread::hardware_concurrency();
    int arraysize=datasize/numthread;
    std::vector<std::vector<int>>mularray(numthread);
    for(int i=0;i<numthread;i++){
        auto start=data.begin()+numsthread;
        auto end=(i==numthread-1)?data.end():data.begin()+numthread;
        mularray[i].assign(start,end);
    }
    //创建线程进行排序
    std::vector<std::thread> threads;
    for(int i=0;i<numthread;i++){
        threads.emplace(quicksort,std::ref(mularray[i]),0,mularray.size()-1);
        //threads.push_back(threads(quicksort,std::ref(mularray[i]),0,mularray.size()-1);
    }
    std::thread merge(mergeThread, std::cref(mularrays), std::ref(data))
    for(auto &t :threads){
        t.join();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();

    mergeThr.join();
    
    
}