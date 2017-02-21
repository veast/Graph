#include "Line.h"
#include <GL\glut.h>
#include <math.h>

void drawLineDDA(int xa, int ya, int xb, int yb) {
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(3.0f);

	int dx = xb - xa;
	int dy = yb - ya;
	int steps, k;

	float xIncrement, yIncrement, x = xa, y = ya;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	xIncrement = (float)(dx) / (float)(steps);
	yIncrement = (float)(dy) / (float)(steps);

	for (k = 0; k < steps; k++) {
		glBegin(GL_POINTS);
		glVertex2i(round(x), round(y));
		glEnd();
		x += xIncrement;
		y += yIncrement;
	}
	glFlush();
}

GLfloat max(GLfloat a, GLfloat b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}
GLfloat min(GLfloat a, GLfloat b) {
	if (a <= b) {
		return a;
	}
	else {
		return b;
	}
}

int Intersect(line_data this_line, line_data another_line, Coord& intersect_point) {
	if (this_line.start.x - this_line.end.x == 0 && another_line.start.x - another_line.end.x == 0) {  //both vertical
		if (this_line.start.x == another_line.start.x) return 1;		// same
		else return -1;			// parallel
	}
	if (this_line.start.x - this_line.end.x == 0) {	//this line vertical
		double a_other, b_other;
		b_other = (another_line.start.x * another_line.end.y - another_line.start.y * another_line.end.x) / (another_line.start.x - another_line.end.x);
		a_other = (another_line.start.y - another_line.end.y) / (another_line.start.x - another_line.end.x);
		double x = this_line.start.x, y = a_other * this_line.start.x + b_other;
		if (x >= min(this_line.start.x, this_line.end.x) && x <= max(this_line.start.x, this_line.end.x)
			&& x >= min(another_line.start.x, another_line.end.x)
			&& x <= max(another_line.start.x, another_line.end.x)) {
			intersect_point.x = x;
			intersect_point.y = y;
			return 0; //intersect
		}
		else {
			return -1; //out bounds
		}
	}
	if (another_line.start.x - another_line.end.x == 0) {		//another line vertical
		double a_my, b_my;
		b_my = (this_line.start.x * this_line.end.y - this_line.start.y * this_line.end.x) / (this_line.start.x - this_line.end.x);
		a_my = (this_line.start.y - this_line.end.y) / (this_line.start.x - this_line.end.x);
		double x = another_line.start.x, y = another_line.start.x * a_my + b_my;
		if (x >= min(this_line.start.x, this_line.end.x) && x <= max(this_line.start.x, this_line.end.x)
			&& x >= min(another_line.start.x, another_line.end.x)
			&& x <= max(another_line.start.x, another_line.end.x)) {
			intersect_point.x = x;
			intersect_point.y = y;
			return 0; //intersect
		}
		else {
			return -1; //out bounds
		}
	}
	/* y = ax + b */
	double a_my, b_my;
	b_my = (this_line.start.x * this_line.end.y - this_line.start.y * this_line.end.x) / (this_line.start.x - this_line.end.x);
	a_my = (this_line.start.y - this_line.end.y) / (this_line.start.x - this_line.end.x);



	double a_other, b_other;
	b_other = (another_line.start.x * another_line.end.y - another_line.start.y * another_line.end.x) / (another_line.start.x - another_line.end.x);
	a_other = (another_line.start.y - another_line.end.y) / (another_line.start.x - another_line.end.x);

	if (a_other == a_my) {
		if (b_my == b_other) {
			return 1; //same
		}
		else {
			return -1; //parallel
		}
	}
	else {
		double x = (b_other - b_my) / (a_my - a_other);
		double y = a_my * x + b_my;
		if (x >= min(this_line.start.x, this_line.end.x) && x <= max(this_line.start.x, this_line.end.x)
			&& x >= min(another_line.start.x, another_line.end.x)
			&& x <= max(another_line.start.x, another_line.end.x)) {
			intersect_point.x = x;
			intersect_point.y = y;
			return 0; //intersect
		}
		else {
			return -1; //out bounds
		}
	}
}

void SwapInt(int &x, int &y) {
	int tmp = x;
	x = y;
	y = tmp;
}

void lineBres(int xa, int ya, int xb, int yb) {
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(3.0f);
	GLint dx, dy, d, UpIncre, DownIncre, x, y;

	if (xa > xb) {				//横坐标小->横坐标大
		SwapInt(xa, xb);
		SwapInt(ya, yb);
	}
	x = xa;
	y = ya;
	dx = xb - xa;
	dy = yb - ya;
	if (dy > 0 && dy <= dx) {			//0<斜率<=1
		d = dx - 2 * dy;
		UpIncre = 2 * dx - 2 * dy;
		DownIncre = -2 * dy;

		while (x <= xb) {
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			x++;
			if (d<0) {
				y++;
				d += UpIncre;
			}
			else
				d += DownIncre;
		}
	}
	else if ((dy >(-dx)) && dy < 0) {				//-1<斜率<=0
		d = dx - 2 * dy;
		UpIncre = -2 * dy;
		DownIncre = -2 * dx - 2 * dy;

		while (x <= xb) {
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			x++;
			if (d > 0) {
				y--;
				d += DownIncre;
			}
			else
				d += UpIncre;
		}
	}
	else if (dy < (-dx)) {							//斜率<-1
		d = -dy - 2 * dx;
		UpIncre = 2 * dx + 2 * dy;
		DownIncre = 2 * dx;

		while (y >= yb) {
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			y--;
			if (d < 0) {
				x++;
				d -= UpIncre;
			}
			else
				d -= DownIncre;
		}
	}
	else {										 //斜率>1
		d = dy - 2 * dx;
		UpIncre = 2 * dy - 2 * dx;
		DownIncre = -2 * dx;

		while (y <= yb) {
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			y++;
			if (d < 0) {
				x++;
				d += UpIncre;
			}
			else
				d += DownIncre;
		}
	}
	glFlush();
}