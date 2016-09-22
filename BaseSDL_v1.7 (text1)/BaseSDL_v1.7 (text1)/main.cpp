#include "main.h"
#include "primitivas.cpp"

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
	
	//despMapa();
    drawLetter('A', 300,100, AZUL );
    drawLetter('a', 310,100, AZUL );
    drawLetter('b', 320,100, AZUL );
    drawLetter('2', 330,100, AZUL );
    drawLetter('0', 340,100, AZUL );
    drawLetter('1', 350,100, AZUL );
    drawLetter('9', 360,100, AZUL );
    drawLetter('.', 370,100, AZUL );
    drawLetter('-', 380,100, AZUL );
    drawString("Maggie", 300, 200, AZUL);

    monster.reset();
	//monster.traslation(15.0,15.0);
}

// Entry point
int main(int argc, char *argv[])
{

	initSDL();
	init();     //inicializar valores iniciales
	initText();
	render();   //dibujar
	idle();     //se llamará esta función una y otra vez

	return 0;
}


void init()
{
	; //aquí se inicializarán datos relacionadas con la aplicación
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
			// Barra espaciadora para encender/apagar animación
			if( event.key.keysym.sym == SDLK_SPACE )
				anim = !anim;
			// 'Z' minúscula para encender/apagar zoom
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

