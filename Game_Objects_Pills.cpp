/*******************************************************************************
 * 	Blue Blast Orange for PSP
 *  	pills.cpp
 *
 *  	Created by Christopher Bonhage on 4/5/07.
 ******************************************************************************/

#include "Game_Objects_Pills.h" 

using namespace Objects;

// ----- Constructors -----------------------------------

Pills::Pills(  )
{
	this->fall_rate = Defaults::PILL_YSPEED ;
	this->bounce_rate = Defaults::PILL_XSPEED ;
	
	this->spawn_rate = Defaults::PILL_SPAWN_RATE ;
	this->spawn_timer.start();
	
	/*
	// Let's load up all of the pills, calculate their rotation caches, and set up their animations.
	char* pill_images[] = { "images/pill_blue.png", "images/pill_orange.png", "images/pill_grey.png" } ;
	int scale = 1 ;		// Keeping everything the same size
	int smooth = 1 ;	// We want a smooth, pretty rotation
	for ( int i = 0 ; i < 3 ; i++ ) {
		this->Images[i] = new Draw::Sprite( pill_images[i] ) ;
		if (!SDL::OpenGL) {
			SDL_Anim* temp_anim = new SDL_Anim( ) ;
			for ( int draw_angle = 0 ; draw_angle < 360 ; draw_angle += 8 )
				temp_anim->AddFrame( rotozoomSurface( this->Images[i]->Surface, draw_angle, scale, smooth) ) ;
			delete this->Images[i] ;
			this->Images[i] = new Draw::Sprite( temp_anim ) ;
		}
	}
	*/
}
		  	
// ----- Destructor -------------------------------------
		
Pills::~Pills(  ) 
{ 
	this->Clear() ;
}
	  	
// ----- Inspectors -------------------------------------
std::list<Objects::Pill*>::iterator Pills::Begin(  )
{
	return this->pills.begin() ;
}

std::list<Objects::Pill*>::iterator Pills::End(  )
{
	return this->pills.end() ;
}

  	
// ----- Mutators ---------------------------------------

void Pills::Draw(  )
{
	std::list<Objects::Pill*>::iterator i;
	Objects::Pill* pill = NULL ;
	for( i = this->pills.begin() ; i != this->pills.end() ; i++ )
	{
		pill = *i;
		
		Draw::Sprite* image = this->Images[pill->getColor()] ;
		
		image->Update() ;
		
		// Correct for Circle[CenterPoint] -> Rectangle[Origin]
		image->Geometry.x = ( pill->x * SDL::Scale - image->Surface->w / 2 ) ;
		image->Geometry.y = ( pill->y * SDL::Scale - image->Surface->w / 2 ) ;
		image->Layer = PILLS_LAYER ;
		image->Rotation = pill->getRotation() ;
		
		Draw::Screen( image ) ;
		
		// Let the pill fall naturally.
		pill->fall();
	}
}

void Pills::Spawn( int level )
{
	// how many pills should have spawned in between frames?
	int spawn_count = (int) floor( (this->spawn_timer.get_ticks() / 1000.0) / this->spawn_rate ) ;
	// go ahead and spawn any that should be spawned by now...
	for ( int i = 1 ; i <= spawn_count ; i++ )
	{
		// figure out each pill's unique fall rate
		float fall = this->fall_rate + Random::Range(-2.0,2.0) ;
		if (fall <= 0)
			fall = this->fall_rate ;
		// Make the pill
		Objects::Pill* pill = new Objects::Pill( 
					Random::Pill_X(), 
					(int)(0 - (Defaults::PILL_RADIUS * Random::Range(1.0, (double) (level / 10)))), 
					(int)this->bounce_rate, 
					(int)fall ) ;
		this->Add( pill ) ;
		// restart the pill_spawn timer
		this->spawn_timer.start();
	}
	
	// Limit the fall rate
	if (this->fall_rate > (75) ) {
		this->fall_rate = (75) ;
	}
	// Limit the spawn rate
	if ( this->spawn_rate < (0.2) ) {
		this->spawn_rate = (0.2) ;
	}
}
void Pills::SpawnPause( bool setting )
{
	if (setting)
		this->spawn_timer.pause() ;
	else
		this->spawn_timer.unpause() ;
}

void Pills::Add( Objects::Pill* pill )
{
	this->pills.push_back( pill );
}

void Pills::Clear(  )
{
	std::list<Objects::Pill*>::iterator i ;
	for ( i = this->pills.begin() ; i != this->pills.end() ; (i!=this->pills.end())?i++:i=i )
		this->Delete( i ) ;
	this->pills.clear() ;
}

void Pills::Delete( std::list<Objects::Pill*>::iterator& pill )
{
	delete (*pill) ;
	pill = this->pills.erase(pill) ;
}

void Pills::SpawnSpeed(float change)
{
	spawn_rate += change;
}

void Pills::FallSpeed(float change)
{
	fall_rate += change;
}

