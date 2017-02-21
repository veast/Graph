#include <GL\glut.h>
#include "MouseFunc.h"
#include "Line.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Polygon.h"
#include "Curve.h"
#include "Cube.h"
#include <stack>
#include <alg.h>
#include <vector>

using namespace std;

//struct Coord {
//	GLfloat x;
//	GLfloat y;
//
//	Coord(GLfloat x, GLfloat y) :
//		x(x), y(y) {
//	}
//};

struct ellipse_data {
	int a;
	int b;
	GLfloat centerx;
	GLfloat centery;
	ellipse_data(int a, int b, GLfloat centerx, GLfloat centery) :a(a), b(b), centerx(centerx), centery(centery) {

	}
};

struct curve_data {
	int num;
	int *pts_x;
	int *pts_y;
	curve_data(int num, int *pts_x, int*pts_y) :num(num), pts_x(pts_x), pts_y(pts_y) {

	}
};


stack<Coord> g_pts_stk;			//storage of temporary points;
vector<Poly_t> g_poly_vec;		//storage of all the polygons;

vector<curve_data> g_curve;
vector<ellipse_data> g_ellipse;
vector<line_data> g_line;

//�ֹ���
void mouseFuncDrawLine(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(Coord(x, y));
		}
		else if (state == GLUT_UP) {
			Coord startpoint(g_pts_stk.top());
			g_pts_stk.pop();
			drawLineDDA(startpoint.x, startpoint.y, x, y);
			//
			Coord end(x, y);
			if (startpoint.x != end.x &&startpoint.y != end.y) {
				line_data line(startpoint, end);
				g_line.push_back(line);
			}
		}
	}
}

void mouseFuncDrawCircle(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(Coord(x, y));
		}
		else if (state == GLUT_UP) {
			Coord startpoint(g_pts_stk.top());
			g_pts_stk.pop();
			GLfloat radius = min(abs(startpoint.x - x) / 2,
				abs(startpoint.y - y) / 2);
			GLfloat centerX = startpoint.x + radius;
			GLfloat centerY = startpoint.y + radius;
			drawCircleMidPoint(centerX, centerY, radius);
		}
	}
}

void mouseFuncDrawEllipse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(Coord(x, y));
		}
		else if (state == GLUT_UP) {
			Coord startpoint(g_pts_stk.top());
			g_pts_stk.pop();
			GLfloat centerX = startpoint.x / 2 + x / 2;
			GLfloat centerY = startpoint.y / 2 + y / 2;
			GLfloat ra = abs(x - startpoint.x) / 2;
			GLfloat rb = abs(y - startpoint.y) / 2;
			drawEllipseMidPoint(centerX, centerY, ra, rb);

			ellipse_data ellipse(ra, rb, centerX, centerY);
			g_ellipse.push_back(ellipse);
		}
	}
}

void mouseFuncDrawPolygon(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			Coord pt(x, y);
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(pt);
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_UP) {
			int num = g_pts_stk.size();
			float *pts_x = new float[num];
			float *pts_y = new float[num];
			for (int i = 0; i < num; i++) {
				pts_x[i] = g_pts_stk.top().x;
				pts_y[i] = g_pts_stk.top().y;
				g_pts_stk.pop();
			}
			drawPolygon(pts_x, pts_y, num);
			g_poly_vec.push_back(Poly_t(pts_x, pts_y, num));
		}
	}
}

void mouseFuncDrawCurve(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			Coord pt(x, y);
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(pt);
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_UP) {
			int num = g_pts_stk.size();
			int *pts_x = new int[num];
			int *pts_y = new int[num];
			for (int i = 0; i < num; i++) {
				pts_x[i] = g_pts_stk.top().x;
				pts_y[i] = g_pts_stk.top().y;
				g_pts_stk.pop();
			}

			drawCurveBsp(pts_x, pts_y, num, 100);
			curve_data curve(num, pts_x, pts_y);
			g_curve.push_back(curve);
		}
	}
}

void mouseFuncDrawCube(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			glColor3f(1.0f, 0.0f, 0.0f);
			glPointSize(2.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			drawCube(x, y, 0);
			glFlush();
		}
	}
}

