//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Face.h"

	Face::Face(){

	}

	Face::~Face(){

	}

	int Face::getVertexCount(){
		return vertexCount;
	}

	NormalVertex** Face::getVertexArray(){
		return vertexArray;
	}

	void Face::setVertexArray(NormalVertex** vArray){
		vertexArray = vArray;
	}

	void Face::setVertexCount(int vCount){
		vertexCount = vCount;
	}
