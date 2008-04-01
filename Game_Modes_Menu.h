#include "Engine.h"

#ifndef __GAME__MODES_MENU_H__
#define __GAME__MODES_MENU_H__

enum MenuOption { NO_SELECTION, NEW_GAME, SHOW_HELP, SHOW_CREDITS, EXIT_GAME };

class Menu: public Game
{
	public:
		Menu			(  ) ;
		~Menu			(  ) ;
		bool	Run		(  ) ;
		void	Events	(  ) ;
		void	Draw	(  ) ;
		void	Release	(  ) ;
		void	Reload	(  ) ;
		
		void	Highlight(  ) ;
		void	Highlight( Controller::ACTION direction );
		void	Select	(  );
				
		void	Call( Game* mode );
		
		Objects::Pills	pills ;
		
		Draw::Sprite* Image ;
		
	private:
		Shapes::Rect	menu_items[5] ;
		MenuOption		highlighted ;
		MenuOption		selected ;
};

#endif
