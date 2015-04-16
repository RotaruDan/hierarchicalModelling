//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Axis.h"

	Axis::Axis(){

	}

	Axis::~Axis(){

	}

	void Axis::draw(){
		glBegin( GL_LINES );
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(200, 0, 0);	  // x   
		glColor3f(1, 0, 0);
 
		glVertex3f(0, 0, 0);      // center
		glVertex3f(0, 200, 0);	  // y
		glColor3f(0, 1, 0);

		glVertex3f(0, 0, 0);      // origin
		glVertex3f(0, 0, 200);	  // z  
		glColor3f(0, 0, 1); 
		glEnd();
	}