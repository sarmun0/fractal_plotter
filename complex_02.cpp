#include <cstdio>
#include "my_complex.h"
#include <gtk/gtk.h>
#include <thread>
#define remax 2
#define immax 2

complex f(complex a,complex u) {
  complex z;
  z=pow(a,2)+u;
  return z;
}

void loop(complex a,complex u,unsigned int l,unsigned int* c) {
  *c=0;
  while ((*c<=l)&&(abs(a)*abs(a)<4)) {
    (*c)++;
    a=f(a,u);
  }
}

void barify(GtkWidget* bar,double percent) {
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(bar),(gdouble)percent);
  g_print("%.15lg\n",percent);
}

void julify(unsigned int Sx,unsigned int Sy,unsigned int l,complex u,FILE* fi,GtkWidget* bar){
  complex a;
  unsigned int i,j;
  static unsigned int c;
  char p=0,cp=0;
  fprintf(fi,"P4\n%d %d\n",Sx,Sy);
  for (i=1;i<=Sy;i++) {
    for (j=1;j<=Sx;j++) {
      c=0;
      a.re=remax*(2*(double)j/Sx-1);
      a.im=immax*(1-2*(double)i/Sy);
//      while ((c<=l)&&(a.re*a.re+a.im*a.im<4)) {
//        c++;
//        a=f(a,u);
//      }
      std::thread one (loop,a,u,l,&c);
      std::thread two (barify,bar,(double)((i-1)*Sx+j)/(Sy*Sx));
      one.join();
      two.join();
      cp++;
      if (c<=l){p++;}
      if (cp==8){fputc(p,fi);cp=0;p=0;}else{p=p<<1;}
    }
  }
}

void click(GtkWidget *button,GtkWidget **b){
  unsigned int sx,sy,iters;
  sx=atoi(gtk_entry_get_text(GTK_ENTRY(b[0])));
  sy=atoi(gtk_entry_get_text(GTK_ENTRY(b[1])));
  iters=atoi(gtk_entry_get_text(GTK_ENTRY(b[4])));
  complex z;
  z.re=atof(gtk_entry_get_text(GTK_ENTRY(b[2])));
  z.im=atof(gtk_entry_get_text(GTK_ENTRY(b[3])));
  FILE *fi;
  fi=fopen(gtk_entry_get_text(GTK_ENTRY(b[5])),"w");
  julify(sx,sy,iters,z,fi,b[6]);
  fclose(fi);
}


void activate(GtkApplication* app,gpointer user_data){
  GtkWidget *window,*button,*grid,*edit[6],*label[6],*bar;
  static GtkWidget *nums[7];
//make a window
  window=gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window),"Hello there!");
  gtk_window_set_default_size(GTK_WINDOW(window),400,200);
//make a grid
  grid=gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window),grid);
//make entries
  edit[0]=gtk_entry_new();
  edit[1]=gtk_entry_new();
  edit[2]=gtk_entry_new();
  edit[3]=gtk_entry_new();
  edit[4]=gtk_entry_new();
  edit[5]=gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid),edit[0],1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),edit[1],3,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),edit[2],1,1,1,1);
  gtk_grid_attach(GTK_GRID(grid),edit[3],3,1,1,1);
  gtk_grid_attach(GTK_GRID(grid),edit[4],1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid),edit[5],3,2,1,1);
  nums[0]=edit[0];
  nums[1]=edit[1];
  nums[2]=edit[2];
  nums[3]=edit[3];
  nums[4]=edit[4];
  nums[5]=edit[5];
//make a label
  label[0]=gtk_label_new("Rx");
  gtk_grid_attach(GTK_GRID(grid),label[0],0,0,1,1);
  label[1]=gtk_label_new("Ry");
  gtk_grid_attach(GTK_GRID(grid),label[1],2,0,1,1);
  label[2]=gtk_label_new("Re(c)=");
  gtk_grid_attach(GTK_GRID(grid),label[2],0,1,1,1);
  label[3]=gtk_label_new("Im(c)=");
  gtk_grid_attach(GTK_GRID(grid),label[3],2,1,1,1);
  label[4]=gtk_label_new("Iters");
  gtk_grid_attach(GTK_GRID(grid),label[4],0,2,1,1);
  label[5]=gtk_label_new("Filename");
  gtk_grid_attach(GTK_GRID(grid),label[5],2,2,1,1);
//make a progress bar
  bar=gtk_progress_bar_new();
  gtk_grid_attach(GTK_GRID(grid),bar,0,4,4,2);
  nums[6]=bar;
//  nums[5]=label;
//make a button
  button=gtk_button_new_with_label("Draw!");
  g_signal_connect(button,"clicked",G_CALLBACK(click),nums);
  gtk_grid_attach(GTK_GRID(grid),button,0,3,4,1);
//show it all
  gtk_widget_show_all(window);
}

int main(int argc, char **argv){
  GtkApplication *app;
  int status;
  app=gtk_application_new("sarmun.complex.app",G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  status=g_application_run(G_APPLICATION(app),argc,argv);
  g_object_unref(app);
  return status;
}
