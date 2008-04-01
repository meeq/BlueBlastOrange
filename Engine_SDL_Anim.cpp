#include "Engine_SDL_Anim.h"

SDL_Anim::SDL_Anim(  )
{
	this->current_frame = 0 ;
	this->paused = false ;
	this->delta.start() ;
}

SDL_Anim::SDL_Anim( SDL_Anim* src )
{
	if ( src != NULL )
		this->frames = src->GetFrames();
	this->current_frame = 0 ;
	this->paused = false ;
	this->delta.start() ;
}

SDL_Anim::SDL_Anim( SDL_Surface* src ) 
{ 
	this->current_frame = this->AddFrame( src ) ;
	this->paused = false ;
	this->delta.start() ;
}

SDL_Anim::~SDL_Anim( )
{
	for ( unsigned int i = 0 ; i < this->frames.size() ; i++ ) {
		SDL_FreeSurface( this->frames[i] );
	}
	this->frames.clear() ;
}

SDL_Surface* SDL_Anim::Play( bool loop )
{
	SDL_Surface* frame = this->GetFrame( this->current_frame ) ;
	if ( !this->paused ) {
		if ( this->delta.get_ticks() > ( Video::FRAMES_PER_SECOND ) )
			this->current_frame += 1;
		if ( this->current_frame >= this->frames.size() )
			if (loop)
				this->current_frame = 0;
			else
				this->current_frame = this->frames.size() - 1 ;
		this->delta.start() ; // Reset the timer
	}

	return frame;
}

void SDL_Anim::Pause() { this->paused = true ; this->delta.pause() ; }
void SDL_Anim::Unpause() { this->paused = false ; this->delta.unpause() ; }

int SDL_Anim::AddFrame( SDL_Surface* frame ) 
{
	this->frames.push_back(frame) ;
	return this->frames.size() - 1 ;
}

SDL_Surface* SDL_Anim::GetFrame( int frame )
{
	if (this->frames.size() == 0)
		return NULL;
	int last_frame = this->frames.size() - 1 ;
	if (frame >= last_frame ) { frame = last_frame ; }
	if (frame == -1 ) { frame = this->current_frame; }
	
	return this->frames[frame] ;
}

std::vector<SDL_Surface*> SDL_Anim::GetFrames(  )
{
	return this->frames ;
}

void SDL_Anim::SetMarker ( int frame )
{
	int last_frame = this->frames.size() - 1 ;
	if (frame >= last_frame ) { frame = last_frame ; }
	this->current_frame = frame ;
}
