#pragma once
#include "main.h"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000

SDL_Surface *screen;
int winX=640, winY=480;
int gLastTick;
int anim=0;
int zoom=0;
int table=0;
//int mouX=0, mouY=0, mouse=0;

void putpixel(int x, int y, int color)
{
    if(!isValid(x,y)) return;
	unsigned int *ptr = (unsigned int*)screen->pixels;
	int lineoffset = (winY-1-y) * (screen->pitch / 4);
	ptr[lineoffset + x] = color;
}

int getpixel( int x, int y )
{
	unsigned int *ptr = (unsigned int*)screen->pixels;
	int lineoffset = (winY-1-y) * (screen->pitch / 4);
	//int lineoffset = y * (screen->pitch / 4);
	//return( 0 );
	return( ptr[lineoffset + x] );
}

void winZoom()
{
	SDL_Rect cuadro;
	int orX, orY, x, y, color;
	orX=winX-ZWX; orY=0;

	cuadro.x=orX; cuadro.y=orY; cuadro.w=ZWX; cuadro.h=ZWY;
	SDL_FillRect( screen, &cuadro, SDL_MapRGB(screen->format, 50, 50, 50 ) );

	cuadro.w=ZWP-1; cuadro.h=ZWP-1;	//ancho y alto de pixelotes
	for( y=0; y<20; y++)
		for( x=0; x<20; x++ )
		{
			color=getpixel( x, y );
			cuadro.x = orX + x*ZWP; cuadro.y = orY + (20-y-1)*ZWP;
			SDL_FillRect( screen, &cuadro, color );
		}
}

//Funciones asociadas a la estructura SDL
void initSDL()
{
	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);

	// Attempt to create a 640x480 window with 32bit pixels.
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_RESIZABLE );

	// If we fail, return error.
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		exit(1);
	}

	gLastTick = SDL_GetTicks();	
}

void render()
{
	int x,y, yofs, ofs;
	// Lock surface if needed
	if (SDL_MUSTLOCK(screen)) 
		if (SDL_LockSurface(screen) < 0) 
			return;
	//borrar pantalla
	//*
	yofs=0;
	
	for (y = 0; y < winY; y++)
	{
		for (x = 0, ofs = yofs; x < winX; x++, ofs++)
		{
			((unsigned int*)screen->pixels)[ofs] = 0;
		}
		yofs += screen->pitch / 4;
	}
    //*/
	//llamar a despliegue de usuario
	principal();
	//activar zoom si está activado (con 'z')
	if( zoom )
	{
		winZoom();
	}
    if( table )
	{
    	drawMatriz();
	}
	// Unlock if needed
	if (SDL_MUSTLOCK(screen)) 
		SDL_UnlockSurface(screen);

	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, winX, winY);    
}
void idle()
{
	// Ask SDL for the time in milliseconds
	int tick;

	// Main loop: loop forever.
	while (1)
	{
		if( anim )
		{

			tick = SDL_GetTicks();
			if (tick <= gLastTick) 
			{
				SDL_Delay(1);
				continue;
			}

			// Render stuff
			render();
			gLastTick += 1000 / PHYSICSFPS;
		} else
			SDL_Delay(100);

		checkEvents();
	}
}

void clearScreen()
{

	for (int y = 0, yofs=0; y < winY; y++)
	{
		for (int x = 0, ofs = yofs; x < winX; x++, ofs++)
		{
			((unsigned int*)screen->pixels)[ofs] = 0;
		}
		yofs += screen->pitch / 4;
	}

}

