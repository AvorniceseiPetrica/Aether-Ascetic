SDL_HEADERS_PATH=SDL/include
SDL_LIBRARIES_PATH=SDL/lib

BUILD_DIR := ./build
SOURCES_DIR := ./AA/src
HEADERS_DIR := ./AA/include

HEADERS := $(wildcard $(HEADERS_DIR)/*.h)
SOURCES := $(wildcard $(SOURCES_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCES_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

EXE=aa


exe: $(OBJECTS)
	@echo "Building @(exe)..."
	g++ -std=c++20 -Wall $(OBJECTS) -o $(exe) -I$(HEADERS_DIR) -I$(SDL_HEADERS_PATH) -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%.cpp $(HEADERS) | $(BUILD_DIR)
	@echo "Building $@..." 
	g++ -std=c++20 -Wall -c $< -o $@ -I$(HEADERS_DIR) -I$(SDL_HEADERS_PATH) -L$(SDL_LIBRARIES_PATH) -lSDL3 -lSDL3_image -Wl,-rpath,SDL/lib


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