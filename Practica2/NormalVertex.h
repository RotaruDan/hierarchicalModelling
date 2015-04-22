//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#ifndef NormalvertexH
#define NormalvertexH

class NormalVertex{

	private:
		int vertexIndex, normalIndex;

	public:
		NormalVertex();
		~NormalVertex();

		void setVertexIndex(int vIndex);
		void setNormalIndex(int nIndex);

		int getVertexIndex();
		int getNormalIndex();
};

#endif