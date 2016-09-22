#include "main.h"
#include "string.h"
#include <math.h>
#include <stdio.h>


//================Prptotipos de funciones===================

void dubujaLetra(int X, int Y, char c  );
void dibujaPalabra(int x,int y,char *palabra);

//==================Variables globales======================

float mostro[4][4]={{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0}};
int COLOR = 0xffffff;
int Colores[10]={0xFF0000,0x00FF00,0x0000FF,0xFFFF00 ,0xCCEEFF ,0x006400,0xFF4500,0xF4A460,0xAACCff,0xCC00CC};
int contaCol=0;
int Relleno=0xffffff;

//========================Bresenham===========================
 
void Bresenham( int x0, int y0, int x1, int y1 ){
	int dx = abs( x1-x0 );
	int dy = abs( y1-y0 );	
	int sy, sx, error=dx-dy, e2;
	
	if( x0 < x1 )		sx = 1;
	else				sx = -1;
	if( y0 < y1 ) 		sy = 1;
	else 				sy = -1;
	
	while( true ){
		if( x0 >= 0 && x0 < screen->w && y0>=0 && y0<screen->h ) 
			putpixel( x0, y0, 0xffffff );
		if( x0 == x1 && y0 == y1 ) 
			break;
		e2 = 2*error;
		
		if( e2 > -dy ){
			error = error - dy;
			x0 = x0 + sx;
		}
		if( x0 == x1 && y0 == y1 ){
			if( x0 >= 0 && x0 < screen->w && y0>=0 && y0<screen->h ) putpixel( x0, y0 , 0xffffff );
			break;
		}
		if( e2 < dx ){
			error = error + dx;
			y0 = y0 + sy;
		}
	}	
}

//======================Relleno Poligonal=========================

void RellenoPoligonal(int X[],int Y[],int vertices,int color)
{
	int nodosX[vertices];
	int i,nodos,j,swap;;
	
	for(int y=1;y<winY;y++)
	{
		j=vertices-1;
		nodos=0;
		for(i=0;i<vertices;i++){
			
			if (Y[i]<y && Y[j]>=y || Y[j]<y && Y[i]>=y){
    	    	nodosX[nodos++]=(int)(X[i]+(y-Y[i])*(X[j]-X[i])/(Y[j]-Y[i])); 
			}	
			j=i;
		}
		i=0;
		while (i<nodos-1){
			
        	if (nodosX[i]>nodosX[i+1]){
	        	swap=nodosX[i];
	 			nodosX[i]=nodosX[i+1];
		    	nodosX[i+1]=swap;
	        	if (i)
	         		i--;
	      	}
          	else
           		i++;
        }

        for(i=0;i<nodos;i++){
			
			if(nodosX[i]>=winX)
				nodosX[i]=winX;
			else if(nodosX[i]<0)
				nodosX[i]=0;
        }
  
        for (i=0; i<nodos-1; i+=2){
			
	    	for (j=nodosX[i]; j<nodosX[i+1]; j++) 
	        	putpixel(j,y,Relleno);
        }
    }	
}

//=====================MatrizIdentidad======================

void matrizIdentidad()
{
	int i,j;
 	for(i=0; i<4; i++)
   		for(j=0; j<4; j++)
    		if(i==j)
      			mostro[i][j]=1.0;
    		else
      			mostro[i][j]=0.0;
}
 
//====================MuestraMatriz========================

void muestraMatriz(int x, int y)
{
   	int i,j,xi=x,yi=y;
   	for(i=0; i<4; i++){
		
		for(j=0; j<4; j++){
			
      		char c[12];
      		sprintf(c, "%f", mostro[i][j]);
      		dibujaPalabra( x , y , c );
      		x+=90;
    	}
  		y-=20;
  		x=xi;
  	}
}

//===================MultiplicaMatriz=====================

void multiplicaMatriz(float matrix2[][4])
{
  	float maux[4][4],suma=0,a,b;
  	int con=0,i,j,k;
  	for(i=0;i<4;i++){
		
    	con=0;
    	for(k=0;k<4;k++){
			
      		for(j=0;j<4;j++){
				
            	a=mostro[i][j];
            	b=matrix2[j][k];
            	suma=suma+(a*b);
          	}
      //if(suma==-0.000158 || suma==0.000158)
          //suma=0.0;
      		maux[i][con]=suma;
      		con++;
      		suma=0;
     	}
 	}
 
 	for(int i=0; i<4; i++)
   		for(int j=0; j<4; j++)
     		mostro[i][j]=maux[i][j];
}

