#pragma once
//#include "main.h"
#include "sdlElements.cpp"
#define AZUL 0x29a7e8
#define ROJO 0xe8292d
#define AMARILLO 0xe8c629
#define NEGRO 0x000000
#define BLANCO 0xffffff

int matProfundidad[600][800];

//Este archivo incluirá las primitivas para ser llamadas desde archivo main.c
// desde la función "principal()"

//Los prototipos de las funciones de las primitivas seberán ponerse en main.h


/* ============== Xiaolin Wu's line algorithm =============== */

void getRGB(int &r, int &g, int &b, int color)
{
    int aux = color;
    b = aux % 256;
    aux /= 256;
    g = aux % 256;
    aux /= 256;
    r = aux;
}

void plot(double x, double y, double c, int color){

	if(!isValid( (int)x, (int)y) ) return;	
	
	int r1,g1,b1,r2,g2,b2,dr,dg,db;
	int fondo=getpixel((int)x, (int)y);
	int aux,gradiente=0;
	
	//obtener el RGB de la linea
    getRGB( r1, g1, b1 , color);
	
    //obtener el RGB del fondo
    getRGB( r2, g2, b2 , fondo);

	//obtener el gradiente del RGB
	dr=r2-r1;
	dr*=(1.0-c);
	dg=g2-g1;
	dg*=(1.0-c);
	db=b2-b1;
	db*=(1.0-c);
	gradiente=(b1+db)+(g1+dg)*256+(r1+dr)*256*256;
	//Dibuja pixel
	putpixel( (int)x, (int)y, gradiente ); //with brightness c (where 0 ? c ? 1)
}
 
int ipart(double x){
     return  (int)x; //return  'integer part of x'
}
 
double round(double x){
     return ipart(x + 0.5); 
}

double fpart(double x){
     int tmp = (int)x;
     return (double)x-tmp; //return 'fractional part of x'
}
 
double rfpart(double x){
     return 1 - fpart(x);
}

void swap(int &x, int &y){
     int tmp = x;
     x = y;
     y = tmp;
}

void drawLine(int x0, int y0, int x1, int y1, int color)
{
     bool steep = abs(y1 - y0) > abs(x1 - x0);
 
     if(steep){
         swap(x0, y0);
         swap(x1, y1);
     }

     if( x0 > x1 ){
       swap(x0, x1);
       swap(y0, y1);
     }
 
     int dx = x1 - x0;
     int dy = y1 - y0;
     double gradient = (double) dy / dx;
 
     // handle first endpoint
     double xend = round(x0);
     double yend = y0 + gradient * (xend - x0);
     double xgap = rfpart(x0 + 0.5);
     
     double xpxl1 = xend;   //this will be used in the main loop
     double ypxl1 = ipart(yend);
     
     if( steep ){
         plot(ypxl1, xpxl1, rfpart(yend) * xgap, color);
         plot(ypxl1+1, xpxl1,  fpart(yend) * xgap, color);
     }
     else{
         plot(xpxl1, ypxl1  , rfpart(yend) * xgap, color);
         plot(xpxl1, ypxl1+1,  fpart(yend) * xgap, color);
     }
     
     double intery = yend + gradient ; // first y-intersection for the main loop
 
     // handle second endpoint

     xend = round(x1) ;
     yend = y1 + gradient * (xend - x1) ;
     xgap = fpart(x1 + 0.5) ;
     double xpxl2 = xend ;//this will be used in the main loop
     double ypxl2 = ipart(yend) ;

     if( steep ){
         plot(ypxl2  , xpxl2, rfpart(yend) * xgap, color) ;
         plot(ypxl2+1, xpxl2,  fpart(yend) * xgap, color) ;      
     }
     else{
         plot(xpxl2, ypxl2,  rfpart(yend) * xgap, color) ;
         plot(xpxl2, ypxl2+1, fpart(yend) * xgap, color) ;
     }
     
     // main loop 	
     for( double x = xpxl1 + 1; x <= xpxl2 - 1; x++){
          
          if( steep ){
             plot( (double)ipart(intery), x, rfpart(intery), color) ;
             plot( (double)ipart(intery)+1, x,  fpart(intery), color) ;
          }
         else{
             plot(x, (double)ipart (intery),  rfpart(intery), color) ;
             plot(x, (double)ipart (intery)+1, fpart(intery), color) ;
         }
         intery = intery + gradient ;   
     }
}


/* ============= Circulo =============== */

void drawCircle( int x, int y, int radio, int color )
{
	// Se dibuja mediante lineas el rededor del perimetro
	int x1 = x + radio,y1=y,x2,y2; // punto incial
	
	for(int i=0; i<=360; i+=3)
	{
		x2 = x + cos(i*3.14159/180)*radio;
		y2 = y + sin(i*3.14159/180)*radio;
		drawLine(x1, y1, x2, y2, color);
		x1 = x2;
		y1 = y2;
	}
}

