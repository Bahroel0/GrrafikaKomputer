#include <GL/glut.h>
#include <cmath>
 
typedef struct { float x; float y; }Point2D_t;
typedef struct { int x; int y; }Point2D_i;
typedef struct { float r; float g; float b;}RGB;
typedef struct { float v[3];}Vector2D_t;

int j=0;
int index = 0;

Vector2D_t point2vector(Point2D_t point){
	 Vector2D_t vec;
	 vec.v[1] = point.x;
	 vec.v[2] = point.y;
	 vec.v[3] = 1.; 
}

Point2D_t vector2point(Vector2D_t vec){
	Point2D_t point;
	point.x = vec.v[1];
	point.y	= vec.v[2];
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}

void animation(Point2D_t *p, int size) {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2f(p[index].x, p[index].y);
	glEnd();
		index++;
		if (index > size){
			index = 0;
		}
	glutTimerFunc(1, Timer, 0);
}

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

void Polygon(Point2D_t *object, int n, RGB color){
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
	for (int i = 0; i<n; i++){
		glVertex3f(object[i].x, object[i].y, 0);
	}
	glEnd();
    
}

void initAnimasiMatahari(){
    // glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	gluOrtho2D(-120, 120, -120, 120);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// gluOrtho2D(-180, 180, -180, 180);
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
    
    Polygon(object, 10, {1.0, 0.0, 0.0});

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

	animation(p,360);
	glFlush();
}

void AnimasiSinus(){
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

	animation(p,360);
	glFlush();
}


float rot = 0;
void rotation(float x)
{
	if (rot < 360) {
		rot += x;
	}
	else
	{
		rot -= 360;
	}
}
void lingkaran(char GL, float o, float x, float y, float R, float G, float B)
{
	glBegin(GL);
	for (float i = 0.0; i <= 6.28; i += 0.01)
	{
		glColor3f(R, G, B);
		glVertex3f(sin(i)*o + x, cos(i)*o + y, 0);
	}
	glEnd();
}
void light()
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 30.0);
	glVertex2f(5.0, 18.0);
	glVertex2f(-5.0, 18.0);
	glEnd();
}
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	gluOrtho2D(-120.0, 120.0, -120.0, 120.0);
}
void sunlight()
{
	glPushMatrix();
	glRotated(rot, 0, 0, 1);
	for (float r = -45; r >= -315; r -= 45)
	{
		glPushMatrix();
		light();
		glRotated(r, 0, 0, 1);
		light();
		glPopMatrix();
	}
	glPopMatrix();
}
void satelit()
{
	lingkaran(GL_LINE_LOOP, 25, 65.0, -45.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(sin(rot*0.07) * 24, cos(rot*0.07) * 24, 0);
	lingkaran(GL_POLYGON, 5, 65.0, -45.0, 1.0, 1.0, 0.0);
	glPopMatrix();
}



void AnimasiMatahari(){
	glClear(GL_COLOR_BUFFER_BIT);
	rotation(0.1);

	lingkaran(GL_POLYGON, 15, 0.0, 0.0, 1.0, 1.0, 0.0);

	sunlight();

	lingkaran(GL_POINTS, 79, 0.0, 0.0, 1.0, 1.0, 1.0);

	glPushMatrix();
	glRotated(rot, 0, 0, 1);
	lingkaran(GL_POLYGON, 10, 65.0, -45.0, 0.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotated(rot, 0, 0, 1);
	satelit();
	glPopMatrix();
	glFlush();
}

int x = 0;
int z = 0;
int z2 = 90;

void tutup(){
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2i(0,0);
	glVertex2i(-200, 0);

	glColor3f(1,1,1);
	glVertex2i(-200, 20);
	glVertex2i(0,20);
	glEnd();
}

void pegangan(){
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	glVertex2i(-120,20);
	glVertex2i(-80, 20);

	glColor3f(1,1,0);
	glVertex2i(-80, 50);
	glVertex2i(-120,50);
	glEnd();
}

void botol(){
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2i(0,1);
	glColor3f(0,0,1);
	glVertex2i(-200,0);
	glColor3f(0,0,1);
	glVertex2i(-200, -200);
	glColor3f(0,0,1);
	glVertex2i(0, -200);
	glEnd();
}

void reshape(int width, int height){
	glViewport(0,0,(GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -320, 320);
	glMatrixMode(GL_MODELVIEW);
}

void AnimasiTutupBotol(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glLoadIdentity();
	botol();
	glRotatef(x, 0, 0, 1);
	if(z <= 90){
		x -= 1;
		z += 1;
	}
	if(z > 90) {
		x += 1;
		z2 -= 1;
	}
	if(z2 < 0){
		x -= 1;
		z = 0;
		z2 = 90;
	}
	tutup();
	pegangan();
	glFlush();
}
int n = 16;
int konstant = 2;
float tetta = 0;
float m = 0.5;
int radius = 1;




void AnimasiOsiloskop(){
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

	animation(p,360);
	glFlush();
}



void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-180, 180, -180, 180);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Draw(){

    

	// SatuGarisEmpatTitik();
    // TvRusak();
	// GambarBintang();

    // Lingkaran();
	// Sinus();
	// Daun();
	// AnimasiLingkaran();
	
	// AnimasiSinus();
	// AnimasiMatahari();
	// AnimasiTutupBotol();
	init();
	AnimasiOsiloskop();
	


}

void mouse(int button,int state,int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(Draw);
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}



int main(int Argc, char* argv[]) {
	// Animasi Osiloskop
	glutInit(&Argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(180, 180);
	glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	glutIdleFunc(Draw);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;

	
	
	
	
	
	
	
	
	// // Tutup botol
	// glutInit(&Argc, argv);
	// glutInitWindowPosition(100, 100);
	// glutInitWindowSize(600, 600);
	// glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	// glViewport(-300,300,-300,300);
	// glutDisplayFunc(Draw);
	// glutReshapeFunc(reshape);
	// glutTimerFunc(1, Timer, 0);
	// glutMainLoop();
	// End of Tutup Botol


	// Animasi Matahari
	// glutInit(&Argc, argv);
	// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// glutInitWindowSize(600, 600);
	// glutInitWindowPosition(400, 50);
	// glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	// glutDisplayFunc(Draw);
	// glutMouseFunc(mouse);
	// glClearColor(0.0, 0.0, 0.0, 1.0);
	// glColor3f(1.0, 1.0, 0.0);
	// gluOrtho2D(-120.0, 120.0, -120.0, 120.0);
	// glutMainLoop();
	// End of Animasi Matahari


}

