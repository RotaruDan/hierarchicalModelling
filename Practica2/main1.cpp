//---------------------------------------------------------------------------
// Dan Cristia, Rotaru
//---------------------------------------------------------------------------
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ObjetoCompuesto.h"
#include "Ejes.h"
#include "Cubo.h"
#include "Vara.h"
using namespace std;
//---------------------------------------------------------------------------

// Viewport
struct viewPort{GLsizei w; GLsizei h;} Vp = {700, 700};

// Camera parameters, those values are overriden on initScene() method.
struct viewCamera{GLdouble eyeX, eyeY, eyeZ;
        GLdouble lookX, lookY, lookZ;
        GLdouble upX, upY, upZ;} 
			initial = {350, 350, 350, 0, 0, 0, 0, 1, 0}, 
			front = {0, 0, 550, 0,0,0, 0,1,0},
			topView = {0, 450, 0, 0,0,0, 1,0,1}, 
			lateral = {550, 0, 0, 0,0,0, 0,1,0};

// Viewing frustum parameters
struct viewVolume{GLdouble xRight, xLeft;
        GLdouble yTop, yBot;
        GLdouble zNear, zFar;} Pj = {350, -350, 350,-350, 1, 1000};

GLdouble scale = 1;
viewCamera * currentView = &initial;
GLdouble xAngle, yAngle, zAngle;

// Scene
ObjetoCompuesto * root;

// prototipos
void updateProjection();
void updateCamera();
void initScene();
void initGL();
void resize(int wW, int wH);
void display();
void keyPres(unsigned char key, int mX, int mY);
//---------------------------------------------------------------------------

// programa principal
int main(int argc, char* argv[]){ 
	// Initialization 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Doble buffer, rgba y profundidad.
	glutInitWindowSize(Vp.w, Vp.h); 
	glutInitWindowPosition(100,100);
	glutInit(&argc,argv);
	// Window construction
	int win=glutCreateWindow("Práctica 2 Opcional - Modelado jerárquico");
	// Callback registration
  
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPres);
	// OpenGL basic setting
	initGL();

	ObjetoCompuesto raiz;
	root = &raiz;

	// iniciar la escena desde la raiz
	Ejes ejes(425);
	raiz.introduceObjeto(&ejes);

	GLdouble ladoCubo = 160;
	GLdouble mitadLadocubo = ladoCubo * 0.5;
	Cubo cubo(ladoCubo);
	raiz.introduceObjeto(&cubo);
	
	char * archivo = "staff.outline";

	Vara vara(archivo);
	vara.setColor(0, 0, 1, 1);
	vara.traslada(new PuntoVector3D(0, mitadLadocubo, 0, 1));
	raiz.introduceObjeto(&vara);
	
	Vara vara2(archivo);
	vara2.setColor(0, 0, 1, 1);
	vara2.traslada(new PuntoVector3D(0, -mitadLadocubo, 0, 1));
	vara2.rota(180, 1, 0, 0);
	raiz.introduceObjeto(&vara2);

	Vara vara3(archivo);
	vara3.setColor(0, 0, 1, 1);
	vara3.traslada(new PuntoVector3D(-mitadLadocubo, 0, 0, 1));
	vara3.rota(90, 0, 0, 1);
	raiz.introduceObjeto(&vara3);

	Vara vara4(archivo);
	vara4.setColor(0, 0, 1, 1);
	vara4.traslada(new PuntoVector3D(mitadLadocubo, 0, 0, 1));
	vara4.rota(-90, 0, 0, 1);
	raiz.introduceObjeto(&vara4);

	Vara vara5(archivo);
	vara5.setColor(0, 0, 1, 1);
	vara5.traslada(new PuntoVector3D(0, 0, mitadLadocubo, 1));
	vara5.rota(90, 1, 0, 0);
	raiz.introduceObjeto(&vara5);

	Vara vara6(archivo);
	vara6.setColor(0, 0, 1, 1);
	vara6.traslada(new PuntoVector3D(0, 0, -mitadLadocubo, 1));
	vara6.rota(-90, 1, 0, 0);
	raiz.introduceObjeto(&vara6);

	initScene();
	// Classic glut's main loop can be stopped after X-closing the window, using freeglut's setting
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
	glutMainLoop();  //while (continue_in_main_loop) glutMainLoopEvent();
	// Window destruction (never reach this point using classic glut)
	glutDestroyWindow(win);
	// liberar la escena
	return 0;
}
//---------------------------------------------------------------------------

void initGL(){

	// Activar características de OpenGL
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);		// z buffer enable
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);   
	glEnable(GL_TEXTURE_2D); 

	GLfloat mat_diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat mat_ambient[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat mat_shininess[] = {100.0f};

	GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat light_position[] = {150, 150, 150, 1.0f};
	
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	// set material property
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Camera set up
	updateCamera();
	// Frustum set up
	updateProjection();
}

void initScene(){


	updateCamera();
	updateProjection();
}

void updateCamera(){
	glMatrixMode(GL_MODELVIEW);   // VIEW
	glLoadIdentity();
	gluLookAt((*currentView).eyeX, (*currentView).eyeY, (*currentView).eyeZ,
		(*currentView).lookX,	(*currentView).lookY,	(*currentView).lookZ, 
		(*currentView).upX, (*currentView).upY, (*currentView).upZ);

}
//---------------------------------------------------------------------------

void resize(int wW, int wH){
	// Viewport set up     
	Vp.w = wW; Vp.h = wH; 

	// Frustum set up
	updateProjection();

	glutPostRedisplay();
}

void updateProjection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Pj.xRight = Vp.w/ 2.0 / scale; Pj.xLeft = -Pj.xRight; 
	Pj.yTop = Vp.h/2.0 / scale;  Pj.yBot = -Pj.yTop; 
	glOrtho(Pj.xLeft,Pj.xRight, Pj.yBot,Pj.yTop, Pj.zNear, Pj.zFar);
	//	glFrustum(Pj.xLeft,Pj.xRight, Pj.yBot,Pj.yTop, Pj.zNear*300, Pj.zFar);
}
//---------------------------------------------------------------------------

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	updateCamera();
	glViewport(0,0, Vp.w, Vp.h); 

	glRotated(xAngle, 1, 0, 0);
	glRotated(yAngle, 0, 1, 0);
	glRotated(zAngle, 0, 0, 1);

	root->dibuja();

	glutSwapBuffers(); // Hay dos buffers que se van intercambiando para ir pinando en ellos
}
//---------------------------------------------------------------------------

void keyPres(unsigned char key, int mX, int mY){
	bool need_redisplay = true;
	if(key == 27) {  /* Escape key */  
		glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop 
	} else if(key == 'i') { 
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
	} else if(key == 'x') { 
		xAngle++;
		yAngle = 0;
		zAngle = 0;
	} else if(key == 'y') { 
		xAngle = 0;
		yAngle++;
		zAngle = 0;
	} else if(key == 'z') { 
		xAngle = 0;
		yAngle = 0;
		zAngle++;
	} else {
		need_redisplay = false;
	}

	if (need_redisplay) { 
		glutPostRedisplay(); // Esto vuelve a invocar a "display"
	}
}
//---------------------------------------------------------------------------
