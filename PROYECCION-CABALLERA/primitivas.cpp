#include "main.h"
#include <string.h>
#include <stdio.h>

//Este archivo incluirá las primitivas para ser llamadas desde archivo main.c
// desde la función "principal()"

//Los prototipos de las funciones de las primitivas seberán ponerse en main.h

//para el mapa de bits de texto
char mapa[256][32];

void initText()
{
	int i;
	FILE    *ifd;
	int leidos;
	char fuente[40];

	strcpy( fuente, "font-cone-256.bmp" );
	
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
    
    for( y=0; y<255; y++ )  //para cada línea
	    for( x=0; x<32; x++ )   //para  cada byte
	    {
			byte=mapa[y][x];
			for( b=0; b<8; b++ )
			{
				//if( byte & 1 )
				if( byte & 128 )
			    //if( byte & 32768 )
			        putpixel( x*8+b, y+offset, 0xffff00 );
				byte = byte << 1;
			}
		}
}


void dubujaLetra(int X, int Y, char c  )
{
     int x , y, b, byte;
     int i = getColumn( c );
     int j = getRow( c );
     int auxj, auxi;
     for( x = i*16, auxi=0; x < i*16+16; x++, auxi++ )
          for( y=j*2, auxj=0; y<j*2+2;auxj++, y++ )
          {
               byte = mapa[x][y];
               for( b=0; b<8; b++)
               {
                    if( byte & 128 )
                        putpixel( X+auxj*8+b, Y+auxi+20, 0xffffff );
                    byte<<=1;
               }     
          }     
}

void dibujaPalabra(int x,int y,char *palabra)
{
     int tam = strlen(palabra);
     
     for(int i=0;i<tam;i++)
        {
          dubujaLetra(x,y,palabra[i]);
          x+=8;     
        }
     
}

int getColumn( char value )
{
        return 15-((int)value/16);
}

int getRow( char value )
{
        return (value%16);
}
