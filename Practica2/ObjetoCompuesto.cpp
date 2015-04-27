 
#include "ObjetoCompuesto.h"

ObjetoCompuesto:: ObjetoCompuesto() {
	hijos = new Objeto3D*[100000];
	numHijos = 0;
}

ObjetoCompuesto:: ~ObjetoCompuesto() {
	for(int i =0; i < numHijos; i++) {     
		delete hijos[i];
    }  
}

void ObjetoCompuesto:: dibuja() {
	for(int i =0; i < numHijos; i++) {     
		hijos[i]->dibuja();
    }
}

void ObjetoCompuesto:: introduceObjeto(Objeto3D* objeto) {
	hijos[numHijos++] = objeto;
}




