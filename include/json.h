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