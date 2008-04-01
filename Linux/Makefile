TARGET = ../bin/Linux/blue-blast-orange

CC = gcc
CPP = g++

cfiles =	Main.cpp Linux/Engine_SDL_rotozoom.o \
			Engine.cpp Engine_Cursor.cpp Engine_Draw.cpp Engine_Modes.cpp \
			Engine_Random.cpp Engine_SDL.cpp Engine_SDL_Anim.cpp \
			Engine_SDL_Controller.cpp Engine_SDL_Delta.cpp \
			Engine_Shapes.cpp Engine_Trig.cpp \
			Game_Draw.cpp Game_Modes.cpp Game_Modes_BBO.cpp \
			Game_Modes_Menu.cpp Game_Objects_Pills.cpp\
			Game_Objects_Pill.cpp Game_Objects_Shield.cpp Game_SDL.cpp
			
flags = 	-Wall -D LINUX -I /usr/include/SDL \
			-l SDL -l SDL_image -l SDL_mixer -l SDL_ttf \
			-I /usr/include/GL -l GL -l GLU

all: ${TARGET}

Linux/Engine_SDL_rotozoom.o:
	${CC} -c -I/usr/include/SDL \
		-o Linux/Engine_SDL_rotozoom.o Engine_SDL_rotozoom.c

${TARGET}: ${cfiles}
	@echo "Linking!"
	${CPP} ${flags} -o ${TARGET} ${cfiles} 

clean:
	@rm -Rf ${TARGET} Linux/Engine_SDL_rotozoom.o

clear: clean

