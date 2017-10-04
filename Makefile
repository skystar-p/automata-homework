OBJECTS = main.cpp parse.cpp state.cpp nfa.cpp
TARGET = hw1

all: build

build:
	g++ --std=c++11 $(OBJECTS) -o $(TARGET)

run:
	./hw1

clean:
	rm -f hw1 *.out
