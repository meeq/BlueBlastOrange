#include "Engine_SDL_Controller.h"

using namespace std;

Controller::Button::Button( TYPE type, int button )
{
	this->type = type;
	this->button = button;
}

bool Controller::Pressed(	ACTION control, 
							multimap<ACTION, Button>::iterator map )
{
	if ( map->first == control )
		if	(	( SDL::Event.type == SDL_KEYDOWN ) && 
				( map->second.type == KEYBOARD )  &&
				( SDL::Event.key.keysym.sym == map->second.button ) 
			)
			return true ;
		else if	(	( SDL::Event.type == SDL_JOYBUTTONDOWN ) && 
					( map->second.type == JOYSTICK ) &&
					( SDL::Event.jbutton.button == map->second.button ) 
				)
			return true ;
		else if	(	( SDL::Event.type == SDL_MOUSEBUTTONDOWN ) && 
					( map->second.type == MOUSE ) &&
					( SDL::Event.button.button == map->second.button ) 
				)
			return true ;

	return false ;
}

bool Controller::Released(	ACTION control, 
							multimap<ACTION, Button>::iterator map )
{
	if ( map->first == control )
		if	(	( SDL::Event.type == SDL_KEYUP ) && 
				( map->second.type == KEYBOARD )  &&
				( SDL::Event.key.keysym.sym == map->second.button ) 
			)
			return true ;
		else if	(	( SDL::Event.type == SDL_JOYBUTTONUP ) && 
					( map->second.type == JOYSTICK ) &&
					( SDL::Event.jbutton.button == map->second.button ) 
				)
			return true ;
		else if	(	( SDL::Event.type == SDL_MOUSEBUTTONUP ) && 
					( map->second.type == MOUSE ) &&
					( SDL::Event.button.button == map->second.button ) 
				)
			return true ;

	return false ;
}

bool Controller::StandardMap( Game* mode )
{
	if ( SDL::Event.type == SDL_VIDEORESIZE ) {
		mode->Release() ;
		SDL::Resize( SDL::Event.resize.w, SDL::Event.resize.h );
		mode->Reload();
		return true ;
	}

	if	( SDL::Event.type == SDL_QUIT ) {
		mode->exit = true ;
		return true ;
	}
		
	if	( SDL::Event.type == SDL_MOUSEMOTION ) {
		mode->cursor.setLocation( (int)((float)SDL::Event.button.x / SDL::Scale), (int)((float)SDL::Event.button.y / SDL::Scale) ) ;
		return true ;
	}
	
	if	( SDL::Event.type == SDL_JOYAXISMOTION ) {
		// All of the dead-zone stuff is handled by the Cursor object
		if( SDL::Event.jaxis.axis == 0 ) // If the X-axis moved...
			mode->cursor.setXVel( SDL::Event.jaxis.value ) ;
		else if ( SDL::Event.jaxis.axis == 1 ) // If the Y-axis moved...
			mode->cursor.setYVel( SDL::Event.jaxis.value ) ;
		return true ;
	}
	
	return false ;
}

int Controller::DeadZone( int value )
{
	if ( fabs( (double) value ) > ( 32767 / 7 ) )
		return value ;
	else
		return 0;
}

int Controller::Velocity ( int velocity )
{
	return velocity / 1500 ;
}
