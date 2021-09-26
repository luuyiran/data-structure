TARGET:=test
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

CFLAG=-W -Wall -std=c89 -W -Wall -g -fstack-protector-all -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

all:$(TARGET)
$(TARGET):$(OBJ)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c -o $@ $< $(CFLAG)

.PHONY:clean
clean:
	@rm -rvf $(TARGET) $(OBJ)