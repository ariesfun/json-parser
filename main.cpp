#include <iostream>
#include <fstream>
#include <sstream>
#include "json.h"
using namespace swift::json;

#include<sys/time.h> // 性能测试

int main() 
{
    /*
    // Test01
    // 反序列化操作，解析json文件测试
    try {
        std::ifstream fin("../json_data/json_test.json"); // 打开文件
        if (!fin.is_open()) {
            throw std::runtime_error("Failed to open the file.");
        }
        std::stringstream ss;
        ss << fin.rdbuf(); // 读取文件
        const std::string &str1 = ss.str(); // stringstream()的str()方法，转为原始字符串格式
        Json res1;
        res1.parse(str1);  // 继续处理json数据
        std::cout << res1.str() << std::endl;

        std::cout << std::endl;
        std::string b_username = res1["data"]["uname"];
        int b_level = res1["data"]["level_info"]["current_level"];
        std::cout << "Your bilibili username: " << b_username << '\n' << "Current level: " << b_level << std::endl; 
        fin.close();

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    // Test02
    // 序列化操作，将数据结构转换成JSON格式的字符串
    std::cout << std::endl;
    Json arr;
    arr[0] = false;
    arr[1] = 100;
    arr[2] = "hhhhh";
    Json obj;
    obj["bool"] = true;
    obj["int"] = 777;
    obj["double"] = 999.9;
    obj["array"] = arr;
    std::cout << obj.str() << std::endl;

    */

    /* 
    // 解析性能测试
    try {
        std::ifstream fin("../json_data/json_test.json");
        if (!fin.is_open()) {
            throw std::runtime_error("Failed to open the file.");
        }
        std::stringstream ss;
        ss << fin.rdbuf();
        const std::string& data = ss.str();

        struct timeval tv;
        gettimeofday(&tv, NULL);
        int start_sec = tv.tv_sec;
        int start_usec = tv.tv_usec;
        const int max = 100000;
        for(int i = 0; i < max; i++) {
            Json json;
            json.parse(data);
        }
        gettimeofday(&tv, NULL);
        int end_sec = tv.tv_sec;
        int end_usec = tv.tv_usec;
        double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
        std::cout << time_diff / 1000 / max << "ms" << std::endl;
        
        }catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    */

    return 0;
}