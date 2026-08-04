CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = main
TEST_TARGET = test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): priority_queue.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) priority_queue.o main.o

$(TEST_TARGET): priority_queue.o test.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) priority_queue.o test.o

priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) -c priority_queue.c

main.o: main.c priority_queue.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c priority_queue.h
	$(CC) $(CFLAGS) -c test.c

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

rebuild: clean all

.PHONY: all clean rebuild test run
