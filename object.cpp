#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <string.h>

typedef struct { float x; float y; }point2D_t;
typedef struct { float r; float g; float b;}RGB;

typedef struct {
    float x, y, z;
}point3D_t;

typedef struct {
    float x, y, z, r, g, b;
}point3D_color;

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

// typedef struct {
//     int numofVertices;
//     point3D_t pnt[100];
//     int numofFaces;
//     face_t fc[32];
// }object3D_t;

typedef struct {
    int numofVertices;
    point3D_color pnt[100];
    int numofFaces;
    face_t fc[32];
}object3D_color;


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

int char_int(char *d) { int sum = atoi(d); return(int) sum; }

void Draw(){
    init();

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

   fp = fopen("limas2.off", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // inisialisasi array untuk menerima nilai titik dan face
    int row[255][255];
    int index = 0;
   while ((read = getline(&line, &len, fp)) != -1) {
        char *p = strtok (line, " ");
        int k=0;
        while (p != NULL)
        {
            row[index][k] = char_int(p);
            p = strtok (NULL, " ");
            k++;
        }
        index++; // mengatur pembacaan setiap baris 
    }
    printf("Jumlah titik : %d\n", row[1][0]);
    printf("Jumlah face : %d\n\n", row[1][1]);
    // printf("kordinat titik pertama : %d, %d, %d\n", row[2][0], row[2][1], row[2][2]);

    for(int l=0; l<row[1][0]; l++){
        printf("Titik %d: %d %d %d, RGB: %d, %d, %d\n", l, row[l+2][0], row[l+2][1], row[l+2][2], row[l+2][3], row[l+2][4], row[l+2][5]);
    }
    
    for(int m=0; m<row[1][1]; m++){
        int kolomFace = row[m+2+row[1][0]][0];
        int h=1;
        printf("Face %d:", m);
        for(h=1; h<=kolomFace; h++){
            printf(" %d ", row[m+2+row[1][0]][h]);
        }
        printf("\n");
    }


    free(line);
    exit(EXIT_SUCCESS);
    
    // object3D_t kubus = {
    //     8,
    //     {
    //         {-25, -25, 25}, {25,-25,25}, {25,25,25}, {-25,25,25}, 
    //         {-25,25,-25}, {25,25,-25}, {25,-25,-25}, {-25,-25,-25}
    //     }, 
    //     12,
    //     {
    //         {3,{3,2,1}}, {3,{0,3,1}}, {3,{0,1,7}}, {3,{4,5,6}}, 
    //         {3,{4,6,7}}, {3,{0,3,7}}, {3,{1,2,6}}, {3,{1,6,7}},  
    //         {3,{2,3,4}}, {3,{2,4,5}}, {3,{2,5,6}}, {3,{3,4,7}}   
    //     }
    // };
    // printf("Banyaknya Titik : %d \n", kubus.numofVertices);
    // printf("Banyaknya Face  : %d \n", kubus.numofFaces);
    // point2D_t object[36];
    // int index = 0;
    // for(int i=0; i<kubus.numofFaces; i++){
    //     printf("Face ke-%d, vertex : %d  ==>\n", i, kubus.fc[i].numofVertices );
    //     for(int j=0; j<kubus.fc[i].numofVertices; j++){
    //         int vertek = kubus.fc[i].pnt[j];
    //         printf("   %d : %.0f, %.0f, %.0f", kubus.fc[i].pnt[j], kubus.pnt[vertek].x, kubus.pnt[vertek].y, kubus.pnt[vertek].z);
    //         printf("\n");

    //         // insert vertex
    //         object[index].x = kubus.pnt[vertek].x;
    //         object[index].y = kubus.pnt[vertek].y;
    //         index++;
    //     }
    // }
    // Polygon(object, 36, {1.0, 0.0, 0.0});
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

