#pragma once
//#include "main.h"
#include "primitivas.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
#define BLANCO 0xffffff
#define SIZE 256
#define CFONDO 0xF7FFE6
#define TOP 0x0C7AE2
#define CARCASA 0x1F2624
#define VERDE 0x00FF4C

string t, hora, dia, year, number, msm;
int ventana = 1;
int MOption = 0;
int userSelect = 0;
int MensajeOP = 0;

SDL_Surface* fontSurface;
SDL_Color fColor;
SDL_Rect fontRect;
TTF_Font* font;

int menuOptionSelect(  )
{
	return MOption % 3;
}

int mensajeOptionSelected(  )
{
	return MensajeOP % 4;
}

int UserSelected(  )
{
	return userSelect % 4;
}

void fontInit(){
        TTF_Init();
        font = TTF_OpenFont("f.ttf", 30);
        int r,g,b;
        getRGB( r,g,b, AZUL + ROJO + AMARILLO );
        fColor.r = r;
        fColor.g = g;
        fColor.b = b;
}

void printF(char *c, int x, int y){
        fontSurface = TTF_RenderText_Solid(font, c, fColor);
        fontRect.x = x;
        fontRect.y = y;
        SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);
        SDL_Flip(screen);
}

typedef struct b$
{
	Poly poly;
	string s;
	bool dentro( int x, int y )
	{
		if( x > poly.X[0] && x < poly.X[2] && y > poly.Y[0] && y < poly.Y[2] )
			return true;
		return false;
	}
}Buttom;

Buttom B[21];

void drawButtom( Buttom B )
{
	drawPolygon( B.poly, "fill");
	int px, py;
	int x1 = B.poly.X[0];
	int y1 = B.poly.Y[0];
	int x2 = B.poly.X[2];
	int y2 = B.poly.Y[2];

	px = B.s.size();
	px = ( x2 - x1 - px*10 ) / 2;

	drawPolygon( B.poly, "fill" );
	drawString( B.s , x1 + px - 2 , y1 , BLANCO );
}

