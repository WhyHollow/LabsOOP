#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "game.h"
#include "RgbImage.h"


#define ROWS 10.0
#define COLUMNS 10.0

extern GLuint	texture[4];


extern int direction;

void init();
void display_callback();
void input_callback(int, int, int);
void reshape_callback(int, int);
void timer_callback(int);
char* filename1 = "./water.bmp",
*filename2 = "./grass.bmp",
*filename3 = "./apple.bmp",
*filename4 = "./hedgehog.bmp";

void loadTextureFromFile(char *filename, int i)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
	glGenTextures(1, &texture[i]);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Typical Texture Generation Using Data From The Bitmap

	glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hedgehog");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable(GL_BLEND);
	loadTextureFromFile(filename1, 0);
	loadTextureFromFile(filename2, 1);
	loadTextureFromFile(filename3, 2);
	loadTextureFromFile(filename4, 3);

	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutSpecialFunc(input_callback);
	glutTimerFunc(100, timer_callback, 0);
	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	initGrid(COLUMNS, ROWS);
}

//Callbacks
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	draw_snake();
	draw_food();
	draw_grid();
	glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLfloat)w, GLfloat(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer_callback, 0);
}
void input_callback(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
			direction = UP;
		break;
	case GLUT_KEY_DOWN:
			direction = DOWN;
		break;
	case GLUT_KEY_RIGHT:
			direction = RIGHT;
		break;
	case GLUT_KEY_LEFT:
			direction = LEFT;
		break;
	}
}
