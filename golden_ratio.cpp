#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979
#define GR 1.61803398874989	//golden ratio constant

using namespace std;

GLint window_width  = 800;
GLint window_height = 600;
vector<double> X;
vector<double> Y;

int initial_step = 10;
int step = 2;
double angle = 360 * GR;

void golden_ratio(){
	double x, y;
	double n_x, n_y;
	double c_x, c_y;
	double step_x, step_y;
	double theta;

	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++){
		x = X.at(i);
		y = Y.at(i);

		if(i == 0){
			c_x = x;
			c_y = y;
			n_x = x + initial_step;
			n_y = y;
			X.push_back(n_x);
			Y.push_back(n_y);
			glVertex2f(n_x, n_y);
			continue;
		}
		x -= c_x;
		y -= c_y;

		n_x = x*cos(angle*PI/180) - y*sin(angle*PI/180);
		n_y = x*sin(angle*PI/180) + y*cos(angle*PI/180);

		theta = acos(n_x/sqrt((n_x*n_x)+(n_y*n_y)))*180/PI;	//theta = arc cosine (adjacent/hipothenuse) in radians
		step_x = step*cos(theta*PI/180);
		step_y = step*sin(theta*PI/180);

		n_x += c_x + step_x;
		n_y += c_y + step_y;

		X.push_back(n_x);
		Y.push_back(n_y);
		glVertex2f(n_x, n_y);
	}
	glEnd();
	glutSwapBuffers();
}

void display (void){
	double x, y;
	
	glPointSize(5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POINTS);
	for (int i = 0; i < X.size(); i++){
		x = X.at(i);
		y = Y.at(i);
		glVertex2f(x , y);
	}
	glEnd();

	glutSwapBuffers();
	//glFlush();
}

void mouse(int bin, int state , int x , int y){
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		y = window_height - y;

		X.push_back(x);
		Y.push_back(y);

		glPointSize(5);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
			glVertex2f(x , y);
		glEnd();
		golden_ratio();
		glutSwapBuffers();
	}	
}

void reshape(GLint width, GLint height){
	window_width  = width;
	window_height = height;
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 27:	// ESCAPE key
		exit (0);
		break;
	}
}

int main (int argc,char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(window_width,window_height);
	/*Set the posotion of window*/
	glutInitWindowPosition(0,0);
	glutCreateWindow("Golden Ratio Flower");

	glClearColor (0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport( 0,0, window_width, window_height);
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0.0, window_width, 0.0, window_height, 1.0, -1.0 );

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 

	/* initialize viewing values */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
}
