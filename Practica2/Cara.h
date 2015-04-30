 
#ifndef Cara_H_
#define Cara_H_

class Cara {
	private:
		int numeroVertices; //Número de vértices
        int* arrayIndicesVertices; //Array con los índices de los vértices
		int indiceNormal; //índice a la normal (1 normal por cara)
    public:
        Cara(int nV, int* aiv, int in);
        ~Cara();
        int getNumeroVertices();        
		int getIndiceVertice(int k);        	
		int getIndiceNormal();
};
#endif
