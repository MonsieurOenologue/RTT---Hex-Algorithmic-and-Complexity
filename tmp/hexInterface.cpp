#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#define hexagon_r	0.2
#define hexagon_dx	hexagon_r * cos(30.0 * M_PI / 180.0)
#define hexagon_dy	hexagon_r * sin(30.0 * M_PI / 180.0)
#define hexagon_gx	2.0 * hexagon_dx
#define hexagon_gy	2.0 * hexagon_dx * sin(60.0 * M_PI / 180.0)

void glDrawHexagon(float x, float y, float z) {
    glBegin(GL_LINE_LOOP);
	    glVertex3f(x - hexagon_dx, y - hexagon_dy, z);
	    glVertex3f(x - hexagon_dx, y + hexagon_dy, z);
	    glVertex3f(x             , y + hexagon_r,  z);
	    glVertex3f(x + hexagon_dx, y + hexagon_dy, z);
	    glVertex3f(x + hexagon_dx, y - hexagon_dy, z);
	    glVertex3f(x             , y - hexagon_r,  z);
    glEnd();
}

void glDrawHexagonGrid(float x, float y, float z, int ni, int nj) {
    glColor3f(0, 0, 0);
    int i, j;
    float x0;
    x -= float(ni-1) * hexagon_gx * 0.5; // just shift x, y to start position (i=0, j=0)
    x -= float(nj-1) * hexagon_dx * 0.5;
    y -= float(nj-1) * hexagon_gy * 0.5;
    for(j = 0, x0 = x; j < nj; j++, x0 += hexagon_dx, x = x0, y += hexagon_gy) {
        for(i = 0; i < ni; i++, x += hexagon_gx) {
            glDrawHexagon(x, y, z);
        }
    }
}

static void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void glPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear,
    		 fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

int main() {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(640, 640, "Hexxxor3000", NULL, NULL);
	if(!window) {
		std::cout << "Failed to create window context" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}
	glfwSwapInterval(1);

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int screenWidth = mode->width, screenHeight = mode->height;

	while(!glfwWindowShouldClose(window)) {
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		glPerspective(60, (double)windowWidth / (double)windowHeight, 0.1, 100);

		glMatrixMode(GL_MODELVIEW_MATRIX);

		glDrawHexagonGrid(0, 0, -6, 11, 11);

		// Update Screen
		glfwSwapBuffers(window);

		// Check for any input, or window movement
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 1;
}
