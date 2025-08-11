AA2_headers_path=AA2/include
AA2_sources_path=AA2/src
SDL_headers_path=SDL/include
SDL_libraries_path=SDL/lib

exe=aa2

$(exe): $(AA2_sources_path)/main.cpp
	g++ -Wall $(AA2_sources_path)/main.cpp -o $(exe) -I$(AA2_headers_path) -I$(SDL_headers_path) -L$(SDL_libraries_path) -lSDL3 -lSDL3_image

.PHONY:
clean:
	rm -f $(exe)