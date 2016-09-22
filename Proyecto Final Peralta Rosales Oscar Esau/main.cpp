//#include "main.h"
#include "pantallas.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
#define BLANCO 0xffffff


Monster monster;

int mouX=0, mouY = 0,  mouB, mouse = 0;
long double offx = 0.0, offy = 0.0, escala = 100.0;
int mcolR, mcolG, mcolB;
bool PROFUNDIDAD = false;
// Prototipos
void idle();
void init();
void checkEvents();

// Poner aquí código para escena

void principal()
{
	resetProfundidad();
	carcasa();
	botones();
	loadVentana();
	
	if( mouse )
	{
		int accion = checkButtom( mouX, mouY );
		//printf("Clic en -> %d\n", accion );
		eventos( accion );
		mouse = 0;
	}
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
	anim = 1;
	fontInit();
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
            {
				anim = !anim;
                if( anim )
                    gLastTick = SDL_GetTicks();
            }
			// 'Z' minúscula para encender/apagar zoom
			if( event.key.keysym.sym == SDLK_z )
			{
				zoom = !zoom;
				render();
			}
            if( event.key.keysym.sym == SDLK_t )
			{
				table = !table;
				render();
			}
			break;
		case SDL_VIDEORESIZE:
			winX=event.resize.w; winY=event.resize.h;
			screen = SDL_SetVideoMode(winX, winY, 32, SDL_SWSURFACE | SDL_RESIZABLE );
			render();
			break;
			
	   case SDL_MOUSEBUTTONDOWN:
            mouX= event.button.x;
            mouY=winY-event.button.y;
            mouse=1;
            mouB=(event.button.button==SDL_BUTTON_LEFT)? 0 : 1;
            render();	
            break;	
		case SDL_QUIT:
			exit(0);
		}
	}
}
