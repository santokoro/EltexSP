CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fPIC
LDFLAGS = -Wl,-rpath,'$$ORIGIN'

LIB = libcontact.so
LIB_OBJ = contact.o

TARGET = phonebook
TEST_TARGET = test_phonebook

all: $(TARGET)

$(LIB): $(LIB_OBJ)
	$(CC) -shared -o $@ $^

$(LIB_OBJ): contact.c contact.h
	$(CC) $(CFLAGS) -c contact.c

$(TARGET): main.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lcontact $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lcontact $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(LIB) $(LIB_OBJ)

.PHONY: all test clean
