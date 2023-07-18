# 指定编译器
CC = g++ 

# 编译选项，指定头文件目录及使用c++11标准
CFLAGS = -I include -std=c++11 
# 搜索所有的源文件
CFILES = $(shell find ./ -name "*.cpp") 
OBJS = $(CFILES:.cpp=.o) # 所有的目标文件
TARGET = main # 最终生成目标

# 编译并生成目标文件
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 清理生成的文件
.PHONY: clean # 伪目标
clean:
	rm -f $(OBJS) $(TARGET)