void botones()
{
	Poly f;

	int x = 210, y = 20;

	f.clear(); f.setColor( NEGRO );
	f.insert( x, y );
	f.insert( x , y + 230 );
	f.insert( x + 200 , y + 230 );
	f.insert( x + 200, y );
	f.insert( x, y );
	drawPolygon(f, "fill");

	x = 225, y = 220;
	y -= 75;	
	int i=0;
	for( ; i<3; i++ )
	{
		B[i].poly.clear();
		B[i].s = '7'+i;
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x , y ); 
		B[i].poly.insert( x , y + 25  ); 
		B[i].poly.insert( x + 50 , y + 25 ); 
		B[i].poly.insert( x + 50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		x += 60;
	}

	x = 225, y -= 30;

	for( ; i<6; i++ )
	{
		B[i].poly.clear();
		B[i].s = '1'+i;
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x , y ); 
		B[i].poly.insert( x , y + 25  ); 
		B[i].poly.insert( x + 50 , y + 25 ); 
		B[i].poly.insert( x + 50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		x += 60;
	}

	x = 225, y -= 30;

	for( ; i<9; i++ )
	{
		B[i].poly.clear();
		B[i].s = '0' - 5 + i;
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x , y ); 
		B[i].poly.insert( x , y + 25  ); 
		B[i].poly.insert( x + 50 , y + 25 ); 
		B[i].poly.insert( x + 50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		x += 60;
	}

	string tmp;
	x = 225, y -= 30;
	for( ; i<12; i++ )
	{
		B[i].poly.clear();
		if( i == 9 ) tmp = "*";
		else if( i == 10 ) tmp = "0";
		else if( i == 11 ) tmp = "#";
		B[i].s = tmp;
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x , y ); 
		B[i].poly.insert( x , y + 25  ); 
		B[i].poly.insert( x + 50 , y + 25 ); 
		B[i].poly.insert( x + 50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		x += 60;
	}

	x = 225, y = 220;

	f.clear(); f.setColor( AZUL );
	f.insert( x + 55, y - 35 );
	f.insert( x + 55, y - 35 + 60 );
	f.insert( x + 115 , y -35 + 60 );
	f.insert( x + 115, y -35 );
	f.insert( x + 55, y -35 );
	drawPolygon(f, "fill");

	B[16].poly.clear();
	B[16].s = "OK";
	B[16].poly.setColor(AZUL); 
	B[16].poly.insert( x + 55 + 15 , y -35 + 15); 
	B[16].poly.insert( x + 55 + 15 , y -35  +15  +30); 
	B[16].poly.insert( x + 55 + 15+ 30 , y - 35 +15 +30); 
	B[16].poly.insert( x + 55 + 15+ 30 , y - 35 +15 ); 
	B[16].poly.insert( x + 55 + 15, y -35 + 15); 
	drawButtom( B[16] );
	
	//izquierda
	B[19].poly.clear();
	B[19].s = "";
	B[19].poly.setColor(AZUL); 
	B[19].poly.insert( x + 55  , y - 20 ); 
	B[19].poly.insert( x + 55 , y + 10 ); 
	B[19].poly.insert( x + 55+ 15 , y + 10); 
	B[19].poly.insert( x + 55+ 15 , y - 20 ); 
	B[19].poly.insert( x + 55 , y -20); 
	drawButtom( B[19] );
	//derecha
	B[20].poly.clear();
	B[20].s = "";
	B[20].poly.setColor(AZUL); 
	B[20].poly.insert( x + 55+45  , y - 20 ); 
	B[20].poly.insert( x + 55+45 , y + 10 ); 
	B[20].poly.insert( x + 55+15+45 , y + 10); 
	B[20].poly.insert( x + 55+15+45 , y - 20 ); 
	B[20].poly.insert( x + 55+45 , y -20); 
	drawButtom( B[20] );
	//arriba
	B[17].poly.clear();
	B[17].s = "";
	B[17].poly.setColor(AZUL); 
	B[17].poly.insert( x + 55 + 15 , y + 10); 
	B[17].poly.insert( x + 55 + 15 , y +25); 
	B[17].poly.insert( x + 55 + 15+ 30 , y+25); 
	B[17].poly.insert( x + 55 + 15+ 30 , y +10 ); 
	B[17].poly.insert( x + 55 + 15 , y +10); 
	drawButtom( B[17] );
	//abajo
	B[18].poly.clear();
	B[18].s = "";
	B[18].poly.setColor(AZUL); 
	B[18].poly.insert( x + 55 + 15 , y + 10 - 45 ); 
	B[18].poly.insert( x + 55 + 15 , y +25-45); 
	B[18].poly.insert( x + 55 + 15+ 30 , y+25-45); 
	B[18].poly.insert( x + 55 + 15+ 30 , y +10-45 ); 
	B[18].poly.insert( x + 55 + 15 , y +10-45); 
	drawButtom( B[18] );

	y -= 2;
	for( i = 12; i<14; i++ )
	{
		B[i].poly.clear();
		B[i].s = "";
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x , y ); 
		B[i].poly.insert( x , y + 25  ); 
		B[i].poly.insert( x + 50 , y + 25 ); 
		B[i].poly.insert( x + 50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		y -= 30;
	}

	x = 225, y = 220;
	y -= 2;
	for( i = 14; i<16; i++ )
	{
		B[i].poly.clear();
		B[i].s = "";
		B[i].poly.setColor(AZUL); 
		B[i].poly.insert( x + 120 , y ); 
		B[i].poly.insert( x +120 , y + 25  ); 
		B[i].poly.insert( x + 120 + 50 , y + 25 ); 
		B[i].poly.insert( x + 120 +50 , y ); 
		B[i].poly.insert( x , y ); 
		drawButtom( B[i] );	
		y -= 30;
	}
	
	tmp = "CELLPHONE";

	drawString( tmp, x+ 38, 25, BLANCO );

	drawLine( 233, 231, 265, 231, BLANCO );
	drawLine( 233, 230, 265, 230, BLANCO );
	drawLine( 233, 201, 265, 201, VERDE );
	drawLine( 233, 200, 265, 200, VERDE );
	drawLine( 233 + 120, 231, 265 + 120, 231, BLANCO );
	drawLine( 233 + 120, 230, 265 + 120, 230, BLANCO );
	drawLine( 233 + 120, 201, 265 + 120, 201, ROJO );
	drawLine( 233 + 120, 200, 265 + 120, 200, ROJO );

	drawLine( x+55, y+86, x+70, y+71, NEGRO );
	drawLine( x+55, y+85, x+70, y+70, NEGRO );
	drawLine( x+55, y+87, x+70, y+72, NEGRO );

	drawLine( x+55+45, y+71, x+70+45, y+87, NEGRO );
	drawLine( x+55+45, y+70, x+70+45, y+86, NEGRO );
	drawLine( x+55+45, y+72, x+70+45, y+88, NEGRO );

	drawLine( x+55, y+26, x+70, y+42, NEGRO );
	drawLine( x+55, y+25, x+70, y+41, NEGRO );
	drawLine( x+55, y+27, x+70, y+43, NEGRO );

	drawLine( x+100, y+42, x+115, y+26, NEGRO );
	drawLine( x+100, y+41, x+115, y+25, NEGRO );
	drawLine( x+100, y+43, x+115, y+27, NEGRO );

	f=B[16].poly;
	f.setColor(NEGRO);
	drawPolygon( f, "wire" );
	for(int i=0; i<5; i++)
	{
		f.X[i]--;
		f.Y[i]--;
	}
	drawPolygon( f, "wire" );
}

