
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
#include <GL/glut.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#define maxsize 4
#define winrate 12
#define ss 0.6f;
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
int matrix[maxsize][maxsize][maxsize] ;
GLuint *                  textures[11];
int gamemode =1;

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------


int step();
void display();
void specialKeys();
void newcube();
GLuint LoadTexture();
int step();
int turn();
void drawcube();
void drawmatrix();
//void win();
void g_ower_screen();
void maindraw();
void newgame();






GLuint LoadTexture( const char * filename )
{

  GLuint texture;

  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 640;
  height = 640;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );
glBindTexture(GL_TEXTURE_2D, 0);
return texture;
}



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
            else if(matrix[pos+delta][y][z]==matrix[pos][y][z]&&matrix[pos][y][z]>0){
               matrix[pos+delta][y][z]++;
               matrix[pos+delta][y][z]*=-1;
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
            else if(matrix[x][pos+delta][z]==matrix[x][pos][z]&&matrix[x][pos][z]>0){
               matrix[x][pos+delta][z]++;
               matrix[x][pos+delta][z]*=-1;
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
            else if(matrix[x][y][pos+delta]==matrix[x][y][pos]&&matrix[x][y][pos]>0){
               matrix[x][y][pos+delta]++;
               matrix[x][y][pos+delta]*=-1;
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
   int space =0 ;
   for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            matrix[x][y][z]=abs(matrix[x][y][z]);
            if(matrix[x][y][z]>=winrate){
               gamemode = 2;
            }
            else if(!matrix[x][y][z]) space++;
         }
      }
   }
   if (!space) gamemode = 3;
   else
   if(ret)newcube();
   return(ret);
}

void newgame(){
   gamemode = 1;
   for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            matrix[x][y][z]=0;
         }
      }
   }
   newcube();
   newcube();
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

void drawmatrix(){
  // glColor3f(0,1,1);
    glColor3f(0,0,1);
   for(int x=0 ;x<=maxsize ; x++){
      for(int y=0; y<=maxsize; y++){
          
	glBegin(GL_LINES); 
		glVertex3f ((-0.5+(float)x/maxsize)*1.2,(-0.5+(float)y/maxsize)*1.2 ,-0.6); 
		glVertex3f ((-0.5+(float)x/maxsize)*1.2,(-0.5+(float)y/maxsize)*1.2,0.6);  
	glEnd();
      }
   }
       glColor3f(0,1,0);
   for(int x=0 ;x<=maxsize ; x++){
      for(int z=0; z<=maxsize; z++){
          
	glBegin(GL_LINES); 
		glVertex3f ((-0.5+(float)x/maxsize)*1.2 ,-0.6,(-0.5+(float)z/maxsize)*1.2); 
		glVertex3f ((-0.5+(float)x/maxsize)*1.2 ,0.6 ,(-0.5+(float)z/maxsize)*1.2); 
	glEnd();
      }
   }
       glColor3f(1,0,0);
   for(int z=0 ;z<=maxsize ; z++){
      for(int y=0; y<=maxsize; y++){
          
	glBegin(GL_LINES); 
		glVertex3f (-0.6,(-0.5+(float)y/maxsize)*1.2 ,(-0.5+(float)z/maxsize)*1.2); 
		glVertex3f (0.6,(-0.5+(float)y/maxsize)*1.2,(-0.5+(float)z/maxsize)*1.2); 
	glEnd();
      }
   }
}


