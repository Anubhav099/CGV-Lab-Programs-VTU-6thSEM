#include <GL/glut.h>
#include <stdio.h>

int n;
float v[][3] = {{0, 0, 1},
             {-0.8, -0.4, 0},
             {0, 0.8, 0},
             {0.8, -0.4, 0}};

void divide_triangle(float a[3], float b[3], float c[3], int n)
{
    float v1[3], v2[3], v3[3];
    if (n > 0)
    {
        for (int j=0; j<3; j++)
        {
            v1[j] = (a[j]+b[j])/2;
            v2[j] = (a[j]+c[j])/2;
            v3[j] = (b[j]+c[j])/2;
        }

        divide_triangle(a, v1, v2, n-1);
        divide_triangle(b, v1, v3, n-1);
        divide_triangle(c, v2, v3, n-1);
    }
    else
    {
        glBegin(GL_TRIANGLES);
            glVertex3fv(a);
            glVertex3fv(b);
            glVertex3fv(c);
        glEnd();
    }
}

void tetrahedron(int n)
{
    glColor3f(1.0, 0.0, 0.0);
    divide_triangle(v[0], v[1], v[2], n);
    
    glColor3f(0.0, 1.0, 0.0);
    divide_triangle(v[0], v[2], v[3], n);
    
    glColor3f(0.0, 0.0, 1.0);
    divide_triangle(v[0], v[1], v[3], n);
    
    glColor3f(1.0, 1.0, 0.0);
    divide_triangle(v[1], v[2], v[3], n);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    tetrahedron(n);
    glFlush();

}

int main(int argc, char **argv)
{
    printf("How many divisions?: ");
    scanf("%d", &n);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Anubhav 3D Sierpinski Gasket");
    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}