#include <stdio.h>
#include <GL/glut.h>
#include <cmath>

typedef struct { float x; float y; }point2D_t;
typedef struct { float r; float g; float b;}RGB;

typedef struct {
    float x, y, z;
}point3D_t;

typedef struct {
    int numofVertices;
    short int pnt[32];
}face_t;

typedef struct {
    int numofVertices;
    point3D_t pnt[100];
    int numofFaces;
    face_t fc[32];
}object3D_t;

void Polygon(point2D_t pnt[],int n, RGB color){
    glColor3f(color.r, color.g, color.b);
    int i;
    glBegin(GL_LINE_LOOP);
        for (i=0;i<n;i++) {
            glVertex2f(pnt[i].x, pnt[i].y);
        }
    glEnd();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-180, 180, -180, 180);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw(){
    init();
    object3D_t kubus = {
        8,
        {
            {-25, -25, 25}, {25,-25,25}, {25,25,25}, {-25,25,25}, 
            {-25,25,-25}, {25,25,-25}, {25,-25,-25}, {-25,-25,-25}
        }, 
        12,
        {
            {3,{3,2,1}}, {3,{0,3,1}}, {3,{0,1,7}}, {3,{4,5,6}}, 
            {3,{4,6,7}}, {3,{0,3,7}}, {3,{1,2,6}}, {3,{1,6,7}},  
            {3,{2,3,4}}, {3,{2,4,5}}, {3,{2,5,6}}, {3,{3,4,7}}   
        }
    };
    printf("Banyaknya Titik : %d \n", kubus.numofVertices);
    printf("Banyaknya Face  : %d \n", kubus.numofFaces);
    point2D_t object[36];
    int index = 0;
    for(int i=0; i<kubus.numofFaces; i++){
        printf("Face ke-%d, vertex : %d  ==>\n", i, kubus.fc[i].numofVertices );
        for(int j=0; j<kubus.fc[i].numofVertices; j++){
            int vertek = kubus.fc[i].pnt[j];
            printf("   %d : %.0f, %.0f, %.0f", kubus.fc[i].pnt[j], kubus.pnt[vertek].x, kubus.pnt[vertek].y, kubus.pnt[vertek].z);
            printf("\n");

            // insert vertex
            object[index].x = kubus.pnt[vertek].x;
            object[index].y = kubus.pnt[vertek].y;
            index++;
        }
    }
    Polygon(object, 36, {1.0, 0.0, 0.0});
    printf("\n\n");
    glFlush();
}


int main(int Argc, char* argv[]){
    glutInit(&Argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(180, 180);
	glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
    return 0;
}

