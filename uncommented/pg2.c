#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1425

GLfloat tria[3][3] = {{100.0, 300.0, 200.0}, {100.0, 100.0, 300.0}, {1.0, 1.0, 1.0}};
GLfloat rot_mat[3][3];
GLfloat result[3][3];
GLfloat theta;

void multiply()
{
    int i, j, l;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            result[i][j] = 0;
            for (l = 0; l < 3; l++)
                result[i][j] = result[i][j] + rot_mat[i][l] * tria[l][j];
        }
}

void rotate(GLfloat m, GLfloat n)
{
    rot_mat[0][0] = cos(theta);
    rot_mat[0][1] = -sin(theta);
    rot_mat[0][2] = m;

    rot_mat[1][0] = sin(theta);
    rot_mat[1][1] = cos(theta);
    rot_mat[1][2] = n;

    rot_mat[2][0] = 0;
    rot_mat[2][1] = 0;
    rot_mat[2][2] = 1;

    multiply();
}

void drawtria()
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(tria[0][0], tria[1][0]);
    glVertex2f(tria[0][1], tria[1][1]);
    glVertex2f(tria[0][2], tria[1][2]);
    glEnd();
}

void drawrotatedtria()
{
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(result[0][0], result[1][0]);
    glVertex2f(result[0][1], result[1][1]);
    glVertex2f(result[0][2], result[1][2]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat m, n;
    drawtria();

    m = -100 * (cos(theta) - 1) + 100 * (sin(theta));
    n = -100 * (cos(theta) - 1) - 100 * (sin(theta));
    rotate(m, n);
    glColor3f(0.0, 1.0, 0.0);
    drawrotatedtria();

    rotate(0, 0);
    glColor3f(0.0, 1.0, 1.0);
    drawrotatedtria();

    glFlush();
}

void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400.0, 499.0, -400.0, 499.0);
}

int main(int argc, char **argv)
{
    printf("Enter the rotation angle\n");
    scanf("%f", &theta);
    theta = theta * PI / 180;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Triangle rotation");

    glutDisplayFunc(display);
    myinit();

    glutMainLoop();

    return 0;
}