void getTime( )
{
	char buffer[SIZE];
	time_t curtime;
	struct tm *loctime;

	/* Get the current time. */
	curtime = time (NULL);

	/* Convert it to local time representation. */
	loctime = localtime (&curtime);

	/* Print out the date and time in the standard format. */
	//fputs (asctime (loctime), stdout);
	t = asctime (loctime);
	
	/* Print it out in a nice format. */
	strftime (buffer, SIZE, "%A\n", loctime);
	dia = buffer;
	strftime (buffer, SIZE, "%B %d\n", loctime);
	year = buffer;
	//fputs (buffer, stdout);
	strftime (buffer, SIZE, "%I:%M %p\n", loctime);
	hora = buffer;
	//fputs (buffer, stdout);
}

void barrita()
{
	Poly b;

	int x = 394, y = 443;

	b.clear();
	b.setColor(BLANCO);
	b.insert( x, y );
	b.insert( x, y+4 );
	b.insert( x+2, y+4);
	b.insert( x+2, y );
	b.insert( x, y );
	drawPolygon(b,"fill");

	b.clear();
	b.setColor(BLANCO);
	b.insert( x+3, y );
	b.insert( x+3, y+7 );
	b.insert( x+5, y+7);
	b.insert( x+5, y );
	b.insert( x+3, y );
	drawPolygon(b,"fill");

	b.clear();
	b.setColor(BLANCO);
	b.insert( x+6, y );
	b.insert( x+6, y+10 );
	b.insert( x+8, y+10);
	b.insert( x+8, y );
	b.insert( x+6, y );
	drawPolygon(b,"fill");

	b.clear();
	b.setColor(BLANCO);
	b.insert( x+9, y );
	b.insert( x+9, y+13 );
	b.insert( x+11, y+13);
	b.insert( x+11, y );
	b.insert( x+9, y );
	drawPolygon(b,"fill");
}

void fondo( )
{
	Poly general;
	Poly border;
	Poly arriba;
	Poly abajo;
	int x=210, y=260;

	general.clear();
	general.setColor( CFONDO );
	general.insert( x , y );
	general.insert( x + 200, y );
	general.insert( x + 200, y + 200 );
	general.insert( x , y + 200 );
	general.insert( x , y );

	drawPolygon( general, "fill" );

	border.clear();
	border.setColor( NEGRO );
	border.insert( x + 3 , y + 3 );
	border.insert( x + 200 - 3 , y + 3 );
	border.insert( x + 200 - 3 , y + 200 - 3 );
	border.insert( x + 3 , y + 200 - 3 );
	border.insert( x + 3 , y + 3);

	drawPolygon( border, "wire" );

	//ancho 193
	//alto 17
	arriba.clear();
	arriba.setColor( NEGRO );
	arriba.insert( x + 4 , y + 180 );
	arriba.insert( x + 197, y + 180 );
	arriba.insert( x + 197, y + 197 );
	arriba.insert( x + 4 , y + 197 );
	arriba.insert( x + 4 , y + 180 );

	drawPolygon( arriba, "fill" );
	
	//alto 21
	abajo.clear();
	abajo.setColor( NEGRO );
	abajo.insert( x + 4 , y + 4 );
	abajo.insert( x + 197, y + 4 );
	abajo.insert( x + 197, y + 25 );
	abajo.insert( x + 4 , y + 25 );
	abajo.insert( x + 4 , y + 4 );

	drawPolygon( abajo, "fill" );

	barrita();
}

