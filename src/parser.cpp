#include "parser.h"

using namespace yazi::json;

// 默认构造
Parser::Parser() : m_str(""), m_idx(0) {}

// 加载字符串
void Parser::load(const std::string &str)
{
    m_str = str; // 保存串
    m_idx = 0;
}

// 忽略空白字符
void Parser::skip_white_space()
{
    // char ch = m_str[m_idx]; 用ch判断错误写法，循环后下标会变
    while(m_str[m_idx] == ' ' || m_str[m_idx] == '\n' || m_str[m_idx] == '\r' || m_str[m_idx] == '\t') {
        m_idx++;
    }
}

// 获取下一个字符
char Parser::get_next_token()
{   
    skip_white_space();
    char ch = m_str[m_idx];
    m_idx++;
    return ch; // 等价于 return m_str[m_index++];
}

Json Parser::parse() // 解析核心
{
    char ch = get_next_token();
    switch(ch)
    {
        case 'n':
            m_idx--;
            return parse_null();
        case 't':
        case 'f':
            m_idx--;
            return parse_bool();
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            m_idx--;
            return parse_number(); 
        case '"':
            return Json(parse_string()); // 通过返回的string来构造字符串类型的Json对象
        case '[':
            return parse_array();
        case '{':
            return parse_object();
        default:
            break;
    }
    // 其他字符时，抛出异常
    throw std::logic_error("unexpected char error");    
}

// 解析不同类型的内容
Json Parser::parse_null()
{
    if(m_str.compare(m_idx, 4, "null") == 0) {
        m_idx += 4;
        return Json();
    }
    throw std::logic_error("parser null error");
}   

Json Parser::parse_bool()
{
    if(m_str.compare(m_idx, 4, "true") == 0) {
        m_idx += 4;
        return Json(true);
    }
    else if(m_str.compare(m_idx, 5, "false") == 0) {
        m_idx += 5;
        return Json(false);
    }
    throw std::logic_error("parser bool error");
}

Json Parser::parse_number() // int和double类型
{
    int pos = m_idx; // 记录初始下标
    if(m_str[m_idx] == '-') { // 是负数
        m_idx++;
    }
    if(!isdigit(m_str[m_idx])) { // 不是数字时，抛异常
        throw std::logic_error("parser number error");
    }
    while(isdigit(m_str[m_idx])) { // 数字和字符数字？？？
        m_idx++;
    }
    // 没有遇到小数点，认为它是整数
    if(m_str[m_idx] != '.') { 
        // 字符串转整数，c_str()返回指向C字符串的指针常量 
        // 将从pos开始的子字符串转换为整数，并返回对应的Json对象
        int n = std::atoi(m_str.c_str() + pos); // pos：可选参数，指向存储第一个无效字符位置的指针
        return Json(n);
    }

    m_idx++; // 遇到小数点，先跳过
    if(!isdigit(m_str[m_idx])) { // 不是数字时
        throw std::logic_error("parser number error");
    }
    // 认为是浮点数
    while(isdigit(m_str[m_idx])) {
        m_idx++;
    }
    // 将从pos开始的子字符串转换为浮点数，并返回对应的Json对象
    double f = std::atof(m_str.c_str() + pos);
    return Json(f);
}

// 字符串解析，需要处理一些转义字符
std::string Parser::parse_string()
{
    std::string res;
    while(true) {
        char ch = m_str[m_idx++]; // 不进行空白字符过滤(保留'\n','\t'等)
        if(ch == '"') {
            break;
        }
        if(ch == '\\') { // 遇到转义
            ch = m_str[m_idx++];
            switch(ch)
            {
                case '\n':
                    res += '\n';
                    break;
                case '\r':
                    res += '\r';
                    break;
                case '\t':
                    res += '\t';
                    break;
                case '\b':
                    res += '\b';
                    break;
                case '\f':
                    res += '\f';
                    break;
                case '"':
                    res += "\\\"";
                    break;
                case '\\':
                    res += "\\\\";
                    break;
                case 'u':
                    res += "\\u";
                    for(int i = 0; i < 4; i++) { // 跟4个字节
                        res += m_str[m_idx++];
                    }
                    break;
                default:
                    break;
            }
        } 
        else { // 非转义
            res += ch;
        }
    }
    return res;
}

Json Parser::parse_array()
{
    return Json();
}

Json Parser::parse_object()
{
    return Json();
}