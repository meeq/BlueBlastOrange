#include "Engine_Shapes.h"

using namespace Shapes;

Shape::Shape( int x, int y ) {	this->setLocation( x, y ) ; }
Shape::Shape( Shape* p ) { this->setLocation( p ) ; }
int Shape::getX() {	return this->x ; }
int Shape::getY() { return this->y ; }
Shape Shape::getLocation() { return Shape( this->getX(), this->getY() ) ; }
void Shape::setX( int x ) { this->x = x ; }
void Shape::setY( int y ) { this->y = y ; }
void Shape::setLocation( int x, int y ) { this->setX(x); this->setY(y) ; }
void Shape::setLocation( Shape* p )
{
	this->setX( p->getX() ) ;
	this->setY( p->getY() ) ;
} 

Point::Point( int x, int y ):Shape( x, y ) { }
Point::Point( Shape* p ):Shape( p ) { }

Rect::Rect( int x, int y, int w, int h ):Shape( x, y ) { this->setSize( w, h ) ; }
Rect::Rect( Shape* p, int w, int h ):Shape( p ) { this->setSize( w, h ) ; }
Rect::Rect( Shape* p, Shape* s ):Shape( p ) { this->setSize( s ) ; }
Rect::Rect( Rect* r ) 
{
	this->setX( r->getX() ) ;
	this->setY( r->getY() ) ;
	this->setW( r->getW() ) ;
	this->setH( r->getH() ) ;
}
bool Rect::collision( Rect r ) { return Trig::Collision( *this, r ) ; }
bool Rect::collision( Circle c ) { return Trig::Collision( *this, c ) ; }
int Rect::getW() { return this->w ; }
int Rect::getH() { return this->h ; }
Shape Rect::getSize() { return Shape( this->getW(), this->getH() ) ; }
void Rect::setW( int w ) { this->w = w ; }
void Rect::setH( int h ) { this->h = h ; }
void Rect::setSize( int w, int h ) { this->setW(w); this->setH(h); }
void Rect::setSize( Shape* p )
{
	this->setW( p->getX() ) ;
	this->setH( p->getY() ) ;
}

Circle::Circle( int x, int y, int r ):Shape( x, y ) { this->setR( r ) ; }
Circle::Circle( Shape* p, int r ):Shape( p ) { this->setR( r ) ; }
bool Circle::collision( Rect r ) { return Trig::Collision( *this, r ) ; }
bool Circle::collision( Circle c ) { return Trig::Collision( *this, c ) ; }
int Circle::getR() { return this->r ; }
void Circle::setR( int r ) { this->r = r ; }
