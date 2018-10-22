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
    point3D_t pnt[255];
    int numofFaces;
    face_t face[255];
}object3D_t;

typedef struct {
    int numofVertices;
    point3D_color pnt[100];
    int numofFaces;
    face_t face[32];
}object3D_color;


void Polygon(point2D_t pnt[],int n, RGB color){
    glColor3f(color.r, color.g, color.b);

    // glDrawArrays(GL_LINE_STRIP, 0, sizeof(pnt)/sizeof(float));
    int i;
    glBegin(GL_LINES);
        for (i=0;i<n;i++) {
            glVertex2f(pnt[i].x, pnt[i].y);
        }
    glEnd();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);
    glClear(GL_COLOR_BUFFER_BIT);
}

int char_int(char *d) { int sum = atoi(d); return(int) sum; }

void FromFileOFF(){
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

    for(int l=0; l<row[1][0]; l++){
        printf("Titik %d: %d %d %d, RGB: %d, %d, %d\n", l, row[l+2][0], row[l+2][1], row[l+2][2], row[l+2][3], row[l+2][4], row[l+2][5]);
    }
    
    printf("\n");
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
}

void ObjectKubus(){
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
        printf("Face ke-%d, vertex : %d  ==>\n", i, kubus.face[i].numofVertices );
        for(int j=0; j<kubus.face[i].numofVertices; j++){
            int vertek = kubus.face[i].pnt[j];
            printf("   %d : %.0f, %.0f, %.0f", kubus.face[i].pnt[j], kubus.pnt[vertek].x, kubus.pnt[vertek].y, kubus.pnt[vertek].z);
            printf("\n");

            // insert vertex
            object[index].x = kubus.pnt[vertek].x;
            object[index].y = kubus.pnt[vertek].y;
            index++;
        }
    }
    Polygon(object, 36, {1.0, 0.0, 0.0});
}

void GambarkanObject3D(int numofVertices, point3D_t *pnt, int numofFaces, face_t *face){
    printf("Banyaknya Titik : %d \n", numofVertices);
    printf("Banyaknya Face  : %d \n", numofFaces);

    int t;
    for(t=0; t<numofVertices; t++){
        printf("Titik %d : %.0f, %.0f, %.0f \n", t, pnt[t].x, pnt[t].y, pnt[t].z);
    }

    for(int i=0; i < numofFaces; i++){
        point2D_t points[numofVertices];
        printf("Face ke-%d, vertex : %d  ==>\n", i, face[i].numofVertices );
        for(int j=0; j < face[i].numofVertices; j++){
            int vertek = face[i].pnt[j];
            printf("   %d : %.0f, %.0f, %.0f", face[i].pnt[j], pnt[vertek].x, pnt[vertek].y, pnt[vertek].z);
            
            points[j].x = pnt[vertek].x;
            points[j].y = pnt[vertek].y;
            
            printf("\n");
        }
        Polygon(points, numofVertices, {1.0, 0.0, 0.0});
    }
    
}

void Tabung(){
    
    int n = 12;
    int pointCount = 2*n+1;
    int faceCount = 3*n;
    int pointCenterTop = 0;
    int rangeTop = 75;
    int pointCenterBottom = 0;
    int rangeBottom = -75;
    point3D_t point[pointCount];
    face_t face[36];

    // inisialisasi titik
    int i, r = 100, teta =0;
    for(i=0; i<pointCount; i++){
        if(i<n){
            point[i].x = r * cos(teta);
            point[i].y = rangeTop;
            point[i].z = r * sin(teta);
        }else{
            point[i].x = r * cos(teta);
            point[i].y = rangeBottom;
            point[i].z = r * sin(teta);
        }
        if(teta <330){
            teta += 360/n;
        }else{
            teta = 0;
        }
    }

    // inisialisasi face
    int j, pointTop3 = 0, pointBottom3 = n, pointBottom4 = n, pointTop4 = 0;
    bool first = true;
    for(j=0; j<faceCount; j++){
        if(j<(n-1)){
            face[j].numofVertices = 3;
            // inisialisasi titik pada face
            int k;
            first = true;
            for(k=0; k < face[j].numofVertices; k++){
                if(first){
                    face[j].pnt[k] = pointCenterTop;
                    first = false; 
                }else{
                    face[j].pnt[k] = pointTop3; 
                }
                pointTop3++;
            }
            pointTop3 = pointTop3-2;
        }else if(j == (n-1)){
            face[j].numofVertices = 3;
            face[j].pnt[0] = pointCenterTop;
            face[j].pnt[1] = pointCenterTop+1;
            face[j].pnt[2] = n-1;
        }else if(j>=n && j<(2*n-1)){
            face[j].numofVertices = 3;
            // inisialisasi titik pada face
            int l;
            first = true;
            for(l=0; l < face[j].numofVertices; l++){
                if(first){
                    face[j].pnt[l] = pointBottom3;
                }else{
                    face[j].pnt[l] = pointBottom3; 
                }
                pointBottom3++;
            }
            pointBottom3 = pointBottom3 - 2;
        }else if(j == (faceCount-1)){
            face[j].numofVertices = 4;
            // inisialisasi titik pada face
            face[j].pnt[0] = pointTop4;
            face[j].pnt[1] = pointBottom4;
            face[j].pnt[3] = pointCenterTop + 1;
            face[j].pnt[2] = pointCenterBottom + 1 + n;
        }else{
            face[j].numofVertices = 4;
            // inisialisasi titik pada face
            face[j].pnt[0] = pointTop4;
            face[j].pnt[1] = pointBottom4;
            face[j].pnt[3] = pointTop4 + 1;
            face[j].pnt[2] = pointBottom4 + 1;
            pointBottom4++;
            pointTop4++;           
        }
    }

    GambarkanObject3D(pointCount, point, faceCount, face);
}

void Draw(){
    init();

    // FromFileOFF();

    Tabung();
    printf("\n\n");
    glFlush();
}

int main(int Argc, char* argv[]){
    glutInit(&Argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
    return 0;
}

