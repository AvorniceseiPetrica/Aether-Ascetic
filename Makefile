AA2_headers_path=AA2/include
AA2_sources_path=AA2/src
SDL_headers_path=SDL/include
SDL_libraries_path=SDL/lib

exe=aa2
SOURCES=$(AA2_sources_path)/main.cpp \
		$(AA2_sources_path)/AA2_Game.cpp \
		$(AA2_sources_path)/AA2_RefLinks.cpp \
		$(AA2_sources_path)/AA2_TextureLoader.cpp \
		$(AA2_sources_path)/AA2_Map.cpp \
		$(AA2_sources_path)/AA2_Tile.cpp \
		$(AA2_sources_path)/AA2_TileManager.cpp \
		$(AA2_sources_path)/AA2_Player.cpp

$(exe): $(SOURCES)
	g++ -Wall $(SOURCES) -o $(exe) -I$(AA2_headers_path) -I$(SDL_headers_path) -L$(SDL_libraries_path) -lSDL3 -lSDL3_image

.PHONY:
clean:
	rm -f $(exe)