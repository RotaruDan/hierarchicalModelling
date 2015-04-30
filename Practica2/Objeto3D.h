
#ifndef Objeto3D_H_
#define Objeto3D_H_

#include "PuntoVector3D.h"
#include "TAfin.h"
  
class Objeto3D {
   protected:   
		TAfin* matriz;
		GLfloat r, g, b, a;
		
   public:	  	   
	    Objeto3D();    
		~Objeto3D();
		virtual void dibuja()=0;
		void traslada(PuntoVector3D* punto);
		void escala(GLfloat fX,GLfloat fY,GLfloat fZ);
		void rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ);
		GLfloat* dameMatrizAfin();
		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		GLfloat getR();
		GLfloat getG();
		GLfloat getB();
		GLfloat getA();
};

#endif
