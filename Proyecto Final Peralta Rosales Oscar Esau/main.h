#pragma once
#include <time.h>
#include <stdlib.h>
#include <SDL_ttf.h>
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

using namespace std;

//Tamańo de pantalla
extern int winX, winY;	//tamańo ventana
extern int gLastTick, anim, zoom, table;
extern SDL_Surface *screen;
extern bool PROFUNDIDAD;
extern int ventana;

//Prototipos de PRIMITIVAS
void putpixel(int x, int y, int color);
int getpixel( int x, int y );
void winZoom();
void initText();
void despMapa();

//rellenar regi�n
void fillDFS(int x, int y, int color, int fondo );
void fillBFS(int x, int y, int color, int fondo );

//limpiar pantalla
void clearScreen();

//Texto
void drawLetter(char c, int x, int y, int color);
void drawString(string str, int x, int y, int color);
void drawMatriz();

// Lines
void plot(double x, double y, double c, int color); 
int ipart(double x);
double round(double x);
double fpart(double x);
double rfpart(double x);
void swap(int &x, int &y);
void drawLine(int x0, int y0, int x1, int y1, int color);

//Circulo
//x, y, inicio, radio, color
void drawCircle( int x, int y, int radio, int color  );

//Poligono Regular
void drawRegularPolygon( int x, int y, int radio, int edge,int color );

//Arc
//x, y, inicio, radio, inicio, fin. color
void drawArc( int x, int y, int radio, int ini, int fin, int color );

//espiral
//x, y, radio, inicio, num vueltas, incremento, color
void drawEspiral(int x, int y, int radio, int ini, double numVueltas, int inc, int color);

//Relleno Poligonal
void polygonalFill(int IMAGE_TOP, int IMAGE_BOT, int IMAGE_LEFT, int IMAGE_RIGHT);
void fillpoly();
//Screen Validations

bool isValid(int x1, int y1, int x2, int y2);
bool isValid(int x1, int y1);

//Prototipos inicializacion 
void initSDL();
void render();
void idle();

//Prototipos de MAIN
void principal();
void checkEvents();

/*  ========== Estructuras =========== */

typedef struct nodo{
    
    double mat[4][4];
    
    void reset(){
        memset(mat,0,sizeof(mat));
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3]= 1.0;
    }
    void multiply(double m[4][4])
    {
        double tmp[4][4];
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                tmp[i][j]=0;
                for(int k=0; k<4; k++)
                    tmp[i][j] += mat[i][k]*m[k][j];
            }
            
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                mat[i][j] = tmp[i][j];
    }
    void multiply( int &x, int &y, int &z)
    {
        double tx = 0.0, ty = 0.0, tz = 0.0;
        
        tx = mat[0][0] * x + mat[0][1] * y + mat[0][2] *z + mat[0][3];
        ty = mat[1][0] * x + mat[1][1] * y + mat[1][2] *z + mat[1][3];
        tz = mat[2][0] * x + mat[2][1] * y + mat[2][2] *z + mat[2][3];
        x = (int)tx;
        y = (int)ty;
        z = (int)tz;
    }
    void traslation(double tx, double ty, double tz)
    {
        double m[4][4];
        memset(m,0,sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
        m[0][3] = tx;
        m[1][3] = ty;
        m[2][3] = tz;
        multiply(m);
    }
    void rotation(int angx, int angy, int angz)
    {
        double m[4][4];
        memset(m,0,sizeof(m));
        m[0][0] = m[3][3] = 1;
        m[1][1] =  m[2][2] = cos(angy*3.14159/180);
        m[2][1] = sin(angy*3.14159/180);
        m[1][2] = - m[2][1];
        multiply(m);
        
        memset(m,0,sizeof(m));
        m[2][2] = m[3][3] = 1;
        m[1][1] =  m[0][0] = cos(angz*3.14159/180);
        m[1][0] = sin(angz*3.14159/180);
        m[0][1] = - m[1][0];
        multiply(m);
        
        memset(m,0,sizeof(m));
        m[1][1] = m[3][3] = 1;
        m[0][0] =  m[2][2] = cos(angx*3.14159/180);
        m[0][2] = sin(angx*3.14159/180);
        m[2][0] = - m[0][2];
        multiply(m);
        
    }
    void scalement(double sx, double sy, double sz)
    {
        double m[4][4];
        memset(m,0,sizeof(m));
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = sz;
        m[3][3] = 1;
        multiply(m);
    }
}Monster;

extern Monster monster;

typedef struct fig
{
	vector<int> X;
	vector<int> Y;
	vector<int> Z;
	vector<int> pointColor;
	int Color;
	Monster monster;
    bool perspective;

    void insert(int x, int y, int z, int color)
    {
        X.push_back(x);
        Y.push_back(y);
        Z.push_back(z);
        pointColor.push_back(color);
    }
	void insert(int x, int y, int z)
	{
		X.push_back(x);
		Y.push_back(y);
        Z.push_back(z);
	}
	void insert(int x, int y)
	{
		X.push_back(x);
		Y.push_back(y);
        Z.push_back(0);
	}
	void setColor(int color)
	{
		Color = color;
	}
	void clear()
	{
		X.clear();
		Y.clear();
        Z.clear();
		pointColor.clear();
        perspective = false;
	}
	int size()
	{
		return (int) X.size();
	}
	int maxY()
	{
        vector<int> tmp = Y;
        sort(tmp.begin(), tmp.end());
        return tmp[tmp.size()-1];
    }
    int minY()
    {
        vector<int> tmp = Y;
        sort(tmp.begin(), tmp.end());
        return tmp[0];
    }
    void perspectiva()
    {
        int Zprp = 200, Zvp = 5;
        int dp = Zprp - Zvp;
        int xprp=200, yprp=200;
        double tx,ty,tz,h;
        for(int i = 0; i < size(); i++)
        {
            tx = X[i];
            ty = Y[i];
            tz = (double)Z[i] * -1 * (double)Zvp / dp - (double)Zvp * (double)Zprp / dp;
            h = ((double)Z[i] * -1 - (double)Zprp) / dp;
            X[i] = xprp + (int)tx/h;
            Y[i] = yprp + (int)ty/h;
        }
    }
    void setMonster()
    {
    	for( int i = 0; i < size(); i++)
    		monster.multiply( X[i], Y[i], Z[i]);
        if( perspective )
            perspectiva();
    }
    void setMonster(Monster monster)
    {
        for(int i=0; i<size(); i++)
            monster.multiply( X[i], Y[i], Z[i] );
        if( perspective )
            perspectiva();
    }
    void perspectiveEnable( bool per )
    {
        perspective = per;
    }
}Poly;


//Relleno Poligonal
void polygonalFill( Poly poly );
void interpolationColor(Poly poly);
void drawPolygon( Poly poly );
void drawPolygon( Poly Poly, string mode ); /* wire - fill - interpolate */


//DrawFractal
void drawFractal( Poly poly, int n, int radio, int color);

//copo de nieve
void drawsnow(int tam, int n, int color);

double distancia(int x1, int y1, int x2, int y2);
void resetProfundidad();