# 自定义环境变量
CC = g++ # 指定编译器

CFLAGS = -I include -std=c++11 -Wall # 指定头文件目录及启用警告
CFILES = $(shell find src -name "*.cpp") # 搜索所有的源文件
OBJS = $(CFILES:.cpp=.o) # 所有的目标文件
TARGET = main # 最终生成目标

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 清理生成的文件
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# 清理生成的文件
.PHONY: clean # 伪目标
clean:
	rm -f $(OBJS) $(TARGET)