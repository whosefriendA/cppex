#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<queue>
#include<filesystem>
namespace fs=std::filesystem;
class SearchConfig {
    public:
    std::string root_path;    // 要搜索的根目录
    fs::path directory;
    std::string file_type;    // 要搜索的文件类型，如 ".txt"、".cpp" 等
      int max_concurrency = 1;  // 默认最大并发数
    int max_depth = 1;        // 默认最大搜索深度
    bool skip_hidden = true;       // 默认跳过隐藏文件或目录
    std::vector<std::string> skip_paths;   // 要跳过的目录或文件的路径
    SearchConfig(){   
    std::cout<<"输入要搜索的根目录"<<std::endl;
    std::cin>>root_path;
    directory=root_path;
    std::cout<<"输入要搜索的文件类型"<<std::endl;
    std::cin>>file_type;
        // 输入默认值的标记为 -1
    std::cout << "输入最大并发数（输入 -1 使用默认值）" << std::endl;
    std::cin >> max_concurrency;
        if (max_concurrency == -1)
            max_concurrency = 1;
    std::cout << "输入最大搜索深度（输入 -1 使用默认值）" << std::endl;
    std::cin >> max_depth;
        if (max_depth == -1)
            max_depth = 1;
    std::cout<<"是否跳过隐藏文件或目录( 1 表示是, 0 表示否)"<<std::endl;
    std::cin>>skip_hidden;
    std::cout<<"要跳过的目录或文件的路径(输入 end 结束输入)"<<std::endl;
    std::string onepath;
     while (onepath!="end") {
        std::cin >> onepath;
        skip_paths.push_back(onepath);
    }

    }

};
class Searchfile{
public:
    Searchfile(const SearchConfig& newconfig) : config(newconfig){}

    void operator()() {
        std::queue<fs::path> directories;
        directories.push(config.root_path);
        std::mutex mtx;
        std::vector<std::thread> threads;
        for (int i = 0; i < config.max_concurrency; ++i) {
            threads.emplace_back([&]() {
                while (true) {
                    fs::path directory;
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        if (directories.empty()) break;
                        directory = directories.front();
                        directories.pop();
                    }
                    searchInDirectory(directory);
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
private:
    SearchConfig config;
    std::mutex cout_mtx;

    bool Skippath(const fs::path& path) {
        for (const auto& skip_path : config.skip_paths) {
            if (path == skip_path) {
                return true; // 跳过指定路径
            }
        }
        return false;
    }
    bool Skiphidden(const fs::path& path){
        if (config.skip_hidden && path.filename().string()[0] == '.') {
            return true; // 跳过隐藏文件
        }
        return false;
    }
    void searchInDirectory(const fs::path& directory, int depth = 0) {
        if (depth > config.max_depth) return;
        if (!fs::exists(directory) || !fs::is_directory(directory)) return;
        if (Skippath(directory)) return;
        for (auto& file : fs::directory_iterator(directory)) {
            if (Skippath(file.path())) continue;
            if (fs::is_directory(file)) {
                searchInDirectory(file, depth + 1);
            } else {
                if (Skiphidden(file.path())) continue;
                if (file.path().extension() == config.file_type) {
                    std::lock_guard<std::mutex> lock(cout_mtx);
                    std::cout << file.path() << std::endl;
                }
            }
        }
    }
};

int main(){
    SearchConfig newconfig;
    Searchfile newsearch(newconfig);
    newsearch();
    return 0;
}
