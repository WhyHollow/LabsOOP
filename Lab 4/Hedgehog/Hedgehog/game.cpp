#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include "game.h"

void unit(int, int);
int random(int, int);

bool seedflag = false;
bool food = false;
int rows = 0, columns = 0;
int direction = NULL;
int foodx[10], foody[10];
int posx = 1;
int posy = 1;
int count;
bool check[10];

GLuint	texture[4];

void initGrid(int x, int y)
{
	columns = x;
	rows = y;
}

void draw_grid()
{
	for (int i = 0; i<columns; i++)
	{
		for (int j = 0; j<rows; j++)
		{
			unit(i, j);
		}
	}
}

void draw_snake()
{

	glColor4f(1.0, 1.0, 1.0, 1.0);

	switch (direction)
	{
	case UP:
		posy++;
		direction = NULL;
		break;
	case DOWN:
		posy--;
		direction = NULL;
		break;
	case RIGHT:
		posx++;
		direction = NULL;
		break;
	case LEFT:
		posx--;
		direction = NULL;
		break;
	default:
		break;
	}
	if (posx != 0 && posx != columns - 1 && posy != 0 && posy != rows - 1)
	{
		for (int i = 0; i < 10; i++) {
			if (posx == foodx[i] && posy == foody[i]) {
				check[i] = false;
			}
		}
	}
	if (posx == 0)
		posx = 1;
	if(posx == columns - 1)
		posx = columns - 2;
	if(posy == 0)
		posy = 1;
	if (posy == rows - 1)
		posy = rows - 2;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(posx, posy);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(posx + 1, posy);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(posx + 1, posy + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(posx, posy + 1);
	glEnd();

	glFlush();
	glDisable(GL_TEXTURE_2D);

}

void foods(int check, int i){
	if (check != 0){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glLoadIdentity();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(foodx[i], foody[i]);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(foodx[i] + 1, foody[i]);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(foodx[i] + 1, foody[i] + 1);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(foodx[i], foody[i] + 1);
		glEnd();

		glFlush();
		glDisable(GL_TEXTURE_2D);
		count++;
	}
}
void draw_food()
{
	if (count == 0)
		food = false;
	count = 0;
	if (!food)
	{
		for (int i = 0; i < 10; i++){
			foodx[i] = random(2, columns - 2);
			foody[i] = random(2, rows - 2);
			check[i] = true;
			std::cout << foodx[i] << " " << foody[i] << std::endl;
		}
		food = true;
	}
	for (int i = 0; i < 10; i++){
		foods(check[i], i);
	}
}

void unit(int x, int y)
{
	if (x == 0 || x == columns - 1 || y == 0 || y == rows - 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glLoadIdentity();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1, y);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(x + 1, y + 1);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y + 1);
		glEnd();

		glFlush();
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glLoadIdentity();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1, y);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(x + 1, y + 1);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y + 1);
		glEnd();

		glFlush();
		glDisable(GL_TEXTURE_2D);
	}
}
int random(int _min, int _max)
{
	if (!seedflag)
	{
		srand(time(NULL));
		seedflag = true;
	}
	//else
	//seedflag = false;
	return _min + rand() % (_max - _min);
}
