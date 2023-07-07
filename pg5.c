#include <GL/glut.h>

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;	   // (Bottom left) Window boundaries
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300; // (Main) Viewport boundaries

// bit codes for the right, left, top, & bottom
int RIGHT = 2;
int LEFT = 1;
int TOP = 8;
int BOTTOM = 4;

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)
// usage of Bitwise OR (|) operator
int ComputeOutCode(double x, double y)
{
	int code = 0;

	if (y > ymax)		code |= TOP;		// above the clip window
	else if (y < ymin)	code |= BOTTOM;		// below the clip window

	if (x > xmax)		code |= RIGHT;		// right of the clip window
	else if (x < xmin)	code |= LEFT;		// left of the clip window

	return code;
}

// Cohen-Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (xmin, ymin) to (xmax, ymax).
// usage of Bitwise OR (|) operator
// usage of Bitwise AND (&) operator
void ClippingAlgorithm(double x0, double y0, double x1, double y1)
{
	// Outcodes for P0, P1, and whatever point lies outside the clip rectangle
	int outcode0, outcode1, outcodeOut;
	int accept = 0, done = 0;
	// compute outcodes
	outcode0 = ComputeOutCode(x0, y0);
	outcode1 = ComputeOutCode(x1, y1);
	do
	{
		if(!(outcode0 | outcode1))			// accept and exit, lies inside the window and does not require clipping.
		{
			accept = 1;
			done = 1;
		}
		else if(outcode0 & outcode1) 		// reject and exit, line lies entirely outside of the window.
			done = 1;
		else								// needs clipping
		{
			double x, y;

			// At least one endpoint is outside the clip rectangle.
			outcodeOut = outcode0 ? outcode0 : outcode1;		//if 1st pt lies outside then select it else select the second point.

			// Now find the intersection point;
			// use formulas y= y0+m*(x-x0), x= x0+(1/m)*(y-y0)
			// which are derived from this formula: (y-y0) = m(x-x0)
			double m = (y1-y0)/(x1-x0);		// Calculate the slope
			if(outcodeOut & TOP)			// Outpoint is above the clip rectangle
			{
				y= ymax;
				x= x0 + (1/m)*(y-y0);
			}
			else if(outcodeOut & BOTTOM) 	// Outpoint is below the clip rectangle
			{
				y= ymin;
				x= x0 + (1/m)*(y-y0);
			}
			else if(outcodeOut & RIGHT) 	// Outpoint is to the right of clip rectangle
			{
				x= xmax;
				y= y0 + m*(x-x0);
			}
			else 							// Outpoint is to the left of clip rectangle
			{
				x= xmin;
				y= y0 + m*(x-x0);
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if(outcodeOut == outcode0)		// if 1st point was selected then update the same
			{
				x0= x;
				y0= y;
				outcode0= ComputeOutCode(x0, y0);
			}
			else							// else the 2nd pt was selected and it needs to be updated
			{
				x1= x;
				y1= y;
				outcode1= ComputeOutCode(x1, y1);
			}
		}
	} while (!done);

	if (accept)
	{
		// Window to viewport mappings
		// Scale parameters
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);
		// Translating from window to viewport and Scaling the computed clipped points; equivalent to:
		// [Translate(xvmin,yvmin)]*[Scale(sx,sy)]*[Translate(-xmin,-ymin)]
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vy1 = yvmin + (y1 - ymin) * sy;

		// draw a red colored viewport
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xvmin, yvmin);
			glVertex2f(xvmax, yvmin);
			glVertex2f(xvmax, yvmax);
			glVertex2f(xvmin, yvmax);
		glEnd();
		
		// draw blue colored clipped line
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

	// draw the SMALL Diagram
	// 1st draw a blue colored window
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmax, ymin);
		glVertex2f(xmax, ymax);
		glVertex2f(xmin, ymax);
	glEnd();

	// 2nd draw the line with red color
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex2d(60, 20);
		glVertex2d(80, 120);
	glEnd();

	// 3rd draw the clipped diagram
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
	glutCreateWindow("Anubhav Cohen-Sutherland Line Clipping Algorithm");
	
	glutDisplayFunc(display);
	myinit();
	
	glutMainLoop();
}