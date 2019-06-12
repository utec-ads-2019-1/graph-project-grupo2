CC = g++

.PHONY: all clean

sources = $(wildcard *.cpp)
headers = $(wildcard *.h)
obj = $(sources:%.cpp=%.o)

FLAGS = -lGL -lGLU -lglut
default: main

%.o: %.cpp
	$(CC) -c $< -o $@

main: $(obj)
	$(CC) $(FLAGS) $(obj) -o $@

clean:
	rm -rf *.o main