//======================Traslacion=========================

void traslacion(int tx, int ty,int tz)
{
 float maux[4][4]={{1.0,0.0,0.0,tx},{0.0,1.0,0.0,ty},{0.0,0.0,1.0,tz},{0.0,0.0,0.0,1.0}};
 multiplicaMatriz(maux);
}

//========================Rotacion==========================

void rotacionZ(float teta)
{
  float maux[4][4]={{cos((teta)/57.29) ,-sin((teta)/57.29) ,0.0,0.0} ,{sin((teta)/57.29),cos((teta)/57.29),0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}};
  multiplicaMatriz(maux);  //maux[0][0]=34.0;
}

void rotacionX(float teta)
{
  float maux[4][4]={{1.0,0.0,0.0,0.0} ,{0.0,cos((teta)/57.29) ,-sin((teta)/57.29) ,0.0},{0.0,sin((teta)/57.29),cos((teta)/57.29),0.0},{0.0,0.0,0.0,1.0}};
  multiplicaMatriz(maux);  //maux[0][0]=34.0;
}

void rotacionY(float teta)
{
  float maux[4][4]={{cos((teta)/57.29),0.0,sin((teta)/57.29),0.0} ,{0.0, 1.0 ,0.0,0.0},{-sin((teta)/57.29),0.0,cos((teta)/57.29),0.0},{0.0,0.0,0.0,1.0}};
  multiplicaMatriz(maux);  //maux[0][0]=34.0;
}
//======================Escalamiento=======================

void escalamiento(float sx, float sy,float sz)
{
 float maux[4][4]={{sx,0.0 ,0.0,0.0} ,{0.0,sy,0.0,0.0},{0.0,0.0,sz,0.0},{0.0,0.0,0.0,1.0}};
 multiplicaMatriz(maux);
}

//=====================Aplica Matriz========================

void AplicaMatriz(float x,float y,int z,int *xi,int *yi,int *zi,int i){
    
	xi[i]=(int)(mostro[0][0]*x + mostro[0][1]*y + mostro[0][2]*z+ mostro[0][3]*1);
	yi[i]=(int)(mostro[1][0]*x + mostro[1][1]*y + mostro[1][2]*z+ mostro[1][3]*1);
	zi[i]=(int)(mostro[2][0]*x + mostro[2][1]*y + mostro[2][2]*z+ mostro[2][3]*1);
}
//=====================Aplica PROYECCION========================

void AplicaProyeccion(float x,float y,int z,int *xi,int *yi,int *zi,int i,float teta){
    
	xi[i]=(int)(mostro2[0][0]*x + mostro2[0][1]*y + mostro2[0][2]*z*L1*cos((teta)/57.29 ) + mostro2[0][3]*1);
	yi[i]=(int)(mostro2[1][0]*x + mostro2[1][1]*y + mostro2[1][2]*z*L1*sin((teta)/57.29)  + mostro2[1][3]*1);
	zi[i]=(int)(mostro2[2][0]*x + mostro2[2][1]*y + mostro2[2][2]*z                       + mostro2[2][3]*1);
}

//======================Dibuja Casa==========================

void dibujaCasa()
{	
	int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=0;		Y[1]=100;      Z[1]=0;
    X[2]=50;	Y[2]=150;      Z[2]=0;
    X[3]=100;	Y[3]=100;      Z[3]=0;
    X[4]=100;	Y[4]=0;        Z[4]=0;
    X[5]=0;		Y[5]=0;        Z[5]=0;
    
    for(int i=0;i<6;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
		AplicaProyeccion(X[i],Y[i],Z[i],X,Y,Z,i,90);
	}

    for(int i=0; i<5 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,5,Relleno);
    contaCol++;
    if(contaCol>9)
    	contaCol=0;
}
void dibujaTriangulo2()//Tiene el vertice de arriba hacia atras Z
{	
	int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=400;	Y[1]=0;        Z[1]=0;
    X[2]=200;	Y[2]=347;      Z[2]=300;
    //X[0]=0;		Y[0]=0;        Z[0]=0;
    
   for(int i=0;i<3;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
	}
  
    for(int i=0; i<2 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,3,Relleno);
}
void dibujaTriangulo()//Vertice hacia adelante z
{	// Relleno=0xff00ff;
	int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=400;	Y[1]=0;        Z[1]=0;
    X[2]=200;	Y[2]=347;      Z[2]=0;
    //X[0]=0;		Y[0]=0;        Z[0]=0;
    
   for(int i=0;i<3;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
	}
  
    for(int i=0; i<2 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,3,Relleno);
}
void dibujaCasa3D()
{
  Relleno=0x8000FF;
  dibujaCasa();
  traslacion(0,0,100);
  Relleno=0x3ADF00;
  dibujaCasa();
  
}

