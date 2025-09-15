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
		$(AA2_sources_path)/AA2_Player.cpp \
		$(AA2_sources_path)/AA2_Camera.cpp \
		$(AA2_sources_path)/AA2_Level.cpp \
		$(AA2_sources_path)/AA2_Entity.cpp \
		$(AA2_sources_path)/AA2_DrawableEntity.cpp \
		$(AA2_sources_path)/AA2_Creature.cpp \
		$(AA2_sources_path)/AA2_LevelManager.cpp \
		$(AA2_sources_path)/AA2_Prop.cpp \
		$(AA2_sources_path)/AA2_PropManager.cpp \
		$(AA2_sources_path)/AA2_World.cpp \
		$(AA2_sources_path)/AA2_PlayState.cpp \
		$(AA2_sources_path)/AA2_MenuState.cpp 

HEADERS=$(AA2_headers_path)/AA2_Config.h \
		$(AA2_headers_path)/AA2_Game.h \
		$(AA2_headers_path)/AA2_RefLinks.h \
		$(AA2_headers_path)/AA2_TextureLoader.h \
		$(AA2_headers_path)/AA2_Map.h \
		$(AA2_headers_path)/AA2_Tile.h \
		$(AA2_headers_path)/AA2_TileManager.h \
		$(AA2_headers_path)/AA2_Player.h \
		$(AA2_headers_path)/AA2_Camera.h \
		$(AA2_headers_path)/AA2_Level.h \
		$(AA2_headers_path)/AA2_Entity.h \
		$(AA2_headers_path)/AA2_DrawableEntity.h \
		$(AA2_headers_path)/AA2_Creature.h \
		$(AA2_headers_path)/AA2_LevelManager.h \
		$(AA2_headers_path)/AA2_Prop.h \
		$(AA2_headers_path)/AA2_PropManager.h \
		$(AA2_headers_path)/AA2_World.h \
		$(AA2_headers_path)/AA2_State.h \
		$(AA2_headers_path)/AA2_PlayState.h \
		$(AA2_headers_path)/AA2_MenuState.h

$(exe): $(SOURCES) $(HEADERS)
	g++ -Wall $(SOURCES) -o $(exe) -I$(AA2_headers_path) -I$(SDL_headers_path) -L$(SDL_libraries_path) -lSDL3 -lSDL3_image

.PHONY:
clean:
	rm -f $(exe)