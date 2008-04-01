/*
 *	SDL_BBO
 *	main.cpp
 */	

// Let's get our headers!
#include "Engine.h"

int main(int argc, char* argv[])
{
	printline("Starting the program...");
	if ( ! SDL::Initialize() )
		return 1;
	printline( "Looks like everything initialized okay..." ) ;
	Menu menu;
	printline( "Let's let the menu do its job..." ) ;
	while( menu.Run() ) { /* Do absolutely nothing */ }
	printline( "We're done; let's uninitialize" ) ;
	SDL::Uninitialize();
	return 0;
}
