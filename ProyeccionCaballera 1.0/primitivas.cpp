//#include "main.h"
#include "sdlElements.cpp"

char mapa[256][32];

int ant,min,max;

void despletraMatriz(int i,int j,char c)
{
     int z=0;
 int x,y,b,byte;
 int col,fila;
 col=c%16;
 fila=c/16;
 for( y=0; y<16; y++ )  //para cada l�nea
	    for( x=0; x<2; x++ )   //para  cada byte
	    {
			byte=mapa[y+240-fila*16][x+col*2];
			for( b=0; b<8; b++ )
			{
				if( byte & 128 )
				{
                   if(x*8+b+i>max)
			        max=x*8+b+i;
			        
			        int a1=x*8+b+i,a2=y+j;
			        aplicaMatriz(&a1,&a2,&z);
			        putpixel( a1, a2, 0xffffff );
                }
				byte = byte << 1;
			}
		}
		return;
}

void kerninMatriz(int x,int y,char c[])
{
     max=x;
     ant=0;
     int tam=strlen(c);
     for(int i=0;i<tam;i++)
     {
        if(c[i]==32)
        max=max+8;
        calculamin(max,y,c[i]);
        despletraMatriz(max-(min-max)+3,y,c[i]);
     }
}


void initText()
{
	int i;
	FILE *ifd;
	int leidos;
	char fuente[40];

	strcpy( fuente, "font-cone-256.bmp");
	ifd = fopen( fuente, "r" );
	if( ifd==0 )
	    return;
	fseek( ifd,  0x3e, SEEK_SET );
	leidos = fread( mapa, 256, 32, ifd );
	fclose( ifd );
}

void despMapa()
{
    int x, y, b, byte;
    int offset=20;
    
    for( y=0; y<255; y++ )  //para cada l�nea
	    for( x=0; x<32; x++ )   //para  cada byte
	    {
			byte=mapa[y][x];
			for( b=0; b<8; b++ )
			{
				if( byte & 128 )
			        putpixel( x*8+b, y+offset, 0xff0000 );
				byte = byte << 1;
			}
		}
		return;
}

void despletra(int i,int j,char c)
{
 int x,y,b,byte;
 int col,fila;
 col=c%16;
 fila=c/16;
 for( y=0; y<16; y++ )  //para cada l�nea
	    for( x=0; x<2; x++ )   //para  cada byte
	    {
			byte=mapa[y+240-fila*16][x+col*2];
			for( b=0; b<8; b++ )
			{
				if( byte & 128 )
				{
                   if(x*8+b+i>max)
			        max=x*8+b+i;
			        putpixel( x*8+b+i, y+j, 0x000000 );
                }
				byte = byte << 1;
			}
		}
		return;
}

void calculamin(int i,int j,char c)
{
  int x,y,b,byte;
  int col,fila;
  min=i+16;
  col=c%16;
  fila=c/16;
  for( y=0; y<16; y++ )  //para cada l�nea
	    for( x=0; x<2; x++ )  //para  cada byte
	    {
			byte=mapa[y+240-fila*16][x+col*2];
			for( b=0; b<8; b++ )
			{
				if( byte & 128 )
				{
                   if(x*8+b+i<min)
                    min=x*8+b+i;
                }
				byte = byte << 1;
			}
		}
		return;
}

void kernin(int x,int y,char c[])
{
     max=x;
     ant=0;
     int tam=strlen(c);
     for(int i=0;i<tam;i++)
     {
        if(c[i]==32)
        max=max+8;
        calculamin(max,y,c[i]);
        despletra(max-(min-max)+3,y,c[i]);
     }
}

void Negrita(int x,int y,char c[])
{
     int auxMax=max,auxMin=min;
     max=x;
     ant=0;
     int tam=strlen(c);
     for(int i=0;i<tam;i++)
     {
        if(c[i]==32)
         max=max+8;
        calculamin(max,y,c[i]);
        auxMax=max,auxMin=min;
        despletra(max-(min-max)+3,y,c[i]);
        max=auxMax;min=auxMin;
        despletra(max-(min-max)+3+1,y,c[i]);
     }
}

void despalabra(int x,int y,char c[])
{
     int tam=strlen(c);
     for(int i=0;i<tam;i++)
     {
      despletra(x,y,c[i]);
      x+=10;
     }
}
