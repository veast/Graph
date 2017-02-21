#include "Cube.h"
#include <GL\glut.h>

#include "Line.h"

#define HD 100


void drawCube(float centerX, float centerY, float centerZ) {
	glPushMatrix();
	glRotatef(20, 0, 1, 0);
	glRotatef(20, 1, 0, 0);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(1.2f);
	glBegin(GL_LINES);
	glVertex3f(centerX + HD, centerY + HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX + HD, centerY + HD, centerZ + HD);

	glVertex3f(centerX + HD, centerY + HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ - HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ - HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ - HD);
	glVertex3f(centerX + HD, centerY + HD, centerZ - HD);

	glVertex3f(centerX + HD, centerY + HD, centerZ + HD);
	glVertex3f(centerX + HD, centerY + HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY + HD, centerZ - HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX - HD, centerY - HD, centerZ - HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ + HD);
	glVertex3f(centerX + HD, centerY - HD, centerZ - HD);
	glEnd();
	glFlush();

	glRotatef(-20, 0, 1, 0);
	glRotatef(-20, 1, 0, 0);
	glPopMatrix();
}