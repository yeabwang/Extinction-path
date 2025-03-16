# Compiler
CXX := g++
CXXFLAGS := -Wall -Iinclude -I"C:\msys64\mingw64\include\SDL2"

# Linker
LDFLAGS := -L"C:\msys64\mingw64\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source files (added Bomb.cpp)
SRCS := Main.cpp \
        $(SRC_DIR)/Game.cpp \
        $(SRC_DIR)/base.cpp \
        $(SRC_DIR)/terrain.cpp \
        $(SRC_DIR)/Dragon.cpp \
        $(SRC_DIR)/Hero.cpp \
        $(SRC_DIR)/Bullet.cpp \
        $(SRC_DIR)/Enemy.cpp \
        $(SRC_DIR)/Tank.cpp \
        $(SRC_DIR)/Helicopter.cpp \
        $(SRC_DIR)/Boss.cpp \
        $(SRC_DIR)/GameScreen.cpp \
        $(SRC_DIR)/SplashScreen.cpp \
        $(SRC_DIR)/Menu.cpp \
        $(SRC_DIR)/PauseScreen.cpp \
        $(SRC_DIR)/WinScreen.cpp \
        $(SRC_DIR)/Missions.cpp \
        $(SRC_DIR)/Sprites.cpp \
        $(SRC_DIR)/Button.cpp \
        $(SRC_DIR)/GameObjects.cpp \
        $(SRC_DIR)/Obstacles.cpp \
        $(SRC_DIR)/SoundEffects.cpp \
        $(SRC_DIR)/Music.cpp \
        $(SRC_DIR)/Health.cpp \
        $(SRC_DIR)/LoadAndSave.cpp \
        $(SRC_DIR)/Point.cpp \
        $(SRC_DIR)/Bomb.cpp

# Object files (adjusted for subdirectory structure)
OBJS_DEBUG := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Debug/%.o, $(filter $(SRC_DIR)/%, $(SRCS))) $(patsubst %.cpp, $(OBJ_DIR)/Debug/%.o, $(filter-out $(SRC_DIR)/%, $(SRCS)))
OBJS_RELEASE := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Release/%.o, $(filter $(SRC_DIR)/%, $(SRCS))) $(patsubst %.cpp, $(OBJ_DIR)/Release/%.o, $(filter-out $(SRC_DIR)/%, $(SRCS)))

# Targets
TARGET_DEBUG := $(BIN_DIR)/Debug/Extinction.exe
TARGET_RELEASE := $(BIN_DIR)/Release/Extinction.exe

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

$(OBJ_DIR)/Debug/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling $< (CPP file)..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< successfully"

# Special rule for Main.cpp (in root directory)
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

$(OBJ_DIR)/Release/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling $< (CPP file)..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< successfully"

# Special rule for Main.cpp (in root directory)
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

# Dependency generation (optional, requires gcc -M)
depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -M $^ > dependecy.d

-include dependecy.d

.PHONY: all debug release clean depend