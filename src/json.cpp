#include "json.h"
#include <sstream>

using namespace yazi::json; 

Json::Json() : m_type(json_null) {}

Json::Json(bool value) : m_type(json_bool)
{
    m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int)
{
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double)
{
    m_value.m_double = value;
}

// C风格字符串(存指针，涉及内存管理)
Json::Json(const char* value) : m_type(json_string)
{
    m_value.m_string = new std::string(value);
}

// C++风格字符串
Json::Json(const std::string& value) 
{
    m_value.m_string = new std::string(value);
}

// 根据枚举类型来构造
Json::Json(Type type) : m_type(type)
{
    switch(type) // 由类型来初始化值
    {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new std::string("");
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<std::string, Json>();
            break;
        default:
            break;
    }
}

// 拷贝构造
Json::Json(const Json &other)
{
    m_type = other.m_type;
    switch(m_type) // 由类型来初始化值
    {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:                              // 浅拷贝，只存储指针
            m_value.m_string = other.m_value.m_string;  
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
            break;
        default:
            break;
    }
}

// 四个基本类型的运算符重载
Json::operator bool() 
{
    if(m_type != json_bool) {
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}

Json::operator int()
{
    if(m_type != json_int) {
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}

Json::operator double()
{
    if(m_type != json_double) {
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}

Json::operator std::string()
{
    if(m_type != json_string) {
        throw new std::logic_error("type error, not string value");
    }
    return *(m_value.m_string); // 返回字符串指针的内容
}

Json & Json::operator [] (int index)
{
    if(m_type != json_array) {
        m_type = json_array;
        m_value.m_array = new std::vector<Json>(); // 创建数组
    }
    if(index < 0) {
        throw new std::logic_error("array[] index < 0");
    }
    int size = (m_value.m_array)->size(); // 获取当前元素个数
    if(index >= size) { // 下标超过当前值，需要扩容将值赋空
        for(int i = size; i <= index; i++) {
            (m_value.m_array)->push_back(Json());
        }
    }
    return (m_value.m_array)->at(index); // 返回数组对应索引的具体值
}

void Json::append(const Json& other)
{
    if(m_type != json_array) {
        m_type = json_array;
        m_value.m_array = new std::vector<Json>(); // 创建数组
    }
    // 已经是数组
    (m_value.m_array)->push_back(other); // 向容器尾部添加一个Json型元素
}

std::string Json::str() const
{
    std::stringstream ss;
    switch(m_type) 
    {
        case json_null:
            ss << "null"; // 写入空值
            break;
        case json_bool:
            if(m_value.m_bool) {
                ss << "true";
            }else {
                ss << "false";
            }
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << '\"' << *(m_value.m_string) << '\"';
            break;
        case json_array: // 数组转字符串
            ss << '[';
            for(auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++) {
                if(it != (m_value.m_array)->begin()) { // 添加逗号分隔
                    ss << ',';
                }
                ss << it->str(); // 递归调用
            }
            ss << ']';
            break;
        case json_object: // 对象转字符串
            ss << '{';
            for(auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++) {
                if(it != (m_value.m_object)->begin()) {
                    ss << ',';
                }
                // 输入键值对内容，值通过递归调用获得
                ss << '\"' << it->first << '\"' << ':' << it->second.str(); 
            }
            ss << '}';
            break;
        default:
            break;
    }
    return ss.str();
}