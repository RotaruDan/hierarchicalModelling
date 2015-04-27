
#include "TAfin.h"
#include <math.h>

TAfin:: TAfin() {
	m = new GLfloat[16];
    //To do: hacer que m sea la identidad
}

TAfin:: ~TAfin() {
	delete[] m;
}

GLfloat* TAfin::dameMatrizModelado() {
	return m;
}

void TAfin:: traslada(GLfloat X, GLfloat Y, GLfloat Z) {   
	//To do 
}

void TAfin:: escala(GLfloat fX, GLfloat fY, GLfloat fZ) {
	//To do 
}

void TAfin:: rota(GLfloat alfa, GLfloat fX, GLfloat fY, GLfloat fZ) {
	 //To do
}

void TAfin:: postMultiplica(GLfloat* mm) {
	 //To do
}


