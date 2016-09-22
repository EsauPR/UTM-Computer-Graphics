#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER)
 #include <SDL.h>
#else
 #include <SDL/SDL.h>
#endif

//Para winZoom
#define	ZWX	200
#define ZWY	200
#define ZWP	10

// Physics iterations per second
#define PHYSICSFPS 30

//Tamaño de pantalla
extern int winX, winY;	//tamaño ventana
extern int gLastTick, anim, zoom;
extern SDL_Surface *screen;
extern int mouX, mouY, mouse;

//Prototipos de SDL
void putpixel(int x, int y, int color);
int getpixel( int x, int y );
void winZoom();

void initSDL();
void render();
void idle();

//Prototipos de PRIMITIVAS
void initText();
void despMapa();

//Prototipos de MAIN
void principal();
void checkEvents();

void drawLetter(char c, int x, int y, int color);
