#include "json.h"
#include "parser.h"
#include <sstream>

using namespace swift::json; 

Json::Json() : m_type(json_null) {}

Json::~Json() {
    clear();
}

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

Json::Json(const char* value) : m_type(json_string)
{
    m_value.m_string = new std::string(value);
}

Json::Json(const std::string &value) : m_type(json_string)
{
    m_value.m_string = new std::string(value);
}

Json::Json(const Json &other) : m_type(json_null)
{
    copy(other);
}

Json::Json(Json&& other)
{
    swap(other);
    
}

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

Json &Json::operator [] (int index)
{
    if(m_type != json_array) {
        throw std::logic_error("not array type");
    }
    if(index < 0) {
        throw std::logic_error("array index < 0 error");
    }
    int size = (m_value.m_array)->size(); // 获取当前元素个数
    if(index >= size) { // 下标超过当前值，需要扩容将值赋空
        throw std::logic_error("array index out of range");
    }
    return (m_value.m_array)->at(index); // 返回数组对应索引的具体值
}

void Json::append(const Json &other)
{
    if(m_type != json_array) {
        clear(); // 对原数组进行清理
        m_type = json_array;
        m_value.m_array = new std::vector<Json>(); // 创建数组
    }
    (m_value.m_array)->push_back(other); // 已经是数组，向容器尾部添加一个Json型元素
}

