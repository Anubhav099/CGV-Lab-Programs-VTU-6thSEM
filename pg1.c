#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
int x1, y11, x2, y2;

void draw_pixel(int x, int y)
{
    glEnable(GL_POINT_SMOOTH);      //optional
    glPointSize(2.0f);              //optional

    glColor3f(0,1,1);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int x2, int y11, int y2)
{
    int incx, incy, inc1, inc2, e;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y11);
    
    if (x1 < x2) incx= 1; else incx= -1;
    if (y11< y2) incy= 1; else incy= -1;
    
    int x = x1;
    int y = y11;
    draw_pixel(x, y);

    if (dx > dy)
    {
        e = 2*dy -dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for(int i=0; i<dx; i++)
        {
            if (e>=0)
            {
                y +=incy;
                e +=inc1;
            }
            else
                e +=inc2;
            x +=incx;
            draw_pixel(x, y);
        }
    }
    else
    {   
        e = 2*dx -dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for(int i=0; i<dy; i++)
        {
            if (e>=0)
            {
                x +=incx;
                e +=inc1;
            }
            else
                e +=inc2;
            y +=incy;
            draw_pixel(x, y);
        }
    }
}

void myDisplay()
{
    draw_line(x1, x2, y11, y2);
    glFlush();
}

void myInit()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 900, 0, 900);
}

void main(int argc, char **argv)
{
    printf("Enter (x1, y1, x2, y2)\n");
    scanf("%d %d %d %d", &x1, &y11, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Anubhav Bresenham's Line Drawing");
    
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}