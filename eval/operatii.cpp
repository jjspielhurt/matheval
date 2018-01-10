#include "operatii.h"
#define epsi 0.0001
#include <cmath>
#include <algorithm>



float adunare(float x, float y)
{
   if(x+y>=inf) return inf;
   if(x+y<=-inf) return -inf;
   return x+y;
}

float diferenta (float x, float y)
{
    if(x+y>=inf) return inf;
    if(x+y<=-inf) return -inf;
    return x-y;
}

float inmultire (float x, float y)
{
    if(x*y>=inf) return inf;
    if(x*y<=-inf) return -inf;
    return x*y;
}

float impartire (float x, float y)
{
    if(y==0) return inf;
    if(x/y>=inf) return inf;
    if(x/y<=-inf) return -inf;
    return x/y;
}

float mod (float x, float y)
{
    if(y==0) return inf;

}

float ridicare_la_putere (float x, float y)
{
    float v=pow(x,y);
    if(v>=inf) return inf;

        return v;
}

float tangenta (float x)
{
  if(abs(x-(PI/2)/PI - x)<epsi) return inf;
  return tan(x);

}

float cotangenta (float x)
{
    if(tangenta(x)==0) return inf;
    else return (1/tan(x));
}

float arcsin (float x)
{
    if(x>1 || x<-1) return inf;
    else return asin(x);
}

float arccos (float x)
{
    if(x>1 || x<-1) return inf;
    else return acos(x);
}

float logaritm (float x)
{
    if(x<=0) return -inf;
    else return log(x);
}

float radical (float x)
{
    if(x<0) return inf;
    else return sqrt(x);
}

float exponentiala (float x)
{
    if(exp(x)>=inf) return inf;
    else return exp(x);
}






