#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <math.h>

#include <list>
#include <vector>
#include <map>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Engine_SDL_rotozoom.h"

// Include the OpenGL headers... wherever they are...
#ifdef WIN32
#include <gl/gl.h>
#include <gl/glu.h>
#endif
#ifdef OSX
#include "gl.h"
#include "glu.h"
#endif
#ifdef LINUX
#include "gl.h"
#include "glu.h"
#endif
#ifdef PSP
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Engine_Prototypes.h"
#include "Game_Prototypes.h"

#include "Engine_SDL_Controller.h"

#include "Engine_Shapes.h"
#include "Engine_Trig.h"
#include "Engine_Random.h"

#include "Engine_Draw.h"

#include "Game_Defaults.h"
#include "Game_Objects.h"

#include "Engine_Cursor.h"

#include "Engine_Modes.h"
#include "Game_SDL_Controller.h"

#include "Engine_SDL.h"
#include "Engine_SDL_Delta.h"
#include "Engine_SDL_Controller.h"
#include "Engine_SDL_Anim.h"

#include "Game_Modes.h"

#include "Game_Draw.h"

void printline( char* string ) ;

int main( int argc, char* argv[] );

#endif
