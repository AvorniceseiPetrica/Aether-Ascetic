SDL_HEADERS_PATH=SDL/include
SDL_LIBRARIES_PATH=SDL/lib

BUILD_DIR := ./build
SOURCES_DIR := ./AA/src
HEADERS_DIR := ./AA/include

HEADERS := $(wildcard $(HEADERS_DIR)/*.h)
SOURCES := $(wildcard $(SOURCES_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

DEBUG_FLAGS = -g -fsanitize=address -fno-omit-frame-pointer

EXE = aa

$(EXE): $(OBJECTS)
	@echo "Building ./$(EXE)..."
	@g++ -std=c++20 -Wall $(OBJECTS) -o $@ -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib

debug: $(OBJECTS)
	@echo "Building ./$(EXE) with debug..."
	@g++ -std=c++20 -Wall $(DEBUG_FLAGS) $(OBJECTS) -o $(EXE) -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib

$(BUILD_DIR):
	@echo "Building ./build"
	@mkdir $@

$(BUILD_DIR)/main.o : $(SOURCES_DIR)/main.cpp
	@echo "Building $@..." 
	@g++ -std=c++20 -Wall -c $< -o $@ -I$(HEADERS_DIR) -I$(SDL_HEADERS_PATH) -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp $(HEADERS_DIR)/%.h | $(BUILD_DIR)
	@echo "Building $@..." 
	@g++ -std=c++20 -Wall -c $< -o $@ -I$(HEADERS_DIR) -I$(SDL_HEADERS_PATH) -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib


info:
	@echo $(HEADERS)
	@echo ""
	@echo $(SOURCES)
	@echo ""
	@echo $(OBJECTS)
	@echo ""
	@echo $(DEPENDENCIES)

.PHONY:

clean:
	rm -rf $(BUILD_DIR) $(EXE)