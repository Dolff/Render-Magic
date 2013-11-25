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
#include <Object.cpp>

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

void render() {

}

//default timer
void myTimer(int value) {
    glutPostRedisplay();

    glutTimerFunc((unsigned int)(1000.0 / 60.0), myTimer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Render Magic");

    cameraRadius = 12.0f;
    cameraTheta = 2.80;
    cameraPhi = 2.0;

    objX = objY = objZ = 0.0f;

    glutTimerFunc((unsigned int)(1000.0 / 60.0), myTimer, 0);

    glutMainLoop();
return 0;
}
