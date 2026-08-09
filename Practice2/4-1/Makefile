CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = contact.c main.c
TEST_SRC = contact.c test.c
TARGET = phonebook
TEST_TARGET = test_phonebook

all: $(TARGET)

$(TARGET): $(SRC) contact.h
	$(CC) $(CFLAGS) -o $@ $(SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) contact.h
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
