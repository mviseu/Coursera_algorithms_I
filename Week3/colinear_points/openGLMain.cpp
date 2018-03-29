#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}


struct Point2 {
	Point2(int xCoor, int yCoor) : x(xCoor), y(yCoor) {}
	GLfloat x{0};
	GLfloat y{0};
};

std::vector<Point2> points = {Point2(-1, -1), Point2(1, 1)};

void Render()
{     
    //clear color and depth buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //glTranslatef(0.0f,0.0f,0.0f);//move forward 4 units
    
    glBegin(GL_LINES); //starts drawing of points
    glColor3f(0.0f,0.0f,1.0f); //blue color
    glVertex3f(0.5f,0.5f,0.0f);//upper-right corner
    glVertex3f(-0.5f,-0.5,0.0f);//lower-left corner

    glColor3f(1.0f,0.0f,0.0f); //blue color
    glVertex3f(-0.5f,0.5f,0.0f);//upper-right corner
    glVertex3f(0.5f,-0.5,0.0f);//lower-left corner


    glColor3f(0.0f,1.0f,0.0f); //blue color
    glVertex3f(0.0f,0.5f,0.0f);//upper-right corner
    glVertex3f(0.0f,-0.5,0.0f);//lower-left corner
    glEnd();//end drawing of points

    glPointSize(10.0f);//set point size to 10 pixels
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,1.0f); //blue color
    glVertex3f(0.5f,0.5f,0.0f);//upper-right corner
    glVertex3f(-0.5f,-0.5,0.0f);//lower-left corner

    glColor3f(1.0f,0.0f,0.0f); //blue color
    glVertex3f(-0.5f,0.5f,0.0f);//upper-right corner
    glVertex3f(0.5f,-0.5,0.0f);//lower-left corner


    glColor3f(0.0f,1.0f,0.0f); //blue color
    glVertex3f(0.0f,0.5f,0.0f);//upper-right corner
    glVertex3f(0.0f,-0.5,0.0f);//lower-left corner
    glEnd();
}

int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
	    std::cerr << "Initialization failed" << std::endl;
	    return -1;
	}
	std::cout << "Initialization succeeded" << std::endl;

	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	if(!window)  {
		std::cout << "Window initialization failed" << std::endl;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
	    //display
		Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}