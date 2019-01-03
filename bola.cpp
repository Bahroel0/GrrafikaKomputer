#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


double sudutRotasi = (float)(0);
typedef struct { 
    float x; float y; 
}point2D_t;

typedef struct { 
    float r; float g; float b;
}RGB;

typedef struct {
    float x, y, z;
}point3D_t;

typedef struct { float v[3]; } Vector3D_t;
typedef struct { float m[3][3]; } matrix3D_t;

typedef struct {
    int numofVertices;
    short int pnt[32];
}face_t;

typedef struct {
    int numofVertices;
    point3D_t pnt[5440];
    int numofFaces;
    face_t fc[5440];
}object3D_t;

int char_int(char *d) { int sum = atoi(d); return(int) sum; }


matrix3D_t createIdentity(){
	matrix3D_t rotate;
	rotate.m[0][0] = 0.0;
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = 0.0;
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = 0.0;
	rotate.m[2][1] = 0.0;
	return rotate;
}

matrix3D_t rotationX(float teta){
	matrix3D_t rotate = createIdentity();
	rotate.m[0][0] = 1.0;
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = cos(teta / 57.3);
	rotate.m[1][2] = -sin(teta / 57.3);

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = sin(teta / 57.3);
	rotate.m[2][2] = cos(teta / 57.3);

	return rotate;
}

matrix3D_t rotationY(float teta){
	matrix3D_t rotate = createIdentity();
	rotate.m[0][0] = cos(teta / 57.3);
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = sin(teta / 57.3);

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = 1.0;
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = -sin(teta / 57.3);
	rotate.m[2][1] = 0.0;
	rotate.m[2][2] = cos(teta / 57.3);

	return rotate;
}

matrix3D_t rotationZ(float teta){
	matrix3D_t rotate = createIdentity();
	rotate.m[0][0] = cos(teta / 57.3);
	rotate.m[0][1] = -sin(teta / 57.3);
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = sin(teta / 57.3);
	rotate.m[1][1] = cos(teta / 57.3);
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = 0.0;
	rotate.m[2][2] = 1.0;

	return rotate;
}

Vector3D_t operator +(Vector3D_t a, Vector3D_t b){
	Vector3D_t c;
	for (int i = 0; i<3; i++){
		c.v[i] = a.v[i] + b.v[i];
	} return c;
}

Vector3D_t operator -(Vector3D_t a, Vector3D_t b){
	Vector3D_t c;
	for (int i = 0; i<3; i++){
		c.v[i] = a.v[i] - b.v[i];
	} return c;
}

Vector3D_t operator *(matrix3D_t a, Vector3D_t b){
	Vector3D_t c; for (int i = 0; i<3; i++){
		c.v[i] = 0; for (int j = 0; j<3; j++){
			c.v[i] += a.m[i][j] * b.v[j];
		}
	} return c;
}

Vector3D_t operator ^(Vector3D_t a,Vector3D_t b){
    Vector3D_t c;
    c.v[0]=a.v[1]*b.v[2]-a.v[2]*b.v[1];
    c.v[1]=a.v[2]*b.v[0]-a.v[0]*b.v[2];
    c.v[2]=a.v[0]*b.v[1]-a.v[1]*b.v[0];
    return c;
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);
    glClear(GL_COLOR_BUFFER_BIT);
}


void cetak(object3D_t object){

    printf("\nObject yang dikirim\n");
    printf("Banyaknya Titik : %d \n", object.numofVertices);
    printf("Banyaknya Face  : %d \n", object.numofFaces);
    printf("\n");

    // print out value of object
    for(int i=0; i<object.numofFaces; i++){
        printf("Face ke-%d, vertex : %d  ==>\n", i, object.fc[i].numofVertices );
        for(int j = 0; j< object.fc[i].numofVertices; j++){
            int point = object.fc[i].pnt[j];
            float x = object.pnt[point].x;
            float y = object.pnt[point].y;
            float z = object.pnt[point].z;
            printf("   %d : %.0f, %.0f, %.0f", point, x, y, z);
            printf("\n");
        }
    }

    for(int i = 0; i < object.numofFaces; i++){
        
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            for(int j = 0; j < object.fc[i].numofVertices; j++){
                int point = object.fc[i].pnt[j];
                float x = object.pnt[point].x;
                float y = object.pnt[point].y;
                glVertex3f(x,y,0.0);
            }
        glEnd();
    }
}

