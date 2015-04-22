//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef PV3DH
#define PV3DH

#include <Windows.h>
#include <gl/GL.h>

class PV3D{

	private:
		GLfloat x, y, z;
		int pv;

	public:
		
		PV3D();
		PV3D(GLfloat x, GLfloat y, GLfloat z, int pv);
		~PV3D();
		void normalize();
		PV3D* clone();
		GLfloat dotProduct(PV3D* v);
		PV3D* crossProduct(PV3D* v);

		void setX(GLfloat x);
		void setY(GLfloat y);
		void setZ(GLfloat z);
		void setPv(GLfloat pV);

		GLfloat getX();
		GLfloat getY();
		GLfloat getZ();
		GLfloat getPv();

	

};

#endif