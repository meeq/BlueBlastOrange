#include "Engine.h"

#ifndef __GAME__OBJECTS_PILL_H__
#define __GAME__OBJECTS_PILL_H__

namespace Random {
	int Pill_X() ;
	BBOColor BBOColor() ;
}

namespace Objects {
	class Pill: public Shapes::Circle
	{
	  public:		  	
		// ----- Constructors -----------------------------------
			Pill( int x = Random::Pill_X(), int y = 0, 
				int xspeed = Defaults::PILL_XSPEED, 
				int yspeed = Defaults::PILL_YSPEED ) ;
		  	
		// ----- Destructor -------------------------------------
			//~Pill();
	  	
		// ----- Inspectors -------------------------------------
			BBOColor getColor() const ;
			Shapes::Circle getShape() const ;
			int getRotation() const ;
	  	
		// ----- Mutators ---------------------------------------
			void fall() ;
	
		// ----- Facilitators -----------------------------------
			//void operator++();
			
	  private:
		BBOColor		color ;
		float			xspeed ;
		float			yspeed ;
		int				rotation ;
	};
}

#endif
