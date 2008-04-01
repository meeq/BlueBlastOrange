/*
 *	SDL_BBO
 *	game.cpp
 */	

// Let's get our headers!

#include "Game_Modes_BBO.h"

using namespace std;

// ******************************************************
// ----- Game Class -------------------------------------
// ******************************************************

// ----- Constructors -----------------------------------
BBO::BBO(  ) : Game(  )
{
	this->level = 1;
	this->score = 0;
	this->shots = 0;
	this->hits = 0;
	this->captures = 0;
	this->drops = 0;
	this->lives = 4;
	
	this->bomb_acc = 0;
	
	this->exit = false;
	this->pause = false;
	
	this->Reload() ;
	
}

BBO::~BBO()
{
	// Stop all streams
	if ( Mix_PlayingMusic() );
		Mix_FadeOutMusic( 500 );
	SDL_Delay( 600 );
	
	this->pills.Clear() ;
	
	this->Release() ;
}

// ----- Methods ----------------------------------------

// Calculate our accuracy based on the number of hits versus the number of shots
int BBO::HitAccuracy ( )
{
	// if you've actually hit anything...
	if (this->hits > 0)
		// figure out the accuracy
		return (int)((float)(this->hits) / (float)(this->shots) * 100.0); 
	// otherwise we'd be dividing by zero, which is quite difficult.
	return 0;
}

// Draws every layer in the game in order, then flips the buffer.
void BBO::Draw (  )
{
	Draw::Blank() ;	// clear the screen
	
	this->Image->Update() ;
	// draw the background image
	this->Image->Geometry.x = SDL::Area.x ;
	this->Image->Geometry.y = SDL::Area.y ;
	this->Image->Layer = BACKGROUND_LAYER ;
	
	Draw::Screen( this->Image ) ;

	if (!this->pause)
		this->pills.Draw() ;
		
	this->shield.Draw() ;	// draw the shield on top of the pills and background
	this->DrawOverlay() ;	// draw the overlays for scores and whatnot
	
	if (this->pause) {
		Draw::Text( "Game Paused", SDL_Fonts::Orson, SDL::Area.w / 2, SDL::Area.h / 2, true );
	}
	
	this->cursor.Draw() ;
	
	Draw::Flip();	// show the player what we've drawn
}

void BBO::Release(void)
{
	delete this->Image  ;
	delete this->Overlay  ;
	delete this->pills.Images[0] ;
	delete this->pills.Images[1] ;
	delete this->pills.Images[2] ;
	delete this->cursor.Image ;
	
	Mix_FreeChunk( SDL_Sounds::Hit ) ;
	Mix_FreeChunk( SDL_Sounds::Miss ) ;
	Mix_FreeChunk( SDL_Sounds::Shield ) ;
	Mix_FreeChunk( SDL_Sounds::Catch ) ;
	Mix_FreeChunk( SDL_Sounds::Drop ) ;
	Mix_FreeChunk( SDL_Sounds::Level ) ;
	
	// Free up any fonts
	TTF_CloseFont( SDL_Fonts::Orson );
}

void BBO::Reload(void)
{
	this->Pause( true ) ;

	SDL_Fonts::Size = 56 * SDL::Scale ;
	SDL_Fonts::Orson = TTF_OpenFont( "images/font.ttf", (int)SDL_Fonts::Size );
	
	Draw::Blank() ;	// clear the screen
	Draw::Text( "Game Loading...", SDL_Fonts::Orson, SDL::Area.w / 2, SDL::Area.h / 2, true );
	Draw::Flip();	// show the player what we've drawn
	
	this->Image = new Draw::Sprite( "images/screen_game.png" ) ;
	this->Overlay = new Draw::Sprite( "images/overlay_game.png" ) ;
	this->cursor.Image = new Draw::Sprite( "images/cursor.png" );
	this->pills.Images[BLUE] = new Draw::Sprite( "images/pill_blue.png" );
	this->pills.Images[ORANGE] = new Draw::Sprite( "images/pill_orange.png" );
	this->pills.Images[GREY] = new Draw::Sprite( "images/pill_grey.png" );
	this->shield.Images[BLUE] = new Draw::Sprite( "images/shield_blue.png" );
	this->shield.Images[ORANGE] = new Draw::Sprite( "images/shield_orange.png" );
	this->shield.Images[GREY] = new Draw::Sprite( "images/shield_grey.png" );
	
	// Load any sounds that the game mode uses
	SDL_Sounds::Hit = Mix_LoadWAV("sounds/hit.wav") ;
	SDL_Sounds::Miss = Mix_LoadWAV("sounds/miss.wav") ;
	SDL_Sounds::Shield = Mix_LoadWAV("sounds/shield.wav") ;
	SDL_Sounds::Catch = Mix_LoadWAV("sounds/catch.wav") ;
	SDL_Sounds::Drop = Mix_LoadWAV("sounds/drop.wav") ;
	SDL_Sounds::Level = Mix_LoadWAV("sounds/level.wav") ;
	SDL_Sounds::Bomb = Mix_LoadWAV("sounds/bomb.wav") ;
	
	this->Pause( false ) ;
}

