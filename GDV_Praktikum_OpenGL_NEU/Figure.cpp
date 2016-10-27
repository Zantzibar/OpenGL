/*
wuerfel.cpp definiert einen Würfel über seine 6 Seiten
Last Update:  13.10.2011   W.-D. Groch
*/
#include <GL/freeglut.h>
#include "Figure.h"
#include <math.h>

// Icosaeder
#define X .525731112119133606 
#define Z .850650808352039932
static GLfloat vdata[12][3] = 
{
	{ -X, 0.0, Z },{ X, 0.0, Z },{ -X, 0.0, -Z },{ X, 0.0, -Z },
	{ 0.0, Z, X },{ 0.0, Z, -X },{ 0.0, -Z, X },{ 0.0, -Z, -X },
	{ Z, X, 0.0 },{ -Z, X, 0.0 },{ Z, -X, 0.0 },{ -Z, -X, 0.0 }
};

static GLuint tindices[20][3] = 
{
	{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
	{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
	{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
	{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 } 
};

int i;

void drawtriangle(float *v1, float *v2, float *v3)
{
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 20; i++) 
	{
		glNormal3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glNormal3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glNormal3fv(&vdata[tindices[i][2]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}

	glEnd();
}

void drawtriangle()
{
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 20; i++)
	{
		glNormal3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glNormal3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glNormal3fv(&vdata[tindices[i][2]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}

	glEnd();
}

// berechnung normalisierungsvector
void normalize(float v[3]) 
{
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) 
	{
		//error("zero length vector");
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
}


void subdivide(float *v1, float *v2, float *v3, long depth)
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;
	if (depth == 0) {
		drawtriangle(v1, v2, v3);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = v1[i] + v2[i];
		v23[i] = v2[i] + v3[i];
		v31[i] = v3[i] + v1[i];
	}
	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}

void Wuerfel(GLfloat fSeitenL)
{
	glBegin(GL_POLYGON);   //Vorderseite
	glColor4f(0.75f, 0.5f, 0.5f, 1.0f);	//Grau
										//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);	//ROT
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glColor4f(0.75f, 0.5f, 0.5f, 1.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f);	//CYAN
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glColor4f(0.75f, 0.5f, 0.5f, 1.0f);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glColor4f(0.75f, 0.5f, 0.5f, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT	
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	return;
}

void Wuerfel2(GLfloat fSeitenL, float red, float green, float blue)
{
	glBegin(GL_POLYGON);   //Vorderseite
	glColor4f(red, green, blue, 1.0f);	//Grau
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glColor4f(red, green, blue, 1.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f);	//CYAN
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glColor4f(red, green, blue, 1.0f);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glColor4f(red, green, blue, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 0.0f, 1.0f); //SCHWARZ
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT	
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 1.0f, 1.0f); //MAGENTA
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Deckflaeche
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //WEISS
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //CYAN
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //BLAU
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //GRUEN
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	//glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //GELB
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //ROT
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	return;
}

void ground() {
	glLineWidth(0.5);
	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (float i = -10; i < 11; i++) {
		glVertex3f(-10.0f, 0.0f, i);
		glVertex3f(10.0f, 0.0f, i);
	}
	for (float i = -10; i < 11; i++) {
		glVertex3f(i, 0.0f, -10.0f);
		glVertex3f(i, 0.0f, 10.0f);
	}
	glEnd();
	return;
}

void coordinatesystem()
{
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
	return;
}

void head(GLfloat factor) {
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.*factor, 0.5*factor, 0.*factor);
	glScalef(1, 0.2, 1);
	triangle(1.25 * factor, 0.5, 0.5, 0.75);		//Dreieck x+ z-
	glPopMatrix();
	glPushMatrix();
	glRotatef(-180, 0, 1, 0);
	glTranslatef(0.*factor, 0.5*factor, 0.*factor);
	glScalef(1, 0.2, 1);
	triangle(1.25 * factor, 0.5, 0.75, 0.5);		//Dreieck x- z-
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.*factor, 0.5*factor, 0.*factor);
	glScalef(1, 0.2, 1);
	triangle(1.25 * factor, 0.5, 0.5, 0.75);		//Dreieck x- z+
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0., 0.5*factor, 0.);
	glScalef(1, 0.2, 1);
	triangle(1.25 * factor, 0.5, 0.75, 0.5);		//Dreieck x+ z+
	glPopMatrix();
}

void engine(GLfloat factor, float engine_spin) {
	glPushMatrix();						//bis hierhin Triebwerk x- z+
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glRotatef(45, 0, 1, 0);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 1, 0);		//Triebwerk Gelb
	glRotatef(engine_spin, 0, 1, 0);					//Spin Rotation
	glTranslatef(0., 0.25*factor, 0.);
	glScalef(2.55*factor, 0.01*factor, 2.55*factor);
	spinner(1 * (factor/2));								//Spinner
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 0, 0);		//Triebwerk Rot
	glPopMatrix();
	glPushMatrix();						//bis hierhin Triebwerk x- z-
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glRotatef(45, 0, 1, 0);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 1, 0);		//Triebwerk Gelb
	glRotatef(engine_spin, 0, 1, 0);					//Spin Rotation
	glTranslatef(0., 0.25*factor, 0.);
	glScalef(2.55*factor, 0.01*factor, 2.55*factor);
	spinner(1 * (factor / 2));								//Spinner
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 0, 0);		//Triebwerk Rot
	glPopMatrix();
	glPushMatrix();						//bis hierhin Triebwerk x+ z-
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glRotatef(45, 0, 1, 0);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 1, 0);		//Triebwerk Gelb
	glRotatef(engine_spin, 0, 1, 0);					//Spin Rotation
	glTranslatef(0., 0.25*factor, 0.);
	glScalef(2.55*factor, 0.01*factor, 2.55*factor);
	spinner(1 * (factor / 2));								//Spinner
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 0, 0);		//Triebwerk Rot
	glPopMatrix();
	/*glPushMatrix();
	glRotatef(75, 0, 0, 1);
	glTranslatef(0.55*factor, 0.625*factor, 0.55*factor);
	glScalef(0.15, 0.5, 0.05);
	triangle(1 * factor, 1, 1, 1);
	glPopMatrix();*/
	glPushMatrix();						//bis hierhin Triebwerk x+ z+
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glRotatef(45, 0, 1, 0);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 1, 0);						//Triebwerk Gelb
	glRotatef(engine_spin, 0, 1, 0);					//Spin Rotation
	glTranslatef(0.,0.25*factor,0.);
	glScalef(2.55*factor, 0.01*factor, 2.55*factor);
	spinner(1 * (factor / 2));								//Spinner
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.55*factor, 0.375*factor, 0.55*factor);
	glScalef(0.15, 1., 0.15);
	Wuerfel2(0.5*factor, 1, 0, 0);		//Triebwerk Rot
	glPopMatrix();
}

