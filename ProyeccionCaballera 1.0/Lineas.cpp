//#include "main.h"
#include "primitivas.cpp"

void Bresenhamline(double x0, double y0, double x1, double y1, int color);

void dibuja3D(int vX[],int vY[],int Z,int numP,Uint32 color)
{
	int vectorX[20],vectorY[20],auxZ,vecX[10],vecY[10];
	for(int i=0;i<numP;i++)
	{
	 		vecX[i]=vectorX[i]=vX[i];
	 		vecY[i]=vectorY[i]=vY[i];
	 		auxZ=Z;
	 		aplicaMatriz(&vectorX[i],&vectorY[i],&auxZ);
	}
	traslada(0,0,-50);
	for(int i=0;i<numP;i++)
	{
            auxZ=Z;
            aplicaMatriz(&vecX[i],&vecY[i],&auxZ);
    }
	for(int i=0;i<numP;i++)
	{	
       Bresenhamline(vectorX[i],vectorY[i],vectorX[(i+1)%numP],vectorY[(i+1)%numP],0xff00ff);
       Bresenhamline(vecX[i],vecY[i],vecX[(i+1)%numP],vecY[(i+1)%numP],0xff00ff);       
       Bresenhamline(vectorX[i],vectorY[i],vecX[i],vecY[i],0xff00ff);
	}
	traslada(0,0,50); //para regresar
	
}

void dibujaFigura(Punto f[],int p)
{
     for(int i=0;i<p;i++)
           Bresenhamline(f[i].x,f[i].y,f[(i+1)%p].x,f[(i+1)%p].y,0xfff00f);
}

void Bresenhamline(double x0, double y0, double x1, double y1, int color)
{
    double dx,dy,sx,sy,err,e2,flag=1;
    
    
    dx=abs((int)x1-(int)x0);
    dy=abs(y1-y0);
    
    sx= x0 < x1 ? 1 : -1;
    sy= y0 < y1 ? 1 : -1;
    
    err=dx-dy;
    while(flag)
    {
        putpixel((int)x0,(int)y0,color);
        //putpixel((int)x0,(int)y0,color);
        
        if(x0==x1&&y0==y1)
            flag=0;
            
        e2=2*err;
        
        if(e2>-dy)
        {
            err-=dy;
            x0+=sx;
        }
        
        if(x0==x1&&y0==y1)
        {
            putpixel((int)x0,(int)y0,color);
            flag=0;
        }
        if(e2<dx)
        {
            err+=dx;
            y0+=sy;    
        }
    }                          
}


void arco(int xp,int yp,int radio,int t1,int t2,Uint32 color)
{
    int x,xx,y,yy,t;
    for(int i=t1;i<=t2;i+=2)
	{
              x= (int)(radio*cos( (float)i/57.29 ) );
              y= (int)(radio*sin( (float)i/57.29) ) ;
              xx= (int)(radio*cos( (float)t/57.29 ) );
              yy= (int)(radio*sin( (float)t/57.29) ) ;
             Bresenhamline(x+xp,y+yp,xx+xp,yy+yp,color);
              t=i;
    }
}
void espiral(int x,int y,double radio,int angI,int vueltas,Uint32 color)
{   
    int x1,x2,y1,y2,t=angI;
    
    for(int angulo=angI;angulo<vueltas*360+angI;angulo+=2)
    {
            x1= (int)(radio*cos( (float)angulo/57.29 ) );
            y1= (int)(radio*sin( (float)angulo/57.29) ) ;
            x2= (int)(radio*cos( (float)t/57.29 ) );
            y2= (int)(radio*sin( (float)t/57.29) ) ;

            Bresenhamline(x+x1,y+y1,x+x2,y+y2,color);
            t=angulo;
            radio+=0.06;
    }
}

void circulo(int x,int y,int radio,Uint32 color)
{
    int x1,x2,y1,y2,t=0;
    for(int i=0;i<360;i+=2)
    {
            x1= (int)(radio*cos( (float)i/57.29 ) );
            y1= (int)(radio*sin( (float)i/57.29) ) ;
            putpixel(x+x1,y+y1,color);
    }
}
