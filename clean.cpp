#include <GL/glut.h>
#include <cmath>
 
typedef struct { float x; float y; }Point2D_t;
typedef struct { int x; int y; }Point2D_i;
typedef struct { float r; float g; float b;}RGB; 

int j=0;

void Point(float x, float y, int size, RGB color){
    glColor3f(color.r, color.g, color.b);
	glPointSize(size);
    glBegin(GL_POINTS);
        glVertex3f(x,y,0.0);
    glEnd();
}

void Line(Point2D_t *point, int n, RGB color){
    glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<n; i++){
		glVertex3f(point[i].x, point[i].y, 0.0);
	}
	glEnd();
}

void Area(Point2D_t *object, int n, RGB color){
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
	for (int i = 0; i<n; i++){
		glVertex3f(object[i].x, object[i].y, 0);
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

void SatuGarisEmpatTitik(){
    Point(25.0, 25.0, 5, {1.0, 0.0, 0.0});
    Point(25.0, -25.0, 5, {1.0, 0.0, 0.0});
    Point(-25.0, 25.0, 5, {1.0, 0.0, 0.0});
    Point(-25.0, -25.0, 5, {1.0, 0.0, 0.0});

    Point2D_t garis[2] = {{-25, 0}, {0, 50}};
    Line(garis, 2, {1.0, 0.0, 0.0});

    glFlush();
}

void GambarBintang(){
    Point2D_t object[10] = { { 10, 80 }, { 29, 20 }, { 87, 20 }, { 40, 0 },
	{ 58, -40 }, { 10, -10 }, { -38, -40 }, { -16, 0 }, { -67, 20 }, { -13, 20 } };
    
    Area(object, 10, {1.0, 0.0, 0.0});

    glFlush();
}

void TvRusak(){
    for (int i = 0; i<1000; i++){
		float a = (float)(rand() % 180);
		float b = (float)(rand() % 180);
		Point(a, b, 2, {0.0, 0.0, 0.0});
		Point(-a, b, 2, {0.0, 0.0, 0.0});
		Point(a,-b, 2, {0.0, 0.0, 0.0});
		Point(-a,-b, 2, {0.0, 0.0, 0.0});
	}


    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
	for (float x = -180; x <= 180; x+=40){
		for (float y = -180; y <= 180; y += 400){
			glVertex3f(x, y, 0.0);
		}
	}

	for (float y = -180; y <= 180; y += 40){
		for (float x = -180; x <= 180; x += 400){
			glVertex3f(x, y, 0.0);
		}
	}
	glEnd();
    glFlush();
}

void Lingkaran(){
	RGB color = {1.0, 0.0, 0.0};
	Point2D_t p[360];
	float jari = 100;
	for (int i = 0; i<=360; i++){
		double teta = (float)(i / 57.3);
		p[i].x =(float)(jari*cos(teta));
		p[i].y = (float)(jari*sin(teta));
	}
	Line(p, 360, color);
	glFlush();
}

void Sinus(){
    int chartesius[] = {-180,180,-180,180}, k, n;
	float amplitudo = 180.0;
	float x = chartesius[0];

    // set warna grafik
    RGB color = {1,0.5,0};
    // menentukan banyaknya gelombang
	k = 1;
	// n merupakan total titik penentu grafik
    n = ( abs(chartesius[0]) + abs(chartesius[1]) ) * k;
	Point2D_t p[n];

	for (int i = 0; i<n; i++){
		double teta = (float)(i / 57.3);
		p[i].x = x;
		x = x + (float) 1/k;
		p[i].y = (float)(amplitudo*sin(teta));
	}
	Line(p, n, color);
	glFlush();
}

void Daun(){
    Point2D_t p[360];
	float jari;
    static int tick = 0;
    RGB color = {1,0,0};

	// variabel k menentukan banyaknya daun
	int k  = 5;
	for (int i = 0; i<360; i++){
		double teta = (float)((i+tick) / 57.3);
		jari = cos(k * teta);
		p[i].x = (float)(jari*cos(teta)) * 100;
		p[i].y = (float)(jari*sin(teta)) * 100;

        tick++;
	}
	Line(p, 360, color);
    glFlush();
}

void AnimasiLingkaran(){
	glClear(GL_COLOR_BUFFER_BIT);
	Point2D_t p[360];
	float jari = 100;
	for (int i = 0; i<=360; i++){
		double teta = (float)(i / 57.3);
		p[i].x =(float)(jari*cos(teta));
		p[i].y = (float)(jari*sin(teta));
	}

	Line(p, 360, {0, 0.0, 0.0});

	double sudut = (float)(j / 57.3);
	float x1 = (float)(jari*cos(sudut));
	float y1 = (float)(jari*sin(sudut));

	Point(x1, y1, 20, {1,0,0});

	glFlush();

	if(j <=360){
		j++;
	}else{
		j = 0;
	}

}

void Draw(){

    init();

	// SatuGarisEmpatTitik();
    // TvRusak();
	// GambarBintang();

    Lingkaran();
	Sinus();
	Daun();
	AnimasiLingkaran();
    
}

void Timer(int){
	glutPostRedisplay();
    glutTimerFunc(40, Timer, 1);
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(180, 180);
	glutCreateWindow("Grafika Komputer");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
    glutTimerFunc(3600, Timer, 1);
	glutMainLoop();
	return 0;
}