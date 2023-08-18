## C++ JSON文件解析器

## 目录

一、项目简介

二、跨平台使用

三、动态库使用

四、解析性能测试

五、项目开发参考资料

----

### 一、项目简介

#### 01.介绍

使用C++11编写实现了一个 **独立、跨平台、简单易用且高性能** 的 `Json` 文件解析器。

其中核心解析部分代码仅 **200** 多行，解析性能比常见的 `jsoncpp`, `blohmann` 等要高很多。

----

#### 02.涉及的主要技术点

面向对象设计，函数重载，运算符重载，标准模板库(STL)使用:vector、map、ifstream、stringstream;

内存管理，enum、union的巧用，以及动态库的制作。

----

#### 03.开发环境及工具

Linux: `Ubuntu 18.04.6 LTS`

IDE: `VSCode 1.8.02`

----

### 二、跨平台使用

#### 解析测试

单个json文件解析测试，并截取其中部分内容输出
测试的json数据，放在`json_data`目录下：
尝试解析`json_test.json`文件，输出结果如下：

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

ps: 后续有时间，可以完善为网页版的在线解析工具

----

### 三、动态库使用
xxx

----

### 四、解析性能测试


- 测试原理

    使用同一个 `json` 文件，对多个平台的解析工具在本地环境进行循环解析10万次，计算每次解析的平均耗时。最后对比各自的解析时间来分析其性能。

- 测试对象

    [`nlohmann`](), [`jsoncpp`](), [`rapidjson`](), [`json-parser`]()

- 测试环境

    硬件环境: 笔电 `Win11 x64`; CPU `AMD Ryzen 7 6800H`; 内存 `32G`

    编译环境: `VSCode 1.8.02` , `MinGW-W64 GCC-8.1.0` 

- 测试环节代码，`test.cpp`

    ```c++
    // 测试部分的核心代码

    ```
- 测试结果

    这里放解析时间对比的表格

- 解析性能分析

    xxx

---

### 五、项目开发参考资料

[【视频 C++ JSON解析器】](https://www.bilibili.com/video/BV1TP411p7cC/?share_source=copy_web&vd_source=64863a79f6edd334371cb7b41a0df347)

[【文档 Introducing JSON】](https://www.json.org/json-en.html)

[【文档 C++ 编写简易JSON解析器】](https://zhuanlan.zhihu.com/p/476271291)


----





