//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "PV3D.h"

	PV3D::PV3D(){

	}

	PV3D::PV3D(GLfloat x, GLfloat y, GLfloat z, int pv){
		setX(x);
		setY(y);
		setZ(z);
		setPv(pv);
	}

	PV3D::~PV3D(){

	}

	void PV3D::normalize(){

	}

	PV3D* PV3D::clone(){

	}

	PV3D* PV3D::crossProduct(PV3D *v){

	}

	GLfloat PV3D::dotProduct(PV3D *v){

	}

	GLfloat PV3D::getX(){
		return x;
	}
	
	GLfloat PV3D::getY(){
		return y;
	}
	
	GLfloat PV3D::getZ(){
		return z;
	}
	
	GLfloat PV3D::getPv(){
		return pv;
	}

	void PV3D::setX(GLfloat newX){
		x = newX;
	}
	
	void PV3D::setY(GLfloat newY){
		y = newY;
	}
	
	void PV3D::setZ(GLfloat newZ){
		z = newZ;
	}
	
	void PV3D::setPv(GLfloat newPv){
		pv = newPv;
	}


