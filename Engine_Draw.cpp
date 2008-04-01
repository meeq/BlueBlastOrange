#include "Engine_Draw.h"

using namespace std;

Draw::Sprite::Sprite(  )
{
	this->Reset() ;
}

Draw::Sprite::Sprite( Sprite* sprite )
{
	this->Reset() ;

	this->Filename = sprite->Filename ;
	this->Surface = sprite->Surface ;
	//if ( sprite->Anim != NULL )
	//	this->Anim = new SDL_Anim( sprite->Anim ) ;
	this->Texture = sprite->Texture ;
	this->Geometry = sprite->Geometry ;
	this->Layer = sprite->Layer ;
}

Draw::Sprite::Sprite( char* filename )
{
	this->Reset() ;
	this->Load( filename ) ;
}

Draw::Sprite::Sprite( SDL_Surface* surface )
{
	this->Reset() ;
	this->Load( surface ) ;
}
/*
Draw::Sprite::Sprite( SDL_Anim* anim )
{
	this->Reset() ;
	this->Load( anim ) ;
}
*/
Draw::Sprite::Sprite( GLuint &texture )
{
	this->Reset() ;
	if (SDL::OpenGL)
		this->Texture = texture ;
}

Draw::Sprite::~Sprite(  )
{
	this->Clear() ;
}

void Draw::Sprite::Load( char* filename )
{
	this->Filename = filename ;
	SDL_Surface* image = SDL::LoadImage( this->Filename );
	this->Load( image ) ;
}

void Draw::Sprite::Load( SDL_Surface* surface )
{
	this->Surface = surface ;
	
	this->Geometry.x = 0 ;
	this->Geometry.y = 0 ;
	this->Geometry.w = this->Surface->w ;
	this->Geometry.h = this->Surface->h ;
	
	MakeGLTexture() ;
}
/*
void Draw::Sprite::Load( SDL_Anim* anim )
{
	this->Surface = anim->GetFrame(0) ;
	
	this->Geometry.x = 0 ;
	this->Geometry.y = 0 ;
	this->Geometry.w = this->Surface->w ;
	this->Geometry.h = this->Surface->h ;
	
	this->Anim = new SDL_Anim( anim ) ;
	
	MakeGLTexture() ;
}
*/

void Draw::Sprite::Reload()
{
	this->Clear() ;
	this->Load( this->Filename ) ;
}

void Draw::Sprite::MakeGLTexture()
{
	if (!SDL::OpenGL)
		return ;
		
	if ( this->Surface->format->BytesPerPixel < 2 ) {
		printf("How the hell is this not True-Color!?\n");
		return;
	}
	
	int w = SDL::GL_TextureSize(this->Surface->w) ;
	int h = SDL::GL_TextureSize(this->Surface->h) ;
	
	Uint8* image = SDL::GL_Texture( this->Surface ) ;

	glDeleteTextures( 1, &(this->Texture) );
	
	glGenTextures( 1, &(this->Texture) );
 
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, this->Texture );
 
	// Edit the texture object's image data using the information SDL_Surface gives us
	//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, (Uint8*) image ) ;
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image  );
	
	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	free (image);
}

void Draw::Sprite::Update()
{
	SDL_Surface* original_surface = this->Surface ;
	//if ( this->Anim != NULL ) 
	//	this->Surface = this->Anim->Play();
		
	if ( this->Surface != original_surface ) {
		this->Geometry.w = this->Surface->w ;
		this->Geometry.h = this->Surface->h ;
		this->MakeGLTexture() ;
	}
}

void Draw::Sprite::Clear()
{
	if (SDL::OpenGL)
		glDeleteTextures( 1, &this->Texture );
	if (this->Surface != NULL )
		SDL_FreeSurface(this->Surface) ;
	//if (this->Anim != NULL)
	//	delete this->Anim ;
		
	this->Reset();
}

void Draw::Sprite::Reset()
{
	this->Geometry.x = 0 ;
	this->Geometry.y = 0 ;
	this->Geometry.w = 0 ;
	this->Geometry.h = 0 ;
	
	this->Layer = 0 ;
	this->Rotation = 0 ;
	
	this->Surface = NULL ;
	//this->Anim = NULL ;
	this->Texture = 0 ;
}

