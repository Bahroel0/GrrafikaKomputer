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
    face_t fc[255];
}object3D_t;

typedef struct {
    int numofVertices;
    point3D_color pnt[100];
    int numofFaces;
    face_t fc[32];
}object3D_color;


void create3DObject(object3D_t object){
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
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
            for(int j = 0; j < object.fc[i].numofVertices; j++){
                int point = object.fc[i].pnt[j];
                float x = object.pnt[point].x;
                float y = object.pnt[point].y;
                glVertex3f(x,y,0.0);
            }
        glEnd();
    }
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

void kubus(){
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
    
}


void Tabung(){
    // inisialisasi jari-jari lingkaran tabung
    int r = 100;
    // inisialisasi sudut jarak antar titik pada lingkaran 
    int sudut = 20;

    // inisialisasi ukuran tabung (titik pusat atas, titik pusat bawah dan jarak lingkaran )
    int pointCenterTop = 0;
    int rangeTop = 75;
    int pointCenterBottom = 0;
    int rangeBottom = -75;

    int n = 360/sudut;
    int numofVertices = 2*n + 1;
    int numofFaces = 3*n;
    
    object3D_t tabung;
    tabung.numofVertices    = numofVertices;
    tabung.numofFaces       = numofFaces;

    int teta = 0;
    // inisialisasi vertex
    for(int i=0; i<=numofVertices; i++){
        if(i==0){
            tabung.pnt[i].x = 0;
            tabung.pnt[i].y = rangeTop;
            tabung.pnt[i].z = 0;
        }
        else if(i<=n){
            tabung.pnt[i].x = r * cos(teta);
            tabung.pnt[i].y = rangeTop;
            tabung.pnt[i].z = r * sin(teta);
        }
        else if(i== numofVertices){
            tabung.pnt[i].x = 0;
            tabung.pnt[i].y = rangeBottom;
            tabung.pnt[i].z = 0;
        }
        else{
            tabung.pnt[i].x = r * cos(teta);
            tabung.pnt[i].y = rangeBottom;
            tabung.pnt[i].z = r * sin(teta);
        }

        if(teta < 360){
            teta += sudut;
        }else {
            teta = sudut;
        }
    }

    // inisialisasi face
    int pointTop3 = 0, pointBottom3 = n, pointBottom4 = n, pointTop4 = 0;

    bool first = true;
    
    for(int i=0; i<tabung.numofFaces; i++){
        if(i<(n-1)){
            tabung.fc[i].numofVertices = 3;
            // inisialisasi titik pada face
            
            first = true;
            for(int j=0; j < tabung.fc[i].numofVertices; j++){
                if(first){
                    tabung.fc[i].pnt[j] = 0;
                    first = false; 
                }else{
                    tabung.fc[i].pnt[j] = pointTop3; 
                }
                pointTop3++;
            }
            pointTop3 = pointTop3-2;

        }else if(i == (n-1)){
            tabung.fc[i].numofVertices = 3;
            tabung.fc[i].pnt[0] = pointCenterTop;
            tabung.fc[i].pnt[1] = pointCenterTop+1;
            tabung.fc[i].pnt[2] = n-1;
        }else if(i>=n && i<(2*n)){
            tabung.fc[i].numofVertices = 3;
            // inisialisasi titik pada face
            first = true;
            for(int j=0; j < tabung.fc[i].numofVertices; j++){
                if(first){
                    tabung.fc[i].pnt[j] = 2 * n + 1;
                    first = false;
                }else{
                    tabung.fc[i].pnt[j] = pointBottom3; 
                }
                pointBottom3++;
            }
            pointBottom3 = pointBottom3 - 2;
        }else if(i == (numofFaces-1)){
            tabung.fc[i].numofVertices = 4;
            // inisialisasi titik pada face
            tabung.fc[i].pnt[0] = pointTop4;
            tabung.fc[i].pnt[1] = pointBottom4;
            tabung.fc[i].pnt[3] = pointCenterTop + 1;
            tabung.fc[i].pnt[2] = pointCenterBottom + 1 + n;
        }else{
            tabung.fc[i].numofVertices = 4;
            // inisialisasi titik pada face
            tabung.fc[i].pnt[0] = pointTop4;
            tabung.fc[i].pnt[1] = pointBottom4;
            tabung.fc[i].pnt[3] = pointTop4 + 1;
            tabung.fc[i].pnt[2] = pointBottom4 + 1;
            pointBottom4++;
            pointTop4++;           
        }
    }

    create3DObject(tabung);
}

