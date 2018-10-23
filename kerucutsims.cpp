#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "GL/glut.h"
#include <iostream>
#include <fstream>

using namespace std;

typedef struct { float x; float y; } Point2D_t;
typedef struct { int x; int y; } Point2D_i;
typedef struct { int x, y, z; } Point3D_t;
typedef struct { float v[3]; } Vector3D_t;
typedef struct { float m[3][3]; } matrix3D_t;
typedef struct { int m[3][3]; } matrix3D_i;
typedef struct { float r; float g; float b; } color_t;
typedef struct { int numofVertices; long int pnt[100]; } face_t;
typedef struct { int numofVertices; Point3D_t pnt[100]; int numofFaces; face_t fc[100]; } object3D_t;

double sudutRotasi = (float)(0);
object3D_t kerucut2;
object3D_t tabung;

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

void create3DObject(object3D_t object){
	for (int i = 0; i<object.numofFaces; i++){
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j<object.fc[i].numofVertices; j++){
			int p = object.fc[i].pnt[j];
			float x = object.pnt[p].x;
			float y = object.pnt[p].y;
			glVertex3f(x, y, 0.0);
		}
		glEnd();
	}
}
void saveFile(object3D_t object, string name){
    ofstream myfile;
    myfile.open ("/Users/student/Documents/Simson/tabung/tabung/"+name+".off");
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

void display() {
	glColor3f(1.0, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
    
    int sudut = 0, r=100, n= 12;
    tabung.numofVertices = 26;
    tabung.numofFaces = n*3;
    tabung.pnt[0].z=-100;
    tabung.pnt[0].x=0;
    tabung.pnt[0].y=0;
    
    kerucut2.numofVertices = n*2+3;
    kerucut2.numofFaces = n*4;
    kerucut2.pnt[0].z=-100;
    kerucut2.pnt[0].x=0;
    kerucut2.pnt[0].y=0;

	for (int i = 1; i <= n; i++){
        float teta = (double)(sudut / 57.3);
		kerucut2.pnt[i].x = (float)(r*cos(teta));
		kerucut2.pnt[i].z = -100;
		kerucut2.pnt[i].y = (float)(r*sin(teta));
		sudut += 360/n;
	}

    kerucut2.pnt[n+1].z=0;
    kerucut2.pnt[n+1].x=0;
    kerucut2.pnt[n+1].y=0;
    
    sudut = 0;
	for (int i = n+2; i <= n*2+1; i++){
		float teta = (double)(sudut / 57.3);
		kerucut2.pnt[i].x = (float)(r*cos(teta));
		kerucut2.pnt[i].z = 100;
		kerucut2.pnt[i].y = (float)(r*sin(teta));
		sudut += 360/n;
	}
    
    kerucut2.pnt[n*2+2].z=100;
    kerucut2.pnt[n*2+2].x=0;
    kerucut2.pnt[n*2+2].y=0;

	for (int i = 0; i < n; i++){
        if(i+1==n){
            kerucut2.fc[i].numofVertices = 3;
            kerucut2.fc[i].pnt[0] = i+1;
            kerucut2.fc[i].pnt[1] = 1;
            kerucut2.fc[i].pnt[2] = 0;
        }else{
            kerucut2.fc[i].numofVertices = 3;
            kerucut2.fc[i].pnt[0] = i+1;
            kerucut2.fc[i].pnt[1] = i+2;
            kerucut2.fc[i].pnt[2] = 0;
        }
	}
    int j = n;
	for (int i = 0; i < n; i++){
        if(i+1==n){
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = 1;
            kerucut2.fc[j].pnt[2] = n+1;
        }else{
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = i+2;
            kerucut2.fc[j].pnt[2] = n+1;
        }
        j++;
	}
	for (int i = n+1; i < n*2+1; i++){
        if(i+1==n*2+1){
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = n+2;
            kerucut2.fc[j].pnt[2] = n+1;
        }else{
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = i+2;
            kerucut2.fc[j].pnt[2] = n+1;
        }
        j++;
	}
	for (int i = n+1; i < n*2+1; i++){
        if(i+1==n*2+1){
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = n+1;
            kerucut2.fc[j].pnt[2] = n*2+2;
        }else{
            kerucut2.fc[j].numofVertices = 3;
            kerucut2.fc[j].pnt[0] = i+1;
            kerucut2.fc[j].pnt[1] = i+2;
            kerucut2.fc[j].pnt[2] = n*2+2;
        }
        j++;
	}

//	for (int i = 1; i <= n; i++){
//        float teta = (double)(sudut / 57.3);
//		tabung.pnt[i].x = (float)(r*cos(teta));
//		tabung.pnt[i].z = -100;
//		tabung.pnt[i].y = (float)(r*sin(teta));
//		sudut += 30;
//	}
//    sudut = 0;
//	for (int i = n+1; i <= n*2; i++){
//		float teta = (double)(sudut / 57.3);
//		tabung.pnt[i].x = (float)(r*cos(teta));
//		tabung.pnt[i].z = 100;
//		tabung.pnt[i].y = (float)(r*sin(teta));
//		sudut += 30;
//	}
//    tabung.pnt[25].z=100;
//    tabung.pnt[25].x=0;
//    tabung.pnt[25].y=0;
//    
//    
//	for (int i = 0; i < n; i++){
//        if(i+1==n){
//            tabung.fc[i].numofVertices = 3;
//            tabung.fc[i].pnt[0] = i+1;
//            tabung.fc[i].pnt[1] = 1;
//            tabung.fc[i].pnt[2] = 0;
//        }else{
//            tabung.fc[i].numofVertices = 3;
//            tabung.fc[i].pnt[0] = i+1;
//            tabung.fc[i].pnt[1] = i+2;
//            tabung.fc[i].pnt[2] = 0;
//        }
//	}
//	for (int i = n; i < n*2; i++){
//        if(i+1==n*2){
//            tabung.fc[i].numofVertices = 3;
//            tabung.fc[i].pnt[0] = i+1;
//            tabung.fc[i].pnt[1] = n+1;
//            tabung.fc[i].pnt[2] = 25;
//        }else{
//            tabung.fc[i].numofVertices = 3;
//            tabung.fc[i].pnt[0] = i+1;
//            tabung.fc[i].pnt[1] = i+2;
//            tabung.fc[i].pnt[2] = 25;
//        }
//	}
//    int k=n;
//    j=0;
//	for (int i = n*2; i < n*3; i++){
//        if(i+1==n*3){
//            tabung.fc[i].numofVertices = 4;
//            tabung.fc[i].pnt[0] = 12;
//            tabung.fc[i].pnt[1] = 1;
//            tabung.fc[i].pnt[2] = 13;
//            tabung.fc[i].pnt[3] = 24;
//        }else{
//            tabung.fc[i].numofVertices = 4;
//            tabung.fc[i].pnt[0] = j+1;
//            tabung.fc[i].pnt[1] = j+2;
//            tabung.fc[i].pnt[2] = k+2;
//            tabung.fc[i].pnt[3] = k+1;
//        }
//        j++;k++;
//	}
    
	matrix3D_t matrix_X = rotationX(sudutRotasi);
	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	matrix3D_t matrix_Z = rotationZ(sudutRotasi);
	for (int i = 0; i<kerucut2.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = kerucut2.pnt[i].x;
		p.v[1] = kerucut2.pnt[i].y;
		p.v[2] = kerucut2.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		kerucut2.pnt[i].x = p.v[0];
		kerucut2.pnt[i].y = p.v[1];
		kerucut2.pnt[i].z = p.v[2];
	}
	create3DObject(kerucut2);
	sudutRotasi++;
    
	if (sudutRotasi >= 360.0)
		sudutRotasi = 0.0;
	glFlush();
    saveFile(kerucut2,"jampasir");
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}
void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
}

int main(int iArgc, char** cppArgv) {

	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Simson Rinekso");
	Initialize();
	//glutIdleFunc(display);
	glutDisplayFunc(display);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();


    return 0;
}

