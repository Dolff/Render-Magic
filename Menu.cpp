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
int lightNum = 0;
bool moveToggle = true;
bool gridOn = true;
vector<bool> lightsOn;


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

void outline(float x1,float y1,float x2,float y2, int color) {
	//1,1 is upper left and 2,2 is bottom right
	glPushMatrix(); {
		if (color == 1) glColor3f(1.0,0.0,0.0);
		else if (color == 2) glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(	x1-4.0, y1-4.0);
			glVertex2f(	x1-4.0, y1);
			glVertex2f(	x2,	y1-4.0);
			glVertex2f( x2, y1);
			glVertex2f( x2+4.0, y1-4.0);
			glVertex2f( x2, y2);
			glVertex2f( x2+4.0, y2+4.0);
			glVertex2f( x1, y2);
			glVertex2f( x1-4.0, y2+4.0);
			glVertex2f( x1, y1);
			glVertex2f( x1-4.0, y1);
		}; glEnd();
	}; glPopMatrix();
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
	
	glPushMatrix(); {
		glBegin(GL_QUAD_STRIP); {
			glColor3f(0.0,0.0,0.0);
			glVertex2f(192.0,320.0-16.0);
			glVertex2f(192.0,320.0+16.0);
			glColor3f(1.0,1.0,1.0);
			glVertex2f(352.0,320.0-16.0);
			glVertex2f(352.0,320.0+16.0);
		}; glEnd();
	}; glPopMatrix();
	outline(192.0,320.0-16.0,352.0,320.0+16.0,2);
	
	glPushMatrix(); {
		glBegin(GL_QUAD_STRIP); {
			glColor3f(0.0,0.0,0.0);
			glVertex2f(192.0,320.0+48.0);
			glVertex2f(192.0,320.0+80.0);
			glColor3f(1.0,1.0,1.0);
			glVertex2f(352.0,320.0+48.0);
			glVertex2f(352.0,320.0+80.0);
		}; glEnd();
	}; glPopMatrix();
	outline(192.0,320.0+48.0,352.0,320.0+80.0,2);
}

void LightButtons() {
	glPushMatrix(); {
		if (!lightsOn[0]) glColor3f(0.5,0.5,0.5);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 32.0);
			glVertex2f(480.0, 32.0);
			glVertex2f(416.0, 96.0);
			glVertex2f(480.0, 96.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 0) outline(416.0,32.0,480.0,96.0,1);
	
	glPushMatrix(); {
		if (!lightsOn[1]) glColor3f(0.5,0.5,0.5);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 128.0);
			glVertex2f(480.0, 128.0);
			glVertex2f(416.0, 192.0);
			glVertex2f(480.0, 192.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 1) outline (416.0,128.0,480.0,192.0,1);
	
	glPushMatrix(); {
		if (!lightsOn[2]) glColor3f(0.5,0.5,0.5);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 224.0);
			glVertex2f(480.0, 224.0);
			glVertex2f(416.0, 288.0);
			glVertex2f(480.0, 288.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 2) outline (416.0,224.0,480.0,288.0,1);
	
	glPushMatrix(); {
		if (!lightsOn[3]) glColor3f(0.5,0.5,0.5);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 320.0);
			glVertex2f(480.0, 320.0);
			glVertex2f(416.0, 384.0);
			glVertex2f(480.0, 384.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 3) outline (416.0,320.0,480.0,384.0,1);
	
	glPushMatrix(); {
		if (!lightsOn[4]) glColor3f(0.5,0.5,0.5);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 416.0);
			glVertex2f(480.0, 416.0);
			glVertex2f(416.0, 480.0);
			glVertex2f(480.0, 480.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 4) outline (416.0,416.0,480.0,480.0,1);
	
}

