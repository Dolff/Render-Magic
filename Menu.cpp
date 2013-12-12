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

void write1(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,20+y);
		}; glEnd();
	} glPopMatrix();
}

void write2(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			glVertex2f(9+x,0+y);
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(1+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(9+x,20+y);
		}; glEnd();
	} glPopMatrix();
}

void write3(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			glVertex2f(9+x,0+y);
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,10+y);
			glVertex2f(2+x,10+y);
			glVertex2f(9+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,20+y);
		}; glEnd();
	} glPopMatrix();
}

void write4(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			glVertex2f(7+x,0+y);
			glVertex2f(1+x,9+y);
			glVertex2f(1+x,9+y);
			glVertex2f(9+x,9+y);
			glVertex2f(7+x,0+y);
			glVertex2f(7+x,20+y);
		}; glEnd();
	} glPopMatrix();
}

void write5(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,20+y);
			glVertex2f(9+x,20+y);
			glVertex2f(1+x,20+y);
		}; glEnd();
	} glPopMatrix();
}

void writeGrid(float x, float y) {
	glPushMatrix();{
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			//G
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(9+x,20+y);
			glVertex2f(9+x,20+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(5+x,10+y);
			//R
			glVertex2f(11+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,10+y);
			glVertex2f(19+x,10+y);
			glVertex2f(11+x,10+y);
			glVertex2f(11+x,10+y);
			glVertex2f(19+x,20+y);
			glVertex2f(11+x,0+y);
			glVertex2f(11+x,20+y);
			//I
			glVertex2f(25+x,0+y);
			glVertex2f(25+x,20+y);
			//D
			glVertex2f(31+x,0+y);
			glVertex2f(39+x,5+y);
			glVertex2f(39+x,5+y);
			glVertex2f(39+x,15+y);
			glVertex2f(39+x,15+y);
			glVertex2f(31+x,20+y);
			glVertex2f(31+x,20+y);
			glVertex2f(31+x,0+y);
		}; glEnd();
	} glPopMatrix();
}

void writeObj(float x, float y) {
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES); {
			//O
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,20+y);
			glVertex2f(9+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(1+x,0+y);
			//B
			glVertex2f(11+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,20+y);
			glVertex2f(19+x,20+y);
			glVertex2f(11+x,20+y);
			glVertex2f(11+x,20+y);
			glVertex2f(11+x,0+y);
			glVertex2f(11+x,10+y);
			glVertex2f(19+x,10+y);
			//J
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(25+x,0+y);
			glVertex2f(25+x,20+y);
			glVertex2f(25+x,20+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,16+y);
		}; glEnd();
	}; glPopMatrix();
}

void writeLight(float x, float y){
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES);{
			//L
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,20+y);
			glVertex2f(1+x,20+y);
			glVertex2f(9+x,20+y);
			//I
			glVertex2f(15+x,0+y);
			glVertex2f(15+x,20+y);
			//G
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(21+x,0+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,20+y);
			glVertex2f(29+x,20+y);
			glVertex2f(29+x,20+y);
			glVertex2f(29+x,10+y);
			glVertex2f(29+x,10+y);
			glVertex2f(25+x,10+y);
			//H
			glVertex2f(31+x,0+y);
			glVertex2f(31+x,20+y);
			glVertex2f(39+x,0+y);
			glVertex2f(39+x,20+y);
			glVertex2f(31+x,10+y);
			glVertex2f(39+x,10+y);
			//T
			glVertex2f(41+x,0+y);
			glVertex2f(49+x,0+y);
			glVertex2f(45+x,0+y);
			glVertex2f(45+x,20+y);
		}; glEnd();
	}; glPopMatrix();
}

void writeTrans(float x, float y) {
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES); {
			//T
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(5+x,0+y);
			glVertex2f(5+x,20+y);
			//R
			glVertex2f(11+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,10+y);
			glVertex2f(19+x,10+y);
			glVertex2f(11+x,10+y);
			glVertex2f(11+x,10+y);
			glVertex2f(19+x,20+y);
			glVertex2f(11+x,0+y);
			glVertex2f(11+x,20+y);
			//A
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,20+y);
			glVertex2f(21+x,0+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,10+y);
			glVertex2f(29+x,10+y);
			//N
			glVertex2f(31+x,0+y);
			glVertex2f(31+x,20+y);
			glVertex2f(39+x,0+y);
			glVertex2f(39+x,20+y);
			glVertex2f(31+x,0+y);
			glVertex2f(39+x,20+y);
			//S
			glVertex2f(41+x,0+y);
			glVertex2f(49+x,0+y);
			glVertex2f(41+x,0+y);
			glVertex2f(41+x,10+y);
			glVertex2f(41+x,10+y);
			glVertex2f(49+x,10+y);
			glVertex2f(49+x,10+y);
			glVertex2f(49+x,20+y);
			glVertex2f(49+x,20+y);
			glVertex2f(41+x,20+y);
		}; glEnd();
	}; glPopMatrix();
}

