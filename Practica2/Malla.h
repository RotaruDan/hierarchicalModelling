 
#ifndef Malla_H_
#define Malla_H_

#include "PuntoVector3D.h"
#include "Cara.h"
#include "Actor.h"

class Malla : public Actor{
	private:
		PuntoVector3D* newell(int i1, int i2, int i3, int i4);
    protected:
        int numeroVertices;
        PuntoVector3D** vertice;
        int numeroNormales;
        PuntoVector3D** normal;
        int numeroCaras;
        Cara** cara;
    public:
        Malla(int nV, int nN, int nC, PuntoVector3D** v, PuntoVector3D** n, Cara** c);
        Malla();
        ~Malla();
        void newelliza();
        int getNumeroVertices();
        int getNumeroNormales();
        int getNumeroCaras();         
        void draw();
        bool solid; //dibujar con aspecto sólido vs esqueleto de aristas
};
#endif
