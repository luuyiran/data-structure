TARGET:=test
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)

CFLAG=-std=c++17 -W -Wall -g -fstack-protector-all -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

all:$(TARGET)
$(TARGET):$(OBJ)
	$(CXX) -o $@ $^ $(CFLAG)

%.o:%.cpp
	$(CXX) -c -o $@ $< $(CFLAG)

.PHONY:clean
clean:
	@rm -rvf $(TARGET) $(OBJ)