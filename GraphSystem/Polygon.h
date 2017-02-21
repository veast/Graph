#pragma once

struct Poly_t {
	float *pts_x;
	float *pts_y;
	int num;

	Poly_t(float *pts_x, float *pts_y, int num)
		: pts_x(pts_x)
		, pts_y(pts_y)
		, num(num) {
	}
};

void drawPolygon(float *pts_x, float *pts_y, int num);
void renderPolygon(Poly_t poly);
bool isInsidePolygon(float *x, float *y, int num, float a, float b);
void clip(Poly_t coords, Poly_t window);