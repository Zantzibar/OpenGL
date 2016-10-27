/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/* ----------------------------------------------------------- */
/* Datei: KeyboardFunc.cpp                                     */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                            */
/* Autor: W. Kestner, W.-D. Groch                              */
/* letzte Aenderung:	Groch   03.05.2011                        */
/* ----------------------------------------------------------- */
/*	                                                            */
/*  Beobachten Sie die Ausgabe im Konsolfenster	waehrend Sie    */
/*  ein ASCII-Zeichen eingeben                                 */
/*	                                                            */
/* ----------------------------------------------------------- */
/*glutKeyboardFunc sets the keyboard callback for the current window.
Usage
void glutKeyboardFunc(void (*func)(unsigned char key,int x, int y));
func The new keyboard callback function.
Description
glutKeyboardFunc sets the keyboard callback for the current window. 
When a user types into the window, each key press generating an 
ASCII character will generate a keyboard callback. The key callback 
parameter is the generated ASCII character. The state of modifier 
keys such as Shift cannot be determined directly; their only effect 
will be on the returned ASCII data. The x and y callback parameters 
indicate the mouse location in window relative coordinates when 
the key was pressed. When a new window is created, no keyboard 
callback is initially registered, and ASCII key strokes in the
window are ignored. Passing NULL to glutKeyboardFunc disables the 
generation of keyboard callbacks. During a keyboard callback, 
glutGetModifiers may be called to determine the state of modifier 
keys when the keystroke generating the callback occurred.
Also, see glutSpecialFunc for a means to detect non-ASCII key strokes.*/ 

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

	void KeyboardFunc ( unsigned char key, int x, int y )
{
    GLfloat xMousePos = float(x);
    GLfloat yMousePos = float(y);
    std::cout <<"key = "<< key <<"  "<< xMousePos<<", "<<yMousePos<<std::endl;

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
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   std::cout<<"Grundlegende Interaktionen:"<<std::endl;
    std::cout<<"Klicken Sie zunaechst ins Grafikfenster;"<<std::endl;
    std::cout<<"druecken Sie eine der 'normalen' Tasten "<<std::endl;
    std::cout<<"und beobachten Sie die Konsole-Ausgabe."<<std::endl<<std::endl;
    std::cout<<"Zum Beenden Graphik-Fenster schliessen!"<<std::endl<<std::endl;

    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );
    glutCreateWindow ("*** KeyboardFunc ***");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    glutKeyboardFunc( KeyboardFunc );  // NEU
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
