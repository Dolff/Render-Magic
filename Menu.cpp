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

int transform = 0;

void drawMenu() {
	glPushMatrix(); {
		glColor3f(0.3,0.3,1.0);
		//translate button
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0,  32.0);
			glVertex2f( 128.0,  32.0);
			glVertex2f(  32.0,  96.0);
			glVertex2f( 128.0,  96.0);
		}; glEnd();
		if (transform == 0) {
			glPushMatrix(); {
				glColor3f(1.0,0.2,0.2);
				glBegin(GL_TRIANGLE_STRIP); {
					glVertex2f(  28.0,  28.0);
					glVertex2f(  28.0,  32.0);
					glVertex2f( 128.0,  28.0);
					glVertex2f( 128.0,  32.0);
					glVertex2f( 132.0,  28.0);
					glVertex2f( 128.0,  96.0);
					glVertex2f( 132.0, 100.0);
					glVertex2f(  32.0,  96.0);
					glVertex2f(  28.0, 100.0);
					glVertex2f(  32.0,  32.0);
					glVertex2f(  28.0,  32.0);
				}; glEnd();
			}; glPopMatrix();			
		}
		
		//scale button
		glColor3f(0.3,0.3,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0, 128.0);
			glVertex2f( 128.0, 128.0);
			glVertex2f(  32.0, 192.0);
			glVertex2f( 128.0, 192.0);
		}; glEnd();
		if (transform == 1) {
			glPushMatrix(); {
				glColor3f(1.0,0.2,0.2);
				glBegin(GL_TRIANGLE_STRIP); {
					glVertex2f(  28.0, 124.0);
					glVertex2f(  28.0, 128.0);
					glVertex2f( 128.0, 124.0);
					glVertex2f( 128.0, 128.0);
					glVertex2f( 132.0, 124.0);
					glVertex2f( 128.0, 192.0);
					glVertex2f( 132.0, 196.0);
					glVertex2f(  32.0, 192.0);
					glVertex2f(  28.0, 196.0);
					glVertex2f(  32.0, 128.0);
					glVertex2f(  28.0, 128.0);
				}; glEnd();
			}; glPopMatrix();			
		}
		
		//rotate button
		glColor3f(0.3,0.3,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0, 224.0);
			glVertex2f( 128.0, 224.0);
			glVertex2f(  32.0, 288.0);
			glVertex2f( 128.0, 288.0);
		}; glEnd();
		if (transform == 2) {
			glPushMatrix(); {
				glColor3f(1.0,0.2,0.2);
				glBegin(GL_TRIANGLE_STRIP); {
					glVertex2f(  28.0, 220.0);
					glVertex2f(  28.0, 224.0);
					glVertex2f( 128.0, 220.0);
					glVertex2f( 128.0, 224.0);
					glVertex2f( 132.0, 220.0);
					glVertex2f( 128.0, 288.0);
					glVertex2f( 132.0, 292.0);
					glVertex2f(  32.0, 288.0);
					glVertex2f(  28.0, 292.0);
					glVertex2f(  32.0, 224.0);
					glVertex2f(  28.0, 224.0);
				}; glEnd();
			}; glPopMatrix();			
		}
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
	
	if (mMouseX >=32 && mMouseX <=128) {
		if (mMouseY >= 32 && mMouseY <= 96) {
			transform = 0;
		} else if (mMouseY >= 128 && mMouseY <= 192) {
			transform = 1;
		} else if (mMouseY >= 224 && mMouseY <= 288) {
			transform = 2;
		}
	}
	std::cout << transform << std::endl;
}













