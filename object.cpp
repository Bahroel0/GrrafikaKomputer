#include <stdio.h>
#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
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

typedef struct {
    point3D_t centerofCirle;
    point3D_t centerofSummit;
    int radius;
    int sudut;
    int height;
}objectKerucut;

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

void create3DObject(object3D_t object){

    // printf("\nObject yang dikirim\n");
    // printf("Banyaknya Titik : %d \n", object.numofVertices);
    // printf("Banyaknya Face  : %d \n", object.numofFaces);
    // printf("\n");

    // print out value of object
    for(int i=0; i<object.numofFaces; i++){
        // printf("Face ke-%d, vertex : %d  ==>\n", i, object.fc[i].numofVertices );
        for(int j = 0; j< object.fc[i].numofVertices; j++){
            int point = object.fc[i].pnt[j];
            float x = object.pnt[point].x;
            float y = object.pnt[point].y;
            float z = object.pnt[point].z;
            // printf("   %d : %.0f, %.0f, %.0f", point, x, y, z);
            // printf("\n");
        }
    }


    for(int i = 0; i < object.numofFaces; i++){
        glColor3f(1, 0, 0);
        // glBegin(GL_LINE_STRIP);
        glBegin(GL_LINE_STRIP);
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


void FromFileOFF(){
    object3D_t object;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // fp = fopen("limas.off", "r");
    // fp = fopen("OFF/tabung.off", "r");
    fp = fopen("A005_01_3622.off", "r");    
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // inisialisasi array untuk menerima nilai titik dan face
    int row[5440][7];
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
    object.numofVertices = row[1][0];

    printf("Jumlah face : %d\n\n", row[1][1]);
    object.numofFaces = row[1][1];

    for(int l=0; l<object.numofVertices; l++){
        // printf("Titik %d: %d %d %d, RGB: %d, %d, %d\n", l, row[l+2][0], row[l+2][1], row[l+2][2], row[l+2][3], row[l+2][4], row[l+2][5]);
        object.pnt[l].x = row[l+2][0];
        object.pnt[l].y = row[l+2][1];
        object.pnt[l].z = row[l+2][2];
        printf("Titik %d: %.3f %.3f %.3f, RGB: %d, %d, %d\n", l, object.pnt[l].x, object.pnt[l].y, object.pnt[l].z, row[l+2][3], row[l+2][4], row[l+2][5]);
    }
    
    printf("\n");
    for(int m=0; m<object.numofFaces; m++){
        int kolomFace = row[m+2+row[1][0]][0];
        int h=1;
        int index = 0;
        object.fc[m].numofVertices = kolomFace;
        printf("Face %d:", m);
        for(h=1; h<=kolomFace; h++){
            object.fc[m].pnt[index] = row[m+2+row[1][0]][h];
            printf(" %d ", row[m+2+row[1][0]][h]);
            index++;
        }
        printf("\n");
    }

    create3DObject(object);

    
    free(line);
    glFlush(); 
    // exit(EXIT_SUCCESS);
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
        float tetas = (double)(teta/ 57.3);
        if(i==0){
            tabung.pnt[i].x = 0;
            tabung.pnt[i].y = rangeTop;
            tabung.pnt[i].z = 0;
        }
        else if(i<=n){
            tabung.pnt[i].x = r * cos(tetas);
            tabung.pnt[i].y = rangeTop;
            tabung.pnt[i].z = r * sin(tetas);
        }
        else if(i== numofVertices){
            tabung.pnt[i].x = 0;
            tabung.pnt[i].y = rangeBottom;
            tabung.pnt[i].z = 0;
        }
        else{
            tabung.pnt[i].x = r * cos(tetas);
            tabung.pnt[i].y = rangeBottom;
            tabung.pnt[i].z = r * sin(tetas);
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

    // create3DObject(tabung);
    // saveFile(tabung, "tabung");

    matrix3D_t matrix_X = rotationX(sudutRotasi);
	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	matrix3D_t matrix_Z = rotationZ(sudutRotasi);
	for (int i = 0; i<tabung.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = tabung.pnt[i].x;
		p.v[1] = tabung.pnt[i].y;
		p.v[2] = tabung.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		tabung.pnt[i].x = p.v[0];
		tabung.pnt[i].y = p.v[1];
		tabung.pnt[i].z = p.v[2];
	}
	create3DObject(tabung);
	sudutRotasi++;

	if (sudutRotasi >= 360.0){
		sudutRotasi = 0.0;
	}
}

void JamPasir(){
    // inisialisasi jari-jari lingkaran tabung
    int r = 150;
    // inisialisasi sudut jarak antar titik pada lingkaran 
    int sudut = 20;

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
        float tetas = (double)(teta/ 57.3);
        if(i == 0){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = height;
            JamPasir.pnt[i].z = pointzCenter;
        }else if(i <= n && i > 0){
            JamPasir.pnt[i].x = r * cos(tetas);
            JamPasir.pnt[i].y = height;
            JamPasir.pnt[i].z = r * sin(tetas);
        }else if(i == (n+1)){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = pointzCenter;
            JamPasir.pnt[i].z = pointzCenter;
        }else if(i<(numofVertices-1) && i > (n+1) ){
            JamPasir.pnt[i].x = r * cos(tetas);
            JamPasir.pnt[i].y = height * -1;
            JamPasir.pnt[i].z = r * sin(tetas);
        }else if(i == (numofVertices-1)){
            JamPasir.pnt[i].x = pointxCenter;
            JamPasir.pnt[i].y = height * -1;
            JamPasir.pnt[i].z = pointzCenter;
        }

        // teta = teta + sudut;
        if(teta <= 360){
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
        }else if(i < (2*n - 1) && i > (n-1)){
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
        }else if(i < (3*n - 1) && i > (2*n - 1)){
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
        }else if(i < (4*n - 1) && i > (3*n - 1)){
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

    // create3DObject(JamPasir);

    matrix3D_t matrix_X = rotationX(sudutRotasi);
	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	matrix3D_t matrix_Z = rotationZ(sudutRotasi);
	for (int i = 0; i<JamPasir.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = JamPasir.pnt[i].x;
		p.v[1] = JamPasir.pnt[i].y;
		p.v[2] = JamPasir.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		JamPasir.pnt[i].x = p.v[0];
		JamPasir.pnt[i].y = p.v[1];
		JamPasir.pnt[i].z = p.v[2];
	}
	create3DObject(JamPasir);
	sudutRotasi++;

	if (sudutRotasi >= 360.0){
		sudutRotasi = 0.0;
	}
    glFlush();





    // create3DObject(JamPasir);
    // saveFile(JamPasir, "jampasir");    
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

    int height = -150;

    int n = 360/sudut;
    int numofVertices = n + 2;
    int numofFaces = 2*n;

    // inisialisasi titik tengah untuk face
    int pointCenterTopFace = 0;
    int pointCenterMidle   = n+1;
    int pointCenterBottomFace = numofVertices;
    
    object3D_t Kerucut;
    Kerucut.numofVertices    = numofVertices;
    Kerucut.numofFaces       = numofFaces;
    
    int teta = 0;

    // input value of each vertex
    for(int i=0; i<Kerucut.numofVertices; i++){
        float tetas = (double)(teta/ 57.3);
        if(i == 0){
            Kerucut.pnt[i].x = pointxCenter;
            Kerucut.pnt[i].y = height;
            Kerucut.pnt[i].z = pointzCenter;
        }else if(i <= n){
            Kerucut.pnt[i].x = r * cos(tetas);
            Kerucut.pnt[i].y = height;
            Kerucut.pnt[i].z = r * sin(tetas);
        }else if(i == (n+1)){
            Kerucut.pnt[i].x = pointxCenter;
            Kerucut.pnt[i].y = pointzCenter;
            Kerucut.pnt[i].z = pointzCenter;
        }else if(i<(numofVertices-1) ){
            Kerucut.pnt[i].x = r * cos(tetas);
            Kerucut.pnt[i].y = height * -1;
            Kerucut.pnt[i].z = r * sin(tetas);
        }else if(i == (numofVertices-1)){
            Kerucut.pnt[i].x = pointxCenter;
            Kerucut.pnt[i].y = height * -1;
            Kerucut.pnt[i].z = pointzCenter;
        }

        if(teta < 360){
            teta += sudut;
        }else {
            teta = sudut;
        }

    }
    int index = 0;
    // input value of face
    for(int i=0; i<Kerucut.numofFaces; i++){
        
        bool first = true;
        Kerucut.fc[i].numofVertices = 3;

        if(i<(n-1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterTopFace;
                    first = false;
                }else{
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i==(n-1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterTopFace;
                    first = false;
                }else if(j==1){
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }else{
                    Kerucut.fc[i].pnt[j] = pointCenterTopFace +1;
                }
            }
            index = 0;
        }else if(i < (2*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else{
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (2*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else if(j==1){
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }else{
                    Kerucut.fc[i].pnt[j] = pointCenterTopFace +1;
                }
            }
            index = n+1;
        }else if(i < (3*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else{
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (3*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterMidle;
                    first = false;
                }else if(j==1){
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }else{
                    Kerucut.fc[i].pnt[j] = pointCenterBottomFace - pointCenterMidle;
                }
            }
            index = pointCenterMidle;
        }else if(i < (4*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterBottomFace -1;
                    first = false;
                }else{
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }
            }
            index--;
        }else if(i == (4*n - 1)){
            for(int j=0; j< Kerucut.fc[i].numofVertices; j++){
                if(first){
                    Kerucut.fc[i].pnt[j] = pointCenterBottomFace;
                    first = false;
                }else if(j==1){
                    index++;
                    Kerucut.fc[i].pnt[j] = index;
                }else{
                    Kerucut.fc[i].pnt[j] = pointCenterBottomFace - pointCenterMidle;
                }
            }
        }       
    }

    // create3DObject(Kerucut);
    // saveFile(Kerucut, "kerucut"); 
    matrix3D_t matrix_X = rotationX(sudutRotasi);
	matrix3D_t matrix_Y = rotationY(sudutRotasi);
	matrix3D_t matrix_Z = rotationZ(sudutRotasi);
	for (int i = 0; i<Kerucut.numofVertices; i++){
		Vector3D_t p;
		p.v[0] = Kerucut.pnt[i].x;
		p.v[1] = Kerucut.pnt[i].y;
		p.v[2] = Kerucut.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		Kerucut.pnt[i].x = p.v[0];
		Kerucut.pnt[i].y = p.v[1];
		Kerucut.pnt[i].z = p.v[2];
	}
	create3DObject(Kerucut);
	sudutRotasi++;

	if (sudutRotasi >= 360.0){
		sudutRotasi = 0.0;
	}
    glFlush();   
}

void KerucutEnamSisi(){
    int xcenter = 0;
    int ycenter = 0;
    int zcenter = 0;

    int radius  = 100;
    int sudut   = 60;
    int height  = 120;

    int n = 360/sudut;

    int numofVertices = 6*n + (6 * 2 );
    int numofFaces       = 6 * 2 * n;

    // inisialisasi kerucut
    objectKerucut Kerucut1, Kerucut2, Kerucut3, Kerucut4, Kerucut5, Kerucut6;
    
    Kerucut1.centerofCirle.x = xcenter;
    Kerucut1.centerofCirle.y = ycenter + radius;
    Kerucut1.centerofCirle.z = zcenter;
    Kerucut1.centerofSummit.x = xcenter;
    Kerucut1.centerofSummit.y = Kerucut1.centerofCirle.y + height;
    Kerucut1.centerofSummit.z = zcenter;
    Kerucut1.sudut = sudut;
    Kerucut1.height= height;
    Kerucut1.radius = radius;

    Kerucut2.centerofCirle.x = xcenter;
    Kerucut2.centerofCirle.y = ycenter + (radius * -1);
    Kerucut2.centerofCirle.z = zcenter; 
    Kerucut2.centerofSummit.x = xcenter;
    Kerucut2.centerofSummit.y = Kerucut1.centerofCirle.y + (height * -1);
    Kerucut2.centerofSummit.z = zcenter;  
    Kerucut2.sudut = sudut;
    Kerucut2.height= height;
    Kerucut2.radius = radius;

    Kerucut3.centerofCirle.x = xcenter + radius;
    Kerucut3.centerofCirle.y = ycenter;
    Kerucut3.centerofCirle.z = zcenter;
    Kerucut3.centerofSummit.x = Kerucut1.centerofCirle.x + height;
    Kerucut3.centerofSummit.y = ycenter;
    Kerucut3.centerofSummit.z = zcenter; 
    Kerucut3.sudut = sudut;
    Kerucut3.height= height;
    Kerucut3.radius = radius;

    Kerucut4.centerofCirle.x = xcenter + (radius * -1);
    Kerucut4.centerofCirle.y = ycenter;
    Kerucut4.centerofCirle.z = zcenter;
    Kerucut4.centerofSummit.x = Kerucut1.centerofCirle.x + (height * -1);
    Kerucut4.centerofSummit.y = ycenter;
    Kerucut4.centerofSummit.z = zcenter; 
    Kerucut4.sudut = sudut;
    Kerucut4.height= height;
    Kerucut4.radius = radius;

    Kerucut5.centerofCirle.x = xcenter;
    Kerucut5.centerofCirle.y = ycenter;
    Kerucut5.centerofCirle.z = zcenter + radius;
    Kerucut5.centerofSummit.x = xcenter;
    Kerucut5.centerofSummit.y = ycenter;
    Kerucut5.centerofSummit.z = Kerucut1.centerofCirle.z + height;
    Kerucut5.sudut = sudut;
    Kerucut5.height= height;
    Kerucut5.radius = radius;

    Kerucut6.centerofCirle.x = xcenter;
    Kerucut6.centerofCirle.y = ycenter;
    Kerucut6.centerofCirle.z = zcenter + (radius * -1);
    Kerucut6.centerofSummit.x = xcenter;
    Kerucut6.centerofSummit.y = ycenter;
    Kerucut6.centerofSummit.z = Kerucut1.centerofCirle.z + (height *  -1);
    Kerucut6.sudut = sudut;
    Kerucut6.height= height;
    Kerucut6.radius = radius;



    object3D_t EnamKerucut;

    EnamKerucut.numofVertices   = numofVertices;
    EnamKerucut.numofFaces      = numofFaces;
    
    // limit of vertex
    int limitvertex1, limitvertex2, limitvertex3, limitvertex4, limitvertex5, limitvertex6;
    limitvertex1 = n+1;
    limitvertex2 = 2*n+3;
    limitvertex3 = 3*n+5;
    limitvertex4 = 4*n+7;
    limitvertex5 = 5*n+9;
    limitvertex6 = 6*n+11;

    // inisialisasi vertex in object EnamKerucut
    int teta = 0;
    for(int i=0; i<EnamKerucut.numofVertices; i++){
        float tetas = (double)(teta/ 57.3);
        if ( i<=limitvertex1 ) {
            // Kerucut1
            if ( i==0 ) {
                EnamKerucut.pnt[i].x = Kerucut1.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut1.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut1.centerofCirle.z;
            }else if ( i<limitvertex1 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut1.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut1.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut1.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut1.centerofSummit.z;
            }
        }else if ( i<=limitvertex2 ) {
            // Kerucut2
            if ( i==(limitvertex2-limitvertex1) ) {
                EnamKerucut.pnt[i].x = Kerucut2.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut2.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut2.centerofCirle.z;
            }else if ( i< limitvertex2 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut2.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut2.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut2.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut2.centerofSummit.z;
            }
        }else if(i<=limitvertex3){
            // Kerucut3
            if ( i==(limitvertex3-limitvertex2) ) {
                EnamKerucut.pnt[i].x = Kerucut3.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut3.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut3.centerofCirle.z;
            }else if ( i< limitvertex3 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut3.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut3.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut3.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut3.centerofSummit.z;
            }
        }else if(i<=limitvertex4){
            // Kerucut4
            if ( i==(limitvertex4-limitvertex3) ) {
                EnamKerucut.pnt[i].x = Kerucut4.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut4.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut4.centerofCirle.z;
            }else if ( i< limitvertex4 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut4.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut4.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut4.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut4.centerofSummit.z;
            }
        }else if(i<=limitvertex5){
            // Kerucut5
            if ( i==(limitvertex5-limitvertex4) ) {
                EnamKerucut.pnt[i].x = Kerucut5.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut5.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut5.centerofCirle.z;
            }else if ( i< limitvertex5 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut5.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut5.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut5.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut5.centerofSummit.z;
            }
        }else if(i<=limitvertex6){
            // Kerucut6
            if ( i==(limitvertex6-limitvertex5) ) {
                EnamKerucut.pnt[i].x = Kerucut6.centerofCirle.x;
                EnamKerucut.pnt[i].y = Kerucut6.centerofCirle.y;
                EnamKerucut.pnt[i].z = Kerucut6.centerofCirle.z;
            }else if ( i< limitvertex6 ){
                EnamKerucut.pnt[i].x = radius * cos(tetas);
                EnamKerucut.pnt[i].y = Kerucut6.centerofCirle.y;
                EnamKerucut.pnt[i].z = radius * sin(tetas);
            }else{
                EnamKerucut.pnt[i].x = Kerucut6.centerofSummit.x;
                EnamKerucut.pnt[i].y = Kerucut6.centerofSummit.y;
                EnamKerucut.pnt[i].z = Kerucut6.centerofSummit.z;
            }
        }
    }

    int limitFace1, limitFace2, limitFace3, limitFace4, limitFace5, limitFace6;
    limitFace1 = 2*n-1;
    limitFace2 = 4*n-1;
    limitFace3 = 6*n-1;
    limitFace4 = 8*n-1;
    limitFace5 = 10*n-1;
    limitFace6 = 12*n-1;

    int index = 0;
    // inisialisasi face in object EnamKerucut
    for(int i=0; i<EnamKerucut.numofFaces; i++){
        bool first  = true;
        EnamKerucut.fc[i].numofVertices = 3;

        if( i<=limitFace1 ) {
            // Kerucut1
            
            for(int j=0; j< EnamKerucut.fc[i].numofVertices; j++){
                if(i<=limitFace1-n){
                    // face lingkaran ada 4
                    // titik 0,1,2,3,4
                    // {0,1,2}{0,2,3}{0,3,4}{0,4,1}
                    

                }else{
                    // face selimut
                    // titik 1,2,3,4,5
                }
            }
            
        }else if( i<=limitFace2 ) {
            // Kerucut2
            if(i<=limitFace2-n){

            }else{
                
            }
        }else if( i<=limitFace3 ) {
            // Kerucut3
            if(i<=limitFace3-n){

            }else{
                
            }
        }else if( i<=limitFace4 ) {
            // Kerucut4
            if(i<=limitFace4-n){

            }else{
                
            }
        }else if( i<=limitFace5 ) {
            // Kerucut5
            if(i<=limitFace5-n){

            }else{
                
            }
        }else if( i<=limitFace6 ) {
            // Kerucut6
            if(i<=limitFace6-n){

            }else{
                
            }
        }
    }

    create3DObject(EnamKerucut);

}


void Draw(){
    init();

    // FromFileOFF();
    // Tabung();
    // JamPasir();
    Kerucut();

    // KerucutEnamSisi();

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