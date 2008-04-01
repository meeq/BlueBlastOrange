#include "Engine.h"

#ifndef __ENGINE_MODES_H__
#define __ENGINE_MODES_H__

class Game
{
	public:
		Game					(  ) ;
		virtual			~Game	(  ) ;
		virtual bool	Run		(  ) ;
		virtual void	Events	(  ) ;
		virtual void	Draw	(  ) ;
		virtual void	Release	(  ) ;
		virtual void	Reload	(  ) ;

		Objects::Cursor											cursor ;
		std::multimap<Controller::ACTION, Controller::Button>	controls ;
		bool													exit ;
	private:
};

#endif
