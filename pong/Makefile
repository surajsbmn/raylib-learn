CXXFLAGS = -std=c++23 -Wall -Wextra -MMD -MP

SRC_DIR   = src
BUILD_DIR = build

# Detect platform
ifeq ($(OS),Windows_NT)
    PLATFORM = windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM = macos
    else
        PLATFORM = linux
    endif
endif

ifeq ($(PLATFORM),windows)
    CXX     = g++
    TARGET  = $(BUILD_DIR)/main.exe
    LDFLAGS = -static -mwindows
    LDLIBS  = -lraylib -lopengl32 -lgdi32 -lwinmm
else
    TARGET = $(BUILD_DIR)/main
    # Prefer pkg-config when raylib provides a .pc file
    HAS_PKGCONFIG := $(shell pkg-config --exists raylib 2>/dev/null && echo yes)
    ifeq ($(HAS_PKGCONFIG),yes)
        CXXFLAGS += $(shell pkg-config --cflags raylib)
        LDLIBS   += $(shell pkg-config --libs raylib)
    else
        LDLIBS   += -lraylib
    endif

    ifeq ($(PLATFORM),macos)
        CXX = clang++
        # Homebrew prefix (Apple Silicon: /opt/homebrew, Intel: /usr/local)
        BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
        ifneq ($(BREW_PREFIX),)
            CXXFLAGS += -I$(BREW_PREFIX)/include
            LDFLAGS  += -L$(BREW_PREFIX)/lib
        endif
        LDLIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    else
        CXX = g++
        LDLIBS += -lGL -lm -lpthread -ldl -lrt -lX11
    endif
endif

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
