#include "Engine.h"

#ifndef __ENGINE__SDL_ANIM__
#define __ENGINE__SDL_ANIM__

#include "Engine_SDL_Delta.h"

class SDL_Anim
{
	public:
		SDL_Anim(  ) ;
		SDL_Anim( SDL_Anim* src ) ;
		SDL_Anim( SDL_Surface* src ) ;
		
		~SDL_Anim(  ) ;
		
		SDL_Surface* Play( bool loop = true ) ;
		void Pause(  ) ;
		void Unpause(  ) ;
		int AddFrame( SDL_Surface* frame ) ;
		SDL_Surface* GetFrame( int frame = -1 ) ;
		std::vector<SDL_Surface*> GetFrames(  ) ;
		
		void SetMarker ( int frame = 0 ) ;
		
	private:
		std::vector<SDL_Surface*> frames ;
		bool paused ;
		unsigned int current_frame ;
		SDL_Delta delta ;
};

#endif
