// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014
#define _USE_MATH_DEFINES
//glutSolidCylinder

#include <iostream>  
#include <GL/freeglut.h>         //lädt alles für OpenGL
//#include "wuerfel.h"
#include <math.h>
#include <glfw3.h>
#include "Figure.h"

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  /* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */

float fRotation = 315.0; // globale Variable :-(
float fSpinner = 0;
float fLenght = 0;
float printstatus = 0;

// angle of rotation for the camera direction
float _angle = 0.0f;

// actual vector representing the camera's direction
float lx = 2.0f, ly = 2.0f, lz = 2.0f;

static float _x = 0.0f;
static float _y = 0.0f;

static float _r = 2.0f;
static float _a = 0.0f;

bool first = true;

static float _h = 0.0f;
static float _v = 0.0f;
static float _hoch = 0.0f;

using namespace std;


/*
	Es gibt 8 Lichtquellen in OpenGL. Wir schalten die erste an. (GL_LIGHT0)

	aus http://www.foerterer.com/cpp/licht/teekanne.htm
*/
float rotation = 0.0f;  // Lichtpositions-Rotation

void initLight()
{
	// Beleuchtung global einschalten
	glEnable(GL_LIGHTING);

	// Farben der Lichtquelle setzen (r,g,b,a)
	GLfloat ambient[4] = { 0.1f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[4] = { 0.6f, 0.4f, 0.2f, 1.0f };
	GLfloat specular[4] = { 0.6f, 0.6f, 0.4f, 1.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


	// Lichtposition setzen (x,y,z,w)
	GLfloat position[4] =
	{ 
		cos(rotation), 0.5f, sin(rotation), 1.0f 
	};
	
	glLightfv(GL_LIGHT0, GL_POSITION, position);

} // initLight()

void initMaterial()
{
	// Materialfarben setzen (r,g,b,a)
	GLfloat globalAmbient[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

	// Globale ambiente Beleuchtung
	// komplett herunternehmen
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
		globalAmbient);

	// Materialparameter setzen
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 16.0f);

} // initMaterial()

void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}


// Maus-Bewegungen mit gedrueckter Maus-Taste
void Motion(int x, int y)
{	
	if (first)
	{
		first = false;
		_x = x;
		_y = y;
		return;
	}

	_a += (_x - x) * 0.01;
 	_x = x;
	
	lx = _r*cos(_a);
	lz = _r*sin(_a);

	std::cout << "Maus: X -> " << lx << ", Y  -> " << lz << std::endl;
	// RenderScene aufrufen.
	glutPostRedisplay();
}

// Maus-Bewegungen mit gedrueckter Maus-Taste
void MotionPassive(int x, int y)
{
	return; 

	if (first)
	{
		first = false;
		_x = x;
		_y = y;
		return;
	}

	_a += (_x - x) * 0.01;
	_x = x;

	lx = _r*cos(_a);
	lz = _r*sin(_a);

	std::cout << "Maus: X -> " << lx << ", Y  -> " << lz << std::endl;
	// RenderScene aufrufen.
	glutPostRedisplay();
}


void MotionWheel(int button, int state, int x, int y)
{
	// -1 = zurueck scrollen
	// 1  = vorwaerts scrollen
	float diff = state * 0.1;
	ly += diff;
	_r += diff; // radius erhoehen
	Motion(_x, _y); // neue koordinaten fuer lx, und lz setzen
}

void MotionP(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON)
	{
		first = true;
		// when the button is released
		if (state == GLUT_UP)
		{
		}
		else
		{// state = GLUT_DOWN
		}
	}
}

// move
void processNormalKeys(unsigned char key, int xx, int yy) 
{
	char clow = tolower(key);
	switch (clow) 
 	{
		case 'w':
		{
			_h += 0.2;
		}break;

		case 'a':
		{
			_v += 0.2;
		}break;

		case 's':
		{
			_h -= 0.2;

		}break;

		case 'd':
		{
			_v -= 0.2;
		}break;

		case 'f':
		{
			_hoch -= 0.2;
		}break;

		case 'r':
		{
			_hoch += 0.2;
		}break;

		case 27:
			exit(0);
			break;
	}
	if (key == 27)
		exit(0);
}


