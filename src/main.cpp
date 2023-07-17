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

    // test02-1
    // 设计一个数组索引方式的API，两种方式增加值 
    // Json arr;
    // arr[0] = true; // 需要重载中括号
    // arr[1] = 123;
    // arr.append(1.23);
    // arr.append("hello world");
    // std::cout << arr.str() << std::endl; // 输出数组内容
    // // 支持动态类型转换
    // bool b = arr[0];
    // int i = arr[1];
    // double f = arr[2];
    // const std::string &s = arr[3];
    
    // test02-2
    // 用迭代器实现对数组内容的遍历
    // Json arr1;
    // arr1[0] = false;
    // arr1[1] = 333;
    // arr1[2] = 444.5;
    // arr1[3] = "hhhhhhhhh"; // arr1[4],arr1[5]会变为空
    // arr1[6] = "222233333";
    // for(auto it = arr1.begin(); it != arr1.end(); it++) { // 遍历每个数组元素
    //         std::cout << (*it).str() << std::endl;
    // }

    // test03
    // 设计对象类型的api
    // Json obj;
    // obj["bool"] = true;
    // obj["int"] = 123;
    // obj["double"] = 1.23;
    // obj["str"] = "hello world"; 
    // std::cout << obj.str() << std::endl;

    // test04-1
    // Json arr2;
    // arr2[0] = true;
    // arr2[1] = 1111;
    // arr2[2] = 2222.2;
    // arr2[3] = "hello world";
    //  std::cout << arr2.str() << std::endl;
    // arr2.remove(0);
    // arr2.remove(6);
    // std::cout << arr2.str() << std::endl;

    // test04-2
    // Json obj1;
    // obj1["bool"] = false;
    // obj1["int"] = 789;
    // obj1["double"] = 8888.8;
    // obj1["str"] = "hello world";
    // std::cout << obj1.has("str") << ' ' << obj1.has("hhh") << std::endl; 
    // obj1.remove("int");
    // obj1.remove("string");
    // std::cout << obj1.str() << std::endl;

    //test05 内存清理
    // Json arr;
    // arr[0] = false;
    // arr[1] = 100;
    // arr[2] = "hhhhh";
    // Json obj;
    // obj["bool"] = true;
    // obj["int"] = 777;
    // obj["double"] = 999.9;
    // obj["array"] = arr;
    // std::cout << obj.str() << std::endl;

    // // arr.clear(); 有error，会重复释放
    // // arr是作为obj的一个成员变量存，当调用obj.clear()时，会自动触发arr的析构函数来释放其占用的内存
    // obj.clear(); // 只用释放这一个即可

    

    std::cout << "Debug Test" << std::endl;
    return 0;
}