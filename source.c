
// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right
//              Up Arrow    - Rotate Up
//              Down Arrow  - Rotate Down     
 
// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include <time.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#define maxsize 4
#define winrate 12

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
int matrix[maxsize][maxsize][maxsize] ;
Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
Pixmap                  pixmap;
int                     pixmap_width = 128, pixmap_height = 128;
GC                      gc;
XImage                  *xim[11];
GLuint                  texture_id;
XFontStruct * font;



// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------

static void set_font_size ( int f_size)
{
    const char * fontname = "-*-helvetica-*-r-*-*-40-*-*-*-*-*-*-*";
    font = XLoadQueryFont (dpy, fontname);
    
    /* If the font could not be loaded, revert to the "fixed" font. */
    if (! font) {
        fprintf (stderr, "unable to load font %s: using fixed\n", fontname);
        font = XLoadQueryFont (dpy, "fixed");
    }
    XSetFont (dpy, gc, font->fid);
}



void create_texture( int nomber){
    set_font_size(40);


 pixmap = XCreatePixmap(dpy, root, pixmap_width, pixmap_height, vi->depth);
 


 XFillRectangle(dpy, pixmap, gc, 0, 0, pixmap_width, pixmap_height);

 //XSetForeground(dpy, gc, 0x000000);
 //XFillArc(dpy, pixmap, gc, 15, 25, 50, 50, 0, 360*64);
  // Font font;
  // font = XLoadFont(dpy, "6x9");
  //  XSetFont(dpy, glc,  font);
/*
char* texture_text;
 switch(nomber){
    case 1:
    break;
 }
*/
 XSetForeground(dpy, gc, 0xffffff);
 XDrawString(dpy, pixmap, gc, 4, pixmap_height-4, "2048", strlen("2048"));

// XSetForeground(dpy, gc, 0xff0000);
 //XFillRectangle(dpy, pixmap, gc, 75, 75, 45, 35);

 XFlush(dpy);
 xim[0] = XGetImage(dpy, pixmap, 0, 0, pixmap_width, pixmap_height, AllPlanes, ZPixmap);

 if(xim == NULL) {
        printf("\n\tximage could not be created.\n\n"); }

 /*     CREATE TEXTURE FROM PIXMAP */



    glEnable(GL_TEXTURE_2D);
 glGenTextures(1, &texture_id);
 glBindTexture(GL_TEXTURE_2D, texture_id);
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}







/*
enum Direction{
   up,
   down,
   right,
   left,
   to,
   from
};*/

/*
int turn( Direction ){
   if( Direction == 0);
}


int turn_x( int rev){
   int ret = 0;
   for(int x=1 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            if( matrix[x-1][y][z] ==  )
         }
      }
   }
}
*/







int step( int dir, int pos);
void display();
void specialKeys();
void newcube();


int step( int dir, int pos){
  int ret = 0;
  int delta;
  if(dir%2) delta=-1;
  else delta=1;
   switch(dir/2){
      case 0:
      
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            if(matrix[pos][y][z]!=0){
               if(matrix[pos+delta][y][z]==0){
                  matrix[pos+delta][y][z]=matrix[pos][y][z];
                  matrix[pos][y][z]=0;
                  ret++;               }
            else if(matrix[pos+delta][y][z]==matrix[pos][y][z]){
               matrix[pos+delta][y][z]++;
               matrix[pos][y][z]=0;
               ret++;
               }
            }
         }
      }
      break;
      case 1:
      
      for(int x=0; x<maxsize; x++){
         for(int z=0; z<maxsize; z++){
            if(matrix[x][pos][z]!=0){
               if(matrix[x][pos+delta][z]==0){
                  matrix[x][pos+delta][z]=matrix[x][pos][z];
                  matrix[x][pos][z]=0;
                  ret++;               }
            else if(matrix[x][pos+delta][z]==matrix[x][pos][z]){
               matrix[x][pos+delta][z]++;
               matrix[x][pos][z]=0;
               ret++;
               }
            }
         }
      }
      break;
      case 2:
      
      for(int x=0; x<maxsize; x++){
         for(int y=0; y<maxsize; y++){
            if(matrix[x][y][pos]!=0){
               if(matrix[x][y][pos+delta]==0){
                  matrix[x][y][pos+delta]=matrix[x][y][pos];
                  matrix[x][y][pos]=0;
                  ret++;               }
            else if(matrix[x][y][pos+delta]==matrix[x][y][pos]){
               matrix[x][y][pos+delta]++;
               matrix[x][y][pos]=0;
               ret++;
               }
            }
         }
      }
      break;
      
      
      }
   return(ret);

   
}


int turn(int dir){
   int ret =0;
   int lastret=-1;
   if(dir%2)
   while (ret-lastret){
   {
       lastret=ret;
      for(int i=1; i<maxsize; i++)
      ret+=step(dir,i);
   }
   }
   else
   while (ret-lastret){
   {
       lastret=ret;
       for(int i=maxsize-2; i>=0; i--)
      ret+=step(dir,i);
   }
   }


   if(ret)newcube();
   return(ret);
}