void mouseFuncRender(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			for (Poly_t p : g_poly_vec) {
				if (isInsidePolygon(p.pts_x, p.pts_y, p.num, x, y)) {
					renderPolygon(p);
				}
			}
		}
	}
}

//ƽ��
void lineTransEvent() {
	if (g_line.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_line.size(); i++) {
		cout << "ֱ�� " << i << ":" << "(" << g_line[i].start.x << "," << g_line[i].start.y << ")" << " --> " << "(" << g_line[i].end.x << "," << g_line[i].end.y << ")" << endl;
	}
	int n;
	cout << "������Ҫƽ�Ƶ�ֱ�߱��" << endl;
	cin >> n;
	if (n >= (int)g_line.size()) {
		cout << "����������" << endl;
		return;
	}
	int offsetx = 0;
	int offsety = 0;

	cout << "������x��仯��" << endl;;
	cin >> offsetx;

	cout << "������y��仯��" << endl;;
	cin >> offsety;
	
	g_line[n].start.x += offsetx;
	g_line[n].start.y += offsety;
	g_line[n].end.x += offsetx;
	g_line[n].end.y += offsety;

	drawLineDDA(g_line[n].start.x, g_line[n].start.y, g_line[n].end.x, g_line[n].end.y);
}

void polygonTransEvent() {
	if (g_poly_vec.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_poly_vec.size(); i++) {
		cout << "����� " << i << " num:" << g_poly_vec[i].num << endl;;
	}
	int n;
	cout << "������Ҫƽ�ƵĶ���α��" << endl;
	cin >> n;
	if (n >= (int)g_poly_vec.size()) {
		cout << "����������" << endl;
		return;
	}
	int offsetx = 0;
	int offsety = 0;

	cout << "������x�᷽��仯��" << endl;;
	cin >> offsetx;

	cout << "������y�᷽��仯��" << endl;;
	cin >> offsety;
	for (int i = 0; i < g_poly_vec[n].num; i++) {
		g_poly_vec[n].pts_x[i] += offsetx;
		g_poly_vec[n].pts_y[i] += offsety;
	}
	drawPolygon(g_poly_vec[n].pts_x, g_poly_vec[n].pts_y, g_poly_vec[n].num);
}

void ellipseTransEvent() {
	if (g_ellipse.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_ellipse.size(); i++) {
		cout << "��Բ " << i << " ����:" << g_ellipse[i].centerx << "," << g_ellipse[i].centery << endl;
	}
	int n;
	cout << "������Ҫƽ�Ƶ���Բ���" << endl;
	cin >> n;
	if (n >= (int)g_ellipse.size()) {
		cout << "����������" << endl;
		return;
	}
	int offsetx = 0;
	int offsety = 0;

	cout << "������x�᷽��仯��" << endl;;
	cin >> offsetx;

	cout << "������y�᷽��仯��" << endl;;
	cin >> offsety;
	g_ellipse[n].centerx += offsetx;
	g_ellipse[n].centery += offsety;
	drawEllipseMidPoint(g_ellipse[n].centerx, g_ellipse[n].centery, g_ellipse[n].a, g_ellipse[n].b);
}

void curveTransEvent() {
	if (g_curve.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_curve.size(); i++) {
		cout << "���� " << i << endl;;
	}
	int n;
	cout << "������Ҫƽ�Ƶ����߱��" << endl;
	cin >> n;
	if (n >= (int)g_curve.size()) {
		cout << "����������" << endl;
		return;
	}
	int offsetx = 0;
	int offsety = 0;

	cout << "������x����仯��" << endl;;
	cin >> offsetx;

	cout << "������y�᷽��仯��" << endl;;
	cin >> offsety;
	for (int i = 0; i < g_curve[n].num; i++) {
		g_curve[n].pts_x[i] += offsetx;
		g_curve[n].pts_y[i] += offsety;
	}
	drawCurveBsp(g_curve[n].pts_x, g_curve[n].pts_y, g_curve[n].num, 100);
}

