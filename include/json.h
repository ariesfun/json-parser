#pragma once
#include <string>
#include <vector>
#include <map>

namespace swift {
namespace json {

class Json {
public:
    enum Type // 标记待解析内容的类型
    {
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object,
    };

    Json();
    ~Json();
    Json(bool value); // 根据值构造
    Json(int value);
    Json(double value);
    Json(const char* value); // C和C++风格字符串
    Json(const std::string &value); 
    Json(Type type); // 根据枚举类型来构造
    Json(const Json &other); // 拷贝构造

    Json &operator [] (int index);  // 数组初始化操作，按下标取值
    void append(const Json &other); // 数组添加数据
    void append(Json&& value); // 移动语义

    // 提供Json类型的API操作
    operator bool(); // 基本类型的运算符重载
    operator int();
    operator double();
    operator std::string();

    // 重载中括号，按指定传入的字符串类型来添加值
    Json &operator [] (const char* key); // C和C++风格的字符串
    Json &operator [] (const std::string &key);
    Json &operator = (const Json &other); // 重载赋值及等号运算符
    Json &operator = (Json&& other);
    bool operator == (const Json &other);
    bool operator != (const Json &other);

    void clear();
    void parse(const std::string &str); // 解析传入的字符串
    std::string str() const; // 以字符串形式，返回解析Json的具体内容

    bool isNull() const; // json的类型判断
    bool isBool() const;
    bool isInt() const;
    bool isDouble() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

    bool asBool() const; // 显示转换
    int asInt() const;
    double asDouble() const;
    std::string asString() const;
    
    bool has(int index);  // 判断数组里有没有某个索引
    bool has(const char* key); // 判断对象里有没有某个key
    bool has(const std::string &key);

    void remove(int index); // 按下标及key来删除元素
    void remove(const char* key);
    void remove(const std::string &key);

    Json get(int index); // 取值
    Json get(const char* key);
    Json get(const std::string &key);

    int size() const; 
    bool empty() const; 

    typedef std::vector<Json>::iterator iterator; // 对数组中内容的遍历
    iterator begin() { return (m_value.m_array)->begin(); } // 定义两个迭代器
    iterator end() { return (m_value.m_array)->end(); }

private:
    void copy(const Json &other); 
    void swap(Json &other); 

private:
    union Value // 联合体定义值，节省内存空间
    {
        bool m_bool;
        int m_int;
        double m_double;
        std::string* m_string;
        std::vector<Json>* m_array;
        std::map<std::string, Json>* m_object;
    };

    Type m_type; // 每个json类型都有两个字段
    Value m_value;
};

}}