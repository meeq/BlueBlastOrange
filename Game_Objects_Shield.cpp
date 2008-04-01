#include "Game_Objects_Shield.h"

using namespace Objects;

// ------ Constructors ------------------------------------
Shield::Shield( Shapes::Rect r, BBOColor color ): Shapes::Rect( r )
{
	this->setColor( color );
	this->capture = false ;
	this->x += Defaults::GAME.x ;
}

Shield::~Shield(  ) {	}

void Shield::Draw(  ) 
{
	BBOColor shield = this->getColor();
	if ( this->captured() )
		shield = GREY ;
	this->Images[shield]->Geometry.x = SDL::Area.x + (this->x * SDL::Scale) ;
	this->Images[shield]->Geometry.y = SDL::Area.y + (this->y * SDL::Scale) ;
	
	this->Images[shield]->Layer = SHIELD_LAYER ;
	
	Draw::Screen( this->Images[shield] );
}

void Shield::setColor( BBOColor color ) { this->color = color ; }
void Shield::swapColor(  ) 
{
	if (this->color == BLUE)
		this->color = ORANGE;
	else
		this->color = BLUE;
}
BBOColor Shield::getColor(  ) { return this->color ; }

Shapes::Rect Shield::getShape(  ) const
{
	return Shapes::Rect( this->x, this->y, this->w, this->h );
}

bool Shield::captured(  )
{
	bool value = this->capture ; // Set a temporary variable for the true/false.
	this->capture = false;		// Reset the catch to false because it's been caught if so.
	return value;				// Return what shield_catch was before we reset it.
}
