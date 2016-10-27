#pragma once
void Wuerfel(GLfloat fSeitenL); // Würfel mit Seitenlänge
void coordinatesystem(); // Zeigt ein Koordinatensystem an. xyz = 10.0
void triangle(GLfloat fSeitenL, float red, float green, float blue);
void body(GLfloat factor, double claw_arm, float engine_spin); // Körper der Drohne mit Greifarm
void head(GLfloat factor); // 4 Dreiecke als Kopf
void spinner(GLfloat fSeitenL);
void ground();
