//---------------------------------------------------------------------------
// Dan Cristia, Rotaru
//---------------------------------------------------------------------------
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include "Group.h"
#include "Axis.h"
#include "Malla.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

// Scene
Group root;

// prototipos
void updateProjection();
void updateCamera();
void initScene();
void split(const string& s, string c, vector<string>& v);
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
	int win=glutCreateWindow("Práctica 2 - Malla por revolución");
	// Callback registration
  
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPres);
	// OpenGL basic setting
	initGL();

	// Axis for debugging
	Axis axis;
	axis.setColor(1, 1, 1, 1);
	root.addChildren(&axis);

	// iniciar la escena desde la raiz

	string STRING;
	ifstream infile;
	infile.open ("staff.outline");
	getline(infile, STRING);
	getline(infile, STRING);
	int vertexNumber = stoi(STRING);
	getline(infile, STRING);	
	getline(infile, STRING);	
	getline(infile, STRING);
	getline(infile, STRING);	
	getline(infile, STRING);		
	
	vector<string> res;
	int i = 0;
	while(!infile.eof()) {
		getline(infile,STRING); // Saves the line in STRING.
		split(STRING, "\t", res);
	}
	infile.close();

	int m = vertexNumber; //número de puntos en el perfil original
	PuntoVector3D** profile = new PuntoVector3D*[m];
	for(int i = 0; i < m; ++i) {
		int idx = 2 * i;
		PuntoVector3D *pv3d = new PuntoVector3D(stof(res[idx]), stof(res[idx + 1]), 0, 1);
		profile[i] = pv3d;
	}
	int n = 100; //número de rotaciones

	//Tamaños de los arrays
	int vertexCount = n * m;
	int facesCount = n*(m-1);
	int normalsCount = facesCount;
	
	//Creación de los arrays
	PuntoVector3D** vertex = new PuntoVector3D*[vertexCount];
	PuntoVector3D** normals = new PuntoVector3D*[normalsCount];
	Cara** faces = new Cara*[facesCount];
	
	//Colocar el perfil original en la tabla de vertices
	for(int j = 0; j < m; ++j) {
		vertex[j] = profile[j]->clonar();
	}
	
	//Vertices de la malla
	for(int i = 1; i < n; ++i) {
		double theta = i * 360 / (double) n;
		double c = cos(theta);
		double s = sin(theta);

		//R_y es la matriz de rotación sobre el eje Y
		for(int j = 0; j < m; ++j){
			int index = i * m + j;
			//Transformar el punto j‐ésimo del perfil original
			double x = c * profile[j]->getX() + s * profile[j]->getZ();
			double z = -s * profile[j]->getX() + c * profile[j]->getZ();
			PuntoVector3D* p = new PuntoVector3D(x, profile[j]->getY(), z, 1);
			vertex[index] = p;
		}
	}

	
	//Construcción de las caras
	int faceIndex = 0;
	for(int i = 0; i < n; ++i) { //unir el perfil i‐ésimo con el (i+1)%n‐ésimo
		for(int j = 0; j < m; ++j) { //este vértice cierra una cara
			int index = i * m + j;
			int* nv = new int[4];
			nv[0] = index;
			nv[1] = (index + m) % vertexCount;
			nv[2] = (index + 1 + m) % vertexCount;
			nv[3] = index + 1;
			Cara* face = new Cara(4, nv, faceIndex);
			faces[faceIndex] = face;
			++faceIndex;
		}
	}
	
	Malla malla(vertexCount, normalsCount, facesCount, vertex, normals, faces);
	malla.newelliza();
	malla.setColor(0, 0, 1, 1);
	root.addChildren(&malla);
  
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

void split(const string& s, string c,  vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

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
	GLfloat light_position[] = {100, 100, 100, 1.0f};
	
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

	glClearColor(0, 0, 0, 1.0f);

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
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0, Vp.w, Vp.h); 
	root.render();

	glutSwapBuffers(); // Hay dos buffers que se van intercambiando para ir pinando en ellos
}
//---------------------------------------------------------------------------

void keyPres(unsigned char key, int mX, int mY){
	bool need_redisplay = true;
	if(key == 27) {  /* Escape key */  
		glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop 
	} else if(key == 'i') { 
		
	} else if(key == 'x') { 
		
	} else if(key == 'y') { 
		
	} else if(key == 'z') { 
		
	} else {
		need_redisplay = false;
	}

	if (need_redisplay) { 
		glutPostRedisplay(); // Esto vuelve a invocar a "display"
	}
}
//---------------------------------------------------------------------------
