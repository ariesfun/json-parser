#include <iostream>
#include "json.h"

using namespace yazi::json;

int main() {

    // 通过基本数据类型来构造一个json
    Json v1; // 空值
    Json v2 = true;
    Json v3 = 123;
    Json v4 = 1.23;
    Json v5 = "hello world\n";



    return 0;
}