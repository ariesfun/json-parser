## C++ JSON 解析器

## 目录

一、项目简介

二、跨平台使用

三、动静态库使用

四、解析性能测试

五、参考资料

----

### 一、项目简介

#### 01. 介绍

使用 `C++11` 编写实现了一个 **独立、跨平台、简单易用且高性能** 的 `Json` 文件格式解析器;

该解析器提供了友好的API，支持序列化和反序列化操作，其中解析核心部分的实现 `parser.cpp` 代码仅有 **200 来行**;

而且解析性能比常见的 `jsoncpp`, `blohmann` 等有所提升。

----

#### 02. 涉及的主要技术点

面向对象设计，函数重载，运算符重载，STL的使用: `vector、map、ifstream、stringstream` 等;

以及内存管理，移动语义，`enum`、`union`的巧用，以及动态库的制作等。

----

#### 03. 开发环境及工具

Linux: `Ubuntu 18.04.6 LTS`

IDE: `VSCode 1.8.02`

GCC: `9.4.0`, GNU Make `4.2.1`, CMake `3.27.0-rc3`

----

### 二、跨平台使用
代码可在 `Linux`，`Windows`，`MacOS` 上运行。

项目目录树如下，
```shell
.
├── CMakeLists.txt
├── include
│   ├── json.h
│   └── parser.h
├── json_data
│   ├── json_test1.json
│   └── json_test.json
├── main.cpp
├── Makefile
├── README.md
├── src
│   ├── json.cpp
│   └── parser.cpp
└── tools_libs
    ├── dynamic
    │   ├── json.h
    │   └── libmyjson.so
    ├── lib_dynamic
    ├── lib_static
    ├── libs_test.cpp
    └── static
        ├── json.h
        └── libmyjson.a

6 directories, 17 files
```

#### 解析测试

单个json文件解析测试，并截取其中部分内容输出
测试的json数据，放在 `json_data` 目录下：
尝试解析 `json_test.json` 文件，输出结果如下：

**使用CMake编译项目:**
```shell
# Linux环境 (使用CMake+make)
mkdir build && cd build
cmake ..
make
./main
```
**解析结果:**
```shell
{"code":0,"data":{"allowance_count":0,"answer_status":0,"email_verified":1,"face":"https://i0.hdslb.com/bfs/face/6a307aa7456c641a9610376509d61a7acc529ba3.jpg","face_nft":0,"face_nft_type":0,"has_shop":false,"isLogin":true,"is_jury":false,"is_senior_member":0,"level_info":{"current_exp":22991,"current_level":5,"current_min":10800,"next_exp":28800},"mid":172382106,"mobile_verified":1,"money":997.7,"moral":70,"official":{"desc":"","role":0,"title":"","type":-1},"officialVerify":{"desc":"","type":-1},"pendant":{"expire":0,"image":"","image_enhance":"","image_enhance_frame":"","name":"","pid":0},"scores":0,"shop_url":"","uname":"Ariesfun","vip":{"avatar_subscript":0,"avatar_subscript_url":"","due_date":0,"label":{"bg_color":"","bg_style":0,"border_color":"","img_label_uri_hans":"","img_label_uri_hans_static":"https://i0.hdslb.com/bfs/vip/d7b702ef65a976b20ed854cbd04cb9e27341bb79.png","img_label_uri_hant":"","img_label_uri_hant_static":"https://i0.hdslb.com/bfs/activity-plat/static/20220614/e369244d0b14644f5e1a06431e22a4d5/KJunwh19T5.png","label_theme":"","path":"","text":"","text_color":"","use_img_label":true},"nickname_color":"","role":0,"status":0,"theme_type":0,"tv_due_date":0,"tv_vip_pay_type":0,"tv_vip_status":0,"type":0,"vip_pay_type":0},"vipDueDate":0,"vipStatus":0,"vipType":0,"vip_avatar_subscript":0,"vip_label":{"bg_color":"","bg_style":0,"border_color":"","img_label_uri_hans":"","img_label_uri_hans_static":"https://i0.hdslb.com/bfs/vip/d7b702ef65a976b20ed854cbd04cb9e27341bb79.png","img_label_uri_hant":"","img_label_uri_hant_static":"https://i0.hdslb.com/bfs/activity-plat/static/20220614/e369244d0b14644f5e1a06431e22a4d5/KJunwh19T5.png","label_theme":"","path":"","text":"","text_color":"","use_img_label":true},"vip_nickname_color":"","vip_pay_type":0,"vip_theme_type":0,"wallet":{"bcoin_balance":0,"coupon_balance":0,"coupon_due_time":0,"mid":172382106},"wbi_img":{"img_url":"https://i0.hdslb.com/bfs/wbi/bae9005f8bf44fb881d391b8367ea573.png","sub_url":"https://i0.hdslb.com/bfs/wbi/18c8b349a6ae441fa3b50ecf161d5c0b.png"}},"message":"0","ttl":1}

Your bilibili username: Ariesfun
Current level: 5
```


