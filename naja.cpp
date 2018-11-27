#include <iostream>
#include <GL/glut.h>

using namespace std;

float x_angle, y_angle, z_angle;

void init() {

    x_angle = y_angle = z_angle = 0;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

}

void color3f(GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red / 255, green / 255, blue / 255);
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat red, GLfloat green, GLfloat blue) {

    color3f(red, green, blue);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();

}

void drawTriangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat red, GLfloat green, GLfloat blue) {

    color3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glEnd();
}

void draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
    glViewport(100, 100, 500, 500);

    glRotatef(x_angle, 1.0, 0.0, 0.0);
    glRotatef(y_angle, 0.0, 1.0, 0.0);
    glRotatef(z_angle, 0.0, 0.0, 1.0);

    glPointSize(10.0);
    drawLine(-10.0, 0.0, 0.0, 10.0, 0.0, 0.0, 255.0, 0.0, 0.0);
    drawLine(0.0, -10.0, 0.0, 0.0, 10.0, 0.0, 0.0, 255.0, 0.0);
    drawLine(0.0, 0.0, -10.0, 0.0, 0.0, 10.0, 0.0, 0.0, 255.0);

    // draw pyramid
    drawTriangle(0.0, 5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 5.0, 255, 255, 255);
    drawTriangle(0.0, 5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, -5.0, 0, 255, 204);
    drawTriangle(0.0, 5.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, -5.0, 102, 102, 255);
    drawTriangle(0.0, 5.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 5.0, 255, 255, 0);
    glFlush();
}

void onKeyPressed(unsigned char key, int a, int b) {
    switch (key) {
    case 'x':
        x_angle -= 3;
        break;
    case 'X':
        x_angle += 3;
        break;
    case 'y':
        y_angle -= 3;
        break;
    case 'Y':
        y_angle += 3;
        break;
    case 'z':
        z_angle -= 3;
        break;
    case 'Z':
        z_angle += 3;
        break;
    default:
        break;
    }
}

void display(){
    draw();
}


int main(int argv, char** argc) {

    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D program");
    glEnable(GL_DEPTH_TEST);

    glutKeyboardFunc(onKeyPressed);
    glutDisplayFunc(display);
    glutMainLoop();

    init();

    return 0;
}