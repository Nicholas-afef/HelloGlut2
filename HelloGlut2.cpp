#include <GL/glut.h>
#include <iostream>


/*
void render();
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//defines the display mode with many attributes, here is depth, double buffering, and color support + alpha
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);		//defines window position
	glutInitWindowSize(640, 480);			//defines window size
	glutCreateWindow("Window Name");		//title
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();							//"I've finished the initialization process and can start rendering
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//clears screen of all previous drawing
	glBegin(GL_TRIANGLES);			//takes a GL enum, indicates what we're going to draw
	glColor3f(1,0,1);
		//glVertex234fid		defines a suite of functions (2-3-4 dimensions, f-i-d for float, int, double)
	glVertex2f(-0.5, -0.5);
	glColor3f(1,1,0);
	glVertex2f(0.5, -0.5);
	glColor3f(0,1,1);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0.0);
	glEnd();						//every gl begin ends with a gl end
	glutSwapBuffers();				//sends what we've drawn to the screen so it can be rendered
}

void keyboard(unsigned char c, int x, int y) {
	if (c == 27) {
		exit(0);
	}
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		glTranslatef(50, 0, 50);
	}
}

/*
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(10.0, 10.0);
	glVertex2f(150.0, 80.0);
	glVertex2f(100.0, 20.0);
	glVertex2f(200.0, 100.0);
	glEnd();
	glFlush();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();
}
*/