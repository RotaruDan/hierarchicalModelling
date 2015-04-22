//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef FaceH
#define FaceH

#include "NormalVertex.h"

class Face{

	private:
		int vertexCount;
		NormalVertex** vertexArray;

	public:
		Face();
		~Face();

		int getVertexCount();
		NormalVertex** getVertexArray();

		void setVertexCount(int vCount);
		void setVertexArray(NormalVertex** vArray);

};

#endif