void body(GLfloat factor, double claw_arm, float engine_spin)
{
	glPushMatrix();
	engine(factor, engine_spin);		//Triebwerke
	glPopMatrix();
	glPushMatrix();
	head(factor);		// Dreiecke (Dach)
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0., 0.375*factor, 0.); // Höhe bei Factor 1: 0,375 + 0,5 / 2 = 0,625
	glScalef(2.5, 0.5, 2.5);
	Wuerfel(0.5*factor);
	glPopMatrix();
	glTranslatef(0., -0.125 * (factor / 2) * (0.5 * claw_arm / 0.5 * (factor / 2)) + 0.25 * (factor), 0.); //Höhe bei Factor 1: 0,5 /2 = 0,25 + 0,125 = 0,375
	glScalef(0.5, 0.5*claw_arm*(factor /2), 0.5);	// y = 0.5 (default) Greifarm hier  darf im body nicht 1 sein
	Wuerfel(0.5*factor);	//unterstes Quadrat

							/*
							glPushMatrix();
							glTranslatef(0, 0.25*factor, 0.0*factor);
							glScalef(1.*factor, 0.5*factor, 2.*factor);
							Wuerfel(0.5*factor);
							glPopMatrix();
							glTranslatef(0.25*factor, 0.0*factor, 0.*factor);
							//triangle(0.5 * factor);
							glTranslatef(-0.25*factor, 0.0*factor, 0.*factor);
							glTranslatef(0, 0.25*factor, 0.*factor);


							triangle(0.5 * factor);
							glTranslatef(0, -0.60*factor, 0.*factor);//passt so
							glScalef(1. * factor, 1.*factor, 0.25*factor);
							Wuerfel(0.25*factor);

							glTranslatef(0.3, 0.3, 0); //T1
							//glPushMatrix();
							glTranslatef(-0.5, 0., 0.); //T2
							glScalef(0.5, 1., 1.); //S1
							Wuerfel(0.5*factor);
							//glPopMatrix();
							glTranslatef(0.5, 0., 0.); //Verschiebe ihn nach rechts
							glScalef(0.5, 1., 1.); //mache den Würfel kleiner
							Wuerfel(0.5*factor);*/
}
void spinner(GLfloat fSeitenL)
{
	glBegin(GL_TRIANGLES);
	glColor4f(0, 0, 0, 1.0f);
	glVertex3f(fSeitenL / 2.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, fSeitenL / 3.0f, 0.0f);
	glVertex3f(+0.0f, 2.0f, fSeitenL / 2.0f);
	glEnd();
}
void triangle(GLfloat fSeitenL, float red, float green, float blue)
{
	glBegin(GL_TRIANGLES);
	glColor4f(red, green, blue, 1.0f);
	glVertex3f(fSeitenL / 2.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, fSeitenL / 2.0f, 0.0f);
	glVertex3f(+0.0f, 0.0f, fSeitenL / 2.0f);
	glEnd();
}
