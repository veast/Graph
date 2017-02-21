#include "Circle.h"
#include <GL\glut.h>
#include "Ellipse.h"


void drawCircleMidPoint(int x, int y, int radius) {
	drawEllipseMidPoint(x, y, radius, radius);
	glFlush();
}


void SetPixel(GLint xCoord, GLint yCoord) {
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void CirclePoints(int x, int y) {                       //根据对称性绘制整个圆
	SetPixel(x, y);
	SetPixel(-x, y);
	SetPixel(x, -y);
	SetPixel(-x, -y);
	SetPixel(y, x);
	SetPixel(y, -x);
	SetPixel(-y, x);
	SetPixel(-y, -x);
}

void MidPointCirle(int x, int y, int radius) {              //中点画圆
															//int x, y;
	float d;
	x = 0;
	y = radius;
	d = 1.25 - radius;
	CirclePoints(x, y);

	while (x <= y) {
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		CirclePoints(x, y);
	}
}