void Json::append(Json&& value) // 传入右值引用，直接移动到数组中
{
    if(m_type != json_array) {
        clear(); 
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(std::move(value));
}

Json::operator bool() 
{
    if(m_type != json_bool) {
        throw std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}

Json::operator int()
{
    if(m_type != json_int) {
        throw std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}

Json::operator double()
{
    if(m_type != json_double) {
        throw std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}

Json::operator std::string()
{
    if(m_type != json_string) {
        throw std::logic_error("type error, not string value");
    }
    return *(m_value.m_string); // 返回字符串指针的内容
}

Json &Json::operator [] (const char* key) // C和C++风格的字符串
{
    std::string name(key);
    return (*this)[name]; // 调用下面的实现
}

Json &Json::operator [] (const std::string &key) // 用json["key"]的语法来访问和操作Json对象的属性
{
    if(m_type != json_object) { 
        clear();
        m_type = json_object; // 转为对象类型
        m_value.m_object = new std::map<std::string, Json>();
    }
    return (*(m_value.m_object))[key]; // 获取map的内容
}

Json &Json::operator = (const Json &other) // 类似拷贝构造函数
{
    clear(); // 先清理内存，再拷贝
    copy(other);
    return *this;
}

Json &Json::operator = (Json&& other)
{
    swap(other); // 利用移动语义避免深拷贝，降低内存开销
    return *this;
}

bool Json::operator == (const Json &other)
{
    if(m_type != other.m_type) {
        return false;
    }
    switch (m_type)
    {
        case json_null:
            return true;
        case json_bool:
            return m_value.m_bool == other.m_value.m_bool;
        case json_int:
            return m_value.m_int == other.m_value.m_int;
        case json_double:
            return m_value.m_double == other.m_value.m_double;
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string); // 比较两字符串指针内容
        case json_array:
            return m_value.m_array == other.m_value.m_array;
        case json_object:
            return m_value.m_object == other.m_value.m_object;
        default:
            break;
    }
    return false;
}

bool Json::operator != (const Json &other)
{
    return !((*this) == other); // 利用前面的相等重载取反
}

void Json::copy (const Json &other) // 封装复用代码，进行拷贝的公共函数
{
    clear();
    m_type = other.m_type;
    switch(m_type) // 由类型来初始化值
    {
        case json_null:
        case json_bool:
        case json_int:
        case json_double:
            m_value= other.m_value;
            break;
        case json_string: // 进行深拷贝，防止因共享指针而导致内存泄漏   
        {                           
            if(other.m_value.m_string != nullptr) {
                m_value.m_string = new std::string(*(other.m_value.m_string)); 
            }
            break;
        }
        case json_array:
        {
            if(other.m_value.m_array != nullptr) {
                m_value.m_array = new std::vector<Json>();
                for(auto it = (other.m_value.m_array)->begin(); it != (other.m_value.m_array)->end(); it++) {
                    m_value.m_array->push_back(*it);
                }
            }
            break;
        }
        case json_object:
        {
            if(other.m_value.m_object != nullptr) {
                m_value.m_object = new std::map<std::string, Json>();
                for(auto it = (other.m_value.m_object)->begin(); it != (other.m_value.m_object)->end(); it++) {
                    (*(m_value.m_object))[it->first] = it->second;
                }
            }
            break;
        }
        default:
            break;
    }
}

void Json::swap(Json &other) // 在两个临时对象之间交换资源，从而实现资源的移动
{
    Type tmp_type = m_type;
    Value tmp_value = m_value;
    m_type = other.m_type;
    m_value = other.m_value;
    other.m_type = tmp_type;
    other.m_value = tmp_value;
}

void Json::clear() // 释放原先创建的地址空间
{
    switch(m_type)
    {
        case json_null:
        case json_bool:
        case json_int:
        case json_double:
            break;
        case json_string:
        {
            if(m_value.m_string != nullptr) {
                delete m_value.m_string;
                m_value.m_string = nullptr;
            }
            break;
        }   
        case json_array:
        {
            if(m_value.m_array != nullptr) {
                for(auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++) {
                    it->clear(); // 递归调用
                }
                delete m_value.m_array; // 数组里的内容可能也涉及动态内存分配，要先一步释放
                m_value.m_array = nullptr;
            }
            break;
        }
        case json_object:
        {
            if(m_value.m_object != nullptr) {
                for(auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++) {
                    (it->second).clear(); 
                }
                delete m_value.m_object;
                m_value.m_object = nullptr;
                break;
            }
            break;
        }
        default:
            break;
        m_type = json_null; // 类型设为空
    }
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
        {
            ss << '[';
            for(auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++) {
                if(it != (m_value.m_array)->begin()) { // 添加逗号分隔
                    ss << ',';
                }
                ss << it->str(); // 递归调用
            }
            ss << ']';
            break;
        }
        case json_object: // 对象转字符串
        {
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
        }
        default:
            break;
    }
    return ss.str();
}

bool Json::isNull() const 
{
    return m_type == json_null; 
}

bool Json::isBool() const 
{
    return m_type == json_bool; 
}

bool Json::isInt() const 
{ 
    return m_type == json_int; 
}

bool Json::isDouble() const 
{
    return m_type == json_double;
}

bool Json::isString() const 
{
    return m_type == json_string;
}

bool Json::isArray() const {
    return m_type == json_array;
}

bool Json::isObject() const 
{
    return m_type == json_object;
}

bool Json::asBool() const // 四种显示的类型转换，加const不让函数体内对类对象进行修改
{
    if(m_type != json_bool) {
        throw std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}

int Json::asInt() const
{
    if(m_type != json_int) {
        throw std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}

double Json::asDouble() const
{
    if(m_type != json_double) {
        throw std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}

std::string Json::asString() const
{
    if(m_type != json_string) {
        throw std::logic_error("type error, not string value");
    }
    return *(m_value.m_string); // 返回字符串的内容
}

bool Json::has(int index) // 判断数组里有没有某个索引
{
    if(m_type != json_array) {
        return false;
    }
    int size = (m_value.m_array)->size();
    return (index >= 0 && index < size);
}

bool Json::has(const char* key)
{
    std::string name(key);
    return has(name); // 调用下面函数的实现
}

bool Json::has(const std::string &key)
{
    if(m_type != json_object) {
        return false;
    }
    // m_value.m_object是一个指向json对象的指针
    // find(key)返回一个迭代器，指向键值为key的元素; end()返回一个迭代器，指向对象的末尾位置
    // 不等，说明找到了对应的键值key
    return ((m_value.m_object)->find(key) != m_value.m_object->end());
}

// 按下标及key来删除元素
void Json::remove(int index) // 移除数组元素
{
    if(m_type != json_array) {
        return;
    }
    int size = (m_value.m_array)->size();
    if(index < 0 || index >=size) {
        return;
    }
    // 下标在范围内，获取到要删除元素的迭代器，用erase()删掉
    (m_value.m_array)->at(index).clear(); // 需要先清理内存
    (m_value.m_array)->erase((m_value.m_array)->begin() + index); 
}

void Json::remove(const char* key) // 移除对象元素
{
    std::string name = key;
    return remove(name); // 调用下面的remove函数的实现
}

void Json::remove(const std::string &key)
{
    if(m_type != json_object) {
        return;
    }
    auto it = m_value.m_object->find(key);
    if(it == m_value.m_object->end()) {
        return;
    }
    it->second.clear(); // 对应的键key存在，先清理内存，再删除
    (m_value.m_object)->erase(key);
}

Json Json::get(int index) 
{
    if(!has(index)) {
        return Json();
    }
    return (*(m_value.m_array))[index];
}

Json Json::get(const char* key) 
{
    if(!has(key)) {
        return Json();
    }
    return (*(m_value.m_object))[key];
}

Json Json::get(const std::string &key) 
{
    if(!has(key)) {
        return Json();
    }
    return (*(m_value.m_object))[key];
}

int Json::size() const // 获取json中的数组或对象的个数
{
    switch (m_type) {
    case json_array:
        return (m_value.m_array)->size();
    case json_object:
        return (m_value.m_object)->size();    
    default:
        break;
    }
    throw std::logic_error("size value type error!");
    return 0;
}

bool Json::empty() const // 判断是否为空
{
    switch (m_type) {
    case json_null:
        return true;
    case json_array:
        return (m_value.m_array)->empty();
    case json_object:
        return (m_value.m_object)->empty();    
    default:
        break;
    }
    return false;
}

 void Json::parse(const std::string &str)
 {
    Parser p;
    p.load_string(str);
    *this = p.parse(); // 将解析后的结果传给Json本身
 }