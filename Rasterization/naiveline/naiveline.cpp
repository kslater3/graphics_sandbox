
#include <cstdlib>
#include <cmath>

#include "GL/glut.h"


int gcd(int, int);

void pixelpoint(int, int);
void naiveline(int, int, int, int);


void myInit(void) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);

    glPointSize(10.0);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}



void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);


	naiveline(10, 10, 20, 20);
    naiveline(10, 30, 30, 35);


    glFlush();
}



int main(int argc, char **argv) {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 150);

	glutInit(&argc, argv);


	glutCreateWindow("Primitives");

	glutDisplayFunc(myDisplay);


    myInit();

	glutMainLoop();


	return 0;
}


int gcd(int a, int b) {
    if(a > b) {
        int c = b;
        b = a;
        a = c;
    }

    int d = 1;
    int q, r;

    do {
        q = a / b;
        r = a % b;

        d = q + 1;

        a = b;
        b = r;
    } while(r > 1);

    return d;
}


void pixelpoint(int x, int y) {
    int p_x = x * 500/50;
    int p_y = y * 500/50;

    if((p_x % 50) >= 25) {
        p_x += 1;
    }
    if((p_y % 50) >= 25) {
        p_y += 1;
    }


    glBegin(GL_POINTS);
        glVertex2i(p_x, p_y);
    glEnd();
}


void naiveline(int x1, int y1, int x2, int y2) {
    int slope_y = y2 - y1;
    int slope_x = x2 - x1;
    int slope_gcd = gcd(abs(slope_x), abs(slope_y));

    slope_x = slope_x/slope_gcd;
    slope_y = slope_y/slope_gcd;

    int current_x = x1;
    int current_y = y1;


    int walk_x, walk_y;

    while(abs(current_x - x2) > slope_x || abs(current_y - y2) > slope_y) {
        walk_x = slope_x;
        walk_y = slope_y;

        while(walk_x > 0 || walk_y > 0) {
            pixelpoint(current_x, current_y);

            if(walk_x >= walk_y) {
                current_x += 1;
                walk_x -= 1;
            }else {
                current_y += 1;
                walk_y -= 1;
            }
        }

        pixelpoint(current_x, current_y);
    }
}
