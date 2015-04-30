 
#include "Cubo.h"

Cubo:: Cubo(GLdouble tam) {
	tamanho = tam;
}

Cubo:: ~Cubo() {

}

void Cubo:: dibuja() {
	glutSolidCube(tamanho);
}




