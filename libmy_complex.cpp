#include "my_complex.h"

bool operator==(const complex& x, const complex& y) {
  if ((x.re==y.re) && (x.im==y.im)) { return 1;}
  else {return 0;}
}

bool operator!=(const complex& x, const complex& y) {
  if ((x.re!=y.re) || (x.im!=y.im)) { return 1;}
  else {return 0;}
}

bool around(complex x, complex y) {
  double a,b;
  a=x.re-y.re;
  b=x.im-y.im;
  if ((a>-0.00001)&&(a<0.00001)&&(b>-0.00001)&&(b<0.00001)){return 1;}
  else {return 0;}
}

complex comp(complex a) {
  complex b;
  b.re=a.re;
  b.im=-a.im;
  return b;
}

complex operator+(const complex& x, const complex& y) {
  complex z;
  z.re=x.re+y.re;
  z.im=x.im+y.im;
  return z;
}

complex operator-(const complex& x,const complex& y) {
  complex z;
  z.re=x.re-y.re;
  z.im=x.im-y.im;
  return z;
}

complex operator*(const complex& x,const complex& y) {
  complex z;
  z.re=x.re*y.re-x.im*y.im;
  z.im=x.re*y.im+x.im*y.re;
  return z;
}

polar_complex operator*(const polar_complex& x, const polar_complex& y) {
  polar_complex z;
  z.mod=x.mod*y.mod;
  z.arg=x.arg+y.arg;
  return z;
}

complex operator/(const complex& x,const complex& y) {
  complex z;
  double down;
  down=y.re*y.re+y.im*y.im;
  z.re=(x.re*y.re+x.im*y.im)/down;
  z.im=(x.im*y.re-x.re*y.im)/down;
  return z;
}

complex pow(complex x,int y) {
  if (y<0){return pow(1/x,-y);}
  else if (y==0){return 1;}
  else if (y==1){return x;}
  else {
    complex z=1;
    unsigned int i;
    for (i=1;i<=y;i++) {
      z=z*x;
    }
    return z;
  }
}

complex log(polar_complex x) {
  complex z;
  z.re=log(x.mod);
  z.im=x.arg;
  return z;
}

complex exp(complex x) {
  complex z;
  z.re=exp(x.re)*cos(x.im);
  z.im=exp(x.re)*sin(x.im);
  return z;
}

complex pow(complex x,double y) {
  return exp(y*log(x));
}

complex pow(complex x,complex y) {
  return exp(y*log(x));
}

double abs(complex x) {
  return sqrt(x.re*x.re+x.im*x.im);
}
