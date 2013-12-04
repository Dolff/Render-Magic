#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

int mMouseX;
int mMouseY;
GLint mouse1 = GLUT_UP;

void drawMenu() {
	glPushMatrix(); {
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(0.0,480.0);
			glVertex2f(0.0,512.0);
			glVertex2f(64.0,480.0);
			glVertex2f(64.0,512.0);
		}; glEnd();
	}; glPopMatrix();

/*TESTING FOR MOUSE FUNCTION */
/*	if (mouse1 == GLUT_DOWN) {
		glPushMatrix(); {
			glColor3f(0.0,1.0,0.0);
			glBegin(GL_TRIANGLE_STRIP); {
				glVertex2f(0.0,0.0);
				glVertex2f(0.0,64.0);
				glVertex2f(64.0,0.0);
				glVertex2f(64.0,64.0);
			} glEnd();
		}; glPopMatrix();
	} */
}

void menuMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		mouse1 = state;
	}
	
	mMouseX = x;
	mMouseY = y;
}













