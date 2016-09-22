//#include "main.h"
#include "primitivas.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000

Monster monster;

int mouX=0, mouY=0,  mouB, mouse=0;
long double offx=0.0, offy=0.0, escala=100.0;
int mcolR, mcolG, mcolB;
// Prototipos
void idle();
void init();
void checkEvents();

// Poner aquí código para escena

int rot=0;
int tras=0, tras2=0;
int inc=1;
int i=0;

Poly poly1;
Poly poly2;
Poly poly3;
Poly poly4;
Poly n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13,n14,n15,n16;
Monster mon, mon1;

int v[3]={AMARILLO,AZUL,ROJO};

void inipoly()
{
    i++;
    poly1.clear();
    poly2.clear();
    poly3.clear();
    poly4.clear();
    n1.clear(); n2.clear(); n3.clear(); n4.clear();
    n5.clear(); n6.clear(); n7.clear(); n8.clear();
    n9.clear(); n10.clear(); n11.clear(); n12.clear();
    n13.clear();

    n13.setColor(AZUL + AMARILLO);
    n13.insert( 0 - winX, 0 - 200,0);
    n13.insert( 0 - winX, 200,0);
    n13.insert( winX, 200,0);
    n13.insert( winX, 0 - 200,0);
    n13.insert( 0 -winX, 0 - 200,0);


    poly1.setColor(v[i%3]);
    poly1.insert(0,0,0);
    poly1.insert(200,0,0);
    poly1.insert(100,150,86);
    poly1.insert(0,0,0);

	poly2.setColor(v[i%3]);
    poly2.insert(0,0,0);
    poly2.insert(100,0,173);
    poly2.insert(100,150,86);
    poly2.insert(0,0,0);

    poly3.setColor(v[i%3]);
    poly3.insert(100,0,173);
    poly3.insert(200,0,0);
    poly3.insert(100,150,86);
    poly3.insert(100,0,173);

    poly4.setColor(v[i%3]);
    poly4.insert(0,0,0);
    poly4.insert(200,0,0);
    poly4.insert(100,0,173);
    poly4.insert(0,0,0);

    poly1.setColor(AMARILLO);
    poly2.setColor(AMARILLO);
    poly3.setColor(AMARILLO);
    poly4.setColor(AMARILLO);

    n1.setColor(AZUL); n2.setColor(AZUL); n3.setColor(AZUL); n4.setColor(AZUL);
    n5.setColor(AZUL); n6.setColor(AZUL); n7.setColor(AZUL); n8.setColor(AZUL);
    n9.setColor(AZUL); n10.setColor(AZUL); n11.setColor(AZUL); n12.setColor(AZUL);
    //n13.setColor(AZUL); n14.setColor(AZUL); n15.setColor(AZUL); n16.setColor(AZUL);

    n1.insert(0,3,0);   n1.insert(6,3,0);   n1.insert(7,6,3); n1.insert(0,3,0);
    n2.insert(0,3,0);   n2.insert(7,0,3);   n2.insert(6,3,0); n2.insert(0,3,0);
    n3.insert(6,3,0);   n3.insert(7,0,3);   n3.insert(9,3,3); n3.insert(6,3,0);
    n4.insert(6,3,0);   n4.insert(9,3,3);   n4.insert(7,6,3); n4.insert(6,3,0);

    n5.insert(0,3,0);   n5.insert(6,3,4);   n5.insert(7,6,3); n5.insert(0,3,0);
    n6.insert(0,3,0);   n6.insert(7,0,3);   n6.insert(6,3,4); n6.insert(0,3,0);
    n7.insert(6,3,4);   n7.insert(7,0,3);   n7.insert(9,3,3); n7.insert(6,3,0);
    n8.insert(6,3,4);   n8.insert(9,3,3);   n8.insert(7,6,3); n8.insert(6,3,0);

    n9.insert(3,6,3);     n9.insert(7,6,3);    n9.insert(12,10,8);  n9.insert(7,8,2);  n9.insert(3,6,3);
    n10.insert(3,6,3);   n10.insert(7,6,3);   n10.insert(12,10,8); n10.insert(7,8,4);  n10.insert(3,6,3);
    n11.insert(3,0,3);   n11.insert(7,0,3);   n11.insert(12,-4,8); n11.insert(7,-2,2); n11.insert(3,0,3);
    n12.insert(3,0,3);   n12.insert(7,0,3);   n12.insert(12,-4,8); n12.insert(7,-2,4); n12.insert(3,0,3);


}

