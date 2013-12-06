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

void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;

	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}

	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}

}

void drawColors() {
	float r,g,b;
	glPushMatrix(); {
		glBegin(GL_QUAD_STRIP); {
			for (float i = 0.0; i < 360.0; ++i) {
				HSVtoRGB(&r,&g,&b,i,1.0,1.0);
				glColor3f(r,g,b);
				glVertex2f(i+32.0,512-32);
				glVertex2f(i+32.0,512-64);
			}
		}; glEnd();
	}; glPopMatrix();
}

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
	
	drawColors();

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















