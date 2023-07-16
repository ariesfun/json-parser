#include "json.h"

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
            m_value.m_int = other.git.m_int;
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