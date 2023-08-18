#pragma once
#include <string>
#include <iostream>
#include "json.h"

namespace swift {
namespace json {

class Parser {
public:
    Parser(); 
    
    // 加载即将要解析的串
    void load(const std::string &str);

    // 解析核心实现，返回Json类型
    Json parse();

private:
    // 忽略空白字符
    void skip_white_space();
    // 获取下一个字符
    char get_next_token();

    // 解析不同类型的内容
    Json parse_null();
    Json parse_bool();
    Json parse_number(); // int和double类型
    std::string parse_string(); // 返回字符串类型
    Json parse_array();
    Json parse_object();

private:
    std::string m_str; // 解析的内容及对应的索引
    int m_idx;
};
    
}}