 
#include "Vara.h"
#include <fstream>

#define PI 3.14159265359;



Vara:: Vara(char* fichero) {
	string STRING;
	ifstream infile;
	infile.open (fichero);
	getline(infile, STRING);
	getline(infile, STRING);
	int vertexNumber = stoi(STRING);
	getline(infile, STRING);	
	getline(infile, STRING);	
	getline(infile, STRING);
	getline(infile, STRING);	
	getline(infile, STRING);		
	
	vector<string> res;
	int i = 0;
	while(!infile.eof()) {
		getline(infile,STRING); // Saves the line in STRING.
		split(STRING, "\t", res);
	}
	infile.close();

	int m = vertexNumber; //número de puntos en el perfil original
	PuntoVector3D** profile = new PuntoVector3D*[m];
	for(int i = 0; i < m; ++i) {
		int idx = 2 * i;
		PuntoVector3D *pv3d = new PuntoVector3D(stof(res[idx]), stof(res[idx + 1]), 0, 1);
		profile[i] = pv3d;
	}
	int n = 50; //número de rotaciones

	//Tamaños de los arrays
	numeroVertices = n * m;
	numeroCaras = n*(m-1);
	numeroNormales = numeroCaras;
	
	//Creación de los arrays
	vertice = new PuntoVector3D*[numeroVertices];
	normal = new PuntoVector3D*[numeroNormales];
	cara = new Cara*[numeroCaras];
	
	//Colocar el perfil original en la tabla de vertices
	for(int j = 0; j < m; ++j) {
		vertice[j] = profile[j]->clonar();
	}
	
	//Vertices de la malla
	for(int i = 1; i < n; ++i) {
		double theta = (double) i * 360 / (double) n / 180 * PI;
		double c = cos(theta);
		double s = sin(theta);

		//R_y es la matriz de rotación sobre el eje Y
		for(int j = 0; j < m; ++j){
			int index = i * m + j;
			//Transformar el punto j‐ésimo del perfil original
			GLfloat x = c * profile[j]->getX() + s * profile[j]->getZ();
			GLfloat z = -s * profile[j]->getX() + c * profile[j]->getZ();
			PuntoVector3D* p = new PuntoVector3D(x, profile[j]->getY(), z, 1);
			vertice[index] = p;
		}
	}

	
	//Construcción de las caras
	int faceIndex = 0;
	for(int i = 0; i < n; ++i) { //unir el perfil i‐ésimo con el (i+1)%n‐ésimo
		for(int j = 0; j < m-1; ++j) { //este vértice cierra una cara
			int index = i * m + j;
			int* nv = new int[4];
			nv[0] = index;
			nv[1] = (index + m) % numeroVertices;
			nv[2] = (index + 1 + m) % numeroVertices;
			nv[3] = index + 1;
			Cara* face = new Cara(4, nv, faceIndex);
			cara[faceIndex] = face;
			++faceIndex;
		}
	}

	newelliza();
}

Vara:: ~Vara() {

}

void Vara::split(const string& s, string c,  vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void Vara::newelliza() {
    for (int i=0; i<numeroCaras; i++) {
		int v0=cara[i]->getIndiceVertice(0);
        int v1=cara[i]->getIndiceVertice(1);
        int v2=cara[i]->getIndiceVertice(2);
        int v3=cara[i]->getIndiceVertice(3);
        PuntoVector3D* v=newell(v0, v1, v2, v3);
        int iN=cara[i]->getIndiceNormal();
        normal[iN]=v;
    }
}

PuntoVector3D* Vara::newell(int i1, int i2, int i3, int i4) {
    PuntoVector3D* v1=vertice[i1];
    PuntoVector3D* v2=vertice[i2];
    PuntoVector3D* v3=vertice[i3];
    PuntoVector3D* v4=vertice[i4];
    GLfloat nx=(v2->getY()-v1->getY())*(v2->getZ()+v1->getZ())+
               (v3->getY()-v2->getY())*(v3->getZ()+v2->getZ())+
               (v4->getY()-v3->getY())*(v4->getZ()+v3->getZ())+
               (v1->getY()-v4->getY())*(v1->getZ()+v4->getZ());
    GLfloat ny=(v2->getZ()-v1->getZ())*(v2->getX()+v1->getX())+
               (v3->getZ()-v2->getZ())*(v3->getX()+v2->getX())+
               (v4->getZ()-v3->getZ())*(v4->getX()+v3->getX())+
               (v1->getZ()-v4->getZ())*(v1->getX()+v4->getX());
    GLfloat nz=(v2->getX()-v1->getX())*(v2->getY()+v1->getY())+
               (v3->getX()-v2->getX())*(v3->getY()+v2->getY())+
               (v4->getX()-v3->getX())*(v4->getY()+v3->getY())+
               (v1->getX()-v4->getX())*(v1->getY()+v4->getY());
    PuntoVector3D* n=new PuntoVector3D(-nx, -ny, -nz, 0);
    n->normalizar();
    return n;
}

void Vara:: dibuja() {
	glMatrixMode(GL_MODELVIEW);
	for (int i=0; i<numeroCaras; i++) {		
		glBegin(GL_POLYGON);
			int iN=cara[i]->getIndiceNormal(); //1 normal por cara
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());   
			for (int j=0; j<cara[i]->getNumeroVertices(); j++) {
				int iV=cara[i]->getIndiceVertice(j);			         				 
				glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			}//for
		glEnd();
	}//for
}




