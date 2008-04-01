#include "Engine_Trig.h"

double Trig::Distance( int x1, int y1, int x2, int y2 )
{
    //Return the distance between the two points
    return sqrt( pow( (double) x2 - x1, 2 ) + pow( (double) y2 - y1, 2 ) );
}

double Trig::Distance( Shapes::Shape* p1, Shapes::Shape* p2 )
{
	return Trig::Distance( p1->getX(), p1->getY(), p2->getX(), p2->getY() );
}

bool Trig::Collision( Shapes::Rect b, Shapes::Point p )
{
	if ( ( p.x >= b.x ) && ( p.x <= b.x + b.w ) && ( p.y >= b.y ) && ( p.y <= b.y + b.h ) ) {
		return true ;
	}
	return false ;
}
bool Trig::Collision( Shapes::Point p, Shapes::Rect b ) { return Trig::Collision( b, p ); }

bool Trig::Collision( Shapes::Rect b1, Shapes::Rect b2 )
{
	// Corner Check
	Shapes::Point corner;
	
	// Box 1 In Box 2
	// Top-Left Corner
	corner = Shapes::Point( b1.x, b1.y ) ;
	if( Trig::Collision( b2, corner ) )
		return true;
	// Top-Right Corner
	corner = Shapes::Point( b1.x + b1.w, b1.y ) ;
	if( Trig::Collision( b2, corner ) )
		return true;
	// Bottom-Left Corner
	corner = Shapes::Point( b1.x, b1.y + b1.h ) ;
	if( Trig::Collision( b2, corner ) )
		return true;	
	// Bottom-Right Corner
	corner = Shapes::Point( b1.x + b1.w, b1.y + b1.h ) ;
	if( Trig::Collision( b2, corner ) )
		return true;
	  
	// Box 2 in Box 1
	// Top-Left Corner
	corner = Shapes::Point( b2.x, b2.y ) ;
	if( Trig::Collision( b1, corner ) )
		return true;
	// Top-Right Corner
	corner = Shapes::Point( b2.x + b2.w, b2.y ) ;
	if( Trig::Collision( b1, corner ) )
		return true;
	// Bottom-Left Corner
	corner = Shapes::Point( b2.x, b2.y + b2.h ) ;
	if( Trig::Collision( b1, corner ) )
		return true;	
	// Bottom-Right Corner
	corner = Shapes::Point( b2.x + b2.w, b2.y + b2.h ) ;
	if( Trig::Collision( b1, corner ) )
		return true;
	return false;
}

bool Trig::Collision( Shapes::Rect b, Shapes::Circle c )
{
	// Let's do a cross-test to see if any rectangle sides are in the circle...
	Shapes::Rect cross_horiz( c.x - c.r, c.y, c.r * 2, 1 ) ; 
	Shapes::Rect cross_vert( c.x, c.y - c.r, 1, c.r * 2 ) ; 
	// These are lines that make a cross inside the circle. (+)
	if ( Trig::Collision( cross_vert, b ) )
		return true;
	if ( Trig::Collision( cross_horiz, b ) )
		return true;
	// Now let's check and see if any rectangle corners are in the circle...
	Shapes::Point corner;
	// Top-Left Corner
	corner = Shapes::Point( b.getX(), b.getY() );
	if( Trig::Distance( &c, &corner ) < c.getR() ) 
		return true;
	// Top-Right Corner
	corner = Shapes::Point( b.getX() + b.getW(), b.getY() );
	if( Trig::Distance( &c, &corner ) < c.getR() ) 
		return true;
	// Bottom-Left Corner
	corner = Shapes::Point( b.getX(), b.getY() + b.getH() );
	if( Trig::Distance( &c, &corner ) < c.getR() )
		return true;
	// Bottom-Right Corner
	corner = Shapes::Point( b.getX() + b.getW(), b.getY() + b.getH() );
	if( Trig::Distance( &c, &corner ) < c.getR() ) 
		return true;
	
	return false; // Looks like the rectangle isn't colliding with the circle.
}
bool Trig::Collision( Shapes::Circle c, Shapes::Rect b ) { return Trig::Collision( b, c ) ; }

bool Trig::Collision( Shapes::Circle c1, Shapes::Circle c2 )
{
	return ( Trig::Distance( &c1, & c2 ) < ( c1.getR() + c2.getR() ) ) ;
}
