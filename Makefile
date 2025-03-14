# Compiler
CXX := g++
CXXFLAGS := -Wall -Iinclude -I"C:\msys64\mingw64\include\SDL2"

# Linker
LDFLAGS := -L"C:\msys64\mingw64\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SRCS := Main.cpp $(wildcard $(SRC_DIR)/*.cpp) Utilities.cpp

# Targets
TARGET_DEBUG := $(BIN_DIR)/Debug/Extinction.exe
TARGET_RELEASE := $(BIN_DIR)/Release/Extinction.exe

# Source files
SRCS := Main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS_DEBUG := $(patsubst %.cpp, $(OBJ_DIR)/Debug/%.o, $(SRCS))
OBJS_RELEASE := $(patsubst %.cpp, $(OBJ_DIR)/Release/%.o, $(SRCS))

# Default target
all: debug

# Debug Build
debug: CXXFLAGS += -g
debug: $(TARGET_DEBUG)

$(TARGET_DEBUG): $(OBJS_DEBUG)

	@echo "Linking Debug Build..."
	@if not exist "$(BIN_DIR)/Debug" mkdir "$(BIN_DIR)/Debug"
	@echo "Linking files into $(TARGET_DEBUG)..."
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Debug Build completed: $(TARGET_DEBUG)"

$(OBJ_DIR)/Debug/%.o: %.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling $< (CPP file)..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< successfully"

# Release Build
release: CXXFLAGS += -O2
release: LDFLAGS += -s
release: $(TARGET_RELEASE)

$(TARGET_RELEASE): $(OBJS_RELEASE)
	@echo "Linking Release Build..."
	@if not exist "$(BIN_DIR)/Release" mkdir "$(BIN_DIR)/Release"
	@echo "Linking files into $(TARGET_RELEASE)..."
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Release Build completed: $(TARGET_RELEASE)"

$(OBJ_DIR)/Release/%.o: %.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling $< (CPP file)..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< successfully"

# Clean
clean:
	@echo "Cleaning up..."
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@echo "Removed $(OBJ_DIR)"
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
	@echo "Removed $(BIN_DIR)"

.PHONY: all debug release clean