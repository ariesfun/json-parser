// 静态库使用测试
// g++ libs_test.cpp -o lib_static -I./static -L./static -lmyjson
#include "./static/json.h"
using namespace swift::json;

#include <iostream>
int main()
{
    // 序列化，构造一个json数据
    Json arr;
    arr[0] = false;
    arr[1] = 100;
    arr[2] = "hhhhh";
    Json obj;
    obj["bool"] = true;
    obj["int"] = 777;
    obj["double"] = 999.9;
    obj["array"] = arr;
    std::cout << obj.str() << std::endl;

    // 反序列化，解析json数据
    std::string str = "{\"result\":\"1\",\"msg\":\"认证成功\"}";
    Json res;
    res.parse(str);
    std::cout << res.str() << std::endl;

//    OutPut:
//    {"array":[false,100,"hhhhh"],"bool":true,"double":999.9,"int":777}
//    {"msg":"认证成功","result":"1"}

    return 0;
}


/*
// 动态库使用测试
// g++ libs_test.cpp -o lib_dynamic -I./dynamic -L./dynamic -lmyjson
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ariesfun/xxx/json-parser/tools_libs/dynamic
#include "./dynamic/json.h"
using namespace swift::json;

#include <iostream>
int main()
{
    std::string str = "{\"result\":\"0\",\"msg\":\"注销成功\"}";
    Json res;
    res.parse(str);
    std::cout << res.str() << std::endl;

    // Output:
    // {"msg":"注销成功","result":"0"}

    return 0;
}
*/
