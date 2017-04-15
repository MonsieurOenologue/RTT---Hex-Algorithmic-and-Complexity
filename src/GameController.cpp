#include "Bruteforce.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <unistd.h>
#elif defined __unix__
#include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#include <cstdlib>
#include <time.h>
#include <thread>
#include <mutex>

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

Action moves;
Bruteforce bf1, bf2;
mutex playing;
bool player1, turnPlayed, playConsole, keepGoing, color;
string playerR, playerL;

unsigned char factor = 1, length = 11;
float offsetX = 0, offsetY = 0, *colors;

float hex_corner_angle(unsigned char i) {
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
    (color) ? glBegin(GL_POLYGON) : glBegin(GL_LINE_LOOP);
    for(unsigned char i = 0; i < 6; ++i) {
        angle = hex_corner_angle(i);
        glVertex2i(hex_cornerX(angle, width), hex_cornerY(angle, height));
    }
    glEnd();
}

void glDrawFlatI(int maxWidth, int maxHeight) {
    float width = sqrt(3) * length * (length + 1 + length / 2), height = length * (length + 1) * 1.5;
    unsigned char i, j;
    for(factor = 1; width * (factor+1) < maxWidth && height * (factor+1) < maxHeight; ++factor);
    offsetX = length * 1.5 * factor;
    offsetY = sqrt(3) * length * (3 / 2) * factor;
    for(i = 0, height = offsetX; i < length; ++i) {
        for(j = 0, width = i * sqrt(3) / 2 * length * factor + offsetY; j < length; ++j) {
            (color) ? glColor3f(colors[(i*length+j)*3], colors[(i*length+j)*3+1], colors[(i*length+j)*3+2]) : glColor3f(0, 0, 0);
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
    if(keepGoing && !playConsole && !turnPlayed && key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        //cout << "Position souris : (" << xpos << ", " << ypos << ")" << endl;
        pixel_to_hex(xpos, ypos);
        //cout << "Position plateau : (" << xpos << ", " << ypos << ")" << endl;
        if(xpos < 0 || xpos >= length || ypos < 0 || ypos >= length) {
            cerr << "Erreur : les coordonnees (" << xpos << "," << ypos << ") sortent du plateau de jeu." << endl;
        } else {
            while(!playing.try_lock()) sleep(0.1);

            if(moves.setPosition(xpos, ypos)) {
                turnPlayed = true;
            } else {
                cerr << "Coup impossible, veuillez recommencer..." << endl;
            }
            playing.unlock();
        }
    }
}

void glInit() {
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void play() {
    unsigned char x, y, latestMove;
    string currentPlayer;
    srand(time(NULL));

    while(moves.continueGame()) {
        turnPlayed = false;
        currentPlayer = ((player1) ? playerR : playerL);
        cout << "C'est au tour de " << currentPlayer << "." << endl;
        if(currentPlayer == "RandAI") {
            do {
                x = rand() % length;
                y = rand() % length;
            } while(!moves.setPosition(x, y));
            turnPlayed = true;
        } else if(currentPlayer == "Bruteforce") {
            if(player1 && bf1.playNextMove(moves)) turnPlayed = true;
            else if(!player1 && bf2.playNextMove(moves)) turnPlayed = true;
            else cerr << "Bruteforce ne peux pas jouer sur ce plateau..." << endl;
        } else {
            if(playConsole) {
                cout << "Entrez la position de votre pion (colonne + ligne) :" << endl;
                playing.lock();
                moves.nextMove();
                turnPlayed = true;
                playing.unlock();
            } else {
                cout << "Cliquez sur la position de votre pion dans l'interface :" << endl;
                while(!playing.try_lock()) sleep(0.1);
                while(!turnPlayed) {
                    if(playConsole) break;
                    playing.unlock();
                    while(!playing.try_lock()) sleep(0.1);
                }
            }
        }
        if(turnPlayed) {
            latestMove = moves.getLatestMove();
            x = ceil(latestMove / length);
            y = latestMove % length;
            if(player1) {
                colors[(x * length + y) * 3 + 1] = 0;
                colors[(x * length + y) * 3 + 2] = 0;
            } else {
                colors[(x * length + y) * 3] = 0;
                colors[(x * length + y) * 3 + 1] = 0;
            }
            moves.displayBoard();
            cout << "Position du pion : " << (unsigned char)(y+65) << (unsigned char)(x+97) << endl << endl;
            player1 = !player1;
        } else cout << endl;
        playing.unlock();
    }

    cout << endl << "Victoire du joueur " << ((player1) ? "2 (bleu) : "+playerL : "1 (rouge) : "+playerR) << "." << endl
         << endl << "A la prochaine sur Hexxxor3000!\nAppuyez sur une touche pour quitter le programme...";

    cin.sync();
    cin.get();

    keepGoing = false;
}

int main() {
    cout << "Bienvenue sur Hexxxor3000!" << endl
         << "Voulez-vous jouer dans la console (c : defaut) ou dans l'interface (i) ?" << endl;
    cin >> playerR;
    playConsole = (playerR[0] != 'i');
    cout << "Aide : \"RandAI\" jouera aleatoirement." << endl
         << "\"Bruteforce\" (J1) peux jouer en plateau de taille max 2." << endl
         << "J1 'x' joue \"haut/bas\" tandis que J2 'o' joue \"gauche/droite\"." << endl
         << "Entrez le nom du joueur 1 (rouge) : ";
    cin >> playerR;
    cout << "Entrez le nom du joueur 2 (bleu) : ";
    cin >> playerL;
    moves.setPlayers(playerR, playerL);
    cout << "Entrez la taille du plateau de jeu (2 <= t <= 15) : ";
    unsigned short nL;
    cin >> nL;
    length = nL;
    if(moves.setLength(length+0)) {
        cout << "Taille : " << length+0 << endl;
    } else {
        length = 11;
        cerr << "Taille '" << nL << "' impossible..." << endl
             << "Nouvelle Taille : " << length+0 << endl;
    }
    if(playerR == "Bruteforce") {
        bf1.generateRecursiveMovesTree(length, true, false);
        bf1.displayMovesTree();
    }
    if(playerL == "Bruteforce") {
        bf2.generateRecursiveMovesTree(length, false, false);
        bf2.displayMovesTree();
    }
    moves.displayBoard();
    player1 = true;
    turnPlayed = false;
    keepGoing = true;
    colors = new float[length * length * 3];
    for(nL = 0; nL < length * length * 3; ++nL) colors[nL] = 1;

    thread console(play);

	GLFWwindow *window;

	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) {
		cout << "Failed to initialize glfw context" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(690, 420, "Hexxxor3000", NULL, NULL);
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
		color = true;
		glDrawFlatI(windowWidth, windowHeight);
		color = false;
		glDrawFlatI(windowWidth, windowHeight);

		// Enable vertex table
        /*glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        // Send data
        glVertexPointer(P_SIZE, GL_FLOAT, 0, pos);
        glColorPointer(C_SIZE, GL_FLOAT, 0, colors);

        // Draw stuff
        glDrawElements(GL_POLYGON, N_VERTS, GL_UNSIGNED_INT, index);

        // Disable vertex table
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);*/

		// Update Screen
		glFlush();
		glfwSwapBuffers(window);

		// Wait for any input, or window movement
		if(keepGoing)
            glfwWaitEventsTimeout(0.25);
		else break;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	if(keepGoing) {
        while(!playing.try_lock()) sleep(0.1);
        playConsole = true;
        playing.unlock();
	}
	console.join();

    return 0;
}
