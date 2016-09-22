//#include "main.h"

#include "Lineas.cpp"
float Matriz[4][4];
void PoligonFill(int X[],int Y[],int vertices,int color);
void identidad()
{
	for(int i=0;i<4;i++)
	 for(int j=0;j<4;j++)
	  if(i==j)
	   Matriz[i][j]=1;
	  else
	   Matriz[i][j]=0;
}

void console(int x,int y)
{
	char s[100];
	int aux=x;
	y-=16;
	int vecx[4],vecy[4],posx,posy;
	
	vecx[0]=0;			vecy[0]=400;
	vecx[1]=0;			vecy[1]=300;//H
	vecx[2]=380;	    vecy[2]=300;
	vecx[3]=380;		vecy[3]=400;
	PoligonFill(vecx,vecy,4,0xfBFDf0);
	for(int i=0;i<4;i++)
	{
	 for(int j=0;j<4;j++)
	 {
	  sprintf(s,"%.4f",Matriz[i][j]);
	  kernin(x,y,s);
	  x+=100;
	 }
	 y-=25;
	 x=aux;
    }
}
void PoligonFill(int X[],int Y[],int vertices,int color)
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
	        	putpixel(j,y,color);
        }
    }	
}

void multiplica(float m[4][4])
{
	float res[4][4]={0};
	
	for(int i=0;i<4;i++)
	 for(int j=0;j<4;j++)
	  for(int ii=0;ii<4;ii++)
	   res[i][j]+=Matriz[i][ii]*m[ii][j];
	for(int i=0;i<4;i++)
	 for(int j=0;j<4;j++)
	  Matriz[i][j]=res[i][j];
}

void traslada(float tx,float ty,float tz)
{
	float m[4][4]={{1.0,0.0,0.0,tx},
	               {0.0,1.0,0.0,ty},
		           {0.0,0.0,1.0,tz},
		           {0.0,0.0,0.0,1.0}};
	multiplica(m);
}

void rota(float t,char c)
{
     float m[4][4]={ {1.0,0.0,0.0,0.0},
                     {0.0,1.0,0.0,0.0},
                     {0.0,0.0,1.0,0.0},
               	     {0.0,0.0,0.0,1.0}};
     switch(c)
     {
              case 'x':
                   m[1][1]=cos(t/57.29);
                   m[1][2]=-sin(t/57.29);
                   m[2][1]=sin(t/57.29);
                   m[2][2]=cos(t/57.29);
                   break;
              case 'z':
                   m[0][0]=cos(t/57.29);
                   m[0][1]=-sin(t/57.29);
                   m[1][0]=sin(t/57.29);
                   m[1][1]=cos(t/57.29);
                   break;
              case 'y'://rota normal en el eje
                   m[0][0]=cos(t/57.29);
                   m[0][2]=sin(t/57.29);
                   m[2][0]=-sin(t/57.29);
                   m[2][2]=cos(t/57.29);
                   break;
    }
    multiplica(m);
}

void escala(float sx,float sy,float sz)
{
     float m[4][4]={ {sx,0.0,0.0,0.0},
	                 {0.0,sy,0.0,0.0},
	                 {0.0,0.0,sz,0.0},
                     {0.0,0.0,0.0,1}
                   };
    multiplica(m);
}

void aplicaMatriz(int *x,int *y,int *z)
{
     int xx=*x;
	 int yy=*y;
     int zz=*z;
     *x=(int)(xx*Matriz[0][0]+yy*Matriz[0][1]+zz*Matriz[0][2]+Matriz[0][3]);
     *y=(int)(xx*Matriz[1][0]+yy*Matriz[1][1]+zz*Matriz[1][2]+Matriz[1][3]);
     *z=(int)(xx*Matriz[2][0]+yy*Matriz[2][1]+zz*Matriz[2][2]+Matriz[2][3]);
}

void caballera(int L,float th)
{
    float c[4][4]={ {1.0,0.0,L*cos(th),0.0},
                    {0.0,1.0,L*sin(th),0.0},
                    {0.0,0.0,0.0      ,0.0},
                    {0.0,0.0,0.0      ,1.0}
                  };
                  
    multiplica(c);
                  
}


