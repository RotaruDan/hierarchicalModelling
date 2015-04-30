 
#ifndef Cara_H_
#define Cara_H_

class Cara {
	private:
		int numeroVertices; //N�mero de v�rtices
        int* arrayIndicesVertices; //Array con los �ndices de los v�rtices
		int indiceNormal; //�ndice a la normal (1 normal por cara)
    public:
        Cara(int nV, int* aiv, int in);
        ~Cara();
        int getNumeroVertices();        
		int getIndiceVertice(int k);        	
		int getIndiceNormal();
};
#endif
