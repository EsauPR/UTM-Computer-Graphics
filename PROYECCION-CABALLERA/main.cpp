#include "main.h"
#include <math.h>

//==================== Prototipos ===================
int L1=10;
void idle();
void init();
void checkEvents();
void dubujaLetra(int x, int y, char c  );
void dibujaPalabra(int x,int y,char *string);
int vecX[10],vecY[10],puntos;
//============== PROTOTIPOS DE MATRIZ ===============

void muestraMatriz(int x, int y );
void matrizIdentidad();
void multiplicaMatriz(float matriz[][3]);
void traslacion(int tx, int ty,int tz);
void rotacionZ(float angulo);
void rotacionX(float angulo);
void rotacionY(float angulo);
void escalamiento(float sx, float sy,float sz);
void Bresenham( int x0, int y0, int x1, int y1 );
void RellenoPoligonal(int X[],int Y[],int verices,int color);
void dibujaCasa();
void dibujaCasa3D();
void dibujaTriangulo();
void dibujaTriangulo2();
void dibujaTriangulo3D();
void dibujaTetraedro();
void dibujaEstrella();
void dibujaCasa3D2();
void dibujaCubo();
void rectangulo();
void cuadro();

struct punto{
       int x;
       int y;
       };
       
void DibujarFractal(punto , punto , punto , int );
punto Mitad(punto P1, punto P2);
//============VARIABLES PARA ANIMACION===============

int AnimaX=0;
int AnimaY=0;
float decre=15.0;

//======================FRACTAL=======================
punto Mitad(punto P1, punto P2){
   punto R;
   
   R.x= (P1.x+P2.x)/2;
   R.y= (P1.y+P2.y)/2;
   return R;
}
void DibujarFractal(punto A, punto B, punto C, int iteraciones){
     punto AB,BC,CA;
     
     if(iteraciones==0){
        vecX[0]=A.x;
        vecY[0]=A.y;
        vecX[1]=B.x;
        vecY[1]=B.y;
        vecX[2]=C.x;
        vecY[2]=C.y;
        RellenoPoligonal(vecX,vecY,3,0xffffff);
        return ;                    
     }
     else{
         AB=Mitad(A,B);
         BC=Mitad(B,C);
         CA=Mitad(C,A);
          DibujarFractal(A, AB,  CA, iteraciones-1);
          DibujarFractal( AB,  B,  BC,  iteraciones-1);
          DibujarFractal( CA,  BC,  C,  iteraciones-1);
          return ;
     }
  }
void principal()
{

    matrizIdentidad();
    //traslacion(5,100,0);
    //escalamiento(0.8,0.8,0.8);
    //rotacionX(decre);
    traslacion(200,150,0);
    //rotacionY(90.0);
     //cuadro();
    //escalamiento(0.5,0.4,0.8);
    
    
    rotacionX(decre);
    rotacionY(decre);
    dibujaCubo();
    rotacionZ(decre);
    
    
    
    //escalamiento(0.5,0.4,0.8);
    //traslacion(5,5,5);
    //dibujaTriangulo();
   //dibujaCasa3D2();
     //matrizIdentidad();
     //dibujaTetraedro();
    //traslacion(50,0,0);
    //dibujaTriangulo2();
   //dibujaCasa3D();
    //traslacion(100,0,0);
    //dibujaCasa();
    //cuadro();
    muestraMatriz(390,400);

    	
   	 dibujaCasa3D2();
    

	AnimaX+=2;
	AnimaY+=1;
	decre+=0.9;
}

//================Cuerpo Principal del programa====================

int main(int argc, char *argv[])
{

	initSDL();
	init();     //inicializar valores iniciales
	initText();
	//render();   //dibujar
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
			if( event.key.keysym.sym == SDLK_SPACE ){
				anim = !anim;
				
			}
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

