#pragma once
#include <string>
#include <vector> // 存数组
#include <map> // 存对象(键值对)

namespace yazi {
namespace json { // 避免冲突，使用二级命名空间

    class Json
    {
        public:
            enum Type // 枚举类型，json的6大类型
            {
                json_null = 0,
                json_bool,
                json_int,
                json_double,
                json_string,
                json_array,
                json_object
            };

            // 构造函数
            Json();
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const char* value); // C格式字符串
            Json(const std::string& value); // C++格式字符串
            Json(Type type); // 根据枚举类型来构造
            Json(const Json &other); //拷贝构造

            // 基本类型的运算符重载
            operator bool();
            operator int();
            operator double();
            operator std::string();

            // 重载中括号，添加数据
            Json & operator [] (int index);
            void append(const Json& other);

            // 以字符串形式，返回Json的具体内容
            std::string str() const;

            // 重载中括号，按指定传入的字符串类型来添加值
            Json & operator [] (const char* key); // C和C++风格的字符串
            Json & operator [] (const std::string &key);
            // 重载赋值运算符
            void operator = (const Json &other);
            void copy(const Json &other); // 封装重复使用的代码
            // 释放原先创建的地址空间
            void clear();

            // 对数组中的内容遍历
            typedef std::vector<Json>::iterator iterator;
            iterator begin() { // 定义两个迭代器
                return (m_value.m_array)->begin();
            }
            iterator end() {
                return (m_value.m_array)->end();
            }

        private:
            union Value // 联合体定义值，占用内存会更小(取决于double)
            {
                bool m_bool;
                int m_int;
                double m_double;
                std::string* m_string; // 字符串
                std::vector<Json>* m_array; // 数组
                std::map<std::string, Json>* m_object; // 对象
            };

            Type m_type; // 两个字段
            Value m_value;
    };

}    
}