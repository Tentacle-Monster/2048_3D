//
// File:        mycube.c
// Author:      Matt Daisley
// Created:     4/25/2012
// Project:     Source code for Make a Cube in OpenGL
// Description: Creates an OpenGL window and draws a 3D cube
//              That the user can rotate using the arrow keys
// 
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
unsigned int matrix[maxsize][maxsize][maxsize] ;


enum Direction{
   up,
   down,
   right,
   left,
   to,
   from
};

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




void display();
void specialKeys();
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
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 2.5;
 
  //e()//  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 2.5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 2.5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 2.5;

  //  Request display update
  glutPostRedisplay();
 
}






  























// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){


    for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            matrix[x][y][z] = 11;
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