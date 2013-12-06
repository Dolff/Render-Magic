//blank file for initial push
//Cody and Dolff

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
#include "Object.cpp"


using namespace std;

//--Global Variables--
int windowWidth = 512;
int windowHeight = 512;
//status of the mouse buttons
GLint leftMouseButton = GLUT_UP, rightMouseButton = GLUT_UP;
int mouseX = 0;
int mouseY = 0;
//camera
//spherical coords
float camTheta, camPhi, camRadius;
//cartesian coords
float camX, camY, camZ;

unsigned int currentObj = 0;
Object cube;
vector<Object*> objList;
bool selection = false;

#include "Menu.cpp"

//draws a grid in the X-Z plane to help give the user perspective
void drawGrid() {
    glDisable(GL_LIGHTING);

    glColor3f(1,1,1);
    glBegin(GL_LINES); {
        //draw the lines along the Z axis
        for(int i = 0; i < 11; i++) {
            glVertex3f((i-5), 0, -5);
            glVertex3f((i-5), 0, 5);
        }
        //draw the lines along the X axis
        for(int i = 0; i < 11; i++) {
            glVertex3f(-5, 0, (i-5));
            glVertex3f(5, 0, (i-5));
        }
    }; glEnd();

    glEnable(GL_LIGHTING);
}

void findCameraPos(float theta, float phi, float radius,
                            float &x, float &y, float &z) {
    x = radius * sinf(theta)*sinf(phi);
    y = radius * -cosf(phi);
    z = radius * -cosf(theta)*sinf(phi);
}

//basic function to resize the display if the window size is changed
void resizeWindow(int w, int h) {
    float aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}

void render(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    gluLookAt(camX, camY, camZ,     //camera is located at (x,y,z)
            0.0f, 0.0f, 0.0f,                           //camera is looking at (0,0,0)
            0.0f, 1.0f, 0.0f); 

	//objList[0]->render();
	for(unsigned int i=0; i<objList.size(); ++i) {
		objList[i]->render();
	}
	drawGrid();

	glutSwapBuffers();
}

void render2(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMenu();
	glutSwapBuffers();
}

void resize2(int w, int h) {
	glViewport(0,0,512,512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,512,512,0);
}

void initScene()
        {glEnable(GL_DEPTH_TEST);

        //turns the lights on
         float lightCol[4] = { 1, 1, 1, 1};
         float ambientCol[4] = {0.0, 0.0, 0.0, 1.0};
         float lPosition[4] = { 10, 10, 10, 1 };
         glLightfv(GL_LIGHT0,GL_POSITION,lPosition);
         glLightfv(GL_LIGHT0,GL_DIFFUSE,lightCol);
         glLightfv(GL_LIGHT0, GL_AMBIENT, ambientCol);
         glEnable(GL_LIGHTING);
         glEnable(GL_LIGHT0);

         glEnable(GL_COLOR_MATERIAL);
         glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

         glShadeModel(GL_SMOOTH);
        }

//default timer
void myTimer(int value) {
    glutPostRedisplay();
    glutTimerFunc((unsigned int)(1000.0 / 60.0), myTimer, 0);
}

void ArrowKeys(int key, int x, int y) {
	switch(key)
	{
	case GLUT_KEY_RIGHT:
		objList[currentObj]->translate(.1,0,0); break;
	case GLUT_KEY_LEFT:
		objList[currentObj]->translate(-.1,0,0); break;
	case GLUT_KEY_UP:
		objList[currentObj]->translate(0,0,.1); break;
	case GLUT_KEY_DOWN:
		objList[currentObj]->translate(0,0,-.1); break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if((key == 0x1b))
		{exit(0);}
	if(key == '.')
		{objList[currentObj]->translate(0,-1,0);}
	if(key == '/')
		{objList[currentObj]->translate(0,1,0);}
		
	//handle scaling
	if(key == 'w') {
		if (transform == 0) objList[currentObj]->translate(.1,0,0);
		if (transform == 1) objList[currentObj]->scale(.1,0,0);
		if (transform == 2) {objList[currentObj]->rotateAxis = 0; objList[currentObj]->rotate(0.5);}
	}
	if(key == 'q') {
		if (transform == 0) objList[currentObj]->translate(-.1,0,0);
		if (transform == 1) objList[currentObj]->scale(-.1,0,0);
		if (transform == 2) {objList[currentObj]->rotateAxis = 0; objList[currentObj]->rotate(-0.5);}
	}
	if(key == 's') {
		if (transform == 0) objList[currentObj]->translate(0,0,.1);
		if (transform == 1) objList[currentObj]->scale(0,0,.1);
		if (transform == 2) {objList[currentObj]->rotateAxis = 2; objList[currentObj]->rotate(0.5);}
	}
	if(key == 'a') {
		if (transform == 0) objList[currentObj]->translate(0,0,-.1);
		if (transform == 1) objList[currentObj]->scale(0,0,-.1);
		if (transform == 2) {objList[currentObj]->rotateAxis = 2; objList[currentObj]->rotate(-0.5);}
	}
	if(key == 'x') {
		if (transform == 0) objList[currentObj]->translate(0,.1,0);
		if (transform == 1) objList[currentObj]->scale(0,.1,0);
		if (transform == 2) {objList[currentObj]->rotateAxis = 1; objList[currentObj]->rotate(0.5);}
	}
	if(key == 'z') {
		if (transform == 0) objList[currentObj]->translate(0,-.1,0);
		if (transform == 1) objList[currentObj]->scale(0,-.1,0);
		if (transform == 2) {objList[currentObj]->rotateAxis = 1; objList[currentObj]->rotate(-0.5);}
	}
		
	if(key == 'o')
		{selection = !selection;}
		
	if(key == '1') {
		if (selection) currentObj = 0;
		else {
			Object* newObj = new Object;
			objList.push_back(newObj);
			currentObj=objList.size()-1;
		}
	} else if (key == '2') {
		if (selection) currentObj = 1;		
	} else if (key == '3') {
		if (selection) currentObj = 2;	
	} else if (key == '4') {
		if (selection) currentObj = 3;	
	} else if (key == '5') {
		if (selection) currentObj = 4;	
	} else if (key == '6') {
		if (selection) currentObj = 5;
	} else if (key == '7') {
		if (selection) currentObj = 6;	
	} else if (key == '8') {
		if (selection) currentObj = 7;	
	} else if (key == '9') {
		if (selection) currentObj = 8;	
	} else if (key == '0') {
		if (selection) currentObj = 9;	
	}
}

void menuKeyboard(unsigned char key, int x, int y) {
	if(key == 0x1b)
		{exit(0);}
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Render Magic");

	objList.push_back(&cube);

    camRadius = 12.0f;
    camTheta = 2.80;
    camPhi = 2.0;
    
    findCameraPos(camTheta, camPhi, camRadius,
						   camX, camY, camZ);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(ArrowKeys);
    glutDisplayFunc(render);
    glutReshapeFunc(resizeWindow);

    initScene();
    glutTimerFunc((unsigned int)(1000.0 / 60.0), myTimer, 0);

    glutInitWindowSize(512,512);
    glutCreateWindow("Menu");
    glutPositionWindow(80+512,50);
    //initScene();
    glutKeyboardFunc(menuKeyboard);
    glutDisplayFunc(render2);
    glutReshapeFunc(resize2);
    glutMouseFunc(menuMouse);

    glutMainLoop();
return 0;
}
