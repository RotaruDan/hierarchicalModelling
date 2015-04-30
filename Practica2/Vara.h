
#ifndef Vara_H_
#define Vara_H_

#include <vector>
#include <string>
#include "Objeto3D.h"
#include "Cara.h"

using namespace std;

class Vara: public Objeto3D {
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
		void split(const string& s, string c, vector<string>& v);
		void newelliza();
		Vara(char* fichero);
		~Vara();
		void dibuja();
};
#endif
