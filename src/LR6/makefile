# Makefile с режимами сборки
CXX = g++
TARGET = program
SOURCES = main.cpp StringClass.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Режимы сборки
DEBUG_FLAGS = -Wall -std=c++11 -g -DDEBUG
RELEASE_FLAGS = -Wall -std=c++11 -O2 -DNDEBUG

# По умолчанию сборка в режиме debug
CXXFLAGS = $(DEBUG_FLAGS)

# Режим debug
debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: $(TARGET)

# Режим release
release: CXXFLAGS = $(RELEASE_FLAGS)
release: $(TARGET)

# Сборка программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция объектных файлов
%.o: %.cpp StringClass.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

# Информация о файлах
info:
	@echo "Target: $(TARGET)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"

.PHONY: debug release clean run info