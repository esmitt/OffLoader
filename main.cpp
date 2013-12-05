#include "OffObject.h"
#include "GL/freeglut.h"
#include <iostream>
#pragma comment(lib, "freeglut.lib")
#define WINDOW_TITLE "Template"
using namespace std;

const float ANGLE = 45.f;
const float FOV = 90.f;
const float NCP = 0.001f;
const float FCP = 40.f;
int m_iWidth = 800;		//width of the viewport
int m_iHeight = 600;	//height of the viewport
COffObject* off_object;
float angle;	//only for rotation
float spin;		//only for rotation
///
/// Function designed to FreeGLU to use the glutKeyboardFunc
/// @param key represents the key pressed in the keyboard
/// 
void keyboardDown(unsigned char key, int x, int y) 
{
 
  switch(key) {
  case 'Q':
  case 'q':
  case  27:   // ESC
	  terminate();
  }
}

void idle(void)
{
	glutPostRedisplay();
}

void destroy()
{
	if(off_object) off_object = NULL;
}

void draw() {
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6,0.6,0.6,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  // begin render the scene
	glm::vec3 v1, v2, v3;
	glTranslatef(0, 0, -1);
	glRotatef(angle+=spin, 0, 1, 0); if (++angle > 360) angle -= 360;
	glScalef(off_object->m_fScale, off_object->m_fScale, off_object->m_fScale);
	glTranslatef(-off_object->m_vecCenter.x, -off_object->m_vecCenter.y, -off_object->m_vecCenter.z);
	for(int k = 0; k < off_object->m_nTriangles; k++)
	{
		v1 = off_object->m_pVecPoints[off_object->m_pVecTriangles[k][VERTEX1]];
		v2 = off_object->m_pVecPoints[off_object->m_pVecTriangles[k][VERTEX2]];
		v3 = off_object->m_pVecPoints[off_object->m_pVecTriangles[k][VERTEX3]];
		glBegin(GL_TRIANGLES);
			glColor3f(v1.x, v1.y, v1.z);
			glVertex3f(v1.x, v1.y, v1.z);
			glColor3f(v2.x, v2.y, v2.z);
			glVertex3f(v2.x, v2.y, v2.z);
			glColor3f(v3.x, v3.y, v3.z);
			glVertex3f(v3.x, v3.y, v3.z);
		glEnd();
	}
  // end render the scene
  
 // //begin - rendering a simple triangle (testing)
	//glBegin(GL_TRIANGLES);
	//	glColor3f(1,0,0);
	//	glVertex3f(-0.5,0,-1);
	//	glColor3f(0.5,0.5,0);
	//	glVertex3f(0.5,0,-1);
	//	glColor3f(0,0.5,0.5);
	//	glVertex3f(0,0.5,-1);
	//glEnd();
 // //begin - rendering a simple triangle
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height) 
{
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);
 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
	float ratio = (height == 0)?1:(GLfloat) width/(GLfloat) height;
  gluPerspective(FOV, ratio, NCP, FCP);
 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

bool initialize()
{
	off_object = new COffObject();
	if(!off_object->loadFile("algo.off"))
	{
		std::cout << "error in loadFile inside initialize function." << std::endl;
		terminate();
		return false;
	}
	angle = 0; spin = 3;	//5 degrees
	glEnable(GL_DEPTH_TEST);
	return true;
}

void terminate()
{
	std::cout << "terminate function." << std::endl;
	destroy();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(m_iWidth, m_iHeight);
	glutCreateWindow(WINDOW_TITLE);	
	glutCreateMenu(NULL);
	if(!initialize()) return 1;
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	//GUI construction
	glutCloseFunc(terminate) ;
	glutMainLoop();
	return 0;
}