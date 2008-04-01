#include "Engine.h"

#ifndef __ENGINE__CURSOR_H__
#define __ENGINE__CURSOR_H__

namespace Objects {
	class Cursor: public Shapes::Circle
	{
		public:
			Cursor(); // Constructor
			~Cursor(); // Destructor
			void	Draw(  ) ;
			// Inspectors
			Shapes::Circle getShape() const ;
			
			int		getXVel(  ) const;
			int		getYVel(  ) const;
			// Mutators
			void	setXVel( int xVel );
			void	setYVel( int yVel );
			void	applyVelocity(  ) ;
			
			Draw::Sprite* Image ;			
			
		private:
			int xVel_ ; // Velocity of the x-axis joystick movement
			int yVel_ ; // Velocity of the y-axis joystick movement
	};
}

#endif