/* =========== Poligono Regular */

void drawRegularPolygon( int x, int y, int radio, int edge, int color )
{
    // Se dibuja mediante lineas el rededor del perimetro
    int x1 = x + radio,y1=y,x2,y2; // punto incial
    
    int inc = 360/edge;

    for(int i=0; i<=360; i+=inc)
    {
        x2 = x + cos(i*3.14159/180)*radio;
        y2 = y + sin(i*3.14159/180)*radio;
        drawLine(x1, y1, x2, y2, color);
        x1 = x2;
        y1 = y2;
    }
}

/* ============= Arco =============== */

void drawArc( int x, int y, int radio, int ini, int fin, int color )
{
	if(ini>fin)    swap(ini,fin);
    int tx,ty;
	int x1 = x + cos(ini*3.14159/180)*radio;
	int y1 = y + sin(ini*3.14159/180)*radio;
    tx = x1;
    ty = y1;
	int x2,y2;

	for(int i=ini; i<=fin; i+=5)
	{
		x2 = x + cos(i*3.14159/180)*radio;
		y2 = y + sin(i*3.14159/180)*radio;
		drawLine(x1, y1, x2, y2, color);
		x1 = x2;
		y1 = y2;
	}
    drawLine( tx, ty, x2, y2, color );
}

/* ============= Espiral =============== */

void drawEspiral(int x, int y, int radio, int ini, double numVueltas, int inc, int color)
{
     double gt = 360*numVueltas; 
     int fin = ini + (int)gt;
     double radio1 = (double)radio;
     double salto = (double)inc/360.0;
     
     int x1 = x + cos(ini*3.14159/180)*radio1;
     int y1 = y + sin(ini*3.14159/180)*radio1;
     int x2,y2;

     for(int i=ini; i<=fin; i++)
     {
        x2 = x + cos(i*3.14159/180)*radio1;
        y2 = y + sin(i*3.14159/180)*radio1;
	    drawLine(x1, y1, x2, y2, color);
    	x1 = x2;
    	y1 = y2;
        radio1 += salto;
     }
}

/* ============= Relleno DFS =============== */

void fillDFS(int x, int y, int color, int fondo )
{
     if(getpixel(x,y)!=fondo) return;
     putpixel(x,y,color);
     
     int pos[]={1,0,-1,0,0,1,0,-1};
     for(int i=0; i<8; i+=2)
         if( isValid( x+pos[i], y+pos[i+1] ) )
             fillDFS(x+pos[i], y+pos[i+1],color,fondo);
}

/* ============= Relleno BFS =============== */

void fillBFS(int x, int y, int color, int fondo )
{
     if(getpixel(x,y)!=fondo) return;
     int pos[]={1,0,-1,0,0,1,0,-1};
     if(color==fondo)
         color = 0x000000;
     
     putpixel(x,y,color);
     queue<int> cola;
     cola.push(x);
     cola.push(y);
     while(!cola.empty())
     {
       x = cola.front(); cola.pop();
       y = cola.front(); cola.pop();
       for(int i=0; i<8; i+=2)
         if( isValid( x+pos[i], y+pos[i+1] ) && getpixel( x+pos[i], y+pos[i+1] )==fondo)
         {
             putpixel(x+pos[i], y+pos[i+1],color);
             cola.push(x+pos[i]);
             cola.push(y+pos[i+1]);
         }
     }
}

/* ============= Validación de Pantalla =============== */

bool isValid(int x1, int y1, int x2, int y2){
    return ( x1<winX && x1>=0 && x2<winX && x2>=0 && y1<winY && y1>=0 && y2<winY && y2>=0)? true:false;
}

bool isValid(int x1, int y1){
    return ( x1<winX && x1>=0 && y1<winY && y1>=0 )? true:false;
}

double distancia(int x1, int y1, int x2, int y2)
{
    return sqrt( ( x2 - x1 ) * ( x2 - x1 ) +  ( y2 - y1 ) * ( y2 - y1 ) );
}

double dist3D(int x1, int y1, int z1, int x2, int y2, int z2)
{
    return sqrt( ( x2 - x1 ) * ( x2 - x1 ) +  ( y2 - y1 ) * ( y2 - y1 ) + ( z2 - z1 ) * ( z2 - z1 ) );
}

/* ============= Relleno Poligonal =============== */

int distZ(int x1, int y1, int x2, int y2, int xp, int yp, int z1, int z2)
{
    double zp;

    double d1 = distancia( x1, y1, xp, yp );
    double d2 = distancia( x2, y2, xp, yp );

    zp = (double)z1 + (double)( z2 - z1 ) * d1 / ( d1 + d2 ); 

    return (int)zp;
}

