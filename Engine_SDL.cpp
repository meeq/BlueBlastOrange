#include "Engine_SDL.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

Uint32 SDL::VideoFlags ;
SDL_Rect SDL::Screen ;
SDL_Rect SDL::Area ;
bool SDL::Fullscreen ;
float SDL::Scale ;
bool SDL::OpenGL ;
	
SDL_Delta SDL::FPS ; // For frame limiting
SDL_Event SDL::Event ; 
SDL_Joystick* SDL::Joystick ;
SDL_Surface* SDL::ScreenBuffer ; 

bool SDL::Initialize( ) 
{
	srand( time(NULL) );	// Seed our random number generator

	// Initialize all of our SDL goodies...
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO ) != 0 ) {
		fprintf( stderr, "SDL_Init failed: %s\n", SDL_GetError(  ) ) ;
		return false;
	}
	SDL_EnableKeyRepeat(0,0);	// We definitely want key-repeats for arrow-key motion.
	SDL_JoystickEventState(SDL_ENABLE); // Start polling the joystick events
	SDL::Joystick = SDL_JoystickOpen( 0 ); // Set the joystick to the first one (or PSP joypad)
	if ( Mix_OpenAudio( 44100, AUDIO_S16, 2, 512 ) < 0 ) { // Set up the audio shit
		printline( "SDL_Mixer Failed to Open an Audio Device." ) ;
		return false;
	}
	TTF_Init(); // Initialize TrueType Fonts in SDL
	
	const SDL_VideoInfo* video_info = SDL_GetVideoInfo( ) ;
	if ( !video_info ) {
		fprintf( stderr, "SDL_GetVideoInfo failed: %s\n", SDL_GetError(  ) ) ;
		return false ;
	}
	
	ReadVideoSettings("settings.ini");
	
	VideoFlags = SDL_RESIZABLE ;
	
	if (SDL::OpenGL) {
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		VideoFlags |= SDL_OPENGL ;
		VideoFlags |= SDL_GL_DOUBLEBUFFER ;
	} else {
		if ( video_info->hw_available )
			VideoFlags = SDL_HWSURFACE ;
		else
			VideoFlags = SDL_SWSURFACE ;
			
		if ( video_info->blit_hw )
			VideoFlags |= SDL_HWACCEL ;
	}
	
	
	if ( SDL::Fullscreen )
		VideoFlags |= SDL_FULLSCREEN ;
		
	SDL::Resize( SDL::Screen.w, SDL::Screen.h ) ;
	
	// Set caption
	SDL_WM_SetCaption("Blue Blast Orange",""); // Set window caption
	SDL_WM_SetIcon(NULL,NULL);
	SDL_ShowCursor(0); // Do not show cursor
	
	Mix_Volume(-1,70);
	
	SDL::Blank();
	FPS.start();
	
	return true;
}

void SDL::Uninitialize( )
{
	// Close down all of the SDL subsystems
	TTF_Quit();
	Mix_CloseAudio();	
	SDL_JoystickClose( SDL::Joystick );
	SDL_Quit(); // And we're done!
}

