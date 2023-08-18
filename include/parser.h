#pragma once
#include <string>
#include <iostream>
#include "json.h"

namespace swift {
namespace json {

class Parser {
public:
    Parser(); 
    void load_string(const std::string &str);  // 加载将要解析的串
    Json parse(); // 解析核心，返回Json类型

private:
    // 忽略空白字符和获取下一个字符
    void skip_white_space();
    char get_next_token();

    // 解析不同类型的内容
    Json parse_null();
    Json parse_bool();
    Json parse_number(); // int and double
    std::string parse_string();
    Json parse_array();
    Json parse_object();

private:
    std::string m_str; // 解析的内容及对应的索引
    int m_idx;
};
    
}}