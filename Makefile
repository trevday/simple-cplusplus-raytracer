TARGET := raytracer
SRCS := ./src/*.cpp
INCLUDES := ./include/*.hpp ./include/*.h

$(TARGET): $(SRCS) $(INCLUDES)
	clang++ -Wall -std=c++14 $(SRCS) -I./include -o3 -o $(TARGET)
