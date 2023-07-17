#include <GL/glut.h>
#include <stdio.h>

int value=0;

int x1=200, y1=200, x2=100, y2=300, x3=200, y3=400, x4=300, y4=300;

void draw_pixel(int x, int y)
{
    if (value == 2) glColor3f(0, 1, 0); //green filling
    else            glColor3f(1, 1, 1); //white filling
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void edgedetect(int x1, int y1, int x2, int y2, int *le, int *re)
{
    int mx;
    if( y1>y2 ) // y1>y2 ie. y1=400 ,y2=300
    {
        int temp = y1;
        y1 = y2;            //swap y1,y2
        y2 = temp;

        temp = x1;
        x1 = x2;            //swap x1,x2
        x2 = temp;
    }
    if( y1!=y2) // not a horizontal line
        mx = (x2-x1)/(y2-y1);
    else
        mx = x2-x1;

    int x = x1;
    for(int i=y1; i<=y2; i++)
    {
        if(x < le[i])    le[i] = x;
        if(x > re[i])    re[i] = x;
        x += mx;
    }
}

void scanfill(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int le[500], re[500];
    for (int i = 0; i < 500; i++)
    {
        le[i] = 500;
        re[i] = 0;
    }

    edgedetect(x1, y1, x2, y2, le, re);
    edgedetect(x2, y2, x3, y3, le, re);
    edgedetect(x3, y3, x4, y4, le, re);
    edgedetect(x4, y4, x1, y1, le, re);
    
    if (value == 2) //Fill
    {
        for(int y=0; y<500; y++)
            if(le[y] <= re[y])
                for(int i=le[y]+1; i<re[y]-1; i++)
                    draw_pixel(i, y);
    }
    else            //Reverese fill
    {
        for(int y=499; y>=0; y--)
            if(le[y] <= re[y])
                for(int i=re[y]; i>le[y]; i--)
                    draw_pixel(i, y);
    }    
}

void menu(int num)
{
    switch (num)
    {
    case 0:     exit(0); break;
    case 1:     glClear(GL_COLOR_BUFFER_BIT); break;
    case 2:
    case 3:     value = num;
    }
    glutPostRedisplay();
}

void createMenu(void)
{
    int submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("scanfill polygon", 2);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);
    glutAddMenuEntry("Reverse", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display(void)
{    
    if(value)
    {
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x3, y3);
            glVertex2f(x4, y4);
        glEnd();
        scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
        value = 0;
        glFlush();
    }
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Menu driven Program for Scan filling ");

    createMenu();
    glutDisplayFunc(display);
    myinit();

    glutMainLoop();
}