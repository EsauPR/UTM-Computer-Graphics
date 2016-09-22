#pragma once
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
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

using namespace std;

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

//Texto
void drawLetter(char c, int x, int y, int color);
void drawString(string str, int x, int y, int color);
void drawMatriz();

/* Estructuras */
typedef struct nodo{
    
    double mat[3][3];
    
    void reset(){
        memset(mat,0,sizeof(mat));
        mat[0][0] = mat[1][1] = mat[2][2] = 1.0;
    }
    void multiply(double m[3][3])
    {
        double tmp[3][3];
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
            {
                tmp[i][j]=0;
                for(int k=0; k<3; k++)
                    tmp[i][j] += mat[i][k]*m[k][j];
            }
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                mat[i][j] = tmp[i][j];
    }
    void multiply( int &x, int &y)
    {
        double tx = 0.0, ty = 0.0;
        for(int i=0; i<2; i++)
            if(i&1) ty = mat[i][0] * x + mat[i][1] * y + mat[i][2];
            else tx = mat[i][0] * x + mat[i][1] * y + mat[i][2];
        x = (int)tx;
        y = (int)ty;
    }
    void traslation(double tx, double ty)
    {
        double m[3][3];
        memset(m,0,sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = 1;
        m[0][2] = tx;
        m[1][2] = ty;
        multiply(m);
    }
    void rotation(int ang)
    {
        double m[3][3];
        memset(m,0,sizeof(m));
        m[0][0] =  m[1][1] = cos(ang*3.14159/180);
        m[1][0] = sin(ang*3.14159/180);
        m[0][1] = - m[1][0];
        m[2][2] = 1;
        multiply(m);
    }
    void scalement(int sx, int sy)
    {
        double m[3][3];
        memset(m,0,sizeof(m));
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = 1;
        multiply(m);
    }
}Monster;

extern Monster monster;
Monster monster;