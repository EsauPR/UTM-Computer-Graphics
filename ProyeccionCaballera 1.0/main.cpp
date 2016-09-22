//#include "main.h"
#include "Matrix.cpp"

void idle();
void init();
void checkEvents();
void console(int x,int y);
Uint32 ColorG;
void dibuja3D(int vX[],int vY[],int Z,int numP,Uint32 color);
//void RellenoPoligonal(int X[],int Y[],int vertices,int color);
void fractal(int n1, double x1_1, double x2_1, double x3_1, double y1_1, double y2_1, double y3_1);
int circle=0;
 int vecX[10],vecY[10];
int fig1x[5],fig1y[5],fig1z[5];
int fig2x[5],fig2y[5],fig2z[5];
int X[10],Y[10],Z[10];
int superX,superY;
int anima=0;
void caballera(int L,float th);




void pintaCasa(int x,int y,int np,int z)
{
	//ColorG= SDL_MapRGB(screen->format, 43+anima,43+anima,43+anima);
    
	  fig1x[0]=x;       fig1y[0]=y;
    fig1x[1]=x+100;   fig1y[1]=y;
    fig1x[2]=x+100;   fig1y[2]=y+100;
    fig1x[3]=x+50;    fig1y[3]=y+150;
    fig1x[4]=x;       fig1y[4]=y+100;
                    
	  dibuja3D(fig1x,fig1y,0,np,0xffffff);
	
	
}



void principal()
{	
	
	identidad();
	
	pintaCasa(70,100,5,0);
	caballera(2,90);
	pintaCasa(400,100,5,0);
	//console(0,400);
	
	
	/*if(Boton==1)
	{
        rota(dmouX,'y');
        rota(dmouY,'x');   
    }
       // for(int j=0;j<5;j++)
	//for(int i=0;i<5;i++)
    //pintaCasa(0+i*110,0,60*j);
	//traslada(100,100,20);
	//rota(360.0,'x');
	
    //escala(0.5,0.4,0.8);
//	traslada(5,5,5);
    int color=0x5F3E0B;
	//pintaCasa(250,0,0);
	int x1,x2,x3,y1,y2,y3;
    
    int base=winX/7;
    //  int vecX[10],vecY[10];
    x1=(winX/2)-(base/2);
    x2=(winX/2)+(base/2);
    x3=(winX/2);
    y1=(winY-(winY/15))-(base);
    y2=(winY-(winY/15));
    y3=(winY-(winY/15))-(base+(base/2));
     vecX[0]=x1;
                vecY[0]=y1;
    vecX[1]=x1;
               vecY[1]=y2;
    vecX[2]=x2;
                vecY[2]=y2;
    vecX[3]=x2;
                vecY[3]=y1;
    vecX[4]=x1;
                vecY[4]=y1;
                //rota(360,'x');
                //traslada(0,-220,0);
               // pintaPoligono(vecX+anima,vecY,5,color);
                rota(180,'x');
                traslada(0,-500,0);
                 //rota(anima,'y');
                 //traslada(-100,0,0);
                  //rota(circle,'y');
              //  rota(circle,'y');
              pintaCasa(x1,y1,5,8);
	int steps=10;
	int n1=steps;
	
///	console(0,400);
 
    if(--n1>0)
    {
        vecX[0]=x1;    vecY[0]=y1;
        vecX[1]=x3;    vecY[1]=y3;
        vecX[2]=x2;   vecY[2]=y1;
        //traslada(n1,0,0);
//for(int i=0;i<n1;i++)
        pintaCasa(x1,y1,3,0);
        //rota(anima,'y');
        
        anima++;
        //traslada(0,-91,0);
      //  pintaPoligono(vecX,vecY,3,color);

        fractal(n1,x1,x3,x2,y1,y3,y1);
        //pintaCasa(x1,y1,5,0);
        //rota(anima,'y');
        fractal(n1,x2,x3,x1,y1,y3,y1);
        //rota(anima,'x');
        }	

*/
    
}

int main(int argc, char *argv[])
{
 	dmouX=dmouY=0;
 	superX=superY=0;
 	anim=1;
 	Boton=-1;
 	initSDL();
	init();     //inicializar valores iniciales
	initText();
	render();   //dibujar
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
			if( event.key.keysym.sym == SDLK_SPACE )
			{anim=!anim;
				render();
				if(anim)
				gLastTick = SDL_GetTicks();	
			}
			break;
		case SDL_VIDEORESIZE:
			winX=event.resize.w; winY=event.resize.h;
			screen = SDL_SetVideoMode(winX, winY, 32, SDL_SWSURFACE | SDL_RESIZABLE );
			render();
			break;
		case SDL_MOUSEBUTTONDOWN:
			//mouX = event.button.x;//se van a comentar 
			//mouY = winY - event.button.y;//para la nueva animacion
			//dmouX=dmouY=0;
			mouse = 1;
			//este d abajo c comenta
			Boton=(event.button.button==SDL_BUTTON_LEFT)?1:0;//1-boton izq,0-boton der
			render();//tambien  c comenta
			break;
        case SDL_MOUSEBUTTONUP:
            //dmouX=0;dmouY=0;//c comenta
            mouse=0;
            Boton=1;
            break;
        case SDL_MOUSEMOTION:
            if(mouse&Boton==1)
            {
                      dmouX+=event.motion.xrel;
                      dmouY-=event.motion.yrel;
            }
            else if(mouse&Boton==0)
            {
                 
                 }
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

void fractal(int n1, double x1_1, double x2_1, double x3_1, double y1_1, double y2_1, double y3_1)
{ 
        int x1,x2,x3,y1,y2,y3,color;
        float r=360.0;
        x1=(int)(x1_1 + (x2_1-x3_1));
        x2 = (int)(x2_1 + (x2_1-x3_1));
        x3 = (int)(((x2_1 + (x2_1-x3_1)) + ((x2_1-x3_1)/2)) + ((x1_1-x2_1)/2));
        y1 = (int)(y1_1 + (y2_1-y3_1));
        y2 = (int)(y2_1 + (y2_1-y3_1));
        y3 = (int)(((y1_1 + (y2_1-y3_1)) + ((y2_1-y1_1)/2)) + ((y2_1-y3_1)/2));

        //color=0x096E0C;
        vecX[0]=x1;
        vecX[1]=x2;
        vecX[2]=(int)x2_1;
        vecX[3]=x1;
        
        vecY[0]=y1;
        vecY[1]=y2;
        vecY[2]=(int)y2_1;
        vecY[3]=y1;
        circle=x1;
      //rota(36,'x');
      //rota(36,'y');
      //rota(x1,'y');
     //escala(0,0,0.9);
   // traslada(0+anima,0+anima,0);
   //rota(anima,'x');
   //
   //rota(x1,'y');
        pintaCasa(x1,y1,4,0);
       //   anima--;
       
        if(--n1 > 0){
           // rota(180,'x');
         // Bresenhamline((int)x1, (int)y1, (int)x3, (int)y3,color);
           // Bresenhamline((int)x2, (int)y2, (int)x3, (int)y3,color);
            
            fractal(n1, x1, x3, x2, y1, y3, y2);
            fractal(n1, x2, x3, x1, y2, y3, y1);
            
        }
}
