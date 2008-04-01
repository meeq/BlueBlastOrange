/*******************************************************************************
 * 	Blue Blast Orange for PSP
 *  	pills.cpp
 *
 *  	Created by Christopher Bonhage on 4/5/07.
 ******************************************************************************/

#include "Game_Objects_Pill.h" 
#include "Game_Modes_BBO.h"

using namespace Objects;

// ------------------------------------------------------
// ----- Constructors -----------------------------------
// ------------------------------------------------------

Pill::Pill( int x, int y, int xspeed, int yspeed ) : 
													Shapes::Circle( x, y, Defaults::PILL_RADIUS )
{
	this->color = Random::BBOColor() ;
	
	this->xspeed = xspeed ;
	this->yspeed = yspeed ;
	this->rotation = 0 ;
}
		  	
// ------------------------------------------------------
// ----- Destructor -------------------------------------
// ------------------------------------------------------
		
//Pill::~Pill() { } 	// Nothing special to do...
	  	
// ------------------------------------------------------
// ----- Inspectors -------------------------------------
// ------------------------------------------------------
	  	
BBOColor Pill::getColor() const		{ return this->color ; }
Shapes::Circle Pill::getShape() const
{
	return Shapes::Circle( this->x, this->y, this->r );
}
int Pill::getRotation() const { return this->rotation ; }
  	
// ------------------------------------------------------
// ----- Mutators ---------------------------------------
// ------------------------------------------------------

void Pill::fall()
{
	rotation += 8 ;
	if ( rotation >= 360 )
		rotation -= 360 ;
	this->setY( this->getY() + (int)floor( yspeed ) ) ;
}

// ------------------------------------------------------
// ----- Other Pill Functions ---------------------------
// ------------------------------------------------------

BBOColor Random::BBOColor()
{ 
	switch( Random::Range(0,1) )
	{
		case BLUE:
			return BLUE;
			break;
		case ORANGE:
			return ORANGE;
			break;
	}
	return GREY ;
}

int Random::Pill_X()
{
	return Random::Range(	Defaults::GAME.x + Defaults::PILL_RADIUS, 
							Defaults::GAME.x + Defaults::GAME.w - Defaults::PILL_RADIUS) ;
}
