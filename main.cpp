#include <iostream>
#include <fstream>
#include <sstream>
#include "json.h"

using namespace swift::json;

int main() {

    // test09，解析json文件
    std::ifstream fin("./json_test.json"); // 打开文件
    std::stringstream ss;
    ss << fin.rdbuf(); // 读取文件
    const std::string &str1 = ss.str(); // stringstream()的str()方法，转为字符串
    Json res1;
    res1.parse(str1);
    std::cout << res1.str() << std::endl;

    std::string b_username = res1["data"]["uname"];
    int b_level = res1["data"]["level_info"]["current_level"];
    std::cout << "your bilibili username: " << b_username << '\n' << "current level: " << b_level << std::endl; 

    std::cout << "Debug Test" << std::endl;
    return 0;
}