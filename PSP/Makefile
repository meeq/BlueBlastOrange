PSPSDK =	$(shell psp-config --pspsdk-path)
PSPBIN = 	$(PSPSDK)/../bin

TARGET =	Blue_Blast_Orange
OBJS =		Main.o \
			Engine_Cursor.o Engine_Draw.o Engine_Modes.o Engine_Random.o \
			Engine_SDL_Anim.o Engine_SDL_Delta.o Engine_SDL_Controller.o \
			Engine_SDL.o Engine_Shapes.o Engine_Trig.o Engine.o \
			Game_Draw.o	Game_Modes_BBO.o Game_Modes_Menu.o Game_Modes.o \
			Game_Objects_Pill.o Game_Objects_Pills.o Game_Objects_Shield.o \
			Game_SDL.o

FLAGS = 	-D PSP
CFLAGS = 	-O2 -G0 -Wall \
			$(shell $(PSPBIN)/sdl-config --cflags | sed s/-Dmain=SDL_main//)
CXXFLAGS = 	$(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = 	$(CFLAGS)

LIBDIR =
LIBS = 	 	-lSDL_mixer -lSDL_image \
			$(shell $(PSPBIN)/sdl-config --libs | sed s/-lSDLmain//) \
			-lSDL_gfx -lSDL_ttf \
			-lfreetype -ljpeg -lpng -lz -lglut -lGLU -lGL \
			-lm -lstdc++ -lpspge -lpspvfpu -lpspsdk -lpspctrl -lpspumd \
			-lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio
		
LDFLAGS = 	-DMODULE_NAME=$(TARGET) PSP/psp-setup.c

#PSPSDK Stuff
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Blue Blast Orange

include $(PSPSDK)/lib/build.mak