void  carcasa()
{
	Poly b;

	int x = 205, y = 15;

	b.clear();
	b.setColor(CARCASA);
	b.insert( x, y );
	b.insert( x, y+450 );
	b.insert( x+210, y+450);
	b.insert( x+210, y );
	b.insert( x, y );
	drawPolygon(b,"fill");
}

void pantalla1()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+65,y+175, BLANCO );
	drawString( "MENU",x+77,y, BLANCO );
	//drawString( "OK",x+85,y, BLANCO );
	//drawString( "Colgar",x+5,y, BLANCO );
	//drawString( "Borrar",x+130,y, BLANCO );

	getTime();

	px = hora.size();
	px = (200 - px*10 ) / 2;
	drawString(hora, x+55, y+130, NEGRO);

	px = dia.size();
	px = (200 - px*10 ) / 2;
	drawString(dia, x+px, y+110, NEGRO);

	px = year.size();
	px = (200 - px*10 ) / 2;
	drawString(year, x+px, y+90, NEGRO);

	drawString("BIENVENIDO", x+46, y+60, NEGRO);
}

void llamada( )
{
	int c1 = 0xA5EBFF, c2=0x00647F;
	Poly f;
	f.clear();
	if( menuOptionSelect() == 0 )
		c1 = 0x00647F;
	else
		c1 =  0xA5EBFF;
		
	f.setColor(c1);

	int x = 225, y=360;

	f.insert( x, y );
	f.insert( x, y+50);
	f.insert( x+50, y+50);
	f.insert( x+50, y);
	f.insert( x, y);

	drawPolygon( f , "fill" );
	int c = 0x3433FF;
	f.setColor(c);
	drawPolygon( f , "wire" );

	drawCircle( x+25, y+35, 10, c );
	fillBFS( x+25, y+35, c , getpixel(x+25, y+35));
	drawArc( x+25, y+10, 15 , 0 , 180, c );
	fillBFS( x+25, y+15, c , getpixel(x+25, y+15));
}

void mensajes( )
{
	int c1 = 0xA5EBFF, c2=0x00647F;
	Poly f;
	f.clear();
	if( menuOptionSelect() == 1 )
		c1 = 0x00647F;
	else
		c1 =  0xA5EBFF;
		
	f.setColor(c1);
	int x = 285, y=360;

	f.insert( x, y );
	f.insert( x, y+50);
	f.insert( x+50, y+50);
	f.insert( x+50, y);
	f.insert( x, y);

	drawPolygon( f , "fill" );
	int c = 0x3433FF;
	f.setColor(c);
	drawPolygon( f , "wire" );

	f.clear(); 
	f.setColor(c);
	f.insert( x+10, y+10 );
	f.insert( x+10, y+40);
	f.insert( x+41, y+40);
	f.insert( x+41, y+10);
	f.insert( x+10, y+10);
	drawPolygon( f , "fill" );

	drawLine( x+10, y+39, x+25, y+30, c1);
	drawLine( x+25, y+30, x+40, y+40, c1);
}

void contactos(  )
{
	int c1 = 0xA5EBFF, c2=0x00647F;
	Poly f;
	f.clear();
	if( menuOptionSelect() == 2 )
		c1 = 0x00647F;
	else
		c1 =  0xA5EBFF;
		
	f.setColor(c1);

	int x = 345, y=360;

	f.insert( x, y );
	f.insert( x, y+50);
	f.insert( x+50, y+50);
	f.insert( x+50, y);
	f.insert( x, y);

	drawPolygon( f , "fill" );
	int c = 0x3433FF;
	f.setColor(c);
	drawPolygon( f , "wire" );

	f.clear(); 
	f.setColor(c);
	f.insert( x+10, y+10 );
	f.insert( x+10, y+40);
	f.insert( x+41, y+40);
	f.insert( x+41, y+10);
	f.insert( x+10, y+10);
	drawPolygon( f , "fill" );

	drawLine( x+15, y+10, x+15, y+40, c1);
}

void menu()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	drawString( "Atras",x+5,y, BLANCO );
	//drawString( "Borrar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "MENU",x+77,y+153, NEGRO );

	llamada();
	mensajes();
	contactos();
	

	if( menuOptionSelect() == 0  )
		drawString( "Llamadas",x+56,y+20, NEGRO );
	else if( menuOptionSelect() == 1 )
		drawString( "Mensajes",x+56,y+20, NEGRO );
	else if( menuOptionSelect() == 2 )
		drawString( "Contactos",x+50,y+20, NEGRO );
}

