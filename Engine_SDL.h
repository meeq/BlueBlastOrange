#include "Engine.h"

#ifndef __ENGINE__SDL_H__
#define __ENGINE__SDL_H__

namespace SDL_Colors {
	const SDL_Color White = { 255, 255, 255 };
	const SDL_Color Black = { 0, 0, 0 };
}

namespace SDL {
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	const Uint32 rmask = 0x000000FF;
	const Uint32 gmask = 0x0000FF00;
	const Uint32 bmask = 0x00FF0000;
	const Uint32 amask = 0xFF000000;
	#else
	const Uint32 rmask = 0xFF000000;
	const Uint32 gmask = 0x00FF0000;
	const Uint32 bmask = 0x0000FF00;
	const Uint32 amask = 0x000000FF;
	#endif

	const Uint32 Origin = 0 ;
	
	extern Uint32 VideoFlags ;
	extern SDL_Rect Screen ;
	extern SDL_Rect Area ;
	extern bool Fullscreen ;
	extern float Scale ;
	
	extern bool OpenGL ;

	extern SDL_Surface* ScreenBuffer ;
	
	// The SDL Event structure
	extern SDL_Event Event ; 
	extern SDL_Joystick* Joystick ; 
	extern SDL_Delta FPS ;

	// The SDL Setup and UnSetup Jargon
	bool Initialize(  );
	void Uninitialize(  );
	
	bool Resize( int width, int height ) ;

	SDL_Surface* LoadImage( char* filename );
	
	void Blit (		SDL_Surface* Src, SDL_Surface* Dest, 
					Sint32 SrcX = 0, Sint32 SrcY = 0, 
					Sint32 DestX = 0, Sint32 DestY = 0, 
					Uint32 W = NULL, Uint32 H = NULL
					);
	void Blit (	SDL_Surface* Src, Sint32 x, Sint32 y ) ;
	void Blit (	Draw::Sprite* sprite ) ;
	
	void Flip(void) ;
	void Blank(void) ;
					
	void ReadVideoSettings( char* filename ) ; // Read in the game settings from a file.
	
	int GL_TextureSize( int input ) ;
	Uint8* GL_Texture( SDL_Surface* surface );
}

#include "Game_SDL.h"

#endif
