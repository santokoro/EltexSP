CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = network.c main.c
TEST_SRC = network.c test.c
TARGET = network_sim
TEST_TARGET = test_network

all: $(TARGET)

$(TARGET): $(SRC) network.h
	$(CC) $(CFLAGS) -o $@ $(SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) network.h
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
