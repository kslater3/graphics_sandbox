/*
I started with a mess, then I switched to a messy para-implementation of the Bresenham Algorithm after reading some
of the Wikipedia article on the matter
*/

#include <cstdlib>
#include <cmath>

#include "GL/glut.h"


int gcd(int, int);

void pixelpoint(int, int);
void naiveline(int, int, int, int);


int window_len = 500;
int window_pixel_depth = 50; //250;


void myInit(void) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);

    glPointSize(((GLfloat) window_len) / ((GLfloat) window_pixel_depth));

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(0.0, (GLdouble) window_len, 0.0, (GLdouble) window_len);
}



void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);


	naiveline(10, 10, 20, 20);
    naiveline(10, 30, 30, 35);
    naiveline(35, 35, 39, 5);
    naiveline(5, 5, 20, 5);
    naiveline(5, 7, 5, 20);

    //naiveline(42, 42, 242, 101);


    glFlush();
}



int main(int argc, char **argv) {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(window_len, window_len);
	glutInitWindowPosition(100, 150);

	glutInit(&argc, argv);


	glutCreateWindow("Primitives");

	glutDisplayFunc(myDisplay);


    myInit();

	glutMainLoop();


	return 0;
}


int gcd(int a, int b) {
    if(a == 0 || b == 0) {
        return 0;
    }

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
    int p_x = x * window_len/window_pixel_depth;
    int p_y = y * window_len/window_pixel_depth;

    if((p_x % window_pixel_depth) >= window_pixel_depth/2) {
        p_x += 1;
    }
    if((p_y % window_pixel_depth) >= window_pixel_depth/2) {
        p_y += 1;
    }


    glBegin(GL_POINTS);
        glVertex2i(p_x, p_y);
    glEnd();
}


void naiveline(int x1, int y1, int x2, int y2) {
    if(x1 == x2) {
        if(y1 > y2) {
            int dummy_y = y2;

            y2 = y1;
            y1 = dummy_y;
        }

        int current_y = y1;

        for(int i = 0; i <= y2 - y1; i++) {
            pixelpoint(x1, current_y);

            current_y += 1;
        }
    }else if(y1 == y2) {
        if(x1 > x2) {
            int dummy_x = x2;

            x2 = x1;
            x1 = dummy_x;
        }

        int current_x = x1;

        for(int i = 0; i <= x2 - x1; i++) {
            pixelpoint(current_x, y1);

            current_x += 1;
        }
    }else {
        int slope_x = x2 - x1;
        int slope_y = y2 - y1;
        int slope_gcd = gcd(abs(slope_x), abs(slope_y));

        slope_x = slope_x/slope_gcd;
        slope_y = slope_y/slope_gcd;


        // y = mx - mx2 + y2
        // y = slope_y*x/slope_x (+1 if slope_y*x % slope_x >= slope_x/2 - 1) - same thing for x2, then add y2 on.
        // Same for the X walk along Y version


        if(abs(slope_y/slope_x) >= 2) {
            if(y1 > y2) {
                int dummy_x = x2;
                int dummy_y = y2;

                x2 = x1;
                y2 = y1;
                x1 = dummy_x;
                y1 = dummy_y;
            }

            int current_x = x1;
            int current_y = y1;

            for(int i = 0; i <= y2 - y1; i++) {
                pixelpoint(current_x, current_y);

                current_y += 1;
                current_x = slope_x * current_y / slope_y;

                if(slope_x * current_y % slope_y >= slope_y/2 - 1) {
                    current_x += 1;
                }

                current_x -= slope_x * y2 / slope_y;

                if(slope_x * y2 % slope_y >= slope_y/2 - 1) {
                    current_x -= 1;
                }

                current_x += y2;
            }
        }else {
            if(x1 > x2) {
                int dummy_x = x2;
                int dummy_y = y2;

                x2 = x1;
                y2 = y1;
                x1 = dummy_x;
                y1 = dummy_y;
            }

            int current_x = x1;
            int current_y = y1;

            for(int i = 0; i <= x2 - x1; i++) {
                pixelpoint(current_x, current_y);

                current_x += 1;
                current_y = slope_y * current_x / slope_x;

                if(slope_y * current_x % slope_x >= slope_x/2 - 1) {
                    current_y += 1;
                }

                current_y -= slope_y * x2 / slope_x;

                if(slope_y * x2 % slope_x >= slope_x/2 - 1) {
                    current_y -= 1;
                }

                current_y += y2;
            }
        }
    }
}