void BBO::Pause ( bool state )
{
	if (state) {
		this->pause = true ;
	} else {
		this->pause = false ;
	}
	
	this->pills.SpawnPause( this->pause ) ;
}

bool BBO::Run (  )
{
	this->CalculateScores() ;			// Check score-related settings
	this->pills.Spawn( this->level );	// Spawn all the pretty new pills
	this->ShieldCheck();
	this->Events();						// Run through the input events and parse them.
	
	while( this->pause ) 
	{
		this->Draw();			// draw a frozen version of the screen
		
		// wait for the player to hit unpause
		while(SDL_PollEvent(&SDL::Event))
		{	
			using namespace Controller ;
			
			if ( StandardMap( this ) )
					continue ;
		
			for(	multimap< ACTION, Button >::iterator i = 
						this->controls.begin() ; 
					i != this->controls.end() ; 
					++i ) 
			{
				if	( Pressed( EXIT, i ) )
					this->exit = true ;
					
				if	( Pressed( PAUSE, i ) )
					this->Pause( false );
			}
		}
		
		if (this->exit)
			this->Pause( false );
	}
	
	this->Draw();				// draw the screen.
		
	if (this->lives < 1) {
		SDL_Delay( 1000 ) ;
		return false;
	}
		
	return true;
}

void BBO::CalculateScores		(  )
{
	// if your score is past one of the level thresholds
	if ( this->score > 100.0 * pow( (float) 1.5, this->level ) )
	{
		// You've obviously leveled up
		this->level++;
		
		// if the level number is even
		if ( this->level % 2 == 0 ) 
			// increase the spawn rate dramatically
			this->pills.SpawnSpeed(-.05f) ;
		// if the level number is odd
		else
			// increase the fall rate dramatically
			this->pills.FallSpeed(2.5f) ;
		
		// We play a pretty sound for you.
		Mix_PlayChannel(-1, SDL_Sounds::Level, 0) ; // Play the 'levelup' sound.
	}
}

void BBO::ShieldCheck ( )
{
	std::list<Objects::Pill*>::iterator i;
	Objects::Pill* pill = NULL ;
	for( i = this->pills.Begin() ; i != this->pills.End() ; (i!=this->pills.End())?i++:i=i )
	{
		pill = *i;
		
		Shapes::Rect shield_threshold( this->shield.x, this->shield.y, this->shield.w, pill->r / 2 );
		Shapes::Circle check_pill( pill->x, pill->y, pill->r / 2 ) ;
		
		if ( Trig::Collision( check_pill, shield_threshold ) )
		{
			// If the pill color is the same as the shield color...
			if ( pill->getColor() == this->shield.getColor() ) {
				this->pills.Delete( i ) ;

				// Update your stats
				this->captures++;
				this->shield.capture = true;
					
				// Give you some points for not sucking
				score += static_cast<int>(this->combo_acc.size() / 5);
				// Rack up that bomb accumulator
				this->bomb_acc += 1;
					
				// Play the sound!
				Mix_PlayChannel(-1, SDL_Sounds::Catch, 0) ; // Play the 'catch' sound.
			}
		} else {
			// If the top of the pill falls below the bottom of the game area
			if ( pill->getY() - Defaults::PILL_RADIUS > Defaults::GAME.h ) {
				this->pills.Delete( i ) ;
				
				// Change your stats
				this->drops++;
				this->lives--;
				this->combo_acc.clear() ; // Ha ha!  You lose a life and your combo!
				this->bomb_acc = 0 ;
				
				// Play the cute little noise
				Mix_PlayChannel(-1, SDL_Sounds::Drop, 0) ; // Play the 'drop' sound.
			}
		}
	}
}

