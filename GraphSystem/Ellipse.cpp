#include "Ellipse.h"
#include <GL\glut.h>


int Round(const float a) {
	return int(a + 0.5);
}

void DrawPixel(GLint xCoord, GLint yCoord) {
	glPointSize(1.5f);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y) {
	DrawPixel(xCenter + x, yCenter + y);
	DrawPixel(xCenter - x, yCenter + y);
	DrawPixel(xCenter + x, yCenter - y);
	DrawPixel(xCenter - x, yCenter - y);
}

void drawEllipseMidPoint(int xCenter, int yCenter, int Rx, int Ry) {
	int Rx2 = Rx*Rx, Ry2 = Ry*Ry;
	int twoRx2 = 2 * Rx2, twoRy2 = 2 * Ry2;
	int p;
	int x = 0, y = Ry;
	int px = 0, py = twoRx2*y;

	ellipsePlotPoints(xCenter, yCenter, x, y);

	p = Round((Ry2 - (Rx2*Ry) + (0.25*Rx2)));
	while (px<py) {
		x++;
		px += twoRy2;
		if (p<0)
			p += Ry2 + px;
		else {
			--y;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	p = Round((Ry2*(x + 0.5)*(x + 0.5) + Rx2*(y - 1)*(y - 1) - Rx2*Ry2));
	while (y > 0) {
		--y;
		py -= twoRx2;
		if (p>0)
			p += Rx2 - py;
		else {
			++x;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	glFlush();
}

bool pointInEllipse(int pointX, int pointY, int centerX, int centerY, int x, int y) {
	float xc = pointX - centerX;
	float yc = pointY - centerY;

	if ((((xc* xc) / (x*x)) + ((yc*yc) / (y*y))) < 1)
		return true;
	else return false;
}

void ellipseRender(int centerX, int centerY, int x, int y) {
	for (int i = 0; i < 600; i++)
		for (int j = 0; j < 600; j++)
			if (pointInEllipse(i, j, centerX, centerY, x, y)) {
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
				glFlush();
			}
}

void ellipseScale(float x, float y, int &ellipseX, int &ellipseY) {
	ellipseX *= x;
	ellipseY *= y;
}

void ellipseTranslate(float offsetX, float offsetY, int &ellipseX, int &ellipseY) {
	ellipseX += offsetX;
	ellipseY += offsetY;
}