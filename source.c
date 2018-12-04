
// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right
//              Up Arrow    - Rotate Up
//              Down Arrow  - Rotate Down     
 
// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define maxsize 4
#define win 12
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
int matrix[maxsize][maxsize][maxsize] ;

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
   if(dir%2)
   for(int i=1; i<maxsize; i++)ret+=step(dir,i);
   else
   for(int i=maxsize-2; i>=0; i--)ret+=step(dir,i);
   return(ret);
}


void drawcube( double dx, double dy, double dz, double size ){
   glBegin(GL_POLYGON);
 
  glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  size + dx , -size + dy , -size + dz  );      // P1 is red
  glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  size + dx ,  size + dy , -size + dz  );      // P2 is green
  glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -size + dx ,  size + dy , -size + dz  );      // P3 is blue
  glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -size + dx , -size + dy , -size + dz  );      // P4 is purple
 
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
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
 
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
            if(matrix[x][y][z]!=0 && matrix[x][y][z]<win ){
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
      /*case GLUT_KEY_UP:
         rotate_x += 2.5;
      break;
      case GLUT_KEY_DOWN:
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


    for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            matrix[x][y][z] = 1;
         }
      }
   }


  matrix[2][1][0]=5;
  matrix[0][0][0]=10;
  matrix[3][3][3]=10;
  matrix[3][0][0]=5;
  matrix[2][0][0]=11;
  matrix[1][1][1]=5;
  matrix[2][2][2]=1;
  matrix[2][1][2]=11;
  matrix[0][0][0]=11;
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("Awesome Cube");
  glutReshapeWindow(700,700);
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 
  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}