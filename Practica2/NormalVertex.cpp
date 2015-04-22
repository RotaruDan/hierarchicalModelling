//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "NormalVertex.h"

	NormalVertex::NormalVertex(){

	}

	NormalVertex::~NormalVertex(){

	}

	int NormalVertex::getVertexIndex(){
		return vertexIndex;
	}

	int NormalVertex::getNormalIndex(){
		return normalIndex;
	}

	void NormalVertex::setVertexIndex(int vIndex){
		vertexIndex = vIndex;
	}

	void NormalVertex::setNormalIndex(int nIndex){
		normalIndex = nIndex;
	}
