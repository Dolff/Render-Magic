/*	Render-Magic/Object.cpp
 *
 *	object class for render-magic project
 *	defines different geometries and their transformation functions
 *
 *
 */
 
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

enum OBJ_TYPE {
	CUBE,
	SPHERE,
	CYLINDER
};

class Object {
	public:
		Object();
		void render();
		void translate(float,float,float);
		void scale(float,float,float);
		void rotate(float,float,float,float);	
	private:
		float x,y,z;
		float scaleX, scaleY, scaleZ;
		float rotateX, rotateY, rotateZ, rotateAngle;
		float R, G, B;
		OBJ_TYPE thisObj;

};

Object::Object() {
	x = y = z = 0;
	scaleX = scaleY = scaleZ = 1;
	rotateX = rotateY = rotateZ = 0;
	thisObj = CUBE;
	R = G = B = 1;
}

void Object::translate(float dx, float dy, float dz) {
	x+=dx;
	y+=dy;
	z+=dz;
}

void Object::scale(float dx, float dy, float dz) {
	if(scaleX > .1 || dx>0) scaleX+=dx;
	if(scaleY > .1 || dy>0) scaleY+=dy;
	if(scaleZ > .1 || dz>0) scaleZ+=dz;
}

void Object::rotate(float angle, float vX, float vY, float vZ) {
	rotateX = vX;
	rotateY = vY;
	rotateZ = vZ;
	rotateAngle = angle;
}

void Object::render() {
	glPushMatrix(); {
		glColor3f(R,G,B);
		glTranslatef(x,y,z);
		glScalef(scaleX,scaleY,scaleZ);
		glRotatef(rotateAngle, rotateX, rotateY, rotateZ);
		//GLUquadricObj *myQuad = gluNewQuadric();
		switch(thisObj) {
			case CUBE:
				glutSolidCube( 2 );
				break;
		}
	}; glPopMatrix();
};

















