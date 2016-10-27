/*
wuerfel.cpp definiert einen Würfel über seine 6 Seiten
Last Update:  13.10.2011   W.-D. Groch
*/
#include <GL/freeglut.h>
#include "Figure.h"


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
