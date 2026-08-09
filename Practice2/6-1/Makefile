CC = gcc
CFLAGS = -Wall -Wextra -std=c99
AR = ar

LIB = libcontact.a
LIB_OBJ = contact.o

TARGET = phonebook
TEST_TARGET = test_phonebook

all: $(TARGET)

$(LIB): $(LIB_OBJ)
	$(AR) rcs $@ $^

$(LIB_OBJ): contact.c contact.h
	$(CC) $(CFLAGS) -c contact.c

$(TARGET): main.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lcontact

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lcontact

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(LIB) $(LIB_OBJ)

.PHONY: all test clean