//��ת
void lineRotateEvent() {
	if (g_line.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_line.size(); i++) {
		cout << "ֱ�� " << i << ":" << "(" << g_line[i].start.x << "," << g_line[i].start.y << ")" << " --> " << "(" << g_line[i].end.x << "," << g_line[i].end.y << ")" << endl;
	}
	int n;
	cout << "������Ҫ��ת��ֱ�߱��" << endl;
	cin >> n;
	if (n >= (int)g_line.size()) {
		cout << "����������" << endl;
		return;
	}
	float angle = 0;

	cout << "��������ת�Ƕ�" << endl;;

	cin >> angle;

	float x = abs(g_line[n].start.x - g_line[n].end.x);
	float y = abs(g_line[n].start.y - g_line[n].end.y);
	double thisangle = 180 * atan(y / x) / 3.14159265358;
	double newagle = thisangle + angle;
	double leng = sqrt(x*x + y*y);

	g_line[n].end.x = g_line[n].start.x + leng*sin(newagle*3.141592653 / 180);
	g_line[n].end.y = g_line[n].start.y + leng*cos(newagle*3.141592653 / 180);

	drawLineDDA(g_line[n].start.x, g_line[n].start.y, g_line[n].end.x, g_line[n].end.y);
}

void polygonRotateEvent() {
	if (g_poly_vec.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_poly_vec.size(); i++) {
		cout << "����� " << i << " num:" << g_poly_vec[i].num << endl;;
	}
	int n;
	cout << "������Ҫ��ת�Ķ���α��" << endl;
	cin >> n;
	if (n >= (int)g_poly_vec.size()) {
		cout << "����������" << endl;
		return;
	}
	float angle = 0;

	cout << "������ת�Ƕȣ�" << endl;
	cin >> angle;
	float radian = angle / 360 * 3.14159265358979323846;
	for (int i = 0; i < n; i++) {
		float a = pow(pow(g_poly_vec[n].pts_x[i], 2) + pow(g_poly_vec[n].pts_y[i], 2), 0.5);
		g_poly_vec[n].pts_x[i] = a*(cos(radian + acos(g_poly_vec[n].pts_x[i] / a)));
		g_poly_vec[n].pts_y[i] = a*(sin(radian + acos(g_poly_vec[n].pts_y[i] / a)));
	}

	drawPolygon(g_poly_vec[n].pts_x, g_poly_vec[n].pts_y, g_poly_vec[n].num);
}

void ellipseRotateEvent() {
	if ((int)g_ellipse.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_ellipse.size(); i++) {
		cout << "��Բ " << i << " ����:" << g_ellipse[i].centerx << "," << g_ellipse[i].centery << endl;
	}
	int n;
	cout << "������Ҫ��ת����Բ���" << endl;

	cin >> n;
	if (n >= (int)g_ellipse.size()) {
		cout << "����������" << endl;
		return;
	}
	if (n >= (int)g_ellipse.size()) {
		cout << "����������" << endl;
		return;
	}
	float angle = 0;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cout << "������Ƕ�" << endl;;
	cin >> angle;
	drawEllipseMidPoint(g_ellipse[n].centerx, g_ellipse[n].centery, g_ellipse[n].a, g_ellipse[n].b);
}

void curveRotateEvent() {
	if (g_curve.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_curve.size(); i++) {
		cout << "���� " << i << endl;;
	}
	int n;
	cout << "������Ҫ��ת�����߱��" << endl;
	cin >> n;
	if (n >= (int)g_curve.size()) {
		cout << "����������" << endl;
		return;
	}
	int offsetx = 0;


	cout << "������Ƕ�" << endl;;
	cin >> offsetx;
	drawCurveBsp(g_curve[n].pts_x, g_curve[n].pts_y, g_curve[n].num, 100);
}

//����
void lineScalEvent() {
	if (g_line.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_line.size(); i++) {
		cout << "ֱ�� " << i << ":" << "(" << g_line[i].start.x << "," << g_line[i].start.y << ")" << " --> " << "(" << g_line[i].end.x << "," << g_line[i].end.y << ")" << endl;
	}
	int n;
	cout << "������Ҫ���ŵ�ֱ�߱��" << endl;
	cin >> n;
	if (n >= (int)g_line.size()) {
		cout << "����������" << endl;
		return;
	}
	double offsetx = 0;
	double offsety = 0;

	cout << "������x�᷽�����" << endl;;
	scanf("%lf", &offsetx);

	cout << "������y�᷽�����" << endl;;
	scanf("%lf", &offsety);
	cout << offsety << endl;///////////

	g_line[n].start.x *= offsetx;
	g_line[n].start.y *= offsety;
	g_line[n].end.x *= offsetx;
	g_line[n].end.y *= offsety;

	drawLineDDA(g_line[n].start.x, g_line[n].start.y, g_line[n].end.x, g_line[n].end.y);
}