void cuadro(){
   int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=100;	Y[1]=0;        Z[1]=0;
    X[2]=100;	 Y[2]=100;      Z[2]=0;
    X[3]=0;	Y[3]=100;      Z[3]=0;
    //X[0]=0;		Y[0]=0;        Z[0]=0;
    
   for(int i=0;i<4;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
	}
  
    for(int i=0; i<3 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,4,Relleno);
}

void cuadro2(){//para el triangulo
   int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=400;	Y[1]=0;        Z[1]=0;
    X[2]=400;	Y[2]=400;      Z[2]=0;
    X[3]=0;	    Y[3]=400;      Z[3]=0;
    //X[0]=0;		Y[0]=0;        Z[0]=0;
    
   for(int i=0;i<4;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
	}
  
    for(int i=0; i<3 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,4,Relleno);
}
void rectangulo(){
   int X[10],Y[10],Z[10];
    
	X[0]=0;		Y[0]=0;        Z[0]=0;
    X[1]=100;	Y[1]=0;        Z[1]=0;
    X[2]=100;	Y[2]=71;      Z[2]=0;
    X[3]=0;		Y[3]=71;      Z[3]=0;
    //X[0]=0;		Y[0]=0;        Z[0]=0;
    
   for(int i=0;i<4;i++){
		AplicaMatriz(X[i],Y[i],Z[i],X,Y,Z,i);
	}
  
    for(int i=0; i<3 ;i++)
     Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
    
    RellenoPoligonal(X,Y,4,Relleno);
}
void dibujaCasa3D2()
{  Relleno=0xff00ff;
    rotacionY(90);
    cuadro();
   Relleno=0xffff00;
 // Relleno=0xff00ff;
  traslacion(0,0,100);
  cuadro();
  rotacionX(270);
  Relleno=0x00ccaa;
  cuadro();
  
  rotacionX(90);
   
  rotacionY(270);
   traslacion(-100,0,0);
   //rotacionY(180);
  //rotacionX(90);
  //matrizIdentidad();*/
  Relleno=0x58FAF4;
  dibujaCasa();
 traslacion(0,0,-100);
  Relleno=0x3ADF00;
  dibujaCasa();
  Relleno=0x0000ff;
  traslacion(0,100,0);
  rotacionY(270);
  rotacionX(315);
  rectangulo();
  //traslacion(0,100,0);
  rotacionX(45);
  traslacion(0,0,-100);
  rotacionX(45);
  Relleno=0x0000ff;
  rectangulo();
  
}
void dibujaTriangulo3D()
{
  Relleno=0x8000FF;
  dibujaTriangulo();
  traslacion(0,0,100);
  Relleno=0x3ADF00;
  dibujaTriangulo();
}
void dibujaTetraedro(){
     Relleno=0xBDBDBD;
     rotacionX(270);
     cuadro2();
     
     rotacionX(90); 
     
     traslacion(0,0,-400);
     rotacionX(35);
     Relleno=0x86B404;
     dibujaTriangulo(); 
     
     rotacionX(325);
     traslacion(0,0,400);
     
     rotacionX(325);
     Relleno=0xF5A9BC;
     dibujaTriangulo();
     
     //rotacionX(20);
     /*traslacion(400,0,0);
     rotacionY(270);*/
     rotacionX(35);
     
     traslacion(400,0,0);
     rotacionY(90);
     rotacionX(325);
     Relleno=0xFF0000;
     dibujaTriangulo();
     
     rotacionX(35);
     rotacionY(270);
     traslacion(-400,0,0);
     
     rotacionY(90);
     rotacionX(35);
     Relleno=0xFFFF00;
     dibujaTriangulo();
     }
     
 void dibujaCubo(){
      Relleno=0xFF0000;
      cuadro();
      
      rotacionX(270);
      Relleno=0xFF8000;
      cuadro();
      
      rotacionX(90);
      
      rotacionX(270);
      traslacion(0,0,100);
      Relleno=0x5F04B4;
      cuadro();
      
      traslacion(0,0,-100);
      rotacionX(90);
      Relleno=0x01DF01; //
      traslacion(100,0,0);
      rotacionY(90);
      cuadro();
      
      rotacionY(270);
      traslacion(-100,0,0);
      
      rotacionY(90);
      Relleno=0x0174DF; //Verde
      cuadro();
      
      rotacionY(270);
      Relleno=0xFFFF00; //Amarrillo
      traslacion(0,0,-100);
      cuadro();
      } 
      
