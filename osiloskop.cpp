#include <GL/glut.h>
#include <cmath>

typedef struct {
	float x;
	float y;
} Point2D_t;

typedef struct {
	int x;
	int y;
} Point2D_i;

void init()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 360, -3, 3);
}

void createSinus(Point2D_t* p, int n)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(p[i].x, p[i].y, 0.0);
	}
	glEnd();
}
int n = 16;
int k = 2;
float degree = 0.0;
float m = 0.5;
int radius = 1;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	Point2D_t p[360];

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0,0);
	glVertex2f(360,0);
	glEnd();

	for (int i = 0; i < 360; i++)
	{
		float tetha = float((i + degree) / 57.3);
		p[i].x = (float)i;
		p[i].y = sin(n * tetha)*(1 + m*sin(2 * tetha));
	}
	createSinus(p, 360);
	degree++;
	if (degree >= 360.0)
		degree = 0.0;

	glFlush();
}


void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Grafika Komputer | 2103161005 | Bahrul Amaruddin");
	init();
	glutDisplayFunc(Draw);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
	return 0;
}
