AA_headers_path=AA/include
AA_sources_path=AA/src
SDL_headers_path=SDL/include
SDL_libraries_path=SDL/lib

exe=aa
SOURCES=$(AA_sources_path)/main.cpp \
		$(AA_sources_path)/AA_Game.cpp \
		$(AA_sources_path)/AA_RefLinks.cpp \
		$(AA_sources_path)/AA_TextureLoader.cpp \
		$(AA_sources_path)/AA_Map.cpp \
		$(AA_sources_path)/AA_Tile.cpp \
		$(AA_sources_path)/AA_TileManager.cpp \
		$(AA_sources_path)/AA_Player.cpp \
		$(AA_sources_path)/AA_Camera.cpp \
		$(AA_sources_path)/AA_Level.cpp \
		$(AA_sources_path)/AA_Entity.cpp \
		$(AA_sources_path)/AA_DrawableEntity.cpp \
		$(AA_sources_path)/AA_Creature.cpp \
		$(AA_sources_path)/AA_LevelManager.cpp \
		$(AA_sources_path)/AA_Prop.cpp \
		$(AA_sources_path)/AA_PropManager.cpp \
		$(AA_sources_path)/AA_World.cpp \
		$(AA_sources_path)/AA_PlayState.cpp \
		$(AA_sources_path)/AA_MenuState.cpp \
		$(AA_sources_path)/AA_Enemy.cpp \
		$(AA_sources_path)/AA_Ghoul.cpp \
		$(AA_sources_path)/AA_EnemyManager.cpp

HEADERS=$(AA_headers_path)/AA_Config.h \
		$(AA_headers_path)/AA_Game.h \
		$(AA_headers_path)/AA_RefLinks.h \
		$(AA_headers_path)/AA_TextureLoader.h \
		$(AA_headers_path)/AA_Map.h \
		$(AA_headers_path)/AA_Tile.h \
		$(AA_headers_path)/AA_TileManager.h \
		$(AA_headers_path)/AA_Player.h \
		$(AA_headers_path)/AA_Camera.h \
		$(AA_headers_path)/AA_Level.h \
		$(AA_headers_path)/AA_Entity.h \
		$(AA_headers_path)/AA_DrawableEntity.h \
		$(AA_headers_path)/AA_Creature.h \
		$(AA_headers_path)/AA_LevelManager.h \
		$(AA_headers_path)/AA_Prop.h \
		$(AA_headers_path)/AA_PropManager.h \
		$(AA_headers_path)/AA_World.h \
		$(AA_headers_path)/AA_State.h \
		$(AA_headers_path)/AA_PlayState.h \
		$(AA_headers_path)/AA_MenuState.h \
		$(AA_headers_path)/AA_Enemy.h \
		$(AA_headers_path)/AA_Ghoul.h \
		$(AA_headers_path)/AA_EnemyManager.h

$(exe): $(SOURCES) $(HEADERS)
	g++ -std=c++20 -Wall $(SOURCES) -o $(exe) -I$(AA_headers_path) -I$(SDL_headers_path) -L$(SDL_libraries_path) -lSDL3 -lSDL3_image

.PHONY:
clean:
	rm -f $(exe)

debug:
	g++ -std=c++20 -Wall -g3 -O0 -fsanitize=address -fno-omit-frame-pointer $(SOURCES) -o $(exe) -I$(AA_headers_path) -I$(SDL_headers_path) -L$(SDL_libraries_path) -lSDL3 -lSDL3_image -fsanitize=address
