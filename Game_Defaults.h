#ifndef __GAME__DEFAULTS_H__
#define __GAME__DEFAULTS_H__

namespace Defaults {
	const Shapes::Rect	GAME = Shapes::Rect( 480, 0, 960, 1200 ) ;
	const Shapes::Rect	SCREEN = Shapes::Rect( 0, 0, 1920, 1200 ) ;
	
	const int			CURSOR_RADIUS = 20 ;
	
	const float			PILL_XSPEED = 0.0;
	const float			PILL_YSPEED = 5.0 ;
	const int			PILL_RADIUS = 40 ;
	const float			PILL_SPAWN_RATE = 1.0 ;
	
	const Shapes::Rect	SHIELD = Shapes::Rect( 0, 900, 960, 300 ) ;
}

#endif