void Draw::Blank( void )
{
	if (SDL::OpenGL) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
	} else
		SDL::Blank() ;
}

void Draw::Flip( void )
{
	if (SDL::Area.x != 0) {
		SDL_Surface* letterbox = SDL_CreateRGBSurface(	SDL_SWSURFACE, 
														SDL::Area.x, 
														SDL::Screen.h , 
														32, 0, 0, 0, 0 ) ;
		Draw::Screen( letterbox , 0, 0 ) ;
		Draw::Screen( letterbox , SDL::Area.x + SDL::Area.w + (SDL::Scale * 3), 0 ) ;
		SDL_FreeSurface( letterbox ) ;
	} else {
		SDL_Surface* letterbox = SDL_CreateRGBSurface(	SDL_SWSURFACE, 
														SDL::Screen.w, 
														SDL::Area.y , 
														32, 0, 0, 0, 0 ) ;
		Draw::Screen( letterbox, 0, 0 ) ;
		Draw::Screen( letterbox, 0, SDL::Area.y + SDL::Area.h + (SDL::Scale * 3) ) ;
		SDL_FreeSurface( letterbox ) ;
	}

	if (SDL::OpenGL)
		SDL_GL_SwapBuffers( );
	else
		SDL::Flip() ;
		
	if( Video::CAP_FPS )		
		if( SDL::FPS.get_ticks() < 1000 / Video::FRAMES_PER_SECOND ) { 
			SDL_Delay( (1000 / Video::FRAMES_PER_SECOND) - SDL::FPS.get_ticks() );
		}
	SDL::FPS.start();
}


void Draw::Screen( SDL_Surface* src, int x, int y )
{
	SDL::Blit( src, x, y ) ;
}

void Draw::Screen( Sprite* sprite )
{
	if (SDL::OpenGL) {
		GLfloat w = (GLfloat)(sprite->Geometry.w) / 2.0 ;
		GLfloat h = (GLfloat)(sprite->Geometry.h) / 2.0 ;
		GLfloat x = (GLfloat)(sprite->Geometry.x) + w ;
		GLfloat y = (GLfloat)(sprite->Geometry.y) + h ;
		float width = (float) sprite->Surface->w / (float) SDL::GL_TextureSize(sprite->Surface->w) ;
		float height = (float) sprite->Surface->h / (float) SDL::GL_TextureSize(sprite->Surface->h) ;
		glLoadIdentity();					// Reset The Current Modelview Matrix
		glTranslatef( x, y, (GLfloat)(sprite->Layer) );
		glRotatef( sprite->Rotation, 0.0f, 0.0f, 1.0f ) ;
		glBindTexture(GL_TEXTURE_2D, sprite->Texture);
		// Draw A Quad
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 0 ); // Bottom-left Corner
			glVertex3f( -1.0 * w, 
						h, 
						0.0f);
			glTexCoord2f( width, 0 ); // Bottom-right corner
			glVertex3f( w, 
						h, 
						0.0f);	
			glTexCoord2f( width, height ); // top-right corner
			glVertex3f( w, 
						-1.0 * h, 
						0.0f);
			glTexCoord2f( 0, height ); // Top-left Corner
			glVertex3f( -1.0 * w, 
						-1.0 * h,
						0.0f);
		glEnd();
	} else
		SDL::Blit( sprite ) ;
}

void Draw::Text( char* message, TTF_Font* font, int x, int y, bool centered )
{
	Draw::Sprite* text;
	text = new Draw::Sprite( TTF_RenderText_Blended( font, message, SDL_Colors::White ) );
	text->Geometry.x = SDL::Area.x + x ;
	text->Geometry.y = SDL::Area.y + y ;
	if (centered) {
		text->Geometry.x -= text->Surface->w / 2 ;
		text->Geometry.y -= text->Surface->h / 2 ;
	}
	text->Layer = TEXT_LAYER ;
	Draw::Screen( text );
	delete text ;
}

