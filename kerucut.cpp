#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <string.h>

using namespace std;

typedef struct { float x; float y; } Point2D_t;
typedef struct { int x; int y; } Point2D_i;
typedef struct { int x, y, z; } Point3D_t;
typedef struct { float v[3]; } Vector3D_t;
typedef struct { float m[3][3]; } matrix3D_t;
typedef struct { int m[3][3]; } matrix3D_i;
typedef struct { float r; float g; float b; } color_t;
typedef struct { int numofVertices; long int pnt[32]; } face_t;
typedef struct { int numofVertices; Point3D_t pnt[100]; int numofFaces; face_t fc[32]; } object3D_t;

double sudutRotasi = (float)(0);
object3D_t kerucut;

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

void display() {
	glColor3f(1.0, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);

	kerucut.numofVertices = 14;
	kerucut.numofFaces = 24;
	int sudut = 0, r = 100;
	kerucut.pnt[0].x = 0;
	kerucut.pnt[0].y = 100;
	kerucut.pnt[0].z = 0;

	kerucut.pnt[13].x = 0;
	kerucut.pnt[13].y = 0;
	kerucut.pnt[13].z = 0;
	for (int i = 1; i <= 12; i++){
		float teta = (double)(sudut / 57.3);
		kerucut.pnt[i].x = (float)(r*cos(teta));
		kerucut.pnt[i].y = 0;
		kerucut.pnt[i].z = (float)(r*sin(teta));
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++){
		kerucut.fc[i].numofVertices = 3;
		if (i<12){
			if (i != 11){
				kerucut.fc[i].pnt[0] = 0;
				kerucut.fc[i].pnt[1] = i + 1;
				kerucut.fc[i].pnt[2] = i + 2;
			}
			else{
				kerucut.fc[i].pnt[0] = 0;
				kerucut.fc[i].pnt[1] = i + 1;
				kerucut.fc[i].pnt[2] = 1;
			}
		}
		else{
			if (i != 23){
				kerucut.fc[i].pnt[0] = 13;
				kerucut.fc[i].pnt[1] = i - 11;
				kerucut.fc[i].pnt[2] = i - 10;
			}
			else{
				kerucut.fc[i].pnt[0] = 13;
				kerucut.fc[i].pnt[1] = i - 11;
				kerucut.fc[i].pnt[2] = 1;
			}
		}
	}
	matrix3D_t matrix_X = rotationX(sudutRotasi);
	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	matrix3D_t matrix_Z = rotationZ(sudutRotasi);
	for (int i = 0; i<kerucut.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = kerucut.pnt[i].x;
		p.v[1] = kerucut.pnt[i].y;
		p.v[2] = kerucut.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		kerucut.pnt[i].x = p.v[0];
		kerucut.pnt[i].y = p.v[1];
		kerucut.pnt[i].z = p.v[2];
	}
	create3DObject(kerucut);
	sudutRotasi++;

	if (sudutRotasi >= 360.0)
		sudutRotasi = 0.0;
	glFlush();
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
	glutCreateWindow("Kerucut");
	Initialize();
	//glutIdleFunc(display);
	glutDisplayFunc(display);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
	return 0;
}