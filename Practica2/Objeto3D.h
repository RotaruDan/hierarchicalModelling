
#ifndef Objeto3D_H_
#define Objeto3D_H_

#include "PuntoVector3D.h"
#include "TAfin.h"
  
class Objeto3D {
   protected:   
		TAfin* matriz;
		
   public:	  	   
	    Objeto3D();    
		~Objeto3D();
		virtual void dibuja()=0;
		void traslada(PuntoVector3D* punto);
		void escala(GLfloat fX,GLfloat fY,GLfloat fZ);
		void rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ);
		GLfloat* dameMatrizAfin();
};

#endif