void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glClearColor(1, 0.5, 0, 0); // orange
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	
	//glClearColor(1, 1, 1, 0); //weiß

	//gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.); // nach oben
	//gluLookAt(0., 1., 1., 0., 0., 0., 0., 1., 0.); // von vorne oben
	//gluLookAt(1., 0., 0., 0., 0., 0., 0., 1., 0.); // von rechts 
	//gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.); // von rechts oben

	// kamera anpassen
	gluLookAt(//1, x, 1,
		lx, ly, lz,
		0,0,0,
		0.0f, 1.0f, 0.0f);
	
	//glEnable(GL_LIGHTING);
	coordinatesystem();
	ground();
	
	initLight();

	glTranslatef(_v, _hoch, _h);
	
	
	// Teapot
	glPushMatrix();	// Einheitsmatrix (0,0,0) auf Stack

		//drawtriangle(); 

	/*
		GLfloat mat_amb_diff[] = { 0.1, 0.5, 0.8, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,
			mat_amb_diff);

		
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat low_shininess[] = { 5.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

		

		GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
*/

	//glutWireTeapot(0.2);
		//glRotatef(_angle_z, 0.0f, 0.0f, 1.0f); //rotating object continuously by 2 degree
		//glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotating object continuously by 2 degree
		//glRotatef(_angle, 0.0f, 0.0f, 1.0f); //rotating object continuously by 2 degree
		//glTranslatef(0, 0, 0.2);
		//glScalef(2, 1, 1);
		//glTranslatef(0,0,-0.1);
		//glPushMatrix(); //Matrix wird auf den Stack gesichert
		//glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt
		/*
		gluLookAt(eyex, eyey, eyez, // Kamera-Position
		centerx, centery, centerz, // Betrachtete Position
		upx, upy, upz); // Kamera-View-Up-Vektor
		*/
		//glRotatef(fRotation, 0, 1, 0);	// Rotation an der y Achse
		body(2, fLenght / 100, fSpinner);

		//glTranslatef(0, 0, -0.5);
	glPopMatrix();	// Einheitsmatrix wieder von Stack holen (0,0,0)

	glFlush();  // Sofort anfangen mit Zeichnen
	glFinish();	// erst anzeigen wenn vollständig gezeichnet



	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt
	// Matrix für Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	//glOrtho( -1., 1., -1., 1., 0.0, 2.0);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

bool countUp = true;

void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	//std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	printstatus = printstatus + 1;
	if (printstatus == 50) {
		std::cout << "Print value= " << value << " & Spinner value: " << fSpinner << " & Rotation: " << fRotation << " & claw arm: "
			<< fLenght << std::endl;
		printstatus = 0;
	}

	// RenderScene aufrufen
	fRotation = fRotation - 1.0; // Rotationswinkel aendern
	if (fRotation <= 0.0) {
		fRotation = fRotation + 360.0;
	}
	for (int i = 0; i <= 50; i++) {
			fSpinner = fSpinner + 1;
	}
	

	if (countUp) {
		fLenght++;
		if (fLenght >= 200)
			countUp = false;
	}
	else {
		fLenght--;
		if (fLenght == 0)
			countUp = true;
	}

	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Christian Hesse; Patrick Zantz");   // Fenster-Erzeugung
	
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutIdleFunc(RenderScene);

	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(processNormalKeys);
	
	glutMouseWheelFunc(MotionWheel);
	glutMouseFunc(MotionP);   //NEU
	glutMotionFunc(Motion);   //NEU
	glutPassiveMotionFunc(MotionPassive);

	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);

	Init();
	
	glutMainLoop();
	return 0;
}