//---------------proyeccion caballera------------------------------------------
void caballera(float phi,int L){



proyect[ 2 ][ 2 ] = 0;
proyect[  0 ] [ 2 ] =  0.5;//cos(phi/57.29) * L;
proyect[ 1 ] [ 2 ] = 0.5;//;sin(phi/57.29) * L;


}
// poner x ,y ,z punto de fuga
struct punto_fuga{
       int xpf;
       int ypf;
       int zpf;
       
       };
typedef struct punto_fuga pf;
void proyeccion_caballera( float px,float py,float pz, int *npx, int *npy, int *npz, pf npf)
{
       int nnpx = (int)( (proyect[ 0 ][ 0 ]* px  ) + ( proyect[ 0 ][ 1 ]* py )+ ( proyect[ 0][ 2 ]* pz ) +proyect[ 0 ][ 3 ] );
       int nnpy = (int)( (proyect[ 1 ][ 0 ]* px  ) + ( proyect[ 1 ][ 1 ]* py )+ ( proyect[ 1][ 2 ]* pz ) +proyect[ 1 ][ 3 ]  );
       *npz =     (int)( (proyect[ 2 ][ 0 ]* px  ) + ( proyect[ 2 ][ 1 ]* py )+ ( proyect[ 2][ 2 ]* pz ) +proyect[ 2 ][ 3 ]  );       


// ingresamos punto de fuga

*npx = nnpx * ( 1-*npz/npf.zpf  ) + npf.xpf * ( *npz/npf.zpf );
*npy = nnpy * ( *npz/npf.zpf     ) + npf.ypf * ( 1- *npz/npf.zpf );


     }     
//----------------------------------------------------------casita3D

void aplicamat( int px,int  py,int pz, int *npx, int *npy, int *npz){
       *npx = (int)( (matrizGlobal3D[ 0 ][ 0 ]* px  ) + ( matrizGlobal3D[ 0 ][ 1 ]* py )+ ( matrizGlobal3D[ 0][ 2 ]* pz ) +matrizGlobal3D[ 0 ][ 3 ] );
       *npy = (int)( (matrizGlobal3D[ 1 ][ 0 ]* px  ) + ( matrizGlobal3D[ 1 ][ 1 ]* py )+ ( matrizGlobal3D[ 1][ 2 ]* pz ) +matrizGlobal3D[ 1 ][ 3 ]  );
       *npz = (int)( (matrizGlobal3D[ 2 ][ 0 ]* px  ) + ( matrizGlobal3D[ 2 ][ 1 ]* py )+ ( matrizGlobal3D[ 2][ 2 ]* pz ) +matrizGlobal3D[ 2 ][ 3 ]  );       

     }        
//======================Dibuja Estrella=======================
/*void dibujaEstrella(){
	int X[17],Y[17];
    
	X[0]=0;		Y[0]=0;
    X[1]=20;	Y[1]=40;
    X[2]=0;	Y[2]=50;
    X[3]=20;	Y[3]=60;
    X[4]=0;		Y[4]=100;
    X[5]=40;		Y[5]=80;
    X[6]=50;		Y[6]=100;
    X[7]=60;	Y[7]=80;
    X[8]=100;	Y[8]=100;
    X[9]=80;	Y[9]=60;
    X[10]=100;		Y[10]=50;
    X[11]=80;		Y[11]=40;
    X[12]=100;		Y[12]=0;
    X[13]=60;	Y[13]=20;
    X[14]=50;	Y[14]=0;
    X[15]=40;	Y[15]=20;
    X[16]=0;		Y[16]=0;
    for(int i=0;i<17;i++){
		AplicaMatriz(X[i],Y[i],X,Y,i);
	}
	for(int i=0; i<16 ;i++)
     	Bresenham(X[i],Y[i],X[i+1],Y[i+1]);
     
    RellenoPoligonal(X,Y,16,Colores[contaCol]);
    contaCol++;
    if(contaCol>9)
    	contaCol=0;
}*/
