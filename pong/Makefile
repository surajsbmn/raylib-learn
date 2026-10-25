CXX      = g++
CXXFLAGS = -std=c++23 -Wall -Wextra
LDLIBS   = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = main.exe
SRC    = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