bool SDL::Resize( int width, int height )
// THIS DOES NOT RESTORE YOUR OPENGL TEXTURES/RESIZE YOUR SDL_SURFACES.  DO THAT YOURSELF, ASSHOLE!
{
	SDL_QuitSubSystem( SDL_INIT_VIDEO );
	SDL_InitSubSystem( SDL_INIT_VIDEO );

	// Update our Screen State Globals with the new values...
	SDL::Screen.w = width ;
	SDL::Screen.h = height ;

	#ifdef PSP
	// The PSP is stuck at a measley 480x272, which is actually a little bit higher of an
	// aspect ratio than ours.  Oh well, black bars on the sides for you!
	//sizes = Sizebot( 480, 272, false ) ;
	SDL::Screen.w = 480 ; 
	SDL::Screen.h = 272 ;
	SDL::Fullscreen = false ;
	#endif
	
	if (SDL::Screen.w <= 0)
		SDL::Screen.w = 1 ;
	if (SDL::Screen.h <= 0)
		SDL::Screen.h = 1 ;
	
	float current_ratio = (float)(SDL::Screen.w) / (float)(SDL::Screen.h) ;
	if ( current_ratio == Video::SCREEN_RATIO ) {
		//fprintf( stdout, "Standard Aspect Ratio.\n") ;
		SDL::Area.w = SDL::Screen.w ; 
		SDL::Area.h = SDL::Screen.h ;
		SDL::Area.x = 0 ; 
		SDL::Area.y = 0 ;
	} else if ( current_ratio > Video::SCREEN_RATIO ) {
		//fprintf( stdout, "Wider Aspect Ratio.\n") ;
		SDL::Area.w = (int) ((float) SDL::Screen.h * Video::SCREEN_RATIO) ; 
		SDL::Area.h = SDL::Screen.h ;
		SDL::Area.x = (SDL::Screen.w - SDL::Area.w) / 2 ; 
		SDL::Area.y = 0 ;
	} else if ( current_ratio < Video::SCREEN_RATIO ) {
		//fprintf( stdout, "Narrower Aspect Ratio.\n") ;
		SDL::Area.w = SDL::Screen.w ; 
		SDL::Area.h = (int) ((float) SDL::Screen.w / Video::SCREEN_RATIO) ;
		SDL::Area.x = 0 ; 
		SDL::Area.y = (SDL::Screen.h - SDL::Area.h) / 2 ;
	}
	
	SDL::Scale = (float) SDL::Area.w / (float) Defaults::SCREEN.w ;
	
	fprintf( stderr, "BBO Size: %dx%d @ (%d,%d) [%f]/[%f]\n",	SDL::Area.w, SDL::Area.h,
																SDL::Area.x, SDL::Area.y,
																current_ratio, SDL::Scale );

	SDL::ScreenBuffer = SDL_SetVideoMode( SDL::Screen.w, SDL::Screen.h, 0, VideoFlags );
									
	if ( !SDL::ScreenBuffer ) {
		fprintf( stderr, "SDL_SetVideoMode failed: %s\n", SDL_GetError(  ) ) ;
		fprintf( stderr, "Blue Blast Orange cannot run at the specified display mode: %dx%d\n",
				SDL::Screen.w, SDL::Screen.h) ;
		return false ;
	}
	
	if (SDL::OpenGL) {
		glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Black Background
		
		// Depth Buffer Setup
		glClearDepth(1.0f);								
		glEnable(GL_DEPTH_TEST);
		glDepthFunc( GL_LEQUAL ) ;
		
		// Enable Texture Mapping
		glEnable(GL_TEXTURE_2D);
		
		// Set up Alpha Blending
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,0.1);
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glViewport( SDL::Area.x, SDL::Area.y, SDL::Area.w, SDL::Area.h ) ;
	
		// Use an Orthographic Projection for 2D Goodness
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		glOrtho(0.0f, SDL::Screen.w, SDL::Screen.h, 0.0f, -100.0f, 100.0f);
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
	}
	
	return true ;
}

void SDL::ReadVideoSettings( char* filename )
{
	ifstream fin(filename) ;
	if (! fin.is_open() ) {
		printf("Settings file not found; reverting to hard-coded defaults!\n");
		SDL::Screen.w = Defaults::SCREEN.w ;
		SDL::Screen.h = Defaults::SCREEN.h ;
		SDL::Fullscreen = false ;
		ofstream fout(filename);
		fout << "width=" << SDL::Screen.w << endl ;
		fout << "height=" << SDL::Screen.h << endl ;
		fout << "fullscreen=" << "false" << endl;
		fout << "opengl=" << "false" << endl;
		fout.close();
	} else {
		string line ;
		printf("Settings file found; reading parameters...\n");
		while ( std::getline ( fin, line ) ) {
			printf( "%s\n", line.c_str() ) ;
			if ( ( line.find( "width" ) ) == 0 ) {
				int width = 0;
				for ( int i = line.find("=")+1 ; i < (int)( line.size() ) ; i++ ) {
					width = (10 * width) + ( line[i] - 48 ) ;
				}
				SDL::Screen.w = width ;
			}
			if ( ( line.find( "height" )) == 0 ) {
				int height = 0;
				for ( int i = line.find("=")+1 ; i < (int)( line.size() ) ; i++ ) {
					height = (10 * height) + ( line[i] - 48 ) ;
				}
				SDL::Screen.h = height ;
			}
			if ( ( line.find( "fullscreen" )) == 0 ) {
				string setting = line.substr( line.find("=")+1 ) ;
				if ( setting == "true" )
					SDL::Fullscreen = true ;
				else
					SDL::Fullscreen = false ;
			}
			if ( ( line.find( "opengl" )) == 0 ) {
				string setting = line.substr( line.find("=")+1 ) ;
				if ( setting == "true" )
					SDL::OpenGL = true ;
				else
					SDL::OpenGL = false ;
			}
		}
	}
}

