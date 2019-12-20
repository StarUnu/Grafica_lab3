#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
/* Establece el tamaño inicial de la ventana de visualizacion.
*/
GLsizei winWidth=700;
GLsizei winHeight=700;
/* Establece el tamaño de la ventana de recorte en coordenadas universales.*/
GLfloat xwcMin= -50.0, xwcMax=50.0;
GLfloat ywcMin= -50.0, ywcMax=50.0;

vector<int>x;
vector<int>y;

class wcPt3D {
public:
GLfloat x, y, z;
};

void bezier (GLint nCtrlPts, GLint nBezCurvePts); 
void init (void)
{
/* Establece el color de la ventana de visualizacion en blanco.*/
//glClearColor (1.0, 1.0, 1.0, 0.0);
}

void plotPoint_b (wcPt3D bezCurvePt)
{
glBegin (GL_POINTS);
glVertex2f (bezCurvePt.x, bezCurvePt.y);
glEnd ( );
}

void plotPoint (int x, int y)
{
glBegin (GL_POINTS);
glVertex2i (x, y);
glEnd ( );
}
/* Calcula los coeficientes binomiales C para un valor dado de n.*/
void binomialCoeffs (GLint n, GLint * C)
{
	GLint k, j;
	/* Compute n!/(k!(n - k)!). */
	for (k = 0; k <= n; k++) {	
		C[k] = 1;
		for (j=n; j >= k+1; j--)
			C [k] *= j;
		for (j=n - k;j>= 2; j--)
		C [k] /= j;
	}
}

void mouse(int button, int state,int mousex, int mousey){
	if(state==GLUT_DOWN and button==GLUT_LEFT_BUTTON){
		//glClearColor (1.0, 1.0, 1.0, 1.0);
		plotPoint(mousex,mousey);
		x.push_back(mousex);
		y.push_back(mousey);
		glPointSize (4);
		glColor3f (0.0,0.0, 1.0);
		cout<<"Entra por aca deberas"<<mousex<<"sdsd"<<mousey<<endl;
	}
	if(state==GLUT_DOWN and button==GLUT_RIGHT_BUTTON){

		GLint nCtrlPts=4;
		GLint nBezCurvePts=10000;
		//glClear (GL_COLOR_BUFFER_BIT);
		glPointSize (4);
		glColor3f (1.0, 0.0, 0.0);
		//
		//Borra la ventana de visualización.
		//Establece el color de los puntos en rojo.
		bezier (nCtrlPts, nBezCurvePts);
		
	}
	glutPostRedisplay();
	glFlush();
}

void computeBezPt (GLfloat u, wcPt3D * bezPt, GLint nCtrlPts, GLint * C)
{
GLint k, n=nCtrlPts - 1;
GLfloat bezBlendFcn;
bezPt->x=bezPt->y=bezPt->z=0.0;
/*
Calcula las funciones de combinación y los puntos de control de
combinación. */
	for (k = 0; k < nCtrlPts; k++) {
	bezBlendFcn = C[k] * pow (u, k) * pow (1 - u, n - k);
	bezPt->x += x[k]* bezBlendFcn;
	bezPt->y += y[k] * bezBlendFcn;
	//bezPt->z += ctrlPts [k].z * bezBlendFcn;
	}
}

void bezier (GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C, k;
	/* Reserva espacio para los coeficientes binomiales*/
	C= new GLint [nCtrlPts];
	
	binomialCoeffs (nCtrlPts - 1, C);
	for (k=0; k <= nBezCurvePts; k++) {
	u = GLfloat (k) / GLfloat (nBezCurvePts);
	computeBezPt (u, &bezCurvePt, nCtrlPts, C);
	plotPoint_b (bezCurvePt);
	}
	delete [ ] C;
}

void displey (void)
{
	//glClearColor (1.0, 1.0, 1.0, 0.0);
/* Establece un número de puntos de control de ejemplo y un número de
* puntos de curva que se deben dibujar a lo largo de la curva de Bezier.
*/
//wcPt3D ctrlPts [4] { {-40.0, -40.0, 0.0}, {-10.0, 200.0, 0.0},{10.0, -200.0, 0.0}, {40.0, 40.0, 0.0} };
x.push_back(-40.0);
y.push_back(-40.0);

x.push_back(-10.0);
y.push_back(200.0);

x.push_back(-10.0);
y.push_back(-200.0);


x.push_back(40.0);
y.push_back(40.0);

x.push_back(70.0);
y.push_back(70.0);
GLint nCtrlPts=5;
GLint nBezCurvePts=10000;
glClear (GL_COLOR_BUFFER_BIT);
glPointSize (4);
glColor3f (1.0, 0.0, 0.0);
//Borra la ventana de visualización.
//Establece el color de los puntos en rojo.
bezier (nCtrlPts, nBezCurvePts); 
glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
/* Mantiene una relación de aspeto de valor 1.0.*/
glViewport (0, 0, newHeight, newHeight);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ( );
gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);
glClear (GL_COLOR_BUFFER_BIT);
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Curva de Bezier");
	init ( );
	glutDisplayFunc (displey);
	glutMouseFunc(mouse);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
	return 0;
}