void writeScale(float x, float y) {
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES); {
			//S
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,20+y);
			glVertex2f(9+x,20+y);
			glVertex2f(1+x,20+y);
			//C
			glVertex2f(11+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(11+x,0+y);
			glVertex2f(11+x,20+y);
			glVertex2f(11+x,20+y);
			glVertex2f(19+x,20+y);
			//A
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,20+y);
			glVertex2f(21+x,0+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,10+y);
			glVertex2f(29+x,10+y);
			//L
			glVertex2f(31+x,0+y);
			glVertex2f(31+x,20+y);
			glVertex2f(31+x,20+y);
			glVertex2f(39+x,20+y);
			//E
			glVertex2f(41+x,0+y);
			glVertex2f(49+x,0+y);
			glVertex2f(41+x,10+y);
			glVertex2f(47+x,10+y);
			glVertex2f(41+x,20+y);
			glVertex2f(49+x,20+y);
			glVertex2f(41+x,0+y);
			glVertex2f(41+x,20+y);
		}; glEnd();
	}; glPopMatrix();
}

void writeIO(float x, float y){
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES); {
			//I
			glVertex2f(5+x,0+y);
			glVertex2f(5+x,20+y);
			///
			glVertex2f(11+x,20+y);
			glVertex2f(19+x,0+y);
			//O
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(29+x,20+y);
			glVertex2f(29+x,20+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,20+y);
			glVertex2f(21+x,0+y);
		}; glEnd();
	}; glPopMatrix();
}

void writeRotate(float x, float y) {
	glPushMatrix(); {
		glColor3f(0,1,0);
		glBegin(GL_LINES); {
			//R
			glVertex2f(1+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,0+y);
			glVertex2f(9+x,10+y);
			glVertex2f(9+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(1+x,10+y);
			glVertex2f(9+x,20+y);
			glVertex2f(1+x,0+y);
			glVertex2f(1+x,20+y);
			//O
			glVertex2f(11+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,0+y);
			glVertex2f(19+x,20+y);
			glVertex2f(19+x,20+y);
			glVertex2f(11+x,20+y);
			glVertex2f(11+x,20+y);
			glVertex2f(11+x,0+y);
			//T
			glVertex2f(21+x,0+y);
			glVertex2f(29+x,0+y);
			glVertex2f(25+x,0+y);
			glVertex2f(25+x,20+y);
			//A
			glVertex2f(31+x,0+y);
			glVertex2f(39+x,0+y);
			glVertex2f(39+x,0+y);
			glVertex2f(39+x,20+y);
			glVertex2f(31+x,0+y);
			glVertex2f(31+x,20+y);
			glVertex2f(31+x,10+y);
			glVertex2f(39+x,10+y);
			//T
			glVertex2f(41+x,0+y);
			glVertex2f(49+x,0+y);
			glVertex2f(45+x,0+y);
			glVertex2f(45+x,20+y);
			//E
			glVertex2f(51+x,0+y);
			glVertex2f(59+x,0+y);
			glVertex2f(51+x,10+y);
			glVertex2f(57+x,10+y);
			glVertex2f(51+x,20+y);
			glVertex2f(59+x,20+y);
			glVertex2f(51+x,0+y);
			glVertex2f(51+x,20+y);
		}; glEnd();
	}; glPopMatrix();
}

void LightButtons() {
	glPushMatrix(); {
		if (!lightsOn[0]) glColor3f(0.8,0.8,0.8);
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
		if (!lightsOn[1]) glColor3f(0.8,0.8,0.8);
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
		if (!lightsOn[2]) glColor3f(0.8,0.8,0.8);
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
		if (!lightsOn[3]) glColor3f(0.8,0.8,0.8);
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
		if (!lightsOn[4]) glColor3f(0.8,0.8,0.8);
		else glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(416.0, 416.0);
			glVertex2f(480.0, 416.0);
			glVertex2f(416.0, 480.0);
			glVertex2f(480.0, 480.0);
		}; glEnd();
	}; glPopMatrix();
	if (lightNum == 4) outline (416.0,416.0,480.0,480.0,1);

	//write "Light"s
writeLight(423,40);
write1(443,65);
writeLight(423,136);
write2(443,161);
writeLight(423,232);
write3(443,257);
writeLight(423,328);
write4(443,353);
writeLight(423,424);
write5(443,449);
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
writeObj(210,40);

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
writeLight(295,40);	

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
writeLight(295,184);
writeIO(305,209);

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
writeGrid(204,184);
writeIO(209, 209);
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
writeTrans(54,40);

		//scale button
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex2f(  32.0, 128.0+48.0);
			glVertex2f( 128.0, 128.0+48.0);
			glVertex2f(  32.0, 192.0+48.0);
			glVertex2f( 128.0, 192.0+48.0);
		}; glEnd();
		if (transform == 1) { outline(32.0,128.0+48.0,128.0,192.0+48.0,1); }
writeScale(54,184);		

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
writeRotate(49,328);

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
		
		
		if (mMouseX >= 192 && mMouseX <=352) {
			//change color on grayscale
			if (mMouseY >= 320+48  && mMouseY <= 320+80) {
				float r,g,b;
				r = g = b = ((mMouseX-192.0)/(352.0-192.0));
				//std::cout << r << " " << g << " " << b << std::endl;
				objList[currentObj]->changeColor(r,g,b);
			}
			
			//change opacity
			if (mMouseY >= 320-16 && mMouseY <= 320+16) {
				objList[currentObj]->changeAlpha((mMouseX-192.0)/(352.0-192.0));
			}
		}
		
		//change opacity
		
	
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
				//std::cout << r << " " << g << " " << b << std::endl;
				objList[currentObj]->changeColor(r,g,b);
			}
		}
	}
	glutPostRedisplay();
	//std::cout << transform << std::endl;
}















