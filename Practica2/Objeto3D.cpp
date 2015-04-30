
#include "Objeto3D.h"

Objeto3D:: Objeto3D() { 	 
    matriz = new TAfin();
	setColor(1, 1, 1, 1);
}

 
Objeto3D:: ~Objeto3D() {
    delete matriz;
}

GLfloat* Objeto3D:: dameMatrizAfin() {
	return matriz->dameMatrizModelado();
}

void Objeto3D:: traslada(PuntoVector3D* punto) {
	matriz->traslada(punto->getX(), punto->getY(), punto->getZ());
}

void Objeto3D:: escala(GLfloat fX,GLfloat fY,GLfloat fZ) {
	matriz->escala(fX, fY, fZ);
}

void Objeto3D:: rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ) {
	matriz->rota(alfa, fX, fY, fZ);
}

void Objeto3D::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	Objeto3D::r = r;
	Objeto3D::g = g;
	Objeto3D::b = b;
	Objeto3D::a = a;
}

GLfloat Objeto3D::getR(){
	return r;
}

GLfloat Objeto3D::getG(){
	return g;
}

GLfloat Objeto3D::getB(){
	return b;
}

GLfloat Objeto3D::getA(){
	return a;
}