void BBO::Shoot			(  )
{	
	this->shots++; // Count the shot.
	bool miss = true; // Assume the worst...
	
	
	
	Objects::Pill* pill;
	for ( list<Objects::Pill*>::iterator i = this->pills.Begin() ; i != this->pills.End() ; (i!=this->pills.End())?i++:i=i )
	{	// Check each pill to see if we hit it.
		pill = (*i);
		// If we are targeting and shot the pill...
		if ( Trig::Collision( this->cursor.getShape(), pill->getShape() ) ) 
		{
			miss = false;				// We hit something.  Rack up that combo!
		
			// Fiddle with the statistics
			this->hits++;				// Give the user credit for hitting it.
			this->combo_acc.push_front( pill->getColor() ); // Add this pill to the combo set
			
			// Give this man some points!
			if (this->combo_acc.size() > 5)
				this->score += 10 * static_cast<int>(this->combo_acc.size() / 5);
			else
				this->score += 10;
			
			
			this->pills.Delete( i ) ;	// Delete the pill
			
			// Oh yeah, and play a sound
			Mix_PlayChannel(-1, SDL_Sounds::Hit, 0) ; // Play the 'hit' sound.
		}
	}
	// If we didn't hit anything...
	if ( miss ) {
		
		// You don't lose points, but you do lose your combo...
		this->combo_acc.clear();
		
		// And we play the little sound for when you miss one.
		Mix_PlayChannel(-1, SDL_Sounds::Miss, 0) ; // Play the 'miss' sound.
		
		pills.SpawnSpeed(.01f);
	}
}

void BBO::Bomb			(  )
{
	// If you've earned a bomb...
	if (this->bomb_acc >= 8) {
		// Delete all of the pills in play
		this->pills.Clear() ;
		
		Mix_PlayChannel(-1, SDL_Sounds::Bomb, 0) ; // Play the 'miss' sound.
	}
	// Reset the bomb accumulator, even (especially) if fired prematurely. 
	this->bomb_acc = 0 ;
}

// Handles the input events from the controller in a menu-environment.
void BBO::Events(void)
{
	while(SDL_PollEvent(&SDL::Event))
	{
		using namespace Controller ;
		
		if ( Controller::StandardMap( this ) )
				continue ;
		
		for(	multimap<ACTION, Button>::iterator i = this->controls.begin() ; 
				i != this->controls.end() ; 
				++i ) 
		{
			if	( Pressed( EXIT, i ) )
					this->exit = true ;
			
			if	( Pressed( PAUSE, i ) ) {
				this->Pause( true );
				continue ;
			}
			
			if	( Pressed( UP, i ) ) {
				cursor.setYVel( -32768 ) ;
				continue ;
			}
			if ( Pressed( DOWN, i ) ) {
				cursor.setYVel( 32767 ) ;
				continue ;
			}
			if ( Released( UP, i ) ) {
				cursor.setYVel( 0 );
				continue ;
			}
			if ( Released( DOWN, i ) ) {
				cursor.setYVel( 0 );
				continue ;
			}
			if	( Pressed( LEFT, i ) ) {
				cursor.setXVel( -32768 ) ;
				continue ;
			}
			if ( Pressed( RIGHT, i ) ) {
				cursor.setXVel( 32767 ) ; 
				continue ;
			}
			if ( Released( LEFT, i ) )  {
				cursor.setXVel( 0 ) ;
				continue ;
			}
			if ( Released( RIGHT, i ) ) {
				cursor.setXVel( 0 );
				continue ;
			}		
			if	( Pressed( SHOOT, i ) ) {
				this->Shoot();
				continue ;
			}
			if	( Pressed( BOMB, i ) ) {
				this->Bomb();
				continue ;
			}
			if	( Pressed( SWITCH_SHIELD, i ) ) {
				this->shield.swapColor();		
				Mix_PlayChannel(-1, SDL_Sounds::Shield, 0) ; // Play the 'shield' sound.		
				continue ;	
			}
			
			if	( Pressed( ORANGE_SHIELD, i ) ) {
				this->shield.setColor( ORANGE );
				Mix_PlayChannel(-1, SDL_Sounds::Shield, 0) ; // Play the 'shield' sound.
				continue ;
			}
							
			if	( Pressed( BLUE_SHIELD, i ) ) {
				this->shield.setColor( BLUE );
				Mix_PlayChannel(-1, SDL_Sounds::Shield, 0) ; // Play the 'shield' sound.
				continue ;
			}
		}
	}
}