void polygonScalEvent() {
	if (g_poly_vec.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_poly_vec.size(); i++) {
		cout << "����� " << i << " num:" << g_poly_vec[i].num << endl;;
	}
	int n;
	cout << "������Ҫ���ŵĶ���α��" << endl;
	cin >> n;
	if (n >= (int)g_poly_vec.size()) {
		cout << "����������" << endl;
		return;
	}
	double offsetx = 0;
	double offsety = 0;

	cout << "������x�᷽�����" << endl;;
	scanf("%lf", &offsetx);

	cout << "������y�᷽�����" << endl;;
	scanf("%lf", &offsety);
	for (int i = 0; i < g_poly_vec[n].num; i++) {
		g_poly_vec[n].pts_x[i] *= offsetx;
		g_poly_vec[n].pts_y[i] *= offsety;
	}
	drawPolygon(g_poly_vec[n].pts_x, g_poly_vec[n].pts_y, g_poly_vec[n].num);
}

void ellipsescalEvent() {

	if (g_ellipse.size() == 0)
	{
		cout << "δ������Բͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_ellipse.size(); i++) {
		cout << "ellipse " << i << " ����:" << g_ellipse[i].centerx << "," << g_ellipse[i].centery << endl;
	}
	int n;
	cout << "������Ҫ���ŵ���Բ���" << endl;
	cin >> n;
	if (n >= (int)g_ellipse.size()) {
		cout << "����������" << endl;
		return;
	}
	double offsetx = 0;
	double offsety = 0;

	cout << "������offsetx" << endl;;
	scanf("%lf", &offsetx);

	cout << "������offsety" << endl;;
	scanf("%lf", &offsety);
	g_ellipse[n].centerx *= offsetx;
	g_ellipse[n].centery *= offsety;
	drawEllipseMidPoint(g_ellipse[n].centerx, g_ellipse[n].centery, g_ellipse[n].a, g_ellipse[n].b);
}

void curveScalEvent() {
	if (g_curve.size() == 0) {
		cout << "���޴洢ͼ��" << endl;
		return;
	}
	for (int i = 0; i < (int)g_curve.size(); i++) {
		cout << " curve" << i << endl;;
	}
	int n;
	cout << "������Ҫ���ŵ����߱��" << endl;
	cin >> n;
	if (n >= (int)g_curve.size()) {
		cout << "����������" << endl;
		return;
	}
	double offsetx = 0;
	double offsety = 0;

	cout << "������x�᷽�����" << endl;;
	scanf("%lf", &offsetx);

	cout << "������y�᷽�����" << endl;;
	scanf("%lf", &offsety);
	for (int i = 0; i < g_curve[n].num; i++) {
		g_curve[n].pts_x[i] *= offsetx;
		g_curve[n].pts_y[i] *= offsety;
	}
	drawCurveBsp(g_curve[n].pts_x, g_curve[n].pts_y, g_curve[n].num, 100);
}

//�ü�
void polygonClipEvent(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			Coord pt(x, y);
			glPointSize(2);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			glFlush();
			g_pts_stk.push(pt);
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_UP) {
			int num = g_pts_stk.size();
			float *pts_x = new float[num];
			float *pts_y = new float[num];
			for (int i = 0; i < num; i++) {
				pts_x[i] = g_pts_stk.top().x;
				pts_y[i] = g_pts_stk.top().y;
				g_pts_stk.pop();
			}
			for (int i = 0; i < (int)g_poly_vec.size(); i++) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				clip(g_poly_vec[i], Poly_t(pts_x, pts_y, num));
			}
		}
	}
}