bool between( int Ysup, int Yinf, int Y ){
    return ( Y >= Yinf && Y < Ysup ) ? true:false;
}

int interseccionX( int ax, int ay, int bx, int by, int y ){
    double delta = (double)(bx - ax)/(by - ay); 
    double diff = (double)y-ay;
    double interseccion = (diff*delta)+(double)ax;
    return (int)interseccion;
}

void polygonalFill(Poly poly){
    int hMAX = screen->h;
    int wMAX = screen->w;
    int x, z;
    double dz, ztmp;
    
    for( int Ybarrido = 0; Ybarrido < hMAX; Ybarrido++)/*Iterar sobre la pantalla*/
    {
        vector < pair< int, int > > intersecciones;
        for( int index = 0; index < poly.size()-1; index++ )/*Iterar sobre puntos del poligono*/
        {
            if( between( max(poly.Y[index], poly.Y[index+1]), min(poly.Y[index],poly.Y[index+1]), Ybarrido ) )
            {
                x = interseccionX( poly.X[index], poly.Y[index], poly.X[index+1], poly.Y[index+1], Ybarrido );
                z = distZ( poly.X[index], poly.Y[index], poly.X[index+1], poly.Y[index+1], x , Ybarrido , poly.Z[ index ], poly.Z[index+1]);                
                intersecciones.push_back( make_pair( x, z ) );/*GuardarInterseccion*/
            }
                
        }
        sort( intersecciones.begin(), intersecciones.end() );
        /* Hacer barrido de las intersecciones en x */
        for( int index = 0; index < intersecciones.size(); index+=2)
        {
            int Xinicio = intersecciones[ index ].first;
            int Xfin    = intersecciones[ index+1 ].first;

            for( int Xbarrido = Xinicio; Xbarrido < Xfin; Xbarrido++ )
            {
                z = distZ(Xinicio, Ybarrido , Xfin, Ybarrido, Xbarrido, Ybarrido, intersecciones[ index ].second, intersecciones[ index+1 ].second);

                if ( PROFUNDIDAD == true && isValid( Xbarrido, Ybarrido ) && z <= matProfundidad[ Xbarrido ][ Ybarrido ] )
                {
                    putpixel( Xbarrido, Ybarrido, poly.Color );
                    matProfundidad[ Xbarrido ][ Ybarrido ] = z;
                }
                else
                    putpixel( Xbarrido, Ybarrido, poly.Color );
            }
        }
    }
}

/* ============ Interseccion de color ============== */

int getColorIntersection(int x1, int y1, int x2, int y2, int xp, int yp, int c1, int c2)
{
    int c3, r1, r2, g1, g2, b1, b2, r3, g3, b3, aux;

    double d1 = distancia( x1, y1, xp, yp );
    double d2 = distancia( x2, y2, xp, yp );

    getRGB(r1,g1,b1,c1);
    getRGB(r2,g2,b2,c2);

    r3 = (double)r1 + (double)( r2 - r1 ) * d1 / ( d1 + d2 ); 
    b3 = (double)b1 + (double)( b2 - b1 ) * d1 / ( d1 + d2 );
    g3 = (double)g1 + (double)( g2 - g1 ) * d1 / ( d1 + d2 );
    
    c3 = b3 + g3 * 256 + r3 * 65536;

    return c3;
}

void interpolationColor(Poly poly){
    int hMAX = screen->h;
    int wMAX = screen->w;
    int col;
    int z;
     
    for( int Ybarrido = 0; Ybarrido < hMAX; Ybarrido++)/*Iterar sobre la pantalla*/
    {
        vector < pair< pair< int, int> , int > > intersecciones;
        for( int index = 0; index < poly.size()-1; index++ )/*Iterar sobre puntos del poligono*/
        {
            if( between( max(poly.Y[index], poly.Y[index+1]), min(poly.Y[index],poly.Y[index+1]), Ybarrido ) ) /*Existe Interseccion*/
            {
                int x,color;
                x = interseccionX( poly.X[index], poly.Y[index], poly.X[index+1], poly.Y[index+1], Ybarrido );
                z = distZ( poly.X[index], poly.Y[index], poly.X[index+1], poly.Y[index+1], x , Ybarrido , poly.Z[ index ], poly.Z[index+1]);
                color = getColorIntersection( poly.X[index], poly.Y[index], poly.X[index+1], poly.Y[index+1], x , Ybarrido , poly.pointColor[index], poly.pointColor[index+1]);
                intersecciones.push_back( make_pair( make_pair(x,color), z ) );
            }                
        }
        sort( intersecciones.begin(), intersecciones.end() );
       
        /* Hacer barrido de las intersecciones en x */
        for( int index = 0; index < intersecciones.size(); index+=2)
        {
            int Xinicio = intersecciones[ index ].first.first;
            int Xfin    = intersecciones[ index+1 ].first.first;

            for( int Xbarrido = Xinicio; Xbarrido < Xfin; Xbarrido++ )
            {
                z = distZ(Xinicio, Ybarrido , Xfin, Ybarrido, Xbarrido, Ybarrido, intersecciones[ index ].second, intersecciones[ index+1 ].second);

                if ( PROFUNDIDAD == true && isValid( Xbarrido, Ybarrido ) && z <= matProfundidad[ Xbarrido ][ Ybarrido ] )
                {
                    col = getColorIntersection(Xinicio, Ybarrido , Xfin, Ybarrido, Xbarrido, Ybarrido, intersecciones[ index ].first.second, intersecciones[ index+1 ].first.second);
                    matProfundidad[ Xbarrido ][ Ybarrido ] = z;
                    putpixel( Xbarrido, Ybarrido, col );
                }
                else putpixel( Xbarrido, Ybarrido, col );
                
            }
        }
    }
}