void drawNumber()
{
	int x=210, y=260;
	if( number != "" )
	{
		char vec[100];
		int i;
		
		for(i=0; number[i]!='\0' && i<8; i++)
			vec[i] = number[i];
		vec[i]='\0';
		printF( vec, x+20, y-180);
		int k=0;
		for( ; number[i]!='\0' ; i++)
			vec[k++] = number[i];
		vec[k]='\0';
		printF( vec, x+50, y-150);
		
	}
}

void PLLamadas()
{
	
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	if( number != "" )
		drawString( "Borrar",x+5,y, BLANCO );
	else
		drawString( "Atras",x+5,y, BLANCO );
	drawString( "Contac",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "LLAMADAS",x+56,y+153, NEGRO );

	drawNumber();

	drawString( "Teclea el num",x+3450,y+20, NEGRO );
		
}

void PLlamando()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	drawString( "LLAMANDO A",x+45,y+150, NEGRO );
	//drawString( "OK",x+85,y, BLANCO );

	drawString( "Altavoz",x+5,y, BLANCO );
	//drawString( "Contac",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	//drawString( "LLAMADAS",x+56,y+153, NEGRO );

	//drawString( number, x+30, y+120 , AZUL + ROJO);
	drawNumber();
}

void PMensajes()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	drawString( "Atras",x+5,y, BLANCO );
	//drawString( "LLamar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "MENSAJES",x+55,y+153, NEGRO );

	Poly f;
	f.clear();
	f.insert( x+20, y+130 );
	f.insert( x+20, y+150 );
	f.insert( x+180, y+150 );
	f.insert( x+180, y +130 );
	f.insert( x+20, y+130 );

	if( mensajeOptionSelected() == 0 )
		f.setColor(0x00647F);
	else
		f.setColor(0xA5EBFF);

	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );
	
	if( mensajeOptionSelected() == 0 )
		drawString( "Nuevo", x+20, y+128, BLANCO );
	else
		drawString( "Nuevo", x+20, y+128, NEGRO );
	

	if( mensajeOptionSelected() == 1 )
		f.setColor(0x00647F);
	else
		f.setColor(0xA5EBFF);

	monster.reset();

	monster.traslation(0,-25,0);
	f.setMonster( monster );

	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );

	if( mensajeOptionSelected() == 1 )
		drawString( "Enviados", x+20, y+102, BLANCO );
	else
		drawString( "Enviados", x+20, y+102, NEGRO );

	if( mensajeOptionSelected() == 2 )
		f.setColor(0x00647F);
	else
		f.setColor(0xA5EBFF);

	monster.reset();

	monster.traslation(0,-25,0);
	f.setMonster( monster );

	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );

	if( mensajeOptionSelected() == 2 )
		drawString( "Recibidos", x+20, y+77, BLANCO );
	else
		drawString( "Recibidos", x+20, y+77, NEGRO );

	if( mensajeOptionSelected() == 3 )
		f.setColor(0x00647F);
	else
		f.setColor(0xA5EBFF);

	monster.reset();

	monster.traslation(0,-25,0);
	f.setMonster( monster );

	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );

	if( mensajeOptionSelected() == 3 )
		drawString( "Borradores", x+20, y+53, BLANCO );
	else
		drawString( "Borradores", x+20, y+53, NEGRO );
	
	
}

void PVacia()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	//drawString( "OK",x+85,y, BLANCO );
	drawString( "Atras",x+5,y, BLANCO );
	//drawString( "LLamar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "\"VACIO\"",x+62,y+133, NEGRO );
}

void PME()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	//drawString( "Atras",x+5,y, BLANCO );
	//drawString( "LLamar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "\"MSM ENVIADO\"",x+32,y+133, NEGRO );
}

void PMenEnviar()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	if( number != "" )
		drawString( "Borrar",x+5,y, BLANCO );
	else
		drawString( "Atras",x+5,y, BLANCO );
	drawString( "Contac",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "ENVIANDO",x+56,y+153, NEGRO );

	drawNumber();

	drawString( "Teclea el num",x+33,y+20, NEGRO );
}

