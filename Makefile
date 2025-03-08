SRC_DIR = src
BUILD_DIR = build
OUTPUT = phymovx
CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(OUTPUT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(OUTPUT): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(BUILD_DIR)/$(OUTPUT)

clean:
	@rm -rf $(BUILD_DIR)
