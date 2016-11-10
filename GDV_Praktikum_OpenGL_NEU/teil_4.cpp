// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014
#define _USE_MATH_DEFINES
//glutSolidCylinder

#include <iostream>  
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <math.h>
#include "Figure.h"
#include <SOIL.h>				// für die texturen

float fRotation = 315.0;
float fSpinner = 0;
float fLenght = 0;
float printstatus = 0;
float _angle = 0.0f; // angle of rotation for the camera direction

					 // alles fuer die Kamera
float lx = 5.0f;
float ly = 4.0f;
float lz = 5.0f;

float _r = 1.0f; // radius
float _a = 0.0f; // alpha

bool first = true;
bool m_bMove = false;
int iTempMove = 0;

// move object
static float _h = 0.0f;
static float _v = 0.0f;
static float _hoch = 0.0f;


GLuint boden; // Textur -> boden 

using namespace std;


/*
Es gibt 8 Lichtquellen in OpenGL. Wir schalten die erste an. (GL_LIGHT0)

aus http://www.foerterer.com/cpp/licht/teekanne.htm

* Grundlagen:
*	- Lichter bestehen aus einem ambienten, einem diffusen und einem spiegelnden Anteil.
*	- Alle drei Anteile haben eine bestimmte Farbe. Diese wird im RGBA-Modell angegeben.
*	- Es werden mindestens acht Lichter (Light0 - Light7) unterstützt.
*	- ambientes Licht ist ungerichtetes Licht.
*	- diffuses Licht kommt aus einer bestimmten Richtung. Wenn es auf eine Oberfläche trifft, wird es in alle Richtungen gleichmässig gestreut.
*	- Der spiegelnde Lichtanteil kommt genau aus einer Richtung und wird in eine vorgegebene Richtung reflektiert.
*	- Je nach Beschaffenheit der Oberfläche ergeben die reflektierten Strahlen an einer bestimmten Stelle ein Glanzlicht (Highlight).
*
* Richtungslicht:
*	- eine Lichtquelle, die unendlich weit entfernt ist und deren Licht in eine bestimmte Richtung strahlt (z.B. die Sonne).
*
* Punktlicht:
*	- eine Lichtquelle innerhalb der Szene, die in alle Richtungen gleichmässig strahlt. Vgl. Glühbirne.
*
* Spotlight:
*  - eingeschränkter Lichtkegel
*
*
*  Wir nehmen ein Punktlicht (Glühbirne)
*/
void initLight()
{
	// Beleuchtung global einschalten
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float light1_pos[] = { 1.0, .5, -0.45, 0.0 };			//Werte für Lichtposition
	float light1_color_am[] = { 0.0, 0.0, 0.0, 0.0 };			//Werte für ambientes Licht
	float light1_color_diff[] = { 0.51, 0.55, 0.51, 1.0 };		//Werte für diffuses Licht
	float light1_color_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };		//Werte für spekuläres Licht

	glShadeModel(GL_SMOOTH); //Schattierungsmodus auf SMOOTH (Verschmieren?)

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_color_am);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color_diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_color_spec);

	// Abschwächungsfaktor für die Lichtquelle
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

	glEnable(GL_LIGHTING);		// Lichtberechnungen verwenden
	glEnable(GL_LIGHT0);		// Lichtquelle einschalten
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION); // Material setzen
	glEnable(GL_COLOR_MATERIAL);

} // initLight()

void initTexture()
{
	// bild fuer boden laden
	boden = SOIL_load_OGL_texture("Bilder/boden1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

}

void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen

	initLight();
	initTexture();

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}


// fuer den zurueckgelegten weg der Maus (Pixel)
float _xTMP = 5.0f;
float _yTMP = 5.0f;

// Maus-Bewegungen mit gedrueckter Maus-Taste
void Motion(int x, int y)
{
	if (first)
	{
		first = false;
		_xTMP = x;
		_yTMP = y;
		return;
	}

	_a += (_xTMP - x) * 0.01;
	_xTMP = x;

	lx = _r*cos(_a);
	lz = _r*sin(_a);

	// std::cout << "Maus: X -> " << lx << ", Y  -> " << lz << std::endl;
	// RenderScene aufrufen.
	glutPostRedisplay();
}


/**
* Scrollen veraendert die Position der Kamera (lookAt)
*
* state = -1 -> zurueck scrollen
* state =  1 -> vorwaerts scrollen
*/
void MotionWheel(int button, int state, int x, int y)
{
	if (first)
	{
		first = false;
		_xTMP = x;
		_yTMP = y;
		return;
	}

	float diff = state * 0.1;
	ly += diff;
	_r += diff; // radius erhoehen

				//lx += diff;
				//lz += diff;
	Motion(_xTMP, _yTMP); // neue koordinaten fuer lx, und lz setzen

						  // RenderScene aufrufen.
	glutPostRedisplay();
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

	case 'g':
	{
		iTempMove = 0;
		// todo fahr ne route
		if (m_bMove)
			m_bMove = false;
		else
			m_bMove = true;
	}break;

	case 27:
		exit(0);
		break;
	}
	if (key == 27)
		exit(0);
}

float rotateMove = 0.0f;


void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glClearColor(1, 0.5, 0, 0); // orange
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

						// kamera anpassen
	gluLookAt(lx, ly, lz,
		0, 0, 0,
		0.0f, 0.5f, 0.0f);

	coordinatesystem();

	// textur einblenden
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, boden);
		glEnable(GL_TEXTURE_2D);
		ground();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glTranslatef(_v, _hoch, _h);

	glPushMatrix();	// Einheitsmatrix (0,0,0) auf Stack
		if (m_bMove)
			glRotatef(rotateMove, 0, 1, 0);	// Rotation an der y Achse

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
bool countUp2 = true;

void Animate(int value)
{
	int limit1 = 100;
	int limit2 = 300;
	int limit3 = 500;
	int limit4 = 700;

	if (m_bMove)
	{
		if (iTempMove > 0 && iTempMove < limit1)
			_v += 0.05;
		else if (rotateMove <= 90)
			rotateMove += 1.0;
		else if (iTempMove > limit1 && iTempMove < limit2)
			_h += 0.05;
		else if (rotateMove <= 180)
			rotateMove += 1.0;
		else if (iTempMove > limit2 && iTempMove < limit3)
			_v -= 0.05;
		else if (rotateMove <= 270)
			rotateMove += 1.0;
		else if (iTempMove > limit3 && iTempMove < limit4)
			_h -= 0.05;
		else if (rotateMove <= 360)
			rotateMove += 1.0;
		else if (iTempMove > limit4)
		{
			if (countUp2)
			{
				_hoch += 0.1;
				if (_hoch >= 10)
					countUp2 = false;
			}
			else
			{
				_hoch -= 0.1;
				rotateMove += 1.0;
				if (_hoch < 0)
				{
					countUp2 = true;
				}
			}

			cout << _hoch << endl;
		}

		iTempMove++;
	}

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
	glutInitWindowSize(1000, 600);         // Fenster-Konfiguration
	glutCreateWindow("Christian Hesse; Patrick Zantz");   // Fenster-Erzeugung

	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutIdleFunc(RenderScene);

	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(processNormalKeys);

	glutMouseWheelFunc(MotionWheel);
	glutMouseFunc(MotionP);   //NEU
	glutMotionFunc(Motion);   //NEU

							  // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);

	Init();

	glutMainLoop();
	return 0;
}
