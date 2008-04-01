#include "Engine.h"

#ifndef __GAME__SDL_H__
#define __GAME__SDL_H__

namespace Video {
	const float SCREEN_RATIO = 1.6;
	const int FRAMES_PER_SECOND = 30;
	const bool CAP_FPS = true;
}

namespace SDL_Sounds {
	extern Mix_Chunk* Hit ;
	extern Mix_Chunk* Miss ;
	extern Mix_Chunk* Shield ;
	extern Mix_Chunk* Catch ;
	extern Mix_Chunk* Drop ;
	extern Mix_Chunk* Level ;
	extern Mix_Chunk* Bomb ;
}

namespace SDL_Fonts {
	extern TTF_Font* Orson ;
	extern float Size ;
}

#endif
