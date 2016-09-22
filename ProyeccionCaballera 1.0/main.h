#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER)
 #include <SDL.h>
#else
 #include <SDL/SDL.h>
#endif

#include <math.h>
//Para winZoom
#define	ZWX	200
#define ZWY	200
#define ZWP	10

// Physics iterations per second
#define PHYSICSFPS 30
using namespace std;
//Tamaño de pantalla

extern int winX, winY;	//tamaño ventana
extern int gLastTick, anim, zoom;
extern SDL_Surface *screen;
extern int mouX, mouY, mouse,Boton;
extern int dmouX,dmouY;
extern float Matriz[4][4];
//variables
struct Punto
{
  int x,y;     
};

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
void despletra(int i,int j,char c);
void despalabra(int x,int y,char c[]);
void kernin(int x,int y,char c[]);
void calculamin(int i,int j,char c);
void Negrita(int x,int y,char s[]);
void Kursiva(int x,int y,char s[]);
void kerninMatriz(int x,int y,char c[]);
void despletraMatriz(int i,int j,char c);

//Prototipos de Matrix
void identidad();
void muestraMatriz(int x,int y);
void multiplica(float m[4][4]);
void traslada(float tx,float ty,float tz);
void escala(float sx,float sy,float sz);
void rota(float t,char c);
void aplicaMatriz(int *x,int *y,int *z);

//Prototipos de Lineas
void breseColor(int x0,int y0,int x1,int y1,Uint32 c);
void brese(int x0,int y0,int x1,int y1);
void linea(int x1,int y1,int x2,int y2,Uint32 c);
void pintaPoligono(int vX[],int vY[],int numP,Uint32 color);
void dibujaFigura(Punto f[],int p);
void pintaPoligono3D(int vX[],int vY[],int vZ[],int numP,Uint32 color);
void pinta3D(int vX[],int vY[],int Z,int numP,Uint32 color);
//Prototipos de MAIN
void principal();
void checkEvents();