void PWrite()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	if( msm == "")
		drawString( "Atras",x+5,y, BLANCO );
	else
		drawString( "Borrar",x+5,y, BLANCO );
	//drawString( "Enviar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "ESCRIBIR SMS",x+32,y+153, NEGRO );

	Poly f;
	f.clear();
	f.setColor( BLANCO );
	f.insert( x+10, y+35 );
	f.insert( x+10, y+35 + 120 );
	f.insert( x+10 + 180 , y+35 + 120 );
	f.insert( x+10 + 180 , y+35 );
	f.insert( x+10, y+35 );

	drawPolygon( f, "fill" );

	int tx=x, ty=y;
	if( msm != "" )
	{
		for( int i=0; msm[i]!='\0'; i++ )
		{
			if( tx > 350 )
			{
				tx = x;
				ty -= 15;
			}
			string stmp = "";
			stmp += msm[i];
			drawString( stmp, tx+20, ty+132, NEGRO );
			tx+=10;
		}
	}
}


void PLlamaEsau()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	drawString( "LLAMANDO A",x+45,y+150, NEGRO );
	//drawString( "OK",x+85,y, BLANCO );

	drawString( "Altavoz",x+5,y, BLANCO );
	//drawString( "Contac",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	//drawString( "LLAMADAS",x+56,y+153, NEGRO );

	//drawString( number, x+30, y+120 , AZUL + ROJO);
	//drawNumber();
	//drawString( "Esau",x+45,y+150, AMARILLO + ROJO + AZUL );
	char vec[] = "Esau";
	printF( vec, x+65, y-170 );
}

void PContactosM()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	drawString( "Atras",x+5,y, BLANCO );
	//drawString( "LLamar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "CONTACTOS",x+52,y+153, NEGRO );

	Poly f;
	f.clear();
	f.insert( x+20, y+130 );
	f.insert( x+20, y+150 );
	f.insert( x+180, y+150 );
	f.insert( x+180, y +130 );
	f.insert( x+20, y+130 );

	
	f.setColor(0x00647F);
		
	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );

	drawString( "Esau 9511235485", x+20, y+127, BLANCO );
}

void PContactos()
{
	int x=210, y=260, px;

	fondo();

	drawString( "Telcel",x+1,y+175, BLANCO );
	//drawString( "MENU",x+77,y, BLANCO );
	drawString( "OK",x+85,y, BLANCO );
	drawString( "Atras",x+5,y, BLANCO );
	drawString( "LLamar",x+130,y, BLANCO );

	getTime();
	drawString(hora, x+80, y+175, BLANCO);
	drawString( "CONTACTOS",x+52,y+153, NEGRO );

	Poly f;
	f.clear();
	f.insert( x+20, y+130 );
	f.insert( x+20, y+150 );
	f.insert( x+180, y+150 );
	f.insert( x+180, y +130 );
	f.insert( x+20, y+130 );

	
	f.setColor(0x00647F);
		
	drawPolygon( f , "fill" );
	f.setColor( AZUL );
	drawPolygon( f , "wire" );

	drawString( "Esau 9511235485", x+20, y+127, BLANCO );
}



void loadVentana()
{
	if( ventana != 2 )
		MOption = 0;
	if( ventana != 3 && ventana != 6 && ventana != 9)
	{
		userSelect = 0; 
		number = "";
	}
		
	if( ventana != 4 )
		MensajeOP = 0;
	if ( ventana != 8 && ventana != 9 && ventana != 12 )
		msm = "";

	switch( ventana )
	{
		case 1: pantalla1(); break;
		case 2: menu(); break;
		case 3: PLLamadas(); break;
		case 4: PMensajes(); break;
		case 5: PContactos(); break;
		case 6: PLlamando(); break;
		case 7 : PVacia(); break;
		case 8 : PWrite(); break;
		case 9 : PMenEnviar(); break;
		case 10 : PME(); break;
		case 11 : PLlamaEsau(); break;
		case 12 : PContactosM(); break;
		default : pantalla1(); break;
	}
}

char buttomValor( int b )
{
	switch(b)
	{
		case 0 : return '7';
		case 1 : return '8';
		case 2 : return '9';
		case 3 : return '4';
		case 4 : return '5';
		case 5 : return '6';
		case 6 : return '1';
		case 7 : return '2';
		case 8 : return '3';
		case 9 : return '*';
		case 10: return '0';
		case 11: return '#';
	}
}

