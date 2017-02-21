#pragma once
#include<iostream>
#include "Line.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Polygon.h"
#include "Curve.h"
#include "Cube.h"
#include <GL\glut.h>
using namespace std;

class Coord {
public:
	GLfloat x;
	GLfloat y;
	Coord() {
	}
	Coord(GLfloat x, GLfloat y) :
		x(x), y(y) {
	}
};
struct line_data {
	Coord start;
	Coord end;
	line_data(Coord start, Coord end) :
		start(start), end(end) {
	}
};
GLfloat max(GLfloat a, GLfloat b);
GLfloat min(GLfloat a, GLfloat b);

void drawLineDDA(int xa, int ya, int xb, int yb);
int Intersect(line_data this_line, line_data another_line, Coord& intersect_point);