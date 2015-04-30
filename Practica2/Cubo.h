
#ifndef Cubo_H_
#define Cubo_H_

#include "Objeto3D.h"

class Cubo: public Objeto3D {
	protected:
		GLdouble tamanho;
	public:
		Cubo(GLdouble tamanho);
		~Cubo();
		void dibuja();
};
#endif