/* ============= Dibujar contorno de poligono*/

void drawPolygon(Poly poly)
{
    for(int i = 0; i < poly.size()-1; i++)
        drawLine( poly.X[i], poly.Y[i], poly.X[i+1], poly.Y[i+1], poly.Color );
}

void drawPolygon( Poly poly, string mode )
{
    if( mode == "wire" )
        drawPolygon( poly );
    else if( mode == "fill" )
        polygonalFill( poly );
    else if( mode == "interpolate" )
        interpolationColor( poly );
    else printf("No se encontró modo de relleno: \"%s\"\n", mode.c_str() );
}

/* ============= Fractal =============== */

void drawFractal( Poly poly, int n, int radio, int color)
{
    if( n < 2){
        polygonalFill( poly );
        /*
        for(int i=0; i<200; i++)
            SDL_Flip(screen);
        //*/
        return;
    }
    
    int rx,ry;

    poly.setColor(color);

    int x = poly.X[0];
    int y = poly.Y[0];

    rx = x;
    ry = y;

    poly.clear();
    poly.insert(x,y);
    poly.insert(x + radio, y);
    poly.insert(x + radio/2 , y + radio * sin(60*3.14159/180));
    poly.insert(x,y);
    drawFractal( poly, n-1, radio/2, color);

    x = rx + radio;

    poly.clear();
    poly.insert(x,y);
    poly.insert(x + radio, y);
    poly.insert(x + radio/2 , y + radio * sin(60*3.14159/180));
    poly.insert(x,y);
    drawFractal( poly, n-1, radio/2, color);

    x = rx + radio/2;
    y = ry + radio * sin(60*3.14159/180);
    
    poly.clear();
    poly.insert(x,y);
    poly.insert(x + radio, y);
    poly.insert(x + radio/2 , y + radio * sin(60*3.14159/180));
    poly.insert(x,y);
    drawFractal( poly, n-1, radio/2, color);
}

/* ============= Copo de nieve =============== */

void snow(float x1, float y1, float x2, float y2, int n, int ang, int color)
{
    if(n<1){
        drawLine(100+x1,353+y1,100+x2,353+y2, color);
        //SDL_Flip(screen);
        return;
    }

    float xp,yp,d;
    d=(sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) );

    xp=x1+(d/3)*cos(ang*3.1416/180);
    yp=y1+(d/3)*sin(ang*3.1416/180);

    snow(x1,y1,xp,yp,n-1,ang, color);

    x1=xp+(d/3)*cos((ang+60)*3.1416/180);
    y1=yp+(d/3)*sin((ang+60)*3.1416/180);

    snow(xp,yp,x1,y1,n-1,ang+60, color);

    xp=xp+(d/3)*cos(ang*3.1416/180);
    yp=yp+(d/3)*sin(ang*3.1416/180);

    snow(x1,y1,xp,yp,n-1,ang+300, color);
    snow(xp,yp,x2,y2,n-1,ang, color);

}

void drawsnow(int tam, int n, int color)
{
    snow(0,0,tam,0,n,0, color);
    snow(tam,0,tam/2,tam*sin(300*3.1416/180),n,240, color);
    snow(tam/2,tam*sin(300*3.1416/180),0,0,n,120, color);
}

/* ============== Seccion de Letras ===============*/

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
    cuadro.x = 10;  cuadro.y = winY - 150;  cuadro.w = winX - 20;   cuadro.h = 140;
    SDL_FillRect( screen, &cuadro, SDL_MapRGB(screen->format, 50, 50, 50 ) );
    
    int x = 30 , y = 100;

    for( int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            sprintf(tmp, "%.4lf", monster.mat[j][i]);
            s = tmp;
            drawString(s, x + i*80, y - j * 30, AZUL);
        }
}

void resetProfundidad()
{
    for (int i = 0; i < 600; i++)
        for (int j = 0; j < 800; j++)
            matProfundidad[i][j] = 2147483647;
        
}