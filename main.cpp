#include <iostream>
#include <fstream>
#include <sstream>
#include "json.h"
using namespace swift::json;

int main() 
{
    // 解析json文件测试
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

    return 0;
}