void toggleButtons() { 
	//object movement
	glPushMatrix(); {
		glColor3f(0.0,0.0,1.0); 
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f( 192.0,  32.0);
			glVertex2f( 256.0,  32.0);
			glVertex2f( 192.0,  96.0);
			glVertex2f( 256.0,  96.0);
		}; glEnd();		
	}; glPopMatrix();
	if (moveToggle) {glColor3f(1.0,1.0,0.0); outline(192.0,32.0,256.0,96.0,1);}
	
	//light movement
	glPushMatrix(); {
		glColor3f(0.0,0.0,1.0); 
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f( 288.0,  32.0);
			glVertex2f( 352.0,  32.0);
			glVertex2f( 288.0,  96.0);
			glVertex2f( 352.0,  96.0);
		}; glEnd();		
	}; glPopMatrix();
	if (!moveToggle) {glColor3f(1.0,1.0,0.0); outline(288.0,32.0,352.0,96.0,1);}
	
	//toggle light
	glPushMatrix(); {
		glColor3f(0.0,0.0,1.0); 
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f( 288.0,  176.0);
			glVertex2f( 352.0,  176.0);
			glVertex2f( 288.0,  240.0);
			glVertex2f( 352.0,  240.0);
		}; glEnd();		
	}; glPopMatrix();
	
	//toggle grid
	glPushMatrix(); {
		if (gridOn) glColor3f(0.0,0.0,1.0);
		else glColor3f(0.5,0.5,0.5);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f( 192.0,  176.0);
			glVertex2f( 256.0,  176.0);
			glVertex2f( 192.0,  240.0);
			glVertex2f( 256.0,  240.0);
		}; glEnd();
	}; glPopMatrix();


}

void drawMenu() {
	glPushMatrix(); {
		glColor3f(0.0,0.0,1.0);
		//translate button
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0,  32.0);
			glVertex2f( 128.0,  32.0);
			glVertex2f(  32.0,  96.0);
			glVertex2f( 128.0,  96.0);
		}; glEnd();
		if (transform == 0) { outline(32.0,32.0,128.0,96.0,1); }
		
		//scale button
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0, 128.0+48.0);
			glVertex2f( 128.0, 128.0+48.0);
			glVertex2f(  32.0, 192.0+48.0);
			glVertex2f( 128.0, 192.0+48.0);
		}; glEnd();
		if (transform == 1) { outline(32.0,128.0+48.0,128.0,192.0+48.0,1); }
		
		//rotate button
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0, 224.0+96.0);
			glVertex2f( 128.0, 224.0+96.0);
			glVertex2f(  32.0, 288.0+96.0);
			glVertex2f( 128.0, 288.0+96.0);
		}; glEnd();
		if (transform == 2) { outline(32.0,224.0+96.0,128.0,288.0+96.0,1); }
	}; glPopMatrix();
	
	LightButtons();
	toggleButtons();
	drawColors();
	

}

void menuMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		mouse1 = state;
	}
	
	mMouseX = x;
	mMouseY = y;
	if (state == GLUT_DOWN) {
		//Transform button selection
		if (mMouseX >=32 && mMouseX <=128) {
			if (mMouseY >= 32 && mMouseY <= 96) { transform = 0; }
			else if (mMouseY >= 128+48 && mMouseY <= 192+48) { transform = 1; }
			else if (mMouseY >= 224+96 && mMouseY <= 288+96) { transform = 2; }
		}
	
		//toggles
		if (mMouseX >= 192 && mMouseX <= 256) {
			if (mMouseY >= 32 && mMouseY <= 96) {moveToggle = true;}
			if (mMouseY >= 176 && mMouseY <=240) {gridOn = !gridOn;}
		}
		
		if (mMouseX >= 288 && mMouseX <=352) {
			if (mMouseY >= 32 && mMouseY <= 96) {moveToggle = false;}
			if (mMouseY >= 176 && mMouseY <= 240) {lightsOn[lightNum] = !lightsOn[lightNum];}
		}
	
		//light button selection
		if (mMouseX > 416 && mMouseX <=480) {
			if (mMouseY >= 32 && mMouseY <= 96) { lightNum = 0; }
			else if (mMouseY >= 128 && mMouseY <= 192) { lightNum = 1; }
			else if (mMouseY >= 224 && mMouseY <= 288) { lightNum = 2; }
			else if (mMouseY >= 320 && mMouseY <= 384) { lightNum = 3; }
			else if (mMouseY >= 416 && mMouseY <= 480) { lightNum = 4; }
		}
	
		//Color selection
		if (mMouseY <= 512-32 && mMouseY >= 512-64) {
			if (mMouseX >= 32 && mMouseX <= 360) {
				float r,g,b;
				HSVtoRGB(&r,&g,&b,mMouseX-32.0,1.0,1.0);
				std::cout << r << " " << g << " " << b << std::endl;
				objList[currentObj]->changeColor(r,g,b);
			}
		}
	}
	glutPostRedisplay();
	//std::cout << transform << std::endl;
}















