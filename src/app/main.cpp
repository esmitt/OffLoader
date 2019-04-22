#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include "OffObject.h"

const float ANGLE = 45.f;
const float FOV = 70.f;
const float NCP = 0.05f;
const float FCP = 50.f;

OffObject off;
DISPLAY_TYPE mode = DISPLAY_TYPE::WIRE;
GLfloat anglex = 0.0, angley = 0.0, anglez = 0.0, scale = 0.5;

void reshape(int width, int height) {
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    float ratio = (height == 0)?1:(GLfloat) width/(GLfloat) height;
    gluPerspective(FOV, ratio, NCP, FCP);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyDown (unsigned char key, int x, int y) {
    switch (key) {
        case '+': scale += 0.01f; break;
        case '-': scale -= 0.01f; scale = std::max(0.01f, scale); break;
        case 'M':
        case 'm':
            switch (mode) {
                case DISPLAY_TYPE::POINTS:
                    mode = DISPLAY_TYPE::WIRE;
                    break;
                case DISPLAY_TYPE::WIRE:
                    mode = DISPLAY_TYPE::POLYGONS;
                    break;
                case DISPLAY_TYPE::POLYGONS:
                    mode = DISPLAY_TYPE::POINTS;
                    break;
            }
            break;
    }
    glutPostRedisplay();
}

void keyDownSpecial (int key, int x, int y) {
   if(key == GLUT_KEY_DOWN)
       anglex += 5;
   if(key == GLUT_KEY_UP)
       anglex -= 5;
   if(key == GLUT_KEY_LEFT)
       angley -= 5;
   if(key == GLUT_KEY_RIGHT)
       angley += 5;
    if(key == GLUT_KEY_PAGE_DOWN)
        anglez -= 5;
    if(key == GLUT_KEY_PAGE_UP)
        anglez += 5;
    glutPostRedisplay();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // put the object in front of the camera
    glTranslatef(0,  0,  -1.0);

    // apply the scaling required
    glScalef(scale, scale, scale);

    // apply the rotations required
    glRotatef(anglex,  1.0,  0.0,  0.0);
    glRotatef(angley,  0.0,  1.0,  0.0);
    glRotatef(anglez,  0.0,  0.0,  1.0);

    // max length of the object = 1
    auto magnitude = 1.0f / off.getMagnitude();
    glScalef(magnitude, magnitude, magnitude);

    // put the center of the object in origin
    auto centroid = off.getCentroid();
    glTranslatef(-centroid.x, -centroid.y, -centroid.z);

    // draw the actual object
    off.draw(mode);

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {

    if(!off.loadFile(argv[1])) {
        std::cerr << "Error loading file" << std::endl;
        return -1;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OffLoader");
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyDown);
    glutSpecialFunc(keyDownSpecial);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