void saveFile(object3D_t object, string name){
    ofstream myfile;
    myfile.open ("/home/bahroel/Kuliah/Semester 5/Grafika Komputer/Project/OpenGL/OFF/"+name+".off");
    myfile << "COFF\n";
    myfile << std::to_string(object.numofVertices)+" "+std::to_string(object.numofFaces)+" 0\n";
    for(int i=0; i<object.numofVertices;i++){
        myfile << std::to_string(object.pnt[i].x)+" "+std::to_string(object.pnt[i].y)+" "+std::to_string(object.pnt[i].z)+" "+" 255 0 0 255\n";
    }
    for (int i=0; i<object.numofFaces; i++) {
        myfile << std::to_string(object.fc[i].numofVertices);
        for (int j = 0; j<object.fc[i].numofVertices; j++) {
            myfile << " "+std::to_string(object.fc[i].pnt[j]);
        }
        myfile << "\n";
    }
    
    myfile.close();
}

void GambarBola(){
    point3D_t center;
    int sudut, n, radius, index, teta;
    object3D_t bola;

    index = 0;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    radius   = 100;

    sudut   = 20;
    n       = 360/sudut;
    double sudutx = (float)(sudut);

    bola.numofVertices  = n*n;
    bola.numofFaces     = n;

    
    teta = 0;

    for(int i=0; i<n; i++){
        float tetas = (double)(teta/ 57.3);
    
        bola.pnt[i].x = 0;
        bola.pnt[i].y = (float)radius * cos(tetas);
        bola.pnt[i].z = (float)radius * sin(tetas);

        if(teta < 360){
            teta += sudut;
        }else {
            teta = sudut;
        }               
    }

    for(int k=1; k<n; k++){
        index = 0;
        matrix3D_t matrix = rotationY(sudutx);

        for(int i=n*k; i< (n*k)+n; i++){

            Vector3D_t p;
            p.v[0] = bola.pnt[index].x;
            p.v[1] = bola.pnt[index].y;
            p.v[2] = bola.pnt[index].z;
            
            p = (matrix)*(p);
            
            bola.pnt[i].x = p.v[0];
            bola.pnt[i].y = p.v[1];
            bola.pnt[i].z = p.v[2];
                
            index++;
            if(index == n){
                index = 0;
            }
        }


        sudutx += (float)sudut;
        if (sudutx >= 360.0){
            sudutx = 0.0;
        }
    }

    index = 0;
    for(int i=0; i< bola.numofFaces; i++){
        bola.fc[i].numofVertices = n;
        for(int j=0; j< bola.fc[i].numofVertices; j++){
            bola.fc[i].pnt[j] = index;
            index++;
        }
    }

	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	for (int i = 0; i<bola.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = bola.pnt[i].x;
		p.v[1] = bola.pnt[i].y;
		p.v[2] = bola.pnt[i].z;

		p = (matrix_Y)*(p);

		bola.pnt[i].x = p.v[0];
		bola.pnt[i].y = p.v[1];
		bola.pnt[i].z = p.v[2];
	}
	cetak(bola);
	sudutRotasi += 0.05;

	if (sudutRotasi >= 360.0){
		sudutRotasi = 0.0;
	}

    // printf("posisi titik 0 : %f, %f, %f", bola.pnt[0].x, bola.pnt[0].y, bola.pnt[0].z);

}

void Draw(){
    init();

    GambarBola();
    // Kerucut();

    printf("\n\n");
    glFlush();
}

int main(int Argc, char* argv[]){
    glutInit(&Argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(800, 800);
	glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
    return 0;
}