#include <GL/glut.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

int RIGHT = 2;
int LEFT = 1;
int TOP = 8;
int BOTTOM = 4;

int ComputeOutCode(double x, double y)
{
    int code = 0;

    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;

    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;

    return code;
}

void ClippingAlgorithm(double x0, double y0, double x1, double y1)
{
    int outcode0, outcode1, outcodeOut;
    int accept = 0, done = 0;
    
    outcode0 = ComputeOutCode(x0, y0);
    outcode1 = ComputeOutCode(x1, y1);
    do
    {
        if (!(outcode0 | outcode1))
        {
            accept = 1;
            done = 1;
        }
        else if (outcode0 & outcode1)
            done = 1;
        else
        {
            double x, y;

            outcodeOut = outcode0 ? outcode0 : outcode1;

            double m = (y1 - y0) / (x1 - x0);
            if (outcodeOut & TOP)
            {
                y = ymax;
                x = x0 + (1 / m) * (y - y0);
            }
            else if (outcodeOut & BOTTOM)
            {
                y = ymin;
                x = x0 + (1 / m) * (y - y0);
            }
            else if (outcodeOut & RIGHT)
            {
                x = xmax;
                y = y0 + m * (x - x0);
            }
            else
            {
                x = xmin;
                y = y0 + m * (x - x0);
            }

            if (outcodeOut == outcode0)
            {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    } while (!done);

    if (accept)
    {
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);

        double vx0 = xvmin + (x0 - xmin) * sx;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vy1 = yvmin + (y1 - ymin) * sy;

        glColor3f(1, 0, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xvmin, yvmin);
            glVertex2f(xvmax, yvmin);
            glVertex2f(xvmax, yvmax);
            glVertex2f(xvmin, yvmax);
        glEnd();
        
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex2d(vx0, vy0);
            glVertex2d(vx1, vy1);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex2d(60, 20);
        glVertex2d(80, 120);
    glEnd();

    ClippingAlgorithm(60, 20, 80, 120);

    glFlush();
}

void myinit()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 499, 0, 499);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
    
    glutDisplayFunc(display);
    myinit();
    
    glutMainLoop();
}

