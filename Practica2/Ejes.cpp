 
#include "Ejes.h"

Ejes:: Ejes(GLdouble tam) {
	tamanho = tam;
}

Ejes:: ~Ejes() {

}

void Ejes:: dibuja() {
	glBegin( GL_LINES );
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);      // origin
	glVertex3f(tamanho, 0, 0);	  // x   
 
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);      // center
	glVertex3f(0, tamanho, 0);	  // y
		
	glColor3f(1, 0, 0); 
	glVertex3f(0, 0, 0);      // origin
	glVertex3f(0, 0, tamanho);	  // z  
	glEnd();
}




