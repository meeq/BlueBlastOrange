/*
 *	SDL_BBO
 *	cursor.cpp
 */	

// Let's get our headers!
#include "Engine_Cursor.h"

// ******************************************************
// ----- Cursor Class -------------------------------------
// ******************************************************

// ----- Constructors -----------------------------------
Objects::Cursor::Cursor():Shapes::Circle(	Defaults::GAME.w / 2, 
											Defaults::GAME.h / 2, 
											Defaults::CURSOR_RADIUS		)
{
	xVel_ = 0;
	yVel_ = 0;
	
}

Objects::Cursor::~Cursor() {  }

// ----- Inspectors -------------------------------------
int Objects::Cursor::getXVel() const { return xVel_ ; }
int Objects::Cursor::getYVel() const { return yVel_ ; }

Shapes::Circle Objects::Cursor::getShape() const
{
	return Shapes::Circle( this->x, this->y, this->r );
}

// ----- Mutators ---------------------------------------
void Objects::Cursor::setXVel( int xVel )
{
	xVel_ = Controller::Velocity( Controller::DeadZone(xVel) );
}

void Objects::Cursor::setYVel( int yVel )
{
	yVel_ = Controller::Velocity( Controller::DeadZone(yVel) );
}


void Objects::Cursor::applyVelocity(  )	// Moves the cursor based on velocity. Checks screen boundaries.
{
	// Let's go ahead and move however far horizontally we should be going...
    this->setX( this->getX() + xVel_ ) ;	
	// If we're outside the screen boundaries...
    if( ( this->getX() < Defaults::GAME.y ) || ( this->getX() > Defaults::GAME.w ) ) 
		// Then we're gonna have to move back!  Cursor can't be missing!
		this->setX( this->getX() - xVel_ );	
		
    // Let's go ahead and move however far vertically we should be going...
    this->setY( this->getY() + yVel_ ) ;	
	// If we're outside the screen boundaries...
    if( ( this->getY() < Defaults::GAME.y ) || ( this->getY() > Defaults::GAME.h ) ) { 
		// Then we're gonna have to move back!  Cursor can't be missing!
        this->setY( this->getY() + yVel_ ) ;
	}
}


void Objects::Cursor::Draw(  ) 
{ 
	this->Image->Update() ;

	int cursor_radius = this->Image->Surface->w / 2 ;
	this->Image->Geometry.x = SDL::Area.x + (int)( ( this->x * SDL::Scale ) - cursor_radius ) ;
	
	this->Image->Geometry.y = SDL::Area.y + (int)( ( this->y * SDL::Scale ) - cursor_radius ) ;
	
	this->Image->Layer = CURSOR_LAYER ;
	
	Draw::Screen( this->Image );
				
	this->applyVelocity();
}
