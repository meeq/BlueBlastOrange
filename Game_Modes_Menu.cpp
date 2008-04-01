/*
 *	SDL_BBO
 *	menu.cpp
 */	

// Let's get our headers!
#include "Game_Modes_Menu.h"
using namespace std;

// Sets up all of the variables our menu will use
Menu::Menu(  ) : Game(  )
{
	this->cursor.r = 1 ; // Super-precise menu cursor
	
	this->exit = false;

	this->highlighted = NEW_GAME ;
	this->selected = NO_SELECTION ;
	
	Objects::Pill* left_pill = new Objects::Pill( 0, 0, 0, 0 ) ;
	this->pills.Add( left_pill ) ;
	Objects::Pill* right_pill = new Objects::Pill( 0, 0, 0, 0 ) ;
	this->pills.Add( right_pill ) ;

	this->menu_items[NEW_GAME] = Shapes::Rect( 1250, 45, 375, 75 ) ;
	this->menu_items[SHOW_HELP] = Shapes::Rect(	1250, 135, 535, 75 ) ;
	this->menu_items[SHOW_CREDITS] = Shapes::Rect(	1250, 225, 535, 75 ) ;
	
	this->Reload();
	
}

Menu::~Menu(  ) 
{
	this->pills.Clear() ;
	
	// Free up all images
	this->Release() ;
}

// Draws the layers in the menu, then flips the buffer.
void Menu::Draw(void)
{
	Draw::Blank(); // Clear the screen
	
	this->Image->Update() ;
	this->Image->Geometry.x = SDL::Area.x ;
	this->Image->Geometry.y = SDL::Area.y ;
	this->Image->Layer = -10 ;
	
	Draw::Screen( this->Image );
	
	this->pills.Draw();
	this->cursor.Draw();
	
	Draw::Flip();
}

void Menu::Release(void)
{
	delete this->Image  ;
	delete this->pills.Images[0] ;
	delete this->pills.Images[1] ;
	delete this->pills.Images[2] ;
	delete this->cursor.Image ;
}

void Menu::Reload(void)
{
	this->Image = new Draw::Sprite( "images/screen_menu.png" ) ;
	this->cursor.Image = new Draw::Sprite( "images/cursor.png" );
	this->pills.Images[BLUE] = new Draw::Sprite( "images/pill_blue.png" );
	this->pills.Images[ORANGE] = new Draw::Sprite( "images/pill_orange.png" );
	this->pills.Images[GREY] = new Draw::Sprite( "images/pill_grey.png" );
}

bool Menu::Run(void)
{
	Events();
	Highlight();
	Select();
	Draw();
	if (this->exit)
		return false;
	return true;
}

// Checks what's highlighted by the cursor and moves the indicator pills accordingly.
void Menu::Highlight(void)
{
	// Check to see if we're highlighting any of the menu options with the cursor...
	if ( Trig::Collision( this->menu_items[NEW_GAME], this->cursor ) )
		this->highlighted = NEW_GAME ;
	if ( Trig::Collision( this->menu_items[SHOW_HELP], this->cursor ) )
		this->highlighted = SHOW_HELP ;
	if ( Trig::Collision( this->menu_items[SHOW_CREDITS], this->cursor ) )
		this->highlighted = SHOW_CREDITS ;
		
	// Figure out where to put the pills that surround the highlighted option
	int x1,x2,y;
	switch ( this->highlighted )
	{
		case NEW_GAME:
			x1	=	this->menu_items[NEW_GAME].getX();
			x2	=	x1 + menu_items[NEW_GAME].getW();
			y	=	this->menu_items[NEW_GAME].getY();
			break;
		case SHOW_HELP:
			x1	=	this->menu_items[SHOW_HELP].getX();
			x2	=	x1 + menu_items[SHOW_HELP].getW();
			y	=	this->menu_items[SHOW_HELP].getY();
			break;
		case SHOW_CREDITS:
		default:
			x1	=	this->menu_items[SHOW_CREDITS].getX();
			x2	=	x1 + menu_items[SHOW_CREDITS].getW();
			y	=	this->menu_items[SHOW_CREDITS].getY();
			break;
	}
	
	list<Objects::Pill*>::iterator i = this->pills.Begin();
	// Move the first pill
		Objects::Pill* pill = (*i);
		// convert the rectangle point to a circle from the radius at the center
		pill->setLocation( x1 + Defaults::PILL_RADIUS, y + Defaults::PILL_RADIUS );
	// Iterate to the second one
		i++;
	// Now move the second one
		pill = (*i);
		// convert the rectangle point to a circle from the radius at the center
		pill->setLocation( x2 + Defaults::PILL_RADIUS, y + Defaults::PILL_RADIUS );
}

// Handles keyboard/d-pad up/down movement in menus.
void Menu::Highlight( Controller::ACTION direction )
{
	if (direction == Controller::UP)
		switch( this->highlighted )
		{
			case NEW_GAME:
				break;
			case SHOW_HELP:
				highlighted = NEW_GAME;
				break;
			case SHOW_CREDITS:
				highlighted = SHOW_HELP;
			default:
				break;
		}
						
	if (direction == Controller::DOWN)
		switch( this->highlighted )
		{
			case NEW_GAME:
				highlighted = SHOW_HELP;
				break;
			case SHOW_HELP:
				highlighted = SHOW_CREDITS;
				break;
			case SHOW_CREDITS:
				break;
			default:
				break;
		}
}

void Menu::Select(void)
{
	switch( this->selected )
	{
		case NEW_GAME:
			this->Call( new BBO );
			break;
		case SHOW_HELP:
			// Stubbed!
			break;
		case SHOW_CREDITS:
			// Stubbed!
			break;
		case EXIT_GAME:
			exit = true;
		default:
			break;
	}
	this->selected = NO_SELECTION; // If something was selected, this will let us choose something else
}

void Menu::Call( Game* mode )
{
	while ( mode->Run() ) {  
		if (mode->exit) {
			this->exit = true;
			break;
		}
	}
	delete mode ;
}

// Handles the input events from the controller in a menu-environment.
void Menu::Events(void)
{
	while(SDL_PollEvent(&SDL::Event))
	{
		using namespace Controller ;
		
		if ( StandardMap( this ) )
			break ;
		
		for(	multimap<ACTION, Button>::iterator i = controls.begin() ; 
			i != controls.end() ; 
			++i ) 
		{
			if	( Pressed( EXIT, i ) )
					this->exit = true ;
			
			if	( Pressed( UP, i ) )
					this->Highlight( Controller::UP );
					
			if	( Pressed( DOWN, i ) )
					this->Highlight( Controller::DOWN );
					
			if	( Pressed( SHOOT, i ) )
					this->selected = this->highlighted;
					
			if	( Pressed( BOMB, i ) )
					this->selected = this->highlighted;
			
		}
	}
}
