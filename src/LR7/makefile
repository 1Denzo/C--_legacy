CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = shapes
SOURCES = main.cpp Shapes.cpp
HEADERS = Shapes.h
OBJECTS = $(SOURCES:.cpp=.o)

# Определение ОС
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	# Linux
	LIBS = 
endif
ifeq ($(UNAME_S),Darwin)
	# MacOS
	LIBS = 
endif
ifdef OS
	# Windows
	LIBS = -lwinmm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
ifeq ($(OS),Windows_NT)
	del $(OBJECTS) $(TARGET) 2>nul || true
endif

run: $(TARGET)
	./$(TARGET)

install:
	sudo cp $(TARGET) /usr/local/bin/

.PHONY: all clean run install