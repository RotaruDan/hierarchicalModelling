 
#include "Cara.h"
 
Cara::Cara(int nV, int* aiv, int in) {
	numeroVertices=nV;
    arrayIndicesVertices= aiv;
	indiceNormal= in;
}

Cara::~Cara() {
    delete[] arrayIndicesVertices;
}

int Cara::getNumeroVertices() {
    return numeroVertices;
}

int Cara::getIndiceVertice(int k) {
    return arrayIndicesVertices[k];
}


int Cara::getIndiceNormal() {
    return indiceNormal;
}




