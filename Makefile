#NMAKE

SDL_PATH = ../SDL
SDL_INCLUDE = $(SDL_PATH)/include
SDL_LIB = $(SDL_PATH)/lib/x64

INCLUDE = ./include

FLAGS = /nologo /W4 /external:W0 /EHsc /I $(INCLUDE) /I $(SDL_INCLUDE) /Fesnake.exe
LINKER = SDL2.lib /link /LIBPATH:"$(SDL_LIB)"

release: src/*.cpp
	$(CC) $(FLAGS) /O2 /GS /GL /Zo- $** $(LINKER) /subsystem:windows

debug: src/*.cpp
	$(CC) $(FLAGS) /DDEBUG_ENABLE $** $(LINKER) /subsystem:console