void Kerucut(){
    // inisialisasi jari-jari lingkaran tabung
    int r = 150;
    // inisialisasi sudut jarak antar titik pada lingkaran 
    int sudut = 30;

    // inisialisasi nilai titik pusat object
    int pointxCenter = 0;
    int pointyCenter = 0;
    int pointzCenter = 0;

    int height = 150;

    int n = 360/sudut;
    int numofVertices = 2*n + 3;
    int numofFaces = 4*n;

    // inisialisasi titik tengah untuk face
    int pointCenterTopFace = 0;
    int pointCenterMidle   = n+1;
    int pointCenterBottomFace = numofVertices;
    
    object3D_t JamPasir;
    JamPasir.numofVertices    = numofVertices;
    JamPasir.numofFaces       = numofFaces;
    
    int teta = 0;

    // input value of each vertex
    for(int i=0; i<JamPasir.numofVertices; i++){
        if(i == 0){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = height;
            JamPasir.pnt[i].z = pointzCenter;
        }else if(i <= n){
            JamPasir.pnt[i].x = r * cos(teta);
            JamPasir.pnt[i].y = height;
            JamPasir.pnt[i].z = r * sin(teta);
        }else if(i == (n+1)){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = pointzCenter;
            JamPasir.pnt[i].z = pointzCenter;
        }else if(i<(numofVertices-1) ){
            JamPasir.pnt[i].x = r * cos(teta);
            JamPasir.pnt[i].y = height * -1;
            JamPasir.pnt[i].z = r * sin(teta);
        }else if(i == (numofVertices-1)){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = height * -1;
            JamPasir.pnt[i].z = pointzCenter;
        }

        if(teta < 360){
            teta += sudut;
        }else {
            teta = sudut;
        }

    }
    int index = 0;
    // input value of face
    for(int i=0; i<JamPasir.numofFaces; i++){
        
        bool first = true;
        JamPasir.fc[i].numofVertices = 3;

        if(i<(n-1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterTopFace;
                    first = false;
                }else{
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i==(n-1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterTopFace;
                    first = false;
                }else if(j==1){
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }else{
                    JamPasir.fc[i].pnt[j] = pointCenterTopFace +1;
                }
            }
            index = 0;
        }else if(i < (2*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else{
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (2*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else if(j==1){
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }else{
                    JamPasir.fc[i].pnt[j] = pointCenterTopFace +1;
                }
            }
            index = n+1;
        }else if(i < (3*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else{
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (3*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else if(j==1){
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }else{
                    JamPasir.fc[i].pnt[j] = pointCenterBottomFace - pointCenterMidle;
                }
            }
            index = pointCenterMidle;
        }else if(i < (4*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterBottomFace -1;
                    first = false;
                }else{
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (4*n - 1)){
            for(int j=0; j< JamPasir.fc[i].numofVertices; j++){
                if(first){
                    JamPasir.fc[i].pnt[j] = pointCenterBottomFace;
                    first = false;
                }else if(j==1){
                    index++;
                    JamPasir.fc[i].pnt[j] = index;
                }else{
                    JamPasir.fc[i].pnt[j] = pointCenterBottomFace - pointCenterMidle;
                }
            }
        }       
    }

    create3DObject(JamPasir);    
}



void Draw(){
    init();

    // FromFileOFF();
    Tabung();
    // Kerucut();


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

