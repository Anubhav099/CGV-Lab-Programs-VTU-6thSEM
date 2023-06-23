#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1416
#define DF 5*sin(theta*PI/180.0) //DF=Displacement Factor

struct Point
{
    float x, y;
};

int bp=20,n=3;
int c[4] = {0,0,0,0};
float theta = 0;
void bino()
{
    int k, j;
    for (k = 0; k <= n; k++)
    {
        c[k] = 1;
        for (j = n; j >= k + 1; j--)
            c[k] *= j;
        for (j = n - k; j >= 2; j--)
            c[k] /= j;
    }
}
void computeBP(float u, struct Point* np, struct Point* p)
{
    int k;
    float blend;
    np->x = np->y = 0.0;
    for (k = 0; k < 4; k++)
    {
        blend = c[k] * pow(u, k) * pow(1 - u, n - k);
        np->x += p[k].x * blend;
        np->y += p[k].y * blend;
    }
}
void bezier(struct Point* p)
{    
    float u;
    int k;
    bino();
    struct Point np;
    glBegin(GL_LINE_STRIP);
        for (k = 0; k <= bp; k++)
        {
            u = (float)k/(float)bp;
            computeBP(u,&np,p);
            glVertex2f(np.x,np.y);
        }
    glEnd();
}
void draw(struct Point p[])
{
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(p);
    }
}
void display()
{
    struct Point p[4] = {{20, 100},{30, 110},{50,90},{60,100}};
    p[1].x += DF;
    p[1].y += DF;
    p[2].x -= DF;
    p[2].y -= DF;
    p[3].x -= DF;
    p[3].y -= DF;
    theta += 1;

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);
	//Draw Flag
    glPushMatrix();
        glColor3f(1,0,0);
        draw(p);
        glColor3f(1, 1, 1);
        draw(p);
        glColor3f(0,1,0);
        draw(p);
    glPopMatrix();

    	//Draw Post
    glColor3f(0.7, 0.5, 0.3);
    glBegin(GL_LINES);
        glVertex2f(20, 100);
        glVertex2f(20, 40);
    glEnd();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void menu(int num){ exit(0); }

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(display);
    //menu to exit
    glutCreateMenu(menu);
    glutAddMenuEntry("Exit",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    gluOrtho2D(0, 150, 0, 150);
    glutMainLoop();
    return 0;
}
