#include "Utilities.h"
#include "Highway.h"
#include <string>
using namespace std;

void StartHighway(int argc, char **argv) {
	// Initial construction (Makes the console and sets size etc.)
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_X,WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("Group Project Team: Toasters");
	glClearColor(1.0,1.0,1.0,0.0);
	gluOrtho2D(0,WINDOW_WIDTH, 0,WINDOW_HEIGHT);
}


void Highway::draw(void) {

    setColor(11);
	// This draws the highway
	
	for (int i = 0; i <= lanes - 1; ++i) {
		drawLine(0, yaxis - (i * 20), width, yaxis - (i * 20));
	}	
}

void Highway::SetSpawns() {
	for (int i = 0; i <= lanes - 2; ++i) {
		if(i <= lanes - 1) {
			Spawns[i] = (yaxis - 10) - (i * 20);
		}
	}	
}

Highway::Highway() {
	// This will set the properties for each highway drawn on the console
	width = WINDOW_WIDTH; // Window_width is the default width of the whole program itself. This is to get exact size lines for the highway that will fit

}