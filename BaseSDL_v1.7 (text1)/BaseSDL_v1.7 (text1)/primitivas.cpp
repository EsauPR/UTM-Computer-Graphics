#pragma once
#include "main.h"
#include "sdlElements.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
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
	//strcpy( fuente, "sksapps-256.bmp" );
	//strcpy( fuente, "tempus-256.bmp" );
	
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

int getColumn( char value ){
	return 15-((int)value/16);
}

int getRow( char value ){
	return (value%16);
}

void drawLetter(char c, int x, int y, int color){
	int row, colum, byte, offset=20;
	char cHex[10];
	int cDec = c;
	sprintf( cHex,"%X",cDec );

	row = 15 - getColumn(c);
	colum = getRow(c);

	//printf("%s %d %d %d\n", cHex, row, colum, (int)strlen(cHex) );

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

void drawString( string str, int x, int y, int color)
{
	for( int i = 0; str[i] != '\0'; i++, x+=10 )
		drawLetter(str[i], x, y, color);
}

void drawMatriz()
{
	SDL_Rect cuadro;
	char tmp[100];
	string s;
	cuadro.x = 10;	cuadro.y = winY - 150;	cuadro.w = winX - 20;	cuadro.h = 140;
	SDL_FillRect( screen, &cuadro, SDL_MapRGB(screen->format, 50, 50, 50 ) );
	
	int x = 30 , y = 100;

	for( int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		{
			sprintf(tmp, "%.1lf", monster.mat[i][j]);
			s = tmp;
			drawString(s, x + i*50, y - j * 30, AZUL);
		}
}