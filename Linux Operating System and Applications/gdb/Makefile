CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = bubble_sort

# 这里必须确保 main.c 和 bubble.c 在当前目录下存在
SRCS = main.c bubble.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 模式规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): bubble.h

.PHONY: clean
clean:
	rm -f $(TARGET) *.o
