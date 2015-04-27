
#ifndef TAfin_H_
#define TAfin_H_

#include <GL/freeglut.h>
 
class TAfin {
   private:
      GLfloat* m;
   public:
      TAfin();
      ~TAfin();
      void traslada(GLfloat X,GLfloat Y,GLfloat Z);
      void escala(GLfloat fX,GLfloat fY,GLfloat fZ);
      void rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ);
      void postMultiplica(GLfloat* mm);
      GLfloat* dameMatrizModelado();
};
#endif
