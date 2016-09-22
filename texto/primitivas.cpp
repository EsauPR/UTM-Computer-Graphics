//#include "main.h"
#include "sdlElements.cpp" 
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
//Este archivo incluirá las primitivas para ser llamadas desde archivo main.c
// desde la función "principal()"

//Los prototipos de las funciones de las primitivas seberán ponerse en main.h

//para el mapa de bits de texto
int mapa[20][20];

void initText()
{
	int i;
	FILE    *ifd;
	int leidos;
	char fuente[40];

	strcpy( fuente, "ford.bmp" );
	//strcpy( fuente, "sksapps-256.bmp" );
	//strcpy( fuente, "tempus-256.bmp" );
	
	ifd = fopen( fuente, "r" );
	if( ifd==0 )
	    return;
	fseek( ifd,  0x3e, SEEK_SET );
	leidos = fread( mapa, 20, 20, ifd );
	fclose( ifd );
}

void despMapa()
{
    int x, y, b, byte;
    int offset=20;
    
    for( y=0; y<20; y++ )  //para cada línea
    {
	    for( x=0; x<20; x++ )   //para  cada byte
	    {
	    	/*
			byte=mapa[y][x];
			for( b=0; b<8; b++ )
			{
				//if( byte & 1 )
				if( byte & 128 )
			    //if( byte & 32768 )
			        putpixel( x*8+b, y+offset, 0xffff00 );
				byte = byte << 1;
			}
			//*/
			putpixel( x, y, mapa[x][y] );
			printf("%d ", mapa[x][y]);
		}
		puts("");
	}
}

int hexValor(char c)
{
	if( c>='0' && c<='9' ) return c-'0';
	for(int i=0; i<7; i++)
		if( c == 'A'+i ) return 10+i;
}

int getColumn( char value )
{
	return 15-((int)value/16);
}

int getRow( char value )
{
	return (value%16);
}

void drawLetter(char c, int x, int y, int color)
{
	int row, colum, byte, offset=20;
	char cHex[10];
	int cDec = c;
	sprintf( cHex,"%X",cDec );

	if(strlen(cHex)==2)
	{
		row = hexValor( cHex[ 0 ] );
		colum = hexValor( cHex[ 1 ] );
	}
	else if(strlen(cHex)==3)
	{
		row = hexValor( cHex[ 0 ] );	row*=10;
		row += hexValor( cHex[ 1 ] );
		colum = hexValor( cHex[ 2 ] );
	}
	else if(strlen(cHex)==3)
	{
		row = hexValor( cHex[ 0 ] );	row*=10;
		row += hexValor( cHex[ 1 ] );
		colum = hexValor( cHex[ 2 ] );	colum*=10;
		colum += hexValor( cHex[ 3 ] );
	}

	printf("%s %d %d %d\n", cHex, row, colum, (int)strlen(cHex) );

	for( int j=0; j<16; j++ )  
	    for( int i=0; i<2; i++ )
	    {
			byte=mapa[ 255 - row * 16 - j ][ colum * 2 + i ];
			for( int b=0; b<8; b++ )
			{
				if( byte & 128 )
			        putpixel( x + i*8+b, y - j + offset, color );
				byte = byte << 1;
			}
		}
}
