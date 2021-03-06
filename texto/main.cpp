//#include "main.h"
#include "primitivas.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
//Para ventana auxiliar
//SDL_Surface *auxiliar;

// Prototipos
void idle();
void init();
void checkEvents();

void principal()
{

	putpixel( 5, 5, 0xff0000 );
	
	if( mouse )
	{
		putpixel( mouX, mouY, 0xff0000 );
		mouse=0;
	}
	
	despMapa();
    drawLetter('A', 300,100, AZUL );
    drawLetter('a', 310,100, AZUL );
    drawLetter('b', 320,100, AZUL );
    drawLetter('B', 330,100, AZUL );
    drawLetter('o', 340,100, AZUL );
    drawLetter('O', 350,100, AZUL );
}

// Entry point
int main(int argc, char *argv[])
{

	initSDL();
	init();     //inicializar valores iniciales
	initText();
	render();   //dibujar
	idle();     //se llamar� esta funci�n una y otra vez

	return 0;
}


void init()
{
	; //aqu� se inicializar�n datos relacionadas con la aplicaci�n
}

void checkEvents()
{
	// Poll for events, and handle the ones we care about.
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			// If escape is pressed, return (and thus, quit)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit( 0 );
			// Barra espaciadora para encender/apagar animaci�n
			if( event.key.keysym.sym == SDLK_SPACE )
				anim = !anim;
			// 'Z' min�scula para encender/apagar zoom
			if( event.key.keysym.sym == SDLK_z )
			{
				zoom = !zoom;
				render();
			}
			break;
		case SDL_VIDEORESIZE:
			winX=event.resize.w; winY=event.resize.h;
			screen = SDL_SetVideoMode(winX, winY, 32, SDL_SWSURFACE | SDL_RESIZABLE );
			render();
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouX = event.button.x;
			mouY = winY - event.button.y;
			mouse = 1;
			//printf( "x: %d, y: %d\n", event.button.x, event.button.y );
			render();
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

