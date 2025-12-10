# Directories
SRC_DIR := .
OBJ_DIR := .

# Source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Compiler flags
CXX := g++
CXXFLAGS := -g -Wall -std=c++17 -fpermissive

# SFML libraries
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Output executable
TARGET := particles.out

# Build executable
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) *.o