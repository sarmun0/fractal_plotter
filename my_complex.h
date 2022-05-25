#include <cmath>

typedef struct complex {
  double re,im;
  complex(){};
  complex(double x){
    re=x;
    im=0;
  }
  complex(double x,double y){
    re=x;
    im=y;
  }
} complex;

typedef struct polar_complex {
  double mod,arg;
  polar_complex(){};
  polar_complex(complex z){
    mod=sqrt(z.re*z.re+z.im*z.im);
    arg=atan(z.im/z.re);
  }
  polar_complex(double x,double y){
    mod=x;
    arg=y;
  }
  operator complex() {
    complex z;
    z.re=mod*cos(arg);
    z.im=mod*sin(arg);
    return z;
  }
} polar_complex;

bool operator==(const complex& x, const complex& y);
bool operator!=(const complex& x, const complex& y);
bool around(complex x, complex y);
complex comp(complex a);
complex operator+(const complex& x, const complex& y);
complex operator-(const complex& x,const complex& y);
complex operator*(const complex& x,const complex& y);
polar_complex operator*(const polar_complex& x,const polar_complex& y);
complex operator/(const complex& x,const complex& y);
complex pow(complex x,int y);
complex log(polar_complex x);
complex exp(complex x);
complex pow(complex x,double y);
complex pow(complex x,complex y);
double abs(complex x);
