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

使用C++编写实现了一个 **独立、跨平台、简单易用且高性能** 的 `Json` 文件解析器。

其中核心解析部分代码仅 **200** 多行，解析性能比常见的 `jsoncpp`, `blohmann` 等要高很多。

----

#### 02.涉及的主要技术点

面向对象设计，函数重载，运算符重载，使用标准模板库(STL):vector、map、ifstream、stringstream;

内存管理，enum、union的巧用，动态库的制作。

----

#### 03.开发环境及工具

Linux: `Ubuntu 18.04.6 LTS`

IDE: `VSCode 1.8.02`

----

### 二、跨平台使用

#### 多平台解析测试
xxx

ps: 后续有时间，可以新增网页版的在线解析工具

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





