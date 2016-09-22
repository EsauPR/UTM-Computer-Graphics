#include "main.h"
//#include "primitivas.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
#define BLANCO 0xffffff

Monster monster;

int mouX=0, mouY = 0,  mouB, mouse = 0;
long double offx = 0.0, offy = 0.0, escala = 100.0;
int mcolR, mcolG, mcolB;
// Prototipos
void idle();
void init();
void checkEvents();

// Poner aquí código para escena

int rot=0;
Poly poly1;
Poly poly2;
Poly poly3;
Poly poly4;

void inipoly()
{
	poly1.clear();
    poly1.setColor(AZUL);
	poly1.insert(-50,-50,-25);
    poly1.insert(-50,50,-25);
    poly1.insert(50,50,-25);
    poly1.insert(50,-50,-25);
    poly1.insert(-50,-50,-25);

    poly2.clear();
    poly2.setColor(AZUL);
    poly2.insert(-50,-50,25);
    poly2.insert(-50,50,25);
    poly2.insert(50,50,25);
    poly2.insert(50,-50,25);
    poly2.insert(-50,-50,25);

 /*
 	Codigo de principal
 	inipoly();

    monster.reset();
    monster.traslation(-0,-0,0);
    monster.rotation(rot,rot,rot);
    
    poly1.setMonster(monster);
    poly2.setMonster(monster);
    
    drawPolygon(poly1);
    drawPolygon(poly2);
    lados();
    //polygonalFill(poly1);
    //polygonalFill(poly2);
    rot += 2;
    rot %= 360;
 */

}

void lados()
{
	for(int i=0; i<poly1.size(); i++)
		drawLine(poly1.X[i], poly1.Y[i], poly2.X[i], poly2.Y[i], AZUL);
}

void principal()
{
    poly1.clear();
    //poly1.setColor(AMARILLO);
    poly1.insert(100,100,0,ROJO);
    poly1.insert(100,400,0,BLANCO);
    poly1.insert(400,400,0,AMARILLO );
    poly1.insert(400,100,0,AZUL );
    poly1.insert(100,100,0,ROJO);

	interpolationColor(poly1);
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

void dib(int n, int color)
{	
	int radio = 300, x = 153, y = 153;
	int x1 ,y1;
    
	poly1.insert(x,y);
	poly1.insert(x + radio, y);
	poly1.insert(x + radio/2 , y + radio * sin(60*3.14159/180));
	poly1.insert(x,y);

	poly1.setColor(color);

	drawFractal( poly1, n , radio/2, color);

	//(color==AMARILLO)?color=AZUL:color=AMARILLO;

	drawsnow(400,n, color);
}

void init()
{

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

