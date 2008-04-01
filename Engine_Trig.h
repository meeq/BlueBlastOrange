#include "Engine.h"

#ifndef __ENGINE__TRIG_H__
#define __ENGINE__TRIG_H__

namespace Trig {
	double Distance( int x1, int y1, int x2, int y2 ) ;
	double Distance( Shapes::Shape* b1, Shapes::Shape* b2 ) ;
	bool Collision( Shapes::Rect b, Shapes::Point p ) ;
	bool Collision( Shapes::Point p, Shapes::Rect b ) ;
	bool Collision( Shapes::Rect b1, Shapes::Rect b2 ) ;
	bool Collision( Shapes::Rect b, Shapes::Circle c ) ;
	bool Collision( Shapes::Circle c, Shapes::Rect b ) ;
	bool Collision( Shapes::Circle c1, Shapes::Circle c2 ) ;
}

#endif