void eventos( int accion )
{
	if( accion == -1 ) return;
	if( ventana == 1 ) //principal
	{
		if( accion < 12 && number.size() < 13 )
		{
			number += buttomValor( accion );
			ventana = 3;
		}
		else switch( accion )
		{
			case 16 : ventana = 2; break;
		}
	}
	else if( ventana == 2 ) //menu
	{
		switch( accion )
		{
			//ok
			case 12 : ventana = 1; break;
			//arriba
			case 17 : break;
			//abajo
			case 18 : break;
			//izquierda
			case 19 : ( MOption > 0 )? MOption-- : MOption = 2; break;
			//derecha
			case 20 : MOption++; break;

			case 16 :   if( menuOptionSelect() == 0 ) ventana = 3;
						if( menuOptionSelect() == 1 ) ventana = 4;
						if( menuOptionSelect() == 2 ) ventana = 5;
						break;

			case 15 : ventana = 1; break;
		}
	}
	else if( ventana == 3 ) //llamadas
	{
		if( accion < 12 && number.size() < 13 )
		{
			number += buttomValor( accion );
			//printf("%s\n", number.c_str());
		}
		else switch( accion )
		{
			case 12 :   if( number == "")
							ventana = 2;
						else{
							string tmp="";
							for(int i=0; i<number.size()-1; i++)
								tmp += number[i];
							number = tmp;
						}
						break;
			case 15 : ventana = 1; break;
			case 14 : ventana = 5; break;
			case 13 : if( number != "" )
						ventana = 6; break;
		}
	}
	else if( ventana == 4 ) // mensajes
	{
		switch( accion )
		{
			case 12 : ventana = 2; break;
			case 15 : ventana = 1; break;
			case 17 : ( MensajeOP > 0 )? MensajeOP-- : MensajeOP=3; break;
			case 18 : MensajeOP++; break;
			case 16 : 	if( mensajeOptionSelected() == 0 )
							ventana = 8 ;
						else ventana = 7;
						break;
		}
	}
	else if( ventana == 5 ) // contactos
	{
		switch( accion )
		{
			case 12 : ventana = 2; break;
			case 15 : ventana = 1; break;
			case 14 : ventana = 11; break;
			case 13 : ventana = 11; break;
			case 16 : ventana = 11; break;
		}
	}
	else if( ventana == 6 ) // llamando
	{
		switch( accion )
		{
			case 15 : ventana = 3; break;
		}
	}
	else if( ventana == 7 ) // vacia
	{
		switch( accion )
		{
			case 12 : ventana = 4; break;
			case 15 : ventana = 1; break;
		}
	}
	else if( ventana == 8 ) // pwrite
	{
		if( accion < 12 && msm.size() < 105 )
		{
			msm += buttomValor( accion );
			//printf("%s\n", number.c_str());
		}
		else switch( accion )
		{
			case 12 : 	if( msm == "")
							ventana = 4;
						else{
							string tmp="";
							for(int i=0; i<msm.size()-1; i++)
								tmp += msm[i];
							msm = tmp;
						}
						break;
			case 15 : ventana = 1; break;
			case 16 : ventana = 9; break;
		}
	}
	else if( ventana == 9 ) // vacia
	{
		if( accion < 12 && number.size() < 13 )
		{
			number += buttomValor( accion );
			//printf("%s\n", number.c_str());
		}
		else switch( accion )
		{
			case 12 :   if( number == "")
							ventana = 8;
						else{
							string tmp="";
							for(int i=0; i<number.size()-1; i++)
								tmp += number[i];
							number = tmp;
						}
						break;
			case 16 : 	if( number != "" )
							ventana = 10;
						break;
			case 14 : ventana = 12; break;
		}
	}
	else if( ventana == 10 ) // vacia
	{
		switch( accion )
		{
			
			case 16 : ventana = 4; break;
			case 15 : ventana = 1; break;
		}
	}
	else if( ventana == 11 ) // vacia
	{
		switch( accion )
		{
			case 15 : ventana = 5; break;
		}
	}
	else if( ventana == 12 ) // vacia
	{
		switch( accion )
		{
			case 12 : ventana = 9; break;
			case 16 : ventana = 10; break;
			case 15 : ventana = 1; break;
		}
	}
}

int checkButtom( int x, int y )
{
	for( int i=0; i<21; i++)
		if( B[i].dentro( x, y ) )
			return i;
	return -1;
}