----

### 三、动静态库使用

静态库和动态库的打包文件放在了 `tools_lib` 文件夹中，并分别使用两种库做了使用测试；

将代码打包成库文件形式，让代码有更好的封装性和安全性，你可以很方便的将该JSON解析器集成到其他项目中。

----

### 四、解析性能测试


- 测试原理

    使用同一个 `json` 文件，对多个平台的解析工具在本地环境进行循环解析10万次，计算每次解析的平均耗时。最后对比各自的解析时间来分析其性能。

- 测试对象

    [`json-parser`]()，[`nlohmann`](), [`jsoncpp`](), [`rapidjson`](), 

- 测试环境

    硬件环境: 笔电 `Win11 x64`; CPU `AMD Ryzen 7 6800H`; 内存 `32G`

    编译环境: `Ubuntu 18.04 LTS` , `VSCode 1.8.02` , `GCC 9.4.0` 

- 测试环节代码，`test.cpp`

    ```c++
    // 测试部分的核心代码
        try {
        std::ifstream fin("../json_data/json_test.json");
        if (!fin.is_open()) {
            throw std::runtime_error("Failed to open the file.");
        }
        std::stringstream ss;
        ss << fin.rdbuf();
        const std::string& data = ss.str();

        struct timeval tv;
        gettimeofday(&tv, NULL);
        int start_sec = tv.tv_sec;
        int start_usec = tv.tv_usec;
        const int max = 100000;
        for(int i = 0; i < max; i++) { // 循环解析10w次，计算平均值
            Json json;
            json.parse(data);
        }
        gettimeofday(&tv, NULL);
        int end_sec = tv.tv_sec;
        int end_usec = tv.tv_usec;
        double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
        std::cout << time_diff / 1000 / max << "ms" << std::endl;
        
        }catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    ```
- 测试结果

    常见JSON解析库耗时比较, 测试跑在linux虚拟机环境上，与实际可能略有差异，仅供参考

    | 项目        | 解析平均耗时（ms） |
    | ----------- | ------------------ |
    | nlohmann    | 0.2361              |
    | jsoncpp     | 0.1572              |
    | rapidjson   | 0.0562              |
    | json-parser | 0.1409              |

- 解析性能分析

    相比于普通的拷贝构造函数和深拷贝（Json::copy）方法，移动构造函数和移动语义的优势在于性能和资源管理上：

    **性能**: 移动构造函数通常比拷贝构造函数更快，因为它只是简单地将资源的所有权从一个对象转移到另一个对象，而不需要进行深拷贝或复制大量数据。

    **资源管理**: 移动构造函数允许在资源管理上更高效地操作，特别是对于动态分配的内存或其他资源。它避免了不必要的数据复制，减少了内存分配和释放的开销。

    总的来说，移动构造函数和移动语义适用于那些可以转移资源所有权而不需要复制的情况，可以提高代码的性能和资源管理效率。
    
    这对于处理大型数据结构或使用动态内存分配的情况尤其有用。而普通的拷贝构造函数和深拷贝适用于需要创建对象的独立副本的情况。

---

### 五、参考资料

[【视频 C++ JSON解析器】](https://www.bilibili.com/video/BV1TP411p7cC/?share_source=copy_web&vd_source=64863a79f6edd334371cb7b41a0df347)

[【文档 Introducing JSON】](https://www.json.org/json-en.html)

[【文档 C++ 编写简易JSON解析器】](https://zhuanlan.zhihu.com/p/476271291)

----