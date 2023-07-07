#include<GL/glut.h>

void obj(double tx,double ty,double tz,double sx,double sy,double sz)
{
	glRotated(50,0,1,0);		// Rotate 50deg in +y axis
	glRotated(10,-1,0,0);		// Rotate 10deg in -x axis
	glRotated(11.7,0,0,-1);		// Rotate 11.7deg in -z axis
	
	glTranslated(tx,ty,tz);		// Translate with given tx, ty, tz
	
	if(sx==0) glutSolidTeapot(0.09);
	else{
		glScaled(sx,sy,sz);
		glutSolidCube(1);
	}
	glLoadIdentity();
}

void display()
{
	glViewport(0,0,700,700);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// All walls are scaled as (1, 1, 0.04) but
	// For different shapes for each wall 0.04 swaps with 1 for each wall
	obj(0,0,0.5,1,1,0.04); 			// Back wall
	obj(0,-0.5,0,1,0.04,1);			// Bottom wall
	obj(-0.5,0,0,0.04,1,1);			// Left Wall
	
	// All legs are drawn at y = -0.3, scaled as (0.02, 0.2, 0.02)
	obj(0,-0.3,0,0.02,0.2,0.02); 		// Back Leg x=0 z=0
	obj(0,-0.3,-0.4,0.02,0.2,0.02);		// Left Leg x=0 z=-ve
	obj(0.4,-0.3,0,0.02,0.2,0.02);		// Right Leg x=+ve z=0
	obj(0.4,-0.3,-0.4,0.02,0.2,0.02);	// Front Leg x=+ve z=-ve
	
	obj(0.2,-0.18,-0.2,0.6,0.02,0.6); 	// Table Top
	
	obj(0.3,-0.1,-0.3,0,0,0);		// Teapot
	
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc,argv);
	
	float ambient[]={1,1,1,1};
	float light_pos[]={27,80,2,3};
	
	glutInitWindowSize(700,700);
	glutCreateWindow("Anubhav Teapot");
	glutDisplayFunc(display);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
}
