/* ------------------------------------------------------------ */
/* OpenGL-Testprogramm (quick and dirty)                        */
/* ------------------------------------------------------------ */
/* Datei: MouseFunction.cpp                                     */
/* zusaetzlich benoetigt: Wuerfel_mit_Normalen.cpp und h       */
/*	                                                             */
/* Autor: W. Kestner, W.-D. Groch                               */
/* letzte Aenderung:	Groch   03.05.2011                         */
/* ------------------------------------------------------------ */
/*	                                                             */
/*	Beobachten Sie die Ausgabe im Konsolfenster,waehrend Sie die  */
/*	Maus bewegen - halten Sie einen mouse button abwechselnd     */
/* gedrueckt und lassen Sie ihn wieder los							 */
/*	                                                             */
/* ------------------------------------------------------------ */

/*
glutMouseFunc sets the mouse callback for the current window.
Usage
void glutMouseFunc(void (*func)(int button, int state,
int x, int y));
func The new mouse callback function.
Description
glutMouseFunc sets the mouse callback for the current window. 
When a user presses and releases mouse buttons in the window, each 
press and each release generates a mouse callback. The button 
parameter is one of GLUT LEFT BUTTON, GLUT MIDDLE BUTTON, or 
GLUT RIGHT BUTTON. For systems with only two mouse buttons, it may
not be possible to generate GLUT MIDDLE BUTTON callback. For 
systems with a single mouse button, it may be possible to generate 
only a GLUT LEFT BUTTON callback. The state parameter is either 
GLUT UP or GLUT DOWN indicatingwhether the callback was due to a 
release or press respectively. The x and y callback parameters 
indicate the window relative coordinates when the mouse button 
state changed. If a GLUT DOWN callback for a specific button is 
triggered, the program can assume a GLUT UP callback for the same 
button will be generated (assuming the window still has a mouse 
callback registered) when the mouse button is released even if 
the mouse has moved outside the window. If a menu is attached to 
a button for a window, mouse callbacks will not be generated for 
that button. During a mouse callback, glutGetModifiers may be 
called to determine the state of modifier keys when the mouse 
event generating the callback occurred. Passing NULL to glutMouseFunc
disables the generation of mouse callbacks..*/ 

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

void MouseFunc ( int button, int state, int x, int y )
// Maus-Tasten und -Bewegung abfragen
{
    GLfloat xMousePos = float(x);
    GLfloat yMousePos = float(y);

    switch(button){
    case GLUT_LEFT_BUTTON:
    if (state==GLUT_DOWN)		
        std::cout <<"linke Maustaste gedrueckt "<< xMousePos<<", "<<yMousePos<<std::endl;
    else
        std::cout <<"linke Maustaste losgelassen "<< xMousePos<<", "<<yMousePos<<std::endl;
    break;

    case GLUT_RIGHT_BUTTON:
    if (state==GLUT_DOWN)		
        std::cout <<"rechte Maustaste gedrueckt "<< xMousePos<<", "<<yMousePos<<std::endl;
    else
        std::cout <<"rechte Maustaste losgelassen "<< xMousePos<<", "<<yMousePos<<std::endl;
    break;
    }
}

void Animate (int value)
{
    // Hier werden Berechnungen durchgefuehrt, die zu einer Animation der Szene  
    // erforderlich sind. Dieser Prozess laeuft im Hintergrund und wird alle 
    // wait_msec Milli-Sekunden aufgerufen. 
    glutPostRedisplay();
    // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
    int wait_msec = 10;
    glutTimerFunc(wait_msec, Animate, ++value);          
}


int main(int argc, char **argv)
{
   std::cout<<"Grundlegende Interaktionen:"<<std::endl;
    std::cout<<"Druecken Sie (innerhalb des Graphik-Fensters)"<<std::endl;
    std::cout<<"die Maustaste und beobachten Sie die Konsole"<<std::endl<<std::endl;
    std::cout<<"Zum Beenden Graphik-Fenster schliessen!"<<std::endl<<std::endl;
    glutInit ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE|GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
    glutInitWindowSize ( 600,600 );
    glutCreateWindow ("*** MouseFunc ***");
    glutDisplayFunc ( RenderScene );
    glutReshapeFunc ( Reshape );
    glutMouseFunc( MouseFunc );    //NEU
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
    glutTimerFunc(10,Animate,0);
    Init();
    glutMainLoop ();
    return 0;
}
