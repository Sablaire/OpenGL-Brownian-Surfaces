
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"glaux.lib")
#include <windows.h>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <stdlib.h> 
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
int alpha = 0, beta = 0;
double x[50], y[50];
void CALLBACK mouse(AUX_EVENTREC *event) {	
	static int x0, y0 = -12345;
	if (y0 != -12345) {
		alpha += event->data[AUX_MOUSEX] - x0;
		beta += event->data[AUX_MOUSEY] - y0; }
	x0 = event->data[AUX_MOUSEX];
	y0 = event->data[AUX_MOUSEY];}
float surface(float ak, float bk, float ck)
{
	float func=0.0;
	float alpk=10;
	for (int i=0;i<=628;i++){
		for (int j=0;j<628;j++){
			func=ck*exp(alpk)*sin(i*cos(bk)+j*sin(bk)+ak);}}
return func;}
void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glColor3f(0.0, 0.0, 0.0); 	
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(0.0, 640.0, 0.0, 480.0); }
void Draw(){
	int i, npoints = 400, x;
	float y;
	float scalefactor = 10.0, frand;
	float colornew = 0.0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glTranslatef(450, 400, 0);
	glScalef(0.5, 0.5, 0.5);
	y = 0.0;
	glColor3f(0, 0, 0);
	glPointSize(3.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	for (float surface=0; surface<=npoints/100; surface+=0.1)	{
	 glColor3f(colornew-1, colornew-1, 1);
		for(i=0; i<=npoints; i++)	{
			x=(-1+(float)i/(npoints/2))*npoints;
			frand=rand()/32768.0;
			y=y+scalefactor*(frand-0.5);
			glVertex3i(x, -200, surface*100);
			glVertex3i(x, y, surface*100);		}
		colornew+=0.1;	}
	glEnd();
	glFlush();}
void CALLBACK display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotated(alpha, 0, 1, 0);
	glRotated(beta, -1, 0, 0);
	Draw();
	glPopMatrix();
	auxSwapBuffers(); }
void CALLBACK resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -500, 500);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW); }
void main(){
	srand(time(0));
	auxInitPosition(600, 10, 800, 600);
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | GL_DOUBLE);
	auxInitWindow("Brownian surfaces");
	auxIdleFunc(display);
	auxReshapeFunc(resize);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSELOC, mouse);
	auxMainLoop(display);  }
