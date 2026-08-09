CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fPIC
LIBS_DIR = libs
LIB_SRCS = $(wildcard $(LIBS_DIR)/*.c)
LIB_SOS = $(LIB_SRCS:.c=.so)

TARGET = calc
TEST_TARGET = test_calc

all: $(TARGET)

$(LIB_SOS): %.so: %.c
	$(CC) $(CFLAGS) -shared -o $@ $< -lm

$(TARGET): main.c $(LIB_SOS)
	$(CC) $(CFLAGS) -o $@ $< -ldl

test: $(TEST_TARGET) $(LIB_SOS)
	./$(TEST_TARGET)

$(TEST_TARGET): test.c $(LIB_SOS)
	$(CC) $(CFLAGS) -o $@ $< -ldl

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(LIBS_DIR)/*.so

.PHONY: all test clean
