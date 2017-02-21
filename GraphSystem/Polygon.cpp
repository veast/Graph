#include "Polygon.h"
#include "Line.h"
#include <GL\glut.h>
#include <vector>
#include <algorithm>
using namespace std;

bool isInsidePolygon(float *x, float *y, int num, float a, float b) {

	size_t   i, j = num - 1;
	bool  oddNodes = false;

	for (i = 0; i < num; i++) {
		if ((y[i] < b && y[j] >= b || y[j] < b && y[i] >= b) 
			&& (x[i] <= a || x[j] <= a)) {
			oddNodes ^= (x[i] + (b - y[i]) / (y[j] - y[i])*(x[j] - x[i]) < a);
		}
		j = i;
	}

	return oddNodes;
}

void drawPolygon(float *pts_x, float *pts_y, int num) {
	if (num < 3) return;
	for (int i = 0; i < num - 1; i++) {
		drawLineDDA(pts_x[i], pts_y[i], pts_x[i + 1], pts_y[i + 1]);
	}
	drawLineDDA(pts_x[num - 1], pts_y[num - 1], pts_x[0], pts_y[0]);
}

void renderPolygon(Poly_t poly) {
	std::initializer_list<float> x_list(&(poly.pts_x[0]), &(poly.pts_x[poly.num]));
	std::initializer_list<float> y_list(&(poly.pts_y[0]), &(poly.pts_y[poly.num]));
	int min_x = min(x_list), max_x = max(x_list);
	int min_y = min(y_list), max_y = max(y_list);
	for (int i = min_x - 5; i <= max_x + 5; i++) {
		for (int j = min_y - 5; j <= max_y + 5; j++) {
			if (isInsidePolygon(poly.pts_x, poly.pts_y, poly.num, i, j)) {
				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POINTS);
				glVertex2i(i, j);
				glEnd();
				glFlush();
			}
		}
	}

}

void clip(Poly_t coords, Poly_t window) {
	vector<Coord> keyPoints;
	for (size_t i = 0; i < coords.num; i++) {
		Coord a, b;
		if (i == coords.num - 1) {
			a.x = coords.pts_x[i];
			a.y = coords.pts_y[i];
			b.x = coords.pts_x[0];
			b.y = coords.pts_y[0];
		}
		else {
			a.x = coords.pts_x[i];
			a.y = coords.pts_y[i];
			b.x = coords.pts_x[i + 1];
			b.y = coords.pts_y[i + 1];
		}
		if (!isInsidePolygon(window.pts_x, window.pts_y, window.num, a.x, a.y) && isInsidePolygon(window.pts_x, window.pts_y, window.num, b.x, b.y)) {
			line_data l(a, b);
			Coord inter;
			for (size_t j = 0; j < window.num - 1; j++) {
				Coord start(window.pts_x[j], window.pts_y[j]);
				Coord end(window.pts_x[j + 1], window.pts_y[j + 1]);
				line_data another_line(start, end);
				if (Intersect(l, another_line, inter) == 0) keyPoints.push_back(inter);
			}
			Coord start(window.pts_x[window.num - 1], window.pts_y[window.num - 1]);
			Coord end(window.pts_x[0], window.pts_y[0]);
			line_data another_line(start, end);
			if (Intersect(l, another_line, inter) == 0) keyPoints.push_back(inter);
			keyPoints.push_back(b);
		}
		else if (isInsidePolygon(window.pts_x, window.pts_y, window.num, a.x, a.y) && isInsidePolygon(window.pts_x, window.pts_y, window.num, b.x, b.y)) {
			keyPoints.push_back(b);
		}
		else if (isInsidePolygon(window.pts_x, window.pts_y, window.num, a.x, a.y) && !isInsidePolygon(window.pts_x, window.pts_y, window.num, b.x, b.y)) {
			line_data l(a, b);
			Coord inter;
			for (size_t j = 0; j < window.num - 1; j++) {
				Coord start(window.pts_x[j], window.pts_y[j]);
				Coord end(window.pts_x[j + 1], window.pts_y[j + 1]);
				line_data another_line(start, end);
				if (Intersect(l, another_line, inter) == 0) keyPoints.push_back(inter);
			}
			Coord start(window.pts_x[window.num - 1], window.pts_y[window.num - 1]);
			Coord end(window.pts_x[0], window.pts_y[0]);
			line_data another_line(start, end);
			if (Intersect(l, another_line, inter) == 0) keyPoints.push_back(inter);
		}
		else {
			vector<Coord> tmp;
			line_data l(a, b);
			Coord inter;

			for (size_t j = 0; j < window.num - 1; j++) {
				Coord start(window.pts_x[j], window.pts_y[j]);
				Coord end(window.pts_x[j + 1], window.pts_y[j + 1]);
				line_data another_line(start, end);
				if (Intersect(l, another_line, inter) == 0) tmp.push_back(inter);
			}
			Coord start(window.pts_x[window.num - 1], window.pts_y[window.num - 1]);
			Coord end(window.pts_x[0], window.pts_y[0]);
			line_data another_line(start, end);
			if (Intersect(l, another_line, inter) == 0) tmp.push_back(inter);

			auto cmp = [=](Coord x, Coord y) {
				return pow((x.x - a.x), 2) + pow((x.y - a.y), 2) < pow((y.x - a.x), 2) + pow((y.y - a.y), 2);
			};
			sort(tmp.begin(), tmp.end(), cmp);

			for (Coord &p : tmp) keyPoints.push_back(p);
		}
	}
	float *keyx = new float[100];
	float *keyy = new float[100];
	int keynum = 0;
	for (int i = 0; i < (int)keyPoints.size(); i++)
	{
		keyx[i] = keyPoints[i].x;
		keyy[i] = keyPoints[i].y;
	}
	if (keyPoints.size()>2)
		drawPolygon(keyx, keyy, keyPoints.size());
}
