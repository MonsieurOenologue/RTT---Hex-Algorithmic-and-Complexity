#include "Action.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <thread>

#define M_PI 3.14159265358979323846

using namespace std;

/**
 *  @file    GameController.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */

char factor = 1, length = 11;
float offsetX = 0, offsetY = 0;

float hex_corner_angle(char i) {
    short angle_deg = 60 * i + 30;
    return M_PI / 180 * angle_deg;
}

float hex_cornerX(float angle_rad, float x) {
    return length * factor * cos(angle_rad) + x;
}

float hex_cornerY(float angle_rad, float y) {
    return length * factor * sin(angle_rad) + y;
}

void pixel_to_hex(double &x, double &y) {
    double q = ((x + length * factor) * sqrt(3) / 3 - y / 3) / length / factor, r = y * 2 / 3 / length / factor;
    y = round(q)-1;
    x = round(r)-1;
}

void glDrawHexagon(float width, float height) {
    float angle;
    glBegin(GL_LINE_LOOP);
        for(char i = 0; i < 6; ++i) {
            angle = hex_corner_angle(i);
            glVertex2i(hex_cornerX(angle, width), hex_cornerY(angle, height));
        }
    glEnd();
}

void glDrawFlatI(int maxWidth, int maxHeight) {
    float width = sqrt(3) * length * (length + 1 + length / 2), height = length * (length + 1) * 1.5;
    char i, j;
    for(factor = 1; width * (factor+1) < maxWidth && height * (factor+1) < maxHeight; ++factor);
    glColor3f(0, 0, 0);
    offsetX = length * 1.5 * factor;
    offsetY = sqrt(3) * length * (3 / 2) * factor;
    for(i = 0, height = offsetX; i < length; ++i) {
        for(j = 0, width = i * sqrt(3) / 2 * length * factor + offsetY; j < length; ++j) {
            glDrawHexagon(width, height);
            width += sqrt(3) * length * factor;
        }
        height += length * 1.5 * factor;
    }
}

static void error_callback(int error, const char* description) {
    cerr << "Error#" << error << ": " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void mouse_button_callback(GLFWwindow* window, int key, int action, int mods) {
    double xpos, ypos;
    if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        cout << "Mouse pos : (" << xpos << ", " << ypos << ")" << endl;
        pixel_to_hex(xpos, ypos);
        cout << "Board pos : (" << xpos << ", " << ypos << ")" << endl;
    }
}

void glInit() {
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void play(Action moves, string playerR, string playerL, bool player1) {
    char randX, randY;
    if(player1) {
        cout << "C'est au tour de " << playerR << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
        if(playerR == "RandAI") {
            do {
                randX = rand() % moves.getLength();
                randY = rand() % moves.getLength();
            } while(!moves.setPosition(randX, randY, 'x'));
        } else moves.nextMove('x');
        player1 = false;
    } else {
        cout << "C'est au tour de " << playerL << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
        if(playerL == "RandAI") {
            do {
                randX = rand() % moves.getLength();
                randY = rand() % moves.getLength();
            } while(!moves.setPosition(randX, randY, 'o'));
        } else moves.nextMove('o');
        player1 = true;
    }
    moves.displayBoard();
}

int main() {
    // Debug attempt (compiling but not running)
    fprintf(stderr, "Hello world!\n");
    fflush(stderr);

    Action moves;
    bool player1 = true;
    srand(time(NULL));
    string playerR, playerL;
    cout << "Tooltip : \"RandAI\" jouera aléatoirement." << endl
         << "Entrez le nom des joueurs 1 et 2 :";
    cin >> playerR >> playerL;
    moves.setPlayers(playerR, playerL);
    moves.displayBoard();

    thread console(play, moves, playerR, playerL, player1);
    console.join();

	GLFWwindow *window;

	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) {
		cout << "Failed to initialize glfw context" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(650, 400, "Hexxxor3000", NULL, NULL);
	if(!window) {
		cout << "Failed to create window context" << endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		cout << "Failed to initialize OpenGL context" << endl;
		return -1;
	}
	glfwSwapInterval(1);

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int screenWidth = mode->width, screenHeight = mode->height;

    GLint windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
	glInit();

	while(!glfwWindowShouldClose(window)) {
		// Scale to window size
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

		glOrtho(0, windowWidth, windowHeight, 0, 0, 1);
		glDrawFlatI(windowWidth, windowHeight);

		// Enable vertex table
        /*glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        // Send data
        glVertexPointer(P_SIZE, GL_FLOAT, 0, pos);
        glColorPointer(C_SIZE, GL_FLOAT, 0, colors);

        // Draw stuff
        glDrawElements(GL_LINE_STRIP, N_VERTS, GL_UNSIGNED_INT, index);

        // Disable vertex table
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);*/

		// Update Screen
		glFlush();
		glfwSwapBuffers(window);

		// Wait for any input, or window movement
		glfwWaitEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

    if(player1) {
        cout << endl << "Victoire du joueur " << playerL << "." << endl;
    } else {
        cout << endl << "Victoire du joueur " << playerR << "." << endl;
    }

    return 0;
}
