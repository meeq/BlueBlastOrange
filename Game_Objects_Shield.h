#include "Engine.h"

#ifndef __GAME__OBJECTS_SHIELD_H__
#define __GAME__OBJECTS_SHIELD_H__

namespace Objects {
	class Shield: public Shapes::Rect
	{
		public:
			  
			Shield( Shapes::Rect r = Defaults::SHIELD, BBOColor color = BLUE ) ;
			~Shield(  ) ;
			
			void		Draw(  ) ;
			
			void		setColor( BBOColor color ) ;
			void		swapColor(  ) ;
			BBOColor	getColor(  ) ;
			
			Shapes::Rect getShape() const ;
			
			bool		capture;
			bool		captured(  ) ;
			
			Draw::Sprite* Images[3] ;
			
		private:
			BBOColor	color;
			
	};
}

#endif
