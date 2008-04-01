#include "Engine.h"

#ifndef __ENGINE__DRAW_H__
#define __ENGINE__DRAW_H__

#include "Engine_Shapes.h"
#include "Engine_SDL.h"

namespace Draw {
	class Sprite
	{
		public:
			Sprite(  ) ;
			Sprite( Sprite* sprite ) ;
			Sprite( char* filename ) ;
			Sprite( SDL_Surface* surface ) ;
			//Sprite( SDL_Anim* anim ) ;
			Sprite( GLuint& texture ) ;
			
			~Sprite() ;
			
			void Load( char* filename ) ;
			void Load( SDL_Surface* surface ) ;
			//void Load( SDL_Anim* anim ) ;
			void Reload() ;
			
			void Clear() ;
			
			void Update() ;
			
			char*			Filename ;
			SDL_Surface*	Surface ;
			//SDL_Anim*		Anim ;
			GLuint			Texture ;
			Shapes::Rect	Geometry ;
			int				Layer ;
			int				Rotation ;
		private:
			void Reset() ;
			void MakeGLTexture() ;
	};


	void Blank(void) ;
	void Flip(void) ;
	
	void Screen	( SDL_Surface* src, int x = 0, int y = 0 ) ;
	void Screen	( Sprite* sprite ) ;
	
	void Text( char* message, TTF_Font* font, int x, int y, bool centered = false ) ;
}

#endif