SDL_Surface* SDL::LoadImage( char* filename )
{
	SDL_Surface* tmp1;	SDL_Surface* tmp2;
	tmp1 = IMG_Load(filename);
	if(!tmp1)
		return NULL;
	// All the cool kids use alpha-transparent PNG images.  Let's set our alpha channel!		
	SDL_SetAlpha(tmp1, 0, 0);
	tmp2 = SDL_DisplayFormatAlpha(tmp1);
	// And we need to clean up after ourselves.  Mom isn't going to do that for us.
	SDL_FreeSurface(tmp1);
// The PSP has a special texture set because of its memory limitations, but the other clients
// need to resize everything for different screen resolutions.
#ifndef PSP
	// Now we need to resize our image to make it fit in any size window.
	// If the window size changes, we'll need to reload all of our images, of course.
	tmp1 = zoomSurface( tmp2, SDL::Scale, SDL::Scale, 1 ) ;
	SDL_FreeSurface( tmp2 );
	return tmp1;	
#endif
	return tmp2;
}

void SDL::Blit	( Draw::Sprite* sprite )
{
	SDL_Surface* image = sprite->Surface ;
	if (sprite->Rotation > 0)
		image = rotozoomSurface(sprite->Surface, sprite->Rotation, 1, 1) ;
	
	SDL_Rect src, dest ;
	src.x = (image->w - sprite->Geometry.w) / 2  ;
	src.y = (image->h - sprite->Geometry.h) / 2  ;
	src.w = sprite->Geometry.w ;
	src.h = sprite->Geometry.h ;
	
	dest.x = sprite->Geometry.x ;
	dest.y = sprite->Geometry.y ;
	dest.w = SDL::Screen.w ;
	dest.h = SDL::Screen.h ;
	
	SDL_BlitSurface(image, &src, SDL::ScreenBuffer, &dest);
	
	if (sprite->Rotation > 0)
		SDL_FreeSurface( image ) ;

}

void SDL::Blit	(	SDL_Surface* Src, Sint32 x, Sint32 y )
{
	SDL_Rect src, dest;
	src.x = 0 ;
	src.y = 0 ;
	src.w = Src->w ;
	src.h = Src->h ;
	
	dest.x = x ;
	dest.y = y ;
	dest.w = SDL::Screen.w ;
	dest.h = SDL::Screen.h ;
	
	SDL_BlitSurface(Src, &src, SDL::ScreenBuffer, &dest);
}

void SDL::Blit	(	SDL_Surface* Src, SDL_Surface* Dest, 
						Sint32 SrcX, Sint32 SrcY, 
						Sint32 DestX, Sint32 DestY, 
						Uint32 W, Uint32 H
					)
{
   SDL_Rect src, dest;

   /* Initialize our rectangles */
   src.x = SrcX;
   src.y = SrcY;
   (W) ? src.w = W : src.w = Src->w;
   (H) ? src.h = H : src.h = Src->h;

   dest.x = DestX;
   dest.y = DestY;
   (W) ? dest.w = W : dest.w = Dest->w;
   (H) ? dest.h = H : dest.h = Dest->h;

	SDL_BlitSurface(Src, &src, Dest, &dest);
}

void SDL::Blank(void)
{
	SDL_FillRect( SDL::ScreenBuffer, 0, 0 );
}

void SDL::Flip(void)
{		
	SDL_Flip( SDL::ScreenBuffer );
}

int SDL::GL_TextureSize( int input ) 
{
	int value = 1;
    while (value < input) {
        value <<= 1;
    }
    return value;
}

Uint8* SDL::GL_Texture( SDL_Surface* surface )
{
	Uint8* raw = (Uint8*) malloc( SDL::GL_TextureSize(surface->w) * SDL::GL_TextureSize(surface->h) * 4 );
	Uint8* srcPixel ; 
	Uint8* dstPixel = raw ;
	Uint32 truePixel ;
	int i, j, bpp ;
	
	SDL_LockSurface( surface );
	
	bpp = surface->format->BytesPerPixel;
	
	for ( i = surface->h - 1 ; i >= 0 ; i-- )
	{
		for ( j = 0 ; j < surface->w ; j++ )
		{
			srcPixel = (Uint8 *)surface->pixels + i * surface->pitch + j * bpp;
			
			switch (bpp) {
				case 1:
					truePixel = *srcPixel;
					break;

				case 2:
					truePixel = *(Uint16 *)srcPixel;
					break;

				case 3:
					if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
						truePixel = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
					else
						truePixel = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
					break;

				case 4:
					truePixel = *(Uint32 *)srcPixel;
				break;

				default:
					printf("Image bpp of %d unusable\n", bpp);
					SDL_UnlockSurface( surface );
					free( raw );
					return NULL;
			}
			
			SDL_GetRGBA(	truePixel, surface->format, 
							&(dstPixel[0]), &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3])	);
			dstPixel++;
			dstPixel++;
			dstPixel++;
			dstPixel++;
		}
		
		while ( j < SDL::GL_TextureSize(surface->w) )
		{
			dstPixel++;
			dstPixel++;
			dstPixel++;
			dstPixel++;
			
			j++ ;
		}
	}
	
	SDL_UnlockSurface( surface );
	
	return raw ;
}
