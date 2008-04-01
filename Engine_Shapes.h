#include "Engine.h"

#ifndef __ENGINE__SHAPES_H__
#define __ENGINE__SHAPES_H__

namespace Shapes {
	// Shape Prototypes
	class Shape;
	class Point;
	class Rect;
	class Circle;
	
	class Shape
	{
		public:
			Shape ( int x = 0, int y = 0 );
			Shape ( Shape* p );
			int getX() ;
			int getY() ;
			Shape getLocation() ;
			void setX( int x ) ;
			void setY( int y ) ;
			void setLocation( int x, int y );
			void setLocation( Shape* p ) ;
			int x, y;
	} ;
	
	class Point: public Shape
	{
		public:
			Point ( int x = 0, int y = 0 );
			Point ( Shape* p );
	} ;
	
	class Rect: public Shape
	{
		public:
			Rect ( int x = 0, int y = 0, int w = 0, int h = 0 ) ;
			Rect ( Shape* p, int w = 0, int h = 0 ) ;
			Rect ( Shape* p, Shape* s ) ;
			Rect ( Rect* r ) ;
			bool collision( Rect r ) ;
			bool collision( Circle c ) ;
			int getW() ;
			int getH() ;
			Shape getSize() ;
			void setW( int w ) ;
			void setH( int h ) ;
			void setSize( int w, int h ) ;
			void setSize( Shape* p ) ;
			int w, h;
	} ;
	
	class Circle: public Shape
	{
		public:
			Circle ( int x = 0, int y = 0, int r = 0 ) ;
			Circle ( Shape* p, int r = 0 ) ;
			bool collision( Rect r ) ;
			bool collision( Circle c ) ;
			int getR() ;
			void setR( int r ) ;
			int r;    
	} ;
}

#endif