bool band=false;
int rot2=0, lastTras, tras1=0, inc2=1;
void principal()
{
	
    rot = (rot+2) % 360;
    SDL_Rect cuadro;
    cuadro.x = 0;  cuadro.y = winY - 200;  cuadro.w = winX;   cuadro.h = 500;
    SDL_FillRect( screen, &cuadro, SDL_MapRGB(screen->format, 50, 50, 50 ) );

    if( tras > 50 ) inc *= -1;
    if( tras < 0   ) inc *= -1;
    tras += inc;

    /*
    inipoly();
    monster.reset();
    monster.traslation(200.0 + tras, 200.0 + tras, 0.0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);
    //*/
    inipoly();
    monster.reset();
    monster.scalement(0.5,0.5,0.5);
    monster.traslation(400.0 + tras, 400.0 + tras, 0.0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);
    
    inipoly();
    monster.traslation(450 + tras ,0,0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);

    inipoly();
    monster.reset();
    monster.scalement(0.5,0.5,0.5);
    monster.traslation(600.0 + tras, 400.0 + tras, 0.0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);
    
    inipoly();
    monster.traslation(450 + tras,0,0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);

    inipoly();
    monster.reset();
    monster.scalement(0.5,0.5,0.5);
    monster.traslation(500.0 + tras, 550.0 + tras, 0.0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);
    
    inipoly();
    monster.traslation(450 + tras ,0,0);
    monster.rotation( rot , rot , 0 );
    poly1.setMonster(monster);  drawPolygon(poly1);
    poly2.setMonster(monster);  drawPolygon(poly2);
    poly3.setMonster(monster);  drawPolygon(poly3);
    poly4.setMonster(monster);  drawPolygon(poly4);

    /*
    mon.reset();
    mon.scalement(10,10,10);
    mon.rotation( 180 , 0 , 0);
    tras1 += inc2;
    if(tras1 == 53 || tras1 == 0)
    {
        band = true;
        lastTras = -6 -tras1;
    }
    
    if(band)
    {
        mon.traslation(lastTras , 7 , 0);
        rot2 += 2;
        tras1 -= inc2;
    }
    else
        mon.traslation(-6 -tras1 , 7  , 0);

    int lastRot = 0;
    if( ( rot2 == 180 && tras1 == 52) || rot2 == 360) 
    {
        band=false;
        rot2 = rot2 % 360;
        inc2 *= -1;
        //tras1 = tras1 - 1;
    }
    

    mon.rotation( rot2 , -rot  , 0);
    n1.setMonster(mon); drawPolygon(n1);
    n2.setMonster(mon); drawPolygon(n2);
    n3.setMonster(mon); drawPolygon(n3);
    n4.setMonster(mon); drawPolygon(n4);
    //*
    n5.setMonster(mon); drawPolygon(n5);
    n6.setMonster(mon); drawPolygon(n6);
    n7.setMonster(mon); drawPolygon(n7);
    n8.setMonster(mon); drawPolygon(n8);
    n9.setMonster(mon); drawPolygon(n9);
    n10.setMonster(mon); drawPolygon(n10);
    n11.setMonster(mon); drawPolygon(n11);
    n12.setMonster(mon); drawPolygon(n12);
    //*/


    mon1.reset();
    mon1.traslation(0,0,0);
    mon1.rotation(0,rot,0);
    n13.setMonster(mon1); drawPolygon(n13);
    for(int i=1; i<=0 ; i++)
    {
        inipoly();
        mon1.rotation(0,rot + 10*i,0);
        n13.setMonster(mon1); drawPolygon(n13);
    }

    printf("%d %d\n",tras1, rot2 );
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

