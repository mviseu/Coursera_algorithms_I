#include <GLFW/glfw3.h>
#include <iostream>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}


int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
	    std::cerr << "Initialization failed" << std::endl;
	    return -1;
	}
	std::cout << "Initialization succeeded" << std::endl;

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if(!window)  {
		std::cout << "Window initialization failed" << std::endl;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window)) {
		int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		
		glLineWidth(2.5); 
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(15, 0, 0);
		glEnd();
	    // Keep running
	    
        glfwSwapBuffers(window);
        glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}