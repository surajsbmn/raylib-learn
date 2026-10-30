CXX      = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -MMD -MP
LDFLAGS  = -static -mwindows
LDLIBS   = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR   = src
BUILD_DIR = build
TARGET    = $(BUILD_DIR)/main.exe

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

-include $(OBJ:.o=.d)

.PHONY: all run clean
