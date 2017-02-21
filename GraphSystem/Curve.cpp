#include "Curve.h"
#include "Line.h"
#include <GL\glut.h>



void drawCurveBsp(int *pts_x, int *pts_y, int pts_num, int n) {
	glPointSize(1.2);
	glLineWidth(1.2);
	glColor3f(0.0f, 0.0f, 1.0f);
	float f1, f2, f3, f4;
	float deltaT = 1.0 / n;
	float T;
	int num_seg = pts_num - 3;

	glBegin(GL_LINE_STRIP);
	for (int num = 0; num < num_seg; num++) {
		for (int i = 0; i <= n; i++) {

			T = i * deltaT;

			f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
			f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
			f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
			f4 = (T*T*T) / 6.0;

			glVertex2f(f1*pts_x[num] + f2*pts_x[num + 1] + f3*pts_x[num + 2] + f4*pts_x[num + 3],
				f1*pts_y[num] + f2*pts_y[num + 1] + f3*pts_y[num + 2] + f4*pts_y[num+3]);
		}
	}

	glEnd();
	glFlush();
}
