//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef RMeshH
#define RMeshH

#include "PV3D.h"
#include "Face.h"
#include "Actor.h"

class RMesh : public Actor {

	private:
	    int vertexCount, normalsCount, facesCount;
		PV3D** vertex;
		PV3D** normals;
		Face** faces;

	public:
		RMesh();
		~RMesh();
		void draw();
};

#endif