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
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(300, 0, 0);	  // x   
 
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);      // center
		glVertex3f(0, 300, 0);	  // y
		
		glColor3f(1, 0, 0); 
		glVertex3f(0, 0, 0);      // origin
		glVertex3f(0, 0, 300);	  // z  
		glEnd();
	}