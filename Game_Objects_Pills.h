#include "Engine.h"

#ifndef __GAME__OBJECTS_PILLS_H__
#define __GAME__OBJECTS_PILLS_H__

#include "Game_Objects_Pill.h"
#include "Engine_SDL_Delta.h"

namespace Objects {
	class Pills
	{
	  public:		  	
		// ----- Constructors -----------------------------------
			Pills(  ) ;
		  	
		// ----- Destructor -------------------------------------
			~Pills(  ) ;
	  	
		// ----- Inspectors -------------------------------------
			std::list<Objects::Pill*>::iterator Begin(  ) ;
			std::list<Objects::Pill*>::iterator End(  ) ;
	  	
		// ----- Mutators ---------------------------------------
			void Draw() ;
			
			void SpawnSpeed(float change) ;
			void FallSpeed(float change) ;
			
			void Spawn(int level = 0) ;
			void SpawnPause(bool setting) ;
						
			void Add( Objects::Pill* pill ) ;
			void Delete( std::list<Objects::Pill*>::iterator& pill ) ;
			void Clear(  ) ;
			
			Draw::Sprite* Images[3] ;
			

	  private:
		std::list<Objects::Pill*> pills ;
	  
		float					fall_rate ;	 // vertical fall rate
		float					bounce_rate ;	 // horizontal movement speed
		
		SDL_Delta				spawn_timer ;
		float					spawn_rate ; // Seconds per new pill spawn
	};
}

#endif
