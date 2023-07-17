#include <iostream>
#include "json.h"

using namespace yazi::json;

int main() {

    // test01
    // 通过基本数据类型来构造一个json
    // Json v1; // 空值
    // Json v2 = true;
    // Json v3 = 123;
    // Json v4 = 1.23;
    // Json v5 = "hello world\n";
    // // 基本类型转换
    // bool b = v2; // Json数据类型转成基本类型（类似动态类型的语言），需要对基本类型的运算符重载
    // int i = v3;
    // double f = v4;
    // const std::string &s = v5;

    // test02
    // 设计一个数组索引方式的API，两种方式增加值 
    // Json arr;
    // arr[0] = true; // 需要重载中括号
    // arr[1] = 123;
    // arr.append(1.23);
    // arr.append("hello world");
    // // 支持动态类型转换
    // bool b = arr[0];
    // int i = arr[1];
    // double f = arr[2];
    // const std::string &s = arr[3];
    // std::cout << arr.str() << std::endl; // 输出数组内容

    // test03
    // 设计对象类型的api
    Json obj;
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["str"] = "hello world"; 
    std::cout << obj.str() << std::endl;

    std::cout << "Debug Test" << std::endl;
    return 0;
}