CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = lab3

SRCS = \
	main.c \
	reader.c \
	scanner.c \
	parser.c \
	token.c \
	charcode.c \
	error.c \
	symtab.c \
	semantics.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
