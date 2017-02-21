#include <GL/glut.h>
#include <stdio.h>

#include "MouseFunc.h"


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("图形学图形编辑处理系统");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	//800 600
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 1000, 600, 0, -500, 500);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutDisplayFunc([]() {});
	createMenus();

	glutMainLoop();
	return 0;
}