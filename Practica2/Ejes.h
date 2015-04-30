
#ifndef Ejes_H_
#define Ejes_H_

#include "Objeto3D.h"

class Ejes: public Objeto3D {
	protected:
		GLdouble tamanho;
	public:
		Ejes(GLdouble tamanho);
		~Ejes();
		void dibuja();
};
#endif
