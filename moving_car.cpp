#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// Abstract base class for shapes
class Shape {
public:
    // Pure virtual function for drawing a shape
    virtual void draw() const = 0;
};

// Derived class representing a circle
class Circle : public Shape {
private:
    GLfloat rx, ry, cx, cy;

public:
    // Constructor for Circle
    Circle(GLfloat _rx, GLfloat _ry, GLfloat _cx, GLfloat _cy)
        : rx(_rx), ry(_ry), cx(_cx), cy(_cy) {}

    // Override draw function for Circle
    void draw() const override {
        glBegin(GL_POLYGON);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i++) {
            float angle = i * 3.1416 / 180;
            float x = rx * cos(angle);
            float y = ry * sin(angle);
            glVertex2f((x + cx), (y + cy));
        }
        glEnd();
    }
};

// Derived class representing a sun
class Sun : public Circle {
public:
    // Constructor for Sun
    Sun(GLfloat _rx, GLfloat _ry, GLfloat _cx, GLfloat _cy)
        : Circle(_rx, _ry, _cx, _cy) {}

    // Override draw function for Sun
    void draw() const override {
        glColor3ub(255, 215, 0);
        Circle::draw();
    }
};

// Derived class representing a rectangle
class Rectangle : public Shape {
private:
    GLfloat width, height, x, y;

public:
    // Constructor for Rectangle
    Rectangle(GLfloat _width, GLfloat _height, GLfloat _x, GLfloat _y)
        : width(_width), height(_height), x(_x), y(_y) {}

    // Override draw function for Rectangle
    void draw() const override {
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
};

// Initialization function
void init(void) {
    glClearColor(0.0, 0.0, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500); // window size
}

// Variable for car movement
float bx = 10;

// Function to draw hills
void hills() {
    // Hills 1
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(-40, 300);
    glVertex2d(200, 300);
    glVertex2d(100, 450);
    glEnd();

    // Hills 2
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2d(150, 300);
    glVertex2d(350, 300);
    glVertex2d(250, 450);
    glEnd();

    // Hills 3
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300);
    glVertex2d(520, 300);
    glVertex2d(400, 450);
    glEnd();
}

// Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Ground Color
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 150);
    glVertex2d(0, 150);
    glEnd();

    // road
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 55);
    glVertex2d(500, 55);
    glVertex2d(500, 115);
    glVertex2d(0, 115);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 60);
    glVertex2d(500, 60);
    glVertex2d(500, 110);
    glVertex2d(0, 110);
    glEnd();

    // hills
    hills();

    // sun design
    Sun sun(20, 20, 175, 450);
    sun.draw();

    glPushMatrix();
    glTranslatef(bx, 0, 0);

    // Car
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(410, 100);
    glVertex2d(490, 100);
    glVertex2d(485, 130);
    glVertex2d(410, 130);
    glEnd();

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(420, 130);
    glVertex2d(475, 130);
    glVertex2d(465, 160);
    glVertex2d(430, 160);
    glEnd();

    // Car window
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(425, 130);
    glVertex2d(445, 130);
    glVertex2d(445, 150);
    glVertex2d(430, 150);
    glEnd();

    // Car window
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(450, 130);
    glVertex2d(470, 130);
    glVertex2d(465, 150);
    glVertex2d(450, 150);
    glEnd();

    // Car wheel
    glColor3ub(0, 0, 0);
    Circle wheel1(10, 14, 435, 100);
    Circle wheel2(10, 14, 465, 100);
    wheel1.draw();
    wheel2.draw();

    glColor3ub(245, 245, 245);
    Circle hub1(6, 10, 435, 100);
    Circle hub2(6, 10, 465, 100);
    hub1.draw();
    hub2.draw();

    // Building
    glColor3ub(128, 128, 128);
    Rectangle building(50, 150, 50, 50);
    building.draw();

    glPopMatrix();
    bx += 0.2;
    if (bx > 0)
        bx = -500;
    glutPostRedisplay();

    glFlush();
    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("A Moving Car Scenario");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

