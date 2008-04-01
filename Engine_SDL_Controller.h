#include "Engine.h"

#ifndef __ENGINE__SDL_CONTROLLER_H__
#define __ENGINE__SDL_CONTROLLER_H__

namespace Controller {
	enum ACTION {	UP, DOWN, LEFT, RIGHT, SHOOT, BOMB, EXIT, PAUSE,
					SWITCH_SHIELD, ORANGE_SHIELD, BLUE_SHIELD	} ;
					
	enum TYPE { KEYBOARD, JOYSTICK, MOUSE } ;
						
	class Button {
		public:
			Button( TYPE type, int button ) ;
			TYPE type ;
			int button ;
	};
						
	bool Pressed(	Controller::ACTION control, 
					std::multimap<Controller::ACTION, Button>::iterator map );
	bool Released(	ACTION control, 
					std::multimap<Controller::ACTION, Button>::iterator map ) ;
	int DeadZone ( int value ) ;
	int Velocity ( int velocity ) ;
}

namespace PSP_JOYSTICK {

	/****** SDL_Joystick Key -> PSP Buttons Mapping *******
	 0 Triangle
	 1 Circle
	 2 Cross
	 3 Square
	 4 Left trigger
	 5 Right trigger
	 6 Down
	 7 Left
	 8 Up
	 9 Right
	10 Select
	11 Start
	12 Home
	13 Hold
	******************************************************/
	enum BUTTONS {	TRIANGLE, CIRCLE, CROSS, SQUARE,
					L, R, DOWN, LEFT, UP, RIGHT,
					SELECT, START, HOME, HOLD };
					
}

#endif
