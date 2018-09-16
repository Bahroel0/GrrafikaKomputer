#include <GL/glut.h>
#include <cmath>
 
typedef struct { float x; float y; }Point2D_t;
typedef struct { int x; int y; }Point2D_i;

void TitikGaris() {
	// inisialize
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f(25.0, 25.0, 0.0);
		glVertex3f(-25.0, 25.0, 0.0);
		glVertex3f(-25.0, -25.0, 0.0);
		glVertex3f(25.0, -25.0, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
		glVertex3f(-25.0, 0.0, 0.0); glVertex3f(25.0, 0.0, 0.0);
		glVertex3f(-25.0, -25.0, 0.0); glVertex3f(-25.0, 25.0, 0.0);
		glVertex3f(-25.0, -25.0, 0.0); glVertex3f(25.0, -25.0, 0.0);
		glVertex3f(25.0, -25.0, 0.0); glVertex3f(25.0, 25.0, 0.0);
		glVertex3f(-25.0, 25.0, 0.0); glVertex3f(25.0, 25.0, 0.0);
	glEnd();
	glFlush();
}

void TitikBerantakan(){
	// inisialize
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1.,-1.,1.);

	glClear(GL_COLOR_BUFFER_BIT);
		
	//gambar titik random
	// glColor3f(0.0, 0.0, 0.0);
	// glPointSize(2);
	// glBegin(GL_POINTS);
	// for (int i = 0; i<1000; i++){
	// 	float a = (float)(rand() % 100) / 100;
	// 	float b = (float)(rand() % 100) / 100;
	// 	glVertex3f(a, b, 0.0);
	// 	glVertex3f(-a, b, 0.0);
	// 	glVertex3f(a,-b, 0.0);
	// 	glVertex3f(-a,-b, 0.0);
	// }
	// glEnd();

	//gambar kotak2 mendatar
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
	for (float x = -1.0; x <= 1.0; x+=0.2){
		for (float y = -1; y <= 1; y += 2.0){
			glVertex3f(x, y, 0.0);
		}
	}

	for (float y = -1; y <= 1; y += 0.2){
		for (float x = -1.0; x <= 1.0; x += 2.0){
			glVertex3f(x, y, 0.0);
		}
	}
	glEnd();

	glFlush();
}

void Bintang(Point2D_t *bintang, int n){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i<n; i++){
		glVertex3f(bintang[i].x, bintang[i].y, 0);
	}
	glEnd();
}

void GambarBintang(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);

	glClear(GL_COLOR_BUFFER_BIT);
	/* Point2D_t bintang[10] = { { 70, 136 }, { 89, 80 }, { 147, 80 }, { 100, 45 },
	{ 118, -9 }, { 70, 24 }, { 22, -9 }, { 44, 45 }, { -7, 80 }, { 53, 80 } }; */
	Point2D_t bintang[10] = { { 10, 80 }, { 29, 20 }, { 87, 20 }, { 40, 0 },
	{ 58, -40 }, { 10, -10 }, { -38, -40 }, { -16, 0 }, { -67, 20 }, { -13, 20 } };
	Bintang(bintang, 10);
	glFlush();
}

void Lingkaran(Point2D_t *p, int n){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<n; i++){
		glVertex3f(p[i].x, p[i].y, 0.0);
	}
	glEnd();
}

void Sinus(){
	int chartesius[] = {-200,200,-200,200}, k, n;
	float amplitudo = 200.0;
	float x = chartesius[0];
	k = 1;
	float rasio = 1/ (float)k;
	n = ( abs(chartesius[0]) + abs(chartesius[1]) ) * k;
	Point2D_t p[n];

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(chartesius[0],chartesius[1], chartesius[2], chartesius[3]);

	for (int i = 0; i<n; i++){
		double teta = (float)(i / 57.3);
		p[i].x = x;
		x = x +1;
		p[i].y = (float)(amplitudo*sin(teta));
	}
	Lingkaran(p, n);
	glFlush();
}

void GambarLingkaran(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);

	Point2D_t p[360];
	float jari = 100;
	for (int i = 0; i<=360; i++){
		double teta = (float)(i / 57.3);
		p[i].x =(float)(jari*cos(teta));
		p[i].y = (float)(jari*sin(teta));
	}
	Lingkaran(p, 360);
	glFlush();
}

void GambarDaun(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);

	static int tick = 0;
	Point2D_t p[360];
	float jari;

	// variabel k menentukan banyaknya daun
	int k  = 3;
	for (int i = 0; i<360; i++){
		double teta = (float)((i+tick) / 57.3);
		jari = cos(k * teta);
		p[i].x = (float)(jari*cos(teta)) * 100;
		p[i].y = (float)(jari*sin(teta)) * 100;
		tick++;
	}
	Lingkaran(p, 360);
	glFlush();
}



void Draw(){
	// TitikGaris();
	// TitikBerantakan();
	// GambarBintang();
	Sinus();
	// GambarLingkaran();
	// GambarDaun();
}


int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Grafika Komputer");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}