void drawcube( double dx, double dy, double dz, int siz ){
   double size = 0.06+siz*0.005 ;
   glBindTexture(GL_TEXTURE_2D, textures[siz-1]);
   glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
  glTexCoord2f(1, 0);     glVertex3f(  size + dx , -size + dy , -size + dz  );
  glTexCoord2f(1, 1);     glVertex3f(  size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(0, 1);     glVertex3f( -size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(0, 0);     glVertex3f( -size + dx , -size + dy , -size + dz  );
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);   glVertex3f(  size + dx , -size + dy , size + dz  );
  glTexCoord2f(0, 1);   glVertex3f(  size + dx ,  size + dy , size + dz  );
  glTexCoord2f(1, 1);   glVertex3f( -size + dx ,  size + dy , size + dz  );
  glTexCoord2f(1, 0);   glVertex3f( -size + dx , -size + dy , size + dz  );
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);   glVertex3f( size + dx , -size + dy , -size + dz  );
  glTexCoord2f(0, 1);   glVertex3f( size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(1, 1);   glVertex3f( size + dx ,  size + dy ,  size + dz  );
  glTexCoord2f(1, 0);   glVertex3f( size + dx , -size + dy ,  size + dz  );
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);   glVertex3f( -size + dx , -size + dy ,  size + dz  );
  glTexCoord2f(0, 1);   glVertex3f( -size + dx ,  size + dy ,  size + dz  );
  glTexCoord2f(1, 1);   glVertex3f( -size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(1, 0);   glVertex3f( -size + dx , -size + dy , -size + dz  );
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);   glVertex3f(  size + dx ,  size + dy ,  size + dz  );
  glTexCoord2f(0, 1);   glVertex3f(  size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(1, 1);   glVertex3f( -size + dx ,  size + dy , -size + dz  );
  glTexCoord2f(1, 0);   glVertex3f( -size + dx ,  size + dy ,  size + dz  );
  glEnd();
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);   glVertex3f(  size + dx , -size + dy , -size + dz  );
  glTexCoord2f(0, 1);   glVertex3f(  size + dx , -size + dy ,  size + dz  );
  glTexCoord2f(1, 1);   glVertex3f( -size + dx , -size + dy ,  size + dz  );
  glTexCoord2f(1, 0);   glVertex3f( -size + dx , -size + dy , -size + dz  );
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}
 
void maindraw(){
   glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
   for(int x=0 ;x<maxsize ; x++){
      for(int y=0; y<maxsize; y++){
         for(int z=0; z<maxsize; z++){
            if(matrix[x][y][z]!=0 && matrix[x][y][z]<winrate ){
            drawcube(1.2/maxsize*x-0.45, 1.2/maxsize*y-0.45, 1.2/maxsize*z-0.45, matrix[x][y][z]);
            }
         }
      }
   }
   drawmatrix();
  
}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
  // Reset transformations
  glLoadIdentity();
 // Rotate when user changes rotate_x and rotate_y
 switch(gamemode){
    case 1:
      maindraw();
    break;
    case 2:
      g_ower_screen("textures/uwin.bmp");
    break;
    case 3:
      g_ower_screen("textures/ulos.bmp");
    break;
 }
   
  // g_ower_screen();
 glFlush();
  glutSwapBuffers();
 
}
void g_ower_screen( char path[]){
   glLoadIdentity();
   GLuint gameower;
    glColor3f(1,1,1);
   gameower =  LoadTexture( path );
   glBindTexture (GL_TEXTURE_2D, 0);
   glBindTexture(GL_TEXTURE_2D, gameower);
   glEnable(GL_TEXTURE_2D);
   glBegin(GL_POLYGON);
  glTexCoord2f(1, 0);     glVertex2f( 1 , -1  );
  glTexCoord2f(1, 1);     glVertex2f( 1 , 1  );
  glTexCoord2f(0, 1);     glVertex2f( -1 , 1  );
  glTexCoord2f(0, 0);     glVertex2f( -1 , -1  );
   glDisable(GL_POLYGON);
  glEnd();
  glutPostRedisplay();


}
/*
void win(){
  // glutInit();
   glutDisplayFunc(g_ower_screen);
    glutSpecialFunc(0);
  glutMainLoop();

}
 */
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
      case GLUT_KEY_F10:
         newgame();
      break;
   }
  glutPostRedisplay();
}



// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
   //srand(time(NULL)); 

   newgame();

/*
  matrix[2][1][0]=11;
  matrix[1][1][0]=11;
  matrix[2][2][1]=11;
  matrix[0][0][0]=1;*/

  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
   
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glMatrixMode(GL_MODELVIEW);
  // Create window

  glutCreateWindow("2048 3D");
  glutReshapeWindow(700,700);
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textures[0] = LoadTexture( "textures/1.bmp" );
    textures[1] = LoadTexture( "textures/2.bmp" );
    textures[2] = LoadTexture( "textures/3.bmp" );
    textures[3] = LoadTexture( "textures/4.bmp" );
    textures[4] = LoadTexture( "textures/5.bmp" );
    textures[5] = LoadTexture( "textures/6.bmp" );
    textures[6] = LoadTexture( "textures/7.bmp" );
    textures[7] = LoadTexture( "textures/8.bmp" );
    textures[8] = LoadTexture( "textures/9.bmp" );
    textures[9] = LoadTexture( "textures/10.bmp" );
    textures[10] = LoadTexture( "textures/11.bmp" );
        
    
    glBindTexture (GL_TEXTURE_2D, 0);
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}