void BBO::DrawOverlay(  ) 
{ 
	// Put the overlay on the screen
	this->Overlay->Geometry.x = SDL::Area.x ;
	this->Overlay->Geometry.y = SDL::Area.y ;
	this->Overlay->Layer = OVERLAY_LAYER ;
	Draw::Screen( this->Overlay );
	
	int margin = (int)(30 * SDL::Scale) ;
	int margin_left = SDL::Area.x + margin ;
	int margin_right = SDL::Area.x + margin + (int)(1440 * SDL::Scale) ;
	int margin_top = SDL::Area.y + margin ;
	
	char	level[20], score[20], accuracy[20], shots[20], 
			hits[20], captures[20], drops[20] ;
	
	// Left Side of the Scores Overlay
	sprintf( level, "Level: %d", this->level );
	Draw::Text( level, SDL_Fonts::Orson, margin_left, margin_top + (0 * SDL_Fonts::Size) ) ;
		
	sprintf( score, "Score: %d", this->score );
	Draw::Text( score, SDL_Fonts::Orson, margin_left, margin_top + (1 * SDL_Fonts::Size) ) ;
	
	// Combo Accumulator Display
	int pill_width = this->pills.Images[GREY]->Surface->w / 2;
	list<BBOColor>::iterator combo ; // We need to iterate through our lists. Tragedy, I know.
	combo = this->combo_acc.begin() ;	// But we're only iterating through the first 5!
	bool score_combo = true;
	BBOColor combo_color ;
	if ( combo == this->combo_acc.end() )
		combo_color = GREY ;
	else
		combo_color = *combo ; // The color we're checking against.
	
	for ( int i = 0 ; i < 5 ; i++ ) {
		BBOColor color ;
		if (combo != this->combo_acc.end()) {
			color = *combo ;
			if (*combo != combo_color)	// If this pill isn't the same color as the first one...
				score_combo = false; 	// You don't have a combo.
			combo++; // Move to the next pill in the accumulator
		} else {
			color = GREY ;
			score_combo = false; 	// You don't have a combo.
		}
		this->pills.Images[color]->Geometry.x = margin_left + i * (pill_width * 1.5) - pill_width / 2 ;
		this->pills.Images[color]->Geometry.y = margin_top + ( 3 * SDL_Fonts::Size ) ;
		this->pills.Images[color]->Layer = PILLS_LAYER ;
		this->pills.Images[color]->Rotation = 0 ;
		Draw::Screen( this->pills.Images[color] );
	}
	char combo_plus[5] = "+0";
	if (score_combo && this->combo_acc.size() > 5 ) {
		sprintf(combo_plus, "+%d", (int) (this->combo_acc.size() - 5) ) ;
	} else {
		this->combo_acc.erase( combo, this->combo_acc.end() );
	}
	Draw::Text(	combo_plus, SDL_Fonts::Orson,	
				margin_left + 5 * (pill_width * 1.5), 
				margin_top + ( 3 * SDL_Fonts::Size ) + (pill_width - SDL_Fonts::Size / 4) ) ;
	
	// Right side of the Scores Overlay	
	sprintf( accuracy, "Accuracy: %d%%", this->HitAccuracy() );
	Draw::Text( accuracy, SDL_Fonts::Orson, margin_right, margin_top + (0 * SDL_Fonts::Size) ) ;
	
	sprintf( shots, "Shots: %d", this->shots );
	Draw::Text( shots, SDL_Fonts::Orson, margin_right, margin_top + (1 * SDL_Fonts::Size) ) ;
	
	sprintf( hits, "Hits: %d", this->hits );
	Draw::Text( hits, SDL_Fonts::Orson, margin_right, margin_top + (2 * SDL_Fonts::Size) ) ;
	
	sprintf( captures, "Captures: %d", this->captures );
	Draw::Text( captures, SDL_Fonts::Orson, margin_right, margin_top + (3 * SDL_Fonts::Size) ) ;
	
	sprintf( drops, "Drops: %d", this->drops );
	Draw::Text( drops, SDL_Fonts::Orson, margin_right, margin_top + (4 * SDL_Fonts::Size) ) ;
}

