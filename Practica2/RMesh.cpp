//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "RMesh.h"

	RMesh::RMesh(){
	}

	RMesh::~RMesh(){
	}

	void RMesh::draw(){		 
		for(int i = 0; i < facesCount; ++i) {
			glLineWidth(1.0);
			glBegin(GL_POLYGON);
			for(int j = 0; j < faces[i]->getVertexCount(); ++j){
				int iN = faces[i]->getVertexArray()[j]->getNormalIndex();
				int iV = faces[i]->getVertexArray()[j]->getVertexIndex();
				glNormal3f(normals[iN]->getX(), normals[iN]->getY(), normals[iN]->getZ());
			}
			glEnd();
		}
	}