 
#include "ObjetoCompuesto.h"

ObjetoCompuesto:: ObjetoCompuesto() {
	hijos = new Objeto3D*[100000];
	numHijos = 0;
	
	m1 = new GLfloat[16];
}

ObjetoCompuesto:: ~ObjetoCompuesto() {
	for(int i =0; i < numHijos; i++) {     
		delete hijos[i];
    }  
}

void ObjetoCompuesto:: dibuja() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(dameMatrizAfin());
	// Copiar en m1 la matriz actual de modelado-vista
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	for(int i =0; i < numHijos; i++) {
		glColor4f(hijos[i]->getR(), hijos[i]->getG(), hijos[i]->getB(), hijos[i]->getA());
		glMultMatrixf(hijos[i]->dameMatrizAfin());
		hijos[i]->dibuja();
		glLoadMatrixf(m1);
    }
	glPopMatrix();
}

void ObjetoCompuesto:: introduceObjeto(Objeto3D* objeto) {
	hijos[numHijos++] = objeto;
}