void newcube(){
   int x,y,z;
   do{
      x = rand() % maxsize;
      y = rand() % maxsize;
      z = rand() % maxsize; 
   }while(matrix[x][y][z]);
   matrix[x][y][z]=1;

}




void drawcube( double dx, double dy, double dz, double size ){
   glBegin(GL_POLYGON);
 
  //glColor3f( 1.0, 0.0, 0.0 );
  glTexCoord2f(0.0, 0.0);     glVertex3f(  size + dx , -size + dy , -size + dz  );      // P1 is red
  //glColor3f( 0.0, 1.0, 0.0 );
  glTexCoord2f(1.0, 0.0);     glVertex3f(  size + dx ,  size + dy , -size + dz  );      // P2 is green
  //glColor3f( 0.0, 0.0, 1.0 );
  glTexCoord2f(1.0, 1.0);     glVertex3f( -size + dx ,  size + dy , -size + dz  );      // P3 is blue
  //glColor3f( 1.0, 0.0, 1.0 );
  glTexCoord2f(0.0, 1.0);     glVertex3f( -size + dx , -size + dy , -size + dz  );      // P4 is purple
 
  glEnd();
  
  

  // White side - BACK
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  size + dx , -size + dy , size + dz  );
  glVertex3f(  size + dx ,  size + dy , size + dz  );
  glVertex3f( -size + dx ,  size + dy , size + dz  );
  glVertex3f( -size + dx , -size + dy , size + dz  );
  glEnd();
 
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( size + dx , -size + dy , -size + dz  );
  glVertex3f( size + dx ,  size + dy , -size + dz  );
  glVertex3f( size + dx ,  size + dy ,  size + dz  );
  glVertex3f( size + dx , -size + dy ,  size + dz  );
  glEnd();
 
  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -size + dx , -size + dy ,  size + dz  );
  glVertex3f( -size + dx ,  size + dy ,  size + dz  );
  glVertex3f( -size + dx ,  size + dy , -size + dz  );
  glVertex3f( -size + dx , -size + dy , -size + dz  );
  glEnd();
 
  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  size + dx ,  size + dy ,  size + dz  );
  glVertex3f(  size + dx ,  size + dy , -size + dz  );
  glVertex3f( -size + dx ,  size + dy , -size + dz  );
  glVertex3f( -size + dx ,  size + dy ,  size + dz  );
  glEnd();
 
  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  size + dx , -size + dy , -size + dz  );
  glVertex3f(  size + dx , -size + dy ,  size + dz  );
  glVertex3f( -size + dx , -size + dy ,  size + dz  );
  glVertex3f( -size + dx , -size + dy , -size + dz  );
  glEnd();
 
}
 


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity();
 
  // Other Transformations
  // glTranslatef( 0.1, 0.0, 0.0 );      // Not included
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included
 
  // Rotate when user changes rotate_x and rotate_y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
 
  // Other Transformations
  // glScalef( 2.0, 2.0, 0.0 );          // Not included
 //  drawcube(0.2,0.2,0.2, 0.5);
 //   drawcube(-0.2,-0.2,-0.2, 0.4);

   for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            if(matrix[x][y][z]!=0 && matrix[x][y][z]<winrate ){
            drawcube(1.2/maxsize*x-0.45, 1.2/maxsize*y-0.45, 1.2/maxsize*z-0.45, 0.02+matrix[x][y][z]*0.004 );
            }
         }
      }
   }



  //Multi-colored side - FRONT
  
  glFlush();
  glutSwapBuffers();
 
}
 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
   switch(key){
      case GLUT_KEY_RIGHT:
         rotate_y += 2.5;
      break;
      case GLUT_KEY_LEFT:
         rotate_y -= 2.5;
      break;
      case GLUT_KEY_UP:
         rotate_x += 2.5;
      break;
      case GLUT_KEY_DOWN:
         rotate_x -= 2.5;
      break;
      case GLUT_KEY_F1:
         turn(1);
      break;
      case GLUT_KEY_F2:
         turn(0);
      break;
      case GLUT_KEY_F3:
         turn(3);
      break;
      case GLUT_KEY_F4:
         turn(2);
      break;
      case GLUT_KEY_F5:
         turn(5);
      break;
      case GLUT_KEY_F6:
         turn(4);
      break;
      case GLUT_KEY_F7:
         newcube();
      break;
      /*case GLUT_KEY_DOWN:
         rotate_x -= 2.5;
      break;
      */
      
   }
  glutPostRedisplay();
 
}






  























// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
   srand(time(NULL)); 

    for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            matrix[x][y][z] = 0;
         }
      }
   }


  matrix[2][1][0]=1;
  matrix[0][0][0]=1;




































  
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("2048 3D");
  glutReshapeWindow(700,700);
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 //create_texture(1); 
 //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixmap_height, pixmap_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(&(xim[0]->data[0])));

  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}