#include "main.h"
#include "sdlElements.cpp"
#define TAM 200

int mouX=0, mouY=0,  mouB, mouse=0;
long double offx=0.0, offy=0.0, escala=100.0;
int mcolR, mcolG, mcolB;
// Prototipos
void idle();
void init();
void checkEvents();
int color[] = {0x00ff00,0x00ffff,0xffff00,0xff00ff};
int matcolor[640][480];

int c1,c2,rt;

int mandelbrod(double x, double y)
{
    double zx = 0.0, zy = 0.0, nzx, nzy;
    
    for(int t=0; t<50; t++)
    {
        nzx = zx*zx - zy*zy;
        nzy = 2.0*zx*zy;
        zx = nzx + x;
        zy = nzy + y;
        
        //*
        
        nzx = zx*zx - zy*zy;
        nzy = 2.0*zx*zy;
        zx = nzx + x;
        zy = nzy + y;
        
        //*/
        c1 = (int)zx; 
        c2 = (int)zy;
        rt = t;
        if(zx*zx + zy*zy > 10.0) 
                 return t;
    }
    c1 = (int)zx; 
    c2 = (int)zy;
    return 0;
}

// Poner aquí código para escena
void principal()
{
	
	if(mouse)
    {
		 offx=(long double) (mouX-winX/2)/ escala+offx;
		 offy=(long double) (mouY-winY/2)/ escala+offy;
		 
		 if( !mouB)
		     escala*=2.0;
		 else
		     escala*=0.25;
		 mouse = 0;  
    }
	int t, color;
    for( int x=0; x<640; x++ )
    	for(int y=0; y<480; y++)
    	 	if(  t = mandelbrod( -2.3 + (double)x/200.0, -1.2 + (double)y/200.0) )
    	 	{
		        color = t*20 + t*256*20 ;//+ t*65536*20;
		        color = c1*20 + 256*c2*20 + c2*c1*65536;
		    //    matcolor[x][y] = color;
		  		//putpixel( x, y, matcolor[x][y]+=20 );
				putpixel( x, y, color );
    	    }

}


// Entry point
int main(int argc, char *argv[])
{

	initSDL();
	init();     //inicializar valores iniciales
	render();   //dibujar
	idle();     //se llamará esta función una y otra vez

	return 0;
}


void init()
{
	; //aquí se inicializarán datos relacionadas con la aplicación
/*
	int color , t;
    int c2 = 0xffff0f, co2 = 0xfffff0;
	for( int x=0; x<640; x++ )
	     for(int y=0; y<480; y++)
         	if( t = mandelbrod( -2.0 + (double)x/250.0, - 0.96 + (double)y/250.0) )
         	{
                //color = t*20 + t*256*20 ;//+ t*65536*20;
               // if(!c2 && !c1 )
                      color = c1*20 + 256*c2*20 + c2*c1*65536;
                //else  color = c1*20 + 256*c2*20;
                matcolor[x][y] = color;
          	//	putpixel( x, y, color );
            }
            else matcolor[x][y] = 0xffffff;
*/
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

