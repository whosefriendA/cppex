#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<filesystem>
class SearchConfig {
    public:
    SearchConfig(){   
    std::cout<<"输入要搜索的根目录"<<std::endl;
    std::cin>>root_path;
    std::cout<<"输入要搜索的文件类型"<<std::endl;
    std::cin>>file_type;
    std::cout<<"输入最大并发数"<<std::endl;
    std::cin>>max_concurrency;
    std::cout<<"输入最大搜索深度"<<std::endl;
    std::cin>>max_depth;
    std::cout<<"是否跳过隐藏文件或目录"<<std::endl;
    std::cin>>skip_hidden;
    std::cout<<"要跳过的目录或文件的路径"<<std::endl;
    std::string onepath;
     while (onepath!="end") {
        std::cin >> onepath;
        skip_paths.push_back(onepath);
    }

    }
    private:
    std::string root_path;    // 要搜索的根目录
    std::string file_type;    // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;      // 最大并发数
    int max_depth;            // 最大搜索深度
    bool skip_hidden;         // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;   // 要跳过的目录或文件的路径
};

class Searchfile{
    public:
    
    private:

    std::vector<std::thread> threads;
    
};
int main(){
    class SearchConfig newconfig;
    
    return 0;
}
