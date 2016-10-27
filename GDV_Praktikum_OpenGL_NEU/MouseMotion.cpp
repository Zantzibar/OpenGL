/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: MouseMotion.cpp                                      */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                            */
/* Autor: W. Kestner, W.-D. Groch                              */
/* letzte Aenderung:	Groch   03.05.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*	Beobachten Sie die Ausgabe im Konsolefenster waehrend Sie    */
/*	die Maus bewegen - halten Sie einen mouse button            */
/*  abwechselnd gedrueckt und lassen Sie ihn los               */
/*	                                                            */
/* ----------------------------------------------------------- */

/*glutMotionFunc and glutPassiveMotionFunc set the motion and 
passive motion callbacks respectively for the current window.
Usage
void glutMotionFunc(void (*func)(int x, int y));
void glutPassiveMotionFunc(void (*func)(int x, int y));
func The new motion or passive motion callback function.
Description
glutMotionFunc and glutPassiveMotionFunc set the motion and 
passive motion callback respectively for the current window.
The motion callback for a window is called when the mouse moves 
within the window while one or more mouse buttons are pressed. 
The passivemotion callback for a window is called when the mouse 
moves within the window while no mouse buttons are pressed.
The x and y callback parameters indicate the mouse location in 
window relative coordinates. Passing NULL to glutMotionFunc or 
glutPassiveMotionFunc disables the generation of the
mouse or passive motion callback respectively.*/ 

#include <windows.h>
#include <GL/freeglut.h>         //laedt alles fuer OpenGL
#include <iostream>
#include <math.h>
#include "Wuerfel_mit_Normalen.h"


GLfloat extent = 1.0f;// Mass fuer die Ausdehnung des Modells

void Init()	
{
// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
// durchgefuehrt werden muessen
    glClearColor ( 0.33f, 0.225f, 0.0f, 1.0f);	//Hintergrundfarbe definieren
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
}

void RenderScene(void)
{
// Hier befindet sich der Code der in jedem frame ausgefuehrt werden muss
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Puffer loeschen
    glLoadIdentity();
    Wuerfel_mit_Normalen(extent);
    glutSwapBuffers(); 
    glFlush();
}

void Reshape(int width,int height)
{
// Hier finden die Reaktionen auf eine Veraenderung der Groesse des 
// Graphikfensters statt
    glMatrixMode(GL_PROJECTION); //Matrix fuer Transf. Frustum->viewport
    glLoadIdentity();
    glViewport(0,0,width,height);
    glOrtho(-extent*2.0,+extent*2.0,-extent*2.0,+extent*2.0,-extent*2.0,+extent*2.0); //Frustum
    glMatrixMode(GL_MODELVIEW); //Modellierungs/Viewing-Matrix
}

void MotionP ( int x, int y )
// Maus-Bewegungen ohne gedrueckte Maus-Taste
{
    GLfloat xMousePos = float(x);
    GLfloat yMousePos = float(y);
    std::cout <<xMousePos<<", "<<yMousePos<<std::endl;
    // RenderScene aufrufen.
    glutPostRedisplay();
}

void Motion ( int x, int y )
// Maus-Bewegungen mit gedrueckter Maus-Taste
{
    GLfloat xMousePos = float(x);
    GLfloat yMousePos = float(y);
    std::cout <<"Maustaste gedrueckt "<< xMousePos<<", "<<yMousePos<<std::endl;
    // RenderScene aufrufen.
    glutPostRedisplay();
}

void Animate (int value)
{
   // Hier werden Berechnungen durchgefuehrt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess laeuft im Hintergrund und wird alle 
   // wait_msec Milli-Sekunden aufgerufen. 
   // RenderScene aufrufen.
   glutPostRedisplay();
   // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
   int wait_msec = 1000;
   glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   std::cout<<"Grundlegende Interaktionen:"<<std::endl;
    std::cout<<"Bewegen Sie die Maus (gedrueckt oder nicht) im"<<std::endl;
    std::cout<<"Graphik-Fenster und beobachten Sie die Konsole!"<<std::endl<<std::endl;
    std::cout<<"Zum Beenden Graphik-Fenster schliessen!"<<std::endl<<std::endl;
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );
    glutCreateWindow ("*** MouseMotion ***");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    glutPassiveMotionFunc( MotionP );   //NEU
    glutMotionFunc( Motion );           //NEU
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
