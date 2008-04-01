/*
 *	SDL_BBO
 *	modes.cpp
 */	

// Let's get our headers!
#include "Game_Modes.h"
using namespace std;

Game::Game()
{	
	controls.insert( make_pair( Controller::UP, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::UP ) ) );
	controls.insert( make_pair( Controller::UP, Controller::Button( Controller::KEYBOARD, SDLK_UP ) ) ) ;
	
	controls.insert( make_pair( Controller::DOWN, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::DOWN ) ) );
	controls.insert( make_pair( Controller::DOWN, Controller::Button( Controller::KEYBOARD, SDLK_DOWN ) ) ) ;
	
	controls.insert( make_pair( Controller::LEFT, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::LEFT ) ) );
	controls.insert( make_pair( Controller::LEFT, Controller::Button( Controller::KEYBOARD, SDLK_LEFT ) ) ) ;
	
	controls.insert( make_pair( Controller::RIGHT, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::RIGHT ) ) );
	controls.insert( make_pair( Controller::RIGHT, Controller::Button( Controller::KEYBOARD, SDLK_RIGHT ) ) ) ;
	
	controls.insert( make_pair( Controller::SHOOT, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::CROSS ) ) );
	controls.insert( make_pair( Controller::SHOOT, Controller::Button( Controller::KEYBOARD, SDLK_SPACE ) ) ) ;
	controls.insert( make_pair( Controller::SHOOT, Controller::Button( Controller::MOUSE, SDL_BUTTON_LEFT ) ) ) ;
	
	controls.insert( make_pair( Controller::BOMB, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::CIRCLE ) ) );
	controls.insert( make_pair( Controller::BOMB, Controller::Button( Controller::KEYBOARD, SDLK_RETURN ) ) ) ;
	controls.insert( make_pair( Controller::BOMB, Controller::Button( Controller::MOUSE, SDL_BUTTON_RIGHT ) ) ) ;
	
	controls.insert( make_pair( Controller::EXIT, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::SELECT ) ) );
	controls.insert( make_pair( Controller::EXIT, Controller::Button( Controller::KEYBOARD, SDLK_ESCAPE ) ) ) ;
	controls.insert( make_pair( Controller::EXIT, Controller::Button( Controller::KEYBOARD, SDLK_q ) ) ) ;
	
	controls.insert( make_pair( Controller::PAUSE, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::START ) ) );
	controls.insert( make_pair( Controller::PAUSE, Controller::Button( Controller::KEYBOARD, SDLK_p ) ) ) ;
	
	controls.insert( make_pair( Controller::SWITCH_SHIELD, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::SQUARE ) ) );
	controls.insert( make_pair( Controller::SWITCH_SHIELD, Controller::Button( Controller::KEYBOARD, SDLK_LSHIFT ) ) ) ;
	controls.insert( make_pair( Controller::SWITCH_SHIELD, Controller::Button( Controller::KEYBOARD, SDLK_RSHIFT ) ) ) ;
	controls.insert( make_pair( Controller::SWITCH_SHIELD, Controller::Button( Controller::MOUSE, SDL_BUTTON_MIDDLE ) ) ) ;
	
	controls.insert( make_pair( Controller::ORANGE_SHIELD, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::L ) ) );
	controls.insert( make_pair( Controller::ORANGE_SHIELD, Controller::Button( Controller::MOUSE, SDL_BUTTON_WHEELUP ) ) ) ;
	
	controls.insert( make_pair( Controller::BLUE_SHIELD, Controller::Button( Controller::JOYSTICK, PSP_JOYSTICK::R ) ) );
	controls.insert( make_pair( Controller::BLUE_SHIELD, Controller::Button( Controller::MOUSE, SDL_BUTTON_WHEELDOWN ) ) ) ;
}