//�˵���ѡ��
void processSubMenuDraw(int option) {
	switch (option) {
	case 0:
		glutMouseFunc(mouseFuncDrawLine);
		break;
	case 1:
		glutMouseFunc(mouseFuncDrawCurve);
		break;
	case 2:
		glutMouseFunc(mouseFuncDrawEllipse);
		break;
	case 3:
		glutMouseFunc(mouseFuncDrawCircle);
		break;
	case 4:
		glutMouseFunc(mouseFuncDrawPolygon);
		break;
	case 5:
		glutMouseFunc(mouseFuncDrawCube);
		break;
	default:
		break;
	}
}

void processMenuEvents(int option) {
	switch (option) {
	case 0:
		glutMouseFunc(mouseFuncRender);
		glFlush();
		break;
	case 1:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		g_poly_vec.clear();
		glFlush();
		break;
	default:
		break;
	}
}

void processChangeMenuEvents(int option) {
	switch (option) {
	case 0:
		lineTransEvent();
		break;
	case 1:
		curveTransEvent();
		break;
	case 2:
		ellipseTransEvent(); break;
	case 3:
		polygonTransEvent(); break;
	default:
		break;
	}
}

void processClipmenuEvents(int option) {
	switch (option) {
	case 0:
		glutMouseFunc(polygonClipEvent);
		break;
	case 1:
		
		break;

	default:
		break;
	}
}

void processRotateMenuEvents(int option) {
	switch (option) {
	case 0:
		lineRotateEvent();
		break;
	case 1:
		curveRotateEvent();
		break;
	case 2:
		ellipseRotateEvent(); break;
	case 3:
		polygonRotateEvent(); break;
	default:
		break;
	}
}

void processScalMenuEvents(int option) {
	switch (option) {
	case 0:
		lineScalEvent();
		break;
	case 1:
		curveScalEvent();
		break;
	case 2:
		ellipsescalEvent(); break;
	case 3:
		polygonScalEvent(); break;
	default:
		break;
	}
}

void processTransformMenuEvents(int option) {
	switch (option) {
	case 0:
		//LinescalEvent();
		break;
	case 1:
		//curvescalEvent();
		break;
	case 2:
		//ellipsescalEvent(); 
		break;
	case 3:
		//polygonscalEvent(); 
		break;
	default:
		break;
	}
}

//�˵�ѡ��
void createMenus() {
	int submenu_create = glutCreateMenu(processSubMenuDraw);
	glutAddMenuEntry("ֱ��", 0);
	glutAddMenuEntry("����", 1);
	glutAddMenuEntry("��Բ", 2);
	glutAddMenuEntry("Բ", 3);
	glutAddMenuEntry("�����", 4);
	glutAddMenuEntry("������", 5);

	int changemenu_create = glutCreateMenu(processChangeMenuEvents);//ƽ��
	glutAddMenuEntry("ֱ��", 0);
	glutAddMenuEntry("����", 1);
	glutAddMenuEntry("��Բ", 2);
	glutAddMenuEntry("�����", 3);

	int rotatemenu_create = glutCreateMenu(processRotateMenuEvents);//��ת
	glutAddMenuEntry("ֱ��", 0);
	glutAddMenuEntry("����", 1);
	glutAddMenuEntry("��Բ", 2);
	glutAddMenuEntry("�����", 3);

	int scalmenu_create = glutCreateMenu(processScalMenuEvents);//����
	glutAddMenuEntry("ֱ��", 0);
	glutAddMenuEntry("����", 1);
	glutAddMenuEntry("��Բ", 2);
	glutAddMenuEntry("�����", 3);

	int clipmenu_create = glutCreateMenu(processClipmenuEvents);//�ü�
	glutAddMenuEntry("�����", 0);

	int transfmenu_create = glutCreateMenu(processTransformMenuEvents);//ͼ�α任
	glutAddSubMenu("ƽ��", changemenu_create);
	glutAddSubMenu("��ת", rotatemenu_create);
	glutAddSubMenu("����", scalmenu_create);
	glutAddSubMenu("�ü�", clipmenu_create);

	int menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("ͼ�λ���", submenu_create);
	glutAddSubMenu("ͼ�α任", transfmenu_create);
	glutAddMenuEntry("�������", 0);
	glutAddMenuEntry("����", 1);
	glutAddMenuEntry("����ͼ��", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
