#ifndef INTERFACE_H
#define INTERFACE
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>

typedef void (*fptr)();

void draw_circle(double, double);
void draw_rect(double, double);
void changeSize(int w, int h);

class Interface {
private:
    int pos_x, pos_y;
    int size_x, size_y;

    static void display_obj();

public:
    Interface(int, int, int, int);
    void init(int &, char **);
    void add_nodes(double x, double y);
    void add_edges(double x, double y);
    void display_func();
    ~Interface();
};

#endif

std::vector<std::pair<double, double>> nodes_obj;
std::vector<std::pair<double, double>> edges_obj;
double ratio;

Interface::Interface(int i_pos_x, int i_pos_y, int i_size_x, int i_size_y) 
: pos_x(i_pos_x), pos_y(i_pos_y), size_x(i_size_x), size_y(i_size_y) {
    ratio = size_x /size_y;
}

Interface::~Interface() {
}

void Interface::init(int &argc, char *argv[]) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(size_x, size_y);
	glutCreateWindow("Graph");
    
}

void Interface::display_func() {
    glutDisplayFunc(display_obj);
    glutReshapeFunc(changeSize);
    glutMainLoop();
}

void Interface::add_nodes(double x, double y) {
    nodes_obj.push_back(std::make_pair(x, y));
}

void Interface::add_edges(double x, double y) {
    edges_obj.push_back(std::make_pair(x, y));
}

void Interface::display_obj() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto obj : nodes_obj) {
        draw_circle(obj.first, obj.second);
        std::cout << obj.first / ratio << " " << obj.second / ratio << std::endl;
    }

    glutSwapBuffers();    
}

void draw_circle(double x, double y) {
    glBegin(GL_POLYGON);
    float theta, radio = 0.5;
    for (int i = 0; i < 360; ++i) {
        theta =  i * 3.14 / 180;
        glVertex3f(x / ratio + radio * cos(theta), y / ratio + radio * sin(theta), -5.0);
    }
    glEnd();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
