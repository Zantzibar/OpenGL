// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream>  
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "wuerfel.h"


float _angle = 0.0;
float _cameraangle = 30.0;


void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0.5, 0, 0); //orange
	//glClearColor(1, 1, 1, 0); //weiß

	//gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.); // nach oben
	//gluLookAt(0., 1., 1., 0., 0., 0., 0., 1., 0.); // von vorne oben
	//gluLookAt(1., 0., 0., 0., 0., 0., 0., 1., 0.); // von rechts 
	gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.); // von rechts oben

	//glDisable(GL_LIGHTING);

	glBegin(GL_LINES);
		// X-Achse, rot
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(1.0, 0.0, 0.0);
		// Y-Achse, grün
		//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 1.0, 0.0);
		// Z-Achse, blau
		//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 1.0);
	glEnd();

	//glEnable(GL_LIGHTING);

	// Teapot
	glPushMatrix();	// Einheitsmatrix (0,0,0) auf Stack
		glTranslatef(0,0,-0.2);
		//glutWireTeapot(0.2);
		//glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotating object continuously by 2 degree
		glTranslatef(0, 0, 0.2);
		glScalef(0.5, 0.5, 1);
		//glTranslatef(0,0,-0.1);
		//glPushMatrix(); //Matrix wird auf den Stack gesichert
		//glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt
		/*
		gluLookAt(eyex, eyey, eyez, // Kamera-Position
		centerx, centery, centerz, // Betrachtete Position
		upx, upy, upz); // Kamera-View-Up-Vektor
		*/
		Wuerfel(0.4);

		glTranslatef(0, 0, 0.3);
		glScalef(0.5, 0.5, 1);
		Wuerfel(0.3);

		//glTranslatef(0, 0, -0.5);
	glPopMatrix();	// Einheitsmatrix wieder von Stack holen (0,0,0)

	glFlush();  // Sofort anfangen mit Zeichnen
	glFinish();	// erst anzeigen wenn vollständig gezeichnet



	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt
	// Matrix für Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten)
	gluPerspective(45., 1., 1, 20);
	//glOrtho( -1., 1., -1., 1., 0.0, 2.0);
	//glOrtho( GLdouble left, GLdouble right,
	//		   GLdouble bottom, GLdouble top,
	//		   GLdouble near, GLdouble far );
	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	_angle += 2.0f;

	if (_angle>360.f)
	{
		_angle -= 360;
	}
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Christian Hesse; Patrick Zantz");   // Fenster-Erzeugung
	

	
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);

	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
