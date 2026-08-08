CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = perms.c main.c
TEST_SRC = perms.c test.c
TARGET = perms
TEST_TARGET = test_perms

all: $(TARGET)

$(TARGET): $(SRC) perms.h
	$(CC) $(CFLAGS) -o $@ $(SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) perms.h
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
