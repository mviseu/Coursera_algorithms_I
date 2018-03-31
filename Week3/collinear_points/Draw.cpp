#include "Draw.h"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace {

const auto unableCreateWindow = std::string("Unable to create a window");
const auto windowName = std::string("Colinear points");
const auto windowDimX = 800;
const auto windowDimY = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void DefineSettings(GLFWwindow& window) {
	glfwSetKeyCallback(&window, key_callback);
	glfwMakeContextCurrent(&window);
    glfwSwapInterval(1);
    glColor3f(0.0f, 0.0f, 1.0f); //blue color
    glPointSize(10.0f);  //set point size to 10 pixels
}

bool IsCoordinateScaled(int coor) {
	coor <= 1 && coor >= -1;
}

bool IsPoint2DScaled(const Point2D& point) {
	return IsCoordinateScaled(point.x) && IsCoordinateScaled(point.y);
}

bool IsLine2DScaled(const Line2D& line) {
	return IsPoint2DScaled(line.p) && IsPoint2DScaled(line.q);
}

void CallVertex(const Point2D& point) {
    glVertex3f(point.x, point.y, 0.0f);
}

void ThrowUnableCreateWindow() {
	throw std::runtime_error(unableCreateWindow);
}

GLFWwindow* CreateWindow() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
	    ThrowUnableCreateWindow();
	}
	auto window = glfwCreateWindow(windowDimX, windowDimY, windowName.c_str(), nullptr, nullptr);
	if(!window)  {
		glfwTerminate();
		ThrowUnableCreateWindow();
	}
	DefineSettings(*window);
	return window;	
}

} // namespace

Draw& Draw::GetDraw() {
	static Draw instance;
	return instance;
}

Draw::Draw() : m_window(*CreateWindow()) {}


bool Draw::ShouldWindowClosePoll() {
    glfwSwapBuffers(&m_window);
    glfwPollEvents();	
    return glfwWindowShouldClose(&m_window);
}

void Draw::AddScaledPoint2D(const Point2D& point) {
	assert(IsPoint2DScaled(point));
    glBegin(GL_POINTS);
    CallVertex(point);
    glEnd();	
}

void Draw::AddScaledLine2D(const Line2D& line) {
	assert(IsLine2DScaled(line));
    glBegin(GL_LINES);
    CallVertex(line.p);
    CallVertex(line.q);
    glEnd();
}

Draw::~Draw() {
	glfwDestroyWindow(&m_window);
	glfwTerminate();	
}