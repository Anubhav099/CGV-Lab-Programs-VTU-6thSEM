#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.1425

GLfloat tria[3][3]={	{100.0,300.0,200.0},		// orginal X coordinates
			{100.0,100.0,300.0},		// orginal Y coordinates
			   {1.0,1.0,1.0}	};	// orginal Z coordinates

GLfloat rot_mat[3][3];	// will store the 2D rotation matrix
GLfloat result[3][3];	// will store the rotated coordinates of the triangle
GLfloat theta;

void multiply()			// Normal Matrix Multiplication
{
	int i,j,l;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			result[i][j]=0;
			for(l=0;l<3;l++)
				result[i][j]=result[i][j]+rot_mat[i][l]*tria[l][j];
		}
}

void rotate(GLfloat m,GLfloat n)	// 2D Rotation Matrix
{
	//1st row
	rot_mat[0][0]=cos(theta);
	rot_mat[0][1]=-sin(theta);
	rot_mat[0][2]=m;
	//2nd row
	rot_mat[1][0]=sin(theta);
	rot_mat[1][1]=cos(theta);
	rot_mat[1][2]=n;
	//3rd row
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;
	
	multiply();
}

void drawtria()
{
	glColor3f(0.0,0.0,1.0);	//blue color
	glBegin(GL_TRIANGLES);
		glVertex2f(tria[0][0],tria[1][0]);	// X and Y coordinates of 1st pnt
		glVertex2f(tria[0][1],tria[1][1]);	// X and Y coordinates of 2nd pnt
		glVertex2f(tria[0][2],tria[1][2]);	// X and Y coordinates of 3rd pnt
	glEnd();
}

void drawrotatedtria()
{
	glColor3f(1.0,0.0,1.0);	// magenta color
	glBegin(GL_TRIANGLES);
		glVertex2f(result[0][0],result[1][0]);	// X and Y computed-rotated coordinates of 1st point
		glVertex2f(result[0][1],result[1][1]);	// X and Y computed-rotated coordinates of 2nd point
		glVertex2f(result[0][2],result[1][2]);	// X and Y computed-rotated coordinates of 3rd point
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat m,n;
	drawtria();			// Draw the original triangle
	
	// Rotation matrix values wrt pivot pnt (x,y) wiz (100,100) here
	m=-100*(cos(theta)-1)+100*(sin(theta));		// derived from composite matrix of
	n=-100*(cos(theta)-1)-100*(sin(theta));		// [Translate(x,y)]*[Rotate()]*[Translate(-x,-y)]
	rotate(m,n);					// Set the rotation matrix wrt to x,y ie 100,100
	glColor3f(0.0,1.0,0.0);		
	drawrotatedtria();
	
	// Rotation matrix wrt origin (0,0)
	rotate(0,0);
	glColor3f(0.0,1.0,1.0);
	drawrotatedtria();
	
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0,499.0,-400.0,499.0);
}

void main(int argc,char **argv)
{
	printf("Enter the rotation angle\n");
	scanf("%f",&theta);
	theta=theta*PI/180;	// converting degree to radians to pass it to openGL functions
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Anubhav Triangle rotation");
	
	glutDisplayFunc(display);
	myinit();
	
	glutMainLoop();
}
