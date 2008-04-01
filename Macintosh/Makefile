TARGET = ../bin/Macintosh/blue-blast-orange

CC = 		gcc
CPP = 		g++

cfiles =	Macintosh/Engine_SDL_rotozoom.o Macintosh/SDLMain.o \
			Main.cpp \
			Engine.cpp Engine_Cursor.cpp Engine_Draw.cpp Engine_Modes.cpp \
			Engine_Random.cpp Engine_SDL.cpp Engine_SDL_Anim.cpp \
			Engine_SDL_Controller.cpp Engine_SDL_Delta.cpp Engine_Shapes.cpp \
			Engine_Trig.cpp \
			Game_Draw.cpp Game_Modes.cpp Game_Modes_BBO.cpp Game_Modes_Menu.cpp \
			Game_Objects_Pills.cpp Game_Objects_Pill.cpp Game_Objects_Shield.cpp Game_SDL.cpp 

flags = 	-Wall -D OSX -framework Cocoa \
			-I /System/Library/Frameworks/OpenGL.framework/Headers -framework OpenGL \
			-I Macintosh/Frameworks/SDL.framework/Headers -framework SDL \
			-I Macintosh/Frameworks/SDL_image.framework/Headers -framework SDL_image \
			-I Macintosh/Frameworks/SDL_mixer.framework/Headers -framework SDL_mixer \
			-I Macintosh/Frameworks/SDL_ttf.framework/Headers -framework SDL_ttf	

all: ${TARGET}

Macintosh/SDLMain.o:
	${CPP} -c -I Macintosh/Frameworks/SDL.framework/Headers \
			-o "Macintosh/SDLMain.o" "Macintosh/SDLMain-CLI.m"

Macintosh/Engine_SDL_rotozoom.o:
	${CC} -c -I Macintosh/Frameworks/SDL.framework/Headers \
			-o "Macintosh/Engine_SDL_rotozoom.o" Engine_SDL_rotozoom.c

${TARGET}: ${cfiles}
	@echo "Linking!"
	${CPP} ${flags} -o ${TARGET} ${cfiles}

clean:
	@rm -Rf ${TARGET} "Macintosh/Engine_SDL_rotozoom.o" "Macintosh/SDLMain.o"

clear: clean

