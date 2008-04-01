#include "Engine.h"

#ifndef __GAME__BBO_H__
#define __GAME__BBO_H__

#include "Game_Objects.h"

class BBO: public Game
{
	public:
		BBO			(  ) ;
		~BBO			(  ) ;
		
		bool	Run		(  ) ;
		void	Events	(  ) ;
		void	Draw	(  ) ;
		void	DrawOverlay	(  ) ;
		
		void	Release	(  ) ;
		void	Reload	(  ) ;
		void	Pause	( bool state ) ;
		
		void	CalculateScores	(  ) ;
		void	ShieldCheck		(  ) ;
				
		void	Shoot		(  ) ;
		void	Bomb		(  ) ;
				
		int		HitAccuracy (  ) ;
		
		std::list<BBOColor>	combo_acc ; // Our beloved combo accumulator.
		int					bomb_acc ;
		
		int		level ;
		int		score ;
		int		shots ;
		int		hits ;
		int		captures ;
		int		drops ;
		int		lives ;
		
		Objects::Pills	pills ;
		Objects::Shield	shield ;
		
		Draw::Sprite* Image ;
		Draw::Sprite* Overlay ;
	
	private:
		
		bool	pause ;
		
};

#endif
